// Hook DLL: injected into the target process by the launcher (via a
// suspended-process + remote LoadLibrary, see ui/main.cpp's StartCapture)
// -- it is NOT loaded via the opengl32.dll search-order trick, so the
// target's own opengl32.dll/gdi32.dll load exactly once, normally, the
// same way they would without us. On load, this patches import tables so:
//   - statically-imported GL/WGL functions (glBegin, glClear, ...) route
//     through our wrappers directly;
//   - wglGetProcAddress (also just an ordinary import) is redirected to
//     our own version, which hands back our wrappers for anything fetched
//     dynamically (buffers, shaders, FBOs, ...) while still resolving the
//     real address underneath so our wrapper can call through;
//   - SwapBuffers (imported from gdi32.dll) and wglSwapBuffers (imported
//     from opengl32.dll, for the rarer app that calls it directly) both
//     mark a frame boundary in the trace before presenting.
// This avoids ever loading a second copy of the real driver, which is
// what made captures unreliable when the interceptor was itself posing as
// opengl32.dll (see README's former "known issues" -- loading the driver
// twice produced a non-functional "zombie" context on some machines).
//
// All of the above is patched not just in the main EXE's own import table,
// but in *every* module already loaded in the process at attach time (see
// PatchModuleGLHooks/EnumerateProcessModules) -- some targets (e.g. an app
// using GLFW) delegate all of their GL/GDI/WGL calls to a dependency DLL
// rather than importing them directly themselves, so patching only the
// main EXE's table would silently intercept nothing.
//
// On top of that, GetProcAddress/LoadLibraryA/LoadLibraryW themselves are
// hooked (wherever KERNEL32.dll is imported, i.e. in every such module
// too): some loaders (GLFW's own WGL backend among them) never let
// opengl32.dll appear in any module's static import table at all -- they
// LoadLibraryA("opengl32.dll") themselves at runtime and resolve every
// single GL/WGL function, including wglGetProcAddress itself, via raw
// GetProcAddress calls on that handle. Neither of those calls goes through
// any import-table slot we could patch up front, so the only remaining
// hook point is GetProcAddress itself: whichever module calls it, for
// whichever name, MyGetProcAddress gets to redirect known GL/WGL names to
// our wrappers before handing back a real address. MyLoadLibraryA/W exist
// so a module loaded *after* our initial pass (or opengl32.dll loaded
// afterwards by name) still gets its own imports patched the same way.
#include <windows.h>
#include <psapi.h>

#include <cstdio>
#include <cstring>
#include <mutex>
#include <unordered_set>
#include <vector>

#include "gl_lookup_table.h"
#include "gl_real_table.h"
#include "iat_patch.h"
#include "trace_writer.h"

TraceWriter g_trace;

namespace {

typedef void* (WINAPI* PFN_wglGetProcAddress)(const char*);
typedef BOOL(WINAPI* PFN_SwapBuffers)(HDC);
typedef BOOL(WINAPI* PFN_wglSwapBuffers)(HDC);

PFN_wglGetProcAddress g_realWglGetProcAddress;
PFN_SwapBuffers g_realSwapBuffers;
PFN_wglSwapBuffers g_realWglSwapBuffers;
HMODULE g_selfModule; // our own hook DLL -- never patched, so its own calls to the real APIs stay real
HANDLE g_captureFrameEvent = nullptr;

void* WINAPI MyWglGetProcAddress(const char* name);
BOOL WINAPI MySwapBuffers(HDC hdc);
BOOL WINAPI MyWglSwapBuffers(HDC hdc);
FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName);
HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName);
HMODULE WINAPI MyLoadLibraryW(LPCWSTR lpLibFileName);

const char* TracePathFromEnv() {
    static char path[MAX_PATH];
    DWORD n = GetEnvironmentVariableA("GLCAP_TRACE_PATH", path, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) snprintf(path, sizeof(path), "gl_capture.trace");
    return path;
}

const char* CaptureModeFromEnv() {
    static char mode[32];
    DWORD n = GetEnvironmentVariableA("GLCAP_CAPTURE_MODE", mode, static_cast<DWORD>(sizeof(mode)));
    if (n == 0 || n >= sizeof(mode)) return "all";
    return mode;
}

std::string CaptureEventNameFromEnv() {
    char name[256];
    DWORD n = GetEnvironmentVariableA("GLCAP_CAPTURE_EVENT", name, static_cast<DWORD>(sizeof(name)));
    if (n == 0 || n >= sizeof(name)) return {};
    return std::string(name);
}

void PollCaptureFrameRequest() {
    if (!g_captureFrameEvent) return;
    if (WaitForSingleObject(g_captureFrameEvent, 0) == WAIT_OBJECT_0) {
        g_trace.ArmOneFrame();
    }
}

void* ResolveOpenGLImport(const char* name) {
    if (strcmp(name, "wglGetProcAddress") == 0) return reinterpret_cast<void*>(&MyWglGetProcAddress);
    if (strcmp(name, "wglSwapBuffers") == 0) return reinterpret_cast<void*>(&MyWglSwapBuffers);
    return LookupWrapper(name);
}

void OnOpenGLImportPatched(const char* name, void* realAddr) {
    if (strcmp(name, "wglGetProcAddress") == 0) { g_realWglGetProcAddress = reinterpret_cast<PFN_wglGetProcAddress>(realAddr); return; }
    if (strcmp(name, "wglSwapBuffers") == 0) { g_realWglSwapBuffers = reinterpret_cast<PFN_wglSwapBuffers>(realAddr); return; }
    StoreRealPointer(name, realAddr);
}

void* ResolveGdiImport(const char* name) {
    if (strcmp(name, "SwapBuffers") == 0) return reinterpret_cast<void*>(&MySwapBuffers);
    return nullptr;
}

void OnGdiImportPatched(const char* name, void* realAddr) {
    if (strcmp(name, "SwapBuffers") == 0) g_realSwapBuffers = reinterpret_cast<PFN_SwapBuffers>(realAddr);
}

void* ResolveLoaderImport(const char* name) {
    if (strcmp(name, "GetProcAddress") == 0) return reinterpret_cast<void*>(&MyGetProcAddress);
    if (strcmp(name, "LoadLibraryA") == 0) return reinterpret_cast<void*>(&MyLoadLibraryA);
    if (strcmp(name, "LoadLibraryW") == 0) return reinterpret_cast<void*>(&MyLoadLibraryW);
    return nullptr;
}

// Nothing to remember here: MyGetProcAddress/MyLoadLibrary* call straight
// through to the real kernel32 exports themselves (our own module's
// import table is never patched, see PatchModuleGLHooks), so there's no
// separate "real pointer" to stash the way OnOpenGLImportPatched/
// OnGdiImportPatched need to for functions our wrappers call through.
void OnLoaderImportPatched(const char*, void*) {}

std::mutex g_patchMutex;
std::unordered_set<HMODULE> g_patchedModules; // re-patching an already-patched module would feed our own wrapper's address back in as "the real one" -- see PatchImports' realAddr capture

// Patches one module's opengl32.dll/gdi32.dll/loader imports (the
// GL/WGL/GDI functions themselves, plus GetProcAddress/LoadLibraryA/W so
// dynamically-resolved or not-yet-loaded modules get caught too). Safe to
// call on the same module repeatedly -- only the first call actually does
// anything, later ones no-op via g_patchedModules -- and safe to call
// speculatively on any HMODULE (PatchImports itself tolerates a module
// with no import directory or a malformed header).
void PatchModuleGLHooks(HMODULE module) {
    if (!module || module == g_selfModule) return;
    std::lock_guard<std::mutex> lock(g_patchMutex);
    if (!g_patchedModules.insert(module).second) return; // already patched
    PatchImports(module, "opengl32.dll", ResolveOpenGLImport, OnOpenGLImportPatched);
    PatchImports(module, "gdi32.dll", ResolveGdiImport, OnGdiImportPatched);
    PatchImports(module, "kernel32.dll", ResolveLoaderImport, OnLoaderImportPatched);
    PatchImports(module, "KernelBase.dll", ResolveLoaderImport, OnLoaderImportPatched);
    PatchImports(module, "KERNELBASE.dll", ResolveLoaderImport, OnLoaderImportPatched);
    PatchImports(module, "api-ms-win-core-libraryloader-l1-2-0.dll", ResolveLoaderImport, OnLoaderImportPatched);
    PatchImports(module, "api-ms-win-core-libraryloader-l1-1-0.dll", ResolveLoaderImport, OnLoaderImportPatched);
}

// Every module currently loaded in this process, via the Kernel32-hosted
// EnumProcessModules (no Psapi.lib needed, unlike the pre-Vista version).
// Retries with a bigger buffer if the module list grew between the sizing
// call and the real one.
std::vector<HMODULE> EnumerateProcessModules() {
    HANDLE proc = GetCurrentProcess();
    std::vector<HMODULE> mods(64);
    for (int attempt = 0; attempt < 4; ++attempt) {
        DWORD needed = 0;
        DWORD bytes = static_cast<DWORD>(mods.size() * sizeof(HMODULE));
        if (!K32EnumProcessModules(proc, mods.data(), bytes, &needed)) return {};
        size_t count = needed / sizeof(HMODULE);
        if (count <= mods.size()) {
            mods.resize(count);
            return mods;
        }
        mods.resize(count);
    }
    return mods;
}

void* WINAPI MyWglGetProcAddress(const char* name) {
    void* real = g_realWglGetProcAddress ? g_realWglGetProcAddress(name) : nullptr;
    void* ours = LookupWrapper(name);
    if (ours) {
        if (!real) {
            // The real wglGetProcAddress legitimately returns null for
            // GL1.1 core functions (glGetIntegerv, glGetString, glFlush,
            // ...) -- per its documented contract, those have to be
            // resolved via plain GetProcAddress on opengl32.dll's own
            // export table instead (see gl_real_table.h's comment on
            // LoadRealGLFunctions, which already does this two-tier
            // lookup for the replay side). Without this fallback,
            // g_real.<fn> would stay null forever for any such function a
            // target resolves exclusively through (wgl)GetProcAddress
            // rather than a static import -- as GLFW/GLAD-style loaders
            // do -- silently turning it into a no-op instead of a capture.
            real = reinterpret_cast<void*>(GetProcAddress(GetModuleHandleA("opengl32.dll"), name));
        }
        if (real) StoreRealPointer(name, real);
        return ours;
    }
    return real;
}

BOOL WINAPI MySwapBuffers(HDC hdc) {
    PollCaptureFrameRequest();
    g_trace.MarkFrameEnd();
    return g_realSwapBuffers ? g_realSwapBuffers(hdc) : FALSE;
}

BOOL WINAPI MyWglSwapBuffers(HDC hdc) {
    PollCaptureFrameRequest();
    g_trace.MarkFrameEnd();
    return g_realWglSwapBuffers ? g_realWglSwapBuffers(hdc) : FALSE;
}

// Global GetProcAddress hook: whichever module calls this (regardless of
// which module handle it passes, or how it obtained it -- LoadLibrary'd
// itself or otherwise), a known GL/WGL name gets redirected to our
// wrapper here, the same way a patched import-table slot would. This is
// the only interception point left for a loader (GLFW's WGL backend, gl3w,
// GLAD-style loaders, ...) that fetches opengl32.dll and every one of its
// functions -- including wglGetProcAddress itself -- purely at runtime,
// never through any static import.
FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
    FARPROC real = GetProcAddress(hModule, lpProcName);
    // Per GetProcAddress's own contract, an ordinal-imported function has
    // its ordinal in the low word of what's passed as lpProcName and zero
    // in the high word -- not a real string pointer at all in that case.
    if (reinterpret_cast<uintptr_t>(lpProcName) <= 0xFFFF) return real;

    if (strcmp(lpProcName, "wglGetProcAddress") == 0) {
        if (real) g_realWglGetProcAddress = reinterpret_cast<PFN_wglGetProcAddress>(real);
        return reinterpret_cast<FARPROC>(&MyWglGetProcAddress);
    }
    if (strcmp(lpProcName, "wglSwapBuffers") == 0) {
        if (real) g_realWglSwapBuffers = reinterpret_cast<PFN_wglSwapBuffers>(real);
        return reinterpret_cast<FARPROC>(&MyWglSwapBuffers);
    }
    if (strcmp(lpProcName, "SwapBuffers") == 0) {
        if (real) g_realSwapBuffers = reinterpret_cast<PFN_SwapBuffers>(real);
        return reinterpret_cast<FARPROC>(&MySwapBuffers);
    }
    if (void* wrapper = LookupWrapper(lpProcName)) {
        if (real) StoreRealPointer(lpProcName, real);
        return reinterpret_cast<FARPROC>(wrapper);
    }
    return real;
}

HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName) {
    HMODULE h = LoadLibraryA(lpLibFileName);
    PatchModuleGLHooks(h);
    return h;
}

HMODULE WINAPI MyLoadLibraryW(LPCWSTR lpLibFileName) {
    HMODULE h = LoadLibraryW(lpLibFileName);
    PatchModuleGLHooks(h);
    return h;
}

} // namespace

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_selfModule = static_cast<HMODULE>(hinstDLL);
        g_trace.Open(TracePathFromEnv());
        g_trace.ConfigureCaptureMode(CaptureModeFromEnv());
        if (g_trace.IsOneFrameMode()) {
            std::string eventName = CaptureEventNameFromEnv();
            if (!eventName.empty()) {
                g_captureFrameEvent = OpenEventA(SYNCHRONIZE, FALSE, eventName.c_str());
            }
        }
        for (HMODULE m : EnumerateProcessModules()) PatchModuleGLHooks(m);
    } else if (reason == DLL_PROCESS_DETACH) {
        if (g_captureFrameEvent) {
            CloseHandle(g_captureFrameEvent);
            g_captureFrameEvent = nullptr;
        }
        g_trace.Close();
    }
    return TRUE;
}

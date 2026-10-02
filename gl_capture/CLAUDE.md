# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

A Windows-only OpenGL call capture/replay tool for debugging rendering issues: inject into a target
process, log every GL call it makes (with enough data to reproduce it), and replay the trace against a
fresh context for inspection. See README.md for the full architecture writeup and detailed usage/UI
behavior (panel layout, call-list format, texture/shader viewers, known limitations) — this file covers
what's needed to build and extend the code productively.

## Build

Requires MSVC + CMake, and a prebuilt static wxWidgets at `../third_party/wxWidgets` (relative to this
directory) — the NuGet-style layout with `include/`, `include/msvc/`, and `lib/vc_x64_lib/` containing the
static Debug/Unicode (`*33ud*`) libs. **Only `--config Debug` is supported** (no Release wx libs are
vendored).

```bash
mkdir build && cd build
cmake -A x64 ..
cmake --build . --config Debug
```

Omit `-G`/let CMake pick the installed Visual Studio version — pinning a generator string breaks as soon
as VS auto-updates to a new major version.

Build individual targets with `--target`: `gl_capture_hook` (the hook DLL), `gl_replay`, `gl_capture_ui`,
`gl_capture_test_app`.

Outputs land in `build/Debug/gl_capture_hook.dll` and `build/Debug/{gl_capture_ui,gl_replay,
gl_capture_test_app}.exe`.

**No test suite and no lint config exist in this repo.** The closest thing to a smoke test is running
`gl_capture_ui.exe` against the bundled `gl_capture_test_app.exe` (its default target when no target is
given) and then replaying the resulting trace; `GLCAP_REPLAY_AUTOEXIT=1` makes `gl_replay.exe` replay once
and exit immediately instead of opening its UI, useful for scripted checks.

**Rebuilding while a previous run is still open will fail to link** (`LNK1168`) because the `.exe`/`.dll`
is locked by the running process — check for and kill lingering `gl_capture_ui.exe` / `gl_replay.exe` /
`gl_capture_test_app.exe` processes before rebuilding.

## Adding or changing a traced GL function

`codegen/functions.json` is the source of truth for which GL functions are known; `codegen/generate.py`
turns it into `generated/*.{h,cpp}` (checked in, not built by CMake — rerun the generator by hand after
editing `functions.json`):

```bash
python codegen/generate.py
```

- A function with only value/enum arguments needs nothing else — codegen emits its capture wrapper,
  replay decoder, and call-list formatter automatically.
- A function with pointer/array arguments (buffer data, vertex/texture data, shader source, id arrays,
  ...) needs `"custom": true` in `functions.json`, and a **hand-written triplet** across:
  - `interceptor/custom_wrappers.cpp` — capture-side: serializes the call's bytes to the trace.
  - `replay/custom_replay.cpp` — replay-side: must decode *exactly* the same byte layout, in the same
    order, then re-issue the call (remapping object ids via `IdRemapper` as needed).
  - `replay/custom_format.cpp` — same decode again, but builds a display string for the call-list panel
    instead of replaying.

  **Nothing enforces these three stay in sync.** A layout change in one without matching changes in the
  other two won't fail to compile — it will silently misdecode or misdisplay. When touching one, check
  the other two.
- A function that must be exported by name but should never be traced (e.g. so a statically-linked
  `GLU32.dll` doesn't fail to load with "entry point not found") gets `"passthrough": true` instead.

The desktop OpenGL registry is vendored in `codegen/gl.xml`. Run
`python codegen/import_gl_registry.py` to regenerate
`codegen/registry_commands.json`, which contains the 1.0-4.6 core and
compatibility command signatures plus pointer-length metadata. This registry
metadata is the source for the typed trace migration; it is deliberately
separate from `functions.json` until each command has a verified capture and
replay policy.

`common/typed_trace.h` defines the versioned argument envelope for migrated
handlers. It distinguishes scalar values, object names, strings, input/output
buffers, and return values. `TraceWriter::BeginTypedCall` writes this envelope
using the existing record format and `kTypedRecordFlag`, so legacy `GLCAP001`
records remain readable while migrated records can be decoded without
hand-maintained byte-layout assumptions.

`python codegen/merge_registry_scalar_commands.py` promotes registry commands
that have only scalar parameters and a `void` return into the active generated
table. These commands are safe to migrate mechanically. Pointer-bearing,
returning, and object-namespace commands remain pending custom handlers until
their replay semantics are implemented.

## Architecture

Five pieces, three of which are CMake targets:

- **`codegen/`** — not built; `generate.py` + `functions.json` (which functions) + `gl_enums.json`
  (~4000 Khronos enum names, for symbolic display) emit `generated/`.
- **`interceptor/`** → `gl_capture_hook.dll`. Injected into an already-running suspended target process
  (see `ui/main.cpp`'s `InjectHookDll`), *not* dropped in as a same-named `opengl32.dll` proxy. This means
  the real driver loads exactly once, normally — the previous same-named-proxy design caused unreliable
  "zombie" contexts on some machines from loading it twice (see README's Known issues). On load
  (`dllmain.cpp`) it patches import tables in **every module currently loaded in the process**
  (`PatchModuleGLHooks` + `EnumerateProcessModules`, not just the main EXE) so statically-imported GL/WGL
  calls redirect to our wrappers and `SwapBuffers`/`wglSwapBuffers` mark frame boundaries — some targets
  (e.g. anything using GLFW) delegate all of their GL/GDI calls to a dependency DLL rather than importing
  them directly themselves, so patching only the main EXE would silently intercept nothing. On top of
  that, `GetProcAddress`/`LoadLibraryA`/`LoadLibraryW` are themselves hooked wherever `kernel32.dll` is
  imported (`MyGetProcAddress`/`MyLoadLibraryA`/`MyLoadLibraryW`), because some loaders (GLFW's own WGL
  backend, GLAD, gl3w) never let `opengl32.dll` appear in any module's static import table at all — they
  `LoadLibraryA("opengl32.dll")` themselves at runtime and resolve every GL/WGL function, including
  `wglGetProcAddress` itself, via raw `GetProcAddress` calls on that handle. `MyLoadLibraryA/W` patch a
  module's imports the moment it's loaded, so this isn't limited to what's present at attach time either.
  **Non-obvious pitfall already hit once**: the real `wglGetProcAddress` legitimately returns `NULL` for
  GL1.1 core functions (`glGetIntegerv`, `glGetString`, `glFlush`, ...) — that's documented WGL behavior,
  not a failure — so `MyWglGetProcAddress` falls back to plain `GetProcAddress` on `opengl32.dll`'s own
  export table in that case. Skipping that fallback silently turns every such function into a permanent
  no-op for any target that resolves it exclusively through `wglGetProcAddress` (as GLFW/GLAD-style
  loaders do), which broke GLFW's own post-context-creation `glGetString` sanity check and made
  `glfwCreateWindow` itself fail outright — a good reminder that a "capture nothing" bug here can surface
  as a completely unrelated-looking failure in the target, not just an empty trace.
- **`replay/`** → `gl_replay.exe`. Loads a trace fully into memory, then replays it against a fresh GL
  context (state can't be rewound, so "run to call N" means restart from scratch and fast-forward, every
  time). wxWidgets UI; actual GL/WGL context setup is plain Win32 on a hidden window, decoupled from the
  wx render panel that displays the read-back pixels.
- **`ui/`** → `gl_capture_ui.exe`. Launcher: picks a target + trace path, launches it `CREATE_SUSPENDED`,
  injects the hook DLL via remote `LoadLibraryA`, resumes it, and can kick off `gl_replay.exe` afterward.
- **`test_app/`** → `gl_capture_test_app.exe`. Pure Win32/GDI (no wxWidgets) smoke-test target rendering a
  lit, textured cube into an FBO — exercises VBOs/VAOs/textures/FBOs/shaders in one run.
- **`common/`** — trace file format (`trace_format.h`), the `IdRemapper` (per-namespace captured-id →
  replay-id map, since the replay driver hands out different ids than the traced process saw), and
  minimal GL type defs kept deliberately separate from `<GL/gl.h>` to avoid dllimport/export collisions.

### Client-memory vertex array capture

The trickiest hand-written logic (`interceptor/client_array_state.h` + the draw-call wrappers in
`custom_wrappers.cpp`): whether a `*Pointer`/`glVertexAttribPointer` call's pointer is a real client
address (needs snapshotting) or a VBO byte offset (already captured via `glBufferData`) is latched *at
that call*, based on the `GL_ARRAY_BUFFER` binding then — matching GL's own semantics, since the
address-vs-offset interpretation is fixed at that moment, not at draw time. The actual byte snapshot,
though, is taken at the *draw* call, sized to exactly what's reachable (`first`/`count`, or the max index
found by scanning a client-memory index buffer for indexed draws). Known gap (also in README): a real VBO
index buffer paired with a client-memory vertex attribute isn't captured, since there's no way to know
which vertices are reachable without shadowing the index buffer's contents.

### Object id remapping

`IdRemapper` (common/id_remapper.h) keeps one map per GL object namespace (`"buffer"`, `"texture"`,
`"framebuffer"`, `"renderbuffer"`, `"vertexarray"`, `"shader"`, `"program"`) since GL's own namespaces are
already separate and the replay driver's ids never match the captured ones. Every `Replay_glGen*`/
`Replay_glDelete*` in `custom_replay.cpp` maps/unmaps; every consumer looks ids up through it.

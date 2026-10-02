#include "iat_patch.h"

#include <cstring>

int PatchImports(HMODULE module, const char* importedDllName, ResolveWrapperFn resolve, OnPatchedFn onPatched) {
    BYTE* base = reinterpret_cast<BYTE*>(module);
    auto* dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return 0;
    auto* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return 0;

    IMAGE_DATA_DIRECTORY importDir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (importDir.VirtualAddress == 0) return 0;

    auto* desc = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(base + importDir.VirtualAddress);
    int patched = 0;
    for (; desc->Name != 0; ++desc) {
        const char* dllName = reinterpret_cast<const char*>(base + desc->Name);
        if (_stricmp(dllName, importedDllName) != 0) continue;
        if (desc->OriginalFirstThunk == 0) continue; // no name table available for this descriptor

        auto* nameThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + desc->OriginalFirstThunk);
        auto* addrThunk = reinterpret_cast<IMAGE_THUNK_DATA*>(base + desc->FirstThunk);

        for (; nameThunk->u1.AddressOfData != 0; ++nameThunk, ++addrThunk) {
            if (IMAGE_SNAP_BY_ORDINAL(nameThunk->u1.Ordinal)) continue; // imported by ordinal, no name

            auto* byName = reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(base + nameThunk->u1.AddressOfData);
            const char* funcName = reinterpret_cast<const char*>(byName->Name);

            void* wrapper = resolve(funcName);
            if (!wrapper) continue;

            void* realAddr = reinterpret_cast<void*>(addrThunk->u1.Function);

            DWORD oldProtect;
            if (!VirtualProtect(&addrThunk->u1.Function, sizeof(void*), PAGE_READWRITE, &oldProtect)) continue;
            addrThunk->u1.Function = reinterpret_cast<ULONG_PTR>(wrapper);
            VirtualProtect(&addrThunk->u1.Function, sizeof(void*), oldProtect, &oldProtect);

            if (onPatched) onPatched(funcName, realAddr);
            ++patched;
        }
    }
    return patched;
}

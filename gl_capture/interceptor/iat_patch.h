#pragma once
#include <windows.h>

// Given an imported function's name, returns the address to redirect that
// import to, or nullptr to leave it untouched.
typedef void* (*ResolveWrapperFn)(const char* name);

// Called for every import actually redirected, with the address it
// originally pointed to (so the caller can save it and call through).
typedef void (*OnPatchedFn)(const char* name, void* realAddr);

// Walks `module`'s import descriptor for `importedDllName` (e.g.
// "opengl32.dll", case-insensitive) and, for each imported-by-name entry
// `resolve` returns non-null for, overwrites that IAT slot with the
// returned address. Imports without a name table (bound imports with no
// original-thunk data) or imported by ordinal are left untouched, since
// there's no name to match against. Returns the number of entries patched.
int PatchImports(HMODULE module, const char* importedDllName, ResolveWrapperFn resolve, OnPatchedFn onPatched);

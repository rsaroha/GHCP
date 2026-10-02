#include <windows.h>

#include "gl_inspect.h"

InspectGLFunctions g_inspect;

void LoadInspectFunctions(void* moduleHandle, void* (*getProcFn)(const char*)) {
    HMODULE mod = (HMODULE)moduleHandle;
#define LOAD(name) \
    g_inspect.name = (PFN_##name)GetProcAddress(mod, #name); \
    if (!g_inspect.name && getProcFn) g_inspect.name = (PFN_##name)getProcFn(#name);
    LOAD(glGetIntegerv)
    LOAD(glGetFloatv)
    LOAD(glIsEnabled)
    LOAD(glGetBufferParameteriv)
    LOAD(glGetTexLevelParameteriv)
    LOAD(glGetFramebufferAttachmentParameteriv)
    LOAD(glGetRenderbufferParameteriv)
    LOAD(glGetProgramiv)
    LOAD(glGetShaderiv)
    LOAD(glGetTexImage)
#undef LOAD
}

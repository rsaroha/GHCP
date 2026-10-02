#pragma once
#include "gl_types_min.h"

// A handful of read-only GL query functions used only by the replay tool's
// resource/state inspector -- kept separate from the capture-side function
// table since the interceptor never needs to call these itself.
typedef void(APIENTRY* PFN_glGetIntegerv)(GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetFloatv)(GLenum, GLfloat*);
typedef GLboolean(APIENTRY* PFN_glIsEnabled)(GLenum);
typedef void(APIENTRY* PFN_glGetBufferParameteriv)(GLenum, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetTexLevelParameteriv)(GLenum, GLint, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetFramebufferAttachmentParameteriv)(GLenum, GLenum, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetRenderbufferParameteriv)(GLenum, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetProgramiv)(GLuint, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetShaderiv)(GLuint, GLenum, GLint*);
typedef void(APIENTRY* PFN_glGetTexImage)(GLenum, GLint, GLenum, GLenum, void*);

struct InspectGLFunctions {
    PFN_glGetIntegerv glGetIntegerv = nullptr;
    PFN_glGetFloatv glGetFloatv = nullptr;
    PFN_glIsEnabled glIsEnabled = nullptr;
    PFN_glGetBufferParameteriv glGetBufferParameteriv = nullptr;
    PFN_glGetTexLevelParameteriv glGetTexLevelParameteriv = nullptr;
    PFN_glGetFramebufferAttachmentParameteriv glGetFramebufferAttachmentParameteriv = nullptr;
    PFN_glGetRenderbufferParameteriv glGetRenderbufferParameteriv = nullptr;
    PFN_glGetProgramiv glGetProgramiv = nullptr;
    PFN_glGetShaderiv glGetShaderiv = nullptr;
    PFN_glGetTexImage glGetTexImage = nullptr;
};

extern InspectGLFunctions g_inspect;

void LoadInspectFunctions(void* moduleHandle, void* (*getProcFn)(const char*));

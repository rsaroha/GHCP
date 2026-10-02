// GENERATED FILE - do not edit by hand. See codegen/generate.py
#pragma once
#include "gl_ids.h"
#include "id_remapper.h"
#include <cstdint>
#include <cstddef>

// Dispatches one decoded call. `args`/`len` is the raw argument
// blob written by the interceptor for this call.
void ReplayDispatch(GLFuncId id, const uint8_t* args, size_t len, IdRemapper& remap);

extern "C" {
void Replay_glGenBuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDeleteBuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glBindBuffer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glBufferData(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glBufferSubData(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGenVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDeleteVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertexAttribPointer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertexPointer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glColorPointer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexCoordPointer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNormalPointer(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGenTextures(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDeleteTextures(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexImage2D(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexSubImage2D(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glShaderSource(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glBindAttribLocation(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetUniformLocation(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetAttribLocation(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glUniformMatrix4fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glUniformMatrix3fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGenFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDeleteFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGenRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDeleteRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDrawArrays(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDrawElements(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDrawArraysInstanced(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDrawElementsInstanced(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetString(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glColor3ubv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glColor4dv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glColor4fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glColor4usv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetBooleanv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetFloatv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetIntegerv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glInterleavedArrays(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glLightModelfv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glLightfv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glLoadMatrixd(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glLoadMatrixf(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNormal3dv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNormal3fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexCoord2dv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexCoord2fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTexCoord2iv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertex3dv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertex3fv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertex3iv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glVertex4sv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glClearBufferfv(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glCreateBuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glCreateFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glCreateRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glCreateTextures(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glCreateVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glDebugMessageInsert(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetProgramInfoLog(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glGetShaderInfoLog(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNamedBufferStorage(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNamedBufferSubData(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glNamedFramebufferDrawBuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTextureSubImage2D(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_glTextureSubImage3D(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglCreateContext(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglDeleteContext(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglMakeCurrent(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglShareLists(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglSwapLayerBuffers(const uint8_t* args, size_t len, IdRemapper& remap);
void Replay_wglCreateContextAttribsARB(const uint8_t* args, size_t len, IdRemapper& remap);
}

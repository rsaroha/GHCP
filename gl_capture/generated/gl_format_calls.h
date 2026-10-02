// GENERATED FILE - do not edit by hand. See codegen/generate.py
#pragma once
#include "gl_ids.h"
#include <cstdint>
#include <cstddef>
#include <string>

std::string FormatCall(GLFuncId id, const uint8_t* args, size_t len);

// Hand-written in replay/custom_format.cpp, for calls with pointer/array args.
std::string Format_glGenBuffers(const uint8_t* args, size_t len);
std::string Format_glDeleteBuffers(const uint8_t* args, size_t len);
std::string Format_glBindBuffer(const uint8_t* args, size_t len);
std::string Format_glBufferData(const uint8_t* args, size_t len);
std::string Format_glBufferSubData(const uint8_t* args, size_t len);
std::string Format_glGenVertexArrays(const uint8_t* args, size_t len);
std::string Format_glDeleteVertexArrays(const uint8_t* args, size_t len);
std::string Format_glVertexAttribPointer(const uint8_t* args, size_t len);
std::string Format_glVertexPointer(const uint8_t* args, size_t len);
std::string Format_glColorPointer(const uint8_t* args, size_t len);
std::string Format_glTexCoordPointer(const uint8_t* args, size_t len);
std::string Format_glNormalPointer(const uint8_t* args, size_t len);
std::string Format_glGenTextures(const uint8_t* args, size_t len);
std::string Format_glDeleteTextures(const uint8_t* args, size_t len);
std::string Format_glTexImage2D(const uint8_t* args, size_t len);
std::string Format_glTexSubImage2D(const uint8_t* args, size_t len);
std::string Format_glShaderSource(const uint8_t* args, size_t len);
std::string Format_glBindAttribLocation(const uint8_t* args, size_t len);
std::string Format_glGetUniformLocation(const uint8_t* args, size_t len);
std::string Format_glGetAttribLocation(const uint8_t* args, size_t len);
std::string Format_glUniformMatrix4fv(const uint8_t* args, size_t len);
std::string Format_glUniformMatrix3fv(const uint8_t* args, size_t len);
std::string Format_glGenFramebuffers(const uint8_t* args, size_t len);
std::string Format_glDeleteFramebuffers(const uint8_t* args, size_t len);
std::string Format_glGenRenderbuffers(const uint8_t* args, size_t len);
std::string Format_glDeleteRenderbuffers(const uint8_t* args, size_t len);
std::string Format_glDrawArrays(const uint8_t* args, size_t len);
std::string Format_glDrawElements(const uint8_t* args, size_t len);
std::string Format_glDrawArraysInstanced(const uint8_t* args, size_t len);
std::string Format_glDrawElementsInstanced(const uint8_t* args, size_t len);
std::string Format_glGetString(const uint8_t* args, size_t len);
std::string Format_glColor3ubv(const uint8_t* args, size_t len);
std::string Format_glColor4dv(const uint8_t* args, size_t len);
std::string Format_glColor4fv(const uint8_t* args, size_t len);
std::string Format_glColor4usv(const uint8_t* args, size_t len);
std::string Format_glGetBooleanv(const uint8_t* args, size_t len);
std::string Format_glGetFloatv(const uint8_t* args, size_t len);
std::string Format_glGetIntegerv(const uint8_t* args, size_t len);
std::string Format_glInterleavedArrays(const uint8_t* args, size_t len);
std::string Format_glLightModelfv(const uint8_t* args, size_t len);
std::string Format_glLightfv(const uint8_t* args, size_t len);
std::string Format_glLoadMatrixd(const uint8_t* args, size_t len);
std::string Format_glLoadMatrixf(const uint8_t* args, size_t len);
std::string Format_glNormal3dv(const uint8_t* args, size_t len);
std::string Format_glNormal3fv(const uint8_t* args, size_t len);
std::string Format_glTexCoord2dv(const uint8_t* args, size_t len);
std::string Format_glTexCoord2fv(const uint8_t* args, size_t len);
std::string Format_glTexCoord2iv(const uint8_t* args, size_t len);
std::string Format_glVertex3dv(const uint8_t* args, size_t len);
std::string Format_glVertex3fv(const uint8_t* args, size_t len);
std::string Format_glVertex3iv(const uint8_t* args, size_t len);
std::string Format_glVertex4sv(const uint8_t* args, size_t len);
std::string Format_glClearBufferfv(const uint8_t* args, size_t len);
std::string Format_glCreateBuffers(const uint8_t* args, size_t len);
std::string Format_glCreateFramebuffers(const uint8_t* args, size_t len);
std::string Format_glCreateRenderbuffers(const uint8_t* args, size_t len);
std::string Format_glCreateTextures(const uint8_t* args, size_t len);
std::string Format_glCreateVertexArrays(const uint8_t* args, size_t len);
std::string Format_glDebugMessageInsert(const uint8_t* args, size_t len);
std::string Format_glGetProgramInfoLog(const uint8_t* args, size_t len);
std::string Format_glGetShaderInfoLog(const uint8_t* args, size_t len);
std::string Format_glNamedBufferStorage(const uint8_t* args, size_t len);
std::string Format_glNamedBufferSubData(const uint8_t* args, size_t len);
std::string Format_glNamedFramebufferDrawBuffers(const uint8_t* args, size_t len);
std::string Format_glTextureSubImage2D(const uint8_t* args, size_t len);
std::string Format_glTextureSubImage3D(const uint8_t* args, size_t len);
std::string Format_wglCreateContext(const uint8_t* args, size_t len);
std::string Format_wglDeleteContext(const uint8_t* args, size_t len);
std::string Format_wglMakeCurrent(const uint8_t* args, size_t len);
std::string Format_wglShareLists(const uint8_t* args, size_t len);
std::string Format_wglSwapLayerBuffers(const uint8_t* args, size_t len);
std::string Format_wglCreateContextAttribsARB(const uint8_t* args, size_t len);


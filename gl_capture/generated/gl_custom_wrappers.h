// GENERATED FILE - do not edit by hand. See codegen/generate.py
// Hand-written implementations live in interceptor/custom_wrappers.cpp
#pragma once
#include "gl_types_min.h"
#include "gl_real_table.h"  // defines APIENTRYGEN

extern "C" {
void APIENTRYGEN glGenBuffers(GLsizei n, GLuint* buffers);
void APIENTRYGEN glDeleteBuffers(GLsizei n, const GLuint* buffers);
void APIENTRYGEN glBindBuffer(GLenum target, GLuint buffer);
void APIENTRYGEN glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
void APIENTRYGEN glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
void APIENTRYGEN glGenVertexArrays(GLsizei n, GLuint* arrays);
void APIENTRYGEN glDeleteVertexArrays(GLsizei n, const GLuint* arrays);
void APIENTRYGEN glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
void APIENTRYGEN glVertexPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
void APIENTRYGEN glColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
void APIENTRYGEN glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
void APIENTRYGEN glNormalPointer(GLenum type, GLsizei stride, const void* pointer);
void APIENTRYGEN glGenTextures(GLsizei n, GLuint* textures);
void APIENTRYGEN glDeleteTextures(GLsizei n, const GLuint* textures);
void APIENTRYGEN glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
void APIENTRYGEN glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
void APIENTRYGEN glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
void APIENTRYGEN glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);
GLint APIENTRYGEN glGetUniformLocation(GLuint program, const GLchar* name);
GLint APIENTRYGEN glGetAttribLocation(GLuint program, const GLchar* name);
void APIENTRYGEN glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void APIENTRYGEN glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void APIENTRYGEN glGenFramebuffers(GLsizei n, GLuint* framebuffers);
void APIENTRYGEN glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
void APIENTRYGEN glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
void APIENTRYGEN glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
void APIENTRYGEN glDrawArrays(GLenum mode, GLint first, GLsizei count);
void APIENTRYGEN glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
void APIENTRYGEN glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
void APIENTRYGEN glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);
const GLubyte* APIENTRYGEN glGetString(GLenum name);
void APIENTRYGEN glColor3ubv(const GLubyte * v);
void APIENTRYGEN glColor4dv(const GLdouble * v);
void APIENTRYGEN glColor4fv(const GLfloat * v);
void APIENTRYGEN glColor4usv(const GLushort * v);
void APIENTRYGEN glGetBooleanv(GLenum pname, GLboolean * data);
void APIENTRYGEN glGetFloatv(GLenum pname, GLfloat * data);
void APIENTRYGEN glGetIntegerv(GLenum pname, GLint * data);
void APIENTRYGEN glInterleavedArrays(GLenum format, GLsizei stride, const void * pointer);
void APIENTRYGEN glLightModelfv(GLenum pname, const GLfloat * params);
void APIENTRYGEN glLightfv(GLenum light, GLenum pname, const GLfloat * params);
void APIENTRYGEN glLoadMatrixd(const GLdouble * m);
void APIENTRYGEN glLoadMatrixf(const GLfloat * m);
void APIENTRYGEN glNormal3dv(const GLdouble * v);
void APIENTRYGEN glNormal3fv(const GLfloat * v);
void APIENTRYGEN glTexCoord2dv(const GLdouble * v);
void APIENTRYGEN glTexCoord2fv(const GLfloat * v);
void APIENTRYGEN glTexCoord2iv(const GLint * v);
void APIENTRYGEN glVertex3dv(const GLdouble * v);
void APIENTRYGEN glVertex3fv(const GLfloat * v);
void APIENTRYGEN glVertex3iv(const GLint * v);
void APIENTRYGEN glVertex4sv(const GLshort * v);
void APIENTRYGEN glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value);
void APIENTRYGEN glCreateBuffers(GLsizei n, GLuint * buffers);
void APIENTRYGEN glCreateFramebuffers(GLsizei n, GLuint * framebuffers);
void APIENTRYGEN glCreateRenderbuffers(GLsizei n, GLuint * renderbuffers);
void APIENTRYGEN glCreateTextures(GLenum target, GLsizei n, GLuint * textures);
void APIENTRYGEN glCreateVertexArrays(GLsizei n, GLuint * arrays);
void APIENTRYGEN glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
void APIENTRYGEN glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void APIENTRYGEN glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void APIENTRYGEN glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
void APIENTRYGEN glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
void APIENTRYGEN glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs);
void APIENTRYGEN glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
void APIENTRYGEN glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
HGLRC APIENTRYGEN wglCreateContext(HDC hdc);
BOOL APIENTRYGEN wglDeleteContext(HGLRC hglrc);
BOOL APIENTRYGEN wglMakeCurrent(HDC hdc, HGLRC hglrc);
BOOL APIENTRYGEN wglShareLists(HGLRC hglrc1, HGLRC hglrc2);
BOOL APIENTRYGEN wglSwapLayerBuffers(HDC hdc, UINT planes);
HGLRC APIENTRYGEN wglCreateContextAttribsARB(HDC hdc, HGLRC shareContext, const GLint* attribList);
}

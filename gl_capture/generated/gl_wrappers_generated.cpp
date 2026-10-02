// GENERATED FILE - do not edit by hand. See codegen/generate.py
#include "gl_real_table.h"
#include "gl_ids.h"
#include "trace_writer.h"

extern TraceWriter g_trace;

extern "C" void APIENTRYGEN glEnable(GLenum cap) {
    auto call = g_trace.BeginCall(GLFuncId::glEnable);
    g_trace.WriteVal(call, cap);
    g_trace.EndCall(call);
    if (g_real.glEnable) g_real.glEnable(cap);
}

extern "C" void APIENTRYGEN glDisable(GLenum cap) {
    auto call = g_trace.BeginCall(GLFuncId::glDisable);
    g_trace.WriteVal(call, cap);
    g_trace.EndCall(call);
    if (g_real.glDisable) g_real.glDisable(cap);
}

extern "C" void APIENTRYGEN glClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    auto call = g_trace.BeginCall(GLFuncId::glClearColor);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, g);
    g_trace.WriteVal(call, b);
    g_trace.WriteVal(call, a);
    g_trace.EndCall(call);
    if (g_real.glClearColor) g_real.glClearColor(r, g, b, a);
}

extern "C" void APIENTRYGEN glClearDepth(GLdouble d) {
    auto call = g_trace.BeginCall(GLFuncId::glClearDepth);
    g_trace.WriteVal(call, d);
    g_trace.EndCall(call);
    if (g_real.glClearDepth) g_real.glClearDepth(d);
}

extern "C" void APIENTRYGEN glClear(GLbitfield mask) {
    auto call = g_trace.BeginCall(GLFuncId::glClear);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glClear) g_real.glClear(mask);
}

extern "C" void APIENTRYGEN glBlendFunc(GLenum sfactor, GLenum dfactor) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendFunc);
    g_trace.WriteVal(call, sfactor);
    g_trace.WriteVal(call, dfactor);
    g_trace.EndCall(call);
    if (g_real.glBlendFunc) g_real.glBlendFunc(sfactor, dfactor);
}

extern "C" void APIENTRYGEN glDepthFunc(GLenum func) {
    auto call = g_trace.BeginCall(GLFuncId::glDepthFunc);
    g_trace.WriteVal(call, func);
    g_trace.EndCall(call);
    if (g_real.glDepthFunc) g_real.glDepthFunc(func);
}

extern "C" void APIENTRYGEN glDepthMask(GLboolean flag) {
    auto call = g_trace.BeginCall(GLFuncId::glDepthMask);
    g_trace.WriteVal(call, flag);
    g_trace.EndCall(call);
    if (g_real.glDepthMask) g_real.glDepthMask(flag);
}

extern "C" void APIENTRYGEN glCullFace(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glCullFace);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glCullFace) g_real.glCullFace(mode);
}

extern "C" void APIENTRYGEN glFrontFace(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glFrontFace);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glFrontFace) g_real.glFrontFace(mode);
}

extern "C" void APIENTRYGEN glPolygonMode(GLenum face, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glPolygonMode);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glPolygonMode) g_real.glPolygonMode(face, mode);
}

extern "C" void APIENTRYGEN glLineWidth(GLfloat width) {
    auto call = g_trace.BeginCall(GLFuncId::glLineWidth);
    g_trace.WriteVal(call, width);
    g_trace.EndCall(call);
    if (g_real.glLineWidth) g_real.glLineWidth(width);
}

extern "C" void APIENTRYGEN glPointSize(GLfloat size) {
    auto call = g_trace.BeginCall(GLFuncId::glPointSize);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glPointSize) g_real.glPointSize(size);
}

extern "C" void APIENTRYGEN glViewport(GLint x, GLint y, GLsizei w, GLsizei h) {
    auto call = g_trace.BeginCall(GLFuncId::glViewport);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, w);
    g_trace.WriteVal(call, h);
    g_trace.EndCall(call);
    if (g_real.glViewport) g_real.glViewport(x, y, w, h);
}

extern "C" void APIENTRYGEN glScissor(GLint x, GLint y, GLsizei w, GLsizei h) {
    auto call = g_trace.BeginCall(GLFuncId::glScissor);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, w);
    g_trace.WriteVal(call, h);
    g_trace.EndCall(call);
    if (g_real.glScissor) g_real.glScissor(x, y, w, h);
}

extern "C" void APIENTRYGEN glMatrixMode(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glMatrixMode);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glMatrixMode) g_real.glMatrixMode(mode);
}

extern "C" void APIENTRYGEN glLoadIdentity(void) {
    auto call = g_trace.BeginCall(GLFuncId::glLoadIdentity);
    g_trace.EndCall(call);
    if (g_real.glLoadIdentity) g_real.glLoadIdentity();
}

extern "C" void APIENTRYGEN glPushMatrix(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPushMatrix);
    g_trace.EndCall(call);
    if (g_real.glPushMatrix) g_real.glPushMatrix();
}

extern "C" void APIENTRYGEN glPopMatrix(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPopMatrix);
    g_trace.EndCall(call);
    if (g_real.glPopMatrix) g_real.glPopMatrix();
}

extern "C" void APIENTRYGEN glTranslatef(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glTranslatef);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glTranslatef) g_real.glTranslatef(x, y, z);
}

extern "C" void APIENTRYGEN glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glRotatef);
    g_trace.WriteVal(call, angle);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRotatef) g_real.glRotatef(angle, x, y, z);
}

extern "C" void APIENTRYGEN glScalef(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glScalef);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glScalef) g_real.glScalef(x, y, z);
}

extern "C" void APIENTRYGEN glOrtho(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) {
    auto call = g_trace.BeginCall(GLFuncId::glOrtho);
    g_trace.WriteVal(call, l);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, b);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, f);
    g_trace.EndCall(call);
    if (g_real.glOrtho) g_real.glOrtho(l, r, b, t, n, f);
}

extern "C" void APIENTRYGEN glFrustum(GLdouble l, GLdouble r, GLdouble b, GLdouble t, GLdouble n, GLdouble f) {
    auto call = g_trace.BeginCall(GLFuncId::glFrustum);
    g_trace.WriteVal(call, l);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, b);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, f);
    g_trace.EndCall(call);
    if (g_real.glFrustum) g_real.glFrustum(l, r, b, t, n, f);
}

extern "C" void APIENTRYGEN glBegin(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glBegin);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glBegin) g_real.glBegin(mode);
}

extern "C" void APIENTRYGEN glEnd(void) {
    auto call = g_trace.BeginCall(GLFuncId::glEnd);
    g_trace.EndCall(call);
    if (g_real.glEnd) g_real.glEnd();
}

extern "C" void APIENTRYGEN glVertex2f(GLfloat x, GLfloat y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertex2f) g_real.glVertex2f(x, y);
}

extern "C" void APIENTRYGEN glVertex3f(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertex3f) g_real.glVertex3f(x, y, z);
}

extern "C" void APIENTRYGEN glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertex4f) g_real.glVertex4f(x, y, z, w);
}

extern "C" void APIENTRYGEN glColor3f(GLfloat r, GLfloat g, GLfloat b) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3f);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, g);
    g_trace.WriteVal(call, b);
    g_trace.EndCall(call);
    if (g_real.glColor3f) g_real.glColor3f(r, g, b);
}

extern "C" void APIENTRYGEN glColor4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4f);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, g);
    g_trace.WriteVal(call, b);
    g_trace.WriteVal(call, a);
    g_trace.EndCall(call);
    if (g_real.glColor4f) g_real.glColor4f(r, g, b, a);
}

extern "C" void APIENTRYGEN glNormal3f(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glNormal3f) g_real.glNormal3f(x, y, z);
}

extern "C" void APIENTRYGEN glTexCoord2f(GLfloat s, GLfloat t) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2f);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2f) g_real.glTexCoord2f(s, t);
}

extern "C" void APIENTRYGEN glEnableClientState(GLenum cap) {
    auto call = g_trace.BeginCall(GLFuncId::glEnableClientState);
    g_trace.WriteVal(call, cap);
    g_trace.EndCall(call);
    if (g_real.glEnableClientState) g_real.glEnableClientState(cap);
}

extern "C" void APIENTRYGEN glDisableClientState(GLenum cap) {
    auto call = g_trace.BeginCall(GLFuncId::glDisableClientState);
    g_trace.WriteVal(call, cap);
    g_trace.EndCall(call);
    if (g_real.glDisableClientState) g_real.glDisableClientState(cap);
}

extern "C" void APIENTRYGEN glBindVertexArray(GLuint array) {
    auto call = g_trace.BeginCall(GLFuncId::glBindVertexArray);
    g_trace.WriteVal(call, array);
    g_trace.EndCall(call);
    if (g_real.glBindVertexArray) g_real.glBindVertexArray(array);
}

extern "C" void APIENTRYGEN glEnableVertexAttribArray(GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glEnableVertexAttribArray);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glEnableVertexAttribArray) g_real.glEnableVertexAttribArray(index);
}

extern "C" void APIENTRYGEN glDisableVertexAttribArray(GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glDisableVertexAttribArray);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glDisableVertexAttribArray) g_real.glDisableVertexAttribArray(index);
}

extern "C" void APIENTRYGEN glBindTexture(GLenum target, GLuint texture) {
    auto call = g_trace.BeginCall(GLFuncId::glBindTexture);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, texture);
    g_trace.EndCall(call);
    if (g_real.glBindTexture) g_real.glBindTexture(target, texture);
}

extern "C" void APIENTRYGEN glActiveTexture(GLenum texture) {
    auto call = g_trace.BeginCall(GLFuncId::glActiveTexture);
    g_trace.WriteVal(call, texture);
    g_trace.EndCall(call);
    if (g_real.glActiveTexture) g_real.glActiveTexture(texture);
}

extern "C" void APIENTRYGEN glTexParameteri(GLenum target, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexParameteri);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexParameteri) g_real.glTexParameteri(target, pname, param);
}

extern "C" void APIENTRYGEN glTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexParameterf);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexParameterf) g_real.glTexParameterf(target, pname, param);
}

extern "C" void APIENTRYGEN glPixelStorei(GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelStorei);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPixelStorei) g_real.glPixelStorei(pname, param);
}

extern "C" void APIENTRYGEN glGenerateMipmap(GLenum target) {
    auto call = g_trace.BeginCall(GLFuncId::glGenerateMipmap);
    g_trace.WriteVal(call, target);
    g_trace.EndCall(call);
    if (g_real.glGenerateMipmap) g_real.glGenerateMipmap(target);
}

extern "C" GLuint APIENTRYGEN glCreateShader(GLenum type) {
    auto call = g_trace.BeginCall(GLFuncId::glCreateShader);
    g_trace.WriteVal(call, type);
    GLuint result = g_real.glCreateShader ? g_real.glCreateShader(type) : GLuint{};
    g_trace.WriteVal(call, result);
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glDeleteShader(GLuint shader) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteShader);
    g_trace.WriteVal(call, shader);
    g_trace.EndCall(call);
    if (g_real.glDeleteShader) g_real.glDeleteShader(shader);
}

extern "C" void APIENTRYGEN glCompileShader(GLuint shader) {
    auto call = g_trace.BeginCall(GLFuncId::glCompileShader);
    g_trace.WriteVal(call, shader);
    g_trace.EndCall(call);
    if (g_real.glCompileShader) g_real.glCompileShader(shader);
}

extern "C" GLuint APIENTRYGEN glCreateProgram(void) {
    auto call = g_trace.BeginCall(GLFuncId::glCreateProgram);
    GLuint result = g_real.glCreateProgram ? g_real.glCreateProgram() : GLuint{};
    g_trace.WriteVal(call, result);
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glDeleteProgram(GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteProgram);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glDeleteProgram) g_real.glDeleteProgram(program);
}

extern "C" void APIENTRYGEN glAttachShader(GLuint program, GLuint shader) {
    auto call = g_trace.BeginCall(GLFuncId::glAttachShader);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, shader);
    g_trace.EndCall(call);
    if (g_real.glAttachShader) g_real.glAttachShader(program, shader);
}

extern "C" void APIENTRYGEN glDetachShader(GLuint program, GLuint shader) {
    auto call = g_trace.BeginCall(GLFuncId::glDetachShader);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, shader);
    g_trace.EndCall(call);
    if (g_real.glDetachShader) g_real.glDetachShader(program, shader);
}

extern "C" void APIENTRYGEN glLinkProgram(GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glLinkProgram);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glLinkProgram) g_real.glLinkProgram(program);
}

extern "C" void APIENTRYGEN glUseProgram(GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glUseProgram);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glUseProgram) g_real.glUseProgram(program);
}

extern "C" void APIENTRYGEN glUniform1i(GLint loc, GLint v0) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform1i);
    g_trace.WriteVal(call, loc);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glUniform1i) g_real.glUniform1i(loc, v0);
}

extern "C" void APIENTRYGEN glUniform1f(GLint loc, GLfloat v0) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform1f);
    g_trace.WriteVal(call, loc);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glUniform1f) g_real.glUniform1f(loc, v0);
}

extern "C" void APIENTRYGEN glUniform2f(GLint loc, GLfloat v0, GLfloat v1) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform2f);
    g_trace.WriteVal(call, loc);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glUniform2f) g_real.glUniform2f(loc, v0, v1);
}

extern "C" void APIENTRYGEN glUniform3f(GLint loc, GLfloat v0, GLfloat v1, GLfloat v2) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform3f);
    g_trace.WriteVal(call, loc);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glUniform3f) g_real.glUniform3f(loc, v0, v1, v2);
}

extern "C" void APIENTRYGEN glUniform4f(GLint loc, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform4f);
    g_trace.WriteVal(call, loc);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glUniform4f) g_real.glUniform4f(loc, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glBindFramebuffer(GLenum target, GLuint fb) {
    auto call = g_trace.BeginCall(GLFuncId::glBindFramebuffer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, fb);
    g_trace.EndCall(call);
    if (g_real.glBindFramebuffer) g_real.glBindFramebuffer(target, fb);
}

extern "C" void APIENTRYGEN glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferTexture2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, textarget);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.EndCall(call);
    if (g_real.glFramebufferTexture2D) g_real.glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

extern "C" void APIENTRYGEN glBindRenderbuffer(GLenum target, GLuint rb) {
    auto call = g_trace.BeginCall(GLFuncId::glBindRenderbuffer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, rb);
    g_trace.EndCall(call);
    if (g_real.glBindRenderbuffer) g_real.glBindRenderbuffer(target, rb);
}

extern "C" void APIENTRYGEN glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei w, GLsizei h) {
    auto call = g_trace.BeginCall(GLFuncId::glRenderbufferStorage);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, w);
    g_trace.WriteVal(call, h);
    g_trace.EndCall(call);
    if (g_real.glRenderbufferStorage) g_real.glRenderbufferStorage(target, internalformat, w, h);
}

extern "C" void APIENTRYGEN glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum rbtarget, GLuint rb) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferRenderbuffer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, rbtarget);
    g_trace.WriteVal(call, rb);
    g_trace.EndCall(call);
    if (g_real.glFramebufferRenderbuffer) g_real.glFramebufferRenderbuffer(target, attachment, rbtarget, rb);
}

extern "C" GLenum APIENTRYGEN glCheckFramebufferStatus(GLenum target) {
    auto call = g_trace.BeginCall(GLFuncId::glCheckFramebufferStatus);
    g_trace.WriteVal(call, target);
    GLenum result = g_real.glCheckFramebufferStatus ? g_real.glCheckFramebufferStatus(target) : GLenum{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glAccum(GLenum op, GLfloat value) {
    auto call = g_trace.BeginCall(GLFuncId::glAccum);
    g_trace.WriteVal(call, op);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glAccum) g_real.glAccum(op, value);
}

extern "C" void APIENTRYGEN glAlphaFunc(GLenum func, GLfloat ref) {
    auto call = g_trace.BeginCall(GLFuncId::glAlphaFunc);
    g_trace.WriteVal(call, func);
    g_trace.WriteVal(call, ref);
    g_trace.EndCall(call);
    if (g_real.glAlphaFunc) g_real.glAlphaFunc(func, ref);
}

extern "C" GLboolean APIENTRYGEN glAreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences) {
    auto call = g_trace.BeginCall(GLFuncId::glAreTexturesResident);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, static_cast<uint8_t>(textures != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(residences != nullptr));
    GLboolean result = g_real.glAreTexturesResident ? g_real.glAreTexturesResident(n, textures, residences) : GLboolean{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glArrayElement(GLint i) {
    auto call = g_trace.BeginCall(GLFuncId::glArrayElement);
    g_trace.WriteVal(call, i);
    g_trace.EndCall(call);
    if (g_real.glArrayElement) g_real.glArrayElement(i);
}

extern "C" void APIENTRYGEN glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap) {
    auto call = g_trace.BeginCall(GLFuncId::glBitmap);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, xorig);
    g_trace.WriteVal(call, yorig);
    g_trace.WriteVal(call, xmove);
    g_trace.WriteVal(call, ymove);
    g_trace.WriteVal(call, static_cast<uint8_t>(bitmap != nullptr));
    g_trace.EndCall(call);
    if (g_real.glBitmap) g_real.glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
}

extern "C" void APIENTRYGEN glCallList(GLuint list) {
    auto call = g_trace.BeginCall(GLFuncId::glCallList);
    g_trace.WriteVal(call, list);
    g_trace.EndCall(call);
    if (g_real.glCallList) g_real.glCallList(list);
}

extern "C" void APIENTRYGEN glCallLists(GLsizei n, GLenum type, const void * lists) {
    auto call = g_trace.BeginCall(GLFuncId::glCallLists);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(lists != nullptr));
    g_trace.EndCall(call);
    if (g_real.glCallLists) g_real.glCallLists(n, type, lists);
}

extern "C" void APIENTRYGEN glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glClearAccum);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glClearAccum) g_real.glClearAccum(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glClearIndex(GLfloat c) {
    auto call = g_trace.BeginCall(GLFuncId::glClearIndex);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glClearIndex) g_real.glClearIndex(c);
}

extern "C" void APIENTRYGEN glClearStencil(GLint s) {
    auto call = g_trace.BeginCall(GLFuncId::glClearStencil);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glClearStencil) g_real.glClearStencil(s);
}

extern "C" void APIENTRYGEN glClipPlane(GLenum plane, const GLdouble * equation) {
    auto call = g_trace.BeginCall(GLFuncId::glClipPlane);
    g_trace.WriteVal(call, plane);
    g_trace.WriteVal(call, static_cast<uint8_t>(equation != nullptr));
    g_trace.EndCall(call);
    if (g_real.glClipPlane) g_real.glClipPlane(plane, equation);
}

extern "C" void APIENTRYGEN glColor3b(GLbyte red, GLbyte green, GLbyte blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3b);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3b) g_real.glColor3b(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3bv(const GLbyte * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3bv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3bv) g_real.glColor3bv(v);
}

extern "C" void APIENTRYGEN glColor3d(GLdouble red, GLdouble green, GLdouble blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3d);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3d) g_real.glColor3d(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3dv) g_real.glColor3dv(v);
}

extern "C" void APIENTRYGEN glColor3fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3fv) g_real.glColor3fv(v);
}

extern "C" void APIENTRYGEN glColor3i(GLint red, GLint green, GLint blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3i);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3i) g_real.glColor3i(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3iv) g_real.glColor3iv(v);
}

extern "C" void APIENTRYGEN glColor3s(GLshort red, GLshort green, GLshort blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3s);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3s) g_real.glColor3s(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3sv) g_real.glColor3sv(v);
}

extern "C" void APIENTRYGEN glColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3ub);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3ub) g_real.glColor3ub(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3ui(GLuint red, GLuint green, GLuint blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3ui);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3ui) g_real.glColor3ui(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3uiv(const GLuint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3uiv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3uiv) g_real.glColor3uiv(v);
}

extern "C" void APIENTRYGEN glColor3us(GLushort red, GLushort green, GLushort blue) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3us);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glColor3us) g_real.glColor3us(red, green, blue);
}

extern "C" void APIENTRYGEN glColor3usv(const GLushort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3usv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor3usv) g_real.glColor3usv(v);
}

extern "C" void APIENTRYGEN glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4b);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4b) g_real.glColor4b(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4bv(const GLbyte * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4bv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor4bv) g_real.glColor4bv(v);
}

extern "C" void APIENTRYGEN glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4d);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4d) g_real.glColor4d(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4i(GLint red, GLint green, GLint blue, GLint alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4i);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4i) g_real.glColor4i(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor4iv) g_real.glColor4iv(v);
}

extern "C" void APIENTRYGEN glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4s);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4s) g_real.glColor4s(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor4sv) g_real.glColor4sv(v);
}

extern "C" void APIENTRYGEN glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4ub);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4ub) g_real.glColor4ub(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4ubv(const GLubyte * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4ubv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor4ubv) g_real.glColor4ubv(v);
}

extern "C" void APIENTRYGEN glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4ui);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4ui) g_real.glColor4ui(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColor4uiv(const GLuint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4uiv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glColor4uiv) g_real.glColor4uiv(v);
}

extern "C" void APIENTRYGEN glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4us);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColor4us) g_real.glColor4us(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glColorMask);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glColorMask) g_real.glColorMask(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glColorMaterial(GLenum face, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glColorMaterial);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glColorMaterial) g_real.glColorMaterial(face, mode);
}

extern "C" void APIENTRYGEN glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyPixels);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, type);
    g_trace.EndCall(call);
    if (g_real.glCopyPixels) g_real.glCopyPixels(x, y, width, height, type);
}

extern "C" void APIENTRYGEN glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTexImage1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, border);
    g_trace.EndCall(call);
    if (g_real.glCopyTexImage1D) g_real.glCopyTexImage1D(target, level, internalformat, x, y, width, border);
}

extern "C" void APIENTRYGEN glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTexImage2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, border);
    g_trace.EndCall(call);
    if (g_real.glCopyTexImage2D) g_real.glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

extern "C" void APIENTRYGEN glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTexSubImage1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.EndCall(call);
    if (g_real.glCopyTexSubImage1D) g_real.glCopyTexSubImage1D(target, level, xoffset, x, y, width);
}

extern "C" void APIENTRYGEN glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTexSubImage2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glCopyTexSubImage2D) g_real.glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

extern "C" void APIENTRYGEN glDeleteLists(GLuint list, GLsizei range) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteLists);
    g_trace.WriteVal(call, list);
    g_trace.WriteVal(call, range);
    g_trace.EndCall(call);
    if (g_real.glDeleteLists) g_real.glDeleteLists(list, range);
}

extern "C" void APIENTRYGEN glDepthRange(GLdouble n, GLdouble f) {
    auto call = g_trace.BeginCall(GLFuncId::glDepthRange);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, f);
    g_trace.EndCall(call);
    if (g_real.glDepthRange) g_real.glDepthRange(n, f);
}

extern "C" void APIENTRYGEN glDrawBuffer(GLenum buf) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawBuffer);
    g_trace.WriteVal(call, buf);
    g_trace.EndCall(call);
    if (g_real.glDrawBuffer) g_real.glDrawBuffer(buf);
}

extern "C" void APIENTRYGEN glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawPixels);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(pixels != nullptr));
    g_trace.EndCall(call);
    if (g_real.glDrawPixels) g_real.glDrawPixels(width, height, format, type, pixels);
}

extern "C" void APIENTRYGEN glEdgeFlag(GLboolean flag) {
    auto call = g_trace.BeginCall(GLFuncId::glEdgeFlag);
    g_trace.WriteVal(call, flag);
    g_trace.EndCall(call);
    if (g_real.glEdgeFlag) g_real.glEdgeFlag(flag);
}

extern "C" void APIENTRYGEN glEdgeFlagPointer(GLsizei stride, const void * pointer) {
    auto call = g_trace.BeginCall(GLFuncId::glEdgeFlagPointer);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, static_cast<uint8_t>(pointer != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEdgeFlagPointer) g_real.glEdgeFlagPointer(stride, pointer);
}

extern "C" void APIENTRYGEN glEdgeFlagv(const GLboolean * flag) {
    auto call = g_trace.BeginCall(GLFuncId::glEdgeFlagv);
    g_trace.WriteVal(call, static_cast<uint8_t>(flag != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEdgeFlagv) g_real.glEdgeFlagv(flag);
}

extern "C" void APIENTRYGEN glEndList(void) {
    auto call = g_trace.BeginCall(GLFuncId::glEndList);
    g_trace.EndCall(call);
    if (g_real.glEndList) g_real.glEndList();
}

extern "C" void APIENTRYGEN glEvalCoord1d(GLdouble u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord1d);
    g_trace.WriteVal(call, u);
    g_trace.EndCall(call);
    if (g_real.glEvalCoord1d) g_real.glEvalCoord1d(u);
}

extern "C" void APIENTRYGEN glEvalCoord1dv(const GLdouble * u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord1dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(u != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEvalCoord1dv) g_real.glEvalCoord1dv(u);
}

extern "C" void APIENTRYGEN glEvalCoord1f(GLfloat u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord1f);
    g_trace.WriteVal(call, u);
    g_trace.EndCall(call);
    if (g_real.glEvalCoord1f) g_real.glEvalCoord1f(u);
}

extern "C" void APIENTRYGEN glEvalCoord1fv(const GLfloat * u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord1fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(u != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEvalCoord1fv) g_real.glEvalCoord1fv(u);
}

extern "C" void APIENTRYGEN glEvalCoord2d(GLdouble u, GLdouble v) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord2d);
    g_trace.WriteVal(call, u);
    g_trace.WriteVal(call, v);
    g_trace.EndCall(call);
    if (g_real.glEvalCoord2d) g_real.glEvalCoord2d(u, v);
}

extern "C" void APIENTRYGEN glEvalCoord2dv(const GLdouble * u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord2dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(u != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEvalCoord2dv) g_real.glEvalCoord2dv(u);
}

extern "C" void APIENTRYGEN glEvalCoord2f(GLfloat u, GLfloat v) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord2f);
    g_trace.WriteVal(call, u);
    g_trace.WriteVal(call, v);
    g_trace.EndCall(call);
    if (g_real.glEvalCoord2f) g_real.glEvalCoord2f(u, v);
}

extern "C" void APIENTRYGEN glEvalCoord2fv(const GLfloat * u) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalCoord2fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(u != nullptr));
    g_trace.EndCall(call);
    if (g_real.glEvalCoord2fv) g_real.glEvalCoord2fv(u);
}

extern "C" void APIENTRYGEN glEvalMesh1(GLenum mode, GLint i1, GLint i2) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalMesh1);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, i1);
    g_trace.WriteVal(call, i2);
    g_trace.EndCall(call);
    if (g_real.glEvalMesh1) g_real.glEvalMesh1(mode, i1, i2);
}

extern "C" void APIENTRYGEN glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalMesh2);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, i1);
    g_trace.WriteVal(call, i2);
    g_trace.WriteVal(call, j1);
    g_trace.WriteVal(call, j2);
    g_trace.EndCall(call);
    if (g_real.glEvalMesh2) g_real.glEvalMesh2(mode, i1, i2, j1, j2);
}

extern "C" void APIENTRYGEN glEvalPoint1(GLint i) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalPoint1);
    g_trace.WriteVal(call, i);
    g_trace.EndCall(call);
    if (g_real.glEvalPoint1) g_real.glEvalPoint1(i);
}

extern "C" void APIENTRYGEN glEvalPoint2(GLint i, GLint j) {
    auto call = g_trace.BeginCall(GLFuncId::glEvalPoint2);
    g_trace.WriteVal(call, i);
    g_trace.WriteVal(call, j);
    g_trace.EndCall(call);
    if (g_real.glEvalPoint2) g_real.glEvalPoint2(i, j);
}

extern "C" void APIENTRYGEN glFeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glFeedbackBuffer);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(buffer != nullptr));
    g_trace.EndCall(call);
    if (g_real.glFeedbackBuffer) g_real.glFeedbackBuffer(size, type, buffer);
}

extern "C" void APIENTRYGEN glFinish(void) {
    auto call = g_trace.BeginCall(GLFuncId::glFinish);
    g_trace.EndCall(call);
    if (g_real.glFinish) g_real.glFinish();
}

extern "C" void APIENTRYGEN glFlush(void) {
    auto call = g_trace.BeginCall(GLFuncId::glFlush);
    g_trace.EndCall(call);
    if (g_real.glFlush) g_real.glFlush();
}

extern "C" void APIENTRYGEN glFogf(GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glFogf);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glFogf) g_real.glFogf(pname, param);
}

extern "C" void APIENTRYGEN glFogfv(GLenum pname, const GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glFogfv);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glFogfv) g_real.glFogfv(pname, params);
}

extern "C" void APIENTRYGEN glFogi(GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glFogi);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glFogi) g_real.glFogi(pname, param);
}

extern "C" void APIENTRYGEN glFogiv(GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glFogiv);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glFogiv) g_real.glFogiv(pname, params);
}

extern "C" GLuint APIENTRYGEN glGenLists(GLsizei range) {
    auto call = g_trace.BeginCall(GLFuncId::glGenLists);
    g_trace.WriteVal(call, range);
    GLuint result = g_real.glGenLists ? g_real.glGenLists(range) : GLuint{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glGetClipPlane(GLenum plane, GLdouble * equation) {
    auto call = g_trace.BeginCall(GLFuncId::glGetClipPlane);
    g_trace.WriteVal(call, plane);
    g_trace.WriteVal(call, static_cast<uint8_t>(equation != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetClipPlane) g_real.glGetClipPlane(plane, equation);
}

extern "C" void APIENTRYGEN glGetDoublev(GLenum pname, GLdouble * data) {
    auto call = g_trace.BeginCall(GLFuncId::glGetDoublev);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(data != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetDoublev) g_real.glGetDoublev(pname, data);
}

extern "C" GLenum APIENTRYGEN glGetError(void) {
    auto call = g_trace.BeginCall(GLFuncId::glGetError);
    GLenum result = g_real.glGetError ? g_real.glGetError() : GLenum{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glGetLightfv(GLenum light, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetLightfv);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetLightfv) g_real.glGetLightfv(light, pname, params);
}

extern "C" void APIENTRYGEN glGetLightiv(GLenum light, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetLightiv);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetLightiv) g_real.glGetLightiv(light, pname, params);
}

extern "C" void APIENTRYGEN glGetMapdv(GLenum target, GLenum query, GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glGetMapdv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, query);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetMapdv) g_real.glGetMapdv(target, query, v);
}

extern "C" void APIENTRYGEN glGetMapfv(GLenum target, GLenum query, GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glGetMapfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, query);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetMapfv) g_real.glGetMapfv(target, query, v);
}

extern "C" void APIENTRYGEN glGetMapiv(GLenum target, GLenum query, GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glGetMapiv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, query);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetMapiv) g_real.glGetMapiv(target, query, v);
}

extern "C" void APIENTRYGEN glGetMaterialfv(GLenum face, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetMaterialfv);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetMaterialfv) g_real.glGetMaterialfv(face, pname, params);
}

extern "C" void APIENTRYGEN glGetMaterialiv(GLenum face, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetMaterialiv);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetMaterialiv) g_real.glGetMaterialiv(face, pname, params);
}

extern "C" void APIENTRYGEN glGetPixelMapfv(GLenum map, GLfloat * values) {
    auto call = g_trace.BeginCall(GLFuncId::glGetPixelMapfv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetPixelMapfv) g_real.glGetPixelMapfv(map, values);
}

extern "C" void APIENTRYGEN glGetPixelMapuiv(GLenum map, GLuint * values) {
    auto call = g_trace.BeginCall(GLFuncId::glGetPixelMapuiv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetPixelMapuiv) g_real.glGetPixelMapuiv(map, values);
}

extern "C" void APIENTRYGEN glGetPixelMapusv(GLenum map, GLushort * values) {
    auto call = g_trace.BeginCall(GLFuncId::glGetPixelMapusv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetPixelMapusv) g_real.glGetPixelMapusv(map, values);
}

extern "C" void APIENTRYGEN glGetPointerv(GLenum pname, void ** params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetPointerv);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetPointerv) g_real.glGetPointerv(pname, params);
}

extern "C" void APIENTRYGEN glGetPolygonStipple(GLubyte * mask) {
    auto call = g_trace.BeginCall(GLFuncId::glGetPolygonStipple);
    g_trace.WriteVal(call, static_cast<uint8_t>(mask != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetPolygonStipple) g_real.glGetPolygonStipple(mask);
}

extern "C" void APIENTRYGEN glGetTexEnvfv(GLenum target, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexEnvfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexEnvfv) g_real.glGetTexEnvfv(target, pname, params);
}

extern "C" void APIENTRYGEN glGetTexEnviv(GLenum target, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexEnviv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexEnviv) g_real.glGetTexEnviv(target, pname, params);
}

extern "C" void APIENTRYGEN glGetTexGendv(GLenum coord, GLenum pname, GLdouble * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexGendv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexGendv) g_real.glGetTexGendv(coord, pname, params);
}

extern "C" void APIENTRYGEN glGetTexGenfv(GLenum coord, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexGenfv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexGenfv) g_real.glGetTexGenfv(coord, pname, params);
}

extern "C" void APIENTRYGEN glGetTexGeniv(GLenum coord, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexGeniv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexGeniv) g_real.glGetTexGeniv(coord, pname, params);
}

extern "C" void APIENTRYGEN glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexImage);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(pixels != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexImage) g_real.glGetTexImage(target, level, format, type, pixels);
}

extern "C" void APIENTRYGEN glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexLevelParameterfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexLevelParameterfv) g_real.glGetTexLevelParameterfv(target, level, pname, params);
}

extern "C" void APIENTRYGEN glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexLevelParameteriv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexLevelParameteriv) g_real.glGetTexLevelParameteriv(target, level, pname, params);
}

extern "C" void APIENTRYGEN glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexParameterfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexParameterfv) g_real.glGetTexParameterfv(target, pname, params);
}

extern "C" void APIENTRYGEN glGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetTexParameteriv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetTexParameteriv) g_real.glGetTexParameteriv(target, pname, params);
}

extern "C" void APIENTRYGEN glHint(GLenum target, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glHint);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glHint) g_real.glHint(target, mode);
}

extern "C" void APIENTRYGEN glIndexMask(GLuint mask) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexMask);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glIndexMask) g_real.glIndexMask(mask);
}

extern "C" void APIENTRYGEN glIndexPointer(GLenum type, GLsizei stride, const void * pointer) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexPointer);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, static_cast<uint8_t>(pointer != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexPointer) g_real.glIndexPointer(type, stride, pointer);
}

extern "C" void APIENTRYGEN glIndexd(GLdouble c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexd);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glIndexd) g_real.glIndexd(c);
}

extern "C" void APIENTRYGEN glIndexdv(const GLdouble * c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexdv);
    g_trace.WriteVal(call, static_cast<uint8_t>(c != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexdv) g_real.glIndexdv(c);
}

extern "C" void APIENTRYGEN glIndexf(GLfloat c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexf);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glIndexf) g_real.glIndexf(c);
}

extern "C" void APIENTRYGEN glIndexfv(const GLfloat * c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexfv);
    g_trace.WriteVal(call, static_cast<uint8_t>(c != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexfv) g_real.glIndexfv(c);
}

extern "C" void APIENTRYGEN glIndexi(GLint c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexi);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glIndexi) g_real.glIndexi(c);
}

extern "C" void APIENTRYGEN glIndexiv(const GLint * c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexiv);
    g_trace.WriteVal(call, static_cast<uint8_t>(c != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexiv) g_real.glIndexiv(c);
}

extern "C" void APIENTRYGEN glIndexs(GLshort c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexs);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glIndexs) g_real.glIndexs(c);
}

extern "C" void APIENTRYGEN glIndexsv(const GLshort * c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexsv);
    g_trace.WriteVal(call, static_cast<uint8_t>(c != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexsv) g_real.glIndexsv(c);
}

extern "C" void APIENTRYGEN glIndexub(GLubyte c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexub);
    g_trace.WriteVal(call, c);
    g_trace.EndCall(call);
    if (g_real.glIndexub) g_real.glIndexub(c);
}

extern "C" void APIENTRYGEN glIndexubv(const GLubyte * c) {
    auto call = g_trace.BeginCall(GLFuncId::glIndexubv);
    g_trace.WriteVal(call, static_cast<uint8_t>(c != nullptr));
    g_trace.EndCall(call);
    if (g_real.glIndexubv) g_real.glIndexubv(c);
}

extern "C" void APIENTRYGEN glInitNames(void) {
    auto call = g_trace.BeginCall(GLFuncId::glInitNames);
    g_trace.EndCall(call);
    if (g_real.glInitNames) g_real.glInitNames();
}

extern "C" GLboolean APIENTRYGEN glIsEnabled(GLenum cap) {
    auto call = g_trace.BeginCall(GLFuncId::glIsEnabled);
    g_trace.WriteVal(call, cap);
    GLboolean result = g_real.glIsEnabled ? g_real.glIsEnabled(cap) : GLboolean{};
    g_trace.EndCall(call);
    return result;
}

extern "C" GLboolean APIENTRYGEN glIsList(GLuint list) {
    auto call = g_trace.BeginCall(GLFuncId::glIsList);
    g_trace.WriteVal(call, list);
    GLboolean result = g_real.glIsList ? g_real.glIsList(list) : GLboolean{};
    g_trace.EndCall(call);
    return result;
}

extern "C" GLboolean APIENTRYGEN glIsTexture(GLuint texture) {
    auto call = g_trace.BeginCall(GLFuncId::glIsTexture);
    g_trace.WriteVal(call, texture);
    GLboolean result = g_real.glIsTexture ? g_real.glIsTexture(texture) : GLboolean{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glLightModelf(GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glLightModelf);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glLightModelf) g_real.glLightModelf(pname, param);
}

extern "C" void APIENTRYGEN glLightModeli(GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glLightModeli);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glLightModeli) g_real.glLightModeli(pname, param);
}

extern "C" void APIENTRYGEN glLightModeliv(GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glLightModeliv);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glLightModeliv) g_real.glLightModeliv(pname, params);
}

extern "C" void APIENTRYGEN glLightf(GLenum light, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glLightf);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glLightf) g_real.glLightf(light, pname, param);
}

extern "C" void APIENTRYGEN glLighti(GLenum light, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glLighti);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glLighti) g_real.glLighti(light, pname, param);
}

extern "C" void APIENTRYGEN glLightiv(GLenum light, GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glLightiv);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glLightiv) g_real.glLightiv(light, pname, params);
}

extern "C" void APIENTRYGEN glLineStipple(GLint factor, GLushort pattern) {
    auto call = g_trace.BeginCall(GLFuncId::glLineStipple);
    g_trace.WriteVal(call, factor);
    g_trace.WriteVal(call, pattern);
    g_trace.EndCall(call);
    if (g_real.glLineStipple) g_real.glLineStipple(factor, pattern);
}

extern "C" void APIENTRYGEN glListBase(GLuint base) {
    auto call = g_trace.BeginCall(GLFuncId::glListBase);
    g_trace.WriteVal(call, base);
    g_trace.EndCall(call);
    if (g_real.glListBase) g_real.glListBase(base);
}

extern "C" void APIENTRYGEN glLoadName(GLuint name) {
    auto call = g_trace.BeginCall(GLFuncId::glLoadName);
    g_trace.WriteVal(call, name);
    g_trace.EndCall(call);
    if (g_real.glLoadName) g_real.glLoadName(name);
}

extern "C" void APIENTRYGEN glLogicOp(GLenum opcode) {
    auto call = g_trace.BeginCall(GLFuncId::glLogicOp);
    g_trace.WriteVal(call, opcode);
    g_trace.EndCall(call);
    if (g_real.glLogicOp) g_real.glLogicOp(opcode);
}

extern "C" void APIENTRYGEN glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points) {
    auto call = g_trace.BeginCall(GLFuncId::glMap1d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, order);
    g_trace.WriteVal(call, static_cast<uint8_t>(points != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMap1d) g_real.glMap1d(target, u1, u2, stride, order, points);
}

extern "C" void APIENTRYGEN glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points) {
    auto call = g_trace.BeginCall(GLFuncId::glMap1f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, order);
    g_trace.WriteVal(call, static_cast<uint8_t>(points != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMap1f) g_real.glMap1f(target, u1, u2, stride, order, points);
}

extern "C" void APIENTRYGEN glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points) {
    auto call = g_trace.BeginCall(GLFuncId::glMap2d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, ustride);
    g_trace.WriteVal(call, uorder);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, vstride);
    g_trace.WriteVal(call, vorder);
    g_trace.WriteVal(call, static_cast<uint8_t>(points != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMap2d) g_real.glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

extern "C" void APIENTRYGEN glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points) {
    auto call = g_trace.BeginCall(GLFuncId::glMap2f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, ustride);
    g_trace.WriteVal(call, uorder);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, vstride);
    g_trace.WriteVal(call, vorder);
    g_trace.WriteVal(call, static_cast<uint8_t>(points != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMap2f) g_real.glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
}

extern "C" void APIENTRYGEN glMapGrid1d(GLint un, GLdouble u1, GLdouble u2) {
    auto call = g_trace.BeginCall(GLFuncId::glMapGrid1d);
    g_trace.WriteVal(call, un);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.EndCall(call);
    if (g_real.glMapGrid1d) g_real.glMapGrid1d(un, u1, u2);
}

extern "C" void APIENTRYGEN glMapGrid1f(GLint un, GLfloat u1, GLfloat u2) {
    auto call = g_trace.BeginCall(GLFuncId::glMapGrid1f);
    g_trace.WriteVal(call, un);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.EndCall(call);
    if (g_real.glMapGrid1f) g_real.glMapGrid1f(un, u1, u2);
}

extern "C" void APIENTRYGEN glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2) {
    auto call = g_trace.BeginCall(GLFuncId::glMapGrid2d);
    g_trace.WriteVal(call, un);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, vn);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glMapGrid2d) g_real.glMapGrid2d(un, u1, u2, vn, v1, v2);
}

extern "C" void APIENTRYGEN glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2) {
    auto call = g_trace.BeginCall(GLFuncId::glMapGrid2f);
    g_trace.WriteVal(call, un);
    g_trace.WriteVal(call, u1);
    g_trace.WriteVal(call, u2);
    g_trace.WriteVal(call, vn);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glMapGrid2f) g_real.glMapGrid2f(un, u1, u2, vn, v1, v2);
}

extern "C" void APIENTRYGEN glMaterialf(GLenum face, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glMaterialf);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glMaterialf) g_real.glMaterialf(face, pname, param);
}

extern "C" void APIENTRYGEN glMaterialfv(GLenum face, GLenum pname, const GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glMaterialfv);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMaterialfv) g_real.glMaterialfv(face, pname, params);
}

extern "C" void APIENTRYGEN glMateriali(GLenum face, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glMateriali);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glMateriali) g_real.glMateriali(face, pname, param);
}

extern "C" void APIENTRYGEN glMaterialiv(GLenum face, GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glMaterialiv);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMaterialiv) g_real.glMaterialiv(face, pname, params);
}

extern "C" void APIENTRYGEN glMultMatrixd(const GLdouble * m) {
    auto call = g_trace.BeginCall(GLFuncId::glMultMatrixd);
    g_trace.WriteVal(call, static_cast<uint8_t>(m != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMultMatrixd) g_real.glMultMatrixd(m);
}

extern "C" void APIENTRYGEN glMultMatrixf(const GLfloat * m) {
    auto call = g_trace.BeginCall(GLFuncId::glMultMatrixf);
    g_trace.WriteVal(call, static_cast<uint8_t>(m != nullptr));
    g_trace.EndCall(call);
    if (g_real.glMultMatrixf) g_real.glMultMatrixf(m);
}

extern "C" void APIENTRYGEN glNewList(GLuint list, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glNewList);
    g_trace.WriteVal(call, list);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glNewList) g_real.glNewList(list, mode);
}

extern "C" void APIENTRYGEN glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3b);
    g_trace.WriteVal(call, nx);
    g_trace.WriteVal(call, ny);
    g_trace.WriteVal(call, nz);
    g_trace.EndCall(call);
    if (g_real.glNormal3b) g_real.glNormal3b(nx, ny, nz);
}

extern "C" void APIENTRYGEN glNormal3bv(const GLbyte * v) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3bv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glNormal3bv) g_real.glNormal3bv(v);
}

extern "C" void APIENTRYGEN glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3d);
    g_trace.WriteVal(call, nx);
    g_trace.WriteVal(call, ny);
    g_trace.WriteVal(call, nz);
    g_trace.EndCall(call);
    if (g_real.glNormal3d) g_real.glNormal3d(nx, ny, nz);
}

extern "C" void APIENTRYGEN glNormal3i(GLint nx, GLint ny, GLint nz) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3i);
    g_trace.WriteVal(call, nx);
    g_trace.WriteVal(call, ny);
    g_trace.WriteVal(call, nz);
    g_trace.EndCall(call);
    if (g_real.glNormal3i) g_real.glNormal3i(nx, ny, nz);
}

extern "C" void APIENTRYGEN glNormal3iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glNormal3iv) g_real.glNormal3iv(v);
}

extern "C" void APIENTRYGEN glNormal3s(GLshort nx, GLshort ny, GLshort nz) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3s);
    g_trace.WriteVal(call, nx);
    g_trace.WriteVal(call, ny);
    g_trace.WriteVal(call, nz);
    g_trace.EndCall(call);
    if (g_real.glNormal3s) g_real.glNormal3s(nx, ny, nz);
}

extern "C" void APIENTRYGEN glNormal3sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glNormal3sv) g_real.glNormal3sv(v);
}

extern "C" void APIENTRYGEN glPassThrough(GLfloat token) {
    auto call = g_trace.BeginCall(GLFuncId::glPassThrough);
    g_trace.WriteVal(call, token);
    g_trace.EndCall(call);
    if (g_real.glPassThrough) g_real.glPassThrough(token);
}

extern "C" void APIENTRYGEN glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelMapfv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, mapsize);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glPixelMapfv) g_real.glPixelMapfv(map, mapsize, values);
}

extern "C" void APIENTRYGEN glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelMapuiv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, mapsize);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glPixelMapuiv) g_real.glPixelMapuiv(map, mapsize, values);
}

extern "C" void APIENTRYGEN glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelMapusv);
    g_trace.WriteVal(call, map);
    g_trace.WriteVal(call, mapsize);
    g_trace.WriteVal(call, static_cast<uint8_t>(values != nullptr));
    g_trace.EndCall(call);
    if (g_real.glPixelMapusv) g_real.glPixelMapusv(map, mapsize, values);
}

extern "C" void APIENTRYGEN glPixelStoref(GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelStoref);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPixelStoref) g_real.glPixelStoref(pname, param);
}

extern "C" void APIENTRYGEN glPixelTransferf(GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelTransferf);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPixelTransferf) g_real.glPixelTransferf(pname, param);
}

extern "C" void APIENTRYGEN glPixelTransferi(GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelTransferi);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPixelTransferi) g_real.glPixelTransferi(pname, param);
}

extern "C" void APIENTRYGEN glPixelZoom(GLfloat xfactor, GLfloat yfactor) {
    auto call = g_trace.BeginCall(GLFuncId::glPixelZoom);
    g_trace.WriteVal(call, xfactor);
    g_trace.WriteVal(call, yfactor);
    g_trace.EndCall(call);
    if (g_real.glPixelZoom) g_real.glPixelZoom(xfactor, yfactor);
}

extern "C" void APIENTRYGEN glPolygonOffset(GLfloat factor, GLfloat units) {
    auto call = g_trace.BeginCall(GLFuncId::glPolygonOffset);
    g_trace.WriteVal(call, factor);
    g_trace.WriteVal(call, units);
    g_trace.EndCall(call);
    if (g_real.glPolygonOffset) g_real.glPolygonOffset(factor, units);
}

extern "C" void APIENTRYGEN glPolygonStipple(const GLubyte * mask) {
    auto call = g_trace.BeginCall(GLFuncId::glPolygonStipple);
    g_trace.WriteVal(call, static_cast<uint8_t>(mask != nullptr));
    g_trace.EndCall(call);
    if (g_real.glPolygonStipple) g_real.glPolygonStipple(mask);
}

extern "C" void APIENTRYGEN glPopAttrib(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPopAttrib);
    g_trace.EndCall(call);
    if (g_real.glPopAttrib) g_real.glPopAttrib();
}

extern "C" void APIENTRYGEN glPopClientAttrib(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPopClientAttrib);
    g_trace.EndCall(call);
    if (g_real.glPopClientAttrib) g_real.glPopClientAttrib();
}

extern "C" void APIENTRYGEN glPopName(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPopName);
    g_trace.EndCall(call);
    if (g_real.glPopName) g_real.glPopName();
}

extern "C" void APIENTRYGEN glPrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities) {
    auto call = g_trace.BeginCall(GLFuncId::glPrioritizeTextures);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, static_cast<uint8_t>(textures != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(priorities != nullptr));
    g_trace.EndCall(call);
    if (g_real.glPrioritizeTextures) g_real.glPrioritizeTextures(n, textures, priorities);
}

extern "C" void APIENTRYGEN glPushAttrib(GLbitfield mask) {
    auto call = g_trace.BeginCall(GLFuncId::glPushAttrib);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glPushAttrib) g_real.glPushAttrib(mask);
}

extern "C" void APIENTRYGEN glPushClientAttrib(GLbitfield mask) {
    auto call = g_trace.BeginCall(GLFuncId::glPushClientAttrib);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glPushClientAttrib) g_real.glPushClientAttrib(mask);
}

extern "C" void APIENTRYGEN glPushName(GLuint name) {
    auto call = g_trace.BeginCall(GLFuncId::glPushName);
    g_trace.WriteVal(call, name);
    g_trace.EndCall(call);
    if (g_real.glPushName) g_real.glPushName(name);
}

extern "C" void APIENTRYGEN glRasterPos2d(GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glRasterPos2d) g_real.glRasterPos2d(x, y);
}

extern "C" void APIENTRYGEN glRasterPos2dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos2dv) g_real.glRasterPos2dv(v);
}

extern "C" void APIENTRYGEN glRasterPos2f(GLfloat x, GLfloat y) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glRasterPos2f) g_real.glRasterPos2f(x, y);
}

extern "C" void APIENTRYGEN glRasterPos2fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos2fv) g_real.glRasterPos2fv(v);
}

extern "C" void APIENTRYGEN glRasterPos2i(GLint x, GLint y) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glRasterPos2i) g_real.glRasterPos2i(x, y);
}

extern "C" void APIENTRYGEN glRasterPos2iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos2iv) g_real.glRasterPos2iv(v);
}

extern "C" void APIENTRYGEN glRasterPos2s(GLshort x, GLshort y) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glRasterPos2s) g_real.glRasterPos2s(x, y);
}

extern "C" void APIENTRYGEN glRasterPos2sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos2sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos2sv) g_real.glRasterPos2sv(v);
}

extern "C" void APIENTRYGEN glRasterPos3d(GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRasterPos3d) g_real.glRasterPos3d(x, y, z);
}

extern "C" void APIENTRYGEN glRasterPos3dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos3dv) g_real.glRasterPos3dv(v);
}

extern "C" void APIENTRYGEN glRasterPos3f(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRasterPos3f) g_real.glRasterPos3f(x, y, z);
}

extern "C" void APIENTRYGEN glRasterPos3fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos3fv) g_real.glRasterPos3fv(v);
}

extern "C" void APIENTRYGEN glRasterPos3i(GLint x, GLint y, GLint z) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRasterPos3i) g_real.glRasterPos3i(x, y, z);
}

extern "C" void APIENTRYGEN glRasterPos3iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos3iv) g_real.glRasterPos3iv(v);
}

extern "C" void APIENTRYGEN glRasterPos3s(GLshort x, GLshort y, GLshort z) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRasterPos3s) g_real.glRasterPos3s(x, y, z);
}

extern "C" void APIENTRYGEN glRasterPos3sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos3sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos3sv) g_real.glRasterPos3sv(v);
}

extern "C" void APIENTRYGEN glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glRasterPos4d) g_real.glRasterPos4d(x, y, z, w);
}

extern "C" void APIENTRYGEN glRasterPos4dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos4dv) g_real.glRasterPos4dv(v);
}

extern "C" void APIENTRYGEN glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glRasterPos4f) g_real.glRasterPos4f(x, y, z, w);
}

extern "C" void APIENTRYGEN glRasterPos4fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos4fv) g_real.glRasterPos4fv(v);
}

extern "C" void APIENTRYGEN glRasterPos4i(GLint x, GLint y, GLint z, GLint w) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glRasterPos4i) g_real.glRasterPos4i(x, y, z, w);
}

extern "C" void APIENTRYGEN glRasterPos4iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos4iv) g_real.glRasterPos4iv(v);
}

extern "C" void APIENTRYGEN glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glRasterPos4s) g_real.glRasterPos4s(x, y, z, w);
}

extern "C" void APIENTRYGEN glRasterPos4sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glRasterPos4sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRasterPos4sv) g_real.glRasterPos4sv(v);
}

extern "C" void APIENTRYGEN glReadBuffer(GLenum src) {
    auto call = g_trace.BeginCall(GLFuncId::glReadBuffer);
    g_trace.WriteVal(call, src);
    g_trace.EndCall(call);
    if (g_real.glReadBuffer) g_real.glReadBuffer(src);
}

extern "C" void APIENTRYGEN glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glReadPixels);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(pixels != nullptr));
    g_trace.EndCall(call);
    if (g_real.glReadPixels) g_real.glReadPixels(x, y, width, height, format, type, pixels);
}

extern "C" void APIENTRYGEN glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectd);
    g_trace.WriteVal(call, x1);
    g_trace.WriteVal(call, y1);
    g_trace.WriteVal(call, x2);
    g_trace.WriteVal(call, y2);
    g_trace.EndCall(call);
    if (g_real.glRectd) g_real.glRectd(x1, y1, x2, y2);
}

extern "C" void APIENTRYGEN glRectdv(const GLdouble * v1, const GLdouble * v2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectdv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v1 != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(v2 != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRectdv) g_real.glRectdv(v1, v2);
}

extern "C" void APIENTRYGEN glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectf);
    g_trace.WriteVal(call, x1);
    g_trace.WriteVal(call, y1);
    g_trace.WriteVal(call, x2);
    g_trace.WriteVal(call, y2);
    g_trace.EndCall(call);
    if (g_real.glRectf) g_real.glRectf(x1, y1, x2, y2);
}

extern "C" void APIENTRYGEN glRectfv(const GLfloat * v1, const GLfloat * v2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectfv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v1 != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(v2 != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRectfv) g_real.glRectfv(v1, v2);
}

extern "C" void APIENTRYGEN glRecti(GLint x1, GLint y1, GLint x2, GLint y2) {
    auto call = g_trace.BeginCall(GLFuncId::glRecti);
    g_trace.WriteVal(call, x1);
    g_trace.WriteVal(call, y1);
    g_trace.WriteVal(call, x2);
    g_trace.WriteVal(call, y2);
    g_trace.EndCall(call);
    if (g_real.glRecti) g_real.glRecti(x1, y1, x2, y2);
}

extern "C" void APIENTRYGEN glRectiv(const GLint * v1, const GLint * v2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectiv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v1 != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(v2 != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRectiv) g_real.glRectiv(v1, v2);
}

extern "C" void APIENTRYGEN glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2) {
    auto call = g_trace.BeginCall(GLFuncId::glRects);
    g_trace.WriteVal(call, x1);
    g_trace.WriteVal(call, y1);
    g_trace.WriteVal(call, x2);
    g_trace.WriteVal(call, y2);
    g_trace.EndCall(call);
    if (g_real.glRects) g_real.glRects(x1, y1, x2, y2);
}

extern "C" void APIENTRYGEN glRectsv(const GLshort * v1, const GLshort * v2) {
    auto call = g_trace.BeginCall(GLFuncId::glRectsv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v1 != nullptr));
    g_trace.WriteVal(call, static_cast<uint8_t>(v2 != nullptr));
    g_trace.EndCall(call);
    if (g_real.glRectsv) g_real.glRectsv(v1, v2);
}

extern "C" GLint APIENTRYGEN glRenderMode(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glRenderMode);
    g_trace.WriteVal(call, mode);
    GLint result = g_real.glRenderMode ? g_real.glRenderMode(mode) : GLint{};
    g_trace.EndCall(call);
    return result;
}

extern "C" void APIENTRYGEN glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glRotated);
    g_trace.WriteVal(call, angle);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glRotated) g_real.glRotated(angle, x, y, z);
}

extern "C" void APIENTRYGEN glScaled(GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glScaled);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glScaled) g_real.glScaled(x, y, z);
}

extern "C" void APIENTRYGEN glSelectBuffer(GLsizei size, GLuint * buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glSelectBuffer);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, static_cast<uint8_t>(buffer != nullptr));
    g_trace.EndCall(call);
    if (g_real.glSelectBuffer) g_real.glSelectBuffer(size, buffer);
}

extern "C" void APIENTRYGEN glShadeModel(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glShadeModel);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glShadeModel) g_real.glShadeModel(mode);
}

extern "C" void APIENTRYGEN glStencilFunc(GLenum func, GLint ref, GLuint mask) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilFunc);
    g_trace.WriteVal(call, func);
    g_trace.WriteVal(call, ref);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glStencilFunc) g_real.glStencilFunc(func, ref, mask);
}

extern "C" void APIENTRYGEN glStencilMask(GLuint mask) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilMask);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glStencilMask) g_real.glStencilMask(mask);
}

extern "C" void APIENTRYGEN glStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilOp);
    g_trace.WriteVal(call, fail);
    g_trace.WriteVal(call, zfail);
    g_trace.WriteVal(call, zpass);
    g_trace.EndCall(call);
    if (g_real.glStencilOp) g_real.glStencilOp(fail, zfail, zpass);
}

extern "C" void APIENTRYGEN glTexCoord1d(GLdouble s) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1d);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glTexCoord1d) g_real.glTexCoord1d(s);
}

extern "C" void APIENTRYGEN glTexCoord1dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord1dv) g_real.glTexCoord1dv(v);
}

extern "C" void APIENTRYGEN glTexCoord1f(GLfloat s) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1f);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glTexCoord1f) g_real.glTexCoord1f(s);
}

extern "C" void APIENTRYGEN glTexCoord1fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord1fv) g_real.glTexCoord1fv(v);
}

extern "C" void APIENTRYGEN glTexCoord1i(GLint s) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1i);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glTexCoord1i) g_real.glTexCoord1i(s);
}

extern "C" void APIENTRYGEN glTexCoord1iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord1iv) g_real.glTexCoord1iv(v);
}

extern "C" void APIENTRYGEN glTexCoord1s(GLshort s) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1s);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glTexCoord1s) g_real.glTexCoord1s(s);
}

extern "C" void APIENTRYGEN glTexCoord1sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord1sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord1sv) g_real.glTexCoord1sv(v);
}

extern "C" void APIENTRYGEN glTexCoord2d(GLdouble s, GLdouble t) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2d);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2d) g_real.glTexCoord2d(s, t);
}

extern "C" void APIENTRYGEN glTexCoord2i(GLint s, GLint t) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2i);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2i) g_real.glTexCoord2i(s, t);
}

extern "C" void APIENTRYGEN glTexCoord2s(GLshort s, GLshort t) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2s);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2s) g_real.glTexCoord2s(s, t);
}

extern "C" void APIENTRYGEN glTexCoord2sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord2sv) g_real.glTexCoord2sv(v);
}

extern "C" void APIENTRYGEN glTexCoord3d(GLdouble s, GLdouble t, GLdouble r) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3d);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glTexCoord3d) g_real.glTexCoord3d(s, t, r);
}

extern "C" void APIENTRYGEN glTexCoord3dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord3dv) g_real.glTexCoord3dv(v);
}

extern "C" void APIENTRYGEN glTexCoord3f(GLfloat s, GLfloat t, GLfloat r) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3f);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glTexCoord3f) g_real.glTexCoord3f(s, t, r);
}

extern "C" void APIENTRYGEN glTexCoord3fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord3fv) g_real.glTexCoord3fv(v);
}

extern "C" void APIENTRYGEN glTexCoord3i(GLint s, GLint t, GLint r) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3i);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glTexCoord3i) g_real.glTexCoord3i(s, t, r);
}

extern "C" void APIENTRYGEN glTexCoord3iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord3iv) g_real.glTexCoord3iv(v);
}

extern "C" void APIENTRYGEN glTexCoord3s(GLshort s, GLshort t, GLshort r) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3s);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glTexCoord3s) g_real.glTexCoord3s(s, t, r);
}

extern "C" void APIENTRYGEN glTexCoord3sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord3sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord3sv) g_real.glTexCoord3sv(v);
}

extern "C" void APIENTRYGEN glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4d);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glTexCoord4d) g_real.glTexCoord4d(s, t, r, q);
}

extern "C" void APIENTRYGEN glTexCoord4dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord4dv) g_real.glTexCoord4dv(v);
}

extern "C" void APIENTRYGEN glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4f);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glTexCoord4f) g_real.glTexCoord4f(s, t, r, q);
}

extern "C" void APIENTRYGEN glTexCoord4fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord4fv) g_real.glTexCoord4fv(v);
}

extern "C" void APIENTRYGEN glTexCoord4i(GLint s, GLint t, GLint r, GLint q) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4i);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glTexCoord4i) g_real.glTexCoord4i(s, t, r, q);
}

extern "C" void APIENTRYGEN glTexCoord4iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord4iv) g_real.glTexCoord4iv(v);
}

extern "C" void APIENTRYGEN glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4s);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glTexCoord4s) g_real.glTexCoord4s(s, t, r, q);
}

extern "C" void APIENTRYGEN glTexCoord4sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord4sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexCoord4sv) g_real.glTexCoord4sv(v);
}

extern "C" void APIENTRYGEN glTexEnvf(GLenum target, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexEnvf);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexEnvf) g_real.glTexEnvf(target, pname, param);
}

extern "C" void APIENTRYGEN glTexEnvfv(GLenum target, GLenum pname, const GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexEnvfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexEnvfv) g_real.glTexEnvfv(target, pname, params);
}

extern "C" void APIENTRYGEN glTexEnvi(GLenum target, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexEnvi);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexEnvi) g_real.glTexEnvi(target, pname, param);
}

extern "C" void APIENTRYGEN glTexEnviv(GLenum target, GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexEnviv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexEnviv) g_real.glTexEnviv(target, pname, params);
}

extern "C" void APIENTRYGEN glTexGend(GLenum coord, GLenum pname, GLdouble param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGend);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexGend) g_real.glTexGend(coord, pname, param);
}

extern "C" void APIENTRYGEN glTexGendv(GLenum coord, GLenum pname, const GLdouble * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGendv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexGendv) g_real.glTexGendv(coord, pname, params);
}

extern "C" void APIENTRYGEN glTexGenf(GLenum coord, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGenf);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexGenf) g_real.glTexGenf(coord, pname, param);
}

extern "C" void APIENTRYGEN glTexGenfv(GLenum coord, GLenum pname, const GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGenfv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexGenfv) g_real.glTexGenfv(coord, pname, params);
}

extern "C" void APIENTRYGEN glTexGeni(GLenum coord, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGeni);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTexGeni) g_real.glTexGeni(coord, pname, param);
}

extern "C" void APIENTRYGEN glTexGeniv(GLenum coord, GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexGeniv);
    g_trace.WriteVal(call, coord);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexGeniv) g_real.glTexGeniv(coord, pname, params);
}

extern "C" void APIENTRYGEN glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTexImage1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, border);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(pixels != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexImage1D) g_real.glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
}

extern "C" void APIENTRYGEN glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexParameterfv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexParameterfv) g_real.glTexParameterfv(target, pname, params);
}

extern "C" void APIENTRYGEN glTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    auto call = g_trace.BeginCall(GLFuncId::glTexParameteriv);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexParameteriv) g_real.glTexParameteriv(target, pname, params);
}

extern "C" void APIENTRYGEN glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTexSubImage1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, static_cast<uint8_t>(pixels != nullptr));
    g_trace.EndCall(call);
    if (g_real.glTexSubImage1D) g_real.glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

extern "C" void APIENTRYGEN glTranslated(GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glTranslated);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glTranslated) g_real.glTranslated(x, y, z);
}

extern "C" void APIENTRYGEN glVertex2d(GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertex2d) g_real.glVertex2d(x, y);
}

extern "C" void APIENTRYGEN glVertex2dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex2dv) g_real.glVertex2dv(v);
}

extern "C" void APIENTRYGEN glVertex2fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex2fv) g_real.glVertex2fv(v);
}

extern "C" void APIENTRYGEN glVertex2i(GLint x, GLint y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertex2i) g_real.glVertex2i(x, y);
}

extern "C" void APIENTRYGEN glVertex2iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex2iv) g_real.glVertex2iv(v);
}

extern "C" void APIENTRYGEN glVertex2s(GLshort x, GLshort y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertex2s) g_real.glVertex2s(x, y);
}

extern "C" void APIENTRYGEN glVertex2sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex2sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex2sv) g_real.glVertex2sv(v);
}

extern "C" void APIENTRYGEN glVertex3d(GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertex3d) g_real.glVertex3d(x, y, z);
}

extern "C" void APIENTRYGEN glVertex3i(GLint x, GLint y, GLint z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertex3i) g_real.glVertex3i(x, y, z);
}

extern "C" void APIENTRYGEN glVertex3s(GLshort x, GLshort y, GLshort z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertex3s) g_real.glVertex3s(x, y, z);
}

extern "C" void APIENTRYGEN glVertex3sv(const GLshort * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3sv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex3sv) g_real.glVertex3sv(v);
}

extern "C" void APIENTRYGEN glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertex4d) g_real.glVertex4d(x, y, z, w);
}

extern "C" void APIENTRYGEN glVertex4dv(const GLdouble * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4dv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex4dv) g_real.glVertex4dv(v);
}

extern "C" void APIENTRYGEN glVertex4fv(const GLfloat * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4fv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex4fv) g_real.glVertex4fv(v);
}

extern "C" void APIENTRYGEN glVertex4i(GLint x, GLint y, GLint z, GLint w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertex4i) g_real.glVertex4i(x, y, z, w);
}

extern "C" void APIENTRYGEN glVertex4iv(const GLint * v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4iv);
    g_trace.WriteVal(call, static_cast<uint8_t>(v != nullptr));
    g_trace.EndCall(call);
    if (g_real.glVertex4iv) g_real.glVertex4iv(v);
}

extern "C" void APIENTRYGEN glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertex4s) g_real.glVertex4s(x, y, z, w);
}

extern "C" void APIENTRYGEN glGetShaderiv(GLuint shader, GLenum pname, GLint* params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetShaderiv);
    g_trace.WriteVal(call, shader);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetShaderiv) g_real.glGetShaderiv(shader, pname, params);
}

extern "C" void APIENTRYGEN glGetProgramiv(GLuint program, GLenum pname, GLint* params) {
    auto call = g_trace.BeginCall(GLFuncId::glGetProgramiv);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint8_t>(params != nullptr));
    g_trace.EndCall(call);
    if (g_real.glGetProgramiv) g_real.glGetProgramiv(program, pname, params);
}

extern "C" void APIENTRYGEN glActiveShaderProgram(GLuint pipeline, GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glActiveShaderProgram);
    g_trace.WriteVal(call, pipeline);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glActiveShaderProgram) g_real.glActiveShaderProgram(pipeline, program);
}

extern "C" void APIENTRYGEN glBeginConditionalRender(GLuint id, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glBeginConditionalRender);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glBeginConditionalRender) g_real.glBeginConditionalRender(id, mode);
}

extern "C" void APIENTRYGEN glBeginQuery(GLenum target, GLuint id) {
    auto call = g_trace.BeginCall(GLFuncId::glBeginQuery);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, id);
    g_trace.EndCall(call);
    if (g_real.glBeginQuery) g_real.glBeginQuery(target, id);
}

extern "C" void APIENTRYGEN glBeginQueryIndexed(GLenum target, GLuint index, GLuint id) {
    auto call = g_trace.BeginCall(GLFuncId::glBeginQueryIndexed);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, id);
    g_trace.EndCall(call);
    if (g_real.glBeginQueryIndexed) g_real.glBeginQueryIndexed(target, index, id);
}

extern "C" void APIENTRYGEN glBeginTransformFeedback(GLenum primitiveMode) {
    auto call = g_trace.BeginCall(GLFuncId::glBeginTransformFeedback);
    g_trace.WriteVal(call, primitiveMode);
    g_trace.EndCall(call);
    if (g_real.glBeginTransformFeedback) g_real.glBeginTransformFeedback(primitiveMode);
}

extern "C" void APIENTRYGEN glBindBufferBase(GLenum target, GLuint index, GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glBindBufferBase);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glBindBufferBase) g_real.glBindBufferBase(target, index, buffer);
}

extern "C" void APIENTRYGEN glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glBindBufferRange);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glBindBufferRange) g_real.glBindBufferRange(target, index, buffer, offset, size);
}

extern "C" void APIENTRYGEN glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) {
    auto call = g_trace.BeginCall(GLFuncId::glBindImageTexture);
    g_trace.WriteVal(call, unit);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, layered);
    g_trace.WriteVal(call, layer);
    g_trace.WriteVal(call, access);
    g_trace.WriteVal(call, format);
    g_trace.EndCall(call);
    if (g_real.glBindImageTexture) g_real.glBindImageTexture(unit, texture, level, layered, layer, access, format);
}

extern "C" void APIENTRYGEN glBindProgramPipeline(GLuint pipeline) {
    auto call = g_trace.BeginCall(GLFuncId::glBindProgramPipeline);
    g_trace.WriteVal(call, pipeline);
    g_trace.EndCall(call);
    if (g_real.glBindProgramPipeline) g_real.glBindProgramPipeline(pipeline);
}

extern "C" void APIENTRYGEN glBindSampler(GLuint unit, GLuint sampler) {
    auto call = g_trace.BeginCall(GLFuncId::glBindSampler);
    g_trace.WriteVal(call, unit);
    g_trace.WriteVal(call, sampler);
    g_trace.EndCall(call);
    if (g_real.glBindSampler) g_real.glBindSampler(unit, sampler);
}

extern "C" void APIENTRYGEN glBindTextureUnit(GLuint unit, GLuint texture) {
    auto call = g_trace.BeginCall(GLFuncId::glBindTextureUnit);
    g_trace.WriteVal(call, unit);
    g_trace.WriteVal(call, texture);
    g_trace.EndCall(call);
    if (g_real.glBindTextureUnit) g_real.glBindTextureUnit(unit, texture);
}

extern "C" void APIENTRYGEN glBindTransformFeedback(GLenum target, GLuint id) {
    auto call = g_trace.BeginCall(GLFuncId::glBindTransformFeedback);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, id);
    g_trace.EndCall(call);
    if (g_real.glBindTransformFeedback) g_real.glBindTransformFeedback(target, id);
}

extern "C" void APIENTRYGEN glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
    auto call = g_trace.BeginCall(GLFuncId::glBindVertexBuffer);
    g_trace.WriteVal(call, bindingindex);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, stride);
    g_trace.EndCall(call);
    if (g_real.glBindVertexBuffer) g_real.glBindVertexBuffer(bindingindex, buffer, offset, stride);
}

extern "C" void APIENTRYGEN glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendColor);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.WriteVal(call, alpha);
    g_trace.EndCall(call);
    if (g_real.glBlendColor) g_real.glBlendColor(red, green, blue, alpha);
}

extern "C" void APIENTRYGEN glBlendEquation(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendEquation);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glBlendEquation) g_real.glBlendEquation(mode);
}

extern "C" void APIENTRYGEN glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendEquationSeparate);
    g_trace.WriteVal(call, modeRGB);
    g_trace.WriteVal(call, modeAlpha);
    g_trace.EndCall(call);
    if (g_real.glBlendEquationSeparate) g_real.glBlendEquationSeparate(modeRGB, modeAlpha);
}

extern "C" void APIENTRYGEN glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendEquationSeparatei);
    g_trace.WriteVal(call, buf);
    g_trace.WriteVal(call, modeRGB);
    g_trace.WriteVal(call, modeAlpha);
    g_trace.EndCall(call);
    if (g_real.glBlendEquationSeparatei) g_real.glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
}

extern "C" void APIENTRYGEN glBlendEquationi(GLuint buf, GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendEquationi);
    g_trace.WriteVal(call, buf);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glBlendEquationi) g_real.glBlendEquationi(buf, mode);
}

extern "C" void APIENTRYGEN glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendFuncSeparate);
    g_trace.WriteVal(call, sfactorRGB);
    g_trace.WriteVal(call, dfactorRGB);
    g_trace.WriteVal(call, sfactorAlpha);
    g_trace.WriteVal(call, dfactorAlpha);
    g_trace.EndCall(call);
    if (g_real.glBlendFuncSeparate) g_real.glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

extern "C" void APIENTRYGEN glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendFuncSeparatei);
    g_trace.WriteVal(call, buf);
    g_trace.WriteVal(call, srcRGB);
    g_trace.WriteVal(call, dstRGB);
    g_trace.WriteVal(call, srcAlpha);
    g_trace.WriteVal(call, dstAlpha);
    g_trace.EndCall(call);
    if (g_real.glBlendFuncSeparatei) g_real.glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
}

extern "C" void APIENTRYGEN glBlendFunci(GLuint buf, GLenum src, GLenum dst) {
    auto call = g_trace.BeginCall(GLFuncId::glBlendFunci);
    g_trace.WriteVal(call, buf);
    g_trace.WriteVal(call, src);
    g_trace.WriteVal(call, dst);
    g_trace.EndCall(call);
    if (g_real.glBlendFunci) g_real.glBlendFunci(buf, src, dst);
}

extern "C" void APIENTRYGEN glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    auto call = g_trace.BeginCall(GLFuncId::glBlitFramebuffer);
    g_trace.WriteVal(call, srcX0);
    g_trace.WriteVal(call, srcY0);
    g_trace.WriteVal(call, srcX1);
    g_trace.WriteVal(call, srcY1);
    g_trace.WriteVal(call, dstX0);
    g_trace.WriteVal(call, dstY0);
    g_trace.WriteVal(call, dstX1);
    g_trace.WriteVal(call, dstY1);
    g_trace.WriteVal(call, mask);
    g_trace.WriteVal(call, filter);
    g_trace.EndCall(call);
    if (g_real.glBlitFramebuffer) g_real.glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

extern "C" void APIENTRYGEN glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) {
    auto call = g_trace.BeginCall(GLFuncId::glBlitNamedFramebuffer);
    g_trace.WriteVal(call, readFramebuffer);
    g_trace.WriteVal(call, drawFramebuffer);
    g_trace.WriteVal(call, srcX0);
    g_trace.WriteVal(call, srcY0);
    g_trace.WriteVal(call, srcX1);
    g_trace.WriteVal(call, srcY1);
    g_trace.WriteVal(call, dstX0);
    g_trace.WriteVal(call, dstY0);
    g_trace.WriteVal(call, dstX1);
    g_trace.WriteVal(call, dstY1);
    g_trace.WriteVal(call, mask);
    g_trace.WriteVal(call, filter);
    g_trace.EndCall(call);
    if (g_real.glBlitNamedFramebuffer) g_real.glBlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
}

extern "C" void APIENTRYGEN glClampColor(GLenum target, GLenum clamp) {
    auto call = g_trace.BeginCall(GLFuncId::glClampColor);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, clamp);
    g_trace.EndCall(call);
    if (g_real.glClampColor) g_real.glClampColor(target, clamp);
}

extern "C" void APIENTRYGEN glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    auto call = g_trace.BeginCall(GLFuncId::glClearBufferfi);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, drawbuffer);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, stencil);
    g_trace.EndCall(call);
    if (g_real.glClearBufferfi) g_real.glClearBufferfi(buffer, drawbuffer, depth, stencil);
}

extern "C" void APIENTRYGEN glClearDepthf(GLfloat d) {
    auto call = g_trace.BeginCall(GLFuncId::glClearDepthf);
    g_trace.WriteVal(call, d);
    g_trace.EndCall(call);
    if (g_real.glClearDepthf) g_real.glClearDepthf(d);
}

extern "C" void APIENTRYGEN glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) {
    auto call = g_trace.BeginCall(GLFuncId::glClearNamedFramebufferfi);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, drawbuffer);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, stencil);
    g_trace.EndCall(call);
    if (g_real.glClearNamedFramebufferfi) g_real.glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
}

extern "C" void APIENTRYGEN glClientActiveTexture(GLenum texture) {
    auto call = g_trace.BeginCall(GLFuncId::glClientActiveTexture);
    g_trace.WriteVal(call, texture);
    g_trace.EndCall(call);
    if (g_real.glClientActiveTexture) g_real.glClientActiveTexture(texture);
}

extern "C" void APIENTRYGEN glClipControl(GLenum origin, GLenum depth) {
    auto call = g_trace.BeginCall(GLFuncId::glClipControl);
    g_trace.WriteVal(call, origin);
    g_trace.WriteVal(call, depth);
    g_trace.EndCall(call);
    if (g_real.glClipControl) g_real.glClipControl(origin, depth);
}

extern "C" void APIENTRYGEN glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) {
    auto call = g_trace.BeginCall(GLFuncId::glColorMaski);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, g);
    g_trace.WriteVal(call, b);
    g_trace.WriteVal(call, a);
    g_trace.EndCall(call);
    if (g_real.glColorMaski) g_real.glColorMaski(index, r, g, b, a);
}

extern "C" void APIENTRYGEN glColorP3ui(GLenum type, GLuint color) {
    auto call = g_trace.BeginCall(GLFuncId::glColorP3ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, color);
    g_trace.EndCall(call);
    if (g_real.glColorP3ui) g_real.glColorP3ui(type, color);
}

extern "C" void APIENTRYGEN glColorP4ui(GLenum type, GLuint color) {
    auto call = g_trace.BeginCall(GLFuncId::glColorP4ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, color);
    g_trace.EndCall(call);
    if (g_real.glColorP4ui) g_real.glColorP4ui(type, color);
}

extern "C" void APIENTRYGEN glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyBufferSubData);
    g_trace.WriteVal(call, readTarget);
    g_trace.WriteVal(call, writeTarget);
    g_trace.WriteVal(call, readOffset);
    g_trace.WriteVal(call, writeOffset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glCopyBufferSubData) g_real.glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}

extern "C" void APIENTRYGEN glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyImageSubData);
    g_trace.WriteVal(call, srcName);
    g_trace.WriteVal(call, srcTarget);
    g_trace.WriteVal(call, srcLevel);
    g_trace.WriteVal(call, srcX);
    g_trace.WriteVal(call, srcY);
    g_trace.WriteVal(call, srcZ);
    g_trace.WriteVal(call, dstName);
    g_trace.WriteVal(call, dstTarget);
    g_trace.WriteVal(call, dstLevel);
    g_trace.WriteVal(call, dstX);
    g_trace.WriteVal(call, dstY);
    g_trace.WriteVal(call, dstZ);
    g_trace.WriteVal(call, srcWidth);
    g_trace.WriteVal(call, srcHeight);
    g_trace.WriteVal(call, srcDepth);
    g_trace.EndCall(call);
    if (g_real.glCopyImageSubData) g_real.glCopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
}

extern "C" void APIENTRYGEN glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyNamedBufferSubData);
    g_trace.WriteVal(call, readBuffer);
    g_trace.WriteVal(call, writeBuffer);
    g_trace.WriteVal(call, readOffset);
    g_trace.WriteVal(call, writeOffset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glCopyNamedBufferSubData) g_real.glCopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
}

extern "C" void APIENTRYGEN glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTexSubImage3D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, zoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glCopyTexSubImage3D) g_real.glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
}

extern "C" void APIENTRYGEN glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTextureSubImage1D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.EndCall(call);
    if (g_real.glCopyTextureSubImage1D) g_real.glCopyTextureSubImage1D(texture, level, xoffset, x, y, width);
}

extern "C" void APIENTRYGEN glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTextureSubImage2D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glCopyTextureSubImage2D) g_real.glCopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
}

extern "C" void APIENTRYGEN glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glCopyTextureSubImage3D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, zoffset);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glCopyTextureSubImage3D) g_real.glCopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
}

extern "C" void APIENTRYGEN glDeleteSync(GLsync sync) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteSync);
    g_trace.WriteVal(call, sync);
    g_trace.EndCall(call);
    if (g_real.glDeleteSync) g_real.glDeleteSync(sync);
}

extern "C" void APIENTRYGEN glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) {
    auto call = g_trace.BeginCall(GLFuncId::glDepthRangeIndexed);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, f);
    g_trace.EndCall(call);
    if (g_real.glDepthRangeIndexed) g_real.glDepthRangeIndexed(index, n, f);
}

extern "C" void APIENTRYGEN glDepthRangef(GLfloat n, GLfloat f) {
    auto call = g_trace.BeginCall(GLFuncId::glDepthRangef);
    g_trace.WriteVal(call, n);
    g_trace.WriteVal(call, f);
    g_trace.EndCall(call);
    if (g_real.glDepthRangef) g_real.glDepthRangef(n, f);
}

extern "C" void APIENTRYGEN glDisableVertexArrayAttrib(GLuint vaobj, GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glDisableVertexArrayAttrib);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glDisableVertexArrayAttrib) g_real.glDisableVertexArrayAttrib(vaobj, index);
}

extern "C" void APIENTRYGEN glDisablei(GLenum target, GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glDisablei);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glDisablei) g_real.glDisablei(target, index);
}

extern "C" void APIENTRYGEN glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) {
    auto call = g_trace.BeginCall(GLFuncId::glDispatchCompute);
    g_trace.WriteVal(call, num_groups_x);
    g_trace.WriteVal(call, num_groups_y);
    g_trace.WriteVal(call, num_groups_z);
    g_trace.EndCall(call);
    if (g_real.glDispatchCompute) g_real.glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
}

extern "C" void APIENTRYGEN glDispatchComputeIndirect(GLintptr indirect) {
    auto call = g_trace.BeginCall(GLFuncId::glDispatchComputeIndirect);
    g_trace.WriteVal(call, indirect);
    g_trace.EndCall(call);
    if (g_real.glDispatchComputeIndirect) g_real.glDispatchComputeIndirect(indirect);
}

extern "C" void APIENTRYGEN glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawArraysInstancedBaseInstance);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, first);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, instancecount);
    g_trace.WriteVal(call, baseinstance);
    g_trace.EndCall(call);
    if (g_real.glDrawArraysInstancedBaseInstance) g_real.glDrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
}

extern "C" void APIENTRYGEN glDrawTransformFeedback(GLenum mode, GLuint id) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawTransformFeedback);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, id);
    g_trace.EndCall(call);
    if (g_real.glDrawTransformFeedback) g_real.glDrawTransformFeedback(mode, id);
}

extern "C" void APIENTRYGEN glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawTransformFeedbackInstanced);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, instancecount);
    g_trace.EndCall(call);
    if (g_real.glDrawTransformFeedbackInstanced) g_real.glDrawTransformFeedbackInstanced(mode, id, instancecount);
}

extern "C" void APIENTRYGEN glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawTransformFeedbackStream);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, stream);
    g_trace.EndCall(call);
    if (g_real.glDrawTransformFeedbackStream) g_real.glDrawTransformFeedbackStream(mode, id, stream);
}

extern "C" void APIENTRYGEN glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) {
    auto call = g_trace.BeginCall(GLFuncId::glDrawTransformFeedbackStreamInstanced);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, stream);
    g_trace.WriteVal(call, instancecount);
    g_trace.EndCall(call);
    if (g_real.glDrawTransformFeedbackStreamInstanced) g_real.glDrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
}

extern "C" void APIENTRYGEN glEnableVertexArrayAttrib(GLuint vaobj, GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glEnableVertexArrayAttrib);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glEnableVertexArrayAttrib) g_real.glEnableVertexArrayAttrib(vaobj, index);
}

extern "C" void APIENTRYGEN glEnablei(GLenum target, GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glEnablei);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glEnablei) g_real.glEnablei(target, index);
}

extern "C" void APIENTRYGEN glEndConditionalRender(void) {
    auto call = g_trace.BeginCall(GLFuncId::glEndConditionalRender);
    g_trace.EndCall(call);
    if (g_real.glEndConditionalRender) g_real.glEndConditionalRender();
}

extern "C" void APIENTRYGEN glEndQuery(GLenum target) {
    auto call = g_trace.BeginCall(GLFuncId::glEndQuery);
    g_trace.WriteVal(call, target);
    g_trace.EndCall(call);
    if (g_real.glEndQuery) g_real.glEndQuery(target);
}

extern "C" void APIENTRYGEN glEndQueryIndexed(GLenum target, GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glEndQueryIndexed);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glEndQueryIndexed) g_real.glEndQueryIndexed(target, index);
}

extern "C" void APIENTRYGEN glEndTransformFeedback(void) {
    auto call = g_trace.BeginCall(GLFuncId::glEndTransformFeedback);
    g_trace.EndCall(call);
    if (g_real.glEndTransformFeedback) g_real.glEndTransformFeedback();
}

extern "C" void APIENTRYGEN glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) {
    auto call = g_trace.BeginCall(GLFuncId::glFlushMappedBufferRange);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, length);
    g_trace.EndCall(call);
    if (g_real.glFlushMappedBufferRange) g_real.glFlushMappedBufferRange(target, offset, length);
}

extern "C" void APIENTRYGEN glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) {
    auto call = g_trace.BeginCall(GLFuncId::glFlushMappedNamedBufferRange);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, length);
    g_trace.EndCall(call);
    if (g_real.glFlushMappedNamedBufferRange) g_real.glFlushMappedNamedBufferRange(buffer, offset, length);
}

extern "C" void APIENTRYGEN glFogCoordd(GLdouble coord) {
    auto call = g_trace.BeginCall(GLFuncId::glFogCoordd);
    g_trace.WriteVal(call, coord);
    g_trace.EndCall(call);
    if (g_real.glFogCoordd) g_real.glFogCoordd(coord);
}

extern "C" void APIENTRYGEN glFogCoordf(GLfloat coord) {
    auto call = g_trace.BeginCall(GLFuncId::glFogCoordf);
    g_trace.WriteVal(call, coord);
    g_trace.EndCall(call);
    if (g_real.glFogCoordf) g_real.glFogCoordf(coord);
}

extern "C" void APIENTRYGEN glFramebufferParameteri(GLenum target, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferParameteri);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glFramebufferParameteri) g_real.glFramebufferParameteri(target, pname, param);
}

extern "C" void APIENTRYGEN glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferTexture);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.EndCall(call);
    if (g_real.glFramebufferTexture) g_real.glFramebufferTexture(target, attachment, texture, level);
}

extern "C" void APIENTRYGEN glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferTexture1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, textarget);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.EndCall(call);
    if (g_real.glFramebufferTexture1D) g_real.glFramebufferTexture1D(target, attachment, textarget, texture, level);
}

extern "C" void APIENTRYGEN glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferTexture3D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, textarget);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, zoffset);
    g_trace.EndCall(call);
    if (g_real.glFramebufferTexture3D) g_real.glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
}

extern "C" void APIENTRYGEN glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    auto call = g_trace.BeginCall(GLFuncId::glFramebufferTextureLayer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, layer);
    g_trace.EndCall(call);
    if (g_real.glFramebufferTextureLayer) g_real.glFramebufferTextureLayer(target, attachment, texture, level, layer);
}

extern "C" void APIENTRYGEN glGenerateTextureMipmap(GLuint texture) {
    auto call = g_trace.BeginCall(GLFuncId::glGenerateTextureMipmap);
    g_trace.WriteVal(call, texture);
    g_trace.EndCall(call);
    if (g_real.glGenerateTextureMipmap) g_real.glGenerateTextureMipmap(texture);
}

extern "C" void APIENTRYGEN glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
    auto call = g_trace.BeginCall(GLFuncId::glGetQueryBufferObjecti64v);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, offset);
    g_trace.EndCall(call);
    if (g_real.glGetQueryBufferObjecti64v) g_real.glGetQueryBufferObjecti64v(id, buffer, pname, offset);
}

extern "C" void APIENTRYGEN glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
    auto call = g_trace.BeginCall(GLFuncId::glGetQueryBufferObjectiv);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, offset);
    g_trace.EndCall(call);
    if (g_real.glGetQueryBufferObjectiv) g_real.glGetQueryBufferObjectiv(id, buffer, pname, offset);
}

extern "C" void APIENTRYGEN glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
    auto call = g_trace.BeginCall(GLFuncId::glGetQueryBufferObjectui64v);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, offset);
    g_trace.EndCall(call);
    if (g_real.glGetQueryBufferObjectui64v) g_real.glGetQueryBufferObjectui64v(id, buffer, pname, offset);
}

extern "C" void APIENTRYGEN glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) {
    auto call = g_trace.BeginCall(GLFuncId::glGetQueryBufferObjectuiv);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, offset);
    g_trace.EndCall(call);
    if (g_real.glGetQueryBufferObjectuiv) g_real.glGetQueryBufferObjectuiv(id, buffer, pname, offset);
}

extern "C" void APIENTRYGEN glInvalidateBufferData(GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glInvalidateBufferData);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glInvalidateBufferData) g_real.glInvalidateBufferData(buffer);
}

extern "C" void APIENTRYGEN glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) {
    auto call = g_trace.BeginCall(GLFuncId::glInvalidateBufferSubData);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, length);
    g_trace.EndCall(call);
    if (g_real.glInvalidateBufferSubData) g_real.glInvalidateBufferSubData(buffer, offset, length);
}

extern "C" void APIENTRYGEN glInvalidateTexImage(GLuint texture, GLint level) {
    auto call = g_trace.BeginCall(GLFuncId::glInvalidateTexImage);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.EndCall(call);
    if (g_real.glInvalidateTexImage) g_real.glInvalidateTexImage(texture, level);
}

extern "C" void APIENTRYGEN glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) {
    auto call = g_trace.BeginCall(GLFuncId::glInvalidateTexSubImage);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, zoffset);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.EndCall(call);
    if (g_real.glInvalidateTexSubImage) g_real.glInvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
}

extern "C" void APIENTRYGEN glMemoryBarrier(GLbitfield barriers) {
    auto call = g_trace.BeginCall(GLFuncId::glMemoryBarrier);
    g_trace.WriteVal(call, barriers);
    g_trace.EndCall(call);
    if (g_real.glMemoryBarrier) g_real.glMemoryBarrier(barriers);
}

extern "C" void APIENTRYGEN glMemoryBarrierByRegion(GLbitfield barriers) {
    auto call = g_trace.BeginCall(GLFuncId::glMemoryBarrierByRegion);
    g_trace.WriteVal(call, barriers);
    g_trace.EndCall(call);
    if (g_real.glMemoryBarrierByRegion) g_real.glMemoryBarrierByRegion(barriers);
}

extern "C" void APIENTRYGEN glMinSampleShading(GLfloat value) {
    auto call = g_trace.BeginCall(GLFuncId::glMinSampleShading);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glMinSampleShading) g_real.glMinSampleShading(value);
}

extern "C" void APIENTRYGEN glMultiTexCoord1d(GLenum target, GLdouble s) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord1d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord1d) g_real.glMultiTexCoord1d(target, s);
}

extern "C" void APIENTRYGEN glMultiTexCoord1f(GLenum target, GLfloat s) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord1f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord1f) g_real.glMultiTexCoord1f(target, s);
}

extern "C" void APIENTRYGEN glMultiTexCoord1i(GLenum target, GLint s) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord1i);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord1i) g_real.glMultiTexCoord1i(target, s);
}

extern "C" void APIENTRYGEN glMultiTexCoord1s(GLenum target, GLshort s) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord1s);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord1s) g_real.glMultiTexCoord1s(target, s);
}

extern "C" void APIENTRYGEN glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord2d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord2d) g_real.glMultiTexCoord2d(target, s, t);
}

extern "C" void APIENTRYGEN glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord2f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord2f) g_real.glMultiTexCoord2f(target, s, t);
}

extern "C" void APIENTRYGEN glMultiTexCoord2i(GLenum target, GLint s, GLint t) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord2i);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord2i) g_real.glMultiTexCoord2i(target, s, t);
}

extern "C" void APIENTRYGEN glMultiTexCoord2s(GLenum target, GLshort s, GLshort t) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord2s);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord2s) g_real.glMultiTexCoord2s(target, s, t);
}

extern "C" void APIENTRYGEN glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord3d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord3d) g_real.glMultiTexCoord3d(target, s, t, r);
}

extern "C" void APIENTRYGEN glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord3f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord3f) g_real.glMultiTexCoord3f(target, s, t, r);
}

extern "C" void APIENTRYGEN glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord3i);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord3i) g_real.glMultiTexCoord3i(target, s, t, r);
}

extern "C" void APIENTRYGEN glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord3s);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord3s) g_real.glMultiTexCoord3s(target, s, t, r);
}

extern "C" void APIENTRYGEN glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord4d);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord4d) g_real.glMultiTexCoord4d(target, s, t, r, q);
}

extern "C" void APIENTRYGEN glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord4f);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord4f) g_real.glMultiTexCoord4f(target, s, t, r, q);
}

extern "C" void APIENTRYGEN glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord4i);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord4i) g_real.glMultiTexCoord4i(target, s, t, r, q);
}

extern "C" void APIENTRYGEN glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoord4s);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, s);
    g_trace.WriteVal(call, t);
    g_trace.WriteVal(call, r);
    g_trace.WriteVal(call, q);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoord4s) g_real.glMultiTexCoord4s(target, s, t, r, q);
}

extern "C" void APIENTRYGEN glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoordP1ui);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoordP1ui) g_real.glMultiTexCoordP1ui(texture, type, coords);
}

extern "C" void APIENTRYGEN glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoordP2ui);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoordP2ui) g_real.glMultiTexCoordP2ui(texture, type, coords);
}

extern "C" void APIENTRYGEN glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoordP3ui);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoordP3ui) g_real.glMultiTexCoordP3ui(texture, type, coords);
}

extern "C" void APIENTRYGEN glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glMultiTexCoordP4ui);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glMultiTexCoordP4ui) g_real.glMultiTexCoordP4ui(texture, type, coords);
}

extern "C" void APIENTRYGEN glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferDrawBuffer);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, buf);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferDrawBuffer) g_real.glNamedFramebufferDrawBuffer(framebuffer, buf);
}

extern "C" void APIENTRYGEN glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferParameteri);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferParameteri) g_real.glNamedFramebufferParameteri(framebuffer, pname, param);
}

extern "C" void APIENTRYGEN glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferReadBuffer);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, src);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferReadBuffer) g_real.glNamedFramebufferReadBuffer(framebuffer, src);
}

extern "C" void APIENTRYGEN glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferRenderbuffer);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, renderbuffertarget);
    g_trace.WriteVal(call, renderbuffer);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferRenderbuffer) g_real.glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
}

extern "C" void APIENTRYGEN glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferTexture);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferTexture) g_real.glNamedFramebufferTexture(framebuffer, attachment, texture, level);
}

extern "C" void APIENTRYGEN glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferTextureLayer);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, attachment);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, layer);
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferTextureLayer) g_real.glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
}

extern "C" void APIENTRYGEN glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedRenderbufferStorage);
    g_trace.WriteVal(call, renderbuffer);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glNamedRenderbufferStorage) g_real.glNamedRenderbufferStorage(renderbuffer, internalformat, width, height);
}

extern "C" void APIENTRYGEN glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedRenderbufferStorageMultisample);
    g_trace.WriteVal(call, renderbuffer);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glNamedRenderbufferStorageMultisample) g_real.glNamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
}

extern "C" void APIENTRYGEN glNormalP3ui(GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glNormalP3ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glNormalP3ui) g_real.glNormalP3ui(type, coords);
}

extern "C" void APIENTRYGEN glPatchParameteri(GLenum pname, GLint value) {
    auto call = g_trace.BeginCall(GLFuncId::glPatchParameteri);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glPatchParameteri) g_real.glPatchParameteri(pname, value);
}

extern "C" void APIENTRYGEN glPauseTransformFeedback(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPauseTransformFeedback);
    g_trace.EndCall(call);
    if (g_real.glPauseTransformFeedback) g_real.glPauseTransformFeedback();
}

extern "C" void APIENTRYGEN glPointParameterf(GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glPointParameterf);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPointParameterf) g_real.glPointParameterf(pname, param);
}

extern "C" void APIENTRYGEN glPointParameteri(GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glPointParameteri);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glPointParameteri) g_real.glPointParameteri(pname, param);
}

extern "C" void APIENTRYGEN glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp) {
    auto call = g_trace.BeginCall(GLFuncId::glPolygonOffsetClamp);
    g_trace.WriteVal(call, factor);
    g_trace.WriteVal(call, units);
    g_trace.WriteVal(call, clamp);
    g_trace.EndCall(call);
    if (g_real.glPolygonOffsetClamp) g_real.glPolygonOffsetClamp(factor, units, clamp);
}

extern "C" void APIENTRYGEN glPopDebugGroup(void) {
    auto call = g_trace.BeginCall(GLFuncId::glPopDebugGroup);
    g_trace.EndCall(call);
    if (g_real.glPopDebugGroup) g_real.glPopDebugGroup();
}

extern "C" void APIENTRYGEN glPrimitiveRestartIndex(GLuint index) {
    auto call = g_trace.BeginCall(GLFuncId::glPrimitiveRestartIndex);
    g_trace.WriteVal(call, index);
    g_trace.EndCall(call);
    if (g_real.glPrimitiveRestartIndex) g_real.glPrimitiveRestartIndex(index);
}

extern "C" void APIENTRYGEN glProgramParameteri(GLuint program, GLenum pname, GLint value) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramParameteri);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glProgramParameteri) g_real.glProgramParameteri(program, pname, value);
}

extern "C" void APIENTRYGEN glProgramUniform1d(GLuint program, GLint location, GLdouble v0) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform1d);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform1d) g_real.glProgramUniform1d(program, location, v0);
}

extern "C" void APIENTRYGEN glProgramUniform1f(GLuint program, GLint location, GLfloat v0) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform1f);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform1f) g_real.glProgramUniform1f(program, location, v0);
}

extern "C" void APIENTRYGEN glProgramUniform1i(GLuint program, GLint location, GLint v0) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform1i);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform1i) g_real.glProgramUniform1i(program, location, v0);
}

extern "C" void APIENTRYGEN glProgramUniform1ui(GLuint program, GLint location, GLuint v0) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform1ui);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform1ui) g_real.glProgramUniform1ui(program, location, v0);
}

extern "C" void APIENTRYGEN glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform2d);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform2d) g_real.glProgramUniform2d(program, location, v0, v1);
}

extern "C" void APIENTRYGEN glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform2f);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform2f) g_real.glProgramUniform2f(program, location, v0, v1);
}

extern "C" void APIENTRYGEN glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform2i);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform2i) g_real.glProgramUniform2i(program, location, v0, v1);
}

extern "C" void APIENTRYGEN glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform2ui);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform2ui) g_real.glProgramUniform2ui(program, location, v0, v1);
}

extern "C" void APIENTRYGEN glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform3d);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform3d) g_real.glProgramUniform3d(program, location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform3f);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform3f) g_real.glProgramUniform3f(program, location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform3i);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform3i) g_real.glProgramUniform3i(program, location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform3ui);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform3ui) g_real.glProgramUniform3ui(program, location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform4d);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform4d) g_real.glProgramUniform4d(program, location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform4f);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform4f) g_real.glProgramUniform4f(program, location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform4i);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform4i) g_real.glProgramUniform4i(program, location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    auto call = g_trace.BeginCall(GLFuncId::glProgramUniform4ui);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glProgramUniform4ui) g_real.glProgramUniform4ui(program, location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glProvokingVertex(GLenum mode) {
    auto call = g_trace.BeginCall(GLFuncId::glProvokingVertex);
    g_trace.WriteVal(call, mode);
    g_trace.EndCall(call);
    if (g_real.glProvokingVertex) g_real.glProvokingVertex(mode);
}

extern "C" void APIENTRYGEN glQueryCounter(GLuint id, GLenum target) {
    auto call = g_trace.BeginCall(GLFuncId::glQueryCounter);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, target);
    g_trace.EndCall(call);
    if (g_real.glQueryCounter) g_real.glQueryCounter(id, target);
}

extern "C" void APIENTRYGEN glReleaseShaderCompiler(void) {
    auto call = g_trace.BeginCall(GLFuncId::glReleaseShaderCompiler);
    g_trace.EndCall(call);
    if (g_real.glReleaseShaderCompiler) g_real.glReleaseShaderCompiler();
}

extern "C" void APIENTRYGEN glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glRenderbufferStorageMultisample);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glRenderbufferStorageMultisample) g_real.glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
}

extern "C" void APIENTRYGEN glResumeTransformFeedback(void) {
    auto call = g_trace.BeginCall(GLFuncId::glResumeTransformFeedback);
    g_trace.EndCall(call);
    if (g_real.glResumeTransformFeedback) g_real.glResumeTransformFeedback();
}

extern "C" void APIENTRYGEN glSampleCoverage(GLfloat value, GLboolean invert) {
    auto call = g_trace.BeginCall(GLFuncId::glSampleCoverage);
    g_trace.WriteVal(call, value);
    g_trace.WriteVal(call, invert);
    g_trace.EndCall(call);
    if (g_real.glSampleCoverage) g_real.glSampleCoverage(value, invert);
}

extern "C" void APIENTRYGEN glSampleMaski(GLuint maskNumber, GLbitfield mask) {
    auto call = g_trace.BeginCall(GLFuncId::glSampleMaski);
    g_trace.WriteVal(call, maskNumber);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glSampleMaski) g_real.glSampleMaski(maskNumber, mask);
}

extern "C" void APIENTRYGEN glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glSamplerParameterf);
    g_trace.WriteVal(call, sampler);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glSamplerParameterf) g_real.glSamplerParameterf(sampler, pname, param);
}

extern "C" void APIENTRYGEN glSamplerParameteri(GLuint sampler, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glSamplerParameteri);
    g_trace.WriteVal(call, sampler);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glSamplerParameteri) g_real.glSamplerParameteri(sampler, pname, param);
}

extern "C" void APIENTRYGEN glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glScissorIndexed);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, left);
    g_trace.WriteVal(call, bottom);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glScissorIndexed) g_real.glScissorIndexed(index, left, bottom, width, height);
}

extern "C" void APIENTRYGEN glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3b);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3b) g_real.glSecondaryColor3b(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3d);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3d) g_real.glSecondaryColor3d(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3f);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3f) g_real.glSecondaryColor3f(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3i(GLint red, GLint green, GLint blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3i);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3i) g_real.glSecondaryColor3i(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3s(GLshort red, GLshort green, GLshort blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3s);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3s) g_real.glSecondaryColor3s(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3ub);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3ub) g_real.glSecondaryColor3ub(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3ui);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3ui) g_real.glSecondaryColor3ui(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColor3us(GLushort red, GLushort green, GLushort blue) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColor3us);
    g_trace.WriteVal(call, red);
    g_trace.WriteVal(call, green);
    g_trace.WriteVal(call, blue);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColor3us) g_real.glSecondaryColor3us(red, green, blue);
}

extern "C" void APIENTRYGEN glSecondaryColorP3ui(GLenum type, GLuint color) {
    auto call = g_trace.BeginCall(GLFuncId::glSecondaryColorP3ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, color);
    g_trace.EndCall(call);
    if (g_real.glSecondaryColorP3ui) g_real.glSecondaryColorP3ui(type, color);
}

extern "C" void APIENTRYGEN glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) {
    auto call = g_trace.BeginCall(GLFuncId::glShaderStorageBlockBinding);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, storageBlockIndex);
    g_trace.WriteVal(call, storageBlockBinding);
    g_trace.EndCall(call);
    if (g_real.glShaderStorageBlockBinding) g_real.glShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
}

extern "C" void APIENTRYGEN glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilFuncSeparate);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, func);
    g_trace.WriteVal(call, ref);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glStencilFuncSeparate) g_real.glStencilFuncSeparate(face, func, ref, mask);
}

extern "C" void APIENTRYGEN glStencilMaskSeparate(GLenum face, GLuint mask) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilMaskSeparate);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, mask);
    g_trace.EndCall(call);
    if (g_real.glStencilMaskSeparate) g_real.glStencilMaskSeparate(face, mask);
}

extern "C" void APIENTRYGEN glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    auto call = g_trace.BeginCall(GLFuncId::glStencilOpSeparate);
    g_trace.WriteVal(call, face);
    g_trace.WriteVal(call, sfail);
    g_trace.WriteVal(call, dpfail);
    g_trace.WriteVal(call, dppass);
    g_trace.EndCall(call);
    if (g_real.glStencilOpSeparate) g_real.glStencilOpSeparate(face, sfail, dpfail, dppass);
}

extern "C" void APIENTRYGEN glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glTexBuffer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glTexBuffer) g_real.glTexBuffer(target, internalformat, buffer);
}

extern "C" void APIENTRYGEN glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glTexBufferRange);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glTexBufferRange) g_real.glTexBufferRange(target, internalformat, buffer, offset, size);
}

extern "C" void APIENTRYGEN glTexCoordP1ui(GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoordP1ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glTexCoordP1ui) g_real.glTexCoordP1ui(type, coords);
}

extern "C" void APIENTRYGEN glTexCoordP2ui(GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoordP2ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glTexCoordP2ui) g_real.glTexCoordP2ui(type, coords);
}

extern "C" void APIENTRYGEN glTexCoordP3ui(GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoordP3ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glTexCoordP3ui) g_real.glTexCoordP3ui(type, coords);
}

extern "C" void APIENTRYGEN glTexCoordP4ui(GLenum type, GLuint coords) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoordP4ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, coords);
    g_trace.EndCall(call);
    if (g_real.glTexCoordP4ui) g_real.glTexCoordP4ui(type, coords);
}

extern "C" void APIENTRYGEN glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTexImage2DMultisample);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTexImage2DMultisample) g_real.glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTexImage3DMultisample);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTexImage3DMultisample) g_real.glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) {
    auto call = g_trace.BeginCall(GLFuncId::glTexStorage1D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.EndCall(call);
    if (g_real.glTexStorage1D) g_real.glTexStorage1D(target, levels, internalformat, width);
}

extern "C" void APIENTRYGEN glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glTexStorage2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glTexStorage2D) g_real.glTexStorage2D(target, levels, internalformat, width, height);
}

extern "C" void APIENTRYGEN glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTexStorage2DMultisample);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTexStorage2DMultisample) g_real.glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
    auto call = g_trace.BeginCall(GLFuncId::glTexStorage3D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.EndCall(call);
    if (g_real.glTexStorage3D) g_real.glTexStorage3D(target, levels, internalformat, width, height, depth);
}

extern "C" void APIENTRYGEN glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTexStorage3DMultisample);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTexStorage3DMultisample) g_real.glTexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTextureBarrier(void) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureBarrier);
    g_trace.EndCall(call);
    if (g_real.glTextureBarrier) g_real.glTextureBarrier();
}

extern "C" void APIENTRYGEN glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureBuffer);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glTextureBuffer) g_real.glTextureBuffer(texture, internalformat, buffer);
}

extern "C" void APIENTRYGEN glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureBufferRange);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glTextureBufferRange) g_real.glTextureBufferRange(texture, internalformat, buffer, offset, size);
}

extern "C" void APIENTRYGEN glTextureParameterf(GLuint texture, GLenum pname, GLfloat param) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureParameterf);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTextureParameterf) g_real.glTextureParameterf(texture, pname, param);
}

extern "C" void APIENTRYGEN glTextureParameteri(GLuint texture, GLenum pname, GLint param) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureParameteri);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, param);
    g_trace.EndCall(call);
    if (g_real.glTextureParameteri) g_real.glTextureParameteri(texture, pname, param);
}

extern "C" void APIENTRYGEN glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureStorage1D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.EndCall(call);
    if (g_real.glTextureStorage1D) g_real.glTextureStorage1D(texture, levels, internalformat, width);
}

extern "C" void APIENTRYGEN glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureStorage2D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.EndCall(call);
    if (g_real.glTextureStorage2D) g_real.glTextureStorage2D(texture, levels, internalformat, width, height);
}

extern "C" void APIENTRYGEN glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureStorage2DMultisample);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTextureStorage2DMultisample) g_real.glTextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureStorage3D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, levels);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.EndCall(call);
    if (g_real.glTextureStorage3D) g_real.glTextureStorage3D(texture, levels, internalformat, width, height, depth);
}

extern "C" void APIENTRYGEN glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureStorage3DMultisample);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, samples);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, fixedsamplelocations);
    g_trace.EndCall(call);
    if (g_real.glTextureStorage3DMultisample) g_real.glTextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
}

extern "C" void APIENTRYGEN glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureView);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, origtexture);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, minlevel);
    g_trace.WriteVal(call, numlevels);
    g_trace.WriteVal(call, minlayer);
    g_trace.WriteVal(call, numlayers);
    g_trace.EndCall(call);
    if (g_real.glTextureView) g_real.glTextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
}

extern "C" void APIENTRYGEN glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glTransformFeedbackBufferBase);
    g_trace.WriteVal(call, xfb);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glTransformFeedbackBufferBase) g_real.glTransformFeedbackBufferBase(xfb, index, buffer);
}

extern "C" void APIENTRYGEN glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) {
    auto call = g_trace.BeginCall(GLFuncId::glTransformFeedbackBufferRange);
    g_trace.WriteVal(call, xfb);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    g_trace.EndCall(call);
    if (g_real.glTransformFeedbackBufferRange) g_real.glTransformFeedbackBufferRange(xfb, index, buffer, offset, size);
}

extern "C" void APIENTRYGEN glUniform1d(GLint location, GLdouble x) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform1d);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glUniform1d) g_real.glUniform1d(location, x);
}

extern "C" void APIENTRYGEN glUniform1ui(GLint location, GLuint v0) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform1ui);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.EndCall(call);
    if (g_real.glUniform1ui) g_real.glUniform1ui(location, v0);
}

extern "C" void APIENTRYGEN glUniform2d(GLint location, GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform2d);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glUniform2d) g_real.glUniform2d(location, x, y);
}

extern "C" void APIENTRYGEN glUniform2i(GLint location, GLint v0, GLint v1) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform2i);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glUniform2i) g_real.glUniform2i(location, v0, v1);
}

extern "C" void APIENTRYGEN glUniform2ui(GLint location, GLuint v0, GLuint v1) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform2ui);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.EndCall(call);
    if (g_real.glUniform2ui) g_real.glUniform2ui(location, v0, v1);
}

extern "C" void APIENTRYGEN glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform3d);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glUniform3d) g_real.glUniform3d(location, x, y, z);
}

extern "C" void APIENTRYGEN glUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform3i);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glUniform3i) g_real.glUniform3i(location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform3ui);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.EndCall(call);
    if (g_real.glUniform3ui) g_real.glUniform3ui(location, v0, v1, v2);
}

extern "C" void APIENTRYGEN glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform4d);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glUniform4d) g_real.glUniform4d(location, x, y, z, w);
}

extern "C" void APIENTRYGEN glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform4i);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glUniform4i) g_real.glUniform4i(location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
    auto call = g_trace.BeginCall(GLFuncId::glUniform4ui);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, v0);
    g_trace.WriteVal(call, v1);
    g_trace.WriteVal(call, v2);
    g_trace.WriteVal(call, v3);
    g_trace.EndCall(call);
    if (g_real.glUniform4ui) g_real.glUniform4ui(location, v0, v1, v2, v3);
}

extern "C" void APIENTRYGEN glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) {
    auto call = g_trace.BeginCall(GLFuncId::glUniformBlockBinding);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, uniformBlockIndex);
    g_trace.WriteVal(call, uniformBlockBinding);
    g_trace.EndCall(call);
    if (g_real.glUniformBlockBinding) g_real.glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
}

extern "C" void APIENTRYGEN glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glUseProgramStages);
    g_trace.WriteVal(call, pipeline);
    g_trace.WriteVal(call, stages);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glUseProgramStages) g_real.glUseProgramStages(pipeline, stages, program);
}

extern "C" void APIENTRYGEN glValidateProgram(GLuint program) {
    auto call = g_trace.BeginCall(GLFuncId::glValidateProgram);
    g_trace.WriteVal(call, program);
    g_trace.EndCall(call);
    if (g_real.glValidateProgram) g_real.glValidateProgram(program);
}

extern "C" void APIENTRYGEN glValidateProgramPipeline(GLuint pipeline) {
    auto call = g_trace.BeginCall(GLFuncId::glValidateProgramPipeline);
    g_trace.WriteVal(call, pipeline);
    g_trace.EndCall(call);
    if (g_real.glValidateProgramPipeline) g_real.glValidateProgramPipeline(pipeline);
}

extern "C" void APIENTRYGEN glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayAttribBinding);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, bindingindex);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayAttribBinding) g_real.glVertexArrayAttribBinding(vaobj, attribindex, bindingindex);
}

extern "C" void APIENTRYGEN glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayAttribFormat);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayAttribFormat) g_real.glVertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayAttribIFormat);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayAttribIFormat) g_real.glVertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayAttribLFormat);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayAttribLFormat) g_real.glVertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayBindingDivisor);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, bindingindex);
    g_trace.WriteVal(call, divisor);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayBindingDivisor) g_real.glVertexArrayBindingDivisor(vaobj, bindingindex, divisor);
}

extern "C" void APIENTRYGEN glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayElementBuffer);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayElementBuffer) g_real.glVertexArrayElementBuffer(vaobj, buffer);
}

extern "C" void APIENTRYGEN glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexArrayVertexBuffer);
    g_trace.WriteVal(call, vaobj);
    g_trace.WriteVal(call, bindingindex);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, stride);
    g_trace.EndCall(call);
    if (g_real.glVertexArrayVertexBuffer) g_real.glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
}

extern "C" void APIENTRYGEN glVertexAttrib1d(GLuint index, GLdouble x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib1d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib1d) g_real.glVertexAttrib1d(index, x);
}

extern "C" void APIENTRYGEN glVertexAttrib1f(GLuint index, GLfloat x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib1f);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib1f) g_real.glVertexAttrib1f(index, x);
}

extern "C" void APIENTRYGEN glVertexAttrib1s(GLuint index, GLshort x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib1s);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib1s) g_real.glVertexAttrib1s(index, x);
}

extern "C" void APIENTRYGEN glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib2d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib2d) g_real.glVertexAttrib2d(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib2f);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib2f) g_real.glVertexAttrib2f(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttrib2s(GLuint index, GLshort x, GLshort y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib2s);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib2s) g_real.glVertexAttrib2s(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib3d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib3d) g_real.glVertexAttrib3d(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib3f);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib3f) g_real.glVertexAttrib3f(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib3s);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib3s) g_real.glVertexAttrib3s(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib4Nub);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib4Nub) g_real.glVertexAttrib4Nub(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib4d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib4d) g_real.glVertexAttrib4d(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib4f);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib4f) g_real.glVertexAttrib4f(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttrib4s);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttrib4s) g_real.glVertexAttrib4s(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttribBinding(GLuint attribindex, GLuint bindingindex) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribBinding);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, bindingindex);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribBinding) g_real.glVertexAttribBinding(attribindex, bindingindex);
}

extern "C" void APIENTRYGEN glVertexAttribDivisor(GLuint index, GLuint divisor) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribDivisor);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, divisor);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribDivisor) g_real.glVertexAttribDivisor(index, divisor);
}

extern "C" void APIENTRYGEN glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribFormat);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribFormat) g_real.glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexAttribI1i(GLuint index, GLint x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI1i);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI1i) g_real.glVertexAttribI1i(index, x);
}

extern "C" void APIENTRYGEN glVertexAttribI1ui(GLuint index, GLuint x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI1ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI1ui) g_real.glVertexAttribI1ui(index, x);
}

extern "C" void APIENTRYGEN glVertexAttribI2i(GLuint index, GLint x, GLint y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI2i);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI2i) g_real.glVertexAttribI2i(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttribI2ui(GLuint index, GLuint x, GLuint y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI2ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI2ui) g_real.glVertexAttribI2ui(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI3i);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI3i) g_real.glVertexAttribI3i(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI3ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI3ui) g_real.glVertexAttribI3ui(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI4i);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI4i) g_real.glVertexAttribI4i(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribI4ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribI4ui) g_real.glVertexAttribI4ui(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribIFormat);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribIFormat) g_real.glVertexAttribIFormat(attribindex, size, type, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexAttribL1d(GLuint index, GLdouble x) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribL1d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribL1d) g_real.glVertexAttribL1d(index, x);
}

extern "C" void APIENTRYGEN glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribL2d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribL2d) g_real.glVertexAttribL2d(index, x, y);
}

extern "C" void APIENTRYGEN glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribL3d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribL3d) g_real.glVertexAttribL3d(index, x, y, z);
}

extern "C" void APIENTRYGEN glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribL4d);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.WriteVal(call, w);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribL4d) g_real.glVertexAttribL4d(index, x, y, z, w);
}

extern "C" void APIENTRYGEN glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribLFormat);
    g_trace.WriteVal(call, attribindex);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, relativeoffset);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribLFormat) g_real.glVertexAttribLFormat(attribindex, size, type, relativeoffset);
}

extern "C" void APIENTRYGEN glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribP1ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribP1ui) g_real.glVertexAttribP1ui(index, type, normalized, value);
}

extern "C" void APIENTRYGEN glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribP2ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribP2ui) g_real.glVertexAttribP2ui(index, type, normalized, value);
}

extern "C" void APIENTRYGEN glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribP3ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribP3ui) g_real.glVertexAttribP3ui(index, type, normalized, value);
}

extern "C" void APIENTRYGEN glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribP4ui);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexAttribP4ui) g_real.glVertexAttribP4ui(index, type, normalized, value);
}

extern "C" void APIENTRYGEN glVertexBindingDivisor(GLuint bindingindex, GLuint divisor) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexBindingDivisor);
    g_trace.WriteVal(call, bindingindex);
    g_trace.WriteVal(call, divisor);
    g_trace.EndCall(call);
    if (g_real.glVertexBindingDivisor) g_real.glVertexBindingDivisor(bindingindex, divisor);
}

extern "C" void APIENTRYGEN glVertexP2ui(GLenum type, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexP2ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexP2ui) g_real.glVertexP2ui(type, value);
}

extern "C" void APIENTRYGEN glVertexP3ui(GLenum type, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexP3ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexP3ui) g_real.glVertexP3ui(type, value);
}

extern "C" void APIENTRYGEN glVertexP4ui(GLenum type, GLuint value) {
    auto call = g_trace.BeginCall(GLFuncId::glVertexP4ui);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, value);
    g_trace.EndCall(call);
    if (g_real.glVertexP4ui) g_real.glVertexP4ui(type, value);
}

extern "C" void APIENTRYGEN glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) {
    auto call = g_trace.BeginCall(GLFuncId::glViewportIndexedf);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, w);
    g_trace.WriteVal(call, h);
    g_trace.EndCall(call);
    if (g_real.glViewportIndexedf) g_real.glViewportIndexedf(index, x, y, w, h);
}

extern "C" void APIENTRYGEN glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) {
    auto call = g_trace.BeginCall(GLFuncId::glWaitSync);
    g_trace.WriteVal(call, sync);
    g_trace.WriteVal(call, flags);
    g_trace.WriteVal(call, timeout);
    g_trace.EndCall(call);
    if (g_real.glWaitSync) g_real.glWaitSync(sync, flags, timeout);
}

extern "C" void APIENTRYGEN glWindowPos2d(GLdouble x, GLdouble y) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos2d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glWindowPos2d) g_real.glWindowPos2d(x, y);
}

extern "C" void APIENTRYGEN glWindowPos2f(GLfloat x, GLfloat y) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos2f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glWindowPos2f) g_real.glWindowPos2f(x, y);
}

extern "C" void APIENTRYGEN glWindowPos2i(GLint x, GLint y) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos2i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glWindowPos2i) g_real.glWindowPos2i(x, y);
}

extern "C" void APIENTRYGEN glWindowPos2s(GLshort x, GLshort y) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos2s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.EndCall(call);
    if (g_real.glWindowPos2s) g_real.glWindowPos2s(x, y);
}

extern "C" void APIENTRYGEN glWindowPos3d(GLdouble x, GLdouble y, GLdouble z) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos3d);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glWindowPos3d) g_real.glWindowPos3d(x, y, z);
}

extern "C" void APIENTRYGEN glWindowPos3f(GLfloat x, GLfloat y, GLfloat z) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos3f);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glWindowPos3f) g_real.glWindowPos3f(x, y, z);
}

extern "C" void APIENTRYGEN glWindowPos3i(GLint x, GLint y, GLint z) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos3i);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glWindowPos3i) g_real.glWindowPos3i(x, y, z);
}

extern "C" void APIENTRYGEN glWindowPos3s(GLshort x, GLshort y, GLshort z) {
    auto call = g_trace.BeginCall(GLFuncId::glWindowPos3s);
    g_trace.WriteVal(call, x);
    g_trace.WriteVal(call, y);
    g_trace.WriteVal(call, z);
    g_trace.EndCall(call);
    if (g_real.glWindowPos3s) g_real.glWindowPos3s(x, y, z);
}


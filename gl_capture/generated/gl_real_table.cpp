#include <windows.h>
#include "gl_real_table.h"
#include <cstring>

RealGLFunctions g_real;

void LoadRealGLFunctions(void* moduleHandle, void* (*getProcFn)(const char*)) {
    HMODULE mod = (HMODULE)moduleHandle;
    g_real.glEnable = (PFN_glEnable)GetProcAddress(mod, "glEnable");
    if (!g_real.glEnable && getProcFn) g_real.glEnable = (PFN_glEnable)getProcFn("glEnable");
    g_real.glDisable = (PFN_glDisable)GetProcAddress(mod, "glDisable");
    if (!g_real.glDisable && getProcFn) g_real.glDisable = (PFN_glDisable)getProcFn("glDisable");
    g_real.glClearColor = (PFN_glClearColor)GetProcAddress(mod, "glClearColor");
    if (!g_real.glClearColor && getProcFn) g_real.glClearColor = (PFN_glClearColor)getProcFn("glClearColor");
    g_real.glClearDepth = (PFN_glClearDepth)GetProcAddress(mod, "glClearDepth");
    if (!g_real.glClearDepth && getProcFn) g_real.glClearDepth = (PFN_glClearDepth)getProcFn("glClearDepth");
    g_real.glClear = (PFN_glClear)GetProcAddress(mod, "glClear");
    if (!g_real.glClear && getProcFn) g_real.glClear = (PFN_glClear)getProcFn("glClear");
    g_real.glBlendFunc = (PFN_glBlendFunc)GetProcAddress(mod, "glBlendFunc");
    if (!g_real.glBlendFunc && getProcFn) g_real.glBlendFunc = (PFN_glBlendFunc)getProcFn("glBlendFunc");
    g_real.glDepthFunc = (PFN_glDepthFunc)GetProcAddress(mod, "glDepthFunc");
    if (!g_real.glDepthFunc && getProcFn) g_real.glDepthFunc = (PFN_glDepthFunc)getProcFn("glDepthFunc");
    g_real.glDepthMask = (PFN_glDepthMask)GetProcAddress(mod, "glDepthMask");
    if (!g_real.glDepthMask && getProcFn) g_real.glDepthMask = (PFN_glDepthMask)getProcFn("glDepthMask");
    g_real.glCullFace = (PFN_glCullFace)GetProcAddress(mod, "glCullFace");
    if (!g_real.glCullFace && getProcFn) g_real.glCullFace = (PFN_glCullFace)getProcFn("glCullFace");
    g_real.glFrontFace = (PFN_glFrontFace)GetProcAddress(mod, "glFrontFace");
    if (!g_real.glFrontFace && getProcFn) g_real.glFrontFace = (PFN_glFrontFace)getProcFn("glFrontFace");
    g_real.glPolygonMode = (PFN_glPolygonMode)GetProcAddress(mod, "glPolygonMode");
    if (!g_real.glPolygonMode && getProcFn) g_real.glPolygonMode = (PFN_glPolygonMode)getProcFn("glPolygonMode");
    g_real.glLineWidth = (PFN_glLineWidth)GetProcAddress(mod, "glLineWidth");
    if (!g_real.glLineWidth && getProcFn) g_real.glLineWidth = (PFN_glLineWidth)getProcFn("glLineWidth");
    g_real.glPointSize = (PFN_glPointSize)GetProcAddress(mod, "glPointSize");
    if (!g_real.glPointSize && getProcFn) g_real.glPointSize = (PFN_glPointSize)getProcFn("glPointSize");
    g_real.glViewport = (PFN_glViewport)GetProcAddress(mod, "glViewport");
    if (!g_real.glViewport && getProcFn) g_real.glViewport = (PFN_glViewport)getProcFn("glViewport");
    g_real.glScissor = (PFN_glScissor)GetProcAddress(mod, "glScissor");
    if (!g_real.glScissor && getProcFn) g_real.glScissor = (PFN_glScissor)getProcFn("glScissor");
    g_real.glMatrixMode = (PFN_glMatrixMode)GetProcAddress(mod, "glMatrixMode");
    if (!g_real.glMatrixMode && getProcFn) g_real.glMatrixMode = (PFN_glMatrixMode)getProcFn("glMatrixMode");
    g_real.glLoadIdentity = (PFN_glLoadIdentity)GetProcAddress(mod, "glLoadIdentity");
    if (!g_real.glLoadIdentity && getProcFn) g_real.glLoadIdentity = (PFN_glLoadIdentity)getProcFn("glLoadIdentity");
    g_real.glPushMatrix = (PFN_glPushMatrix)GetProcAddress(mod, "glPushMatrix");
    if (!g_real.glPushMatrix && getProcFn) g_real.glPushMatrix = (PFN_glPushMatrix)getProcFn("glPushMatrix");
    g_real.glPopMatrix = (PFN_glPopMatrix)GetProcAddress(mod, "glPopMatrix");
    if (!g_real.glPopMatrix && getProcFn) g_real.glPopMatrix = (PFN_glPopMatrix)getProcFn("glPopMatrix");
    g_real.glTranslatef = (PFN_glTranslatef)GetProcAddress(mod, "glTranslatef");
    if (!g_real.glTranslatef && getProcFn) g_real.glTranslatef = (PFN_glTranslatef)getProcFn("glTranslatef");
    g_real.glRotatef = (PFN_glRotatef)GetProcAddress(mod, "glRotatef");
    if (!g_real.glRotatef && getProcFn) g_real.glRotatef = (PFN_glRotatef)getProcFn("glRotatef");
    g_real.glScalef = (PFN_glScalef)GetProcAddress(mod, "glScalef");
    if (!g_real.glScalef && getProcFn) g_real.glScalef = (PFN_glScalef)getProcFn("glScalef");
    g_real.glOrtho = (PFN_glOrtho)GetProcAddress(mod, "glOrtho");
    if (!g_real.glOrtho && getProcFn) g_real.glOrtho = (PFN_glOrtho)getProcFn("glOrtho");
    g_real.glFrustum = (PFN_glFrustum)GetProcAddress(mod, "glFrustum");
    if (!g_real.glFrustum && getProcFn) g_real.glFrustum = (PFN_glFrustum)getProcFn("glFrustum");
    g_real.glBegin = (PFN_glBegin)GetProcAddress(mod, "glBegin");
    if (!g_real.glBegin && getProcFn) g_real.glBegin = (PFN_glBegin)getProcFn("glBegin");
    g_real.glEnd = (PFN_glEnd)GetProcAddress(mod, "glEnd");
    if (!g_real.glEnd && getProcFn) g_real.glEnd = (PFN_glEnd)getProcFn("glEnd");
    g_real.glVertex2f = (PFN_glVertex2f)GetProcAddress(mod, "glVertex2f");
    if (!g_real.glVertex2f && getProcFn) g_real.glVertex2f = (PFN_glVertex2f)getProcFn("glVertex2f");
    g_real.glVertex3f = (PFN_glVertex3f)GetProcAddress(mod, "glVertex3f");
    if (!g_real.glVertex3f && getProcFn) g_real.glVertex3f = (PFN_glVertex3f)getProcFn("glVertex3f");
    g_real.glVertex4f = (PFN_glVertex4f)GetProcAddress(mod, "glVertex4f");
    if (!g_real.glVertex4f && getProcFn) g_real.glVertex4f = (PFN_glVertex4f)getProcFn("glVertex4f");
    g_real.glColor3f = (PFN_glColor3f)GetProcAddress(mod, "glColor3f");
    if (!g_real.glColor3f && getProcFn) g_real.glColor3f = (PFN_glColor3f)getProcFn("glColor3f");
    g_real.glColor4f = (PFN_glColor4f)GetProcAddress(mod, "glColor4f");
    if (!g_real.glColor4f && getProcFn) g_real.glColor4f = (PFN_glColor4f)getProcFn("glColor4f");
    g_real.glNormal3f = (PFN_glNormal3f)GetProcAddress(mod, "glNormal3f");
    if (!g_real.glNormal3f && getProcFn) g_real.glNormal3f = (PFN_glNormal3f)getProcFn("glNormal3f");
    g_real.glTexCoord2f = (PFN_glTexCoord2f)GetProcAddress(mod, "glTexCoord2f");
    if (!g_real.glTexCoord2f && getProcFn) g_real.glTexCoord2f = (PFN_glTexCoord2f)getProcFn("glTexCoord2f");
    g_real.glEnableClientState = (PFN_glEnableClientState)GetProcAddress(mod, "glEnableClientState");
    if (!g_real.glEnableClientState && getProcFn) g_real.glEnableClientState = (PFN_glEnableClientState)getProcFn("glEnableClientState");
    g_real.glDisableClientState = (PFN_glDisableClientState)GetProcAddress(mod, "glDisableClientState");
    if (!g_real.glDisableClientState && getProcFn) g_real.glDisableClientState = (PFN_glDisableClientState)getProcFn("glDisableClientState");
    g_real.glGenBuffers = (PFN_glGenBuffers)GetProcAddress(mod, "glGenBuffers");
    if (!g_real.glGenBuffers && getProcFn) g_real.glGenBuffers = (PFN_glGenBuffers)getProcFn("glGenBuffers");
    g_real.glDeleteBuffers = (PFN_glDeleteBuffers)GetProcAddress(mod, "glDeleteBuffers");
    if (!g_real.glDeleteBuffers && getProcFn) g_real.glDeleteBuffers = (PFN_glDeleteBuffers)getProcFn("glDeleteBuffers");
    g_real.glBindBuffer = (PFN_glBindBuffer)GetProcAddress(mod, "glBindBuffer");
    if (!g_real.glBindBuffer && getProcFn) g_real.glBindBuffer = (PFN_glBindBuffer)getProcFn("glBindBuffer");
    g_real.glBufferData = (PFN_glBufferData)GetProcAddress(mod, "glBufferData");
    if (!g_real.glBufferData && getProcFn) g_real.glBufferData = (PFN_glBufferData)getProcFn("glBufferData");
    g_real.glBufferSubData = (PFN_glBufferSubData)GetProcAddress(mod, "glBufferSubData");
    if (!g_real.glBufferSubData && getProcFn) g_real.glBufferSubData = (PFN_glBufferSubData)getProcFn("glBufferSubData");
    g_real.glGenVertexArrays = (PFN_glGenVertexArrays)GetProcAddress(mod, "glGenVertexArrays");
    if (!g_real.glGenVertexArrays && getProcFn) g_real.glGenVertexArrays = (PFN_glGenVertexArrays)getProcFn("glGenVertexArrays");
    g_real.glDeleteVertexArrays = (PFN_glDeleteVertexArrays)GetProcAddress(mod, "glDeleteVertexArrays");
    if (!g_real.glDeleteVertexArrays && getProcFn) g_real.glDeleteVertexArrays = (PFN_glDeleteVertexArrays)getProcFn("glDeleteVertexArrays");
    g_real.glBindVertexArray = (PFN_glBindVertexArray)GetProcAddress(mod, "glBindVertexArray");
    if (!g_real.glBindVertexArray && getProcFn) g_real.glBindVertexArray = (PFN_glBindVertexArray)getProcFn("glBindVertexArray");
    g_real.glEnableVertexAttribArray = (PFN_glEnableVertexAttribArray)GetProcAddress(mod, "glEnableVertexAttribArray");
    if (!g_real.glEnableVertexAttribArray && getProcFn) g_real.glEnableVertexAttribArray = (PFN_glEnableVertexAttribArray)getProcFn("glEnableVertexAttribArray");
    g_real.glDisableVertexAttribArray = (PFN_glDisableVertexAttribArray)GetProcAddress(mod, "glDisableVertexAttribArray");
    if (!g_real.glDisableVertexAttribArray && getProcFn) g_real.glDisableVertexAttribArray = (PFN_glDisableVertexAttribArray)getProcFn("glDisableVertexAttribArray");
    g_real.glVertexAttribPointer = (PFN_glVertexAttribPointer)GetProcAddress(mod, "glVertexAttribPointer");
    if (!g_real.glVertexAttribPointer && getProcFn) g_real.glVertexAttribPointer = (PFN_glVertexAttribPointer)getProcFn("glVertexAttribPointer");
    g_real.glVertexPointer = (PFN_glVertexPointer)GetProcAddress(mod, "glVertexPointer");
    if (!g_real.glVertexPointer && getProcFn) g_real.glVertexPointer = (PFN_glVertexPointer)getProcFn("glVertexPointer");
    g_real.glColorPointer = (PFN_glColorPointer)GetProcAddress(mod, "glColorPointer");
    if (!g_real.glColorPointer && getProcFn) g_real.glColorPointer = (PFN_glColorPointer)getProcFn("glColorPointer");
    g_real.glTexCoordPointer = (PFN_glTexCoordPointer)GetProcAddress(mod, "glTexCoordPointer");
    if (!g_real.glTexCoordPointer && getProcFn) g_real.glTexCoordPointer = (PFN_glTexCoordPointer)getProcFn("glTexCoordPointer");
    g_real.glNormalPointer = (PFN_glNormalPointer)GetProcAddress(mod, "glNormalPointer");
    if (!g_real.glNormalPointer && getProcFn) g_real.glNormalPointer = (PFN_glNormalPointer)getProcFn("glNormalPointer");
    g_real.glGenTextures = (PFN_glGenTextures)GetProcAddress(mod, "glGenTextures");
    if (!g_real.glGenTextures && getProcFn) g_real.glGenTextures = (PFN_glGenTextures)getProcFn("glGenTextures");
    g_real.glDeleteTextures = (PFN_glDeleteTextures)GetProcAddress(mod, "glDeleteTextures");
    if (!g_real.glDeleteTextures && getProcFn) g_real.glDeleteTextures = (PFN_glDeleteTextures)getProcFn("glDeleteTextures");
    g_real.glBindTexture = (PFN_glBindTexture)GetProcAddress(mod, "glBindTexture");
    if (!g_real.glBindTexture && getProcFn) g_real.glBindTexture = (PFN_glBindTexture)getProcFn("glBindTexture");
    g_real.glActiveTexture = (PFN_glActiveTexture)GetProcAddress(mod, "glActiveTexture");
    if (!g_real.glActiveTexture && getProcFn) g_real.glActiveTexture = (PFN_glActiveTexture)getProcFn("glActiveTexture");
    g_real.glTexParameteri = (PFN_glTexParameteri)GetProcAddress(mod, "glTexParameteri");
    if (!g_real.glTexParameteri && getProcFn) g_real.glTexParameteri = (PFN_glTexParameteri)getProcFn("glTexParameteri");
    g_real.glTexParameterf = (PFN_glTexParameterf)GetProcAddress(mod, "glTexParameterf");
    if (!g_real.glTexParameterf && getProcFn) g_real.glTexParameterf = (PFN_glTexParameterf)getProcFn("glTexParameterf");
    g_real.glPixelStorei = (PFN_glPixelStorei)GetProcAddress(mod, "glPixelStorei");
    if (!g_real.glPixelStorei && getProcFn) g_real.glPixelStorei = (PFN_glPixelStorei)getProcFn("glPixelStorei");
    g_real.glTexImage2D = (PFN_glTexImage2D)GetProcAddress(mod, "glTexImage2D");
    if (!g_real.glTexImage2D && getProcFn) g_real.glTexImage2D = (PFN_glTexImage2D)getProcFn("glTexImage2D");
    g_real.glTexSubImage2D = (PFN_glTexSubImage2D)GetProcAddress(mod, "glTexSubImage2D");
    if (!g_real.glTexSubImage2D && getProcFn) g_real.glTexSubImage2D = (PFN_glTexSubImage2D)getProcFn("glTexSubImage2D");
    g_real.glGenerateMipmap = (PFN_glGenerateMipmap)GetProcAddress(mod, "glGenerateMipmap");
    if (!g_real.glGenerateMipmap && getProcFn) g_real.glGenerateMipmap = (PFN_glGenerateMipmap)getProcFn("glGenerateMipmap");
    g_real.glCreateShader = (PFN_glCreateShader)GetProcAddress(mod, "glCreateShader");
    if (!g_real.glCreateShader && getProcFn) g_real.glCreateShader = (PFN_glCreateShader)getProcFn("glCreateShader");
    g_real.glDeleteShader = (PFN_glDeleteShader)GetProcAddress(mod, "glDeleteShader");
    if (!g_real.glDeleteShader && getProcFn) g_real.glDeleteShader = (PFN_glDeleteShader)getProcFn("glDeleteShader");
    g_real.glShaderSource = (PFN_glShaderSource)GetProcAddress(mod, "glShaderSource");
    if (!g_real.glShaderSource && getProcFn) g_real.glShaderSource = (PFN_glShaderSource)getProcFn("glShaderSource");
    g_real.glCompileShader = (PFN_glCompileShader)GetProcAddress(mod, "glCompileShader");
    if (!g_real.glCompileShader && getProcFn) g_real.glCompileShader = (PFN_glCompileShader)getProcFn("glCompileShader");
    g_real.glCreateProgram = (PFN_glCreateProgram)GetProcAddress(mod, "glCreateProgram");
    if (!g_real.glCreateProgram && getProcFn) g_real.glCreateProgram = (PFN_glCreateProgram)getProcFn("glCreateProgram");
    g_real.glDeleteProgram = (PFN_glDeleteProgram)GetProcAddress(mod, "glDeleteProgram");
    if (!g_real.glDeleteProgram && getProcFn) g_real.glDeleteProgram = (PFN_glDeleteProgram)getProcFn("glDeleteProgram");
    g_real.glAttachShader = (PFN_glAttachShader)GetProcAddress(mod, "glAttachShader");
    if (!g_real.glAttachShader && getProcFn) g_real.glAttachShader = (PFN_glAttachShader)getProcFn("glAttachShader");
    g_real.glDetachShader = (PFN_glDetachShader)GetProcAddress(mod, "glDetachShader");
    if (!g_real.glDetachShader && getProcFn) g_real.glDetachShader = (PFN_glDetachShader)getProcFn("glDetachShader");
    g_real.glLinkProgram = (PFN_glLinkProgram)GetProcAddress(mod, "glLinkProgram");
    if (!g_real.glLinkProgram && getProcFn) g_real.glLinkProgram = (PFN_glLinkProgram)getProcFn("glLinkProgram");
    g_real.glUseProgram = (PFN_glUseProgram)GetProcAddress(mod, "glUseProgram");
    if (!g_real.glUseProgram && getProcFn) g_real.glUseProgram = (PFN_glUseProgram)getProcFn("glUseProgram");
    g_real.glBindAttribLocation = (PFN_glBindAttribLocation)GetProcAddress(mod, "glBindAttribLocation");
    if (!g_real.glBindAttribLocation && getProcFn) g_real.glBindAttribLocation = (PFN_glBindAttribLocation)getProcFn("glBindAttribLocation");
    g_real.glGetUniformLocation = (PFN_glGetUniformLocation)GetProcAddress(mod, "glGetUniformLocation");
    if (!g_real.glGetUniformLocation && getProcFn) g_real.glGetUniformLocation = (PFN_glGetUniformLocation)getProcFn("glGetUniformLocation");
    g_real.glGetAttribLocation = (PFN_glGetAttribLocation)GetProcAddress(mod, "glGetAttribLocation");
    if (!g_real.glGetAttribLocation && getProcFn) g_real.glGetAttribLocation = (PFN_glGetAttribLocation)getProcFn("glGetAttribLocation");
    g_real.glUniform1i = (PFN_glUniform1i)GetProcAddress(mod, "glUniform1i");
    if (!g_real.glUniform1i && getProcFn) g_real.glUniform1i = (PFN_glUniform1i)getProcFn("glUniform1i");
    g_real.glUniform1f = (PFN_glUniform1f)GetProcAddress(mod, "glUniform1f");
    if (!g_real.glUniform1f && getProcFn) g_real.glUniform1f = (PFN_glUniform1f)getProcFn("glUniform1f");
    g_real.glUniform2f = (PFN_glUniform2f)GetProcAddress(mod, "glUniform2f");
    if (!g_real.glUniform2f && getProcFn) g_real.glUniform2f = (PFN_glUniform2f)getProcFn("glUniform2f");
    g_real.glUniform3f = (PFN_glUniform3f)GetProcAddress(mod, "glUniform3f");
    if (!g_real.glUniform3f && getProcFn) g_real.glUniform3f = (PFN_glUniform3f)getProcFn("glUniform3f");
    g_real.glUniform4f = (PFN_glUniform4f)GetProcAddress(mod, "glUniform4f");
    if (!g_real.glUniform4f && getProcFn) g_real.glUniform4f = (PFN_glUniform4f)getProcFn("glUniform4f");
    g_real.glUniformMatrix4fv = (PFN_glUniformMatrix4fv)GetProcAddress(mod, "glUniformMatrix4fv");
    if (!g_real.glUniformMatrix4fv && getProcFn) g_real.glUniformMatrix4fv = (PFN_glUniformMatrix4fv)getProcFn("glUniformMatrix4fv");
    g_real.glUniformMatrix3fv = (PFN_glUniformMatrix3fv)GetProcAddress(mod, "glUniformMatrix3fv");
    if (!g_real.glUniformMatrix3fv && getProcFn) g_real.glUniformMatrix3fv = (PFN_glUniformMatrix3fv)getProcFn("glUniformMatrix3fv");
    g_real.glGenFramebuffers = (PFN_glGenFramebuffers)GetProcAddress(mod, "glGenFramebuffers");
    if (!g_real.glGenFramebuffers && getProcFn) g_real.glGenFramebuffers = (PFN_glGenFramebuffers)getProcFn("glGenFramebuffers");
    g_real.glDeleteFramebuffers = (PFN_glDeleteFramebuffers)GetProcAddress(mod, "glDeleteFramebuffers");
    if (!g_real.glDeleteFramebuffers && getProcFn) g_real.glDeleteFramebuffers = (PFN_glDeleteFramebuffers)getProcFn("glDeleteFramebuffers");
    g_real.glBindFramebuffer = (PFN_glBindFramebuffer)GetProcAddress(mod, "glBindFramebuffer");
    if (!g_real.glBindFramebuffer && getProcFn) g_real.glBindFramebuffer = (PFN_glBindFramebuffer)getProcFn("glBindFramebuffer");
    g_real.glFramebufferTexture2D = (PFN_glFramebufferTexture2D)GetProcAddress(mod, "glFramebufferTexture2D");
    if (!g_real.glFramebufferTexture2D && getProcFn) g_real.glFramebufferTexture2D = (PFN_glFramebufferTexture2D)getProcFn("glFramebufferTexture2D");
    g_real.glGenRenderbuffers = (PFN_glGenRenderbuffers)GetProcAddress(mod, "glGenRenderbuffers");
    if (!g_real.glGenRenderbuffers && getProcFn) g_real.glGenRenderbuffers = (PFN_glGenRenderbuffers)getProcFn("glGenRenderbuffers");
    g_real.glDeleteRenderbuffers = (PFN_glDeleteRenderbuffers)GetProcAddress(mod, "glDeleteRenderbuffers");
    if (!g_real.glDeleteRenderbuffers && getProcFn) g_real.glDeleteRenderbuffers = (PFN_glDeleteRenderbuffers)getProcFn("glDeleteRenderbuffers");
    g_real.glBindRenderbuffer = (PFN_glBindRenderbuffer)GetProcAddress(mod, "glBindRenderbuffer");
    if (!g_real.glBindRenderbuffer && getProcFn) g_real.glBindRenderbuffer = (PFN_glBindRenderbuffer)getProcFn("glBindRenderbuffer");
    g_real.glRenderbufferStorage = (PFN_glRenderbufferStorage)GetProcAddress(mod, "glRenderbufferStorage");
    if (!g_real.glRenderbufferStorage && getProcFn) g_real.glRenderbufferStorage = (PFN_glRenderbufferStorage)getProcFn("glRenderbufferStorage");
    g_real.glFramebufferRenderbuffer = (PFN_glFramebufferRenderbuffer)GetProcAddress(mod, "glFramebufferRenderbuffer");
    if (!g_real.glFramebufferRenderbuffer && getProcFn) g_real.glFramebufferRenderbuffer = (PFN_glFramebufferRenderbuffer)getProcFn("glFramebufferRenderbuffer");
    g_real.glCheckFramebufferStatus = (PFN_glCheckFramebufferStatus)GetProcAddress(mod, "glCheckFramebufferStatus");
    if (!g_real.glCheckFramebufferStatus && getProcFn) g_real.glCheckFramebufferStatus = (PFN_glCheckFramebufferStatus)getProcFn("glCheckFramebufferStatus");
    g_real.glDrawArrays = (PFN_glDrawArrays)GetProcAddress(mod, "glDrawArrays");
    if (!g_real.glDrawArrays && getProcFn) g_real.glDrawArrays = (PFN_glDrawArrays)getProcFn("glDrawArrays");
    g_real.glDrawElements = (PFN_glDrawElements)GetProcAddress(mod, "glDrawElements");
    if (!g_real.glDrawElements && getProcFn) g_real.glDrawElements = (PFN_glDrawElements)getProcFn("glDrawElements");
    g_real.glDrawArraysInstanced = (PFN_glDrawArraysInstanced)GetProcAddress(mod, "glDrawArraysInstanced");
    if (!g_real.glDrawArraysInstanced && getProcFn) g_real.glDrawArraysInstanced = (PFN_glDrawArraysInstanced)getProcFn("glDrawArraysInstanced");
    g_real.glDrawElementsInstanced = (PFN_glDrawElementsInstanced)GetProcAddress(mod, "glDrawElementsInstanced");
    if (!g_real.glDrawElementsInstanced && getProcFn) g_real.glDrawElementsInstanced = (PFN_glDrawElementsInstanced)getProcFn("glDrawElementsInstanced");
    g_real.glGetString = (PFN_glGetString)GetProcAddress(mod, "glGetString");
    if (!g_real.glGetString && getProcFn) g_real.glGetString = (PFN_glGetString)getProcFn("glGetString");
    g_real.glAccum = (PFN_glAccum)GetProcAddress(mod, "glAccum");
    if (!g_real.glAccum && getProcFn) g_real.glAccum = (PFN_glAccum)getProcFn("glAccum");
    g_real.glAlphaFunc = (PFN_glAlphaFunc)GetProcAddress(mod, "glAlphaFunc");
    if (!g_real.glAlphaFunc && getProcFn) g_real.glAlphaFunc = (PFN_glAlphaFunc)getProcFn("glAlphaFunc");
    g_real.glAreTexturesResident = (PFN_glAreTexturesResident)GetProcAddress(mod, "glAreTexturesResident");
    if (!g_real.glAreTexturesResident && getProcFn) g_real.glAreTexturesResident = (PFN_glAreTexturesResident)getProcFn("glAreTexturesResident");
    g_real.glArrayElement = (PFN_glArrayElement)GetProcAddress(mod, "glArrayElement");
    if (!g_real.glArrayElement && getProcFn) g_real.glArrayElement = (PFN_glArrayElement)getProcFn("glArrayElement");
    g_real.glBitmap = (PFN_glBitmap)GetProcAddress(mod, "glBitmap");
    if (!g_real.glBitmap && getProcFn) g_real.glBitmap = (PFN_glBitmap)getProcFn("glBitmap");
    g_real.glCallList = (PFN_glCallList)GetProcAddress(mod, "glCallList");
    if (!g_real.glCallList && getProcFn) g_real.glCallList = (PFN_glCallList)getProcFn("glCallList");
    g_real.glCallLists = (PFN_glCallLists)GetProcAddress(mod, "glCallLists");
    if (!g_real.glCallLists && getProcFn) g_real.glCallLists = (PFN_glCallLists)getProcFn("glCallLists");
    g_real.glClearAccum = (PFN_glClearAccum)GetProcAddress(mod, "glClearAccum");
    if (!g_real.glClearAccum && getProcFn) g_real.glClearAccum = (PFN_glClearAccum)getProcFn("glClearAccum");
    g_real.glClearIndex = (PFN_glClearIndex)GetProcAddress(mod, "glClearIndex");
    if (!g_real.glClearIndex && getProcFn) g_real.glClearIndex = (PFN_glClearIndex)getProcFn("glClearIndex");
    g_real.glClearStencil = (PFN_glClearStencil)GetProcAddress(mod, "glClearStencil");
    if (!g_real.glClearStencil && getProcFn) g_real.glClearStencil = (PFN_glClearStencil)getProcFn("glClearStencil");
    g_real.glClipPlane = (PFN_glClipPlane)GetProcAddress(mod, "glClipPlane");
    if (!g_real.glClipPlane && getProcFn) g_real.glClipPlane = (PFN_glClipPlane)getProcFn("glClipPlane");
    g_real.glColor3b = (PFN_glColor3b)GetProcAddress(mod, "glColor3b");
    if (!g_real.glColor3b && getProcFn) g_real.glColor3b = (PFN_glColor3b)getProcFn("glColor3b");
    g_real.glColor3bv = (PFN_glColor3bv)GetProcAddress(mod, "glColor3bv");
    if (!g_real.glColor3bv && getProcFn) g_real.glColor3bv = (PFN_glColor3bv)getProcFn("glColor3bv");
    g_real.glColor3d = (PFN_glColor3d)GetProcAddress(mod, "glColor3d");
    if (!g_real.glColor3d && getProcFn) g_real.glColor3d = (PFN_glColor3d)getProcFn("glColor3d");
    g_real.glColor3dv = (PFN_glColor3dv)GetProcAddress(mod, "glColor3dv");
    if (!g_real.glColor3dv && getProcFn) g_real.glColor3dv = (PFN_glColor3dv)getProcFn("glColor3dv");
    g_real.glColor3fv = (PFN_glColor3fv)GetProcAddress(mod, "glColor3fv");
    if (!g_real.glColor3fv && getProcFn) g_real.glColor3fv = (PFN_glColor3fv)getProcFn("glColor3fv");
    g_real.glColor3i = (PFN_glColor3i)GetProcAddress(mod, "glColor3i");
    if (!g_real.glColor3i && getProcFn) g_real.glColor3i = (PFN_glColor3i)getProcFn("glColor3i");
    g_real.glColor3iv = (PFN_glColor3iv)GetProcAddress(mod, "glColor3iv");
    if (!g_real.glColor3iv && getProcFn) g_real.glColor3iv = (PFN_glColor3iv)getProcFn("glColor3iv");
    g_real.glColor3s = (PFN_glColor3s)GetProcAddress(mod, "glColor3s");
    if (!g_real.glColor3s && getProcFn) g_real.glColor3s = (PFN_glColor3s)getProcFn("glColor3s");
    g_real.glColor3sv = (PFN_glColor3sv)GetProcAddress(mod, "glColor3sv");
    if (!g_real.glColor3sv && getProcFn) g_real.glColor3sv = (PFN_glColor3sv)getProcFn("glColor3sv");
    g_real.glColor3ub = (PFN_glColor3ub)GetProcAddress(mod, "glColor3ub");
    if (!g_real.glColor3ub && getProcFn) g_real.glColor3ub = (PFN_glColor3ub)getProcFn("glColor3ub");
    g_real.glColor3ubv = (PFN_glColor3ubv)GetProcAddress(mod, "glColor3ubv");
    if (!g_real.glColor3ubv && getProcFn) g_real.glColor3ubv = (PFN_glColor3ubv)getProcFn("glColor3ubv");
    g_real.glColor3ui = (PFN_glColor3ui)GetProcAddress(mod, "glColor3ui");
    if (!g_real.glColor3ui && getProcFn) g_real.glColor3ui = (PFN_glColor3ui)getProcFn("glColor3ui");
    g_real.glColor3uiv = (PFN_glColor3uiv)GetProcAddress(mod, "glColor3uiv");
    if (!g_real.glColor3uiv && getProcFn) g_real.glColor3uiv = (PFN_glColor3uiv)getProcFn("glColor3uiv");
    g_real.glColor3us = (PFN_glColor3us)GetProcAddress(mod, "glColor3us");
    if (!g_real.glColor3us && getProcFn) g_real.glColor3us = (PFN_glColor3us)getProcFn("glColor3us");
    g_real.glColor3usv = (PFN_glColor3usv)GetProcAddress(mod, "glColor3usv");
    if (!g_real.glColor3usv && getProcFn) g_real.glColor3usv = (PFN_glColor3usv)getProcFn("glColor3usv");
    g_real.glColor4b = (PFN_glColor4b)GetProcAddress(mod, "glColor4b");
    if (!g_real.glColor4b && getProcFn) g_real.glColor4b = (PFN_glColor4b)getProcFn("glColor4b");
    g_real.glColor4bv = (PFN_glColor4bv)GetProcAddress(mod, "glColor4bv");
    if (!g_real.glColor4bv && getProcFn) g_real.glColor4bv = (PFN_glColor4bv)getProcFn("glColor4bv");
    g_real.glColor4d = (PFN_glColor4d)GetProcAddress(mod, "glColor4d");
    if (!g_real.glColor4d && getProcFn) g_real.glColor4d = (PFN_glColor4d)getProcFn("glColor4d");
    g_real.glColor4dv = (PFN_glColor4dv)GetProcAddress(mod, "glColor4dv");
    if (!g_real.glColor4dv && getProcFn) g_real.glColor4dv = (PFN_glColor4dv)getProcFn("glColor4dv");
    g_real.glColor4fv = (PFN_glColor4fv)GetProcAddress(mod, "glColor4fv");
    if (!g_real.glColor4fv && getProcFn) g_real.glColor4fv = (PFN_glColor4fv)getProcFn("glColor4fv");
    g_real.glColor4i = (PFN_glColor4i)GetProcAddress(mod, "glColor4i");
    if (!g_real.glColor4i && getProcFn) g_real.glColor4i = (PFN_glColor4i)getProcFn("glColor4i");
    g_real.glColor4iv = (PFN_glColor4iv)GetProcAddress(mod, "glColor4iv");
    if (!g_real.glColor4iv && getProcFn) g_real.glColor4iv = (PFN_glColor4iv)getProcFn("glColor4iv");
    g_real.glColor4s = (PFN_glColor4s)GetProcAddress(mod, "glColor4s");
    if (!g_real.glColor4s && getProcFn) g_real.glColor4s = (PFN_glColor4s)getProcFn("glColor4s");
    g_real.glColor4sv = (PFN_glColor4sv)GetProcAddress(mod, "glColor4sv");
    if (!g_real.glColor4sv && getProcFn) g_real.glColor4sv = (PFN_glColor4sv)getProcFn("glColor4sv");
    g_real.glColor4ub = (PFN_glColor4ub)GetProcAddress(mod, "glColor4ub");
    if (!g_real.glColor4ub && getProcFn) g_real.glColor4ub = (PFN_glColor4ub)getProcFn("glColor4ub");
    g_real.glColor4ubv = (PFN_glColor4ubv)GetProcAddress(mod, "glColor4ubv");
    if (!g_real.glColor4ubv && getProcFn) g_real.glColor4ubv = (PFN_glColor4ubv)getProcFn("glColor4ubv");
    g_real.glColor4ui = (PFN_glColor4ui)GetProcAddress(mod, "glColor4ui");
    if (!g_real.glColor4ui && getProcFn) g_real.glColor4ui = (PFN_glColor4ui)getProcFn("glColor4ui");
    g_real.glColor4uiv = (PFN_glColor4uiv)GetProcAddress(mod, "glColor4uiv");
    if (!g_real.glColor4uiv && getProcFn) g_real.glColor4uiv = (PFN_glColor4uiv)getProcFn("glColor4uiv");
    g_real.glColor4us = (PFN_glColor4us)GetProcAddress(mod, "glColor4us");
    if (!g_real.glColor4us && getProcFn) g_real.glColor4us = (PFN_glColor4us)getProcFn("glColor4us");
    g_real.glColor4usv = (PFN_glColor4usv)GetProcAddress(mod, "glColor4usv");
    if (!g_real.glColor4usv && getProcFn) g_real.glColor4usv = (PFN_glColor4usv)getProcFn("glColor4usv");
    g_real.glColorMask = (PFN_glColorMask)GetProcAddress(mod, "glColorMask");
    if (!g_real.glColorMask && getProcFn) g_real.glColorMask = (PFN_glColorMask)getProcFn("glColorMask");
    g_real.glColorMaterial = (PFN_glColorMaterial)GetProcAddress(mod, "glColorMaterial");
    if (!g_real.glColorMaterial && getProcFn) g_real.glColorMaterial = (PFN_glColorMaterial)getProcFn("glColorMaterial");
    g_real.glCopyPixels = (PFN_glCopyPixels)GetProcAddress(mod, "glCopyPixels");
    if (!g_real.glCopyPixels && getProcFn) g_real.glCopyPixels = (PFN_glCopyPixels)getProcFn("glCopyPixels");
    g_real.glCopyTexImage1D = (PFN_glCopyTexImage1D)GetProcAddress(mod, "glCopyTexImage1D");
    if (!g_real.glCopyTexImage1D && getProcFn) g_real.glCopyTexImage1D = (PFN_glCopyTexImage1D)getProcFn("glCopyTexImage1D");
    g_real.glCopyTexImage2D = (PFN_glCopyTexImage2D)GetProcAddress(mod, "glCopyTexImage2D");
    if (!g_real.glCopyTexImage2D && getProcFn) g_real.glCopyTexImage2D = (PFN_glCopyTexImage2D)getProcFn("glCopyTexImage2D");
    g_real.glCopyTexSubImage1D = (PFN_glCopyTexSubImage1D)GetProcAddress(mod, "glCopyTexSubImage1D");
    if (!g_real.glCopyTexSubImage1D && getProcFn) g_real.glCopyTexSubImage1D = (PFN_glCopyTexSubImage1D)getProcFn("glCopyTexSubImage1D");
    g_real.glCopyTexSubImage2D = (PFN_glCopyTexSubImage2D)GetProcAddress(mod, "glCopyTexSubImage2D");
    if (!g_real.glCopyTexSubImage2D && getProcFn) g_real.glCopyTexSubImage2D = (PFN_glCopyTexSubImage2D)getProcFn("glCopyTexSubImage2D");
    g_real.glDeleteLists = (PFN_glDeleteLists)GetProcAddress(mod, "glDeleteLists");
    if (!g_real.glDeleteLists && getProcFn) g_real.glDeleteLists = (PFN_glDeleteLists)getProcFn("glDeleteLists");
    g_real.glDepthRange = (PFN_glDepthRange)GetProcAddress(mod, "glDepthRange");
    if (!g_real.glDepthRange && getProcFn) g_real.glDepthRange = (PFN_glDepthRange)getProcFn("glDepthRange");
    g_real.glDrawBuffer = (PFN_glDrawBuffer)GetProcAddress(mod, "glDrawBuffer");
    if (!g_real.glDrawBuffer && getProcFn) g_real.glDrawBuffer = (PFN_glDrawBuffer)getProcFn("glDrawBuffer");
    g_real.glDrawPixels = (PFN_glDrawPixels)GetProcAddress(mod, "glDrawPixels");
    if (!g_real.glDrawPixels && getProcFn) g_real.glDrawPixels = (PFN_glDrawPixels)getProcFn("glDrawPixels");
    g_real.glEdgeFlag = (PFN_glEdgeFlag)GetProcAddress(mod, "glEdgeFlag");
    if (!g_real.glEdgeFlag && getProcFn) g_real.glEdgeFlag = (PFN_glEdgeFlag)getProcFn("glEdgeFlag");
    g_real.glEdgeFlagPointer = (PFN_glEdgeFlagPointer)GetProcAddress(mod, "glEdgeFlagPointer");
    if (!g_real.glEdgeFlagPointer && getProcFn) g_real.glEdgeFlagPointer = (PFN_glEdgeFlagPointer)getProcFn("glEdgeFlagPointer");
    g_real.glEdgeFlagv = (PFN_glEdgeFlagv)GetProcAddress(mod, "glEdgeFlagv");
    if (!g_real.glEdgeFlagv && getProcFn) g_real.glEdgeFlagv = (PFN_glEdgeFlagv)getProcFn("glEdgeFlagv");
    g_real.glEndList = (PFN_glEndList)GetProcAddress(mod, "glEndList");
    if (!g_real.glEndList && getProcFn) g_real.glEndList = (PFN_glEndList)getProcFn("glEndList");
    g_real.glEvalCoord1d = (PFN_glEvalCoord1d)GetProcAddress(mod, "glEvalCoord1d");
    if (!g_real.glEvalCoord1d && getProcFn) g_real.glEvalCoord1d = (PFN_glEvalCoord1d)getProcFn("glEvalCoord1d");
    g_real.glEvalCoord1dv = (PFN_glEvalCoord1dv)GetProcAddress(mod, "glEvalCoord1dv");
    if (!g_real.glEvalCoord1dv && getProcFn) g_real.glEvalCoord1dv = (PFN_glEvalCoord1dv)getProcFn("glEvalCoord1dv");
    g_real.glEvalCoord1f = (PFN_glEvalCoord1f)GetProcAddress(mod, "glEvalCoord1f");
    if (!g_real.glEvalCoord1f && getProcFn) g_real.glEvalCoord1f = (PFN_glEvalCoord1f)getProcFn("glEvalCoord1f");
    g_real.glEvalCoord1fv = (PFN_glEvalCoord1fv)GetProcAddress(mod, "glEvalCoord1fv");
    if (!g_real.glEvalCoord1fv && getProcFn) g_real.glEvalCoord1fv = (PFN_glEvalCoord1fv)getProcFn("glEvalCoord1fv");
    g_real.glEvalCoord2d = (PFN_glEvalCoord2d)GetProcAddress(mod, "glEvalCoord2d");
    if (!g_real.glEvalCoord2d && getProcFn) g_real.glEvalCoord2d = (PFN_glEvalCoord2d)getProcFn("glEvalCoord2d");
    g_real.glEvalCoord2dv = (PFN_glEvalCoord2dv)GetProcAddress(mod, "glEvalCoord2dv");
    if (!g_real.glEvalCoord2dv && getProcFn) g_real.glEvalCoord2dv = (PFN_glEvalCoord2dv)getProcFn("glEvalCoord2dv");
    g_real.glEvalCoord2f = (PFN_glEvalCoord2f)GetProcAddress(mod, "glEvalCoord2f");
    if (!g_real.glEvalCoord2f && getProcFn) g_real.glEvalCoord2f = (PFN_glEvalCoord2f)getProcFn("glEvalCoord2f");
    g_real.glEvalCoord2fv = (PFN_glEvalCoord2fv)GetProcAddress(mod, "glEvalCoord2fv");
    if (!g_real.glEvalCoord2fv && getProcFn) g_real.glEvalCoord2fv = (PFN_glEvalCoord2fv)getProcFn("glEvalCoord2fv");
    g_real.glEvalMesh1 = (PFN_glEvalMesh1)GetProcAddress(mod, "glEvalMesh1");
    if (!g_real.glEvalMesh1 && getProcFn) g_real.glEvalMesh1 = (PFN_glEvalMesh1)getProcFn("glEvalMesh1");
    g_real.glEvalMesh2 = (PFN_glEvalMesh2)GetProcAddress(mod, "glEvalMesh2");
    if (!g_real.glEvalMesh2 && getProcFn) g_real.glEvalMesh2 = (PFN_glEvalMesh2)getProcFn("glEvalMesh2");
    g_real.glEvalPoint1 = (PFN_glEvalPoint1)GetProcAddress(mod, "glEvalPoint1");
    if (!g_real.glEvalPoint1 && getProcFn) g_real.glEvalPoint1 = (PFN_glEvalPoint1)getProcFn("glEvalPoint1");
    g_real.glEvalPoint2 = (PFN_glEvalPoint2)GetProcAddress(mod, "glEvalPoint2");
    if (!g_real.glEvalPoint2 && getProcFn) g_real.glEvalPoint2 = (PFN_glEvalPoint2)getProcFn("glEvalPoint2");
    g_real.glFeedbackBuffer = (PFN_glFeedbackBuffer)GetProcAddress(mod, "glFeedbackBuffer");
    if (!g_real.glFeedbackBuffer && getProcFn) g_real.glFeedbackBuffer = (PFN_glFeedbackBuffer)getProcFn("glFeedbackBuffer");
    g_real.glFinish = (PFN_glFinish)GetProcAddress(mod, "glFinish");
    if (!g_real.glFinish && getProcFn) g_real.glFinish = (PFN_glFinish)getProcFn("glFinish");
    g_real.glFlush = (PFN_glFlush)GetProcAddress(mod, "glFlush");
    if (!g_real.glFlush && getProcFn) g_real.glFlush = (PFN_glFlush)getProcFn("glFlush");
    g_real.glFogf = (PFN_glFogf)GetProcAddress(mod, "glFogf");
    if (!g_real.glFogf && getProcFn) g_real.glFogf = (PFN_glFogf)getProcFn("glFogf");
    g_real.glFogfv = (PFN_glFogfv)GetProcAddress(mod, "glFogfv");
    if (!g_real.glFogfv && getProcFn) g_real.glFogfv = (PFN_glFogfv)getProcFn("glFogfv");
    g_real.glFogi = (PFN_glFogi)GetProcAddress(mod, "glFogi");
    if (!g_real.glFogi && getProcFn) g_real.glFogi = (PFN_glFogi)getProcFn("glFogi");
    g_real.glFogiv = (PFN_glFogiv)GetProcAddress(mod, "glFogiv");
    if (!g_real.glFogiv && getProcFn) g_real.glFogiv = (PFN_glFogiv)getProcFn("glFogiv");
    g_real.glGenLists = (PFN_glGenLists)GetProcAddress(mod, "glGenLists");
    if (!g_real.glGenLists && getProcFn) g_real.glGenLists = (PFN_glGenLists)getProcFn("glGenLists");
    g_real.glGetBooleanv = (PFN_glGetBooleanv)GetProcAddress(mod, "glGetBooleanv");
    if (!g_real.glGetBooleanv && getProcFn) g_real.glGetBooleanv = (PFN_glGetBooleanv)getProcFn("glGetBooleanv");
    g_real.glGetClipPlane = (PFN_glGetClipPlane)GetProcAddress(mod, "glGetClipPlane");
    if (!g_real.glGetClipPlane && getProcFn) g_real.glGetClipPlane = (PFN_glGetClipPlane)getProcFn("glGetClipPlane");
    g_real.glGetDoublev = (PFN_glGetDoublev)GetProcAddress(mod, "glGetDoublev");
    if (!g_real.glGetDoublev && getProcFn) g_real.glGetDoublev = (PFN_glGetDoublev)getProcFn("glGetDoublev");
    g_real.glGetError = (PFN_glGetError)GetProcAddress(mod, "glGetError");
    if (!g_real.glGetError && getProcFn) g_real.glGetError = (PFN_glGetError)getProcFn("glGetError");
    g_real.glGetFloatv = (PFN_glGetFloatv)GetProcAddress(mod, "glGetFloatv");
    if (!g_real.glGetFloatv && getProcFn) g_real.glGetFloatv = (PFN_glGetFloatv)getProcFn("glGetFloatv");
    g_real.glGetIntegerv = (PFN_glGetIntegerv)GetProcAddress(mod, "glGetIntegerv");
    if (!g_real.glGetIntegerv && getProcFn) g_real.glGetIntegerv = (PFN_glGetIntegerv)getProcFn("glGetIntegerv");
    g_real.glGetLightfv = (PFN_glGetLightfv)GetProcAddress(mod, "glGetLightfv");
    if (!g_real.glGetLightfv && getProcFn) g_real.glGetLightfv = (PFN_glGetLightfv)getProcFn("glGetLightfv");
    g_real.glGetLightiv = (PFN_glGetLightiv)GetProcAddress(mod, "glGetLightiv");
    if (!g_real.glGetLightiv && getProcFn) g_real.glGetLightiv = (PFN_glGetLightiv)getProcFn("glGetLightiv");
    g_real.glGetMapdv = (PFN_glGetMapdv)GetProcAddress(mod, "glGetMapdv");
    if (!g_real.glGetMapdv && getProcFn) g_real.glGetMapdv = (PFN_glGetMapdv)getProcFn("glGetMapdv");
    g_real.glGetMapfv = (PFN_glGetMapfv)GetProcAddress(mod, "glGetMapfv");
    if (!g_real.glGetMapfv && getProcFn) g_real.glGetMapfv = (PFN_glGetMapfv)getProcFn("glGetMapfv");
    g_real.glGetMapiv = (PFN_glGetMapiv)GetProcAddress(mod, "glGetMapiv");
    if (!g_real.glGetMapiv && getProcFn) g_real.glGetMapiv = (PFN_glGetMapiv)getProcFn("glGetMapiv");
    g_real.glGetMaterialfv = (PFN_glGetMaterialfv)GetProcAddress(mod, "glGetMaterialfv");
    if (!g_real.glGetMaterialfv && getProcFn) g_real.glGetMaterialfv = (PFN_glGetMaterialfv)getProcFn("glGetMaterialfv");
    g_real.glGetMaterialiv = (PFN_glGetMaterialiv)GetProcAddress(mod, "glGetMaterialiv");
    if (!g_real.glGetMaterialiv && getProcFn) g_real.glGetMaterialiv = (PFN_glGetMaterialiv)getProcFn("glGetMaterialiv");
    g_real.glGetPixelMapfv = (PFN_glGetPixelMapfv)GetProcAddress(mod, "glGetPixelMapfv");
    if (!g_real.glGetPixelMapfv && getProcFn) g_real.glGetPixelMapfv = (PFN_glGetPixelMapfv)getProcFn("glGetPixelMapfv");
    g_real.glGetPixelMapuiv = (PFN_glGetPixelMapuiv)GetProcAddress(mod, "glGetPixelMapuiv");
    if (!g_real.glGetPixelMapuiv && getProcFn) g_real.glGetPixelMapuiv = (PFN_glGetPixelMapuiv)getProcFn("glGetPixelMapuiv");
    g_real.glGetPixelMapusv = (PFN_glGetPixelMapusv)GetProcAddress(mod, "glGetPixelMapusv");
    if (!g_real.glGetPixelMapusv && getProcFn) g_real.glGetPixelMapusv = (PFN_glGetPixelMapusv)getProcFn("glGetPixelMapusv");
    g_real.glGetPointerv = (PFN_glGetPointerv)GetProcAddress(mod, "glGetPointerv");
    if (!g_real.glGetPointerv && getProcFn) g_real.glGetPointerv = (PFN_glGetPointerv)getProcFn("glGetPointerv");
    g_real.glGetPolygonStipple = (PFN_glGetPolygonStipple)GetProcAddress(mod, "glGetPolygonStipple");
    if (!g_real.glGetPolygonStipple && getProcFn) g_real.glGetPolygonStipple = (PFN_glGetPolygonStipple)getProcFn("glGetPolygonStipple");
    g_real.glGetTexEnvfv = (PFN_glGetTexEnvfv)GetProcAddress(mod, "glGetTexEnvfv");
    if (!g_real.glGetTexEnvfv && getProcFn) g_real.glGetTexEnvfv = (PFN_glGetTexEnvfv)getProcFn("glGetTexEnvfv");
    g_real.glGetTexEnviv = (PFN_glGetTexEnviv)GetProcAddress(mod, "glGetTexEnviv");
    if (!g_real.glGetTexEnviv && getProcFn) g_real.glGetTexEnviv = (PFN_glGetTexEnviv)getProcFn("glGetTexEnviv");
    g_real.glGetTexGendv = (PFN_glGetTexGendv)GetProcAddress(mod, "glGetTexGendv");
    if (!g_real.glGetTexGendv && getProcFn) g_real.glGetTexGendv = (PFN_glGetTexGendv)getProcFn("glGetTexGendv");
    g_real.glGetTexGenfv = (PFN_glGetTexGenfv)GetProcAddress(mod, "glGetTexGenfv");
    if (!g_real.glGetTexGenfv && getProcFn) g_real.glGetTexGenfv = (PFN_glGetTexGenfv)getProcFn("glGetTexGenfv");
    g_real.glGetTexGeniv = (PFN_glGetTexGeniv)GetProcAddress(mod, "glGetTexGeniv");
    if (!g_real.glGetTexGeniv && getProcFn) g_real.glGetTexGeniv = (PFN_glGetTexGeniv)getProcFn("glGetTexGeniv");
    g_real.glGetTexImage = (PFN_glGetTexImage)GetProcAddress(mod, "glGetTexImage");
    if (!g_real.glGetTexImage && getProcFn) g_real.glGetTexImage = (PFN_glGetTexImage)getProcFn("glGetTexImage");
    g_real.glGetTexLevelParameterfv = (PFN_glGetTexLevelParameterfv)GetProcAddress(mod, "glGetTexLevelParameterfv");
    if (!g_real.glGetTexLevelParameterfv && getProcFn) g_real.glGetTexLevelParameterfv = (PFN_glGetTexLevelParameterfv)getProcFn("glGetTexLevelParameterfv");
    g_real.glGetTexLevelParameteriv = (PFN_glGetTexLevelParameteriv)GetProcAddress(mod, "glGetTexLevelParameteriv");
    if (!g_real.glGetTexLevelParameteriv && getProcFn) g_real.glGetTexLevelParameteriv = (PFN_glGetTexLevelParameteriv)getProcFn("glGetTexLevelParameteriv");
    g_real.glGetTexParameterfv = (PFN_glGetTexParameterfv)GetProcAddress(mod, "glGetTexParameterfv");
    if (!g_real.glGetTexParameterfv && getProcFn) g_real.glGetTexParameterfv = (PFN_glGetTexParameterfv)getProcFn("glGetTexParameterfv");
    g_real.glGetTexParameteriv = (PFN_glGetTexParameteriv)GetProcAddress(mod, "glGetTexParameteriv");
    if (!g_real.glGetTexParameteriv && getProcFn) g_real.glGetTexParameteriv = (PFN_glGetTexParameteriv)getProcFn("glGetTexParameteriv");
    g_real.glHint = (PFN_glHint)GetProcAddress(mod, "glHint");
    if (!g_real.glHint && getProcFn) g_real.glHint = (PFN_glHint)getProcFn("glHint");
    g_real.glIndexMask = (PFN_glIndexMask)GetProcAddress(mod, "glIndexMask");
    if (!g_real.glIndexMask && getProcFn) g_real.glIndexMask = (PFN_glIndexMask)getProcFn("glIndexMask");
    g_real.glIndexPointer = (PFN_glIndexPointer)GetProcAddress(mod, "glIndexPointer");
    if (!g_real.glIndexPointer && getProcFn) g_real.glIndexPointer = (PFN_glIndexPointer)getProcFn("glIndexPointer");
    g_real.glIndexd = (PFN_glIndexd)GetProcAddress(mod, "glIndexd");
    if (!g_real.glIndexd && getProcFn) g_real.glIndexd = (PFN_glIndexd)getProcFn("glIndexd");
    g_real.glIndexdv = (PFN_glIndexdv)GetProcAddress(mod, "glIndexdv");
    if (!g_real.glIndexdv && getProcFn) g_real.glIndexdv = (PFN_glIndexdv)getProcFn("glIndexdv");
    g_real.glIndexf = (PFN_glIndexf)GetProcAddress(mod, "glIndexf");
    if (!g_real.glIndexf && getProcFn) g_real.glIndexf = (PFN_glIndexf)getProcFn("glIndexf");
    g_real.glIndexfv = (PFN_glIndexfv)GetProcAddress(mod, "glIndexfv");
    if (!g_real.glIndexfv && getProcFn) g_real.glIndexfv = (PFN_glIndexfv)getProcFn("glIndexfv");
    g_real.glIndexi = (PFN_glIndexi)GetProcAddress(mod, "glIndexi");
    if (!g_real.glIndexi && getProcFn) g_real.glIndexi = (PFN_glIndexi)getProcFn("glIndexi");
    g_real.glIndexiv = (PFN_glIndexiv)GetProcAddress(mod, "glIndexiv");
    if (!g_real.glIndexiv && getProcFn) g_real.glIndexiv = (PFN_glIndexiv)getProcFn("glIndexiv");
    g_real.glIndexs = (PFN_glIndexs)GetProcAddress(mod, "glIndexs");
    if (!g_real.glIndexs && getProcFn) g_real.glIndexs = (PFN_glIndexs)getProcFn("glIndexs");
    g_real.glIndexsv = (PFN_glIndexsv)GetProcAddress(mod, "glIndexsv");
    if (!g_real.glIndexsv && getProcFn) g_real.glIndexsv = (PFN_glIndexsv)getProcFn("glIndexsv");
    g_real.glIndexub = (PFN_glIndexub)GetProcAddress(mod, "glIndexub");
    if (!g_real.glIndexub && getProcFn) g_real.glIndexub = (PFN_glIndexub)getProcFn("glIndexub");
    g_real.glIndexubv = (PFN_glIndexubv)GetProcAddress(mod, "glIndexubv");
    if (!g_real.glIndexubv && getProcFn) g_real.glIndexubv = (PFN_glIndexubv)getProcFn("glIndexubv");
    g_real.glInitNames = (PFN_glInitNames)GetProcAddress(mod, "glInitNames");
    if (!g_real.glInitNames && getProcFn) g_real.glInitNames = (PFN_glInitNames)getProcFn("glInitNames");
    g_real.glInterleavedArrays = (PFN_glInterleavedArrays)GetProcAddress(mod, "glInterleavedArrays");
    if (!g_real.glInterleavedArrays && getProcFn) g_real.glInterleavedArrays = (PFN_glInterleavedArrays)getProcFn("glInterleavedArrays");
    g_real.glIsEnabled = (PFN_glIsEnabled)GetProcAddress(mod, "glIsEnabled");
    if (!g_real.glIsEnabled && getProcFn) g_real.glIsEnabled = (PFN_glIsEnabled)getProcFn("glIsEnabled");
    g_real.glIsList = (PFN_glIsList)GetProcAddress(mod, "glIsList");
    if (!g_real.glIsList && getProcFn) g_real.glIsList = (PFN_glIsList)getProcFn("glIsList");
    g_real.glIsTexture = (PFN_glIsTexture)GetProcAddress(mod, "glIsTexture");
    if (!g_real.glIsTexture && getProcFn) g_real.glIsTexture = (PFN_glIsTexture)getProcFn("glIsTexture");
    g_real.glLightModelf = (PFN_glLightModelf)GetProcAddress(mod, "glLightModelf");
    if (!g_real.glLightModelf && getProcFn) g_real.glLightModelf = (PFN_glLightModelf)getProcFn("glLightModelf");
    g_real.glLightModelfv = (PFN_glLightModelfv)GetProcAddress(mod, "glLightModelfv");
    if (!g_real.glLightModelfv && getProcFn) g_real.glLightModelfv = (PFN_glLightModelfv)getProcFn("glLightModelfv");
    g_real.glLightModeli = (PFN_glLightModeli)GetProcAddress(mod, "glLightModeli");
    if (!g_real.glLightModeli && getProcFn) g_real.glLightModeli = (PFN_glLightModeli)getProcFn("glLightModeli");
    g_real.glLightModeliv = (PFN_glLightModeliv)GetProcAddress(mod, "glLightModeliv");
    if (!g_real.glLightModeliv && getProcFn) g_real.glLightModeliv = (PFN_glLightModeliv)getProcFn("glLightModeliv");
    g_real.glLightf = (PFN_glLightf)GetProcAddress(mod, "glLightf");
    if (!g_real.glLightf && getProcFn) g_real.glLightf = (PFN_glLightf)getProcFn("glLightf");
    g_real.glLightfv = (PFN_glLightfv)GetProcAddress(mod, "glLightfv");
    if (!g_real.glLightfv && getProcFn) g_real.glLightfv = (PFN_glLightfv)getProcFn("glLightfv");
    g_real.glLighti = (PFN_glLighti)GetProcAddress(mod, "glLighti");
    if (!g_real.glLighti && getProcFn) g_real.glLighti = (PFN_glLighti)getProcFn("glLighti");
    g_real.glLightiv = (PFN_glLightiv)GetProcAddress(mod, "glLightiv");
    if (!g_real.glLightiv && getProcFn) g_real.glLightiv = (PFN_glLightiv)getProcFn("glLightiv");
    g_real.glLineStipple = (PFN_glLineStipple)GetProcAddress(mod, "glLineStipple");
    if (!g_real.glLineStipple && getProcFn) g_real.glLineStipple = (PFN_glLineStipple)getProcFn("glLineStipple");
    g_real.glListBase = (PFN_glListBase)GetProcAddress(mod, "glListBase");
    if (!g_real.glListBase && getProcFn) g_real.glListBase = (PFN_glListBase)getProcFn("glListBase");
    g_real.glLoadMatrixd = (PFN_glLoadMatrixd)GetProcAddress(mod, "glLoadMatrixd");
    if (!g_real.glLoadMatrixd && getProcFn) g_real.glLoadMatrixd = (PFN_glLoadMatrixd)getProcFn("glLoadMatrixd");
    g_real.glLoadMatrixf = (PFN_glLoadMatrixf)GetProcAddress(mod, "glLoadMatrixf");
    if (!g_real.glLoadMatrixf && getProcFn) g_real.glLoadMatrixf = (PFN_glLoadMatrixf)getProcFn("glLoadMatrixf");
    g_real.glLoadName = (PFN_glLoadName)GetProcAddress(mod, "glLoadName");
    if (!g_real.glLoadName && getProcFn) g_real.glLoadName = (PFN_glLoadName)getProcFn("glLoadName");
    g_real.glLogicOp = (PFN_glLogicOp)GetProcAddress(mod, "glLogicOp");
    if (!g_real.glLogicOp && getProcFn) g_real.glLogicOp = (PFN_glLogicOp)getProcFn("glLogicOp");
    g_real.glMap1d = (PFN_glMap1d)GetProcAddress(mod, "glMap1d");
    if (!g_real.glMap1d && getProcFn) g_real.glMap1d = (PFN_glMap1d)getProcFn("glMap1d");
    g_real.glMap1f = (PFN_glMap1f)GetProcAddress(mod, "glMap1f");
    if (!g_real.glMap1f && getProcFn) g_real.glMap1f = (PFN_glMap1f)getProcFn("glMap1f");
    g_real.glMap2d = (PFN_glMap2d)GetProcAddress(mod, "glMap2d");
    if (!g_real.glMap2d && getProcFn) g_real.glMap2d = (PFN_glMap2d)getProcFn("glMap2d");
    g_real.glMap2f = (PFN_glMap2f)GetProcAddress(mod, "glMap2f");
    if (!g_real.glMap2f && getProcFn) g_real.glMap2f = (PFN_glMap2f)getProcFn("glMap2f");
    g_real.glMapGrid1d = (PFN_glMapGrid1d)GetProcAddress(mod, "glMapGrid1d");
    if (!g_real.glMapGrid1d && getProcFn) g_real.glMapGrid1d = (PFN_glMapGrid1d)getProcFn("glMapGrid1d");
    g_real.glMapGrid1f = (PFN_glMapGrid1f)GetProcAddress(mod, "glMapGrid1f");
    if (!g_real.glMapGrid1f && getProcFn) g_real.glMapGrid1f = (PFN_glMapGrid1f)getProcFn("glMapGrid1f");
    g_real.glMapGrid2d = (PFN_glMapGrid2d)GetProcAddress(mod, "glMapGrid2d");
    if (!g_real.glMapGrid2d && getProcFn) g_real.glMapGrid2d = (PFN_glMapGrid2d)getProcFn("glMapGrid2d");
    g_real.glMapGrid2f = (PFN_glMapGrid2f)GetProcAddress(mod, "glMapGrid2f");
    if (!g_real.glMapGrid2f && getProcFn) g_real.glMapGrid2f = (PFN_glMapGrid2f)getProcFn("glMapGrid2f");
    g_real.glMaterialf = (PFN_glMaterialf)GetProcAddress(mod, "glMaterialf");
    if (!g_real.glMaterialf && getProcFn) g_real.glMaterialf = (PFN_glMaterialf)getProcFn("glMaterialf");
    g_real.glMaterialfv = (PFN_glMaterialfv)GetProcAddress(mod, "glMaterialfv");
    if (!g_real.glMaterialfv && getProcFn) g_real.glMaterialfv = (PFN_glMaterialfv)getProcFn("glMaterialfv");
    g_real.glMateriali = (PFN_glMateriali)GetProcAddress(mod, "glMateriali");
    if (!g_real.glMateriali && getProcFn) g_real.glMateriali = (PFN_glMateriali)getProcFn("glMateriali");
    g_real.glMaterialiv = (PFN_glMaterialiv)GetProcAddress(mod, "glMaterialiv");
    if (!g_real.glMaterialiv && getProcFn) g_real.glMaterialiv = (PFN_glMaterialiv)getProcFn("glMaterialiv");
    g_real.glMultMatrixd = (PFN_glMultMatrixd)GetProcAddress(mod, "glMultMatrixd");
    if (!g_real.glMultMatrixd && getProcFn) g_real.glMultMatrixd = (PFN_glMultMatrixd)getProcFn("glMultMatrixd");
    g_real.glMultMatrixf = (PFN_glMultMatrixf)GetProcAddress(mod, "glMultMatrixf");
    if (!g_real.glMultMatrixf && getProcFn) g_real.glMultMatrixf = (PFN_glMultMatrixf)getProcFn("glMultMatrixf");
    g_real.glNewList = (PFN_glNewList)GetProcAddress(mod, "glNewList");
    if (!g_real.glNewList && getProcFn) g_real.glNewList = (PFN_glNewList)getProcFn("glNewList");
    g_real.glNormal3b = (PFN_glNormal3b)GetProcAddress(mod, "glNormal3b");
    if (!g_real.glNormal3b && getProcFn) g_real.glNormal3b = (PFN_glNormal3b)getProcFn("glNormal3b");
    g_real.glNormal3bv = (PFN_glNormal3bv)GetProcAddress(mod, "glNormal3bv");
    if (!g_real.glNormal3bv && getProcFn) g_real.glNormal3bv = (PFN_glNormal3bv)getProcFn("glNormal3bv");
    g_real.glNormal3d = (PFN_glNormal3d)GetProcAddress(mod, "glNormal3d");
    if (!g_real.glNormal3d && getProcFn) g_real.glNormal3d = (PFN_glNormal3d)getProcFn("glNormal3d");
    g_real.glNormal3dv = (PFN_glNormal3dv)GetProcAddress(mod, "glNormal3dv");
    if (!g_real.glNormal3dv && getProcFn) g_real.glNormal3dv = (PFN_glNormal3dv)getProcFn("glNormal3dv");
    g_real.glNormal3fv = (PFN_glNormal3fv)GetProcAddress(mod, "glNormal3fv");
    if (!g_real.glNormal3fv && getProcFn) g_real.glNormal3fv = (PFN_glNormal3fv)getProcFn("glNormal3fv");
    g_real.glNormal3i = (PFN_glNormal3i)GetProcAddress(mod, "glNormal3i");
    if (!g_real.glNormal3i && getProcFn) g_real.glNormal3i = (PFN_glNormal3i)getProcFn("glNormal3i");
    g_real.glNormal3iv = (PFN_glNormal3iv)GetProcAddress(mod, "glNormal3iv");
    if (!g_real.glNormal3iv && getProcFn) g_real.glNormal3iv = (PFN_glNormal3iv)getProcFn("glNormal3iv");
    g_real.glNormal3s = (PFN_glNormal3s)GetProcAddress(mod, "glNormal3s");
    if (!g_real.glNormal3s && getProcFn) g_real.glNormal3s = (PFN_glNormal3s)getProcFn("glNormal3s");
    g_real.glNormal3sv = (PFN_glNormal3sv)GetProcAddress(mod, "glNormal3sv");
    if (!g_real.glNormal3sv && getProcFn) g_real.glNormal3sv = (PFN_glNormal3sv)getProcFn("glNormal3sv");
    g_real.glPassThrough = (PFN_glPassThrough)GetProcAddress(mod, "glPassThrough");
    if (!g_real.glPassThrough && getProcFn) g_real.glPassThrough = (PFN_glPassThrough)getProcFn("glPassThrough");
    g_real.glPixelMapfv = (PFN_glPixelMapfv)GetProcAddress(mod, "glPixelMapfv");
    if (!g_real.glPixelMapfv && getProcFn) g_real.glPixelMapfv = (PFN_glPixelMapfv)getProcFn("glPixelMapfv");
    g_real.glPixelMapuiv = (PFN_glPixelMapuiv)GetProcAddress(mod, "glPixelMapuiv");
    if (!g_real.glPixelMapuiv && getProcFn) g_real.glPixelMapuiv = (PFN_glPixelMapuiv)getProcFn("glPixelMapuiv");
    g_real.glPixelMapusv = (PFN_glPixelMapusv)GetProcAddress(mod, "glPixelMapusv");
    if (!g_real.glPixelMapusv && getProcFn) g_real.glPixelMapusv = (PFN_glPixelMapusv)getProcFn("glPixelMapusv");
    g_real.glPixelStoref = (PFN_glPixelStoref)GetProcAddress(mod, "glPixelStoref");
    if (!g_real.glPixelStoref && getProcFn) g_real.glPixelStoref = (PFN_glPixelStoref)getProcFn("glPixelStoref");
    g_real.glPixelTransferf = (PFN_glPixelTransferf)GetProcAddress(mod, "glPixelTransferf");
    if (!g_real.glPixelTransferf && getProcFn) g_real.glPixelTransferf = (PFN_glPixelTransferf)getProcFn("glPixelTransferf");
    g_real.glPixelTransferi = (PFN_glPixelTransferi)GetProcAddress(mod, "glPixelTransferi");
    if (!g_real.glPixelTransferi && getProcFn) g_real.glPixelTransferi = (PFN_glPixelTransferi)getProcFn("glPixelTransferi");
    g_real.glPixelZoom = (PFN_glPixelZoom)GetProcAddress(mod, "glPixelZoom");
    if (!g_real.glPixelZoom && getProcFn) g_real.glPixelZoom = (PFN_glPixelZoom)getProcFn("glPixelZoom");
    g_real.glPolygonOffset = (PFN_glPolygonOffset)GetProcAddress(mod, "glPolygonOffset");
    if (!g_real.glPolygonOffset && getProcFn) g_real.glPolygonOffset = (PFN_glPolygonOffset)getProcFn("glPolygonOffset");
    g_real.glPolygonStipple = (PFN_glPolygonStipple)GetProcAddress(mod, "glPolygonStipple");
    if (!g_real.glPolygonStipple && getProcFn) g_real.glPolygonStipple = (PFN_glPolygonStipple)getProcFn("glPolygonStipple");
    g_real.glPopAttrib = (PFN_glPopAttrib)GetProcAddress(mod, "glPopAttrib");
    if (!g_real.glPopAttrib && getProcFn) g_real.glPopAttrib = (PFN_glPopAttrib)getProcFn("glPopAttrib");
    g_real.glPopClientAttrib = (PFN_glPopClientAttrib)GetProcAddress(mod, "glPopClientAttrib");
    if (!g_real.glPopClientAttrib && getProcFn) g_real.glPopClientAttrib = (PFN_glPopClientAttrib)getProcFn("glPopClientAttrib");
    g_real.glPopName = (PFN_glPopName)GetProcAddress(mod, "glPopName");
    if (!g_real.glPopName && getProcFn) g_real.glPopName = (PFN_glPopName)getProcFn("glPopName");
    g_real.glPrioritizeTextures = (PFN_glPrioritizeTextures)GetProcAddress(mod, "glPrioritizeTextures");
    if (!g_real.glPrioritizeTextures && getProcFn) g_real.glPrioritizeTextures = (PFN_glPrioritizeTextures)getProcFn("glPrioritizeTextures");
    g_real.glPushAttrib = (PFN_glPushAttrib)GetProcAddress(mod, "glPushAttrib");
    if (!g_real.glPushAttrib && getProcFn) g_real.glPushAttrib = (PFN_glPushAttrib)getProcFn("glPushAttrib");
    g_real.glPushClientAttrib = (PFN_glPushClientAttrib)GetProcAddress(mod, "glPushClientAttrib");
    if (!g_real.glPushClientAttrib && getProcFn) g_real.glPushClientAttrib = (PFN_glPushClientAttrib)getProcFn("glPushClientAttrib");
    g_real.glPushName = (PFN_glPushName)GetProcAddress(mod, "glPushName");
    if (!g_real.glPushName && getProcFn) g_real.glPushName = (PFN_glPushName)getProcFn("glPushName");
    g_real.glRasterPos2d = (PFN_glRasterPos2d)GetProcAddress(mod, "glRasterPos2d");
    if (!g_real.glRasterPos2d && getProcFn) g_real.glRasterPos2d = (PFN_glRasterPos2d)getProcFn("glRasterPos2d");
    g_real.glRasterPos2dv = (PFN_glRasterPos2dv)GetProcAddress(mod, "glRasterPos2dv");
    if (!g_real.glRasterPos2dv && getProcFn) g_real.glRasterPos2dv = (PFN_glRasterPos2dv)getProcFn("glRasterPos2dv");
    g_real.glRasterPos2f = (PFN_glRasterPos2f)GetProcAddress(mod, "glRasterPos2f");
    if (!g_real.glRasterPos2f && getProcFn) g_real.glRasterPos2f = (PFN_glRasterPos2f)getProcFn("glRasterPos2f");
    g_real.glRasterPos2fv = (PFN_glRasterPos2fv)GetProcAddress(mod, "glRasterPos2fv");
    if (!g_real.glRasterPos2fv && getProcFn) g_real.glRasterPos2fv = (PFN_glRasterPos2fv)getProcFn("glRasterPos2fv");
    g_real.glRasterPos2i = (PFN_glRasterPos2i)GetProcAddress(mod, "glRasterPos2i");
    if (!g_real.glRasterPos2i && getProcFn) g_real.glRasterPos2i = (PFN_glRasterPos2i)getProcFn("glRasterPos2i");
    g_real.glRasterPos2iv = (PFN_glRasterPos2iv)GetProcAddress(mod, "glRasterPos2iv");
    if (!g_real.glRasterPos2iv && getProcFn) g_real.glRasterPos2iv = (PFN_glRasterPos2iv)getProcFn("glRasterPos2iv");
    g_real.glRasterPos2s = (PFN_glRasterPos2s)GetProcAddress(mod, "glRasterPos2s");
    if (!g_real.glRasterPos2s && getProcFn) g_real.glRasterPos2s = (PFN_glRasterPos2s)getProcFn("glRasterPos2s");
    g_real.glRasterPos2sv = (PFN_glRasterPos2sv)GetProcAddress(mod, "glRasterPos2sv");
    if (!g_real.glRasterPos2sv && getProcFn) g_real.glRasterPos2sv = (PFN_glRasterPos2sv)getProcFn("glRasterPos2sv");
    g_real.glRasterPos3d = (PFN_glRasterPos3d)GetProcAddress(mod, "glRasterPos3d");
    if (!g_real.glRasterPos3d && getProcFn) g_real.glRasterPos3d = (PFN_glRasterPos3d)getProcFn("glRasterPos3d");
    g_real.glRasterPos3dv = (PFN_glRasterPos3dv)GetProcAddress(mod, "glRasterPos3dv");
    if (!g_real.glRasterPos3dv && getProcFn) g_real.glRasterPos3dv = (PFN_glRasterPos3dv)getProcFn("glRasterPos3dv");
    g_real.glRasterPos3f = (PFN_glRasterPos3f)GetProcAddress(mod, "glRasterPos3f");
    if (!g_real.glRasterPos3f && getProcFn) g_real.glRasterPos3f = (PFN_glRasterPos3f)getProcFn("glRasterPos3f");
    g_real.glRasterPos3fv = (PFN_glRasterPos3fv)GetProcAddress(mod, "glRasterPos3fv");
    if (!g_real.glRasterPos3fv && getProcFn) g_real.glRasterPos3fv = (PFN_glRasterPos3fv)getProcFn("glRasterPos3fv");
    g_real.glRasterPos3i = (PFN_glRasterPos3i)GetProcAddress(mod, "glRasterPos3i");
    if (!g_real.glRasterPos3i && getProcFn) g_real.glRasterPos3i = (PFN_glRasterPos3i)getProcFn("glRasterPos3i");
    g_real.glRasterPos3iv = (PFN_glRasterPos3iv)GetProcAddress(mod, "glRasterPos3iv");
    if (!g_real.glRasterPos3iv && getProcFn) g_real.glRasterPos3iv = (PFN_glRasterPos3iv)getProcFn("glRasterPos3iv");
    g_real.glRasterPos3s = (PFN_glRasterPos3s)GetProcAddress(mod, "glRasterPos3s");
    if (!g_real.glRasterPos3s && getProcFn) g_real.glRasterPos3s = (PFN_glRasterPos3s)getProcFn("glRasterPos3s");
    g_real.glRasterPos3sv = (PFN_glRasterPos3sv)GetProcAddress(mod, "glRasterPos3sv");
    if (!g_real.glRasterPos3sv && getProcFn) g_real.glRasterPos3sv = (PFN_glRasterPos3sv)getProcFn("glRasterPos3sv");
    g_real.glRasterPos4d = (PFN_glRasterPos4d)GetProcAddress(mod, "glRasterPos4d");
    if (!g_real.glRasterPos4d && getProcFn) g_real.glRasterPos4d = (PFN_glRasterPos4d)getProcFn("glRasterPos4d");
    g_real.glRasterPos4dv = (PFN_glRasterPos4dv)GetProcAddress(mod, "glRasterPos4dv");
    if (!g_real.glRasterPos4dv && getProcFn) g_real.glRasterPos4dv = (PFN_glRasterPos4dv)getProcFn("glRasterPos4dv");
    g_real.glRasterPos4f = (PFN_glRasterPos4f)GetProcAddress(mod, "glRasterPos4f");
    if (!g_real.glRasterPos4f && getProcFn) g_real.glRasterPos4f = (PFN_glRasterPos4f)getProcFn("glRasterPos4f");
    g_real.glRasterPos4fv = (PFN_glRasterPos4fv)GetProcAddress(mod, "glRasterPos4fv");
    if (!g_real.glRasterPos4fv && getProcFn) g_real.glRasterPos4fv = (PFN_glRasterPos4fv)getProcFn("glRasterPos4fv");
    g_real.glRasterPos4i = (PFN_glRasterPos4i)GetProcAddress(mod, "glRasterPos4i");
    if (!g_real.glRasterPos4i && getProcFn) g_real.glRasterPos4i = (PFN_glRasterPos4i)getProcFn("glRasterPos4i");
    g_real.glRasterPos4iv = (PFN_glRasterPos4iv)GetProcAddress(mod, "glRasterPos4iv");
    if (!g_real.glRasterPos4iv && getProcFn) g_real.glRasterPos4iv = (PFN_glRasterPos4iv)getProcFn("glRasterPos4iv");
    g_real.glRasterPos4s = (PFN_glRasterPos4s)GetProcAddress(mod, "glRasterPos4s");
    if (!g_real.glRasterPos4s && getProcFn) g_real.glRasterPos4s = (PFN_glRasterPos4s)getProcFn("glRasterPos4s");
    g_real.glRasterPos4sv = (PFN_glRasterPos4sv)GetProcAddress(mod, "glRasterPos4sv");
    if (!g_real.glRasterPos4sv && getProcFn) g_real.glRasterPos4sv = (PFN_glRasterPos4sv)getProcFn("glRasterPos4sv");
    g_real.glReadBuffer = (PFN_glReadBuffer)GetProcAddress(mod, "glReadBuffer");
    if (!g_real.glReadBuffer && getProcFn) g_real.glReadBuffer = (PFN_glReadBuffer)getProcFn("glReadBuffer");
    g_real.glReadPixels = (PFN_glReadPixels)GetProcAddress(mod, "glReadPixels");
    if (!g_real.glReadPixels && getProcFn) g_real.glReadPixels = (PFN_glReadPixels)getProcFn("glReadPixels");
    g_real.glRectd = (PFN_glRectd)GetProcAddress(mod, "glRectd");
    if (!g_real.glRectd && getProcFn) g_real.glRectd = (PFN_glRectd)getProcFn("glRectd");
    g_real.glRectdv = (PFN_glRectdv)GetProcAddress(mod, "glRectdv");
    if (!g_real.glRectdv && getProcFn) g_real.glRectdv = (PFN_glRectdv)getProcFn("glRectdv");
    g_real.glRectf = (PFN_glRectf)GetProcAddress(mod, "glRectf");
    if (!g_real.glRectf && getProcFn) g_real.glRectf = (PFN_glRectf)getProcFn("glRectf");
    g_real.glRectfv = (PFN_glRectfv)GetProcAddress(mod, "glRectfv");
    if (!g_real.glRectfv && getProcFn) g_real.glRectfv = (PFN_glRectfv)getProcFn("glRectfv");
    g_real.glRecti = (PFN_glRecti)GetProcAddress(mod, "glRecti");
    if (!g_real.glRecti && getProcFn) g_real.glRecti = (PFN_glRecti)getProcFn("glRecti");
    g_real.glRectiv = (PFN_glRectiv)GetProcAddress(mod, "glRectiv");
    if (!g_real.glRectiv && getProcFn) g_real.glRectiv = (PFN_glRectiv)getProcFn("glRectiv");
    g_real.glRects = (PFN_glRects)GetProcAddress(mod, "glRects");
    if (!g_real.glRects && getProcFn) g_real.glRects = (PFN_glRects)getProcFn("glRects");
    g_real.glRectsv = (PFN_glRectsv)GetProcAddress(mod, "glRectsv");
    if (!g_real.glRectsv && getProcFn) g_real.glRectsv = (PFN_glRectsv)getProcFn("glRectsv");
    g_real.glRenderMode = (PFN_glRenderMode)GetProcAddress(mod, "glRenderMode");
    if (!g_real.glRenderMode && getProcFn) g_real.glRenderMode = (PFN_glRenderMode)getProcFn("glRenderMode");
    g_real.glRotated = (PFN_glRotated)GetProcAddress(mod, "glRotated");
    if (!g_real.glRotated && getProcFn) g_real.glRotated = (PFN_glRotated)getProcFn("glRotated");
    g_real.glScaled = (PFN_glScaled)GetProcAddress(mod, "glScaled");
    if (!g_real.glScaled && getProcFn) g_real.glScaled = (PFN_glScaled)getProcFn("glScaled");
    g_real.glSelectBuffer = (PFN_glSelectBuffer)GetProcAddress(mod, "glSelectBuffer");
    if (!g_real.glSelectBuffer && getProcFn) g_real.glSelectBuffer = (PFN_glSelectBuffer)getProcFn("glSelectBuffer");
    g_real.glShadeModel = (PFN_glShadeModel)GetProcAddress(mod, "glShadeModel");
    if (!g_real.glShadeModel && getProcFn) g_real.glShadeModel = (PFN_glShadeModel)getProcFn("glShadeModel");
    g_real.glStencilFunc = (PFN_glStencilFunc)GetProcAddress(mod, "glStencilFunc");
    if (!g_real.glStencilFunc && getProcFn) g_real.glStencilFunc = (PFN_glStencilFunc)getProcFn("glStencilFunc");
    g_real.glStencilMask = (PFN_glStencilMask)GetProcAddress(mod, "glStencilMask");
    if (!g_real.glStencilMask && getProcFn) g_real.glStencilMask = (PFN_glStencilMask)getProcFn("glStencilMask");
    g_real.glStencilOp = (PFN_glStencilOp)GetProcAddress(mod, "glStencilOp");
    if (!g_real.glStencilOp && getProcFn) g_real.glStencilOp = (PFN_glStencilOp)getProcFn("glStencilOp");
    g_real.glTexCoord1d = (PFN_glTexCoord1d)GetProcAddress(mod, "glTexCoord1d");
    if (!g_real.glTexCoord1d && getProcFn) g_real.glTexCoord1d = (PFN_glTexCoord1d)getProcFn("glTexCoord1d");
    g_real.glTexCoord1dv = (PFN_glTexCoord1dv)GetProcAddress(mod, "glTexCoord1dv");
    if (!g_real.glTexCoord1dv && getProcFn) g_real.glTexCoord1dv = (PFN_glTexCoord1dv)getProcFn("glTexCoord1dv");
    g_real.glTexCoord1f = (PFN_glTexCoord1f)GetProcAddress(mod, "glTexCoord1f");
    if (!g_real.glTexCoord1f && getProcFn) g_real.glTexCoord1f = (PFN_glTexCoord1f)getProcFn("glTexCoord1f");
    g_real.glTexCoord1fv = (PFN_glTexCoord1fv)GetProcAddress(mod, "glTexCoord1fv");
    if (!g_real.glTexCoord1fv && getProcFn) g_real.glTexCoord1fv = (PFN_glTexCoord1fv)getProcFn("glTexCoord1fv");
    g_real.glTexCoord1i = (PFN_glTexCoord1i)GetProcAddress(mod, "glTexCoord1i");
    if (!g_real.glTexCoord1i && getProcFn) g_real.glTexCoord1i = (PFN_glTexCoord1i)getProcFn("glTexCoord1i");
    g_real.glTexCoord1iv = (PFN_glTexCoord1iv)GetProcAddress(mod, "glTexCoord1iv");
    if (!g_real.glTexCoord1iv && getProcFn) g_real.glTexCoord1iv = (PFN_glTexCoord1iv)getProcFn("glTexCoord1iv");
    g_real.glTexCoord1s = (PFN_glTexCoord1s)GetProcAddress(mod, "glTexCoord1s");
    if (!g_real.glTexCoord1s && getProcFn) g_real.glTexCoord1s = (PFN_glTexCoord1s)getProcFn("glTexCoord1s");
    g_real.glTexCoord1sv = (PFN_glTexCoord1sv)GetProcAddress(mod, "glTexCoord1sv");
    if (!g_real.glTexCoord1sv && getProcFn) g_real.glTexCoord1sv = (PFN_glTexCoord1sv)getProcFn("glTexCoord1sv");
    g_real.glTexCoord2d = (PFN_glTexCoord2d)GetProcAddress(mod, "glTexCoord2d");
    if (!g_real.glTexCoord2d && getProcFn) g_real.glTexCoord2d = (PFN_glTexCoord2d)getProcFn("glTexCoord2d");
    g_real.glTexCoord2dv = (PFN_glTexCoord2dv)GetProcAddress(mod, "glTexCoord2dv");
    if (!g_real.glTexCoord2dv && getProcFn) g_real.glTexCoord2dv = (PFN_glTexCoord2dv)getProcFn("glTexCoord2dv");
    g_real.glTexCoord2fv = (PFN_glTexCoord2fv)GetProcAddress(mod, "glTexCoord2fv");
    if (!g_real.glTexCoord2fv && getProcFn) g_real.glTexCoord2fv = (PFN_glTexCoord2fv)getProcFn("glTexCoord2fv");
    g_real.glTexCoord2i = (PFN_glTexCoord2i)GetProcAddress(mod, "glTexCoord2i");
    if (!g_real.glTexCoord2i && getProcFn) g_real.glTexCoord2i = (PFN_glTexCoord2i)getProcFn("glTexCoord2i");
    g_real.glTexCoord2iv = (PFN_glTexCoord2iv)GetProcAddress(mod, "glTexCoord2iv");
    if (!g_real.glTexCoord2iv && getProcFn) g_real.glTexCoord2iv = (PFN_glTexCoord2iv)getProcFn("glTexCoord2iv");
    g_real.glTexCoord2s = (PFN_glTexCoord2s)GetProcAddress(mod, "glTexCoord2s");
    if (!g_real.glTexCoord2s && getProcFn) g_real.glTexCoord2s = (PFN_glTexCoord2s)getProcFn("glTexCoord2s");
    g_real.glTexCoord2sv = (PFN_glTexCoord2sv)GetProcAddress(mod, "glTexCoord2sv");
    if (!g_real.glTexCoord2sv && getProcFn) g_real.glTexCoord2sv = (PFN_glTexCoord2sv)getProcFn("glTexCoord2sv");
    g_real.glTexCoord3d = (PFN_glTexCoord3d)GetProcAddress(mod, "glTexCoord3d");
    if (!g_real.glTexCoord3d && getProcFn) g_real.glTexCoord3d = (PFN_glTexCoord3d)getProcFn("glTexCoord3d");
    g_real.glTexCoord3dv = (PFN_glTexCoord3dv)GetProcAddress(mod, "glTexCoord3dv");
    if (!g_real.glTexCoord3dv && getProcFn) g_real.glTexCoord3dv = (PFN_glTexCoord3dv)getProcFn("glTexCoord3dv");
    g_real.glTexCoord3f = (PFN_glTexCoord3f)GetProcAddress(mod, "glTexCoord3f");
    if (!g_real.glTexCoord3f && getProcFn) g_real.glTexCoord3f = (PFN_glTexCoord3f)getProcFn("glTexCoord3f");
    g_real.glTexCoord3fv = (PFN_glTexCoord3fv)GetProcAddress(mod, "glTexCoord3fv");
    if (!g_real.glTexCoord3fv && getProcFn) g_real.glTexCoord3fv = (PFN_glTexCoord3fv)getProcFn("glTexCoord3fv");
    g_real.glTexCoord3i = (PFN_glTexCoord3i)GetProcAddress(mod, "glTexCoord3i");
    if (!g_real.glTexCoord3i && getProcFn) g_real.glTexCoord3i = (PFN_glTexCoord3i)getProcFn("glTexCoord3i");
    g_real.glTexCoord3iv = (PFN_glTexCoord3iv)GetProcAddress(mod, "glTexCoord3iv");
    if (!g_real.glTexCoord3iv && getProcFn) g_real.glTexCoord3iv = (PFN_glTexCoord3iv)getProcFn("glTexCoord3iv");
    g_real.glTexCoord3s = (PFN_glTexCoord3s)GetProcAddress(mod, "glTexCoord3s");
    if (!g_real.glTexCoord3s && getProcFn) g_real.glTexCoord3s = (PFN_glTexCoord3s)getProcFn("glTexCoord3s");
    g_real.glTexCoord3sv = (PFN_glTexCoord3sv)GetProcAddress(mod, "glTexCoord3sv");
    if (!g_real.glTexCoord3sv && getProcFn) g_real.glTexCoord3sv = (PFN_glTexCoord3sv)getProcFn("glTexCoord3sv");
    g_real.glTexCoord4d = (PFN_glTexCoord4d)GetProcAddress(mod, "glTexCoord4d");
    if (!g_real.glTexCoord4d && getProcFn) g_real.glTexCoord4d = (PFN_glTexCoord4d)getProcFn("glTexCoord4d");
    g_real.glTexCoord4dv = (PFN_glTexCoord4dv)GetProcAddress(mod, "glTexCoord4dv");
    if (!g_real.glTexCoord4dv && getProcFn) g_real.glTexCoord4dv = (PFN_glTexCoord4dv)getProcFn("glTexCoord4dv");
    g_real.glTexCoord4f = (PFN_glTexCoord4f)GetProcAddress(mod, "glTexCoord4f");
    if (!g_real.glTexCoord4f && getProcFn) g_real.glTexCoord4f = (PFN_glTexCoord4f)getProcFn("glTexCoord4f");
    g_real.glTexCoord4fv = (PFN_glTexCoord4fv)GetProcAddress(mod, "glTexCoord4fv");
    if (!g_real.glTexCoord4fv && getProcFn) g_real.glTexCoord4fv = (PFN_glTexCoord4fv)getProcFn("glTexCoord4fv");
    g_real.glTexCoord4i = (PFN_glTexCoord4i)GetProcAddress(mod, "glTexCoord4i");
    if (!g_real.glTexCoord4i && getProcFn) g_real.glTexCoord4i = (PFN_glTexCoord4i)getProcFn("glTexCoord4i");
    g_real.glTexCoord4iv = (PFN_glTexCoord4iv)GetProcAddress(mod, "glTexCoord4iv");
    if (!g_real.glTexCoord4iv && getProcFn) g_real.glTexCoord4iv = (PFN_glTexCoord4iv)getProcFn("glTexCoord4iv");
    g_real.glTexCoord4s = (PFN_glTexCoord4s)GetProcAddress(mod, "glTexCoord4s");
    if (!g_real.glTexCoord4s && getProcFn) g_real.glTexCoord4s = (PFN_glTexCoord4s)getProcFn("glTexCoord4s");
    g_real.glTexCoord4sv = (PFN_glTexCoord4sv)GetProcAddress(mod, "glTexCoord4sv");
    if (!g_real.glTexCoord4sv && getProcFn) g_real.glTexCoord4sv = (PFN_glTexCoord4sv)getProcFn("glTexCoord4sv");
    g_real.glTexEnvf = (PFN_glTexEnvf)GetProcAddress(mod, "glTexEnvf");
    if (!g_real.glTexEnvf && getProcFn) g_real.glTexEnvf = (PFN_glTexEnvf)getProcFn("glTexEnvf");
    g_real.glTexEnvfv = (PFN_glTexEnvfv)GetProcAddress(mod, "glTexEnvfv");
    if (!g_real.glTexEnvfv && getProcFn) g_real.glTexEnvfv = (PFN_glTexEnvfv)getProcFn("glTexEnvfv");
    g_real.glTexEnvi = (PFN_glTexEnvi)GetProcAddress(mod, "glTexEnvi");
    if (!g_real.glTexEnvi && getProcFn) g_real.glTexEnvi = (PFN_glTexEnvi)getProcFn("glTexEnvi");
    g_real.glTexEnviv = (PFN_glTexEnviv)GetProcAddress(mod, "glTexEnviv");
    if (!g_real.glTexEnviv && getProcFn) g_real.glTexEnviv = (PFN_glTexEnviv)getProcFn("glTexEnviv");
    g_real.glTexGend = (PFN_glTexGend)GetProcAddress(mod, "glTexGend");
    if (!g_real.glTexGend && getProcFn) g_real.glTexGend = (PFN_glTexGend)getProcFn("glTexGend");
    g_real.glTexGendv = (PFN_glTexGendv)GetProcAddress(mod, "glTexGendv");
    if (!g_real.glTexGendv && getProcFn) g_real.glTexGendv = (PFN_glTexGendv)getProcFn("glTexGendv");
    g_real.glTexGenf = (PFN_glTexGenf)GetProcAddress(mod, "glTexGenf");
    if (!g_real.glTexGenf && getProcFn) g_real.glTexGenf = (PFN_glTexGenf)getProcFn("glTexGenf");
    g_real.glTexGenfv = (PFN_glTexGenfv)GetProcAddress(mod, "glTexGenfv");
    if (!g_real.glTexGenfv && getProcFn) g_real.glTexGenfv = (PFN_glTexGenfv)getProcFn("glTexGenfv");
    g_real.glTexGeni = (PFN_glTexGeni)GetProcAddress(mod, "glTexGeni");
    if (!g_real.glTexGeni && getProcFn) g_real.glTexGeni = (PFN_glTexGeni)getProcFn("glTexGeni");
    g_real.glTexGeniv = (PFN_glTexGeniv)GetProcAddress(mod, "glTexGeniv");
    if (!g_real.glTexGeniv && getProcFn) g_real.glTexGeniv = (PFN_glTexGeniv)getProcFn("glTexGeniv");
    g_real.glTexImage1D = (PFN_glTexImage1D)GetProcAddress(mod, "glTexImage1D");
    if (!g_real.glTexImage1D && getProcFn) g_real.glTexImage1D = (PFN_glTexImage1D)getProcFn("glTexImage1D");
    g_real.glTexParameterfv = (PFN_glTexParameterfv)GetProcAddress(mod, "glTexParameterfv");
    if (!g_real.glTexParameterfv && getProcFn) g_real.glTexParameterfv = (PFN_glTexParameterfv)getProcFn("glTexParameterfv");
    g_real.glTexParameteriv = (PFN_glTexParameteriv)GetProcAddress(mod, "glTexParameteriv");
    if (!g_real.glTexParameteriv && getProcFn) g_real.glTexParameteriv = (PFN_glTexParameteriv)getProcFn("glTexParameteriv");
    g_real.glTexSubImage1D = (PFN_glTexSubImage1D)GetProcAddress(mod, "glTexSubImage1D");
    if (!g_real.glTexSubImage1D && getProcFn) g_real.glTexSubImage1D = (PFN_glTexSubImage1D)getProcFn("glTexSubImage1D");
    g_real.glTranslated = (PFN_glTranslated)GetProcAddress(mod, "glTranslated");
    if (!g_real.glTranslated && getProcFn) g_real.glTranslated = (PFN_glTranslated)getProcFn("glTranslated");
    g_real.glVertex2d = (PFN_glVertex2d)GetProcAddress(mod, "glVertex2d");
    if (!g_real.glVertex2d && getProcFn) g_real.glVertex2d = (PFN_glVertex2d)getProcFn("glVertex2d");
    g_real.glVertex2dv = (PFN_glVertex2dv)GetProcAddress(mod, "glVertex2dv");
    if (!g_real.glVertex2dv && getProcFn) g_real.glVertex2dv = (PFN_glVertex2dv)getProcFn("glVertex2dv");
    g_real.glVertex2fv = (PFN_glVertex2fv)GetProcAddress(mod, "glVertex2fv");
    if (!g_real.glVertex2fv && getProcFn) g_real.glVertex2fv = (PFN_glVertex2fv)getProcFn("glVertex2fv");
    g_real.glVertex2i = (PFN_glVertex2i)GetProcAddress(mod, "glVertex2i");
    if (!g_real.glVertex2i && getProcFn) g_real.glVertex2i = (PFN_glVertex2i)getProcFn("glVertex2i");
    g_real.glVertex2iv = (PFN_glVertex2iv)GetProcAddress(mod, "glVertex2iv");
    if (!g_real.glVertex2iv && getProcFn) g_real.glVertex2iv = (PFN_glVertex2iv)getProcFn("glVertex2iv");
    g_real.glVertex2s = (PFN_glVertex2s)GetProcAddress(mod, "glVertex2s");
    if (!g_real.glVertex2s && getProcFn) g_real.glVertex2s = (PFN_glVertex2s)getProcFn("glVertex2s");
    g_real.glVertex2sv = (PFN_glVertex2sv)GetProcAddress(mod, "glVertex2sv");
    if (!g_real.glVertex2sv && getProcFn) g_real.glVertex2sv = (PFN_glVertex2sv)getProcFn("glVertex2sv");
    g_real.glVertex3d = (PFN_glVertex3d)GetProcAddress(mod, "glVertex3d");
    if (!g_real.glVertex3d && getProcFn) g_real.glVertex3d = (PFN_glVertex3d)getProcFn("glVertex3d");
    g_real.glVertex3dv = (PFN_glVertex3dv)GetProcAddress(mod, "glVertex3dv");
    if (!g_real.glVertex3dv && getProcFn) g_real.glVertex3dv = (PFN_glVertex3dv)getProcFn("glVertex3dv");
    g_real.glVertex3fv = (PFN_glVertex3fv)GetProcAddress(mod, "glVertex3fv");
    if (!g_real.glVertex3fv && getProcFn) g_real.glVertex3fv = (PFN_glVertex3fv)getProcFn("glVertex3fv");
    g_real.glVertex3i = (PFN_glVertex3i)GetProcAddress(mod, "glVertex3i");
    if (!g_real.glVertex3i && getProcFn) g_real.glVertex3i = (PFN_glVertex3i)getProcFn("glVertex3i");
    g_real.glVertex3iv = (PFN_glVertex3iv)GetProcAddress(mod, "glVertex3iv");
    if (!g_real.glVertex3iv && getProcFn) g_real.glVertex3iv = (PFN_glVertex3iv)getProcFn("glVertex3iv");
    g_real.glVertex3s = (PFN_glVertex3s)GetProcAddress(mod, "glVertex3s");
    if (!g_real.glVertex3s && getProcFn) g_real.glVertex3s = (PFN_glVertex3s)getProcFn("glVertex3s");
    g_real.glVertex3sv = (PFN_glVertex3sv)GetProcAddress(mod, "glVertex3sv");
    if (!g_real.glVertex3sv && getProcFn) g_real.glVertex3sv = (PFN_glVertex3sv)getProcFn("glVertex3sv");
    g_real.glVertex4d = (PFN_glVertex4d)GetProcAddress(mod, "glVertex4d");
    if (!g_real.glVertex4d && getProcFn) g_real.glVertex4d = (PFN_glVertex4d)getProcFn("glVertex4d");
    g_real.glVertex4dv = (PFN_glVertex4dv)GetProcAddress(mod, "glVertex4dv");
    if (!g_real.glVertex4dv && getProcFn) g_real.glVertex4dv = (PFN_glVertex4dv)getProcFn("glVertex4dv");
    g_real.glVertex4fv = (PFN_glVertex4fv)GetProcAddress(mod, "glVertex4fv");
    if (!g_real.glVertex4fv && getProcFn) g_real.glVertex4fv = (PFN_glVertex4fv)getProcFn("glVertex4fv");
    g_real.glVertex4i = (PFN_glVertex4i)GetProcAddress(mod, "glVertex4i");
    if (!g_real.glVertex4i && getProcFn) g_real.glVertex4i = (PFN_glVertex4i)getProcFn("glVertex4i");
    g_real.glVertex4iv = (PFN_glVertex4iv)GetProcAddress(mod, "glVertex4iv");
    if (!g_real.glVertex4iv && getProcFn) g_real.glVertex4iv = (PFN_glVertex4iv)getProcFn("glVertex4iv");
    g_real.glVertex4s = (PFN_glVertex4s)GetProcAddress(mod, "glVertex4s");
    if (!g_real.glVertex4s && getProcFn) g_real.glVertex4s = (PFN_glVertex4s)getProcFn("glVertex4s");
    g_real.glVertex4sv = (PFN_glVertex4sv)GetProcAddress(mod, "glVertex4sv");
    if (!g_real.glVertex4sv && getProcFn) g_real.glVertex4sv = (PFN_glVertex4sv)getProcFn("glVertex4sv");
    g_real.glGetShaderiv = (PFN_glGetShaderiv)GetProcAddress(mod, "glGetShaderiv");
    if (!g_real.glGetShaderiv && getProcFn) g_real.glGetShaderiv = (PFN_glGetShaderiv)getProcFn("glGetShaderiv");
    g_real.glGetProgramiv = (PFN_glGetProgramiv)GetProcAddress(mod, "glGetProgramiv");
    if (!g_real.glGetProgramiv && getProcFn) g_real.glGetProgramiv = (PFN_glGetProgramiv)getProcFn("glGetProgramiv");
    g_real.glActiveShaderProgram = (PFN_glActiveShaderProgram)GetProcAddress(mod, "glActiveShaderProgram");
    if (!g_real.glActiveShaderProgram && getProcFn) g_real.glActiveShaderProgram = (PFN_glActiveShaderProgram)getProcFn("glActiveShaderProgram");
    g_real.glBeginConditionalRender = (PFN_glBeginConditionalRender)GetProcAddress(mod, "glBeginConditionalRender");
    if (!g_real.glBeginConditionalRender && getProcFn) g_real.glBeginConditionalRender = (PFN_glBeginConditionalRender)getProcFn("glBeginConditionalRender");
    g_real.glBeginQuery = (PFN_glBeginQuery)GetProcAddress(mod, "glBeginQuery");
    if (!g_real.glBeginQuery && getProcFn) g_real.glBeginQuery = (PFN_glBeginQuery)getProcFn("glBeginQuery");
    g_real.glBeginQueryIndexed = (PFN_glBeginQueryIndexed)GetProcAddress(mod, "glBeginQueryIndexed");
    if (!g_real.glBeginQueryIndexed && getProcFn) g_real.glBeginQueryIndexed = (PFN_glBeginQueryIndexed)getProcFn("glBeginQueryIndexed");
    g_real.glBeginTransformFeedback = (PFN_glBeginTransformFeedback)GetProcAddress(mod, "glBeginTransformFeedback");
    if (!g_real.glBeginTransformFeedback && getProcFn) g_real.glBeginTransformFeedback = (PFN_glBeginTransformFeedback)getProcFn("glBeginTransformFeedback");
    g_real.glBindBufferBase = (PFN_glBindBufferBase)GetProcAddress(mod, "glBindBufferBase");
    if (!g_real.glBindBufferBase && getProcFn) g_real.glBindBufferBase = (PFN_glBindBufferBase)getProcFn("glBindBufferBase");
    g_real.glBindBufferRange = (PFN_glBindBufferRange)GetProcAddress(mod, "glBindBufferRange");
    if (!g_real.glBindBufferRange && getProcFn) g_real.glBindBufferRange = (PFN_glBindBufferRange)getProcFn("glBindBufferRange");
    g_real.glBindImageTexture = (PFN_glBindImageTexture)GetProcAddress(mod, "glBindImageTexture");
    if (!g_real.glBindImageTexture && getProcFn) g_real.glBindImageTexture = (PFN_glBindImageTexture)getProcFn("glBindImageTexture");
    g_real.glBindProgramPipeline = (PFN_glBindProgramPipeline)GetProcAddress(mod, "glBindProgramPipeline");
    if (!g_real.glBindProgramPipeline && getProcFn) g_real.glBindProgramPipeline = (PFN_glBindProgramPipeline)getProcFn("glBindProgramPipeline");
    g_real.glBindSampler = (PFN_glBindSampler)GetProcAddress(mod, "glBindSampler");
    if (!g_real.glBindSampler && getProcFn) g_real.glBindSampler = (PFN_glBindSampler)getProcFn("glBindSampler");
    g_real.glBindTextureUnit = (PFN_glBindTextureUnit)GetProcAddress(mod, "glBindTextureUnit");
    if (!g_real.glBindTextureUnit && getProcFn) g_real.glBindTextureUnit = (PFN_glBindTextureUnit)getProcFn("glBindTextureUnit");
    g_real.glBindTransformFeedback = (PFN_glBindTransformFeedback)GetProcAddress(mod, "glBindTransformFeedback");
    if (!g_real.glBindTransformFeedback && getProcFn) g_real.glBindTransformFeedback = (PFN_glBindTransformFeedback)getProcFn("glBindTransformFeedback");
    g_real.glBindVertexBuffer = (PFN_glBindVertexBuffer)GetProcAddress(mod, "glBindVertexBuffer");
    if (!g_real.glBindVertexBuffer && getProcFn) g_real.glBindVertexBuffer = (PFN_glBindVertexBuffer)getProcFn("glBindVertexBuffer");
    g_real.glBlendColor = (PFN_glBlendColor)GetProcAddress(mod, "glBlendColor");
    if (!g_real.glBlendColor && getProcFn) g_real.glBlendColor = (PFN_glBlendColor)getProcFn("glBlendColor");
    g_real.glBlendEquation = (PFN_glBlendEquation)GetProcAddress(mod, "glBlendEquation");
    if (!g_real.glBlendEquation && getProcFn) g_real.glBlendEquation = (PFN_glBlendEquation)getProcFn("glBlendEquation");
    g_real.glBlendEquationSeparate = (PFN_glBlendEquationSeparate)GetProcAddress(mod, "glBlendEquationSeparate");
    if (!g_real.glBlendEquationSeparate && getProcFn) g_real.glBlendEquationSeparate = (PFN_glBlendEquationSeparate)getProcFn("glBlendEquationSeparate");
    g_real.glBlendEquationSeparatei = (PFN_glBlendEquationSeparatei)GetProcAddress(mod, "glBlendEquationSeparatei");
    if (!g_real.glBlendEquationSeparatei && getProcFn) g_real.glBlendEquationSeparatei = (PFN_glBlendEquationSeparatei)getProcFn("glBlendEquationSeparatei");
    g_real.glBlendEquationi = (PFN_glBlendEquationi)GetProcAddress(mod, "glBlendEquationi");
    if (!g_real.glBlendEquationi && getProcFn) g_real.glBlendEquationi = (PFN_glBlendEquationi)getProcFn("glBlendEquationi");
    g_real.glBlendFuncSeparate = (PFN_glBlendFuncSeparate)GetProcAddress(mod, "glBlendFuncSeparate");
    if (!g_real.glBlendFuncSeparate && getProcFn) g_real.glBlendFuncSeparate = (PFN_glBlendFuncSeparate)getProcFn("glBlendFuncSeparate");
    g_real.glBlendFuncSeparatei = (PFN_glBlendFuncSeparatei)GetProcAddress(mod, "glBlendFuncSeparatei");
    if (!g_real.glBlendFuncSeparatei && getProcFn) g_real.glBlendFuncSeparatei = (PFN_glBlendFuncSeparatei)getProcFn("glBlendFuncSeparatei");
    g_real.glBlendFunci = (PFN_glBlendFunci)GetProcAddress(mod, "glBlendFunci");
    if (!g_real.glBlendFunci && getProcFn) g_real.glBlendFunci = (PFN_glBlendFunci)getProcFn("glBlendFunci");
    g_real.glBlitFramebuffer = (PFN_glBlitFramebuffer)GetProcAddress(mod, "glBlitFramebuffer");
    if (!g_real.glBlitFramebuffer && getProcFn) g_real.glBlitFramebuffer = (PFN_glBlitFramebuffer)getProcFn("glBlitFramebuffer");
    g_real.glBlitNamedFramebuffer = (PFN_glBlitNamedFramebuffer)GetProcAddress(mod, "glBlitNamedFramebuffer");
    if (!g_real.glBlitNamedFramebuffer && getProcFn) g_real.glBlitNamedFramebuffer = (PFN_glBlitNamedFramebuffer)getProcFn("glBlitNamedFramebuffer");
    g_real.glClampColor = (PFN_glClampColor)GetProcAddress(mod, "glClampColor");
    if (!g_real.glClampColor && getProcFn) g_real.glClampColor = (PFN_glClampColor)getProcFn("glClampColor");
    g_real.glClearBufferfi = (PFN_glClearBufferfi)GetProcAddress(mod, "glClearBufferfi");
    if (!g_real.glClearBufferfi && getProcFn) g_real.glClearBufferfi = (PFN_glClearBufferfi)getProcFn("glClearBufferfi");
    g_real.glClearDepthf = (PFN_glClearDepthf)GetProcAddress(mod, "glClearDepthf");
    if (!g_real.glClearDepthf && getProcFn) g_real.glClearDepthf = (PFN_glClearDepthf)getProcFn("glClearDepthf");
    g_real.glClearNamedFramebufferfi = (PFN_glClearNamedFramebufferfi)GetProcAddress(mod, "glClearNamedFramebufferfi");
    if (!g_real.glClearNamedFramebufferfi && getProcFn) g_real.glClearNamedFramebufferfi = (PFN_glClearNamedFramebufferfi)getProcFn("glClearNamedFramebufferfi");
    g_real.glClientActiveTexture = (PFN_glClientActiveTexture)GetProcAddress(mod, "glClientActiveTexture");
    if (!g_real.glClientActiveTexture && getProcFn) g_real.glClientActiveTexture = (PFN_glClientActiveTexture)getProcFn("glClientActiveTexture");
    g_real.glClipControl = (PFN_glClipControl)GetProcAddress(mod, "glClipControl");
    if (!g_real.glClipControl && getProcFn) g_real.glClipControl = (PFN_glClipControl)getProcFn("glClipControl");
    g_real.glColorMaski = (PFN_glColorMaski)GetProcAddress(mod, "glColorMaski");
    if (!g_real.glColorMaski && getProcFn) g_real.glColorMaski = (PFN_glColorMaski)getProcFn("glColorMaski");
    g_real.glColorP3ui = (PFN_glColorP3ui)GetProcAddress(mod, "glColorP3ui");
    if (!g_real.glColorP3ui && getProcFn) g_real.glColorP3ui = (PFN_glColorP3ui)getProcFn("glColorP3ui");
    g_real.glColorP4ui = (PFN_glColorP4ui)GetProcAddress(mod, "glColorP4ui");
    if (!g_real.glColorP4ui && getProcFn) g_real.glColorP4ui = (PFN_glColorP4ui)getProcFn("glColorP4ui");
    g_real.glCopyBufferSubData = (PFN_glCopyBufferSubData)GetProcAddress(mod, "glCopyBufferSubData");
    if (!g_real.glCopyBufferSubData && getProcFn) g_real.glCopyBufferSubData = (PFN_glCopyBufferSubData)getProcFn("glCopyBufferSubData");
    g_real.glCopyImageSubData = (PFN_glCopyImageSubData)GetProcAddress(mod, "glCopyImageSubData");
    if (!g_real.glCopyImageSubData && getProcFn) g_real.glCopyImageSubData = (PFN_glCopyImageSubData)getProcFn("glCopyImageSubData");
    g_real.glCopyNamedBufferSubData = (PFN_glCopyNamedBufferSubData)GetProcAddress(mod, "glCopyNamedBufferSubData");
    if (!g_real.glCopyNamedBufferSubData && getProcFn) g_real.glCopyNamedBufferSubData = (PFN_glCopyNamedBufferSubData)getProcFn("glCopyNamedBufferSubData");
    g_real.glCopyTexSubImage3D = (PFN_glCopyTexSubImage3D)GetProcAddress(mod, "glCopyTexSubImage3D");
    if (!g_real.glCopyTexSubImage3D && getProcFn) g_real.glCopyTexSubImage3D = (PFN_glCopyTexSubImage3D)getProcFn("glCopyTexSubImage3D");
    g_real.glCopyTextureSubImage1D = (PFN_glCopyTextureSubImage1D)GetProcAddress(mod, "glCopyTextureSubImage1D");
    if (!g_real.glCopyTextureSubImage1D && getProcFn) g_real.glCopyTextureSubImage1D = (PFN_glCopyTextureSubImage1D)getProcFn("glCopyTextureSubImage1D");
    g_real.glCopyTextureSubImage2D = (PFN_glCopyTextureSubImage2D)GetProcAddress(mod, "glCopyTextureSubImage2D");
    if (!g_real.glCopyTextureSubImage2D && getProcFn) g_real.glCopyTextureSubImage2D = (PFN_glCopyTextureSubImage2D)getProcFn("glCopyTextureSubImage2D");
    g_real.glCopyTextureSubImage3D = (PFN_glCopyTextureSubImage3D)GetProcAddress(mod, "glCopyTextureSubImage3D");
    if (!g_real.glCopyTextureSubImage3D && getProcFn) g_real.glCopyTextureSubImage3D = (PFN_glCopyTextureSubImage3D)getProcFn("glCopyTextureSubImage3D");
    g_real.glDeleteSync = (PFN_glDeleteSync)GetProcAddress(mod, "glDeleteSync");
    if (!g_real.glDeleteSync && getProcFn) g_real.glDeleteSync = (PFN_glDeleteSync)getProcFn("glDeleteSync");
    g_real.glDepthRangeIndexed = (PFN_glDepthRangeIndexed)GetProcAddress(mod, "glDepthRangeIndexed");
    if (!g_real.glDepthRangeIndexed && getProcFn) g_real.glDepthRangeIndexed = (PFN_glDepthRangeIndexed)getProcFn("glDepthRangeIndexed");
    g_real.glDepthRangef = (PFN_glDepthRangef)GetProcAddress(mod, "glDepthRangef");
    if (!g_real.glDepthRangef && getProcFn) g_real.glDepthRangef = (PFN_glDepthRangef)getProcFn("glDepthRangef");
    g_real.glDisableVertexArrayAttrib = (PFN_glDisableVertexArrayAttrib)GetProcAddress(mod, "glDisableVertexArrayAttrib");
    if (!g_real.glDisableVertexArrayAttrib && getProcFn) g_real.glDisableVertexArrayAttrib = (PFN_glDisableVertexArrayAttrib)getProcFn("glDisableVertexArrayAttrib");
    g_real.glDisablei = (PFN_glDisablei)GetProcAddress(mod, "glDisablei");
    if (!g_real.glDisablei && getProcFn) g_real.glDisablei = (PFN_glDisablei)getProcFn("glDisablei");
    g_real.glDispatchCompute = (PFN_glDispatchCompute)GetProcAddress(mod, "glDispatchCompute");
    if (!g_real.glDispatchCompute && getProcFn) g_real.glDispatchCompute = (PFN_glDispatchCompute)getProcFn("glDispatchCompute");
    g_real.glDispatchComputeIndirect = (PFN_glDispatchComputeIndirect)GetProcAddress(mod, "glDispatchComputeIndirect");
    if (!g_real.glDispatchComputeIndirect && getProcFn) g_real.glDispatchComputeIndirect = (PFN_glDispatchComputeIndirect)getProcFn("glDispatchComputeIndirect");
    g_real.glDrawArraysInstancedBaseInstance = (PFN_glDrawArraysInstancedBaseInstance)GetProcAddress(mod, "glDrawArraysInstancedBaseInstance");
    if (!g_real.glDrawArraysInstancedBaseInstance && getProcFn) g_real.glDrawArraysInstancedBaseInstance = (PFN_glDrawArraysInstancedBaseInstance)getProcFn("glDrawArraysInstancedBaseInstance");
    g_real.glDrawTransformFeedback = (PFN_glDrawTransformFeedback)GetProcAddress(mod, "glDrawTransformFeedback");
    if (!g_real.glDrawTransformFeedback && getProcFn) g_real.glDrawTransformFeedback = (PFN_glDrawTransformFeedback)getProcFn("glDrawTransformFeedback");
    g_real.glDrawTransformFeedbackInstanced = (PFN_glDrawTransformFeedbackInstanced)GetProcAddress(mod, "glDrawTransformFeedbackInstanced");
    if (!g_real.glDrawTransformFeedbackInstanced && getProcFn) g_real.glDrawTransformFeedbackInstanced = (PFN_glDrawTransformFeedbackInstanced)getProcFn("glDrawTransformFeedbackInstanced");
    g_real.glDrawTransformFeedbackStream = (PFN_glDrawTransformFeedbackStream)GetProcAddress(mod, "glDrawTransformFeedbackStream");
    if (!g_real.glDrawTransformFeedbackStream && getProcFn) g_real.glDrawTransformFeedbackStream = (PFN_glDrawTransformFeedbackStream)getProcFn("glDrawTransformFeedbackStream");
    g_real.glDrawTransformFeedbackStreamInstanced = (PFN_glDrawTransformFeedbackStreamInstanced)GetProcAddress(mod, "glDrawTransformFeedbackStreamInstanced");
    if (!g_real.glDrawTransformFeedbackStreamInstanced && getProcFn) g_real.glDrawTransformFeedbackStreamInstanced = (PFN_glDrawTransformFeedbackStreamInstanced)getProcFn("glDrawTransformFeedbackStreamInstanced");
    g_real.glEnableVertexArrayAttrib = (PFN_glEnableVertexArrayAttrib)GetProcAddress(mod, "glEnableVertexArrayAttrib");
    if (!g_real.glEnableVertexArrayAttrib && getProcFn) g_real.glEnableVertexArrayAttrib = (PFN_glEnableVertexArrayAttrib)getProcFn("glEnableVertexArrayAttrib");
    g_real.glEnablei = (PFN_glEnablei)GetProcAddress(mod, "glEnablei");
    if (!g_real.glEnablei && getProcFn) g_real.glEnablei = (PFN_glEnablei)getProcFn("glEnablei");
    g_real.glEndConditionalRender = (PFN_glEndConditionalRender)GetProcAddress(mod, "glEndConditionalRender");
    if (!g_real.glEndConditionalRender && getProcFn) g_real.glEndConditionalRender = (PFN_glEndConditionalRender)getProcFn("glEndConditionalRender");
    g_real.glEndQuery = (PFN_glEndQuery)GetProcAddress(mod, "glEndQuery");
    if (!g_real.glEndQuery && getProcFn) g_real.glEndQuery = (PFN_glEndQuery)getProcFn("glEndQuery");
    g_real.glEndQueryIndexed = (PFN_glEndQueryIndexed)GetProcAddress(mod, "glEndQueryIndexed");
    if (!g_real.glEndQueryIndexed && getProcFn) g_real.glEndQueryIndexed = (PFN_glEndQueryIndexed)getProcFn("glEndQueryIndexed");
    g_real.glEndTransformFeedback = (PFN_glEndTransformFeedback)GetProcAddress(mod, "glEndTransformFeedback");
    if (!g_real.glEndTransformFeedback && getProcFn) g_real.glEndTransformFeedback = (PFN_glEndTransformFeedback)getProcFn("glEndTransformFeedback");
    g_real.glFlushMappedBufferRange = (PFN_glFlushMappedBufferRange)GetProcAddress(mod, "glFlushMappedBufferRange");
    if (!g_real.glFlushMappedBufferRange && getProcFn) g_real.glFlushMappedBufferRange = (PFN_glFlushMappedBufferRange)getProcFn("glFlushMappedBufferRange");
    g_real.glFlushMappedNamedBufferRange = (PFN_glFlushMappedNamedBufferRange)GetProcAddress(mod, "glFlushMappedNamedBufferRange");
    if (!g_real.glFlushMappedNamedBufferRange && getProcFn) g_real.glFlushMappedNamedBufferRange = (PFN_glFlushMappedNamedBufferRange)getProcFn("glFlushMappedNamedBufferRange");
    g_real.glFogCoordd = (PFN_glFogCoordd)GetProcAddress(mod, "glFogCoordd");
    if (!g_real.glFogCoordd && getProcFn) g_real.glFogCoordd = (PFN_glFogCoordd)getProcFn("glFogCoordd");
    g_real.glFogCoordf = (PFN_glFogCoordf)GetProcAddress(mod, "glFogCoordf");
    if (!g_real.glFogCoordf && getProcFn) g_real.glFogCoordf = (PFN_glFogCoordf)getProcFn("glFogCoordf");
    g_real.glFramebufferParameteri = (PFN_glFramebufferParameteri)GetProcAddress(mod, "glFramebufferParameteri");
    if (!g_real.glFramebufferParameteri && getProcFn) g_real.glFramebufferParameteri = (PFN_glFramebufferParameteri)getProcFn("glFramebufferParameteri");
    g_real.glFramebufferTexture = (PFN_glFramebufferTexture)GetProcAddress(mod, "glFramebufferTexture");
    if (!g_real.glFramebufferTexture && getProcFn) g_real.glFramebufferTexture = (PFN_glFramebufferTexture)getProcFn("glFramebufferTexture");
    g_real.glFramebufferTexture1D = (PFN_glFramebufferTexture1D)GetProcAddress(mod, "glFramebufferTexture1D");
    if (!g_real.glFramebufferTexture1D && getProcFn) g_real.glFramebufferTexture1D = (PFN_glFramebufferTexture1D)getProcFn("glFramebufferTexture1D");
    g_real.glFramebufferTexture3D = (PFN_glFramebufferTexture3D)GetProcAddress(mod, "glFramebufferTexture3D");
    if (!g_real.glFramebufferTexture3D && getProcFn) g_real.glFramebufferTexture3D = (PFN_glFramebufferTexture3D)getProcFn("glFramebufferTexture3D");
    g_real.glFramebufferTextureLayer = (PFN_glFramebufferTextureLayer)GetProcAddress(mod, "glFramebufferTextureLayer");
    if (!g_real.glFramebufferTextureLayer && getProcFn) g_real.glFramebufferTextureLayer = (PFN_glFramebufferTextureLayer)getProcFn("glFramebufferTextureLayer");
    g_real.glGenerateTextureMipmap = (PFN_glGenerateTextureMipmap)GetProcAddress(mod, "glGenerateTextureMipmap");
    if (!g_real.glGenerateTextureMipmap && getProcFn) g_real.glGenerateTextureMipmap = (PFN_glGenerateTextureMipmap)getProcFn("glGenerateTextureMipmap");
    g_real.glGetQueryBufferObjecti64v = (PFN_glGetQueryBufferObjecti64v)GetProcAddress(mod, "glGetQueryBufferObjecti64v");
    if (!g_real.glGetQueryBufferObjecti64v && getProcFn) g_real.glGetQueryBufferObjecti64v = (PFN_glGetQueryBufferObjecti64v)getProcFn("glGetQueryBufferObjecti64v");
    g_real.glGetQueryBufferObjectiv = (PFN_glGetQueryBufferObjectiv)GetProcAddress(mod, "glGetQueryBufferObjectiv");
    if (!g_real.glGetQueryBufferObjectiv && getProcFn) g_real.glGetQueryBufferObjectiv = (PFN_glGetQueryBufferObjectiv)getProcFn("glGetQueryBufferObjectiv");
    g_real.glGetQueryBufferObjectui64v = (PFN_glGetQueryBufferObjectui64v)GetProcAddress(mod, "glGetQueryBufferObjectui64v");
    if (!g_real.glGetQueryBufferObjectui64v && getProcFn) g_real.glGetQueryBufferObjectui64v = (PFN_glGetQueryBufferObjectui64v)getProcFn("glGetQueryBufferObjectui64v");
    g_real.glGetQueryBufferObjectuiv = (PFN_glGetQueryBufferObjectuiv)GetProcAddress(mod, "glGetQueryBufferObjectuiv");
    if (!g_real.glGetQueryBufferObjectuiv && getProcFn) g_real.glGetQueryBufferObjectuiv = (PFN_glGetQueryBufferObjectuiv)getProcFn("glGetQueryBufferObjectuiv");
    g_real.glInvalidateBufferData = (PFN_glInvalidateBufferData)GetProcAddress(mod, "glInvalidateBufferData");
    if (!g_real.glInvalidateBufferData && getProcFn) g_real.glInvalidateBufferData = (PFN_glInvalidateBufferData)getProcFn("glInvalidateBufferData");
    g_real.glInvalidateBufferSubData = (PFN_glInvalidateBufferSubData)GetProcAddress(mod, "glInvalidateBufferSubData");
    if (!g_real.glInvalidateBufferSubData && getProcFn) g_real.glInvalidateBufferSubData = (PFN_glInvalidateBufferSubData)getProcFn("glInvalidateBufferSubData");
    g_real.glInvalidateTexImage = (PFN_glInvalidateTexImage)GetProcAddress(mod, "glInvalidateTexImage");
    if (!g_real.glInvalidateTexImage && getProcFn) g_real.glInvalidateTexImage = (PFN_glInvalidateTexImage)getProcFn("glInvalidateTexImage");
    g_real.glInvalidateTexSubImage = (PFN_glInvalidateTexSubImage)GetProcAddress(mod, "glInvalidateTexSubImage");
    if (!g_real.glInvalidateTexSubImage && getProcFn) g_real.glInvalidateTexSubImage = (PFN_glInvalidateTexSubImage)getProcFn("glInvalidateTexSubImage");
    g_real.glMemoryBarrier = (PFN_glMemoryBarrier)GetProcAddress(mod, "glMemoryBarrier");
    if (!g_real.glMemoryBarrier && getProcFn) g_real.glMemoryBarrier = (PFN_glMemoryBarrier)getProcFn("glMemoryBarrier");
    g_real.glMemoryBarrierByRegion = (PFN_glMemoryBarrierByRegion)GetProcAddress(mod, "glMemoryBarrierByRegion");
    if (!g_real.glMemoryBarrierByRegion && getProcFn) g_real.glMemoryBarrierByRegion = (PFN_glMemoryBarrierByRegion)getProcFn("glMemoryBarrierByRegion");
    g_real.glMinSampleShading = (PFN_glMinSampleShading)GetProcAddress(mod, "glMinSampleShading");
    if (!g_real.glMinSampleShading && getProcFn) g_real.glMinSampleShading = (PFN_glMinSampleShading)getProcFn("glMinSampleShading");
    g_real.glMultiTexCoord1d = (PFN_glMultiTexCoord1d)GetProcAddress(mod, "glMultiTexCoord1d");
    if (!g_real.glMultiTexCoord1d && getProcFn) g_real.glMultiTexCoord1d = (PFN_glMultiTexCoord1d)getProcFn("glMultiTexCoord1d");
    g_real.glMultiTexCoord1f = (PFN_glMultiTexCoord1f)GetProcAddress(mod, "glMultiTexCoord1f");
    if (!g_real.glMultiTexCoord1f && getProcFn) g_real.glMultiTexCoord1f = (PFN_glMultiTexCoord1f)getProcFn("glMultiTexCoord1f");
    g_real.glMultiTexCoord1i = (PFN_glMultiTexCoord1i)GetProcAddress(mod, "glMultiTexCoord1i");
    if (!g_real.glMultiTexCoord1i && getProcFn) g_real.glMultiTexCoord1i = (PFN_glMultiTexCoord1i)getProcFn("glMultiTexCoord1i");
    g_real.glMultiTexCoord1s = (PFN_glMultiTexCoord1s)GetProcAddress(mod, "glMultiTexCoord1s");
    if (!g_real.glMultiTexCoord1s && getProcFn) g_real.glMultiTexCoord1s = (PFN_glMultiTexCoord1s)getProcFn("glMultiTexCoord1s");
    g_real.glMultiTexCoord2d = (PFN_glMultiTexCoord2d)GetProcAddress(mod, "glMultiTexCoord2d");
    if (!g_real.glMultiTexCoord2d && getProcFn) g_real.glMultiTexCoord2d = (PFN_glMultiTexCoord2d)getProcFn("glMultiTexCoord2d");
    g_real.glMultiTexCoord2f = (PFN_glMultiTexCoord2f)GetProcAddress(mod, "glMultiTexCoord2f");
    if (!g_real.glMultiTexCoord2f && getProcFn) g_real.glMultiTexCoord2f = (PFN_glMultiTexCoord2f)getProcFn("glMultiTexCoord2f");
    g_real.glMultiTexCoord2i = (PFN_glMultiTexCoord2i)GetProcAddress(mod, "glMultiTexCoord2i");
    if (!g_real.glMultiTexCoord2i && getProcFn) g_real.glMultiTexCoord2i = (PFN_glMultiTexCoord2i)getProcFn("glMultiTexCoord2i");
    g_real.glMultiTexCoord2s = (PFN_glMultiTexCoord2s)GetProcAddress(mod, "glMultiTexCoord2s");
    if (!g_real.glMultiTexCoord2s && getProcFn) g_real.glMultiTexCoord2s = (PFN_glMultiTexCoord2s)getProcFn("glMultiTexCoord2s");
    g_real.glMultiTexCoord3d = (PFN_glMultiTexCoord3d)GetProcAddress(mod, "glMultiTexCoord3d");
    if (!g_real.glMultiTexCoord3d && getProcFn) g_real.glMultiTexCoord3d = (PFN_glMultiTexCoord3d)getProcFn("glMultiTexCoord3d");
    g_real.glMultiTexCoord3f = (PFN_glMultiTexCoord3f)GetProcAddress(mod, "glMultiTexCoord3f");
    if (!g_real.glMultiTexCoord3f && getProcFn) g_real.glMultiTexCoord3f = (PFN_glMultiTexCoord3f)getProcFn("glMultiTexCoord3f");
    g_real.glMultiTexCoord3i = (PFN_glMultiTexCoord3i)GetProcAddress(mod, "glMultiTexCoord3i");
    if (!g_real.glMultiTexCoord3i && getProcFn) g_real.glMultiTexCoord3i = (PFN_glMultiTexCoord3i)getProcFn("glMultiTexCoord3i");
    g_real.glMultiTexCoord3s = (PFN_glMultiTexCoord3s)GetProcAddress(mod, "glMultiTexCoord3s");
    if (!g_real.glMultiTexCoord3s && getProcFn) g_real.glMultiTexCoord3s = (PFN_glMultiTexCoord3s)getProcFn("glMultiTexCoord3s");
    g_real.glMultiTexCoord4d = (PFN_glMultiTexCoord4d)GetProcAddress(mod, "glMultiTexCoord4d");
    if (!g_real.glMultiTexCoord4d && getProcFn) g_real.glMultiTexCoord4d = (PFN_glMultiTexCoord4d)getProcFn("glMultiTexCoord4d");
    g_real.glMultiTexCoord4f = (PFN_glMultiTexCoord4f)GetProcAddress(mod, "glMultiTexCoord4f");
    if (!g_real.glMultiTexCoord4f && getProcFn) g_real.glMultiTexCoord4f = (PFN_glMultiTexCoord4f)getProcFn("glMultiTexCoord4f");
    g_real.glMultiTexCoord4i = (PFN_glMultiTexCoord4i)GetProcAddress(mod, "glMultiTexCoord4i");
    if (!g_real.glMultiTexCoord4i && getProcFn) g_real.glMultiTexCoord4i = (PFN_glMultiTexCoord4i)getProcFn("glMultiTexCoord4i");
    g_real.glMultiTexCoord4s = (PFN_glMultiTexCoord4s)GetProcAddress(mod, "glMultiTexCoord4s");
    if (!g_real.glMultiTexCoord4s && getProcFn) g_real.glMultiTexCoord4s = (PFN_glMultiTexCoord4s)getProcFn("glMultiTexCoord4s");
    g_real.glMultiTexCoordP1ui = (PFN_glMultiTexCoordP1ui)GetProcAddress(mod, "glMultiTexCoordP1ui");
    if (!g_real.glMultiTexCoordP1ui && getProcFn) g_real.glMultiTexCoordP1ui = (PFN_glMultiTexCoordP1ui)getProcFn("glMultiTexCoordP1ui");
    g_real.glMultiTexCoordP2ui = (PFN_glMultiTexCoordP2ui)GetProcAddress(mod, "glMultiTexCoordP2ui");
    if (!g_real.glMultiTexCoordP2ui && getProcFn) g_real.glMultiTexCoordP2ui = (PFN_glMultiTexCoordP2ui)getProcFn("glMultiTexCoordP2ui");
    g_real.glMultiTexCoordP3ui = (PFN_glMultiTexCoordP3ui)GetProcAddress(mod, "glMultiTexCoordP3ui");
    if (!g_real.glMultiTexCoordP3ui && getProcFn) g_real.glMultiTexCoordP3ui = (PFN_glMultiTexCoordP3ui)getProcFn("glMultiTexCoordP3ui");
    g_real.glMultiTexCoordP4ui = (PFN_glMultiTexCoordP4ui)GetProcAddress(mod, "glMultiTexCoordP4ui");
    if (!g_real.glMultiTexCoordP4ui && getProcFn) g_real.glMultiTexCoordP4ui = (PFN_glMultiTexCoordP4ui)getProcFn("glMultiTexCoordP4ui");
    g_real.glNamedFramebufferDrawBuffer = (PFN_glNamedFramebufferDrawBuffer)GetProcAddress(mod, "glNamedFramebufferDrawBuffer");
    if (!g_real.glNamedFramebufferDrawBuffer && getProcFn) g_real.glNamedFramebufferDrawBuffer = (PFN_glNamedFramebufferDrawBuffer)getProcFn("glNamedFramebufferDrawBuffer");
    g_real.glNamedFramebufferParameteri = (PFN_glNamedFramebufferParameteri)GetProcAddress(mod, "glNamedFramebufferParameteri");
    if (!g_real.glNamedFramebufferParameteri && getProcFn) g_real.glNamedFramebufferParameteri = (PFN_glNamedFramebufferParameteri)getProcFn("glNamedFramebufferParameteri");
    g_real.glNamedFramebufferReadBuffer = (PFN_glNamedFramebufferReadBuffer)GetProcAddress(mod, "glNamedFramebufferReadBuffer");
    if (!g_real.glNamedFramebufferReadBuffer && getProcFn) g_real.glNamedFramebufferReadBuffer = (PFN_glNamedFramebufferReadBuffer)getProcFn("glNamedFramebufferReadBuffer");
    g_real.glNamedFramebufferRenderbuffer = (PFN_glNamedFramebufferRenderbuffer)GetProcAddress(mod, "glNamedFramebufferRenderbuffer");
    if (!g_real.glNamedFramebufferRenderbuffer && getProcFn) g_real.glNamedFramebufferRenderbuffer = (PFN_glNamedFramebufferRenderbuffer)getProcFn("glNamedFramebufferRenderbuffer");
    g_real.glNamedFramebufferTexture = (PFN_glNamedFramebufferTexture)GetProcAddress(mod, "glNamedFramebufferTexture");
    if (!g_real.glNamedFramebufferTexture && getProcFn) g_real.glNamedFramebufferTexture = (PFN_glNamedFramebufferTexture)getProcFn("glNamedFramebufferTexture");
    g_real.glNamedFramebufferTextureLayer = (PFN_glNamedFramebufferTextureLayer)GetProcAddress(mod, "glNamedFramebufferTextureLayer");
    if (!g_real.glNamedFramebufferTextureLayer && getProcFn) g_real.glNamedFramebufferTextureLayer = (PFN_glNamedFramebufferTextureLayer)getProcFn("glNamedFramebufferTextureLayer");
    g_real.glNamedRenderbufferStorage = (PFN_glNamedRenderbufferStorage)GetProcAddress(mod, "glNamedRenderbufferStorage");
    if (!g_real.glNamedRenderbufferStorage && getProcFn) g_real.glNamedRenderbufferStorage = (PFN_glNamedRenderbufferStorage)getProcFn("glNamedRenderbufferStorage");
    g_real.glNamedRenderbufferStorageMultisample = (PFN_glNamedRenderbufferStorageMultisample)GetProcAddress(mod, "glNamedRenderbufferStorageMultisample");
    if (!g_real.glNamedRenderbufferStorageMultisample && getProcFn) g_real.glNamedRenderbufferStorageMultisample = (PFN_glNamedRenderbufferStorageMultisample)getProcFn("glNamedRenderbufferStorageMultisample");
    g_real.glNormalP3ui = (PFN_glNormalP3ui)GetProcAddress(mod, "glNormalP3ui");
    if (!g_real.glNormalP3ui && getProcFn) g_real.glNormalP3ui = (PFN_glNormalP3ui)getProcFn("glNormalP3ui");
    g_real.glPatchParameteri = (PFN_glPatchParameteri)GetProcAddress(mod, "glPatchParameteri");
    if (!g_real.glPatchParameteri && getProcFn) g_real.glPatchParameteri = (PFN_glPatchParameteri)getProcFn("glPatchParameteri");
    g_real.glPauseTransformFeedback = (PFN_glPauseTransformFeedback)GetProcAddress(mod, "glPauseTransformFeedback");
    if (!g_real.glPauseTransformFeedback && getProcFn) g_real.glPauseTransformFeedback = (PFN_glPauseTransformFeedback)getProcFn("glPauseTransformFeedback");
    g_real.glPointParameterf = (PFN_glPointParameterf)GetProcAddress(mod, "glPointParameterf");
    if (!g_real.glPointParameterf && getProcFn) g_real.glPointParameterf = (PFN_glPointParameterf)getProcFn("glPointParameterf");
    g_real.glPointParameteri = (PFN_glPointParameteri)GetProcAddress(mod, "glPointParameteri");
    if (!g_real.glPointParameteri && getProcFn) g_real.glPointParameteri = (PFN_glPointParameteri)getProcFn("glPointParameteri");
    g_real.glPolygonOffsetClamp = (PFN_glPolygonOffsetClamp)GetProcAddress(mod, "glPolygonOffsetClamp");
    if (!g_real.glPolygonOffsetClamp && getProcFn) g_real.glPolygonOffsetClamp = (PFN_glPolygonOffsetClamp)getProcFn("glPolygonOffsetClamp");
    g_real.glPopDebugGroup = (PFN_glPopDebugGroup)GetProcAddress(mod, "glPopDebugGroup");
    if (!g_real.glPopDebugGroup && getProcFn) g_real.glPopDebugGroup = (PFN_glPopDebugGroup)getProcFn("glPopDebugGroup");
    g_real.glPrimitiveRestartIndex = (PFN_glPrimitiveRestartIndex)GetProcAddress(mod, "glPrimitiveRestartIndex");
    if (!g_real.glPrimitiveRestartIndex && getProcFn) g_real.glPrimitiveRestartIndex = (PFN_glPrimitiveRestartIndex)getProcFn("glPrimitiveRestartIndex");
    g_real.glProgramParameteri = (PFN_glProgramParameteri)GetProcAddress(mod, "glProgramParameteri");
    if (!g_real.glProgramParameteri && getProcFn) g_real.glProgramParameteri = (PFN_glProgramParameteri)getProcFn("glProgramParameteri");
    g_real.glProgramUniform1d = (PFN_glProgramUniform1d)GetProcAddress(mod, "glProgramUniform1d");
    if (!g_real.glProgramUniform1d && getProcFn) g_real.glProgramUniform1d = (PFN_glProgramUniform1d)getProcFn("glProgramUniform1d");
    g_real.glProgramUniform1f = (PFN_glProgramUniform1f)GetProcAddress(mod, "glProgramUniform1f");
    if (!g_real.glProgramUniform1f && getProcFn) g_real.glProgramUniform1f = (PFN_glProgramUniform1f)getProcFn("glProgramUniform1f");
    g_real.glProgramUniform1i = (PFN_glProgramUniform1i)GetProcAddress(mod, "glProgramUniform1i");
    if (!g_real.glProgramUniform1i && getProcFn) g_real.glProgramUniform1i = (PFN_glProgramUniform1i)getProcFn("glProgramUniform1i");
    g_real.glProgramUniform1ui = (PFN_glProgramUniform1ui)GetProcAddress(mod, "glProgramUniform1ui");
    if (!g_real.glProgramUniform1ui && getProcFn) g_real.glProgramUniform1ui = (PFN_glProgramUniform1ui)getProcFn("glProgramUniform1ui");
    g_real.glProgramUniform2d = (PFN_glProgramUniform2d)GetProcAddress(mod, "glProgramUniform2d");
    if (!g_real.glProgramUniform2d && getProcFn) g_real.glProgramUniform2d = (PFN_glProgramUniform2d)getProcFn("glProgramUniform2d");
    g_real.glProgramUniform2f = (PFN_glProgramUniform2f)GetProcAddress(mod, "glProgramUniform2f");
    if (!g_real.glProgramUniform2f && getProcFn) g_real.glProgramUniform2f = (PFN_glProgramUniform2f)getProcFn("glProgramUniform2f");
    g_real.glProgramUniform2i = (PFN_glProgramUniform2i)GetProcAddress(mod, "glProgramUniform2i");
    if (!g_real.glProgramUniform2i && getProcFn) g_real.glProgramUniform2i = (PFN_glProgramUniform2i)getProcFn("glProgramUniform2i");
    g_real.glProgramUniform2ui = (PFN_glProgramUniform2ui)GetProcAddress(mod, "glProgramUniform2ui");
    if (!g_real.glProgramUniform2ui && getProcFn) g_real.glProgramUniform2ui = (PFN_glProgramUniform2ui)getProcFn("glProgramUniform2ui");
    g_real.glProgramUniform3d = (PFN_glProgramUniform3d)GetProcAddress(mod, "glProgramUniform3d");
    if (!g_real.glProgramUniform3d && getProcFn) g_real.glProgramUniform3d = (PFN_glProgramUniform3d)getProcFn("glProgramUniform3d");
    g_real.glProgramUniform3f = (PFN_glProgramUniform3f)GetProcAddress(mod, "glProgramUniform3f");
    if (!g_real.glProgramUniform3f && getProcFn) g_real.glProgramUniform3f = (PFN_glProgramUniform3f)getProcFn("glProgramUniform3f");
    g_real.glProgramUniform3i = (PFN_glProgramUniform3i)GetProcAddress(mod, "glProgramUniform3i");
    if (!g_real.glProgramUniform3i && getProcFn) g_real.glProgramUniform3i = (PFN_glProgramUniform3i)getProcFn("glProgramUniform3i");
    g_real.glProgramUniform3ui = (PFN_glProgramUniform3ui)GetProcAddress(mod, "glProgramUniform3ui");
    if (!g_real.glProgramUniform3ui && getProcFn) g_real.glProgramUniform3ui = (PFN_glProgramUniform3ui)getProcFn("glProgramUniform3ui");
    g_real.glProgramUniform4d = (PFN_glProgramUniform4d)GetProcAddress(mod, "glProgramUniform4d");
    if (!g_real.glProgramUniform4d && getProcFn) g_real.glProgramUniform4d = (PFN_glProgramUniform4d)getProcFn("glProgramUniform4d");
    g_real.glProgramUniform4f = (PFN_glProgramUniform4f)GetProcAddress(mod, "glProgramUniform4f");
    if (!g_real.glProgramUniform4f && getProcFn) g_real.glProgramUniform4f = (PFN_glProgramUniform4f)getProcFn("glProgramUniform4f");
    g_real.glProgramUniform4i = (PFN_glProgramUniform4i)GetProcAddress(mod, "glProgramUniform4i");
    if (!g_real.glProgramUniform4i && getProcFn) g_real.glProgramUniform4i = (PFN_glProgramUniform4i)getProcFn("glProgramUniform4i");
    g_real.glProgramUniform4ui = (PFN_glProgramUniform4ui)GetProcAddress(mod, "glProgramUniform4ui");
    if (!g_real.glProgramUniform4ui && getProcFn) g_real.glProgramUniform4ui = (PFN_glProgramUniform4ui)getProcFn("glProgramUniform4ui");
    g_real.glProvokingVertex = (PFN_glProvokingVertex)GetProcAddress(mod, "glProvokingVertex");
    if (!g_real.glProvokingVertex && getProcFn) g_real.glProvokingVertex = (PFN_glProvokingVertex)getProcFn("glProvokingVertex");
    g_real.glQueryCounter = (PFN_glQueryCounter)GetProcAddress(mod, "glQueryCounter");
    if (!g_real.glQueryCounter && getProcFn) g_real.glQueryCounter = (PFN_glQueryCounter)getProcFn("glQueryCounter");
    g_real.glReleaseShaderCompiler = (PFN_glReleaseShaderCompiler)GetProcAddress(mod, "glReleaseShaderCompiler");
    if (!g_real.glReleaseShaderCompiler && getProcFn) g_real.glReleaseShaderCompiler = (PFN_glReleaseShaderCompiler)getProcFn("glReleaseShaderCompiler");
    g_real.glRenderbufferStorageMultisample = (PFN_glRenderbufferStorageMultisample)GetProcAddress(mod, "glRenderbufferStorageMultisample");
    if (!g_real.glRenderbufferStorageMultisample && getProcFn) g_real.glRenderbufferStorageMultisample = (PFN_glRenderbufferStorageMultisample)getProcFn("glRenderbufferStorageMultisample");
    g_real.glResumeTransformFeedback = (PFN_glResumeTransformFeedback)GetProcAddress(mod, "glResumeTransformFeedback");
    if (!g_real.glResumeTransformFeedback && getProcFn) g_real.glResumeTransformFeedback = (PFN_glResumeTransformFeedback)getProcFn("glResumeTransformFeedback");
    g_real.glSampleCoverage = (PFN_glSampleCoverage)GetProcAddress(mod, "glSampleCoverage");
    if (!g_real.glSampleCoverage && getProcFn) g_real.glSampleCoverage = (PFN_glSampleCoverage)getProcFn("glSampleCoverage");
    g_real.glSampleMaski = (PFN_glSampleMaski)GetProcAddress(mod, "glSampleMaski");
    if (!g_real.glSampleMaski && getProcFn) g_real.glSampleMaski = (PFN_glSampleMaski)getProcFn("glSampleMaski");
    g_real.glSamplerParameterf = (PFN_glSamplerParameterf)GetProcAddress(mod, "glSamplerParameterf");
    if (!g_real.glSamplerParameterf && getProcFn) g_real.glSamplerParameterf = (PFN_glSamplerParameterf)getProcFn("glSamplerParameterf");
    g_real.glSamplerParameteri = (PFN_glSamplerParameteri)GetProcAddress(mod, "glSamplerParameteri");
    if (!g_real.glSamplerParameteri && getProcFn) g_real.glSamplerParameteri = (PFN_glSamplerParameteri)getProcFn("glSamplerParameteri");
    g_real.glScissorIndexed = (PFN_glScissorIndexed)GetProcAddress(mod, "glScissorIndexed");
    if (!g_real.glScissorIndexed && getProcFn) g_real.glScissorIndexed = (PFN_glScissorIndexed)getProcFn("glScissorIndexed");
    g_real.glSecondaryColor3b = (PFN_glSecondaryColor3b)GetProcAddress(mod, "glSecondaryColor3b");
    if (!g_real.glSecondaryColor3b && getProcFn) g_real.glSecondaryColor3b = (PFN_glSecondaryColor3b)getProcFn("glSecondaryColor3b");
    g_real.glSecondaryColor3d = (PFN_glSecondaryColor3d)GetProcAddress(mod, "glSecondaryColor3d");
    if (!g_real.glSecondaryColor3d && getProcFn) g_real.glSecondaryColor3d = (PFN_glSecondaryColor3d)getProcFn("glSecondaryColor3d");
    g_real.glSecondaryColor3f = (PFN_glSecondaryColor3f)GetProcAddress(mod, "glSecondaryColor3f");
    if (!g_real.glSecondaryColor3f && getProcFn) g_real.glSecondaryColor3f = (PFN_glSecondaryColor3f)getProcFn("glSecondaryColor3f");
    g_real.glSecondaryColor3i = (PFN_glSecondaryColor3i)GetProcAddress(mod, "glSecondaryColor3i");
    if (!g_real.glSecondaryColor3i && getProcFn) g_real.glSecondaryColor3i = (PFN_glSecondaryColor3i)getProcFn("glSecondaryColor3i");
    g_real.glSecondaryColor3s = (PFN_glSecondaryColor3s)GetProcAddress(mod, "glSecondaryColor3s");
    if (!g_real.glSecondaryColor3s && getProcFn) g_real.glSecondaryColor3s = (PFN_glSecondaryColor3s)getProcFn("glSecondaryColor3s");
    g_real.glSecondaryColor3ub = (PFN_glSecondaryColor3ub)GetProcAddress(mod, "glSecondaryColor3ub");
    if (!g_real.glSecondaryColor3ub && getProcFn) g_real.glSecondaryColor3ub = (PFN_glSecondaryColor3ub)getProcFn("glSecondaryColor3ub");
    g_real.glSecondaryColor3ui = (PFN_glSecondaryColor3ui)GetProcAddress(mod, "glSecondaryColor3ui");
    if (!g_real.glSecondaryColor3ui && getProcFn) g_real.glSecondaryColor3ui = (PFN_glSecondaryColor3ui)getProcFn("glSecondaryColor3ui");
    g_real.glSecondaryColor3us = (PFN_glSecondaryColor3us)GetProcAddress(mod, "glSecondaryColor3us");
    if (!g_real.glSecondaryColor3us && getProcFn) g_real.glSecondaryColor3us = (PFN_glSecondaryColor3us)getProcFn("glSecondaryColor3us");
    g_real.glSecondaryColorP3ui = (PFN_glSecondaryColorP3ui)GetProcAddress(mod, "glSecondaryColorP3ui");
    if (!g_real.glSecondaryColorP3ui && getProcFn) g_real.glSecondaryColorP3ui = (PFN_glSecondaryColorP3ui)getProcFn("glSecondaryColorP3ui");
    g_real.glShaderStorageBlockBinding = (PFN_glShaderStorageBlockBinding)GetProcAddress(mod, "glShaderStorageBlockBinding");
    if (!g_real.glShaderStorageBlockBinding && getProcFn) g_real.glShaderStorageBlockBinding = (PFN_glShaderStorageBlockBinding)getProcFn("glShaderStorageBlockBinding");
    g_real.glStencilFuncSeparate = (PFN_glStencilFuncSeparate)GetProcAddress(mod, "glStencilFuncSeparate");
    if (!g_real.glStencilFuncSeparate && getProcFn) g_real.glStencilFuncSeparate = (PFN_glStencilFuncSeparate)getProcFn("glStencilFuncSeparate");
    g_real.glStencilMaskSeparate = (PFN_glStencilMaskSeparate)GetProcAddress(mod, "glStencilMaskSeparate");
    if (!g_real.glStencilMaskSeparate && getProcFn) g_real.glStencilMaskSeparate = (PFN_glStencilMaskSeparate)getProcFn("glStencilMaskSeparate");
    g_real.glStencilOpSeparate = (PFN_glStencilOpSeparate)GetProcAddress(mod, "glStencilOpSeparate");
    if (!g_real.glStencilOpSeparate && getProcFn) g_real.glStencilOpSeparate = (PFN_glStencilOpSeparate)getProcFn("glStencilOpSeparate");
    g_real.glTexBuffer = (PFN_glTexBuffer)GetProcAddress(mod, "glTexBuffer");
    if (!g_real.glTexBuffer && getProcFn) g_real.glTexBuffer = (PFN_glTexBuffer)getProcFn("glTexBuffer");
    g_real.glTexBufferRange = (PFN_glTexBufferRange)GetProcAddress(mod, "glTexBufferRange");
    if (!g_real.glTexBufferRange && getProcFn) g_real.glTexBufferRange = (PFN_glTexBufferRange)getProcFn("glTexBufferRange");
    g_real.glTexCoordP1ui = (PFN_glTexCoordP1ui)GetProcAddress(mod, "glTexCoordP1ui");
    if (!g_real.glTexCoordP1ui && getProcFn) g_real.glTexCoordP1ui = (PFN_glTexCoordP1ui)getProcFn("glTexCoordP1ui");
    g_real.glTexCoordP2ui = (PFN_glTexCoordP2ui)GetProcAddress(mod, "glTexCoordP2ui");
    if (!g_real.glTexCoordP2ui && getProcFn) g_real.glTexCoordP2ui = (PFN_glTexCoordP2ui)getProcFn("glTexCoordP2ui");
    g_real.glTexCoordP3ui = (PFN_glTexCoordP3ui)GetProcAddress(mod, "glTexCoordP3ui");
    if (!g_real.glTexCoordP3ui && getProcFn) g_real.glTexCoordP3ui = (PFN_glTexCoordP3ui)getProcFn("glTexCoordP3ui");
    g_real.glTexCoordP4ui = (PFN_glTexCoordP4ui)GetProcAddress(mod, "glTexCoordP4ui");
    if (!g_real.glTexCoordP4ui && getProcFn) g_real.glTexCoordP4ui = (PFN_glTexCoordP4ui)getProcFn("glTexCoordP4ui");
    g_real.glTexImage2DMultisample = (PFN_glTexImage2DMultisample)GetProcAddress(mod, "glTexImage2DMultisample");
    if (!g_real.glTexImage2DMultisample && getProcFn) g_real.glTexImage2DMultisample = (PFN_glTexImage2DMultisample)getProcFn("glTexImage2DMultisample");
    g_real.glTexImage3DMultisample = (PFN_glTexImage3DMultisample)GetProcAddress(mod, "glTexImage3DMultisample");
    if (!g_real.glTexImage3DMultisample && getProcFn) g_real.glTexImage3DMultisample = (PFN_glTexImage3DMultisample)getProcFn("glTexImage3DMultisample");
    g_real.glTexStorage1D = (PFN_glTexStorage1D)GetProcAddress(mod, "glTexStorage1D");
    if (!g_real.glTexStorage1D && getProcFn) g_real.glTexStorage1D = (PFN_glTexStorage1D)getProcFn("glTexStorage1D");
    g_real.glTexStorage2D = (PFN_glTexStorage2D)GetProcAddress(mod, "glTexStorage2D");
    if (!g_real.glTexStorage2D && getProcFn) g_real.glTexStorage2D = (PFN_glTexStorage2D)getProcFn("glTexStorage2D");
    g_real.glTexStorage2DMultisample = (PFN_glTexStorage2DMultisample)GetProcAddress(mod, "glTexStorage2DMultisample");
    if (!g_real.glTexStorage2DMultisample && getProcFn) g_real.glTexStorage2DMultisample = (PFN_glTexStorage2DMultisample)getProcFn("glTexStorage2DMultisample");
    g_real.glTexStorage3D = (PFN_glTexStorage3D)GetProcAddress(mod, "glTexStorage3D");
    if (!g_real.glTexStorage3D && getProcFn) g_real.glTexStorage3D = (PFN_glTexStorage3D)getProcFn("glTexStorage3D");
    g_real.glTexStorage3DMultisample = (PFN_glTexStorage3DMultisample)GetProcAddress(mod, "glTexStorage3DMultisample");
    if (!g_real.glTexStorage3DMultisample && getProcFn) g_real.glTexStorage3DMultisample = (PFN_glTexStorage3DMultisample)getProcFn("glTexStorage3DMultisample");
    g_real.glTextureBarrier = (PFN_glTextureBarrier)GetProcAddress(mod, "glTextureBarrier");
    if (!g_real.glTextureBarrier && getProcFn) g_real.glTextureBarrier = (PFN_glTextureBarrier)getProcFn("glTextureBarrier");
    g_real.glTextureBuffer = (PFN_glTextureBuffer)GetProcAddress(mod, "glTextureBuffer");
    if (!g_real.glTextureBuffer && getProcFn) g_real.glTextureBuffer = (PFN_glTextureBuffer)getProcFn("glTextureBuffer");
    g_real.glTextureBufferRange = (PFN_glTextureBufferRange)GetProcAddress(mod, "glTextureBufferRange");
    if (!g_real.glTextureBufferRange && getProcFn) g_real.glTextureBufferRange = (PFN_glTextureBufferRange)getProcFn("glTextureBufferRange");
    g_real.glTextureParameterf = (PFN_glTextureParameterf)GetProcAddress(mod, "glTextureParameterf");
    if (!g_real.glTextureParameterf && getProcFn) g_real.glTextureParameterf = (PFN_glTextureParameterf)getProcFn("glTextureParameterf");
    g_real.glTextureParameteri = (PFN_glTextureParameteri)GetProcAddress(mod, "glTextureParameteri");
    if (!g_real.glTextureParameteri && getProcFn) g_real.glTextureParameteri = (PFN_glTextureParameteri)getProcFn("glTextureParameteri");
    g_real.glTextureStorage1D = (PFN_glTextureStorage1D)GetProcAddress(mod, "glTextureStorage1D");
    if (!g_real.glTextureStorage1D && getProcFn) g_real.glTextureStorage1D = (PFN_glTextureStorage1D)getProcFn("glTextureStorage1D");
    g_real.glTextureStorage2D = (PFN_glTextureStorage2D)GetProcAddress(mod, "glTextureStorage2D");
    if (!g_real.glTextureStorage2D && getProcFn) g_real.glTextureStorage2D = (PFN_glTextureStorage2D)getProcFn("glTextureStorage2D");
    g_real.glTextureStorage2DMultisample = (PFN_glTextureStorage2DMultisample)GetProcAddress(mod, "glTextureStorage2DMultisample");
    if (!g_real.glTextureStorage2DMultisample && getProcFn) g_real.glTextureStorage2DMultisample = (PFN_glTextureStorage2DMultisample)getProcFn("glTextureStorage2DMultisample");
    g_real.glTextureStorage3D = (PFN_glTextureStorage3D)GetProcAddress(mod, "glTextureStorage3D");
    if (!g_real.glTextureStorage3D && getProcFn) g_real.glTextureStorage3D = (PFN_glTextureStorage3D)getProcFn("glTextureStorage3D");
    g_real.glTextureStorage3DMultisample = (PFN_glTextureStorage3DMultisample)GetProcAddress(mod, "glTextureStorage3DMultisample");
    if (!g_real.glTextureStorage3DMultisample && getProcFn) g_real.glTextureStorage3DMultisample = (PFN_glTextureStorage3DMultisample)getProcFn("glTextureStorage3DMultisample");
    g_real.glTextureView = (PFN_glTextureView)GetProcAddress(mod, "glTextureView");
    if (!g_real.glTextureView && getProcFn) g_real.glTextureView = (PFN_glTextureView)getProcFn("glTextureView");
    g_real.glTransformFeedbackBufferBase = (PFN_glTransformFeedbackBufferBase)GetProcAddress(mod, "glTransformFeedbackBufferBase");
    if (!g_real.glTransformFeedbackBufferBase && getProcFn) g_real.glTransformFeedbackBufferBase = (PFN_glTransformFeedbackBufferBase)getProcFn("glTransformFeedbackBufferBase");
    g_real.glTransformFeedbackBufferRange = (PFN_glTransformFeedbackBufferRange)GetProcAddress(mod, "glTransformFeedbackBufferRange");
    if (!g_real.glTransformFeedbackBufferRange && getProcFn) g_real.glTransformFeedbackBufferRange = (PFN_glTransformFeedbackBufferRange)getProcFn("glTransformFeedbackBufferRange");
    g_real.glUniform1d = (PFN_glUniform1d)GetProcAddress(mod, "glUniform1d");
    if (!g_real.glUniform1d && getProcFn) g_real.glUniform1d = (PFN_glUniform1d)getProcFn("glUniform1d");
    g_real.glUniform1ui = (PFN_glUniform1ui)GetProcAddress(mod, "glUniform1ui");
    if (!g_real.glUniform1ui && getProcFn) g_real.glUniform1ui = (PFN_glUniform1ui)getProcFn("glUniform1ui");
    g_real.glUniform2d = (PFN_glUniform2d)GetProcAddress(mod, "glUniform2d");
    if (!g_real.glUniform2d && getProcFn) g_real.glUniform2d = (PFN_glUniform2d)getProcFn("glUniform2d");
    g_real.glUniform2i = (PFN_glUniform2i)GetProcAddress(mod, "glUniform2i");
    if (!g_real.glUniform2i && getProcFn) g_real.glUniform2i = (PFN_glUniform2i)getProcFn("glUniform2i");
    g_real.glUniform2ui = (PFN_glUniform2ui)GetProcAddress(mod, "glUniform2ui");
    if (!g_real.glUniform2ui && getProcFn) g_real.glUniform2ui = (PFN_glUniform2ui)getProcFn("glUniform2ui");
    g_real.glUniform3d = (PFN_glUniform3d)GetProcAddress(mod, "glUniform3d");
    if (!g_real.glUniform3d && getProcFn) g_real.glUniform3d = (PFN_glUniform3d)getProcFn("glUniform3d");
    g_real.glUniform3i = (PFN_glUniform3i)GetProcAddress(mod, "glUniform3i");
    if (!g_real.glUniform3i && getProcFn) g_real.glUniform3i = (PFN_glUniform3i)getProcFn("glUniform3i");
    g_real.glUniform3ui = (PFN_glUniform3ui)GetProcAddress(mod, "glUniform3ui");
    if (!g_real.glUniform3ui && getProcFn) g_real.glUniform3ui = (PFN_glUniform3ui)getProcFn("glUniform3ui");
    g_real.glUniform4d = (PFN_glUniform4d)GetProcAddress(mod, "glUniform4d");
    if (!g_real.glUniform4d && getProcFn) g_real.glUniform4d = (PFN_glUniform4d)getProcFn("glUniform4d");
    g_real.glUniform4i = (PFN_glUniform4i)GetProcAddress(mod, "glUniform4i");
    if (!g_real.glUniform4i && getProcFn) g_real.glUniform4i = (PFN_glUniform4i)getProcFn("glUniform4i");
    g_real.glUniform4ui = (PFN_glUniform4ui)GetProcAddress(mod, "glUniform4ui");
    if (!g_real.glUniform4ui && getProcFn) g_real.glUniform4ui = (PFN_glUniform4ui)getProcFn("glUniform4ui");
    g_real.glUniformBlockBinding = (PFN_glUniformBlockBinding)GetProcAddress(mod, "glUniformBlockBinding");
    if (!g_real.glUniformBlockBinding && getProcFn) g_real.glUniformBlockBinding = (PFN_glUniformBlockBinding)getProcFn("glUniformBlockBinding");
    g_real.glUseProgramStages = (PFN_glUseProgramStages)GetProcAddress(mod, "glUseProgramStages");
    if (!g_real.glUseProgramStages && getProcFn) g_real.glUseProgramStages = (PFN_glUseProgramStages)getProcFn("glUseProgramStages");
    g_real.glValidateProgram = (PFN_glValidateProgram)GetProcAddress(mod, "glValidateProgram");
    if (!g_real.glValidateProgram && getProcFn) g_real.glValidateProgram = (PFN_glValidateProgram)getProcFn("glValidateProgram");
    g_real.glValidateProgramPipeline = (PFN_glValidateProgramPipeline)GetProcAddress(mod, "glValidateProgramPipeline");
    if (!g_real.glValidateProgramPipeline && getProcFn) g_real.glValidateProgramPipeline = (PFN_glValidateProgramPipeline)getProcFn("glValidateProgramPipeline");
    g_real.glVertexArrayAttribBinding = (PFN_glVertexArrayAttribBinding)GetProcAddress(mod, "glVertexArrayAttribBinding");
    if (!g_real.glVertexArrayAttribBinding && getProcFn) g_real.glVertexArrayAttribBinding = (PFN_glVertexArrayAttribBinding)getProcFn("glVertexArrayAttribBinding");
    g_real.glVertexArrayAttribFormat = (PFN_glVertexArrayAttribFormat)GetProcAddress(mod, "glVertexArrayAttribFormat");
    if (!g_real.glVertexArrayAttribFormat && getProcFn) g_real.glVertexArrayAttribFormat = (PFN_glVertexArrayAttribFormat)getProcFn("glVertexArrayAttribFormat");
    g_real.glVertexArrayAttribIFormat = (PFN_glVertexArrayAttribIFormat)GetProcAddress(mod, "glVertexArrayAttribIFormat");
    if (!g_real.glVertexArrayAttribIFormat && getProcFn) g_real.glVertexArrayAttribIFormat = (PFN_glVertexArrayAttribIFormat)getProcFn("glVertexArrayAttribIFormat");
    g_real.glVertexArrayAttribLFormat = (PFN_glVertexArrayAttribLFormat)GetProcAddress(mod, "glVertexArrayAttribLFormat");
    if (!g_real.glVertexArrayAttribLFormat && getProcFn) g_real.glVertexArrayAttribLFormat = (PFN_glVertexArrayAttribLFormat)getProcFn("glVertexArrayAttribLFormat");
    g_real.glVertexArrayBindingDivisor = (PFN_glVertexArrayBindingDivisor)GetProcAddress(mod, "glVertexArrayBindingDivisor");
    if (!g_real.glVertexArrayBindingDivisor && getProcFn) g_real.glVertexArrayBindingDivisor = (PFN_glVertexArrayBindingDivisor)getProcFn("glVertexArrayBindingDivisor");
    g_real.glVertexArrayElementBuffer = (PFN_glVertexArrayElementBuffer)GetProcAddress(mod, "glVertexArrayElementBuffer");
    if (!g_real.glVertexArrayElementBuffer && getProcFn) g_real.glVertexArrayElementBuffer = (PFN_glVertexArrayElementBuffer)getProcFn("glVertexArrayElementBuffer");
    g_real.glVertexArrayVertexBuffer = (PFN_glVertexArrayVertexBuffer)GetProcAddress(mod, "glVertexArrayVertexBuffer");
    if (!g_real.glVertexArrayVertexBuffer && getProcFn) g_real.glVertexArrayVertexBuffer = (PFN_glVertexArrayVertexBuffer)getProcFn("glVertexArrayVertexBuffer");
    g_real.glVertexAttrib1d = (PFN_glVertexAttrib1d)GetProcAddress(mod, "glVertexAttrib1d");
    if (!g_real.glVertexAttrib1d && getProcFn) g_real.glVertexAttrib1d = (PFN_glVertexAttrib1d)getProcFn("glVertexAttrib1d");
    g_real.glVertexAttrib1f = (PFN_glVertexAttrib1f)GetProcAddress(mod, "glVertexAttrib1f");
    if (!g_real.glVertexAttrib1f && getProcFn) g_real.glVertexAttrib1f = (PFN_glVertexAttrib1f)getProcFn("glVertexAttrib1f");
    g_real.glVertexAttrib1s = (PFN_glVertexAttrib1s)GetProcAddress(mod, "glVertexAttrib1s");
    if (!g_real.glVertexAttrib1s && getProcFn) g_real.glVertexAttrib1s = (PFN_glVertexAttrib1s)getProcFn("glVertexAttrib1s");
    g_real.glVertexAttrib2d = (PFN_glVertexAttrib2d)GetProcAddress(mod, "glVertexAttrib2d");
    if (!g_real.glVertexAttrib2d && getProcFn) g_real.glVertexAttrib2d = (PFN_glVertexAttrib2d)getProcFn("glVertexAttrib2d");
    g_real.glVertexAttrib2f = (PFN_glVertexAttrib2f)GetProcAddress(mod, "glVertexAttrib2f");
    if (!g_real.glVertexAttrib2f && getProcFn) g_real.glVertexAttrib2f = (PFN_glVertexAttrib2f)getProcFn("glVertexAttrib2f");
    g_real.glVertexAttrib2s = (PFN_glVertexAttrib2s)GetProcAddress(mod, "glVertexAttrib2s");
    if (!g_real.glVertexAttrib2s && getProcFn) g_real.glVertexAttrib2s = (PFN_glVertexAttrib2s)getProcFn("glVertexAttrib2s");
    g_real.glVertexAttrib3d = (PFN_glVertexAttrib3d)GetProcAddress(mod, "glVertexAttrib3d");
    if (!g_real.glVertexAttrib3d && getProcFn) g_real.glVertexAttrib3d = (PFN_glVertexAttrib3d)getProcFn("glVertexAttrib3d");
    g_real.glVertexAttrib3f = (PFN_glVertexAttrib3f)GetProcAddress(mod, "glVertexAttrib3f");
    if (!g_real.glVertexAttrib3f && getProcFn) g_real.glVertexAttrib3f = (PFN_glVertexAttrib3f)getProcFn("glVertexAttrib3f");
    g_real.glVertexAttrib3s = (PFN_glVertexAttrib3s)GetProcAddress(mod, "glVertexAttrib3s");
    if (!g_real.glVertexAttrib3s && getProcFn) g_real.glVertexAttrib3s = (PFN_glVertexAttrib3s)getProcFn("glVertexAttrib3s");
    g_real.glVertexAttrib4Nub = (PFN_glVertexAttrib4Nub)GetProcAddress(mod, "glVertexAttrib4Nub");
    if (!g_real.glVertexAttrib4Nub && getProcFn) g_real.glVertexAttrib4Nub = (PFN_glVertexAttrib4Nub)getProcFn("glVertexAttrib4Nub");
    g_real.glVertexAttrib4d = (PFN_glVertexAttrib4d)GetProcAddress(mod, "glVertexAttrib4d");
    if (!g_real.glVertexAttrib4d && getProcFn) g_real.glVertexAttrib4d = (PFN_glVertexAttrib4d)getProcFn("glVertexAttrib4d");
    g_real.glVertexAttrib4f = (PFN_glVertexAttrib4f)GetProcAddress(mod, "glVertexAttrib4f");
    if (!g_real.glVertexAttrib4f && getProcFn) g_real.glVertexAttrib4f = (PFN_glVertexAttrib4f)getProcFn("glVertexAttrib4f");
    g_real.glVertexAttrib4s = (PFN_glVertexAttrib4s)GetProcAddress(mod, "glVertexAttrib4s");
    if (!g_real.glVertexAttrib4s && getProcFn) g_real.glVertexAttrib4s = (PFN_glVertexAttrib4s)getProcFn("glVertexAttrib4s");
    g_real.glVertexAttribBinding = (PFN_glVertexAttribBinding)GetProcAddress(mod, "glVertexAttribBinding");
    if (!g_real.glVertexAttribBinding && getProcFn) g_real.glVertexAttribBinding = (PFN_glVertexAttribBinding)getProcFn("glVertexAttribBinding");
    g_real.glVertexAttribDivisor = (PFN_glVertexAttribDivisor)GetProcAddress(mod, "glVertexAttribDivisor");
    if (!g_real.glVertexAttribDivisor && getProcFn) g_real.glVertexAttribDivisor = (PFN_glVertexAttribDivisor)getProcFn("glVertexAttribDivisor");
    g_real.glVertexAttribFormat = (PFN_glVertexAttribFormat)GetProcAddress(mod, "glVertexAttribFormat");
    if (!g_real.glVertexAttribFormat && getProcFn) g_real.glVertexAttribFormat = (PFN_glVertexAttribFormat)getProcFn("glVertexAttribFormat");
    g_real.glVertexAttribI1i = (PFN_glVertexAttribI1i)GetProcAddress(mod, "glVertexAttribI1i");
    if (!g_real.glVertexAttribI1i && getProcFn) g_real.glVertexAttribI1i = (PFN_glVertexAttribI1i)getProcFn("glVertexAttribI1i");
    g_real.glVertexAttribI1ui = (PFN_glVertexAttribI1ui)GetProcAddress(mod, "glVertexAttribI1ui");
    if (!g_real.glVertexAttribI1ui && getProcFn) g_real.glVertexAttribI1ui = (PFN_glVertexAttribI1ui)getProcFn("glVertexAttribI1ui");
    g_real.glVertexAttribI2i = (PFN_glVertexAttribI2i)GetProcAddress(mod, "glVertexAttribI2i");
    if (!g_real.glVertexAttribI2i && getProcFn) g_real.glVertexAttribI2i = (PFN_glVertexAttribI2i)getProcFn("glVertexAttribI2i");
    g_real.glVertexAttribI2ui = (PFN_glVertexAttribI2ui)GetProcAddress(mod, "glVertexAttribI2ui");
    if (!g_real.glVertexAttribI2ui && getProcFn) g_real.glVertexAttribI2ui = (PFN_glVertexAttribI2ui)getProcFn("glVertexAttribI2ui");
    g_real.glVertexAttribI3i = (PFN_glVertexAttribI3i)GetProcAddress(mod, "glVertexAttribI3i");
    if (!g_real.glVertexAttribI3i && getProcFn) g_real.glVertexAttribI3i = (PFN_glVertexAttribI3i)getProcFn("glVertexAttribI3i");
    g_real.glVertexAttribI3ui = (PFN_glVertexAttribI3ui)GetProcAddress(mod, "glVertexAttribI3ui");
    if (!g_real.glVertexAttribI3ui && getProcFn) g_real.glVertexAttribI3ui = (PFN_glVertexAttribI3ui)getProcFn("glVertexAttribI3ui");
    g_real.glVertexAttribI4i = (PFN_glVertexAttribI4i)GetProcAddress(mod, "glVertexAttribI4i");
    if (!g_real.glVertexAttribI4i && getProcFn) g_real.glVertexAttribI4i = (PFN_glVertexAttribI4i)getProcFn("glVertexAttribI4i");
    g_real.glVertexAttribI4ui = (PFN_glVertexAttribI4ui)GetProcAddress(mod, "glVertexAttribI4ui");
    if (!g_real.glVertexAttribI4ui && getProcFn) g_real.glVertexAttribI4ui = (PFN_glVertexAttribI4ui)getProcFn("glVertexAttribI4ui");
    g_real.glVertexAttribIFormat = (PFN_glVertexAttribIFormat)GetProcAddress(mod, "glVertexAttribIFormat");
    if (!g_real.glVertexAttribIFormat && getProcFn) g_real.glVertexAttribIFormat = (PFN_glVertexAttribIFormat)getProcFn("glVertexAttribIFormat");
    g_real.glVertexAttribL1d = (PFN_glVertexAttribL1d)GetProcAddress(mod, "glVertexAttribL1d");
    if (!g_real.glVertexAttribL1d && getProcFn) g_real.glVertexAttribL1d = (PFN_glVertexAttribL1d)getProcFn("glVertexAttribL1d");
    g_real.glVertexAttribL2d = (PFN_glVertexAttribL2d)GetProcAddress(mod, "glVertexAttribL2d");
    if (!g_real.glVertexAttribL2d && getProcFn) g_real.glVertexAttribL2d = (PFN_glVertexAttribL2d)getProcFn("glVertexAttribL2d");
    g_real.glVertexAttribL3d = (PFN_glVertexAttribL3d)GetProcAddress(mod, "glVertexAttribL3d");
    if (!g_real.glVertexAttribL3d && getProcFn) g_real.glVertexAttribL3d = (PFN_glVertexAttribL3d)getProcFn("glVertexAttribL3d");
    g_real.glVertexAttribL4d = (PFN_glVertexAttribL4d)GetProcAddress(mod, "glVertexAttribL4d");
    if (!g_real.glVertexAttribL4d && getProcFn) g_real.glVertexAttribL4d = (PFN_glVertexAttribL4d)getProcFn("glVertexAttribL4d");
    g_real.glVertexAttribLFormat = (PFN_glVertexAttribLFormat)GetProcAddress(mod, "glVertexAttribLFormat");
    if (!g_real.glVertexAttribLFormat && getProcFn) g_real.glVertexAttribLFormat = (PFN_glVertexAttribLFormat)getProcFn("glVertexAttribLFormat");
    g_real.glVertexAttribP1ui = (PFN_glVertexAttribP1ui)GetProcAddress(mod, "glVertexAttribP1ui");
    if (!g_real.glVertexAttribP1ui && getProcFn) g_real.glVertexAttribP1ui = (PFN_glVertexAttribP1ui)getProcFn("glVertexAttribP1ui");
    g_real.glVertexAttribP2ui = (PFN_glVertexAttribP2ui)GetProcAddress(mod, "glVertexAttribP2ui");
    if (!g_real.glVertexAttribP2ui && getProcFn) g_real.glVertexAttribP2ui = (PFN_glVertexAttribP2ui)getProcFn("glVertexAttribP2ui");
    g_real.glVertexAttribP3ui = (PFN_glVertexAttribP3ui)GetProcAddress(mod, "glVertexAttribP3ui");
    if (!g_real.glVertexAttribP3ui && getProcFn) g_real.glVertexAttribP3ui = (PFN_glVertexAttribP3ui)getProcFn("glVertexAttribP3ui");
    g_real.glVertexAttribP4ui = (PFN_glVertexAttribP4ui)GetProcAddress(mod, "glVertexAttribP4ui");
    if (!g_real.glVertexAttribP4ui && getProcFn) g_real.glVertexAttribP4ui = (PFN_glVertexAttribP4ui)getProcFn("glVertexAttribP4ui");
    g_real.glVertexBindingDivisor = (PFN_glVertexBindingDivisor)GetProcAddress(mod, "glVertexBindingDivisor");
    if (!g_real.glVertexBindingDivisor && getProcFn) g_real.glVertexBindingDivisor = (PFN_glVertexBindingDivisor)getProcFn("glVertexBindingDivisor");
    g_real.glVertexP2ui = (PFN_glVertexP2ui)GetProcAddress(mod, "glVertexP2ui");
    if (!g_real.glVertexP2ui && getProcFn) g_real.glVertexP2ui = (PFN_glVertexP2ui)getProcFn("glVertexP2ui");
    g_real.glVertexP3ui = (PFN_glVertexP3ui)GetProcAddress(mod, "glVertexP3ui");
    if (!g_real.glVertexP3ui && getProcFn) g_real.glVertexP3ui = (PFN_glVertexP3ui)getProcFn("glVertexP3ui");
    g_real.glVertexP4ui = (PFN_glVertexP4ui)GetProcAddress(mod, "glVertexP4ui");
    if (!g_real.glVertexP4ui && getProcFn) g_real.glVertexP4ui = (PFN_glVertexP4ui)getProcFn("glVertexP4ui");
    g_real.glViewportIndexedf = (PFN_glViewportIndexedf)GetProcAddress(mod, "glViewportIndexedf");
    if (!g_real.glViewportIndexedf && getProcFn) g_real.glViewportIndexedf = (PFN_glViewportIndexedf)getProcFn("glViewportIndexedf");
    g_real.glWaitSync = (PFN_glWaitSync)GetProcAddress(mod, "glWaitSync");
    if (!g_real.glWaitSync && getProcFn) g_real.glWaitSync = (PFN_glWaitSync)getProcFn("glWaitSync");
    g_real.glWindowPos2d = (PFN_glWindowPos2d)GetProcAddress(mod, "glWindowPos2d");
    if (!g_real.glWindowPos2d && getProcFn) g_real.glWindowPos2d = (PFN_glWindowPos2d)getProcFn("glWindowPos2d");
    g_real.glWindowPos2f = (PFN_glWindowPos2f)GetProcAddress(mod, "glWindowPos2f");
    if (!g_real.glWindowPos2f && getProcFn) g_real.glWindowPos2f = (PFN_glWindowPos2f)getProcFn("glWindowPos2f");
    g_real.glWindowPos2i = (PFN_glWindowPos2i)GetProcAddress(mod, "glWindowPos2i");
    if (!g_real.glWindowPos2i && getProcFn) g_real.glWindowPos2i = (PFN_glWindowPos2i)getProcFn("glWindowPos2i");
    g_real.glWindowPos2s = (PFN_glWindowPos2s)GetProcAddress(mod, "glWindowPos2s");
    if (!g_real.glWindowPos2s && getProcFn) g_real.glWindowPos2s = (PFN_glWindowPos2s)getProcFn("glWindowPos2s");
    g_real.glWindowPos3d = (PFN_glWindowPos3d)GetProcAddress(mod, "glWindowPos3d");
    if (!g_real.glWindowPos3d && getProcFn) g_real.glWindowPos3d = (PFN_glWindowPos3d)getProcFn("glWindowPos3d");
    g_real.glWindowPos3f = (PFN_glWindowPos3f)GetProcAddress(mod, "glWindowPos3f");
    if (!g_real.glWindowPos3f && getProcFn) g_real.glWindowPos3f = (PFN_glWindowPos3f)getProcFn("glWindowPos3f");
    g_real.glWindowPos3i = (PFN_glWindowPos3i)GetProcAddress(mod, "glWindowPos3i");
    if (!g_real.glWindowPos3i && getProcFn) g_real.glWindowPos3i = (PFN_glWindowPos3i)getProcFn("glWindowPos3i");
    g_real.glWindowPos3s = (PFN_glWindowPos3s)GetProcAddress(mod, "glWindowPos3s");
    if (!g_real.glWindowPos3s && getProcFn) g_real.glWindowPos3s = (PFN_glWindowPos3s)getProcFn("glWindowPos3s");
    g_real.glClearBufferfv = (PFN_glClearBufferfv)GetProcAddress(mod, "glClearBufferfv");
    if (!g_real.glClearBufferfv && getProcFn) g_real.glClearBufferfv = (PFN_glClearBufferfv)getProcFn("glClearBufferfv");
    g_real.glCreateBuffers = (PFN_glCreateBuffers)GetProcAddress(mod, "glCreateBuffers");
    if (!g_real.glCreateBuffers && getProcFn) g_real.glCreateBuffers = (PFN_glCreateBuffers)getProcFn("glCreateBuffers");
    g_real.glCreateFramebuffers = (PFN_glCreateFramebuffers)GetProcAddress(mod, "glCreateFramebuffers");
    if (!g_real.glCreateFramebuffers && getProcFn) g_real.glCreateFramebuffers = (PFN_glCreateFramebuffers)getProcFn("glCreateFramebuffers");
    g_real.glCreateRenderbuffers = (PFN_glCreateRenderbuffers)GetProcAddress(mod, "glCreateRenderbuffers");
    if (!g_real.glCreateRenderbuffers && getProcFn) g_real.glCreateRenderbuffers = (PFN_glCreateRenderbuffers)getProcFn("glCreateRenderbuffers");
    g_real.glCreateTextures = (PFN_glCreateTextures)GetProcAddress(mod, "glCreateTextures");
    if (!g_real.glCreateTextures && getProcFn) g_real.glCreateTextures = (PFN_glCreateTextures)getProcFn("glCreateTextures");
    g_real.glCreateVertexArrays = (PFN_glCreateVertexArrays)GetProcAddress(mod, "glCreateVertexArrays");
    if (!g_real.glCreateVertexArrays && getProcFn) g_real.glCreateVertexArrays = (PFN_glCreateVertexArrays)getProcFn("glCreateVertexArrays");
    g_real.glDebugMessageInsert = (PFN_glDebugMessageInsert)GetProcAddress(mod, "glDebugMessageInsert");
    if (!g_real.glDebugMessageInsert && getProcFn) g_real.glDebugMessageInsert = (PFN_glDebugMessageInsert)getProcFn("glDebugMessageInsert");
    g_real.glGetProgramInfoLog = (PFN_glGetProgramInfoLog)GetProcAddress(mod, "glGetProgramInfoLog");
    if (!g_real.glGetProgramInfoLog && getProcFn) g_real.glGetProgramInfoLog = (PFN_glGetProgramInfoLog)getProcFn("glGetProgramInfoLog");
    g_real.glGetShaderInfoLog = (PFN_glGetShaderInfoLog)GetProcAddress(mod, "glGetShaderInfoLog");
    if (!g_real.glGetShaderInfoLog && getProcFn) g_real.glGetShaderInfoLog = (PFN_glGetShaderInfoLog)getProcFn("glGetShaderInfoLog");
    g_real.glNamedBufferStorage = (PFN_glNamedBufferStorage)GetProcAddress(mod, "glNamedBufferStorage");
    if (!g_real.glNamedBufferStorage && getProcFn) g_real.glNamedBufferStorage = (PFN_glNamedBufferStorage)getProcFn("glNamedBufferStorage");
    g_real.glNamedBufferSubData = (PFN_glNamedBufferSubData)GetProcAddress(mod, "glNamedBufferSubData");
    if (!g_real.glNamedBufferSubData && getProcFn) g_real.glNamedBufferSubData = (PFN_glNamedBufferSubData)getProcFn("glNamedBufferSubData");
    g_real.glNamedFramebufferDrawBuffers = (PFN_glNamedFramebufferDrawBuffers)GetProcAddress(mod, "glNamedFramebufferDrawBuffers");
    if (!g_real.glNamedFramebufferDrawBuffers && getProcFn) g_real.glNamedFramebufferDrawBuffers = (PFN_glNamedFramebufferDrawBuffers)getProcFn("glNamedFramebufferDrawBuffers");
    g_real.glTextureSubImage2D = (PFN_glTextureSubImage2D)GetProcAddress(mod, "glTextureSubImage2D");
    if (!g_real.glTextureSubImage2D && getProcFn) g_real.glTextureSubImage2D = (PFN_glTextureSubImage2D)getProcFn("glTextureSubImage2D");
    g_real.glTextureSubImage3D = (PFN_glTextureSubImage3D)GetProcAddress(mod, "glTextureSubImage3D");
    if (!g_real.glTextureSubImage3D && getProcFn) g_real.glTextureSubImage3D = (PFN_glTextureSubImage3D)getProcFn("glTextureSubImage3D");
    g_real.wglCreateContext = (PFN_wglCreateContext)GetProcAddress(mod, "wglCreateContext");
    if (!g_real.wglCreateContext && getProcFn) g_real.wglCreateContext = (PFN_wglCreateContext)getProcFn("wglCreateContext");
    g_real.wglDeleteContext = (PFN_wglDeleteContext)GetProcAddress(mod, "wglDeleteContext");
    if (!g_real.wglDeleteContext && getProcFn) g_real.wglDeleteContext = (PFN_wglDeleteContext)getProcFn("wglDeleteContext");
    g_real.wglMakeCurrent = (PFN_wglMakeCurrent)GetProcAddress(mod, "wglMakeCurrent");
    if (!g_real.wglMakeCurrent && getProcFn) g_real.wglMakeCurrent = (PFN_wglMakeCurrent)getProcFn("wglMakeCurrent");
    g_real.wglShareLists = (PFN_wglShareLists)GetProcAddress(mod, "wglShareLists");
    if (!g_real.wglShareLists && getProcFn) g_real.wglShareLists = (PFN_wglShareLists)getProcFn("wglShareLists");
    g_real.wglSwapLayerBuffers = (PFN_wglSwapLayerBuffers)GetProcAddress(mod, "wglSwapLayerBuffers");
    if (!g_real.wglSwapLayerBuffers && getProcFn) g_real.wglSwapLayerBuffers = (PFN_wglSwapLayerBuffers)getProcFn("wglSwapLayerBuffers");
    g_real.wglCreateContextAttribsARB = (PFN_wglCreateContextAttribsARB)GetProcAddress(mod, "wglCreateContextAttribsARB");
    if (!g_real.wglCreateContextAttribsARB && getProcFn) g_real.wglCreateContextAttribsARB = (PFN_wglCreateContextAttribsARB)getProcFn("wglCreateContextAttribsARB");
}

void StoreRealPointer(const char* name, void* addr) {
    if (strcmp(name, "glEnable") == 0) { g_real.glEnable = (PFN_glEnable)addr; return; }
    if (strcmp(name, "glDisable") == 0) { g_real.glDisable = (PFN_glDisable)addr; return; }
    if (strcmp(name, "glClearColor") == 0) { g_real.glClearColor = (PFN_glClearColor)addr; return; }
    if (strcmp(name, "glClearDepth") == 0) { g_real.glClearDepth = (PFN_glClearDepth)addr; return; }
    if (strcmp(name, "glClear") == 0) { g_real.glClear = (PFN_glClear)addr; return; }
    if (strcmp(name, "glBlendFunc") == 0) { g_real.glBlendFunc = (PFN_glBlendFunc)addr; return; }
    if (strcmp(name, "glDepthFunc") == 0) { g_real.glDepthFunc = (PFN_glDepthFunc)addr; return; }
    if (strcmp(name, "glDepthMask") == 0) { g_real.glDepthMask = (PFN_glDepthMask)addr; return; }
    if (strcmp(name, "glCullFace") == 0) { g_real.glCullFace = (PFN_glCullFace)addr; return; }
    if (strcmp(name, "glFrontFace") == 0) { g_real.glFrontFace = (PFN_glFrontFace)addr; return; }
    if (strcmp(name, "glPolygonMode") == 0) { g_real.glPolygonMode = (PFN_glPolygonMode)addr; return; }
    if (strcmp(name, "glLineWidth") == 0) { g_real.glLineWidth = (PFN_glLineWidth)addr; return; }
    if (strcmp(name, "glPointSize") == 0) { g_real.glPointSize = (PFN_glPointSize)addr; return; }
    if (strcmp(name, "glViewport") == 0) { g_real.glViewport = (PFN_glViewport)addr; return; }
    if (strcmp(name, "glScissor") == 0) { g_real.glScissor = (PFN_glScissor)addr; return; }
    if (strcmp(name, "glMatrixMode") == 0) { g_real.glMatrixMode = (PFN_glMatrixMode)addr; return; }
    if (strcmp(name, "glLoadIdentity") == 0) { g_real.glLoadIdentity = (PFN_glLoadIdentity)addr; return; }
    if (strcmp(name, "glPushMatrix") == 0) { g_real.glPushMatrix = (PFN_glPushMatrix)addr; return; }
    if (strcmp(name, "glPopMatrix") == 0) { g_real.glPopMatrix = (PFN_glPopMatrix)addr; return; }
    if (strcmp(name, "glTranslatef") == 0) { g_real.glTranslatef = (PFN_glTranslatef)addr; return; }
    if (strcmp(name, "glRotatef") == 0) { g_real.glRotatef = (PFN_glRotatef)addr; return; }
    if (strcmp(name, "glScalef") == 0) { g_real.glScalef = (PFN_glScalef)addr; return; }
    if (strcmp(name, "glOrtho") == 0) { g_real.glOrtho = (PFN_glOrtho)addr; return; }
    if (strcmp(name, "glFrustum") == 0) { g_real.glFrustum = (PFN_glFrustum)addr; return; }
    if (strcmp(name, "glBegin") == 0) { g_real.glBegin = (PFN_glBegin)addr; return; }
    if (strcmp(name, "glEnd") == 0) { g_real.glEnd = (PFN_glEnd)addr; return; }
    if (strcmp(name, "glVertex2f") == 0) { g_real.glVertex2f = (PFN_glVertex2f)addr; return; }
    if (strcmp(name, "glVertex3f") == 0) { g_real.glVertex3f = (PFN_glVertex3f)addr; return; }
    if (strcmp(name, "glVertex4f") == 0) { g_real.glVertex4f = (PFN_glVertex4f)addr; return; }
    if (strcmp(name, "glColor3f") == 0) { g_real.glColor3f = (PFN_glColor3f)addr; return; }
    if (strcmp(name, "glColor4f") == 0) { g_real.glColor4f = (PFN_glColor4f)addr; return; }
    if (strcmp(name, "glNormal3f") == 0) { g_real.glNormal3f = (PFN_glNormal3f)addr; return; }
    if (strcmp(name, "glTexCoord2f") == 0) { g_real.glTexCoord2f = (PFN_glTexCoord2f)addr; return; }
    if (strcmp(name, "glEnableClientState") == 0) { g_real.glEnableClientState = (PFN_glEnableClientState)addr; return; }
    if (strcmp(name, "glDisableClientState") == 0) { g_real.glDisableClientState = (PFN_glDisableClientState)addr; return; }
    if (strcmp(name, "glGenBuffers") == 0) { g_real.glGenBuffers = (PFN_glGenBuffers)addr; return; }
    if (strcmp(name, "glDeleteBuffers") == 0) { g_real.glDeleteBuffers = (PFN_glDeleteBuffers)addr; return; }
    if (strcmp(name, "glBindBuffer") == 0) { g_real.glBindBuffer = (PFN_glBindBuffer)addr; return; }
    if (strcmp(name, "glBufferData") == 0) { g_real.glBufferData = (PFN_glBufferData)addr; return; }
    if (strcmp(name, "glBufferSubData") == 0) { g_real.glBufferSubData = (PFN_glBufferSubData)addr; return; }
    if (strcmp(name, "glGenVertexArrays") == 0) { g_real.glGenVertexArrays = (PFN_glGenVertexArrays)addr; return; }
    if (strcmp(name, "glDeleteVertexArrays") == 0) { g_real.glDeleteVertexArrays = (PFN_glDeleteVertexArrays)addr; return; }
    if (strcmp(name, "glBindVertexArray") == 0) { g_real.glBindVertexArray = (PFN_glBindVertexArray)addr; return; }
    if (strcmp(name, "glEnableVertexAttribArray") == 0) { g_real.glEnableVertexAttribArray = (PFN_glEnableVertexAttribArray)addr; return; }
    if (strcmp(name, "glDisableVertexAttribArray") == 0) { g_real.glDisableVertexAttribArray = (PFN_glDisableVertexAttribArray)addr; return; }
    if (strcmp(name, "glVertexAttribPointer") == 0) { g_real.glVertexAttribPointer = (PFN_glVertexAttribPointer)addr; return; }
    if (strcmp(name, "glVertexPointer") == 0) { g_real.glVertexPointer = (PFN_glVertexPointer)addr; return; }
    if (strcmp(name, "glColorPointer") == 0) { g_real.glColorPointer = (PFN_glColorPointer)addr; return; }
    if (strcmp(name, "glTexCoordPointer") == 0) { g_real.glTexCoordPointer = (PFN_glTexCoordPointer)addr; return; }
    if (strcmp(name, "glNormalPointer") == 0) { g_real.glNormalPointer = (PFN_glNormalPointer)addr; return; }
    if (strcmp(name, "glGenTextures") == 0) { g_real.glGenTextures = (PFN_glGenTextures)addr; return; }
    if (strcmp(name, "glDeleteTextures") == 0) { g_real.glDeleteTextures = (PFN_glDeleteTextures)addr; return; }
    if (strcmp(name, "glBindTexture") == 0) { g_real.glBindTexture = (PFN_glBindTexture)addr; return; }
    if (strcmp(name, "glActiveTexture") == 0) { g_real.glActiveTexture = (PFN_glActiveTexture)addr; return; }
    if (strcmp(name, "glTexParameteri") == 0) { g_real.glTexParameteri = (PFN_glTexParameteri)addr; return; }
    if (strcmp(name, "glTexParameterf") == 0) { g_real.glTexParameterf = (PFN_glTexParameterf)addr; return; }
    if (strcmp(name, "glPixelStorei") == 0) { g_real.glPixelStorei = (PFN_glPixelStorei)addr; return; }
    if (strcmp(name, "glTexImage2D") == 0) { g_real.glTexImage2D = (PFN_glTexImage2D)addr; return; }
    if (strcmp(name, "glTexSubImage2D") == 0) { g_real.glTexSubImage2D = (PFN_glTexSubImage2D)addr; return; }
    if (strcmp(name, "glGenerateMipmap") == 0) { g_real.glGenerateMipmap = (PFN_glGenerateMipmap)addr; return; }
    if (strcmp(name, "glCreateShader") == 0) { g_real.glCreateShader = (PFN_glCreateShader)addr; return; }
    if (strcmp(name, "glDeleteShader") == 0) { g_real.glDeleteShader = (PFN_glDeleteShader)addr; return; }
    if (strcmp(name, "glShaderSource") == 0) { g_real.glShaderSource = (PFN_glShaderSource)addr; return; }
    if (strcmp(name, "glCompileShader") == 0) { g_real.glCompileShader = (PFN_glCompileShader)addr; return; }
    if (strcmp(name, "glCreateProgram") == 0) { g_real.glCreateProgram = (PFN_glCreateProgram)addr; return; }
    if (strcmp(name, "glDeleteProgram") == 0) { g_real.glDeleteProgram = (PFN_glDeleteProgram)addr; return; }
    if (strcmp(name, "glAttachShader") == 0) { g_real.glAttachShader = (PFN_glAttachShader)addr; return; }
    if (strcmp(name, "glDetachShader") == 0) { g_real.glDetachShader = (PFN_glDetachShader)addr; return; }
    if (strcmp(name, "glLinkProgram") == 0) { g_real.glLinkProgram = (PFN_glLinkProgram)addr; return; }
    if (strcmp(name, "glUseProgram") == 0) { g_real.glUseProgram = (PFN_glUseProgram)addr; return; }
    if (strcmp(name, "glBindAttribLocation") == 0) { g_real.glBindAttribLocation = (PFN_glBindAttribLocation)addr; return; }
    if (strcmp(name, "glGetUniformLocation") == 0) { g_real.glGetUniformLocation = (PFN_glGetUniformLocation)addr; return; }
    if (strcmp(name, "glGetAttribLocation") == 0) { g_real.glGetAttribLocation = (PFN_glGetAttribLocation)addr; return; }
    if (strcmp(name, "glUniform1i") == 0) { g_real.glUniform1i = (PFN_glUniform1i)addr; return; }
    if (strcmp(name, "glUniform1f") == 0) { g_real.glUniform1f = (PFN_glUniform1f)addr; return; }
    if (strcmp(name, "glUniform2f") == 0) { g_real.glUniform2f = (PFN_glUniform2f)addr; return; }
    if (strcmp(name, "glUniform3f") == 0) { g_real.glUniform3f = (PFN_glUniform3f)addr; return; }
    if (strcmp(name, "glUniform4f") == 0) { g_real.glUniform4f = (PFN_glUniform4f)addr; return; }
    if (strcmp(name, "glUniformMatrix4fv") == 0) { g_real.glUniformMatrix4fv = (PFN_glUniformMatrix4fv)addr; return; }
    if (strcmp(name, "glUniformMatrix3fv") == 0) { g_real.glUniformMatrix3fv = (PFN_glUniformMatrix3fv)addr; return; }
    if (strcmp(name, "glGenFramebuffers") == 0) { g_real.glGenFramebuffers = (PFN_glGenFramebuffers)addr; return; }
    if (strcmp(name, "glDeleteFramebuffers") == 0) { g_real.glDeleteFramebuffers = (PFN_glDeleteFramebuffers)addr; return; }
    if (strcmp(name, "glBindFramebuffer") == 0) { g_real.glBindFramebuffer = (PFN_glBindFramebuffer)addr; return; }
    if (strcmp(name, "glFramebufferTexture2D") == 0) { g_real.glFramebufferTexture2D = (PFN_glFramebufferTexture2D)addr; return; }
    if (strcmp(name, "glGenRenderbuffers") == 0) { g_real.glGenRenderbuffers = (PFN_glGenRenderbuffers)addr; return; }
    if (strcmp(name, "glDeleteRenderbuffers") == 0) { g_real.glDeleteRenderbuffers = (PFN_glDeleteRenderbuffers)addr; return; }
    if (strcmp(name, "glBindRenderbuffer") == 0) { g_real.glBindRenderbuffer = (PFN_glBindRenderbuffer)addr; return; }
    if (strcmp(name, "glRenderbufferStorage") == 0) { g_real.glRenderbufferStorage = (PFN_glRenderbufferStorage)addr; return; }
    if (strcmp(name, "glFramebufferRenderbuffer") == 0) { g_real.glFramebufferRenderbuffer = (PFN_glFramebufferRenderbuffer)addr; return; }
    if (strcmp(name, "glCheckFramebufferStatus") == 0) { g_real.glCheckFramebufferStatus = (PFN_glCheckFramebufferStatus)addr; return; }
    if (strcmp(name, "glDrawArrays") == 0) { g_real.glDrawArrays = (PFN_glDrawArrays)addr; return; }
    if (strcmp(name, "glDrawElements") == 0) { g_real.glDrawElements = (PFN_glDrawElements)addr; return; }
    if (strcmp(name, "glDrawArraysInstanced") == 0) { g_real.glDrawArraysInstanced = (PFN_glDrawArraysInstanced)addr; return; }
    if (strcmp(name, "glDrawElementsInstanced") == 0) { g_real.glDrawElementsInstanced = (PFN_glDrawElementsInstanced)addr; return; }
    if (strcmp(name, "glGetString") == 0) { g_real.glGetString = (PFN_glGetString)addr; return; }
    if (strcmp(name, "glAccum") == 0) { g_real.glAccum = (PFN_glAccum)addr; return; }
    if (strcmp(name, "glAlphaFunc") == 0) { g_real.glAlphaFunc = (PFN_glAlphaFunc)addr; return; }
    if (strcmp(name, "glAreTexturesResident") == 0) { g_real.glAreTexturesResident = (PFN_glAreTexturesResident)addr; return; }
    if (strcmp(name, "glArrayElement") == 0) { g_real.glArrayElement = (PFN_glArrayElement)addr; return; }
    if (strcmp(name, "glBitmap") == 0) { g_real.glBitmap = (PFN_glBitmap)addr; return; }
    if (strcmp(name, "glCallList") == 0) { g_real.glCallList = (PFN_glCallList)addr; return; }
    if (strcmp(name, "glCallLists") == 0) { g_real.glCallLists = (PFN_glCallLists)addr; return; }
    if (strcmp(name, "glClearAccum") == 0) { g_real.glClearAccum = (PFN_glClearAccum)addr; return; }
    if (strcmp(name, "glClearIndex") == 0) { g_real.glClearIndex = (PFN_glClearIndex)addr; return; }
    if (strcmp(name, "glClearStencil") == 0) { g_real.glClearStencil = (PFN_glClearStencil)addr; return; }
    if (strcmp(name, "glClipPlane") == 0) { g_real.glClipPlane = (PFN_glClipPlane)addr; return; }
    if (strcmp(name, "glColor3b") == 0) { g_real.glColor3b = (PFN_glColor3b)addr; return; }
    if (strcmp(name, "glColor3bv") == 0) { g_real.glColor3bv = (PFN_glColor3bv)addr; return; }
    if (strcmp(name, "glColor3d") == 0) { g_real.glColor3d = (PFN_glColor3d)addr; return; }
    if (strcmp(name, "glColor3dv") == 0) { g_real.glColor3dv = (PFN_glColor3dv)addr; return; }
    if (strcmp(name, "glColor3fv") == 0) { g_real.glColor3fv = (PFN_glColor3fv)addr; return; }
    if (strcmp(name, "glColor3i") == 0) { g_real.glColor3i = (PFN_glColor3i)addr; return; }
    if (strcmp(name, "glColor3iv") == 0) { g_real.glColor3iv = (PFN_glColor3iv)addr; return; }
    if (strcmp(name, "glColor3s") == 0) { g_real.glColor3s = (PFN_glColor3s)addr; return; }
    if (strcmp(name, "glColor3sv") == 0) { g_real.glColor3sv = (PFN_glColor3sv)addr; return; }
    if (strcmp(name, "glColor3ub") == 0) { g_real.glColor3ub = (PFN_glColor3ub)addr; return; }
    if (strcmp(name, "glColor3ubv") == 0) { g_real.glColor3ubv = (PFN_glColor3ubv)addr; return; }
    if (strcmp(name, "glColor3ui") == 0) { g_real.glColor3ui = (PFN_glColor3ui)addr; return; }
    if (strcmp(name, "glColor3uiv") == 0) { g_real.glColor3uiv = (PFN_glColor3uiv)addr; return; }
    if (strcmp(name, "glColor3us") == 0) { g_real.glColor3us = (PFN_glColor3us)addr; return; }
    if (strcmp(name, "glColor3usv") == 0) { g_real.glColor3usv = (PFN_glColor3usv)addr; return; }
    if (strcmp(name, "glColor4b") == 0) { g_real.glColor4b = (PFN_glColor4b)addr; return; }
    if (strcmp(name, "glColor4bv") == 0) { g_real.glColor4bv = (PFN_glColor4bv)addr; return; }
    if (strcmp(name, "glColor4d") == 0) { g_real.glColor4d = (PFN_glColor4d)addr; return; }
    if (strcmp(name, "glColor4dv") == 0) { g_real.glColor4dv = (PFN_glColor4dv)addr; return; }
    if (strcmp(name, "glColor4fv") == 0) { g_real.glColor4fv = (PFN_glColor4fv)addr; return; }
    if (strcmp(name, "glColor4i") == 0) { g_real.glColor4i = (PFN_glColor4i)addr; return; }
    if (strcmp(name, "glColor4iv") == 0) { g_real.glColor4iv = (PFN_glColor4iv)addr; return; }
    if (strcmp(name, "glColor4s") == 0) { g_real.glColor4s = (PFN_glColor4s)addr; return; }
    if (strcmp(name, "glColor4sv") == 0) { g_real.glColor4sv = (PFN_glColor4sv)addr; return; }
    if (strcmp(name, "glColor4ub") == 0) { g_real.glColor4ub = (PFN_glColor4ub)addr; return; }
    if (strcmp(name, "glColor4ubv") == 0) { g_real.glColor4ubv = (PFN_glColor4ubv)addr; return; }
    if (strcmp(name, "glColor4ui") == 0) { g_real.glColor4ui = (PFN_glColor4ui)addr; return; }
    if (strcmp(name, "glColor4uiv") == 0) { g_real.glColor4uiv = (PFN_glColor4uiv)addr; return; }
    if (strcmp(name, "glColor4us") == 0) { g_real.glColor4us = (PFN_glColor4us)addr; return; }
    if (strcmp(name, "glColor4usv") == 0) { g_real.glColor4usv = (PFN_glColor4usv)addr; return; }
    if (strcmp(name, "glColorMask") == 0) { g_real.glColorMask = (PFN_glColorMask)addr; return; }
    if (strcmp(name, "glColorMaterial") == 0) { g_real.glColorMaterial = (PFN_glColorMaterial)addr; return; }
    if (strcmp(name, "glCopyPixels") == 0) { g_real.glCopyPixels = (PFN_glCopyPixels)addr; return; }
    if (strcmp(name, "glCopyTexImage1D") == 0) { g_real.glCopyTexImage1D = (PFN_glCopyTexImage1D)addr; return; }
    if (strcmp(name, "glCopyTexImage2D") == 0) { g_real.glCopyTexImage2D = (PFN_glCopyTexImage2D)addr; return; }
    if (strcmp(name, "glCopyTexSubImage1D") == 0) { g_real.glCopyTexSubImage1D = (PFN_glCopyTexSubImage1D)addr; return; }
    if (strcmp(name, "glCopyTexSubImage2D") == 0) { g_real.glCopyTexSubImage2D = (PFN_glCopyTexSubImage2D)addr; return; }
    if (strcmp(name, "glDeleteLists") == 0) { g_real.glDeleteLists = (PFN_glDeleteLists)addr; return; }
    if (strcmp(name, "glDepthRange") == 0) { g_real.glDepthRange = (PFN_glDepthRange)addr; return; }
    if (strcmp(name, "glDrawBuffer") == 0) { g_real.glDrawBuffer = (PFN_glDrawBuffer)addr; return; }
    if (strcmp(name, "glDrawPixels") == 0) { g_real.glDrawPixels = (PFN_glDrawPixels)addr; return; }
    if (strcmp(name, "glEdgeFlag") == 0) { g_real.glEdgeFlag = (PFN_glEdgeFlag)addr; return; }
    if (strcmp(name, "glEdgeFlagPointer") == 0) { g_real.glEdgeFlagPointer = (PFN_glEdgeFlagPointer)addr; return; }
    if (strcmp(name, "glEdgeFlagv") == 0) { g_real.glEdgeFlagv = (PFN_glEdgeFlagv)addr; return; }
    if (strcmp(name, "glEndList") == 0) { g_real.glEndList = (PFN_glEndList)addr; return; }
    if (strcmp(name, "glEvalCoord1d") == 0) { g_real.glEvalCoord1d = (PFN_glEvalCoord1d)addr; return; }
    if (strcmp(name, "glEvalCoord1dv") == 0) { g_real.glEvalCoord1dv = (PFN_glEvalCoord1dv)addr; return; }
    if (strcmp(name, "glEvalCoord1f") == 0) { g_real.glEvalCoord1f = (PFN_glEvalCoord1f)addr; return; }
    if (strcmp(name, "glEvalCoord1fv") == 0) { g_real.glEvalCoord1fv = (PFN_glEvalCoord1fv)addr; return; }
    if (strcmp(name, "glEvalCoord2d") == 0) { g_real.glEvalCoord2d = (PFN_glEvalCoord2d)addr; return; }
    if (strcmp(name, "glEvalCoord2dv") == 0) { g_real.glEvalCoord2dv = (PFN_glEvalCoord2dv)addr; return; }
    if (strcmp(name, "glEvalCoord2f") == 0) { g_real.glEvalCoord2f = (PFN_glEvalCoord2f)addr; return; }
    if (strcmp(name, "glEvalCoord2fv") == 0) { g_real.glEvalCoord2fv = (PFN_glEvalCoord2fv)addr; return; }
    if (strcmp(name, "glEvalMesh1") == 0) { g_real.glEvalMesh1 = (PFN_glEvalMesh1)addr; return; }
    if (strcmp(name, "glEvalMesh2") == 0) { g_real.glEvalMesh2 = (PFN_glEvalMesh2)addr; return; }
    if (strcmp(name, "glEvalPoint1") == 0) { g_real.glEvalPoint1 = (PFN_glEvalPoint1)addr; return; }
    if (strcmp(name, "glEvalPoint2") == 0) { g_real.glEvalPoint2 = (PFN_glEvalPoint2)addr; return; }
    if (strcmp(name, "glFeedbackBuffer") == 0) { g_real.glFeedbackBuffer = (PFN_glFeedbackBuffer)addr; return; }
    if (strcmp(name, "glFinish") == 0) { g_real.glFinish = (PFN_glFinish)addr; return; }
    if (strcmp(name, "glFlush") == 0) { g_real.glFlush = (PFN_glFlush)addr; return; }
    if (strcmp(name, "glFogf") == 0) { g_real.glFogf = (PFN_glFogf)addr; return; }
    if (strcmp(name, "glFogfv") == 0) { g_real.glFogfv = (PFN_glFogfv)addr; return; }
    if (strcmp(name, "glFogi") == 0) { g_real.glFogi = (PFN_glFogi)addr; return; }
    if (strcmp(name, "glFogiv") == 0) { g_real.glFogiv = (PFN_glFogiv)addr; return; }
    if (strcmp(name, "glGenLists") == 0) { g_real.glGenLists = (PFN_glGenLists)addr; return; }
    if (strcmp(name, "glGetBooleanv") == 0) { g_real.glGetBooleanv = (PFN_glGetBooleanv)addr; return; }
    if (strcmp(name, "glGetClipPlane") == 0) { g_real.glGetClipPlane = (PFN_glGetClipPlane)addr; return; }
    if (strcmp(name, "glGetDoublev") == 0) { g_real.glGetDoublev = (PFN_glGetDoublev)addr; return; }
    if (strcmp(name, "glGetError") == 0) { g_real.glGetError = (PFN_glGetError)addr; return; }
    if (strcmp(name, "glGetFloatv") == 0) { g_real.glGetFloatv = (PFN_glGetFloatv)addr; return; }
    if (strcmp(name, "glGetIntegerv") == 0) { g_real.glGetIntegerv = (PFN_glGetIntegerv)addr; return; }
    if (strcmp(name, "glGetLightfv") == 0) { g_real.glGetLightfv = (PFN_glGetLightfv)addr; return; }
    if (strcmp(name, "glGetLightiv") == 0) { g_real.glGetLightiv = (PFN_glGetLightiv)addr; return; }
    if (strcmp(name, "glGetMapdv") == 0) { g_real.glGetMapdv = (PFN_glGetMapdv)addr; return; }
    if (strcmp(name, "glGetMapfv") == 0) { g_real.glGetMapfv = (PFN_glGetMapfv)addr; return; }
    if (strcmp(name, "glGetMapiv") == 0) { g_real.glGetMapiv = (PFN_glGetMapiv)addr; return; }
    if (strcmp(name, "glGetMaterialfv") == 0) { g_real.glGetMaterialfv = (PFN_glGetMaterialfv)addr; return; }
    if (strcmp(name, "glGetMaterialiv") == 0) { g_real.glGetMaterialiv = (PFN_glGetMaterialiv)addr; return; }
    if (strcmp(name, "glGetPixelMapfv") == 0) { g_real.glGetPixelMapfv = (PFN_glGetPixelMapfv)addr; return; }
    if (strcmp(name, "glGetPixelMapuiv") == 0) { g_real.glGetPixelMapuiv = (PFN_glGetPixelMapuiv)addr; return; }
    if (strcmp(name, "glGetPixelMapusv") == 0) { g_real.glGetPixelMapusv = (PFN_glGetPixelMapusv)addr; return; }
    if (strcmp(name, "glGetPointerv") == 0) { g_real.glGetPointerv = (PFN_glGetPointerv)addr; return; }
    if (strcmp(name, "glGetPolygonStipple") == 0) { g_real.glGetPolygonStipple = (PFN_glGetPolygonStipple)addr; return; }
    if (strcmp(name, "glGetTexEnvfv") == 0) { g_real.glGetTexEnvfv = (PFN_glGetTexEnvfv)addr; return; }
    if (strcmp(name, "glGetTexEnviv") == 0) { g_real.glGetTexEnviv = (PFN_glGetTexEnviv)addr; return; }
    if (strcmp(name, "glGetTexGendv") == 0) { g_real.glGetTexGendv = (PFN_glGetTexGendv)addr; return; }
    if (strcmp(name, "glGetTexGenfv") == 0) { g_real.glGetTexGenfv = (PFN_glGetTexGenfv)addr; return; }
    if (strcmp(name, "glGetTexGeniv") == 0) { g_real.glGetTexGeniv = (PFN_glGetTexGeniv)addr; return; }
    if (strcmp(name, "glGetTexImage") == 0) { g_real.glGetTexImage = (PFN_glGetTexImage)addr; return; }
    if (strcmp(name, "glGetTexLevelParameterfv") == 0) { g_real.glGetTexLevelParameterfv = (PFN_glGetTexLevelParameterfv)addr; return; }
    if (strcmp(name, "glGetTexLevelParameteriv") == 0) { g_real.glGetTexLevelParameteriv = (PFN_glGetTexLevelParameteriv)addr; return; }
    if (strcmp(name, "glGetTexParameterfv") == 0) { g_real.glGetTexParameterfv = (PFN_glGetTexParameterfv)addr; return; }
    if (strcmp(name, "glGetTexParameteriv") == 0) { g_real.glGetTexParameteriv = (PFN_glGetTexParameteriv)addr; return; }
    if (strcmp(name, "glHint") == 0) { g_real.glHint = (PFN_glHint)addr; return; }
    if (strcmp(name, "glIndexMask") == 0) { g_real.glIndexMask = (PFN_glIndexMask)addr; return; }
    if (strcmp(name, "glIndexPointer") == 0) { g_real.glIndexPointer = (PFN_glIndexPointer)addr; return; }
    if (strcmp(name, "glIndexd") == 0) { g_real.glIndexd = (PFN_glIndexd)addr; return; }
    if (strcmp(name, "glIndexdv") == 0) { g_real.glIndexdv = (PFN_glIndexdv)addr; return; }
    if (strcmp(name, "glIndexf") == 0) { g_real.glIndexf = (PFN_glIndexf)addr; return; }
    if (strcmp(name, "glIndexfv") == 0) { g_real.glIndexfv = (PFN_glIndexfv)addr; return; }
    if (strcmp(name, "glIndexi") == 0) { g_real.glIndexi = (PFN_glIndexi)addr; return; }
    if (strcmp(name, "glIndexiv") == 0) { g_real.glIndexiv = (PFN_glIndexiv)addr; return; }
    if (strcmp(name, "glIndexs") == 0) { g_real.glIndexs = (PFN_glIndexs)addr; return; }
    if (strcmp(name, "glIndexsv") == 0) { g_real.glIndexsv = (PFN_glIndexsv)addr; return; }
    if (strcmp(name, "glIndexub") == 0) { g_real.glIndexub = (PFN_glIndexub)addr; return; }
    if (strcmp(name, "glIndexubv") == 0) { g_real.glIndexubv = (PFN_glIndexubv)addr; return; }
    if (strcmp(name, "glInitNames") == 0) { g_real.glInitNames = (PFN_glInitNames)addr; return; }
    if (strcmp(name, "glInterleavedArrays") == 0) { g_real.glInterleavedArrays = (PFN_glInterleavedArrays)addr; return; }
    if (strcmp(name, "glIsEnabled") == 0) { g_real.glIsEnabled = (PFN_glIsEnabled)addr; return; }
    if (strcmp(name, "glIsList") == 0) { g_real.glIsList = (PFN_glIsList)addr; return; }
    if (strcmp(name, "glIsTexture") == 0) { g_real.glIsTexture = (PFN_glIsTexture)addr; return; }
    if (strcmp(name, "glLightModelf") == 0) { g_real.glLightModelf = (PFN_glLightModelf)addr; return; }
    if (strcmp(name, "glLightModelfv") == 0) { g_real.glLightModelfv = (PFN_glLightModelfv)addr; return; }
    if (strcmp(name, "glLightModeli") == 0) { g_real.glLightModeli = (PFN_glLightModeli)addr; return; }
    if (strcmp(name, "glLightModeliv") == 0) { g_real.glLightModeliv = (PFN_glLightModeliv)addr; return; }
    if (strcmp(name, "glLightf") == 0) { g_real.glLightf = (PFN_glLightf)addr; return; }
    if (strcmp(name, "glLightfv") == 0) { g_real.glLightfv = (PFN_glLightfv)addr; return; }
    if (strcmp(name, "glLighti") == 0) { g_real.glLighti = (PFN_glLighti)addr; return; }
    if (strcmp(name, "glLightiv") == 0) { g_real.glLightiv = (PFN_glLightiv)addr; return; }
    if (strcmp(name, "glLineStipple") == 0) { g_real.glLineStipple = (PFN_glLineStipple)addr; return; }
    if (strcmp(name, "glListBase") == 0) { g_real.glListBase = (PFN_glListBase)addr; return; }
    if (strcmp(name, "glLoadMatrixd") == 0) { g_real.glLoadMatrixd = (PFN_glLoadMatrixd)addr; return; }
    if (strcmp(name, "glLoadMatrixf") == 0) { g_real.glLoadMatrixf = (PFN_glLoadMatrixf)addr; return; }
    if (strcmp(name, "glLoadName") == 0) { g_real.glLoadName = (PFN_glLoadName)addr; return; }
    if (strcmp(name, "glLogicOp") == 0) { g_real.glLogicOp = (PFN_glLogicOp)addr; return; }
    if (strcmp(name, "glMap1d") == 0) { g_real.glMap1d = (PFN_glMap1d)addr; return; }
    if (strcmp(name, "glMap1f") == 0) { g_real.glMap1f = (PFN_glMap1f)addr; return; }
    if (strcmp(name, "glMap2d") == 0) { g_real.glMap2d = (PFN_glMap2d)addr; return; }
    if (strcmp(name, "glMap2f") == 0) { g_real.glMap2f = (PFN_glMap2f)addr; return; }
    if (strcmp(name, "glMapGrid1d") == 0) { g_real.glMapGrid1d = (PFN_glMapGrid1d)addr; return; }
    if (strcmp(name, "glMapGrid1f") == 0) { g_real.glMapGrid1f = (PFN_glMapGrid1f)addr; return; }
    if (strcmp(name, "glMapGrid2d") == 0) { g_real.glMapGrid2d = (PFN_glMapGrid2d)addr; return; }
    if (strcmp(name, "glMapGrid2f") == 0) { g_real.glMapGrid2f = (PFN_glMapGrid2f)addr; return; }
    if (strcmp(name, "glMaterialf") == 0) { g_real.glMaterialf = (PFN_glMaterialf)addr; return; }
    if (strcmp(name, "glMaterialfv") == 0) { g_real.glMaterialfv = (PFN_glMaterialfv)addr; return; }
    if (strcmp(name, "glMateriali") == 0) { g_real.glMateriali = (PFN_glMateriali)addr; return; }
    if (strcmp(name, "glMaterialiv") == 0) { g_real.glMaterialiv = (PFN_glMaterialiv)addr; return; }
    if (strcmp(name, "glMultMatrixd") == 0) { g_real.glMultMatrixd = (PFN_glMultMatrixd)addr; return; }
    if (strcmp(name, "glMultMatrixf") == 0) { g_real.glMultMatrixf = (PFN_glMultMatrixf)addr; return; }
    if (strcmp(name, "glNewList") == 0) { g_real.glNewList = (PFN_glNewList)addr; return; }
    if (strcmp(name, "glNormal3b") == 0) { g_real.glNormal3b = (PFN_glNormal3b)addr; return; }
    if (strcmp(name, "glNormal3bv") == 0) { g_real.glNormal3bv = (PFN_glNormal3bv)addr; return; }
    if (strcmp(name, "glNormal3d") == 0) { g_real.glNormal3d = (PFN_glNormal3d)addr; return; }
    if (strcmp(name, "glNormal3dv") == 0) { g_real.glNormal3dv = (PFN_glNormal3dv)addr; return; }
    if (strcmp(name, "glNormal3fv") == 0) { g_real.glNormal3fv = (PFN_glNormal3fv)addr; return; }
    if (strcmp(name, "glNormal3i") == 0) { g_real.glNormal3i = (PFN_glNormal3i)addr; return; }
    if (strcmp(name, "glNormal3iv") == 0) { g_real.glNormal3iv = (PFN_glNormal3iv)addr; return; }
    if (strcmp(name, "glNormal3s") == 0) { g_real.glNormal3s = (PFN_glNormal3s)addr; return; }
    if (strcmp(name, "glNormal3sv") == 0) { g_real.glNormal3sv = (PFN_glNormal3sv)addr; return; }
    if (strcmp(name, "glPassThrough") == 0) { g_real.glPassThrough = (PFN_glPassThrough)addr; return; }
    if (strcmp(name, "glPixelMapfv") == 0) { g_real.glPixelMapfv = (PFN_glPixelMapfv)addr; return; }
    if (strcmp(name, "glPixelMapuiv") == 0) { g_real.glPixelMapuiv = (PFN_glPixelMapuiv)addr; return; }
    if (strcmp(name, "glPixelMapusv") == 0) { g_real.glPixelMapusv = (PFN_glPixelMapusv)addr; return; }
    if (strcmp(name, "glPixelStoref") == 0) { g_real.glPixelStoref = (PFN_glPixelStoref)addr; return; }
    if (strcmp(name, "glPixelTransferf") == 0) { g_real.glPixelTransferf = (PFN_glPixelTransferf)addr; return; }
    if (strcmp(name, "glPixelTransferi") == 0) { g_real.glPixelTransferi = (PFN_glPixelTransferi)addr; return; }
    if (strcmp(name, "glPixelZoom") == 0) { g_real.glPixelZoom = (PFN_glPixelZoom)addr; return; }
    if (strcmp(name, "glPolygonOffset") == 0) { g_real.glPolygonOffset = (PFN_glPolygonOffset)addr; return; }
    if (strcmp(name, "glPolygonStipple") == 0) { g_real.glPolygonStipple = (PFN_glPolygonStipple)addr; return; }
    if (strcmp(name, "glPopAttrib") == 0) { g_real.glPopAttrib = (PFN_glPopAttrib)addr; return; }
    if (strcmp(name, "glPopClientAttrib") == 0) { g_real.glPopClientAttrib = (PFN_glPopClientAttrib)addr; return; }
    if (strcmp(name, "glPopName") == 0) { g_real.glPopName = (PFN_glPopName)addr; return; }
    if (strcmp(name, "glPrioritizeTextures") == 0) { g_real.glPrioritizeTextures = (PFN_glPrioritizeTextures)addr; return; }
    if (strcmp(name, "glPushAttrib") == 0) { g_real.glPushAttrib = (PFN_glPushAttrib)addr; return; }
    if (strcmp(name, "glPushClientAttrib") == 0) { g_real.glPushClientAttrib = (PFN_glPushClientAttrib)addr; return; }
    if (strcmp(name, "glPushName") == 0) { g_real.glPushName = (PFN_glPushName)addr; return; }
    if (strcmp(name, "glRasterPos2d") == 0) { g_real.glRasterPos2d = (PFN_glRasterPos2d)addr; return; }
    if (strcmp(name, "glRasterPos2dv") == 0) { g_real.glRasterPos2dv = (PFN_glRasterPos2dv)addr; return; }
    if (strcmp(name, "glRasterPos2f") == 0) { g_real.glRasterPos2f = (PFN_glRasterPos2f)addr; return; }
    if (strcmp(name, "glRasterPos2fv") == 0) { g_real.glRasterPos2fv = (PFN_glRasterPos2fv)addr; return; }
    if (strcmp(name, "glRasterPos2i") == 0) { g_real.glRasterPos2i = (PFN_glRasterPos2i)addr; return; }
    if (strcmp(name, "glRasterPos2iv") == 0) { g_real.glRasterPos2iv = (PFN_glRasterPos2iv)addr; return; }
    if (strcmp(name, "glRasterPos2s") == 0) { g_real.glRasterPos2s = (PFN_glRasterPos2s)addr; return; }
    if (strcmp(name, "glRasterPos2sv") == 0) { g_real.glRasterPos2sv = (PFN_glRasterPos2sv)addr; return; }
    if (strcmp(name, "glRasterPos3d") == 0) { g_real.glRasterPos3d = (PFN_glRasterPos3d)addr; return; }
    if (strcmp(name, "glRasterPos3dv") == 0) { g_real.glRasterPos3dv = (PFN_glRasterPos3dv)addr; return; }
    if (strcmp(name, "glRasterPos3f") == 0) { g_real.glRasterPos3f = (PFN_glRasterPos3f)addr; return; }
    if (strcmp(name, "glRasterPos3fv") == 0) { g_real.glRasterPos3fv = (PFN_glRasterPos3fv)addr; return; }
    if (strcmp(name, "glRasterPos3i") == 0) { g_real.glRasterPos3i = (PFN_glRasterPos3i)addr; return; }
    if (strcmp(name, "glRasterPos3iv") == 0) { g_real.glRasterPos3iv = (PFN_glRasterPos3iv)addr; return; }
    if (strcmp(name, "glRasterPos3s") == 0) { g_real.glRasterPos3s = (PFN_glRasterPos3s)addr; return; }
    if (strcmp(name, "glRasterPos3sv") == 0) { g_real.glRasterPos3sv = (PFN_glRasterPos3sv)addr; return; }
    if (strcmp(name, "glRasterPos4d") == 0) { g_real.glRasterPos4d = (PFN_glRasterPos4d)addr; return; }
    if (strcmp(name, "glRasterPos4dv") == 0) { g_real.glRasterPos4dv = (PFN_glRasterPos4dv)addr; return; }
    if (strcmp(name, "glRasterPos4f") == 0) { g_real.glRasterPos4f = (PFN_glRasterPos4f)addr; return; }
    if (strcmp(name, "glRasterPos4fv") == 0) { g_real.glRasterPos4fv = (PFN_glRasterPos4fv)addr; return; }
    if (strcmp(name, "glRasterPos4i") == 0) { g_real.glRasterPos4i = (PFN_glRasterPos4i)addr; return; }
    if (strcmp(name, "glRasterPos4iv") == 0) { g_real.glRasterPos4iv = (PFN_glRasterPos4iv)addr; return; }
    if (strcmp(name, "glRasterPos4s") == 0) { g_real.glRasterPos4s = (PFN_glRasterPos4s)addr; return; }
    if (strcmp(name, "glRasterPos4sv") == 0) { g_real.glRasterPos4sv = (PFN_glRasterPos4sv)addr; return; }
    if (strcmp(name, "glReadBuffer") == 0) { g_real.glReadBuffer = (PFN_glReadBuffer)addr; return; }
    if (strcmp(name, "glReadPixels") == 0) { g_real.glReadPixels = (PFN_glReadPixels)addr; return; }
    if (strcmp(name, "glRectd") == 0) { g_real.glRectd = (PFN_glRectd)addr; return; }
    if (strcmp(name, "glRectdv") == 0) { g_real.glRectdv = (PFN_glRectdv)addr; return; }
    if (strcmp(name, "glRectf") == 0) { g_real.glRectf = (PFN_glRectf)addr; return; }
    if (strcmp(name, "glRectfv") == 0) { g_real.glRectfv = (PFN_glRectfv)addr; return; }
    if (strcmp(name, "glRecti") == 0) { g_real.glRecti = (PFN_glRecti)addr; return; }
    if (strcmp(name, "glRectiv") == 0) { g_real.glRectiv = (PFN_glRectiv)addr; return; }
    if (strcmp(name, "glRects") == 0) { g_real.glRects = (PFN_glRects)addr; return; }
    if (strcmp(name, "glRectsv") == 0) { g_real.glRectsv = (PFN_glRectsv)addr; return; }
    if (strcmp(name, "glRenderMode") == 0) { g_real.glRenderMode = (PFN_glRenderMode)addr; return; }
    if (strcmp(name, "glRotated") == 0) { g_real.glRotated = (PFN_glRotated)addr; return; }
    if (strcmp(name, "glScaled") == 0) { g_real.glScaled = (PFN_glScaled)addr; return; }
    if (strcmp(name, "glSelectBuffer") == 0) { g_real.glSelectBuffer = (PFN_glSelectBuffer)addr; return; }
    if (strcmp(name, "glShadeModel") == 0) { g_real.glShadeModel = (PFN_glShadeModel)addr; return; }
    if (strcmp(name, "glStencilFunc") == 0) { g_real.glStencilFunc = (PFN_glStencilFunc)addr; return; }
    if (strcmp(name, "glStencilMask") == 0) { g_real.glStencilMask = (PFN_glStencilMask)addr; return; }
    if (strcmp(name, "glStencilOp") == 0) { g_real.glStencilOp = (PFN_glStencilOp)addr; return; }
    if (strcmp(name, "glTexCoord1d") == 0) { g_real.glTexCoord1d = (PFN_glTexCoord1d)addr; return; }
    if (strcmp(name, "glTexCoord1dv") == 0) { g_real.glTexCoord1dv = (PFN_glTexCoord1dv)addr; return; }
    if (strcmp(name, "glTexCoord1f") == 0) { g_real.glTexCoord1f = (PFN_glTexCoord1f)addr; return; }
    if (strcmp(name, "glTexCoord1fv") == 0) { g_real.glTexCoord1fv = (PFN_glTexCoord1fv)addr; return; }
    if (strcmp(name, "glTexCoord1i") == 0) { g_real.glTexCoord1i = (PFN_glTexCoord1i)addr; return; }
    if (strcmp(name, "glTexCoord1iv") == 0) { g_real.glTexCoord1iv = (PFN_glTexCoord1iv)addr; return; }
    if (strcmp(name, "glTexCoord1s") == 0) { g_real.glTexCoord1s = (PFN_glTexCoord1s)addr; return; }
    if (strcmp(name, "glTexCoord1sv") == 0) { g_real.glTexCoord1sv = (PFN_glTexCoord1sv)addr; return; }
    if (strcmp(name, "glTexCoord2d") == 0) { g_real.glTexCoord2d = (PFN_glTexCoord2d)addr; return; }
    if (strcmp(name, "glTexCoord2dv") == 0) { g_real.glTexCoord2dv = (PFN_glTexCoord2dv)addr; return; }
    if (strcmp(name, "glTexCoord2fv") == 0) { g_real.glTexCoord2fv = (PFN_glTexCoord2fv)addr; return; }
    if (strcmp(name, "glTexCoord2i") == 0) { g_real.glTexCoord2i = (PFN_glTexCoord2i)addr; return; }
    if (strcmp(name, "glTexCoord2iv") == 0) { g_real.glTexCoord2iv = (PFN_glTexCoord2iv)addr; return; }
    if (strcmp(name, "glTexCoord2s") == 0) { g_real.glTexCoord2s = (PFN_glTexCoord2s)addr; return; }
    if (strcmp(name, "glTexCoord2sv") == 0) { g_real.glTexCoord2sv = (PFN_glTexCoord2sv)addr; return; }
    if (strcmp(name, "glTexCoord3d") == 0) { g_real.glTexCoord3d = (PFN_glTexCoord3d)addr; return; }
    if (strcmp(name, "glTexCoord3dv") == 0) { g_real.glTexCoord3dv = (PFN_glTexCoord3dv)addr; return; }
    if (strcmp(name, "glTexCoord3f") == 0) { g_real.glTexCoord3f = (PFN_glTexCoord3f)addr; return; }
    if (strcmp(name, "glTexCoord3fv") == 0) { g_real.glTexCoord3fv = (PFN_glTexCoord3fv)addr; return; }
    if (strcmp(name, "glTexCoord3i") == 0) { g_real.glTexCoord3i = (PFN_glTexCoord3i)addr; return; }
    if (strcmp(name, "glTexCoord3iv") == 0) { g_real.glTexCoord3iv = (PFN_glTexCoord3iv)addr; return; }
    if (strcmp(name, "glTexCoord3s") == 0) { g_real.glTexCoord3s = (PFN_glTexCoord3s)addr; return; }
    if (strcmp(name, "glTexCoord3sv") == 0) { g_real.glTexCoord3sv = (PFN_glTexCoord3sv)addr; return; }
    if (strcmp(name, "glTexCoord4d") == 0) { g_real.glTexCoord4d = (PFN_glTexCoord4d)addr; return; }
    if (strcmp(name, "glTexCoord4dv") == 0) { g_real.glTexCoord4dv = (PFN_glTexCoord4dv)addr; return; }
    if (strcmp(name, "glTexCoord4f") == 0) { g_real.glTexCoord4f = (PFN_glTexCoord4f)addr; return; }
    if (strcmp(name, "glTexCoord4fv") == 0) { g_real.glTexCoord4fv = (PFN_glTexCoord4fv)addr; return; }
    if (strcmp(name, "glTexCoord4i") == 0) { g_real.glTexCoord4i = (PFN_glTexCoord4i)addr; return; }
    if (strcmp(name, "glTexCoord4iv") == 0) { g_real.glTexCoord4iv = (PFN_glTexCoord4iv)addr; return; }
    if (strcmp(name, "glTexCoord4s") == 0) { g_real.glTexCoord4s = (PFN_glTexCoord4s)addr; return; }
    if (strcmp(name, "glTexCoord4sv") == 0) { g_real.glTexCoord4sv = (PFN_glTexCoord4sv)addr; return; }
    if (strcmp(name, "glTexEnvf") == 0) { g_real.glTexEnvf = (PFN_glTexEnvf)addr; return; }
    if (strcmp(name, "glTexEnvfv") == 0) { g_real.glTexEnvfv = (PFN_glTexEnvfv)addr; return; }
    if (strcmp(name, "glTexEnvi") == 0) { g_real.glTexEnvi = (PFN_glTexEnvi)addr; return; }
    if (strcmp(name, "glTexEnviv") == 0) { g_real.glTexEnviv = (PFN_glTexEnviv)addr; return; }
    if (strcmp(name, "glTexGend") == 0) { g_real.glTexGend = (PFN_glTexGend)addr; return; }
    if (strcmp(name, "glTexGendv") == 0) { g_real.glTexGendv = (PFN_glTexGendv)addr; return; }
    if (strcmp(name, "glTexGenf") == 0) { g_real.glTexGenf = (PFN_glTexGenf)addr; return; }
    if (strcmp(name, "glTexGenfv") == 0) { g_real.glTexGenfv = (PFN_glTexGenfv)addr; return; }
    if (strcmp(name, "glTexGeni") == 0) { g_real.glTexGeni = (PFN_glTexGeni)addr; return; }
    if (strcmp(name, "glTexGeniv") == 0) { g_real.glTexGeniv = (PFN_glTexGeniv)addr; return; }
    if (strcmp(name, "glTexImage1D") == 0) { g_real.glTexImage1D = (PFN_glTexImage1D)addr; return; }
    if (strcmp(name, "glTexParameterfv") == 0) { g_real.glTexParameterfv = (PFN_glTexParameterfv)addr; return; }
    if (strcmp(name, "glTexParameteriv") == 0) { g_real.glTexParameteriv = (PFN_glTexParameteriv)addr; return; }
    if (strcmp(name, "glTexSubImage1D") == 0) { g_real.glTexSubImage1D = (PFN_glTexSubImage1D)addr; return; }
    if (strcmp(name, "glTranslated") == 0) { g_real.glTranslated = (PFN_glTranslated)addr; return; }
    if (strcmp(name, "glVertex2d") == 0) { g_real.glVertex2d = (PFN_glVertex2d)addr; return; }
    if (strcmp(name, "glVertex2dv") == 0) { g_real.glVertex2dv = (PFN_glVertex2dv)addr; return; }
    if (strcmp(name, "glVertex2fv") == 0) { g_real.glVertex2fv = (PFN_glVertex2fv)addr; return; }
    if (strcmp(name, "glVertex2i") == 0) { g_real.glVertex2i = (PFN_glVertex2i)addr; return; }
    if (strcmp(name, "glVertex2iv") == 0) { g_real.glVertex2iv = (PFN_glVertex2iv)addr; return; }
    if (strcmp(name, "glVertex2s") == 0) { g_real.glVertex2s = (PFN_glVertex2s)addr; return; }
    if (strcmp(name, "glVertex2sv") == 0) { g_real.glVertex2sv = (PFN_glVertex2sv)addr; return; }
    if (strcmp(name, "glVertex3d") == 0) { g_real.glVertex3d = (PFN_glVertex3d)addr; return; }
    if (strcmp(name, "glVertex3dv") == 0) { g_real.glVertex3dv = (PFN_glVertex3dv)addr; return; }
    if (strcmp(name, "glVertex3fv") == 0) { g_real.glVertex3fv = (PFN_glVertex3fv)addr; return; }
    if (strcmp(name, "glVertex3i") == 0) { g_real.glVertex3i = (PFN_glVertex3i)addr; return; }
    if (strcmp(name, "glVertex3iv") == 0) { g_real.glVertex3iv = (PFN_glVertex3iv)addr; return; }
    if (strcmp(name, "glVertex3s") == 0) { g_real.glVertex3s = (PFN_glVertex3s)addr; return; }
    if (strcmp(name, "glVertex3sv") == 0) { g_real.glVertex3sv = (PFN_glVertex3sv)addr; return; }
    if (strcmp(name, "glVertex4d") == 0) { g_real.glVertex4d = (PFN_glVertex4d)addr; return; }
    if (strcmp(name, "glVertex4dv") == 0) { g_real.glVertex4dv = (PFN_glVertex4dv)addr; return; }
    if (strcmp(name, "glVertex4fv") == 0) { g_real.glVertex4fv = (PFN_glVertex4fv)addr; return; }
    if (strcmp(name, "glVertex4i") == 0) { g_real.glVertex4i = (PFN_glVertex4i)addr; return; }
    if (strcmp(name, "glVertex4iv") == 0) { g_real.glVertex4iv = (PFN_glVertex4iv)addr; return; }
    if (strcmp(name, "glVertex4s") == 0) { g_real.glVertex4s = (PFN_glVertex4s)addr; return; }
    if (strcmp(name, "glVertex4sv") == 0) { g_real.glVertex4sv = (PFN_glVertex4sv)addr; return; }
    if (strcmp(name, "glGetShaderiv") == 0) { g_real.glGetShaderiv = (PFN_glGetShaderiv)addr; return; }
    if (strcmp(name, "glGetProgramiv") == 0) { g_real.glGetProgramiv = (PFN_glGetProgramiv)addr; return; }
    if (strcmp(name, "glActiveShaderProgram") == 0) { g_real.glActiveShaderProgram = (PFN_glActiveShaderProgram)addr; return; }
    if (strcmp(name, "glBeginConditionalRender") == 0) { g_real.glBeginConditionalRender = (PFN_glBeginConditionalRender)addr; return; }
    if (strcmp(name, "glBeginQuery") == 0) { g_real.glBeginQuery = (PFN_glBeginQuery)addr; return; }
    if (strcmp(name, "glBeginQueryIndexed") == 0) { g_real.glBeginQueryIndexed = (PFN_glBeginQueryIndexed)addr; return; }
    if (strcmp(name, "glBeginTransformFeedback") == 0) { g_real.glBeginTransformFeedback = (PFN_glBeginTransformFeedback)addr; return; }
    if (strcmp(name, "glBindBufferBase") == 0) { g_real.glBindBufferBase = (PFN_glBindBufferBase)addr; return; }
    if (strcmp(name, "glBindBufferRange") == 0) { g_real.glBindBufferRange = (PFN_glBindBufferRange)addr; return; }
    if (strcmp(name, "glBindImageTexture") == 0) { g_real.glBindImageTexture = (PFN_glBindImageTexture)addr; return; }
    if (strcmp(name, "glBindProgramPipeline") == 0) { g_real.glBindProgramPipeline = (PFN_glBindProgramPipeline)addr; return; }
    if (strcmp(name, "glBindSampler") == 0) { g_real.glBindSampler = (PFN_glBindSampler)addr; return; }
    if (strcmp(name, "glBindTextureUnit") == 0) { g_real.glBindTextureUnit = (PFN_glBindTextureUnit)addr; return; }
    if (strcmp(name, "glBindTransformFeedback") == 0) { g_real.glBindTransformFeedback = (PFN_glBindTransformFeedback)addr; return; }
    if (strcmp(name, "glBindVertexBuffer") == 0) { g_real.glBindVertexBuffer = (PFN_glBindVertexBuffer)addr; return; }
    if (strcmp(name, "glBlendColor") == 0) { g_real.glBlendColor = (PFN_glBlendColor)addr; return; }
    if (strcmp(name, "glBlendEquation") == 0) { g_real.glBlendEquation = (PFN_glBlendEquation)addr; return; }
    if (strcmp(name, "glBlendEquationSeparate") == 0) { g_real.glBlendEquationSeparate = (PFN_glBlendEquationSeparate)addr; return; }
    if (strcmp(name, "glBlendEquationSeparatei") == 0) { g_real.glBlendEquationSeparatei = (PFN_glBlendEquationSeparatei)addr; return; }
    if (strcmp(name, "glBlendEquationi") == 0) { g_real.glBlendEquationi = (PFN_glBlendEquationi)addr; return; }
    if (strcmp(name, "glBlendFuncSeparate") == 0) { g_real.glBlendFuncSeparate = (PFN_glBlendFuncSeparate)addr; return; }
    if (strcmp(name, "glBlendFuncSeparatei") == 0) { g_real.glBlendFuncSeparatei = (PFN_glBlendFuncSeparatei)addr; return; }
    if (strcmp(name, "glBlendFunci") == 0) { g_real.glBlendFunci = (PFN_glBlendFunci)addr; return; }
    if (strcmp(name, "glBlitFramebuffer") == 0) { g_real.glBlitFramebuffer = (PFN_glBlitFramebuffer)addr; return; }
    if (strcmp(name, "glBlitNamedFramebuffer") == 0) { g_real.glBlitNamedFramebuffer = (PFN_glBlitNamedFramebuffer)addr; return; }
    if (strcmp(name, "glClampColor") == 0) { g_real.glClampColor = (PFN_glClampColor)addr; return; }
    if (strcmp(name, "glClearBufferfi") == 0) { g_real.glClearBufferfi = (PFN_glClearBufferfi)addr; return; }
    if (strcmp(name, "glClearDepthf") == 0) { g_real.glClearDepthf = (PFN_glClearDepthf)addr; return; }
    if (strcmp(name, "glClearNamedFramebufferfi") == 0) { g_real.glClearNamedFramebufferfi = (PFN_glClearNamedFramebufferfi)addr; return; }
    if (strcmp(name, "glClientActiveTexture") == 0) { g_real.glClientActiveTexture = (PFN_glClientActiveTexture)addr; return; }
    if (strcmp(name, "glClipControl") == 0) { g_real.glClipControl = (PFN_glClipControl)addr; return; }
    if (strcmp(name, "glColorMaski") == 0) { g_real.glColorMaski = (PFN_glColorMaski)addr; return; }
    if (strcmp(name, "glColorP3ui") == 0) { g_real.glColorP3ui = (PFN_glColorP3ui)addr; return; }
    if (strcmp(name, "glColorP4ui") == 0) { g_real.glColorP4ui = (PFN_glColorP4ui)addr; return; }
    if (strcmp(name, "glCopyBufferSubData") == 0) { g_real.glCopyBufferSubData = (PFN_glCopyBufferSubData)addr; return; }
    if (strcmp(name, "glCopyImageSubData") == 0) { g_real.glCopyImageSubData = (PFN_glCopyImageSubData)addr; return; }
    if (strcmp(name, "glCopyNamedBufferSubData") == 0) { g_real.glCopyNamedBufferSubData = (PFN_glCopyNamedBufferSubData)addr; return; }
    if (strcmp(name, "glCopyTexSubImage3D") == 0) { g_real.glCopyTexSubImage3D = (PFN_glCopyTexSubImage3D)addr; return; }
    if (strcmp(name, "glCopyTextureSubImage1D") == 0) { g_real.glCopyTextureSubImage1D = (PFN_glCopyTextureSubImage1D)addr; return; }
    if (strcmp(name, "glCopyTextureSubImage2D") == 0) { g_real.glCopyTextureSubImage2D = (PFN_glCopyTextureSubImage2D)addr; return; }
    if (strcmp(name, "glCopyTextureSubImage3D") == 0) { g_real.glCopyTextureSubImage3D = (PFN_glCopyTextureSubImage3D)addr; return; }
    if (strcmp(name, "glDeleteSync") == 0) { g_real.glDeleteSync = (PFN_glDeleteSync)addr; return; }
    if (strcmp(name, "glDepthRangeIndexed") == 0) { g_real.glDepthRangeIndexed = (PFN_glDepthRangeIndexed)addr; return; }
    if (strcmp(name, "glDepthRangef") == 0) { g_real.glDepthRangef = (PFN_glDepthRangef)addr; return; }
    if (strcmp(name, "glDisableVertexArrayAttrib") == 0) { g_real.glDisableVertexArrayAttrib = (PFN_glDisableVertexArrayAttrib)addr; return; }
    if (strcmp(name, "glDisablei") == 0) { g_real.glDisablei = (PFN_glDisablei)addr; return; }
    if (strcmp(name, "glDispatchCompute") == 0) { g_real.glDispatchCompute = (PFN_glDispatchCompute)addr; return; }
    if (strcmp(name, "glDispatchComputeIndirect") == 0) { g_real.glDispatchComputeIndirect = (PFN_glDispatchComputeIndirect)addr; return; }
    if (strcmp(name, "glDrawArraysInstancedBaseInstance") == 0) { g_real.glDrawArraysInstancedBaseInstance = (PFN_glDrawArraysInstancedBaseInstance)addr; return; }
    if (strcmp(name, "glDrawTransformFeedback") == 0) { g_real.glDrawTransformFeedback = (PFN_glDrawTransformFeedback)addr; return; }
    if (strcmp(name, "glDrawTransformFeedbackInstanced") == 0) { g_real.glDrawTransformFeedbackInstanced = (PFN_glDrawTransformFeedbackInstanced)addr; return; }
    if (strcmp(name, "glDrawTransformFeedbackStream") == 0) { g_real.glDrawTransformFeedbackStream = (PFN_glDrawTransformFeedbackStream)addr; return; }
    if (strcmp(name, "glDrawTransformFeedbackStreamInstanced") == 0) { g_real.glDrawTransformFeedbackStreamInstanced = (PFN_glDrawTransformFeedbackStreamInstanced)addr; return; }
    if (strcmp(name, "glEnableVertexArrayAttrib") == 0) { g_real.glEnableVertexArrayAttrib = (PFN_glEnableVertexArrayAttrib)addr; return; }
    if (strcmp(name, "glEnablei") == 0) { g_real.glEnablei = (PFN_glEnablei)addr; return; }
    if (strcmp(name, "glEndConditionalRender") == 0) { g_real.glEndConditionalRender = (PFN_glEndConditionalRender)addr; return; }
    if (strcmp(name, "glEndQuery") == 0) { g_real.glEndQuery = (PFN_glEndQuery)addr; return; }
    if (strcmp(name, "glEndQueryIndexed") == 0) { g_real.glEndQueryIndexed = (PFN_glEndQueryIndexed)addr; return; }
    if (strcmp(name, "glEndTransformFeedback") == 0) { g_real.glEndTransformFeedback = (PFN_glEndTransformFeedback)addr; return; }
    if (strcmp(name, "glFlushMappedBufferRange") == 0) { g_real.glFlushMappedBufferRange = (PFN_glFlushMappedBufferRange)addr; return; }
    if (strcmp(name, "glFlushMappedNamedBufferRange") == 0) { g_real.glFlushMappedNamedBufferRange = (PFN_glFlushMappedNamedBufferRange)addr; return; }
    if (strcmp(name, "glFogCoordd") == 0) { g_real.glFogCoordd = (PFN_glFogCoordd)addr; return; }
    if (strcmp(name, "glFogCoordf") == 0) { g_real.glFogCoordf = (PFN_glFogCoordf)addr; return; }
    if (strcmp(name, "glFramebufferParameteri") == 0) { g_real.glFramebufferParameteri = (PFN_glFramebufferParameteri)addr; return; }
    if (strcmp(name, "glFramebufferTexture") == 0) { g_real.glFramebufferTexture = (PFN_glFramebufferTexture)addr; return; }
    if (strcmp(name, "glFramebufferTexture1D") == 0) { g_real.glFramebufferTexture1D = (PFN_glFramebufferTexture1D)addr; return; }
    if (strcmp(name, "glFramebufferTexture3D") == 0) { g_real.glFramebufferTexture3D = (PFN_glFramebufferTexture3D)addr; return; }
    if (strcmp(name, "glFramebufferTextureLayer") == 0) { g_real.glFramebufferTextureLayer = (PFN_glFramebufferTextureLayer)addr; return; }
    if (strcmp(name, "glGenerateTextureMipmap") == 0) { g_real.glGenerateTextureMipmap = (PFN_glGenerateTextureMipmap)addr; return; }
    if (strcmp(name, "glGetQueryBufferObjecti64v") == 0) { g_real.glGetQueryBufferObjecti64v = (PFN_glGetQueryBufferObjecti64v)addr; return; }
    if (strcmp(name, "glGetQueryBufferObjectiv") == 0) { g_real.glGetQueryBufferObjectiv = (PFN_glGetQueryBufferObjectiv)addr; return; }
    if (strcmp(name, "glGetQueryBufferObjectui64v") == 0) { g_real.glGetQueryBufferObjectui64v = (PFN_glGetQueryBufferObjectui64v)addr; return; }
    if (strcmp(name, "glGetQueryBufferObjectuiv") == 0) { g_real.glGetQueryBufferObjectuiv = (PFN_glGetQueryBufferObjectuiv)addr; return; }
    if (strcmp(name, "glInvalidateBufferData") == 0) { g_real.glInvalidateBufferData = (PFN_glInvalidateBufferData)addr; return; }
    if (strcmp(name, "glInvalidateBufferSubData") == 0) { g_real.glInvalidateBufferSubData = (PFN_glInvalidateBufferSubData)addr; return; }
    if (strcmp(name, "glInvalidateTexImage") == 0) { g_real.glInvalidateTexImage = (PFN_glInvalidateTexImage)addr; return; }
    if (strcmp(name, "glInvalidateTexSubImage") == 0) { g_real.glInvalidateTexSubImage = (PFN_glInvalidateTexSubImage)addr; return; }
    if (strcmp(name, "glMemoryBarrier") == 0) { g_real.glMemoryBarrier = (PFN_glMemoryBarrier)addr; return; }
    if (strcmp(name, "glMemoryBarrierByRegion") == 0) { g_real.glMemoryBarrierByRegion = (PFN_glMemoryBarrierByRegion)addr; return; }
    if (strcmp(name, "glMinSampleShading") == 0) { g_real.glMinSampleShading = (PFN_glMinSampleShading)addr; return; }
    if (strcmp(name, "glMultiTexCoord1d") == 0) { g_real.glMultiTexCoord1d = (PFN_glMultiTexCoord1d)addr; return; }
    if (strcmp(name, "glMultiTexCoord1f") == 0) { g_real.glMultiTexCoord1f = (PFN_glMultiTexCoord1f)addr; return; }
    if (strcmp(name, "glMultiTexCoord1i") == 0) { g_real.glMultiTexCoord1i = (PFN_glMultiTexCoord1i)addr; return; }
    if (strcmp(name, "glMultiTexCoord1s") == 0) { g_real.glMultiTexCoord1s = (PFN_glMultiTexCoord1s)addr; return; }
    if (strcmp(name, "glMultiTexCoord2d") == 0) { g_real.glMultiTexCoord2d = (PFN_glMultiTexCoord2d)addr; return; }
    if (strcmp(name, "glMultiTexCoord2f") == 0) { g_real.glMultiTexCoord2f = (PFN_glMultiTexCoord2f)addr; return; }
    if (strcmp(name, "glMultiTexCoord2i") == 0) { g_real.glMultiTexCoord2i = (PFN_glMultiTexCoord2i)addr; return; }
    if (strcmp(name, "glMultiTexCoord2s") == 0) { g_real.glMultiTexCoord2s = (PFN_glMultiTexCoord2s)addr; return; }
    if (strcmp(name, "glMultiTexCoord3d") == 0) { g_real.glMultiTexCoord3d = (PFN_glMultiTexCoord3d)addr; return; }
    if (strcmp(name, "glMultiTexCoord3f") == 0) { g_real.glMultiTexCoord3f = (PFN_glMultiTexCoord3f)addr; return; }
    if (strcmp(name, "glMultiTexCoord3i") == 0) { g_real.glMultiTexCoord3i = (PFN_glMultiTexCoord3i)addr; return; }
    if (strcmp(name, "glMultiTexCoord3s") == 0) { g_real.glMultiTexCoord3s = (PFN_glMultiTexCoord3s)addr; return; }
    if (strcmp(name, "glMultiTexCoord4d") == 0) { g_real.glMultiTexCoord4d = (PFN_glMultiTexCoord4d)addr; return; }
    if (strcmp(name, "glMultiTexCoord4f") == 0) { g_real.glMultiTexCoord4f = (PFN_glMultiTexCoord4f)addr; return; }
    if (strcmp(name, "glMultiTexCoord4i") == 0) { g_real.glMultiTexCoord4i = (PFN_glMultiTexCoord4i)addr; return; }
    if (strcmp(name, "glMultiTexCoord4s") == 0) { g_real.glMultiTexCoord4s = (PFN_glMultiTexCoord4s)addr; return; }
    if (strcmp(name, "glMultiTexCoordP1ui") == 0) { g_real.glMultiTexCoordP1ui = (PFN_glMultiTexCoordP1ui)addr; return; }
    if (strcmp(name, "glMultiTexCoordP2ui") == 0) { g_real.glMultiTexCoordP2ui = (PFN_glMultiTexCoordP2ui)addr; return; }
    if (strcmp(name, "glMultiTexCoordP3ui") == 0) { g_real.glMultiTexCoordP3ui = (PFN_glMultiTexCoordP3ui)addr; return; }
    if (strcmp(name, "glMultiTexCoordP4ui") == 0) { g_real.glMultiTexCoordP4ui = (PFN_glMultiTexCoordP4ui)addr; return; }
    if (strcmp(name, "glNamedFramebufferDrawBuffer") == 0) { g_real.glNamedFramebufferDrawBuffer = (PFN_glNamedFramebufferDrawBuffer)addr; return; }
    if (strcmp(name, "glNamedFramebufferParameteri") == 0) { g_real.glNamedFramebufferParameteri = (PFN_glNamedFramebufferParameteri)addr; return; }
    if (strcmp(name, "glNamedFramebufferReadBuffer") == 0) { g_real.glNamedFramebufferReadBuffer = (PFN_glNamedFramebufferReadBuffer)addr; return; }
    if (strcmp(name, "glNamedFramebufferRenderbuffer") == 0) { g_real.glNamedFramebufferRenderbuffer = (PFN_glNamedFramebufferRenderbuffer)addr; return; }
    if (strcmp(name, "glNamedFramebufferTexture") == 0) { g_real.glNamedFramebufferTexture = (PFN_glNamedFramebufferTexture)addr; return; }
    if (strcmp(name, "glNamedFramebufferTextureLayer") == 0) { g_real.glNamedFramebufferTextureLayer = (PFN_glNamedFramebufferTextureLayer)addr; return; }
    if (strcmp(name, "glNamedRenderbufferStorage") == 0) { g_real.glNamedRenderbufferStorage = (PFN_glNamedRenderbufferStorage)addr; return; }
    if (strcmp(name, "glNamedRenderbufferStorageMultisample") == 0) { g_real.glNamedRenderbufferStorageMultisample = (PFN_glNamedRenderbufferStorageMultisample)addr; return; }
    if (strcmp(name, "glNormalP3ui") == 0) { g_real.glNormalP3ui = (PFN_glNormalP3ui)addr; return; }
    if (strcmp(name, "glPatchParameteri") == 0) { g_real.glPatchParameteri = (PFN_glPatchParameteri)addr; return; }
    if (strcmp(name, "glPauseTransformFeedback") == 0) { g_real.glPauseTransformFeedback = (PFN_glPauseTransformFeedback)addr; return; }
    if (strcmp(name, "glPointParameterf") == 0) { g_real.glPointParameterf = (PFN_glPointParameterf)addr; return; }
    if (strcmp(name, "glPointParameteri") == 0) { g_real.glPointParameteri = (PFN_glPointParameteri)addr; return; }
    if (strcmp(name, "glPolygonOffsetClamp") == 0) { g_real.glPolygonOffsetClamp = (PFN_glPolygonOffsetClamp)addr; return; }
    if (strcmp(name, "glPopDebugGroup") == 0) { g_real.glPopDebugGroup = (PFN_glPopDebugGroup)addr; return; }
    if (strcmp(name, "glPrimitiveRestartIndex") == 0) { g_real.glPrimitiveRestartIndex = (PFN_glPrimitiveRestartIndex)addr; return; }
    if (strcmp(name, "glProgramParameteri") == 0) { g_real.glProgramParameteri = (PFN_glProgramParameteri)addr; return; }
    if (strcmp(name, "glProgramUniform1d") == 0) { g_real.glProgramUniform1d = (PFN_glProgramUniform1d)addr; return; }
    if (strcmp(name, "glProgramUniform1f") == 0) { g_real.glProgramUniform1f = (PFN_glProgramUniform1f)addr; return; }
    if (strcmp(name, "glProgramUniform1i") == 0) { g_real.glProgramUniform1i = (PFN_glProgramUniform1i)addr; return; }
    if (strcmp(name, "glProgramUniform1ui") == 0) { g_real.glProgramUniform1ui = (PFN_glProgramUniform1ui)addr; return; }
    if (strcmp(name, "glProgramUniform2d") == 0) { g_real.glProgramUniform2d = (PFN_glProgramUniform2d)addr; return; }
    if (strcmp(name, "glProgramUniform2f") == 0) { g_real.glProgramUniform2f = (PFN_glProgramUniform2f)addr; return; }
    if (strcmp(name, "glProgramUniform2i") == 0) { g_real.glProgramUniform2i = (PFN_glProgramUniform2i)addr; return; }
    if (strcmp(name, "glProgramUniform2ui") == 0) { g_real.glProgramUniform2ui = (PFN_glProgramUniform2ui)addr; return; }
    if (strcmp(name, "glProgramUniform3d") == 0) { g_real.glProgramUniform3d = (PFN_glProgramUniform3d)addr; return; }
    if (strcmp(name, "glProgramUniform3f") == 0) { g_real.glProgramUniform3f = (PFN_glProgramUniform3f)addr; return; }
    if (strcmp(name, "glProgramUniform3i") == 0) { g_real.glProgramUniform3i = (PFN_glProgramUniform3i)addr; return; }
    if (strcmp(name, "glProgramUniform3ui") == 0) { g_real.glProgramUniform3ui = (PFN_glProgramUniform3ui)addr; return; }
    if (strcmp(name, "glProgramUniform4d") == 0) { g_real.glProgramUniform4d = (PFN_glProgramUniform4d)addr; return; }
    if (strcmp(name, "glProgramUniform4f") == 0) { g_real.glProgramUniform4f = (PFN_glProgramUniform4f)addr; return; }
    if (strcmp(name, "glProgramUniform4i") == 0) { g_real.glProgramUniform4i = (PFN_glProgramUniform4i)addr; return; }
    if (strcmp(name, "glProgramUniform4ui") == 0) { g_real.glProgramUniform4ui = (PFN_glProgramUniform4ui)addr; return; }
    if (strcmp(name, "glProvokingVertex") == 0) { g_real.glProvokingVertex = (PFN_glProvokingVertex)addr; return; }
    if (strcmp(name, "glQueryCounter") == 0) { g_real.glQueryCounter = (PFN_glQueryCounter)addr; return; }
    if (strcmp(name, "glReleaseShaderCompiler") == 0) { g_real.glReleaseShaderCompiler = (PFN_glReleaseShaderCompiler)addr; return; }
    if (strcmp(name, "glRenderbufferStorageMultisample") == 0) { g_real.glRenderbufferStorageMultisample = (PFN_glRenderbufferStorageMultisample)addr; return; }
    if (strcmp(name, "glResumeTransformFeedback") == 0) { g_real.glResumeTransformFeedback = (PFN_glResumeTransformFeedback)addr; return; }
    if (strcmp(name, "glSampleCoverage") == 0) { g_real.glSampleCoverage = (PFN_glSampleCoverage)addr; return; }
    if (strcmp(name, "glSampleMaski") == 0) { g_real.glSampleMaski = (PFN_glSampleMaski)addr; return; }
    if (strcmp(name, "glSamplerParameterf") == 0) { g_real.glSamplerParameterf = (PFN_glSamplerParameterf)addr; return; }
    if (strcmp(name, "glSamplerParameteri") == 0) { g_real.glSamplerParameteri = (PFN_glSamplerParameteri)addr; return; }
    if (strcmp(name, "glScissorIndexed") == 0) { g_real.glScissorIndexed = (PFN_glScissorIndexed)addr; return; }
    if (strcmp(name, "glSecondaryColor3b") == 0) { g_real.glSecondaryColor3b = (PFN_glSecondaryColor3b)addr; return; }
    if (strcmp(name, "glSecondaryColor3d") == 0) { g_real.glSecondaryColor3d = (PFN_glSecondaryColor3d)addr; return; }
    if (strcmp(name, "glSecondaryColor3f") == 0) { g_real.glSecondaryColor3f = (PFN_glSecondaryColor3f)addr; return; }
    if (strcmp(name, "glSecondaryColor3i") == 0) { g_real.glSecondaryColor3i = (PFN_glSecondaryColor3i)addr; return; }
    if (strcmp(name, "glSecondaryColor3s") == 0) { g_real.glSecondaryColor3s = (PFN_glSecondaryColor3s)addr; return; }
    if (strcmp(name, "glSecondaryColor3ub") == 0) { g_real.glSecondaryColor3ub = (PFN_glSecondaryColor3ub)addr; return; }
    if (strcmp(name, "glSecondaryColor3ui") == 0) { g_real.glSecondaryColor3ui = (PFN_glSecondaryColor3ui)addr; return; }
    if (strcmp(name, "glSecondaryColor3us") == 0) { g_real.glSecondaryColor3us = (PFN_glSecondaryColor3us)addr; return; }
    if (strcmp(name, "glSecondaryColorP3ui") == 0) { g_real.glSecondaryColorP3ui = (PFN_glSecondaryColorP3ui)addr; return; }
    if (strcmp(name, "glShaderStorageBlockBinding") == 0) { g_real.glShaderStorageBlockBinding = (PFN_glShaderStorageBlockBinding)addr; return; }
    if (strcmp(name, "glStencilFuncSeparate") == 0) { g_real.glStencilFuncSeparate = (PFN_glStencilFuncSeparate)addr; return; }
    if (strcmp(name, "glStencilMaskSeparate") == 0) { g_real.glStencilMaskSeparate = (PFN_glStencilMaskSeparate)addr; return; }
    if (strcmp(name, "glStencilOpSeparate") == 0) { g_real.glStencilOpSeparate = (PFN_glStencilOpSeparate)addr; return; }
    if (strcmp(name, "glTexBuffer") == 0) { g_real.glTexBuffer = (PFN_glTexBuffer)addr; return; }
    if (strcmp(name, "glTexBufferRange") == 0) { g_real.glTexBufferRange = (PFN_glTexBufferRange)addr; return; }
    if (strcmp(name, "glTexCoordP1ui") == 0) { g_real.glTexCoordP1ui = (PFN_glTexCoordP1ui)addr; return; }
    if (strcmp(name, "glTexCoordP2ui") == 0) { g_real.glTexCoordP2ui = (PFN_glTexCoordP2ui)addr; return; }
    if (strcmp(name, "glTexCoordP3ui") == 0) { g_real.glTexCoordP3ui = (PFN_glTexCoordP3ui)addr; return; }
    if (strcmp(name, "glTexCoordP4ui") == 0) { g_real.glTexCoordP4ui = (PFN_glTexCoordP4ui)addr; return; }
    if (strcmp(name, "glTexImage2DMultisample") == 0) { g_real.glTexImage2DMultisample = (PFN_glTexImage2DMultisample)addr; return; }
    if (strcmp(name, "glTexImage3DMultisample") == 0) { g_real.glTexImage3DMultisample = (PFN_glTexImage3DMultisample)addr; return; }
    if (strcmp(name, "glTexStorage1D") == 0) { g_real.glTexStorage1D = (PFN_glTexStorage1D)addr; return; }
    if (strcmp(name, "glTexStorage2D") == 0) { g_real.glTexStorage2D = (PFN_glTexStorage2D)addr; return; }
    if (strcmp(name, "glTexStorage2DMultisample") == 0) { g_real.glTexStorage2DMultisample = (PFN_glTexStorage2DMultisample)addr; return; }
    if (strcmp(name, "glTexStorage3D") == 0) { g_real.glTexStorage3D = (PFN_glTexStorage3D)addr; return; }
    if (strcmp(name, "glTexStorage3DMultisample") == 0) { g_real.glTexStorage3DMultisample = (PFN_glTexStorage3DMultisample)addr; return; }
    if (strcmp(name, "glTextureBarrier") == 0) { g_real.glTextureBarrier = (PFN_glTextureBarrier)addr; return; }
    if (strcmp(name, "glTextureBuffer") == 0) { g_real.glTextureBuffer = (PFN_glTextureBuffer)addr; return; }
    if (strcmp(name, "glTextureBufferRange") == 0) { g_real.glTextureBufferRange = (PFN_glTextureBufferRange)addr; return; }
    if (strcmp(name, "glTextureParameterf") == 0) { g_real.glTextureParameterf = (PFN_glTextureParameterf)addr; return; }
    if (strcmp(name, "glTextureParameteri") == 0) { g_real.glTextureParameteri = (PFN_glTextureParameteri)addr; return; }
    if (strcmp(name, "glTextureStorage1D") == 0) { g_real.glTextureStorage1D = (PFN_glTextureStorage1D)addr; return; }
    if (strcmp(name, "glTextureStorage2D") == 0) { g_real.glTextureStorage2D = (PFN_glTextureStorage2D)addr; return; }
    if (strcmp(name, "glTextureStorage2DMultisample") == 0) { g_real.glTextureStorage2DMultisample = (PFN_glTextureStorage2DMultisample)addr; return; }
    if (strcmp(name, "glTextureStorage3D") == 0) { g_real.glTextureStorage3D = (PFN_glTextureStorage3D)addr; return; }
    if (strcmp(name, "glTextureStorage3DMultisample") == 0) { g_real.glTextureStorage3DMultisample = (PFN_glTextureStorage3DMultisample)addr; return; }
    if (strcmp(name, "glTextureView") == 0) { g_real.glTextureView = (PFN_glTextureView)addr; return; }
    if (strcmp(name, "glTransformFeedbackBufferBase") == 0) { g_real.glTransformFeedbackBufferBase = (PFN_glTransformFeedbackBufferBase)addr; return; }
    if (strcmp(name, "glTransformFeedbackBufferRange") == 0) { g_real.glTransformFeedbackBufferRange = (PFN_glTransformFeedbackBufferRange)addr; return; }
    if (strcmp(name, "glUniform1d") == 0) { g_real.glUniform1d = (PFN_glUniform1d)addr; return; }
    if (strcmp(name, "glUniform1ui") == 0) { g_real.glUniform1ui = (PFN_glUniform1ui)addr; return; }
    if (strcmp(name, "glUniform2d") == 0) { g_real.glUniform2d = (PFN_glUniform2d)addr; return; }
    if (strcmp(name, "glUniform2i") == 0) { g_real.glUniform2i = (PFN_glUniform2i)addr; return; }
    if (strcmp(name, "glUniform2ui") == 0) { g_real.glUniform2ui = (PFN_glUniform2ui)addr; return; }
    if (strcmp(name, "glUniform3d") == 0) { g_real.glUniform3d = (PFN_glUniform3d)addr; return; }
    if (strcmp(name, "glUniform3i") == 0) { g_real.glUniform3i = (PFN_glUniform3i)addr; return; }
    if (strcmp(name, "glUniform3ui") == 0) { g_real.glUniform3ui = (PFN_glUniform3ui)addr; return; }
    if (strcmp(name, "glUniform4d") == 0) { g_real.glUniform4d = (PFN_glUniform4d)addr; return; }
    if (strcmp(name, "glUniform4i") == 0) { g_real.glUniform4i = (PFN_glUniform4i)addr; return; }
    if (strcmp(name, "glUniform4ui") == 0) { g_real.glUniform4ui = (PFN_glUniform4ui)addr; return; }
    if (strcmp(name, "glUniformBlockBinding") == 0) { g_real.glUniformBlockBinding = (PFN_glUniformBlockBinding)addr; return; }
    if (strcmp(name, "glUseProgramStages") == 0) { g_real.glUseProgramStages = (PFN_glUseProgramStages)addr; return; }
    if (strcmp(name, "glValidateProgram") == 0) { g_real.glValidateProgram = (PFN_glValidateProgram)addr; return; }
    if (strcmp(name, "glValidateProgramPipeline") == 0) { g_real.glValidateProgramPipeline = (PFN_glValidateProgramPipeline)addr; return; }
    if (strcmp(name, "glVertexArrayAttribBinding") == 0) { g_real.glVertexArrayAttribBinding = (PFN_glVertexArrayAttribBinding)addr; return; }
    if (strcmp(name, "glVertexArrayAttribFormat") == 0) { g_real.glVertexArrayAttribFormat = (PFN_glVertexArrayAttribFormat)addr; return; }
    if (strcmp(name, "glVertexArrayAttribIFormat") == 0) { g_real.glVertexArrayAttribIFormat = (PFN_glVertexArrayAttribIFormat)addr; return; }
    if (strcmp(name, "glVertexArrayAttribLFormat") == 0) { g_real.glVertexArrayAttribLFormat = (PFN_glVertexArrayAttribLFormat)addr; return; }
    if (strcmp(name, "glVertexArrayBindingDivisor") == 0) { g_real.glVertexArrayBindingDivisor = (PFN_glVertexArrayBindingDivisor)addr; return; }
    if (strcmp(name, "glVertexArrayElementBuffer") == 0) { g_real.glVertexArrayElementBuffer = (PFN_glVertexArrayElementBuffer)addr; return; }
    if (strcmp(name, "glVertexArrayVertexBuffer") == 0) { g_real.glVertexArrayVertexBuffer = (PFN_glVertexArrayVertexBuffer)addr; return; }
    if (strcmp(name, "glVertexAttrib1d") == 0) { g_real.glVertexAttrib1d = (PFN_glVertexAttrib1d)addr; return; }
    if (strcmp(name, "glVertexAttrib1f") == 0) { g_real.glVertexAttrib1f = (PFN_glVertexAttrib1f)addr; return; }
    if (strcmp(name, "glVertexAttrib1s") == 0) { g_real.glVertexAttrib1s = (PFN_glVertexAttrib1s)addr; return; }
    if (strcmp(name, "glVertexAttrib2d") == 0) { g_real.glVertexAttrib2d = (PFN_glVertexAttrib2d)addr; return; }
    if (strcmp(name, "glVertexAttrib2f") == 0) { g_real.glVertexAttrib2f = (PFN_glVertexAttrib2f)addr; return; }
    if (strcmp(name, "glVertexAttrib2s") == 0) { g_real.glVertexAttrib2s = (PFN_glVertexAttrib2s)addr; return; }
    if (strcmp(name, "glVertexAttrib3d") == 0) { g_real.glVertexAttrib3d = (PFN_glVertexAttrib3d)addr; return; }
    if (strcmp(name, "glVertexAttrib3f") == 0) { g_real.glVertexAttrib3f = (PFN_glVertexAttrib3f)addr; return; }
    if (strcmp(name, "glVertexAttrib3s") == 0) { g_real.glVertexAttrib3s = (PFN_glVertexAttrib3s)addr; return; }
    if (strcmp(name, "glVertexAttrib4Nub") == 0) { g_real.glVertexAttrib4Nub = (PFN_glVertexAttrib4Nub)addr; return; }
    if (strcmp(name, "glVertexAttrib4d") == 0) { g_real.glVertexAttrib4d = (PFN_glVertexAttrib4d)addr; return; }
    if (strcmp(name, "glVertexAttrib4f") == 0) { g_real.glVertexAttrib4f = (PFN_glVertexAttrib4f)addr; return; }
    if (strcmp(name, "glVertexAttrib4s") == 0) { g_real.glVertexAttrib4s = (PFN_glVertexAttrib4s)addr; return; }
    if (strcmp(name, "glVertexAttribBinding") == 0) { g_real.glVertexAttribBinding = (PFN_glVertexAttribBinding)addr; return; }
    if (strcmp(name, "glVertexAttribDivisor") == 0) { g_real.glVertexAttribDivisor = (PFN_glVertexAttribDivisor)addr; return; }
    if (strcmp(name, "glVertexAttribFormat") == 0) { g_real.glVertexAttribFormat = (PFN_glVertexAttribFormat)addr; return; }
    if (strcmp(name, "glVertexAttribI1i") == 0) { g_real.glVertexAttribI1i = (PFN_glVertexAttribI1i)addr; return; }
    if (strcmp(name, "glVertexAttribI1ui") == 0) { g_real.glVertexAttribI1ui = (PFN_glVertexAttribI1ui)addr; return; }
    if (strcmp(name, "glVertexAttribI2i") == 0) { g_real.glVertexAttribI2i = (PFN_glVertexAttribI2i)addr; return; }
    if (strcmp(name, "glVertexAttribI2ui") == 0) { g_real.glVertexAttribI2ui = (PFN_glVertexAttribI2ui)addr; return; }
    if (strcmp(name, "glVertexAttribI3i") == 0) { g_real.glVertexAttribI3i = (PFN_glVertexAttribI3i)addr; return; }
    if (strcmp(name, "glVertexAttribI3ui") == 0) { g_real.glVertexAttribI3ui = (PFN_glVertexAttribI3ui)addr; return; }
    if (strcmp(name, "glVertexAttribI4i") == 0) { g_real.glVertexAttribI4i = (PFN_glVertexAttribI4i)addr; return; }
    if (strcmp(name, "glVertexAttribI4ui") == 0) { g_real.glVertexAttribI4ui = (PFN_glVertexAttribI4ui)addr; return; }
    if (strcmp(name, "glVertexAttribIFormat") == 0) { g_real.glVertexAttribIFormat = (PFN_glVertexAttribIFormat)addr; return; }
    if (strcmp(name, "glVertexAttribL1d") == 0) { g_real.glVertexAttribL1d = (PFN_glVertexAttribL1d)addr; return; }
    if (strcmp(name, "glVertexAttribL2d") == 0) { g_real.glVertexAttribL2d = (PFN_glVertexAttribL2d)addr; return; }
    if (strcmp(name, "glVertexAttribL3d") == 0) { g_real.glVertexAttribL3d = (PFN_glVertexAttribL3d)addr; return; }
    if (strcmp(name, "glVertexAttribL4d") == 0) { g_real.glVertexAttribL4d = (PFN_glVertexAttribL4d)addr; return; }
    if (strcmp(name, "glVertexAttribLFormat") == 0) { g_real.glVertexAttribLFormat = (PFN_glVertexAttribLFormat)addr; return; }
    if (strcmp(name, "glVertexAttribP1ui") == 0) { g_real.glVertexAttribP1ui = (PFN_glVertexAttribP1ui)addr; return; }
    if (strcmp(name, "glVertexAttribP2ui") == 0) { g_real.glVertexAttribP2ui = (PFN_glVertexAttribP2ui)addr; return; }
    if (strcmp(name, "glVertexAttribP3ui") == 0) { g_real.glVertexAttribP3ui = (PFN_glVertexAttribP3ui)addr; return; }
    if (strcmp(name, "glVertexAttribP4ui") == 0) { g_real.glVertexAttribP4ui = (PFN_glVertexAttribP4ui)addr; return; }
    if (strcmp(name, "glVertexBindingDivisor") == 0) { g_real.glVertexBindingDivisor = (PFN_glVertexBindingDivisor)addr; return; }
    if (strcmp(name, "glVertexP2ui") == 0) { g_real.glVertexP2ui = (PFN_glVertexP2ui)addr; return; }
    if (strcmp(name, "glVertexP3ui") == 0) { g_real.glVertexP3ui = (PFN_glVertexP3ui)addr; return; }
    if (strcmp(name, "glVertexP4ui") == 0) { g_real.glVertexP4ui = (PFN_glVertexP4ui)addr; return; }
    if (strcmp(name, "glViewportIndexedf") == 0) { g_real.glViewportIndexedf = (PFN_glViewportIndexedf)addr; return; }
    if (strcmp(name, "glWaitSync") == 0) { g_real.glWaitSync = (PFN_glWaitSync)addr; return; }
    if (strcmp(name, "glWindowPos2d") == 0) { g_real.glWindowPos2d = (PFN_glWindowPos2d)addr; return; }
    if (strcmp(name, "glWindowPos2f") == 0) { g_real.glWindowPos2f = (PFN_glWindowPos2f)addr; return; }
    if (strcmp(name, "glWindowPos2i") == 0) { g_real.glWindowPos2i = (PFN_glWindowPos2i)addr; return; }
    if (strcmp(name, "glWindowPos2s") == 0) { g_real.glWindowPos2s = (PFN_glWindowPos2s)addr; return; }
    if (strcmp(name, "glWindowPos3d") == 0) { g_real.glWindowPos3d = (PFN_glWindowPos3d)addr; return; }
    if (strcmp(name, "glWindowPos3f") == 0) { g_real.glWindowPos3f = (PFN_glWindowPos3f)addr; return; }
    if (strcmp(name, "glWindowPos3i") == 0) { g_real.glWindowPos3i = (PFN_glWindowPos3i)addr; return; }
    if (strcmp(name, "glWindowPos3s") == 0) { g_real.glWindowPos3s = (PFN_glWindowPos3s)addr; return; }
    if (strcmp(name, "glClearBufferfv") == 0) { g_real.glClearBufferfv = (PFN_glClearBufferfv)addr; return; }
    if (strcmp(name, "glCreateBuffers") == 0) { g_real.glCreateBuffers = (PFN_glCreateBuffers)addr; return; }
    if (strcmp(name, "glCreateFramebuffers") == 0) { g_real.glCreateFramebuffers = (PFN_glCreateFramebuffers)addr; return; }
    if (strcmp(name, "glCreateRenderbuffers") == 0) { g_real.glCreateRenderbuffers = (PFN_glCreateRenderbuffers)addr; return; }
    if (strcmp(name, "glCreateTextures") == 0) { g_real.glCreateTextures = (PFN_glCreateTextures)addr; return; }
    if (strcmp(name, "glCreateVertexArrays") == 0) { g_real.glCreateVertexArrays = (PFN_glCreateVertexArrays)addr; return; }
    if (strcmp(name, "glDebugMessageInsert") == 0) { g_real.glDebugMessageInsert = (PFN_glDebugMessageInsert)addr; return; }
    if (strcmp(name, "glGetProgramInfoLog") == 0) { g_real.glGetProgramInfoLog = (PFN_glGetProgramInfoLog)addr; return; }
    if (strcmp(name, "glGetShaderInfoLog") == 0) { g_real.glGetShaderInfoLog = (PFN_glGetShaderInfoLog)addr; return; }
    if (strcmp(name, "glNamedBufferStorage") == 0) { g_real.glNamedBufferStorage = (PFN_glNamedBufferStorage)addr; return; }
    if (strcmp(name, "glNamedBufferSubData") == 0) { g_real.glNamedBufferSubData = (PFN_glNamedBufferSubData)addr; return; }
    if (strcmp(name, "glNamedFramebufferDrawBuffers") == 0) { g_real.glNamedFramebufferDrawBuffers = (PFN_glNamedFramebufferDrawBuffers)addr; return; }
    if (strcmp(name, "glTextureSubImage2D") == 0) { g_real.glTextureSubImage2D = (PFN_glTextureSubImage2D)addr; return; }
    if (strcmp(name, "glTextureSubImage3D") == 0) { g_real.glTextureSubImage3D = (PFN_glTextureSubImage3D)addr; return; }
    if (strcmp(name, "wglCreateContext") == 0) { g_real.wglCreateContext = (PFN_wglCreateContext)addr; return; }
    if (strcmp(name, "wglDeleteContext") == 0) { g_real.wglDeleteContext = (PFN_wglDeleteContext)addr; return; }
    if (strcmp(name, "wglMakeCurrent") == 0) { g_real.wglMakeCurrent = (PFN_wglMakeCurrent)addr; return; }
    if (strcmp(name, "wglShareLists") == 0) { g_real.wglShareLists = (PFN_wglShareLists)addr; return; }
    if (strcmp(name, "wglSwapLayerBuffers") == 0) { g_real.wglSwapLayerBuffers = (PFN_wglSwapLayerBuffers)addr; return; }
    if (strcmp(name, "wglCreateContextAttribsARB") == 0) { g_real.wglCreateContextAttribsARB = (PFN_wglCreateContextAttribsARB)addr; return; }
}

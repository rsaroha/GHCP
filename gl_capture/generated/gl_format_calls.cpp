// GENERATED FILE - do not edit by hand. See codegen/generate.py
#include "gl_format_calls.h"
#include "gl_enum_names.h"
#include "gl_types_min.h"
#include "byte_cursor.h"
#include <cstdio>

std::string FormatCall(GLFuncId id, const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    char buf[256];
    switch (id) {
    case GLFuncId::glEnable: {
        std::string s = "glEnable(";
        GLenum a_cap = cur.Read<GLenum>();
        s += "cap=";
        if (const char* nm = LookupEnumName(a_cap)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_cap); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDisable: {
        std::string s = "glDisable(";
        GLenum a_cap = cur.Read<GLenum>();
        s += "cap=";
        if (const char* nm = LookupEnumName(a_cap)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_cap); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glClearColor: {
        std::string s = "glClearColor(";
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "r=%g", a_r); s += buf;
        GLfloat a_g = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", g=%g", a_g); s += buf;
        GLfloat a_b = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", b=%g", a_b); s += buf;
        GLfloat a_a = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", a=%g", a_a); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearDepth: {
        std::string s = "glClearDepth(";
        GLdouble a_d = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "d=%g", a_d); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClear: {
        std::string s = "glClear(";
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += "mask="; s += FormatBitfield(a_mask);
        s += ")";
        return s;
    }
    case GLFuncId::glBlendFunc: {
        std::string s = "glBlendFunc(";
        GLenum a_sfactor = cur.Read<GLenum>();
        s += "sfactor=";
        if (const char* nm = LookupEnumName(a_sfactor)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_sfactor); s += buf; }
        GLenum a_dfactor = cur.Read<GLenum>();
        s += ", dfactor=";
        if (const char* nm = LookupEnumName(a_dfactor)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dfactor); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDepthFunc: {
        std::string s = "glDepthFunc(";
        GLenum a_func = cur.Read<GLenum>();
        s += "func=";
        if (const char* nm = LookupEnumName(a_func)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_func); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDepthMask: {
        std::string s = "glDepthMask(";
        GLboolean a_flag = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), "flag=%d", a_flag); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCullFace: {
        std::string s = "glCullFace(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glFrontFace: {
        std::string s = "glFrontFace(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glPolygonMode: {
        std::string s = "glPolygonMode(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glLineWidth: {
        std::string s = "glLineWidth(";
        GLfloat a_width = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "width=%g", a_width); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPointSize: {
        std::string s = "glPointSize(";
        GLfloat a_size = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "size=%g", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glViewport: {
        std::string s = "glViewport(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_w = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        GLsizei a_h = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", h=%d", a_h); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glScissor: {
        std::string s = "glScissor(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_w = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        GLsizei a_h = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", h=%d", a_h); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMatrixMode: {
        std::string s = "glMatrixMode(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glLoadIdentity: {
        std::string s = "glLoadIdentity(";
        s += ")";
        return s;
    }
    case GLFuncId::glPushMatrix: {
        std::string s = "glPushMatrix(";
        s += ")";
        return s;
    }
    case GLFuncId::glPopMatrix: {
        std::string s = "glPopMatrix(";
        s += ")";
        return s;
    }
    case GLFuncId::glTranslatef: {
        std::string s = "glTranslatef(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRotatef: {
        std::string s = "glRotatef(";
        GLfloat a_angle = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "angle=%g", a_angle); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glScalef: {
        std::string s = "glScalef(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glOrtho: {
        std::string s = "glOrtho(";
        GLdouble a_l = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "l=%g", a_l); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLdouble a_b = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", b=%g", a_b); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_n = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", n=%g", a_n); s += buf;
        GLdouble a_f = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", f=%g", a_f); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFrustum: {
        std::string s = "glFrustum(";
        GLdouble a_l = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "l=%g", a_l); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLdouble a_b = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", b=%g", a_b); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_n = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", n=%g", a_n); s += buf;
        GLdouble a_f = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", f=%g", a_f); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBegin: {
        std::string s = "glBegin(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glEnd: {
        std::string s = "glEnd(";
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2f: {
        std::string s = "glVertex2f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex3f: {
        std::string s = "glVertex3f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4f: {
        std::string s = "glVertex4f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLfloat a_w = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3f: {
        std::string s = "glColor3f(";
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "r=%g", a_r); s += buf;
        GLfloat a_g = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", g=%g", a_g); s += buf;
        GLfloat a_b = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", b=%g", a_b); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4f: {
        std::string s = "glColor4f(";
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "r=%g", a_r); s += buf;
        GLfloat a_g = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", g=%g", a_g); s += buf;
        GLfloat a_b = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", b=%g", a_b); s += buf;
        GLfloat a_a = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", a=%g", a_a); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3f: {
        std::string s = "glNormal3f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord2f: {
        std::string s = "glTexCoord2f(";
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEnableClientState: {
        std::string s = "glEnableClientState(";
        GLenum a_cap = cur.Read<GLenum>();
        s += "cap=";
        if (const char* nm = LookupEnumName(a_cap)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_cap); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDisableClientState: {
        std::string s = "glDisableClientState(";
        GLenum a_cap = cur.Read<GLenum>();
        s += "cap=";
        if (const char* nm = LookupEnumName(a_cap)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_cap); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glGenBuffers: return Format_glGenBuffers(args, len);
    case GLFuncId::glDeleteBuffers: return Format_glDeleteBuffers(args, len);
    case GLFuncId::glBindBuffer: return Format_glBindBuffer(args, len);
    case GLFuncId::glBufferData: return Format_glBufferData(args, len);
    case GLFuncId::glBufferSubData: return Format_glBufferSubData(args, len);
    case GLFuncId::glGenVertexArrays: return Format_glGenVertexArrays(args, len);
    case GLFuncId::glDeleteVertexArrays: return Format_glDeleteVertexArrays(args, len);
    case GLFuncId::glBindVertexArray: {
        std::string s = "glBindVertexArray(";
        GLuint a_array = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "array=%u", a_array); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEnableVertexAttribArray: {
        std::string s = "glEnableVertexAttribArray(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDisableVertexAttribArray: {
        std::string s = "glDisableVertexAttribArray(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribPointer: return Format_glVertexAttribPointer(args, len);
    case GLFuncId::glVertexPointer: return Format_glVertexPointer(args, len);
    case GLFuncId::glColorPointer: return Format_glColorPointer(args, len);
    case GLFuncId::glTexCoordPointer: return Format_glTexCoordPointer(args, len);
    case GLFuncId::glNormalPointer: return Format_glNormalPointer(args, len);
    case GLFuncId::glGenTextures: return Format_glGenTextures(args, len);
    case GLFuncId::glDeleteTextures: return Format_glDeleteTextures(args, len);
    case GLFuncId::glBindTexture: {
        std::string s = "glBindTexture(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glActiveTexture: {
        std::string s = "glActiveTexture(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glTexParameteri: {
        std::string s = "glTexParameteri(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexParameterf: {
        std::string s = "glTexParameterf(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPixelStorei: {
        std::string s = "glPixelStorei(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexImage2D: return Format_glTexImage2D(args, len);
    case GLFuncId::glTexSubImage2D: return Format_glTexSubImage2D(args, len);
    case GLFuncId::glGenerateMipmap: {
        std::string s = "glGenerateMipmap(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glCreateShader: {
        std::string s = "glCreateShader(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        s += ")";
        GLuint a_ret = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), " -> %u", a_ret); s += buf;
        return s;
    }
    case GLFuncId::glDeleteShader: {
        std::string s = "glDeleteShader(";
        GLuint a_shader = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "shader=%u", a_shader); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glShaderSource: return Format_glShaderSource(args, len);
    case GLFuncId::glCompileShader: {
        std::string s = "glCompileShader(";
        GLuint a_shader = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "shader=%u", a_shader); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCreateProgram: {
        std::string s = "glCreateProgram(";
        s += ")";
        GLuint a_ret = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), " -> %u", a_ret); s += buf;
        return s;
    }
    case GLFuncId::glDeleteProgram: {
        std::string s = "glDeleteProgram(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glAttachShader: {
        std::string s = "glAttachShader(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLuint a_shader = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", shader=%u", a_shader); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDetachShader: {
        std::string s = "glDetachShader(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLuint a_shader = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", shader=%u", a_shader); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLinkProgram: {
        std::string s = "glLinkProgram(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUseProgram: {
        std::string s = "glUseProgram(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindAttribLocation: return Format_glBindAttribLocation(args, len);
    case GLFuncId::glGetUniformLocation: return Format_glGetUniformLocation(args, len);
    case GLFuncId::glGetAttribLocation: return Format_glGetAttribLocation(args, len);
    case GLFuncId::glUniform1i: {
        std::string s = "glUniform1i(";
        GLint a_loc = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "loc=%d", a_loc); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform1f: {
        std::string s = "glUniform1f(";
        GLint a_loc = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "loc=%d", a_loc); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform2f: {
        std::string s = "glUniform2f(";
        GLint a_loc = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "loc=%d", a_loc); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform3f: {
        std::string s = "glUniform3f(";
        GLint a_loc = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "loc=%d", a_loc); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform4f: {
        std::string s = "glUniform4f(";
        GLint a_loc = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "loc=%d", a_loc); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        GLfloat a_v3 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v3=%g", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniformMatrix4fv: return Format_glUniformMatrix4fv(args, len);
    case GLFuncId::glUniformMatrix3fv: return Format_glUniformMatrix3fv(args, len);
    case GLFuncId::glGenFramebuffers: return Format_glGenFramebuffers(args, len);
    case GLFuncId::glDeleteFramebuffers: return Format_glDeleteFramebuffers(args, len);
    case GLFuncId::glBindFramebuffer: {
        std::string s = "glBindFramebuffer(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_fb = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", fb=%u", a_fb); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferTexture2D: {
        std::string s = "glFramebufferTexture2D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLenum a_textarget = cur.Read<GLenum>();
        s += ", textarget=";
        if (const char* nm = LookupEnumName(a_textarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_textarget); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGenRenderbuffers: return Format_glGenRenderbuffers(args, len);
    case GLFuncId::glDeleteRenderbuffers: return Format_glDeleteRenderbuffers(args, len);
    case GLFuncId::glBindRenderbuffer: {
        std::string s = "glBindRenderbuffer(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_rb = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", rb=%u", a_rb); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRenderbufferStorage: {
        std::string s = "glRenderbufferStorage(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_w = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        GLsizei a_h = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", h=%d", a_h); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferRenderbuffer: {
        std::string s = "glFramebufferRenderbuffer(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLenum a_rbtarget = cur.Read<GLenum>();
        s += ", rbtarget=";
        if (const char* nm = LookupEnumName(a_rbtarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_rbtarget); s += buf; }
        GLuint a_rb = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", rb=%u", a_rb); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCheckFramebufferStatus: {
        std::string s = "glCheckFramebufferStatus(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDrawArrays: return Format_glDrawArrays(args, len);
    case GLFuncId::glDrawElements: return Format_glDrawElements(args, len);
    case GLFuncId::glDrawArraysInstanced: return Format_glDrawArraysInstanced(args, len);
    case GLFuncId::glDrawElementsInstanced: return Format_glDrawElementsInstanced(args, len);
    case GLFuncId::glGetString: return Format_glGetString(args, len);
    case GLFuncId::glAccum: {
        std::string s = "glAccum(";
        GLenum a_op = cur.Read<GLenum>();
        s += "op=";
        if (const char* nm = LookupEnumName(a_op)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_op); s += buf; }
        GLfloat a_value = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", value=%g", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glAlphaFunc: {
        std::string s = "glAlphaFunc(";
        GLenum a_func = cur.Read<GLenum>();
        s += "func=";
        if (const char* nm = LookupEnumName(a_func)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_func); s += buf; }
        GLfloat a_ref = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", ref=%g", a_ref); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glAreTexturesResident: {
        std::string s = "glAreTexturesResident(";
        GLsizei a_n = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "n=%d", a_n); s += buf;
        uint8_t a_textures_present = cur.Read<uint8_t>();
        s += ", textures="; s += (a_textures_present ? "present" : "null");
        uint8_t a_residences_present = cur.Read<uint8_t>();
        s += ", residences="; s += (a_residences_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glArrayElement: {
        std::string s = "glArrayElement(";
        GLint a_i = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "i=%d", a_i); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBitmap: {
        std::string s = "glBitmap(";
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLfloat a_xorig = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", xorig=%g", a_xorig); s += buf;
        GLfloat a_yorig = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", yorig=%g", a_yorig); s += buf;
        GLfloat a_xmove = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", xmove=%g", a_xmove); s += buf;
        GLfloat a_ymove = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", ymove=%g", a_ymove); s += buf;
        uint8_t a_bitmap_present = cur.Read<uint8_t>();
        s += ", bitmap="; s += (a_bitmap_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glCallList: {
        std::string s = "glCallList(";
        GLuint a_list = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "list=%u", a_list); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCallLists: {
        std::string s = "glCallLists(";
        GLsizei a_n = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "n=%d", a_n); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_lists_present = cur.Read<uint8_t>();
        s += ", lists="; s += (a_lists_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glClearAccum: {
        std::string s = "glClearAccum(";
        GLfloat a_red = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLfloat a_green = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLfloat a_blue = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        GLfloat a_alpha = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", alpha=%g", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearIndex: {
        std::string s = "glClearIndex(";
        GLfloat a_c = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "c=%g", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearStencil: {
        std::string s = "glClearStencil(";
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClipPlane: {
        std::string s = "glClipPlane(";
        GLenum a_plane = cur.Read<GLenum>();
        s += "plane=";
        if (const char* nm = LookupEnumName(a_plane)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_plane); s += buf; }
        uint8_t a_equation_present = cur.Read<uint8_t>();
        s += ", equation="; s += (a_equation_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3b: {
        std::string s = "glColor3b(";
        GLbyte a_red = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLbyte a_green = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLbyte a_blue = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3bv: {
        std::string s = "glColor3bv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3d: {
        std::string s = "glColor3d(";
        GLdouble a_red = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLdouble a_green = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLdouble a_blue = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3dv: {
        std::string s = "glColor3dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3fv: {
        std::string s = "glColor3fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3i: {
        std::string s = "glColor3i(";
        GLint a_red = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLint a_green = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLint a_blue = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3iv: {
        std::string s = "glColor3iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3s: {
        std::string s = "glColor3s(";
        GLshort a_red = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLshort a_green = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLshort a_blue = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3sv: {
        std::string s = "glColor3sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3ub: {
        std::string s = "glColor3ub(";
        GLubyte a_red = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLubyte a_green = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLubyte a_blue = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3ubv: return Format_glColor3ubv(args, len);
    case GLFuncId::glColor3ui: {
        std::string s = "glColor3ui(";
        GLuint a_red = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLuint a_green = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLuint a_blue = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3uiv: {
        std::string s = "glColor3uiv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor3us: {
        std::string s = "glColor3us(";
        GLushort a_red = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLushort a_green = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLushort a_blue = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor3usv: {
        std::string s = "glColor3usv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4b: {
        std::string s = "glColor4b(";
        GLbyte a_red = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLbyte a_green = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLbyte a_blue = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        GLbyte a_alpha = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", alpha=%d", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4bv: {
        std::string s = "glColor4bv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4d: {
        std::string s = "glColor4d(";
        GLdouble a_red = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLdouble a_green = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLdouble a_blue = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        GLdouble a_alpha = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", alpha=%g", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4dv: return Format_glColor4dv(args, len);
    case GLFuncId::glColor4fv: return Format_glColor4fv(args, len);
    case GLFuncId::glColor4i: {
        std::string s = "glColor4i(";
        GLint a_red = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLint a_green = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLint a_blue = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        GLint a_alpha = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", alpha=%d", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4iv: {
        std::string s = "glColor4iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4s: {
        std::string s = "glColor4s(";
        GLshort a_red = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLshort a_green = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLshort a_blue = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        GLshort a_alpha = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", alpha=%d", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4sv: {
        std::string s = "glColor4sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4ub: {
        std::string s = "glColor4ub(";
        GLubyte a_red = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLubyte a_green = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLubyte a_blue = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        GLubyte a_alpha = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", alpha=%u", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4ubv: {
        std::string s = "glColor4ubv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4ui: {
        std::string s = "glColor4ui(";
        GLuint a_red = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLuint a_green = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLuint a_blue = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        GLuint a_alpha = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", alpha=%u", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4uiv: {
        std::string s = "glColor4uiv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glColor4us: {
        std::string s = "glColor4us(";
        GLushort a_red = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLushort a_green = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLushort a_blue = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        GLushort a_alpha = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", alpha=%u", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColor4usv: return Format_glColor4usv(args, len);
    case GLFuncId::glColorMask: {
        std::string s = "glColorMask(";
        GLboolean a_red = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLboolean a_green = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLboolean a_blue = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        GLboolean a_alpha = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", alpha=%d", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColorMaterial: {
        std::string s = "glColorMaterial(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glCopyPixels: {
        std::string s = "glCopyPixels(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTexImage1D: {
        std::string s = "glCopyTexImage1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLint a_border = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", border=%d", a_border); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTexImage2D: {
        std::string s = "glCopyTexImage2D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLint a_border = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", border=%d", a_border); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTexSubImage1D: {
        std::string s = "glCopyTexSubImage1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTexSubImage2D: {
        std::string s = "glCopyTexSubImage2D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_yoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", yoffset=%d", a_yoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDeleteLists: {
        std::string s = "glDeleteLists(";
        GLuint a_list = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "list=%u", a_list); s += buf;
        GLsizei a_range = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", range=%d", a_range); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDepthRange: {
        std::string s = "glDepthRange(";
        GLdouble a_n = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "n=%g", a_n); s += buf;
        GLdouble a_f = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", f=%g", a_f); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawBuffer: {
        std::string s = "glDrawBuffer(";
        GLenum a_buf = cur.Read<GLenum>();
        s += "buf=";
        if (const char* nm = LookupEnumName(a_buf)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_buf); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glDrawPixels: {
        std::string s = "glDrawPixels(";
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        s += ", pixels="; s += (a_pixels_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEdgeFlag: {
        std::string s = "glEdgeFlag(";
        GLboolean a_flag = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), "flag=%d", a_flag); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEdgeFlagPointer: {
        std::string s = "glEdgeFlagPointer(";
        GLsizei a_stride = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "stride=%d", a_stride); s += buf;
        uint8_t a_pointer_present = cur.Read<uint8_t>();
        s += ", pointer="; s += (a_pointer_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEdgeFlagv: {
        std::string s = "glEdgeFlagv(";
        uint8_t a_flag_present = cur.Read<uint8_t>();
        s += "flag="; s += (a_flag_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEndList: {
        std::string s = "glEndList(";
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord1d: {
        std::string s = "glEvalCoord1d(";
        GLdouble a_u = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "u=%g", a_u); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord1dv: {
        std::string s = "glEvalCoord1dv(";
        uint8_t a_u_present = cur.Read<uint8_t>();
        s += "u="; s += (a_u_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord1f: {
        std::string s = "glEvalCoord1f(";
        GLfloat a_u = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "u=%g", a_u); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord1fv: {
        std::string s = "glEvalCoord1fv(";
        uint8_t a_u_present = cur.Read<uint8_t>();
        s += "u="; s += (a_u_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord2d: {
        std::string s = "glEvalCoord2d(";
        GLdouble a_u = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "u=%g", a_u); s += buf;
        GLdouble a_v = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v=%g", a_v); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord2dv: {
        std::string s = "glEvalCoord2dv(";
        uint8_t a_u_present = cur.Read<uint8_t>();
        s += "u="; s += (a_u_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord2f: {
        std::string s = "glEvalCoord2f(";
        GLfloat a_u = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "u=%g", a_u); s += buf;
        GLfloat a_v = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v=%g", a_v); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalCoord2fv: {
        std::string s = "glEvalCoord2fv(";
        uint8_t a_u_present = cur.Read<uint8_t>();
        s += "u="; s += (a_u_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glEvalMesh1: {
        std::string s = "glEvalMesh1(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLint a_i1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", i1=%d", a_i1); s += buf;
        GLint a_i2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", i2=%d", a_i2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalMesh2: {
        std::string s = "glEvalMesh2(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLint a_i1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", i1=%d", a_i1); s += buf;
        GLint a_i2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", i2=%d", a_i2); s += buf;
        GLint a_j1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", j1=%d", a_j1); s += buf;
        GLint a_j2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", j2=%d", a_j2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalPoint1: {
        std::string s = "glEvalPoint1(";
        GLint a_i = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "i=%d", a_i); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEvalPoint2: {
        std::string s = "glEvalPoint2(";
        GLint a_i = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "i=%d", a_i); s += buf;
        GLint a_j = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", j=%d", a_j); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFeedbackBuffer: {
        std::string s = "glFeedbackBuffer(";
        GLsizei a_size = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_buffer_present = cur.Read<uint8_t>();
        s += ", buffer="; s += (a_buffer_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glFinish: {
        std::string s = "glFinish(";
        s += ")";
        return s;
    }
    case GLFuncId::glFlush: {
        std::string s = "glFlush(";
        s += ")";
        return s;
    }
    case GLFuncId::glFogf: {
        std::string s = "glFogf(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFogfv: {
        std::string s = "glFogfv(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glFogi: {
        std::string s = "glFogi(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFogiv: {
        std::string s = "glFogiv(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGenLists: {
        std::string s = "glGenLists(";
        GLsizei a_range = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "range=%d", a_range); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGetBooleanv: return Format_glGetBooleanv(args, len);
    case GLFuncId::glGetClipPlane: {
        std::string s = "glGetClipPlane(";
        GLenum a_plane = cur.Read<GLenum>();
        s += "plane=";
        if (const char* nm = LookupEnumName(a_plane)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_plane); s += buf; }
        uint8_t a_equation_present = cur.Read<uint8_t>();
        s += ", equation="; s += (a_equation_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetDoublev: {
        std::string s = "glGetDoublev(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_data_present = cur.Read<uint8_t>();
        s += ", data="; s += (a_data_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetError: {
        std::string s = "glGetError(";
        s += ")";
        return s;
    }
    case GLFuncId::glGetFloatv: return Format_glGetFloatv(args, len);
    case GLFuncId::glGetIntegerv: return Format_glGetIntegerv(args, len);
    case GLFuncId::glGetLightfv: {
        std::string s = "glGetLightfv(";
        GLenum a_light = cur.Read<GLenum>();
        s += "light=";
        if (const char* nm = LookupEnumName(a_light)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_light); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetLightiv: {
        std::string s = "glGetLightiv(";
        GLenum a_light = cur.Read<GLenum>();
        s += "light=";
        if (const char* nm = LookupEnumName(a_light)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_light); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetMapdv: {
        std::string s = "glGetMapdv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_query = cur.Read<GLenum>();
        s += ", query=";
        if (const char* nm = LookupEnumName(a_query)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_query); s += buf; }
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += ", v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetMapfv: {
        std::string s = "glGetMapfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_query = cur.Read<GLenum>();
        s += ", query=";
        if (const char* nm = LookupEnumName(a_query)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_query); s += buf; }
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += ", v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetMapiv: {
        std::string s = "glGetMapiv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_query = cur.Read<GLenum>();
        s += ", query=";
        if (const char* nm = LookupEnumName(a_query)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_query); s += buf; }
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += ", v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetMaterialfv: {
        std::string s = "glGetMaterialfv(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetMaterialiv: {
        std::string s = "glGetMaterialiv(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetPixelMapfv: {
        std::string s = "glGetPixelMapfv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetPixelMapuiv: {
        std::string s = "glGetPixelMapuiv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetPixelMapusv: {
        std::string s = "glGetPixelMapusv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetPointerv: {
        std::string s = "glGetPointerv(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetPolygonStipple: {
        std::string s = "glGetPolygonStipple(";
        uint8_t a_mask_present = cur.Read<uint8_t>();
        s += "mask="; s += (a_mask_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexEnvfv: {
        std::string s = "glGetTexEnvfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexEnviv: {
        std::string s = "glGetTexEnviv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexGendv: {
        std::string s = "glGetTexGendv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexGenfv: {
        std::string s = "glGetTexGenfv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexGeniv: {
        std::string s = "glGetTexGeniv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexImage: {
        std::string s = "glGetTexImage(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        s += ", pixels="; s += (a_pixels_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexLevelParameterfv: {
        std::string s = "glGetTexLevelParameterfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexLevelParameteriv: {
        std::string s = "glGetTexLevelParameteriv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexParameterfv: {
        std::string s = "glGetTexParameterfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetTexParameteriv: {
        std::string s = "glGetTexParameteriv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glHint: {
        std::string s = "glHint(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glIndexMask: {
        std::string s = "glIndexMask(";
        GLuint a_mask = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "mask=%u", a_mask); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexPointer: {
        std::string s = "glIndexPointer(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLsizei a_stride = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", stride=%d", a_stride); s += buf;
        uint8_t a_pointer_present = cur.Read<uint8_t>();
        s += ", pointer="; s += (a_pointer_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glIndexd: {
        std::string s = "glIndexd(";
        GLdouble a_c = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "c=%g", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexdv: {
        std::string s = "glIndexdv(";
        uint8_t a_c_present = cur.Read<uint8_t>();
        s += "c="; s += (a_c_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glIndexf: {
        std::string s = "glIndexf(";
        GLfloat a_c = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "c=%g", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexfv: {
        std::string s = "glIndexfv(";
        uint8_t a_c_present = cur.Read<uint8_t>();
        s += "c="; s += (a_c_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glIndexi: {
        std::string s = "glIndexi(";
        GLint a_c = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "c=%d", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexiv: {
        std::string s = "glIndexiv(";
        uint8_t a_c_present = cur.Read<uint8_t>();
        s += "c="; s += (a_c_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glIndexs: {
        std::string s = "glIndexs(";
        GLshort a_c = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "c=%d", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexsv: {
        std::string s = "glIndexsv(";
        uint8_t a_c_present = cur.Read<uint8_t>();
        s += "c="; s += (a_c_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glIndexub: {
        std::string s = "glIndexub(";
        GLubyte a_c = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), "c=%u", a_c); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIndexubv: {
        std::string s = "glIndexubv(";
        uint8_t a_c_present = cur.Read<uint8_t>();
        s += "c="; s += (a_c_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glInitNames: {
        std::string s = "glInitNames(";
        s += ")";
        return s;
    }
    case GLFuncId::glInterleavedArrays: return Format_glInterleavedArrays(args, len);
    case GLFuncId::glIsEnabled: {
        std::string s = "glIsEnabled(";
        GLenum a_cap = cur.Read<GLenum>();
        s += "cap=";
        if (const char* nm = LookupEnumName(a_cap)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_cap); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glIsList: {
        std::string s = "glIsList(";
        GLuint a_list = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "list=%u", a_list); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glIsTexture: {
        std::string s = "glIsTexture(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLightModelf: {
        std::string s = "glLightModelf(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLightModelfv: return Format_glLightModelfv(args, len);
    case GLFuncId::glLightModeli: {
        std::string s = "glLightModeli(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLightModeliv: {
        std::string s = "glLightModeliv(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glLightf: {
        std::string s = "glLightf(";
        GLenum a_light = cur.Read<GLenum>();
        s += "light=";
        if (const char* nm = LookupEnumName(a_light)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_light); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLightfv: return Format_glLightfv(args, len);
    case GLFuncId::glLighti: {
        std::string s = "glLighti(";
        GLenum a_light = cur.Read<GLenum>();
        s += "light=";
        if (const char* nm = LookupEnumName(a_light)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_light); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLightiv: {
        std::string s = "glLightiv(";
        GLenum a_light = cur.Read<GLenum>();
        s += "light=";
        if (const char* nm = LookupEnumName(a_light)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_light); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glLineStipple: {
        std::string s = "glLineStipple(";
        GLint a_factor = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "factor=%d", a_factor); s += buf;
        GLushort a_pattern = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", pattern=%u", a_pattern); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glListBase: {
        std::string s = "glListBase(";
        GLuint a_base = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "base=%u", a_base); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLoadMatrixd: return Format_glLoadMatrixd(args, len);
    case GLFuncId::glLoadMatrixf: return Format_glLoadMatrixf(args, len);
    case GLFuncId::glLoadName: {
        std::string s = "glLoadName(";
        GLuint a_name = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "name=%u", a_name); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glLogicOp: {
        std::string s = "glLogicOp(";
        GLenum a_opcode = cur.Read<GLenum>();
        s += "opcode=";
        if (const char* nm = LookupEnumName(a_opcode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_opcode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glMap1d: {
        std::string s = "glMap1d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_u1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLdouble a_u2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_stride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", stride=%d", a_stride); s += buf;
        GLint a_order = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", order=%d", a_order); s += buf;
        uint8_t a_points_present = cur.Read<uint8_t>();
        s += ", points="; s += (a_points_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMap1f: {
        std::string s = "glMap1f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_u1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLfloat a_u2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_stride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", stride=%d", a_stride); s += buf;
        GLint a_order = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", order=%d", a_order); s += buf;
        uint8_t a_points_present = cur.Read<uint8_t>();
        s += ", points="; s += (a_points_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMap2d: {
        std::string s = "glMap2d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_u1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLdouble a_u2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_ustride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", ustride=%d", a_ustride); s += buf;
        GLint a_uorder = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", uorder=%d", a_uorder); s += buf;
        GLdouble a_v1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLdouble a_v2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        GLint a_vstride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vstride=%d", a_vstride); s += buf;
        GLint a_vorder = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vorder=%d", a_vorder); s += buf;
        uint8_t a_points_present = cur.Read<uint8_t>();
        s += ", points="; s += (a_points_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMap2f: {
        std::string s = "glMap2f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_u1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLfloat a_u2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_ustride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", ustride=%d", a_ustride); s += buf;
        GLint a_uorder = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", uorder=%d", a_uorder); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        GLint a_vstride = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vstride=%d", a_vstride); s += buf;
        GLint a_vorder = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vorder=%d", a_vorder); s += buf;
        uint8_t a_points_present = cur.Read<uint8_t>();
        s += ", points="; s += (a_points_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMapGrid1d: {
        std::string s = "glMapGrid1d(";
        GLint a_un = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "un=%d", a_un); s += buf;
        GLdouble a_u1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLdouble a_u2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMapGrid1f: {
        std::string s = "glMapGrid1f(";
        GLint a_un = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "un=%d", a_un); s += buf;
        GLfloat a_u1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLfloat a_u2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMapGrid2d: {
        std::string s = "glMapGrid2d(";
        GLint a_un = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "un=%d", a_un); s += buf;
        GLdouble a_u1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLdouble a_u2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_vn = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vn=%d", a_vn); s += buf;
        GLdouble a_v1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLdouble a_v2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMapGrid2f: {
        std::string s = "glMapGrid2f(";
        GLint a_un = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "un=%d", a_un); s += buf;
        GLfloat a_u1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u1=%g", a_u1); s += buf;
        GLfloat a_u2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", u2=%g", a_u2); s += buf;
        GLint a_vn = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", vn=%d", a_vn); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMaterialf: {
        std::string s = "glMaterialf(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMaterialfv: {
        std::string s = "glMaterialfv(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMateriali: {
        std::string s = "glMateriali(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMaterialiv: {
        std::string s = "glMaterialiv(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMultMatrixd: {
        std::string s = "glMultMatrixd(";
        uint8_t a_m_present = cur.Read<uint8_t>();
        s += "m="; s += (a_m_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glMultMatrixf: {
        std::string s = "glMultMatrixf(";
        uint8_t a_m_present = cur.Read<uint8_t>();
        s += "m="; s += (a_m_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glNewList: {
        std::string s = "glNewList(";
        GLuint a_list = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "list=%u", a_list); s += buf;
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3b: {
        std::string s = "glNormal3b(";
        GLbyte a_nx = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), "nx=%d", a_nx); s += buf;
        GLbyte a_ny = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", ny=%d", a_ny); s += buf;
        GLbyte a_nz = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", nz=%d", a_nz); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3bv: {
        std::string s = "glNormal3bv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3d: {
        std::string s = "glNormal3d(";
        GLdouble a_nx = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "nx=%g", a_nx); s += buf;
        GLdouble a_ny = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", ny=%g", a_ny); s += buf;
        GLdouble a_nz = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", nz=%g", a_nz); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3dv: return Format_glNormal3dv(args, len);
    case GLFuncId::glNormal3fv: return Format_glNormal3fv(args, len);
    case GLFuncId::glNormal3i: {
        std::string s = "glNormal3i(";
        GLint a_nx = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "nx=%d", a_nx); s += buf;
        GLint a_ny = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", ny=%d", a_ny); s += buf;
        GLint a_nz = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", nz=%d", a_nz); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3iv: {
        std::string s = "glNormal3iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3s: {
        std::string s = "glNormal3s(";
        GLshort a_nx = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "nx=%d", a_nx); s += buf;
        GLshort a_ny = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", ny=%d", a_ny); s += buf;
        GLshort a_nz = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", nz=%d", a_nz); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormal3sv: {
        std::string s = "glNormal3sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPassThrough: {
        std::string s = "glPassThrough(";
        GLfloat a_token = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "token=%g", a_token); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPixelMapfv: {
        std::string s = "glPixelMapfv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        GLsizei a_mapsize = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", mapsize=%d", a_mapsize); s += buf;
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPixelMapuiv: {
        std::string s = "glPixelMapuiv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        GLsizei a_mapsize = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", mapsize=%d", a_mapsize); s += buf;
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPixelMapusv: {
        std::string s = "glPixelMapusv(";
        GLenum a_map = cur.Read<GLenum>();
        s += "map=";
        if (const char* nm = LookupEnumName(a_map)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_map); s += buf; }
        GLsizei a_mapsize = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", mapsize=%d", a_mapsize); s += buf;
        uint8_t a_values_present = cur.Read<uint8_t>();
        s += ", values="; s += (a_values_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPixelStoref: {
        std::string s = "glPixelStoref(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPixelTransferf: {
        std::string s = "glPixelTransferf(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPixelTransferi: {
        std::string s = "glPixelTransferi(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPixelZoom: {
        std::string s = "glPixelZoom(";
        GLfloat a_xfactor = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "xfactor=%g", a_xfactor); s += buf;
        GLfloat a_yfactor = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", yfactor=%g", a_yfactor); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPolygonOffset: {
        std::string s = "glPolygonOffset(";
        GLfloat a_factor = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "factor=%g", a_factor); s += buf;
        GLfloat a_units = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", units=%g", a_units); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPolygonStipple: {
        std::string s = "glPolygonStipple(";
        uint8_t a_mask_present = cur.Read<uint8_t>();
        s += "mask="; s += (a_mask_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPopAttrib: {
        std::string s = "glPopAttrib(";
        s += ")";
        return s;
    }
    case GLFuncId::glPopClientAttrib: {
        std::string s = "glPopClientAttrib(";
        s += ")";
        return s;
    }
    case GLFuncId::glPopName: {
        std::string s = "glPopName(";
        s += ")";
        return s;
    }
    case GLFuncId::glPrioritizeTextures: {
        std::string s = "glPrioritizeTextures(";
        GLsizei a_n = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "n=%d", a_n); s += buf;
        uint8_t a_textures_present = cur.Read<uint8_t>();
        s += ", textures="; s += (a_textures_present ? "present" : "null");
        uint8_t a_priorities_present = cur.Read<uint8_t>();
        s += ", priorities="; s += (a_priorities_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glPushAttrib: {
        std::string s = "glPushAttrib(";
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += "mask="; s += FormatBitfield(a_mask);
        s += ")";
        return s;
    }
    case GLFuncId::glPushClientAttrib: {
        std::string s = "glPushClientAttrib(";
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += "mask="; s += FormatBitfield(a_mask);
        s += ")";
        return s;
    }
    case GLFuncId::glPushName: {
        std::string s = "glPushName(";
        GLuint a_name = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "name=%u", a_name); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2d: {
        std::string s = "glRasterPos2d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2dv: {
        std::string s = "glRasterPos2dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2f: {
        std::string s = "glRasterPos2f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2fv: {
        std::string s = "glRasterPos2fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2i: {
        std::string s = "glRasterPos2i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2iv: {
        std::string s = "glRasterPos2iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2s: {
        std::string s = "glRasterPos2s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos2sv: {
        std::string s = "glRasterPos2sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3d: {
        std::string s = "glRasterPos3d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3dv: {
        std::string s = "glRasterPos3dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3f: {
        std::string s = "glRasterPos3f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3fv: {
        std::string s = "glRasterPos3fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3i: {
        std::string s = "glRasterPos3i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3iv: {
        std::string s = "glRasterPos3iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3s: {
        std::string s = "glRasterPos3s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos3sv: {
        std::string s = "glRasterPos3sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4d: {
        std::string s = "glRasterPos4d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLdouble a_w = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4dv: {
        std::string s = "glRasterPos4dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4f: {
        std::string s = "glRasterPos4f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLfloat a_w = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4fv: {
        std::string s = "glRasterPos4fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4i: {
        std::string s = "glRasterPos4i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLint a_w = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4iv: {
        std::string s = "glRasterPos4iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4s: {
        std::string s = "glRasterPos4s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLshort a_w = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRasterPos4sv: {
        std::string s = "glRasterPos4sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glReadBuffer: {
        std::string s = "glReadBuffer(";
        GLenum a_src = cur.Read<GLenum>();
        s += "src=";
        if (const char* nm = LookupEnumName(a_src)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_src); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glReadPixels: {
        std::string s = "glReadPixels(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        s += ", pixels="; s += (a_pixels_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRectd: {
        std::string s = "glRectd(";
        GLdouble a_x1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x1=%g", a_x1); s += buf;
        GLdouble a_y1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y1=%g", a_y1); s += buf;
        GLdouble a_x2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x2=%g", a_x2); s += buf;
        GLdouble a_y2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y2=%g", a_y2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRectdv: {
        std::string s = "glRectdv(";
        uint8_t a_v1_present = cur.Read<uint8_t>();
        s += "v1="; s += (a_v1_present ? "present" : "null");
        uint8_t a_v2_present = cur.Read<uint8_t>();
        s += ", v2="; s += (a_v2_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRectf: {
        std::string s = "glRectf(";
        GLfloat a_x1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x1=%g", a_x1); s += buf;
        GLfloat a_y1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y1=%g", a_y1); s += buf;
        GLfloat a_x2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x2=%g", a_x2); s += buf;
        GLfloat a_y2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y2=%g", a_y2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRectfv: {
        std::string s = "glRectfv(";
        uint8_t a_v1_present = cur.Read<uint8_t>();
        s += "v1="; s += (a_v1_present ? "present" : "null");
        uint8_t a_v2_present = cur.Read<uint8_t>();
        s += ", v2="; s += (a_v2_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRecti: {
        std::string s = "glRecti(";
        GLint a_x1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x1=%d", a_x1); s += buf;
        GLint a_y1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y1=%d", a_y1); s += buf;
        GLint a_x2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x2=%d", a_x2); s += buf;
        GLint a_y2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y2=%d", a_y2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRectiv: {
        std::string s = "glRectiv(";
        uint8_t a_v1_present = cur.Read<uint8_t>();
        s += "v1="; s += (a_v1_present ? "present" : "null");
        uint8_t a_v2_present = cur.Read<uint8_t>();
        s += ", v2="; s += (a_v2_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRects: {
        std::string s = "glRects(";
        GLshort a_x1 = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x1=%d", a_x1); s += buf;
        GLshort a_y1 = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y1=%d", a_y1); s += buf;
        GLshort a_x2 = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", x2=%d", a_x2); s += buf;
        GLshort a_y2 = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y2=%d", a_y2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glRectsv: {
        std::string s = "glRectsv(";
        uint8_t a_v1_present = cur.Read<uint8_t>();
        s += "v1="; s += (a_v1_present ? "present" : "null");
        uint8_t a_v2_present = cur.Read<uint8_t>();
        s += ", v2="; s += (a_v2_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glRenderMode: {
        std::string s = "glRenderMode(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glRotated: {
        std::string s = "glRotated(";
        GLdouble a_angle = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "angle=%g", a_angle); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glScaled: {
        std::string s = "glScaled(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSelectBuffer: {
        std::string s = "glSelectBuffer(";
        GLsizei a_size = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), "size=%d", a_size); s += buf;
        uint8_t a_buffer_present = cur.Read<uint8_t>();
        s += ", buffer="; s += (a_buffer_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glShadeModel: {
        std::string s = "glShadeModel(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glStencilFunc: {
        std::string s = "glStencilFunc(";
        GLenum a_func = cur.Read<GLenum>();
        s += "func=";
        if (const char* nm = LookupEnumName(a_func)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_func); s += buf; }
        GLint a_ref = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", ref=%d", a_ref); s += buf;
        GLuint a_mask = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", mask=%u", a_mask); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glStencilMask: {
        std::string s = "glStencilMask(";
        GLuint a_mask = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "mask=%u", a_mask); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glStencilOp: {
        std::string s = "glStencilOp(";
        GLenum a_fail = cur.Read<GLenum>();
        s += "fail=";
        if (const char* nm = LookupEnumName(a_fail)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_fail); s += buf; }
        GLenum a_zfail = cur.Read<GLenum>();
        s += ", zfail=";
        if (const char* nm = LookupEnumName(a_zfail)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_zfail); s += buf; }
        GLenum a_zpass = cur.Read<GLenum>();
        s += ", zpass=";
        if (const char* nm = LookupEnumName(a_zpass)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_zpass); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1d: {
        std::string s = "glTexCoord1d(";
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1dv: {
        std::string s = "glTexCoord1dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1f: {
        std::string s = "glTexCoord1f(";
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1fv: {
        std::string s = "glTexCoord1fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1i: {
        std::string s = "glTexCoord1i(";
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1iv: {
        std::string s = "glTexCoord1iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1s: {
        std::string s = "glTexCoord1s(";
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord1sv: {
        std::string s = "glTexCoord1sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord2d: {
        std::string s = "glTexCoord2d(";
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord2dv: return Format_glTexCoord2dv(args, len);
    case GLFuncId::glTexCoord2fv: return Format_glTexCoord2fv(args, len);
    case GLFuncId::glTexCoord2i: {
        std::string s = "glTexCoord2i(";
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord2iv: return Format_glTexCoord2iv(args, len);
    case GLFuncId::glTexCoord2s: {
        std::string s = "glTexCoord2s(";
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord2sv: {
        std::string s = "glTexCoord2sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3d: {
        std::string s = "glTexCoord3d(";
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3dv: {
        std::string s = "glTexCoord3dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3f: {
        std::string s = "glTexCoord3f(";
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3fv: {
        std::string s = "glTexCoord3fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3i: {
        std::string s = "glTexCoord3i(";
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLint a_r = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3iv: {
        std::string s = "glTexCoord3iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3s: {
        std::string s = "glTexCoord3s(";
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLshort a_r = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord3sv: {
        std::string s = "glTexCoord3sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4d: {
        std::string s = "glTexCoord4d(";
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLdouble a_q = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", q=%g", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4dv: {
        std::string s = "glTexCoord4dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4f: {
        std::string s = "glTexCoord4f(";
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLfloat a_q = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", q=%g", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4fv: {
        std::string s = "glTexCoord4fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4i: {
        std::string s = "glTexCoord4i(";
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLint a_r = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        GLint a_q = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", q=%d", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4iv: {
        std::string s = "glTexCoord4iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4s: {
        std::string s = "glTexCoord4s(";
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLshort a_r = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        GLshort a_q = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", q=%d", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoord4sv: {
        std::string s = "glTexCoord4sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexEnvf: {
        std::string s = "glTexEnvf(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexEnvfv: {
        std::string s = "glTexEnvfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexEnvi: {
        std::string s = "glTexEnvi(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexEnviv: {
        std::string s = "glTexEnviv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexGend: {
        std::string s = "glTexGend(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLdouble a_param = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexGendv: {
        std::string s = "glTexGendv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexGenf: {
        std::string s = "glTexGenf(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexGenfv: {
        std::string s = "glTexGenfv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexGeni: {
        std::string s = "glTexGeni(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexGeniv: {
        std::string s = "glTexGeniv(";
        GLenum a_coord = cur.Read<GLenum>();
        s += "coord=";
        if (const char* nm = LookupEnumName(a_coord)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_coord); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexImage1D: {
        std::string s = "glTexImage1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_internalformat = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", internalformat=%d", a_internalformat); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLint a_border = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", border=%d", a_border); s += buf;
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        s += ", pixels="; s += (a_pixels_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexParameterfv: {
        std::string s = "glTexParameterfv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexParameteriv: {
        std::string s = "glTexParameteriv(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTexSubImage1D: {
        std::string s = "glTexSubImage1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        s += ", pixels="; s += (a_pixels_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glTranslated: {
        std::string s = "glTranslated(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2d: {
        std::string s = "glVertex2d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2dv: {
        std::string s = "glVertex2dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2fv: {
        std::string s = "glVertex2fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2i: {
        std::string s = "glVertex2i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2iv: {
        std::string s = "glVertex2iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2s: {
        std::string s = "glVertex2s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex2sv: {
        std::string s = "glVertex2sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex3d: {
        std::string s = "glVertex3d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex3dv: return Format_glVertex3dv(args, len);
    case GLFuncId::glVertex3fv: return Format_glVertex3fv(args, len);
    case GLFuncId::glVertex3i: {
        std::string s = "glVertex3i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex3iv: return Format_glVertex3iv(args, len);
    case GLFuncId::glVertex3s: {
        std::string s = "glVertex3s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex3sv: {
        std::string s = "glVertex3sv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4d: {
        std::string s = "glVertex4d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLdouble a_w = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4dv: {
        std::string s = "glVertex4dv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4fv: {
        std::string s = "glVertex4fv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4i: {
        std::string s = "glVertex4i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLint a_w = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4iv: {
        std::string s = "glVertex4iv(";
        uint8_t a_v_present = cur.Read<uint8_t>();
        s += "v="; s += (a_v_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4s: {
        std::string s = "glVertex4s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLshort a_w = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertex4sv: return Format_glVertex4sv(args, len);
    case GLFuncId::glGetShaderiv: {
        std::string s = "glGetShaderiv(";
        GLuint a_shader = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "shader=%u", a_shader); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glGetProgramiv: {
        std::string s = "glGetProgramiv(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        uint8_t a_params_present = cur.Read<uint8_t>();
        s += ", params="; s += (a_params_present ? "present" : "null");
        s += ")";
        return s;
    }
    case GLFuncId::glActiveShaderProgram: {
        std::string s = "glActiveShaderProgram(";
        GLuint a_pipeline = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "pipeline=%u", a_pipeline); s += buf;
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBeginConditionalRender: {
        std::string s = "glBeginConditionalRender(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBeginQuery: {
        std::string s = "glBeginQuery(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBeginQueryIndexed: {
        std::string s = "glBeginQueryIndexed(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBeginTransformFeedback: {
        std::string s = "glBeginTransformFeedback(";
        GLenum a_primitiveMode = cur.Read<GLenum>();
        s += "primitiveMode=";
        if (const char* nm = LookupEnumName(a_primitiveMode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_primitiveMode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBindBufferBase: {
        std::string s = "glBindBufferBase(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindBufferRange: {
        std::string s = "glBindBufferRange(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindImageTexture: {
        std::string s = "glBindImageTexture(";
        GLuint a_unit = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "unit=%u", a_unit); s += buf;
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLboolean a_layered = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", layered=%d", a_layered); s += buf;
        GLint a_layer = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", layer=%d", a_layer); s += buf;
        GLenum a_access = cur.Read<GLenum>();
        s += ", access=";
        if (const char* nm = LookupEnumName(a_access)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_access); s += buf; }
        GLenum a_format = cur.Read<GLenum>();
        s += ", format=";
        if (const char* nm = LookupEnumName(a_format)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_format); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBindProgramPipeline: {
        std::string s = "glBindProgramPipeline(";
        GLuint a_pipeline = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "pipeline=%u", a_pipeline); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindSampler: {
        std::string s = "glBindSampler(";
        GLuint a_unit = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "unit=%u", a_unit); s += buf;
        GLuint a_sampler = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", sampler=%u", a_sampler); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindTextureUnit: {
        std::string s = "glBindTextureUnit(";
        GLuint a_unit = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "unit=%u", a_unit); s += buf;
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindTransformFeedback: {
        std::string s = "glBindTransformFeedback(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBindVertexBuffer: {
        std::string s = "glBindVertexBuffer(";
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "bindingindex=%u", a_bindingindex); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizei a_stride = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", stride=%d", a_stride); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBlendColor: {
        std::string s = "glBlendColor(";
        GLfloat a_red = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLfloat a_green = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLfloat a_blue = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        GLfloat a_alpha = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", alpha=%g", a_alpha); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glBlendEquation: {
        std::string s = "glBlendEquation(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendEquationSeparate: {
        std::string s = "glBlendEquationSeparate(";
        GLenum a_modeRGB = cur.Read<GLenum>();
        s += "modeRGB=";
        if (const char* nm = LookupEnumName(a_modeRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_modeRGB); s += buf; }
        GLenum a_modeAlpha = cur.Read<GLenum>();
        s += ", modeAlpha=";
        if (const char* nm = LookupEnumName(a_modeAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_modeAlpha); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendEquationSeparatei: {
        std::string s = "glBlendEquationSeparatei(";
        GLuint a_buf = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buf=%u", a_buf); s += buf;
        GLenum a_modeRGB = cur.Read<GLenum>();
        s += ", modeRGB=";
        if (const char* nm = LookupEnumName(a_modeRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_modeRGB); s += buf; }
        GLenum a_modeAlpha = cur.Read<GLenum>();
        s += ", modeAlpha=";
        if (const char* nm = LookupEnumName(a_modeAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_modeAlpha); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendEquationi: {
        std::string s = "glBlendEquationi(";
        GLuint a_buf = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buf=%u", a_buf); s += buf;
        GLenum a_mode = cur.Read<GLenum>();
        s += ", mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendFuncSeparate: {
        std::string s = "glBlendFuncSeparate(";
        GLenum a_sfactorRGB = cur.Read<GLenum>();
        s += "sfactorRGB=";
        if (const char* nm = LookupEnumName(a_sfactorRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_sfactorRGB); s += buf; }
        GLenum a_dfactorRGB = cur.Read<GLenum>();
        s += ", dfactorRGB=";
        if (const char* nm = LookupEnumName(a_dfactorRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dfactorRGB); s += buf; }
        GLenum a_sfactorAlpha = cur.Read<GLenum>();
        s += ", sfactorAlpha=";
        if (const char* nm = LookupEnumName(a_sfactorAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_sfactorAlpha); s += buf; }
        GLenum a_dfactorAlpha = cur.Read<GLenum>();
        s += ", dfactorAlpha=";
        if (const char* nm = LookupEnumName(a_dfactorAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dfactorAlpha); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendFuncSeparatei: {
        std::string s = "glBlendFuncSeparatei(";
        GLuint a_buf = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buf=%u", a_buf); s += buf;
        GLenum a_srcRGB = cur.Read<GLenum>();
        s += ", srcRGB=";
        if (const char* nm = LookupEnumName(a_srcRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_srcRGB); s += buf; }
        GLenum a_dstRGB = cur.Read<GLenum>();
        s += ", dstRGB=";
        if (const char* nm = LookupEnumName(a_dstRGB)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dstRGB); s += buf; }
        GLenum a_srcAlpha = cur.Read<GLenum>();
        s += ", srcAlpha=";
        if (const char* nm = LookupEnumName(a_srcAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_srcAlpha); s += buf; }
        GLenum a_dstAlpha = cur.Read<GLenum>();
        s += ", dstAlpha=";
        if (const char* nm = LookupEnumName(a_dstAlpha)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dstAlpha); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlendFunci: {
        std::string s = "glBlendFunci(";
        GLuint a_buf = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buf=%u", a_buf); s += buf;
        GLenum a_src = cur.Read<GLenum>();
        s += ", src=";
        if (const char* nm = LookupEnumName(a_src)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_src); s += buf; }
        GLenum a_dst = cur.Read<GLenum>();
        s += ", dst=";
        if (const char* nm = LookupEnumName(a_dst)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dst); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlitFramebuffer: {
        std::string s = "glBlitFramebuffer(";
        GLint a_srcX0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "srcX0=%d", a_srcX0); s += buf;
        GLint a_srcY0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcY0=%d", a_srcY0); s += buf;
        GLint a_srcX1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcX1=%d", a_srcX1); s += buf;
        GLint a_srcY1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcY1=%d", a_srcY1); s += buf;
        GLint a_dstX0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstX0=%d", a_dstX0); s += buf;
        GLint a_dstY0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstY0=%d", a_dstY0); s += buf;
        GLint a_dstX1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstX1=%d", a_dstX1); s += buf;
        GLint a_dstY1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstY1=%d", a_dstY1); s += buf;
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += ", mask="; s += FormatBitfield(a_mask);
        GLenum a_filter = cur.Read<GLenum>();
        s += ", filter=";
        if (const char* nm = LookupEnumName(a_filter)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_filter); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glBlitNamedFramebuffer: {
        std::string s = "glBlitNamedFramebuffer(";
        GLuint a_readFramebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "readFramebuffer=%u", a_readFramebuffer); s += buf;
        GLuint a_drawFramebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", drawFramebuffer=%u", a_drawFramebuffer); s += buf;
        GLint a_srcX0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcX0=%d", a_srcX0); s += buf;
        GLint a_srcY0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcY0=%d", a_srcY0); s += buf;
        GLint a_srcX1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcX1=%d", a_srcX1); s += buf;
        GLint a_srcY1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcY1=%d", a_srcY1); s += buf;
        GLint a_dstX0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstX0=%d", a_dstX0); s += buf;
        GLint a_dstY0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstY0=%d", a_dstY0); s += buf;
        GLint a_dstX1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstX1=%d", a_dstX1); s += buf;
        GLint a_dstY1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstY1=%d", a_dstY1); s += buf;
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += ", mask="; s += FormatBitfield(a_mask);
        GLenum a_filter = cur.Read<GLenum>();
        s += ", filter=";
        if (const char* nm = LookupEnumName(a_filter)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_filter); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glClampColor: {
        std::string s = "glClampColor(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_clamp = cur.Read<GLenum>();
        s += ", clamp=";
        if (const char* nm = LookupEnumName(a_clamp)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_clamp); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glClearBufferfi: {
        std::string s = "glClearBufferfi(";
        GLenum a_buffer = cur.Read<GLenum>();
        s += "buffer=";
        if (const char* nm = LookupEnumName(a_buffer)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_buffer); s += buf; }
        GLint a_drawbuffer = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", drawbuffer=%d", a_drawbuffer); s += buf;
        GLfloat a_depth = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", depth=%g", a_depth); s += buf;
        GLint a_stencil = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", stencil=%d", a_stencil); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearDepthf: {
        std::string s = "glClearDepthf(";
        GLfloat a_d = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "d=%g", a_d); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearNamedFramebufferfi: {
        std::string s = "glClearNamedFramebufferfi(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_buffer = cur.Read<GLenum>();
        s += ", buffer=";
        if (const char* nm = LookupEnumName(a_buffer)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_buffer); s += buf; }
        GLint a_drawbuffer = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", drawbuffer=%d", a_drawbuffer); s += buf;
        GLfloat a_depth = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", depth=%g", a_depth); s += buf;
        GLint a_stencil = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", stencil=%d", a_stencil); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClientActiveTexture: {
        std::string s = "glClientActiveTexture(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glClipControl: {
        std::string s = "glClipControl(";
        GLenum a_origin = cur.Read<GLenum>();
        s += "origin=";
        if (const char* nm = LookupEnumName(a_origin)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_origin); s += buf; }
        GLenum a_depth = cur.Read<GLenum>();
        s += ", depth=";
        if (const char* nm = LookupEnumName(a_depth)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_depth); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glColorMaski: {
        std::string s = "glColorMaski(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLboolean a_r = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        GLboolean a_g = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", g=%d", a_g); s += buf;
        GLboolean a_b = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", b=%d", a_b); s += buf;
        GLboolean a_a = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", a=%d", a_a); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColorP3ui: {
        std::string s = "glColorP3ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_color = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", color=%u", a_color); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glColorP4ui: {
        std::string s = "glColorP4ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_color = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", color=%u", a_color); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyBufferSubData: {
        std::string s = "glCopyBufferSubData(";
        GLenum a_readTarget = cur.Read<GLenum>();
        s += "readTarget=";
        if (const char* nm = LookupEnumName(a_readTarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_readTarget); s += buf; }
        GLenum a_writeTarget = cur.Read<GLenum>();
        s += ", writeTarget=";
        if (const char* nm = LookupEnumName(a_writeTarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_writeTarget); s += buf; }
        GLintptr a_readOffset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", readOffset=%lld", a_readOffset); s += buf;
        GLintptr a_writeOffset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", writeOffset=%lld", a_writeOffset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyImageSubData: {
        std::string s = "glCopyImageSubData(";
        GLuint a_srcName = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "srcName=%u", a_srcName); s += buf;
        GLenum a_srcTarget = cur.Read<GLenum>();
        s += ", srcTarget=";
        if (const char* nm = LookupEnumName(a_srcTarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_srcTarget); s += buf; }
        GLint a_srcLevel = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcLevel=%d", a_srcLevel); s += buf;
        GLint a_srcX = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcX=%d", a_srcX); s += buf;
        GLint a_srcY = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcY=%d", a_srcY); s += buf;
        GLint a_srcZ = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", srcZ=%d", a_srcZ); s += buf;
        GLuint a_dstName = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", dstName=%u", a_dstName); s += buf;
        GLenum a_dstTarget = cur.Read<GLenum>();
        s += ", dstTarget=";
        if (const char* nm = LookupEnumName(a_dstTarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dstTarget); s += buf; }
        GLint a_dstLevel = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstLevel=%d", a_dstLevel); s += buf;
        GLint a_dstX = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstX=%d", a_dstX); s += buf;
        GLint a_dstY = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstY=%d", a_dstY); s += buf;
        GLint a_dstZ = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", dstZ=%d", a_dstZ); s += buf;
        GLsizei a_srcWidth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", srcWidth=%d", a_srcWidth); s += buf;
        GLsizei a_srcHeight = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", srcHeight=%d", a_srcHeight); s += buf;
        GLsizei a_srcDepth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", srcDepth=%d", a_srcDepth); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyNamedBufferSubData: {
        std::string s = "glCopyNamedBufferSubData(";
        GLuint a_readBuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "readBuffer=%u", a_readBuffer); s += buf;
        GLuint a_writeBuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", writeBuffer=%u", a_writeBuffer); s += buf;
        GLintptr a_readOffset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", readOffset=%lld", a_readOffset); s += buf;
        GLintptr a_writeOffset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", writeOffset=%lld", a_writeOffset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTexSubImage3D: {
        std::string s = "glCopyTexSubImage3D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_yoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", yoffset=%d", a_yoffset); s += buf;
        GLint a_zoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", zoffset=%d", a_zoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTextureSubImage1D: {
        std::string s = "glCopyTextureSubImage1D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTextureSubImage2D: {
        std::string s = "glCopyTextureSubImage2D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_yoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", yoffset=%d", a_yoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glCopyTextureSubImage3D: {
        std::string s = "glCopyTextureSubImage3D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_yoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", yoffset=%d", a_yoffset); s += buf;
        GLint a_zoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", zoffset=%d", a_zoffset); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDeleteSync: {
        std::string s = "glDeleteSync(";
        GLsync a_sync = cur.Read<GLsync>();
        snprintf(buf, sizeof(buf), "sync=%p", a_sync); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDepthRangeIndexed: {
        std::string s = "glDepthRangeIndexed(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_n = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", n=%g", a_n); s += buf;
        GLdouble a_f = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", f=%g", a_f); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDepthRangef: {
        std::string s = "glDepthRangef(";
        GLfloat a_n = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "n=%g", a_n); s += buf;
        GLfloat a_f = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", f=%g", a_f); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDisableVertexArrayAttrib: {
        std::string s = "glDisableVertexArrayAttrib(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDisablei: {
        std::string s = "glDisablei(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDispatchCompute: {
        std::string s = "glDispatchCompute(";
        GLuint a_num_groups_x = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "num_groups_x=%u", a_num_groups_x); s += buf;
        GLuint a_num_groups_y = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", num_groups_y=%u", a_num_groups_y); s += buf;
        GLuint a_num_groups_z = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", num_groups_z=%u", a_num_groups_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDispatchComputeIndirect: {
        std::string s = "glDispatchComputeIndirect(";
        GLintptr a_indirect = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), "indirect=%lld", a_indirect); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawArraysInstancedBaseInstance: {
        std::string s = "glDrawArraysInstancedBaseInstance(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLint a_first = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", first=%d", a_first); s += buf;
        GLsizei a_count = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", count=%d", a_count); s += buf;
        GLsizei a_instancecount = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", instancecount=%d", a_instancecount); s += buf;
        GLuint a_baseinstance = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", baseinstance=%u", a_baseinstance); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawTransformFeedback: {
        std::string s = "glDrawTransformFeedback(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawTransformFeedbackInstanced: {
        std::string s = "glDrawTransformFeedbackInstanced(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        GLsizei a_instancecount = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", instancecount=%d", a_instancecount); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawTransformFeedbackStream: {
        std::string s = "glDrawTransformFeedbackStream(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        GLuint a_stream = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", stream=%u", a_stream); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glDrawTransformFeedbackStreamInstanced: {
        std::string s = "glDrawTransformFeedbackStreamInstanced(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", id=%u", a_id); s += buf;
        GLuint a_stream = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", stream=%u", a_stream); s += buf;
        GLsizei a_instancecount = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", instancecount=%d", a_instancecount); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEnableVertexArrayAttrib: {
        std::string s = "glEnableVertexArrayAttrib(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEnablei: {
        std::string s = "glEnablei(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEndConditionalRender: {
        std::string s = "glEndConditionalRender(";
        s += ")";
        return s;
    }
    case GLFuncId::glEndQuery: {
        std::string s = "glEndQuery(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glEndQueryIndexed: {
        std::string s = "glEndQueryIndexed(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glEndTransformFeedback: {
        std::string s = "glEndTransformFeedback(";
        s += ")";
        return s;
    }
    case GLFuncId::glFlushMappedBufferRange: {
        std::string s = "glFlushMappedBufferRange(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", length=%lld", a_length); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFlushMappedNamedBufferRange: {
        std::string s = "glFlushMappedNamedBufferRange(";
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", length=%lld", a_length); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFogCoordd: {
        std::string s = "glFogCoordd(";
        GLdouble a_coord = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "coord=%g", a_coord); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFogCoordf: {
        std::string s = "glFogCoordf(";
        GLfloat a_coord = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "coord=%g", a_coord); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferParameteri: {
        std::string s = "glFramebufferParameteri(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferTexture: {
        std::string s = "glFramebufferTexture(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferTexture1D: {
        std::string s = "glFramebufferTexture1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLenum a_textarget = cur.Read<GLenum>();
        s += ", textarget=";
        if (const char* nm = LookupEnumName(a_textarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_textarget); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferTexture3D: {
        std::string s = "glFramebufferTexture3D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLenum a_textarget = cur.Read<GLenum>();
        s += ", textarget=";
        if (const char* nm = LookupEnumName(a_textarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_textarget); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_zoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", zoffset=%d", a_zoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glFramebufferTextureLayer: {
        std::string s = "glFramebufferTextureLayer(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_layer = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", layer=%d", a_layer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGenerateTextureMipmap: {
        std::string s = "glGenerateTextureMipmap(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGetQueryBufferObjecti64v: {
        std::string s = "glGetQueryBufferObjecti64v(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGetQueryBufferObjectiv: {
        std::string s = "glGetQueryBufferObjectiv(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGetQueryBufferObjectui64v: {
        std::string s = "glGetQueryBufferObjectui64v(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glGetQueryBufferObjectuiv: {
        std::string s = "glGetQueryBufferObjectuiv(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glInvalidateBufferData: {
        std::string s = "glInvalidateBufferData(";
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glInvalidateBufferSubData: {
        std::string s = "glInvalidateBufferSubData(";
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", length=%lld", a_length); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glInvalidateTexImage: {
        std::string s = "glInvalidateTexImage(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glInvalidateTexSubImage: {
        std::string s = "glInvalidateTexSubImage(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_xoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", xoffset=%d", a_xoffset); s += buf;
        GLint a_yoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", yoffset=%d", a_yoffset); s += buf;
        GLint a_zoffset = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", zoffset=%d", a_zoffset); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMemoryBarrier: {
        std::string s = "glMemoryBarrier(";
        GLbitfield a_barriers = cur.Read<GLbitfield>();
        s += "barriers="; s += FormatBitfield(a_barriers);
        s += ")";
        return s;
    }
    case GLFuncId::glMemoryBarrierByRegion: {
        std::string s = "glMemoryBarrierByRegion(";
        GLbitfield a_barriers = cur.Read<GLbitfield>();
        s += "barriers="; s += FormatBitfield(a_barriers);
        s += ")";
        return s;
    }
    case GLFuncId::glMinSampleShading: {
        std::string s = "glMinSampleShading(";
        GLfloat a_value = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "value=%g", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord1d: {
        std::string s = "glMultiTexCoord1d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord1f: {
        std::string s = "glMultiTexCoord1f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord1i: {
        std::string s = "glMultiTexCoord1i(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord1s: {
        std::string s = "glMultiTexCoord1s(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord2d: {
        std::string s = "glMultiTexCoord2d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord2f: {
        std::string s = "glMultiTexCoord2f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord2i: {
        std::string s = "glMultiTexCoord2i(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord2s: {
        std::string s = "glMultiTexCoord2s(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord3d: {
        std::string s = "glMultiTexCoord3d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord3f: {
        std::string s = "glMultiTexCoord3f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord3i: {
        std::string s = "glMultiTexCoord3i(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLint a_r = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord3s: {
        std::string s = "glMultiTexCoord3s(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLshort a_r = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord4d: {
        std::string s = "glMultiTexCoord4d(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLdouble a_s = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLdouble a_t = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLdouble a_r = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLdouble a_q = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", q=%g", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord4f: {
        std::string s = "glMultiTexCoord4f(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLfloat a_s = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", s=%g", a_s); s += buf;
        GLfloat a_t = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", t=%g", a_t); s += buf;
        GLfloat a_r = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", r=%g", a_r); s += buf;
        GLfloat a_q = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", q=%g", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord4i: {
        std::string s = "glMultiTexCoord4i(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLint a_s = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLint a_t = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLint a_r = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        GLint a_q = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", q=%d", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoord4s: {
        std::string s = "glMultiTexCoord4s(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLshort a_s = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", s=%d", a_s); s += buf;
        GLshort a_t = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", t=%d", a_t); s += buf;
        GLshort a_r = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", r=%d", a_r); s += buf;
        GLshort a_q = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", q=%d", a_q); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoordP1ui: {
        std::string s = "glMultiTexCoordP1ui(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoordP2ui: {
        std::string s = "glMultiTexCoordP2ui(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoordP3ui: {
        std::string s = "glMultiTexCoordP3ui(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glMultiTexCoordP4ui: {
        std::string s = "glMultiTexCoordP4ui(";
        GLenum a_texture = cur.Read<GLenum>();
        s += "texture=";
        if (const char* nm = LookupEnumName(a_texture)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_texture); s += buf; }
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferDrawBuffer: {
        std::string s = "glNamedFramebufferDrawBuffer(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_buf = cur.Read<GLenum>();
        s += ", buf=";
        if (const char* nm = LookupEnumName(a_buf)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_buf); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferParameteri: {
        std::string s = "glNamedFramebufferParameteri(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferReadBuffer: {
        std::string s = "glNamedFramebufferReadBuffer(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_src = cur.Read<GLenum>();
        s += ", src=";
        if (const char* nm = LookupEnumName(a_src)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_src); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferRenderbuffer: {
        std::string s = "glNamedFramebufferRenderbuffer(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLenum a_renderbuffertarget = cur.Read<GLenum>();
        s += ", renderbuffertarget=";
        if (const char* nm = LookupEnumName(a_renderbuffertarget)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_renderbuffertarget); s += buf; }
        GLuint a_renderbuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", renderbuffer=%u", a_renderbuffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferTexture: {
        std::string s = "glNamedFramebufferTexture(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedFramebufferTextureLayer: {
        std::string s = "glNamedFramebufferTextureLayer(";
        GLuint a_framebuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "framebuffer=%u", a_framebuffer); s += buf;
        GLenum a_attachment = cur.Read<GLenum>();
        s += ", attachment=";
        if (const char* nm = LookupEnumName(a_attachment)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_attachment); s += buf; }
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", texture=%u", a_texture); s += buf;
        GLint a_level = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", level=%d", a_level); s += buf;
        GLint a_layer = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", layer=%d", a_layer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedRenderbufferStorage: {
        std::string s = "glNamedRenderbufferStorage(";
        GLuint a_renderbuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "renderbuffer=%u", a_renderbuffer); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNamedRenderbufferStorageMultisample: {
        std::string s = "glNamedRenderbufferStorageMultisample(";
        GLuint a_renderbuffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "renderbuffer=%u", a_renderbuffer); s += buf;
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glNormalP3ui: {
        std::string s = "glNormalP3ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPatchParameteri: {
        std::string s = "glPatchParameteri(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_value = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", value=%d", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPauseTransformFeedback: {
        std::string s = "glPauseTransformFeedback(";
        s += ")";
        return s;
    }
    case GLFuncId::glPointParameterf: {
        std::string s = "glPointParameterf(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPointParameteri: {
        std::string s = "glPointParameteri(";
        GLenum a_pname = cur.Read<GLenum>();
        s += "pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPolygonOffsetClamp: {
        std::string s = "glPolygonOffsetClamp(";
        GLfloat a_factor = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "factor=%g", a_factor); s += buf;
        GLfloat a_units = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", units=%g", a_units); s += buf;
        GLfloat a_clamp = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", clamp=%g", a_clamp); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glPopDebugGroup: {
        std::string s = "glPopDebugGroup(";
        s += ")";
        return s;
    }
    case GLFuncId::glPrimitiveRestartIndex: {
        std::string s = "glPrimitiveRestartIndex(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramParameteri: {
        std::string s = "glProgramParameteri(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_value = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", value=%d", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform1d: {
        std::string s = "glProgramUniform1d(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLdouble a_v0 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform1f: {
        std::string s = "glProgramUniform1f(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform1i: {
        std::string s = "glProgramUniform1i(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform1ui: {
        std::string s = "glProgramUniform1ui(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform2d: {
        std::string s = "glProgramUniform2d(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLdouble a_v0 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLdouble a_v1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform2f: {
        std::string s = "glProgramUniform2f(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform2i: {
        std::string s = "glProgramUniform2i(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform2ui: {
        std::string s = "glProgramUniform2ui(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform3d: {
        std::string s = "glProgramUniform3d(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLdouble a_v0 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLdouble a_v1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLdouble a_v2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform3f: {
        std::string s = "glProgramUniform3f(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform3i: {
        std::string s = "glProgramUniform3i(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        GLint a_v2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v2=%d", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform3ui: {
        std::string s = "glProgramUniform3ui(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        GLuint a_v2 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v2=%u", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform4d: {
        std::string s = "glProgramUniform4d(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLdouble a_v0 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLdouble a_v1 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLdouble a_v2 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        GLdouble a_v3 = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", v3=%g", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform4f: {
        std::string s = "glProgramUniform4f(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLfloat a_v0 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v0=%g", a_v0); s += buf;
        GLfloat a_v1 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v1=%g", a_v1); s += buf;
        GLfloat a_v2 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v2=%g", a_v2); s += buf;
        GLfloat a_v3 = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", v3=%g", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform4i: {
        std::string s = "glProgramUniform4i(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        GLint a_v2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v2=%d", a_v2); s += buf;
        GLint a_v3 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v3=%d", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProgramUniform4ui: {
        std::string s = "glProgramUniform4ui(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        GLuint a_v2 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v2=%u", a_v2); s += buf;
        GLuint a_v3 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v3=%u", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glProvokingVertex: {
        std::string s = "glProvokingVertex(";
        GLenum a_mode = cur.Read<GLenum>();
        s += "mode=";
        if (const char* nm = LookupEnumName(a_mode)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_mode); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glQueryCounter: {
        std::string s = "glQueryCounter(";
        GLuint a_id = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "id=%u", a_id); s += buf;
        GLenum a_target = cur.Read<GLenum>();
        s += ", target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glReleaseShaderCompiler: {
        std::string s = "glReleaseShaderCompiler(";
        s += ")";
        return s;
    }
    case GLFuncId::glRenderbufferStorageMultisample: {
        std::string s = "glRenderbufferStorageMultisample(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glResumeTransformFeedback: {
        std::string s = "glResumeTransformFeedback(";
        s += ")";
        return s;
    }
    case GLFuncId::glSampleCoverage: {
        std::string s = "glSampleCoverage(";
        GLfloat a_value = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "value=%g", a_value); s += buf;
        GLboolean a_invert = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", invert=%d", a_invert); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSampleMaski: {
        std::string s = "glSampleMaski(";
        GLuint a_maskNumber = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "maskNumber=%u", a_maskNumber); s += buf;
        GLbitfield a_mask = cur.Read<GLbitfield>();
        s += ", mask="; s += FormatBitfield(a_mask);
        s += ")";
        return s;
    }
    case GLFuncId::glSamplerParameterf: {
        std::string s = "glSamplerParameterf(";
        GLuint a_sampler = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "sampler=%u", a_sampler); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSamplerParameteri: {
        std::string s = "glSamplerParameteri(";
        GLuint a_sampler = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "sampler=%u", a_sampler); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glScissorIndexed: {
        std::string s = "glScissorIndexed(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLint a_left = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", left=%d", a_left); s += buf;
        GLint a_bottom = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", bottom=%d", a_bottom); s += buf;
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3b: {
        std::string s = "glSecondaryColor3b(";
        GLbyte a_red = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLbyte a_green = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLbyte a_blue = cur.Read<GLbyte>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3d: {
        std::string s = "glSecondaryColor3d(";
        GLdouble a_red = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLdouble a_green = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLdouble a_blue = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3f: {
        std::string s = "glSecondaryColor3f(";
        GLfloat a_red = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "red=%g", a_red); s += buf;
        GLfloat a_green = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", green=%g", a_green); s += buf;
        GLfloat a_blue = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", blue=%g", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3i: {
        std::string s = "glSecondaryColor3i(";
        GLint a_red = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLint a_green = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLint a_blue = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3s: {
        std::string s = "glSecondaryColor3s(";
        GLshort a_red = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "red=%d", a_red); s += buf;
        GLshort a_green = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", green=%d", a_green); s += buf;
        GLshort a_blue = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", blue=%d", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3ub: {
        std::string s = "glSecondaryColor3ub(";
        GLubyte a_red = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLubyte a_green = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLubyte a_blue = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3ui: {
        std::string s = "glSecondaryColor3ui(";
        GLuint a_red = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLuint a_green = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLuint a_blue = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColor3us: {
        std::string s = "glSecondaryColor3us(";
        GLushort a_red = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), "red=%u", a_red); s += buf;
        GLushort a_green = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", green=%u", a_green); s += buf;
        GLushort a_blue = cur.Read<GLushort>();
        snprintf(buf, sizeof(buf), ", blue=%u", a_blue); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glSecondaryColorP3ui: {
        std::string s = "glSecondaryColorP3ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_color = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", color=%u", a_color); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glShaderStorageBlockBinding: {
        std::string s = "glShaderStorageBlockBinding(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLuint a_storageBlockIndex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", storageBlockIndex=%u", a_storageBlockIndex); s += buf;
        GLuint a_storageBlockBinding = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", storageBlockBinding=%u", a_storageBlockBinding); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glStencilFuncSeparate: {
        std::string s = "glStencilFuncSeparate(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_func = cur.Read<GLenum>();
        s += ", func=";
        if (const char* nm = LookupEnumName(a_func)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_func); s += buf; }
        GLint a_ref = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", ref=%d", a_ref); s += buf;
        GLuint a_mask = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", mask=%u", a_mask); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glStencilMaskSeparate: {
        std::string s = "glStencilMaskSeparate(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLuint a_mask = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", mask=%u", a_mask); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glStencilOpSeparate: {
        std::string s = "glStencilOpSeparate(";
        GLenum a_face = cur.Read<GLenum>();
        s += "face=";
        if (const char* nm = LookupEnumName(a_face)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_face); s += buf; }
        GLenum a_sfail = cur.Read<GLenum>();
        s += ", sfail=";
        if (const char* nm = LookupEnumName(a_sfail)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_sfail); s += buf; }
        GLenum a_dpfail = cur.Read<GLenum>();
        s += ", dpfail=";
        if (const char* nm = LookupEnumName(a_dpfail)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dpfail); s += buf; }
        GLenum a_dppass = cur.Read<GLenum>();
        s += ", dppass=";
        if (const char* nm = LookupEnumName(a_dppass)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_dppass); s += buf; }
        s += ")";
        return s;
    }
    case GLFuncId::glTexBuffer: {
        std::string s = "glTexBuffer(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexBufferRange: {
        std::string s = "glTexBufferRange(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoordP1ui: {
        std::string s = "glTexCoordP1ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoordP2ui: {
        std::string s = "glTexCoordP2ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoordP3ui: {
        std::string s = "glTexCoordP3ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexCoordP4ui: {
        std::string s = "glTexCoordP4ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_coords = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", coords=%u", a_coords); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexImage2DMultisample: {
        std::string s = "glTexImage2DMultisample(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexImage3DMultisample: {
        std::string s = "glTexImage3DMultisample(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexStorage1D: {
        std::string s = "glTexStorage1D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexStorage2D: {
        std::string s = "glTexStorage2D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexStorage2DMultisample: {
        std::string s = "glTexStorage2DMultisample(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexStorage3D: {
        std::string s = "glTexStorage3D(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTexStorage3DMultisample: {
        std::string s = "glTexStorage3DMultisample(";
        GLenum a_target = cur.Read<GLenum>();
        s += "target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureBarrier: {
        std::string s = "glTextureBarrier(";
        s += ")";
        return s;
    }
    case GLFuncId::glTextureBuffer: {
        std::string s = "glTextureBuffer(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureBufferRange: {
        std::string s = "glTextureBufferRange(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureParameterf: {
        std::string s = "glTextureParameterf(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLfloat a_param = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", param=%g", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureParameteri: {
        std::string s = "glTextureParameteri(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLenum a_pname = cur.Read<GLenum>();
        s += ", pname=";
        if (const char* nm = LookupEnumName(a_pname)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_pname); s += buf; }
        GLint a_param = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", param=%d", a_param); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureStorage1D: {
        std::string s = "glTextureStorage1D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureStorage2D: {
        std::string s = "glTextureStorage2D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureStorage2DMultisample: {
        std::string s = "glTextureStorage2DMultisample(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureStorage3D: {
        std::string s = "glTextureStorage3D(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLsizei a_levels = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", levels=%d", a_levels); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureStorage3DMultisample: {
        std::string s = "glTextureStorage3DMultisample(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLsizei a_samples = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", samples=%d", a_samples); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLsizei a_width = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", width=%d", a_width); s += buf;
        GLsizei a_height = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", height=%d", a_height); s += buf;
        GLsizei a_depth = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", depth=%d", a_depth); s += buf;
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", fixedsamplelocations=%d", a_fixedsamplelocations); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTextureView: {
        std::string s = "glTextureView(";
        GLuint a_texture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "texture=%u", a_texture); s += buf;
        GLenum a_target = cur.Read<GLenum>();
        s += ", target=";
        if (const char* nm = LookupEnumName(a_target)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_target); s += buf; }
        GLuint a_origtexture = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", origtexture=%u", a_origtexture); s += buf;
        GLenum a_internalformat = cur.Read<GLenum>();
        s += ", internalformat=";
        if (const char* nm = LookupEnumName(a_internalformat)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_internalformat); s += buf; }
        GLuint a_minlevel = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", minlevel=%u", a_minlevel); s += buf;
        GLuint a_numlevels = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", numlevels=%u", a_numlevels); s += buf;
        GLuint a_minlayer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", minlayer=%u", a_minlayer); s += buf;
        GLuint a_numlayers = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", numlayers=%u", a_numlayers); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTransformFeedbackBufferBase: {
        std::string s = "glTransformFeedbackBufferBase(";
        GLuint a_xfb = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "xfb=%u", a_xfb); s += buf;
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glTransformFeedbackBufferRange: {
        std::string s = "glTransformFeedbackBufferRange(";
        GLuint a_xfb = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "xfb=%u", a_xfb); s += buf;
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", index=%u", a_index); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        snprintf(buf, sizeof(buf), ", size=%lld", a_size); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform1d: {
        std::string s = "glUniform1d(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform1ui: {
        std::string s = "glUniform1ui(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform2d: {
        std::string s = "glUniform2d(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform2i: {
        std::string s = "glUniform2i(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform2ui: {
        std::string s = "glUniform2ui(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform3d: {
        std::string s = "glUniform3d(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform3i: {
        std::string s = "glUniform3i(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        GLint a_v2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v2=%d", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform3ui: {
        std::string s = "glUniform3ui(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        GLuint a_v2 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v2=%u", a_v2); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform4d: {
        std::string s = "glUniform4d(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLdouble a_w = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform4i: {
        std::string s = "glUniform4i(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLint a_v0 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v0=%d", a_v0); s += buf;
        GLint a_v1 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v1=%d", a_v1); s += buf;
        GLint a_v2 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v2=%d", a_v2); s += buf;
        GLint a_v3 = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", v3=%d", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniform4ui: {
        std::string s = "glUniform4ui(";
        GLint a_location = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "location=%d", a_location); s += buf;
        GLuint a_v0 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v0=%u", a_v0); s += buf;
        GLuint a_v1 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v1=%u", a_v1); s += buf;
        GLuint a_v2 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v2=%u", a_v2); s += buf;
        GLuint a_v3 = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", v3=%u", a_v3); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUniformBlockBinding: {
        std::string s = "glUniformBlockBinding(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        GLuint a_uniformBlockIndex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", uniformBlockIndex=%u", a_uniformBlockIndex); s += buf;
        GLuint a_uniformBlockBinding = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", uniformBlockBinding=%u", a_uniformBlockBinding); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glUseProgramStages: {
        std::string s = "glUseProgramStages(";
        GLuint a_pipeline = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "pipeline=%u", a_pipeline); s += buf;
        GLbitfield a_stages = cur.Read<GLbitfield>();
        s += ", stages="; s += FormatBitfield(a_stages);
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glValidateProgram: {
        std::string s = "glValidateProgram(";
        GLuint a_program = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "program=%u", a_program); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glValidateProgramPipeline: {
        std::string s = "glValidateProgramPipeline(";
        GLuint a_pipeline = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "pipeline=%u", a_pipeline); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayAttribBinding: {
        std::string s = "glVertexArrayAttribBinding(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", attribindex=%u", a_attribindex); s += buf;
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", bindingindex=%u", a_bindingindex); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayAttribFormat: {
        std::string s = "glVertexArrayAttribFormat(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayAttribIFormat: {
        std::string s = "glVertexArrayAttribIFormat(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayAttribLFormat: {
        std::string s = "glVertexArrayAttribLFormat(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayBindingDivisor: {
        std::string s = "glVertexArrayBindingDivisor(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", bindingindex=%u", a_bindingindex); s += buf;
        GLuint a_divisor = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", divisor=%u", a_divisor); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayElementBuffer: {
        std::string s = "glVertexArrayElementBuffer(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexArrayVertexBuffer: {
        std::string s = "glVertexArrayVertexBuffer(";
        GLuint a_vaobj = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "vaobj=%u", a_vaobj); s += buf;
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", bindingindex=%u", a_bindingindex); s += buf;
        GLuint a_buffer = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", buffer=%u", a_buffer); s += buf;
        GLintptr a_offset = cur.Read<GLintptr>();
        snprintf(buf, sizeof(buf), ", offset=%lld", a_offset); s += buf;
        GLsizei a_stride = cur.Read<GLsizei>();
        snprintf(buf, sizeof(buf), ", stride=%d", a_stride); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib1d: {
        std::string s = "glVertexAttrib1d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib1f: {
        std::string s = "glVertexAttrib1f(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib1s: {
        std::string s = "glVertexAttrib1s(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib2d: {
        std::string s = "glVertexAttrib2d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib2f: {
        std::string s = "glVertexAttrib2f(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib2s: {
        std::string s = "glVertexAttrib2s(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib3d: {
        std::string s = "glVertexAttrib3d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib3f: {
        std::string s = "glVertexAttrib3f(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib3s: {
        std::string s = "glVertexAttrib3s(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib4Nub: {
        std::string s = "glVertexAttrib4Nub(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLubyte a_x = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", x=%u", a_x); s += buf;
        GLubyte a_y = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", y=%u", a_y); s += buf;
        GLubyte a_z = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", z=%u", a_z); s += buf;
        GLubyte a_w = cur.Read<GLubyte>();
        snprintf(buf, sizeof(buf), ", w=%u", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib4d: {
        std::string s = "glVertexAttrib4d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLdouble a_w = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib4f: {
        std::string s = "glVertexAttrib4f(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLfloat a_w = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttrib4s: {
        std::string s = "glVertexAttrib4s(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLshort a_w = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribBinding: {
        std::string s = "glVertexAttribBinding(";
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "attribindex=%u", a_attribindex); s += buf;
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", bindingindex=%u", a_bindingindex); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribDivisor: {
        std::string s = "glVertexAttribDivisor(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLuint a_divisor = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", divisor=%u", a_divisor); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribFormat: {
        std::string s = "glVertexAttribFormat(";
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI1i: {
        std::string s = "glVertexAttribI1i(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI1ui: {
        std::string s = "glVertexAttribI1ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLuint a_x = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", x=%u", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI2i: {
        std::string s = "glVertexAttribI2i(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI2ui: {
        std::string s = "glVertexAttribI2ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLuint a_x = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", x=%u", a_x); s += buf;
        GLuint a_y = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", y=%u", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI3i: {
        std::string s = "glVertexAttribI3i(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI3ui: {
        std::string s = "glVertexAttribI3ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLuint a_x = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", x=%u", a_x); s += buf;
        GLuint a_y = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", y=%u", a_y); s += buf;
        GLuint a_z = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", z=%u", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI4i: {
        std::string s = "glVertexAttribI4i(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        GLint a_w = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", w=%d", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribI4ui: {
        std::string s = "glVertexAttribI4ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLuint a_x = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", x=%u", a_x); s += buf;
        GLuint a_y = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", y=%u", a_y); s += buf;
        GLuint a_z = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", z=%u", a_z); s += buf;
        GLuint a_w = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", w=%u", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribIFormat: {
        std::string s = "glVertexAttribIFormat(";
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribL1d: {
        std::string s = "glVertexAttribL1d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribL2d: {
        std::string s = "glVertexAttribL2d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribL3d: {
        std::string s = "glVertexAttribL3d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribL4d: {
        std::string s = "glVertexAttribL4d(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        GLdouble a_w = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribLFormat: {
        std::string s = "glVertexAttribLFormat(";
        GLuint a_attribindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "attribindex=%u", a_attribindex); s += buf;
        GLint a_size = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", size=%d", a_size); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_relativeoffset = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", relativeoffset=%u", a_relativeoffset); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribP1ui: {
        std::string s = "glVertexAttribP1ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribP2ui: {
        std::string s = "glVertexAttribP2ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribP3ui: {
        std::string s = "glVertexAttribP3ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexAttribP4ui: {
        std::string s = "glVertexAttribP4ui(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLenum a_type = cur.Read<GLenum>();
        s += ", type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLboolean a_normalized = cur.Read<GLboolean>();
        snprintf(buf, sizeof(buf), ", normalized=%d", a_normalized); s += buf;
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexBindingDivisor: {
        std::string s = "glVertexBindingDivisor(";
        GLuint a_bindingindex = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "bindingindex=%u", a_bindingindex); s += buf;
        GLuint a_divisor = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", divisor=%u", a_divisor); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexP2ui: {
        std::string s = "glVertexP2ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexP3ui: {
        std::string s = "glVertexP3ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glVertexP4ui: {
        std::string s = "glVertexP4ui(";
        GLenum a_type = cur.Read<GLenum>();
        s += "type=";
        if (const char* nm = LookupEnumName(a_type)) s += nm;
        else { snprintf(buf, sizeof(buf), "0x%X", a_type); s += buf; }
        GLuint a_value = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), ", value=%u", a_value); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glViewportIndexedf: {
        std::string s = "glViewportIndexedf(";
        GLuint a_index = cur.Read<GLuint>();
        snprintf(buf, sizeof(buf), "index=%u", a_index); s += buf;
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_w = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", w=%g", a_w); s += buf;
        GLfloat a_h = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", h=%g", a_h); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWaitSync: {
        std::string s = "glWaitSync(";
        GLsync a_sync = cur.Read<GLsync>();
        snprintf(buf, sizeof(buf), "sync=%p", a_sync); s += buf;
        GLbitfield a_flags = cur.Read<GLbitfield>();
        s += ", flags="; s += FormatBitfield(a_flags);
        GLuint64 a_timeout = cur.Read<GLuint64>();
        snprintf(buf, sizeof(buf), ", timeout=%llu", a_timeout); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos2d: {
        std::string s = "glWindowPos2d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos2f: {
        std::string s = "glWindowPos2f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos2i: {
        std::string s = "glWindowPos2i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos2s: {
        std::string s = "glWindowPos2s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos3d: {
        std::string s = "glWindowPos3d(";
        GLdouble a_x = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLdouble a_y = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLdouble a_z = cur.Read<GLdouble>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos3f: {
        std::string s = "glWindowPos3f(";
        GLfloat a_x = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), "x=%g", a_x); s += buf;
        GLfloat a_y = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", y=%g", a_y); s += buf;
        GLfloat a_z = cur.Read<GLfloat>();
        snprintf(buf, sizeof(buf), ", z=%g", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos3i: {
        std::string s = "glWindowPos3i(";
        GLint a_x = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLint a_y = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLint a_z = cur.Read<GLint>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glWindowPos3s: {
        std::string s = "glWindowPos3s(";
        GLshort a_x = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), "x=%d", a_x); s += buf;
        GLshort a_y = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", y=%d", a_y); s += buf;
        GLshort a_z = cur.Read<GLshort>();
        snprintf(buf, sizeof(buf), ", z=%d", a_z); s += buf;
        s += ")";
        return s;
    }
    case GLFuncId::glClearBufferfv: return Format_glClearBufferfv(args, len);
    case GLFuncId::glCreateBuffers: return Format_glCreateBuffers(args, len);
    case GLFuncId::glCreateFramebuffers: return Format_glCreateFramebuffers(args, len);
    case GLFuncId::glCreateRenderbuffers: return Format_glCreateRenderbuffers(args, len);
    case GLFuncId::glCreateTextures: return Format_glCreateTextures(args, len);
    case GLFuncId::glCreateVertexArrays: return Format_glCreateVertexArrays(args, len);
    case GLFuncId::glDebugMessageInsert: return Format_glDebugMessageInsert(args, len);
    case GLFuncId::glGetProgramInfoLog: return Format_glGetProgramInfoLog(args, len);
    case GLFuncId::glGetShaderInfoLog: return Format_glGetShaderInfoLog(args, len);
    case GLFuncId::glNamedBufferStorage: return Format_glNamedBufferStorage(args, len);
    case GLFuncId::glNamedBufferSubData: return Format_glNamedBufferSubData(args, len);
    case GLFuncId::glNamedFramebufferDrawBuffers: return Format_glNamedFramebufferDrawBuffers(args, len);
    case GLFuncId::glTextureSubImage2D: return Format_glTextureSubImage2D(args, len);
    case GLFuncId::glTextureSubImage3D: return Format_glTextureSubImage3D(args, len);
    case GLFuncId::wglCreateContext: return Format_wglCreateContext(args, len);
    case GLFuncId::wglDeleteContext: return Format_wglDeleteContext(args, len);
    case GLFuncId::wglMakeCurrent: return Format_wglMakeCurrent(args, len);
    case GLFuncId::wglShareLists: return Format_wglShareLists(args, len);
    case GLFuncId::wglSwapLayerBuffers: return Format_wglSwapLayerBuffers(args, len);
    case GLFuncId::wglCreateContextAttribsARB: return Format_wglCreateContextAttribsARB(args, len);
    default: return "?";
    }
}

// GENERATED FILE - do not edit by hand. See codegen/generate.py
#include "gl_replay_decode.h"
#include "gl_real_table.h"
#include "byte_cursor.h"

void ReplayDispatch(GLFuncId id, const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    switch (id) {
    case GLFuncId::glEnable: {
        GLenum a_cap = cur.Read<GLenum>();
        g_real.glEnable(a_cap);
        break;
    }
    case GLFuncId::glDisable: {
        GLenum a_cap = cur.Read<GLenum>();
        g_real.glDisable(a_cap);
        break;
    }
    case GLFuncId::glClearColor: {
        GLfloat a_r = cur.Read<GLfloat>();
        GLfloat a_g = cur.Read<GLfloat>();
        GLfloat a_b = cur.Read<GLfloat>();
        GLfloat a_a = cur.Read<GLfloat>();
        g_real.glClearColor(a_r, a_g, a_b, a_a);
        break;
    }
    case GLFuncId::glClearDepth: {
        GLdouble a_d = cur.Read<GLdouble>();
        g_real.glClearDepth(a_d);
        break;
    }
    case GLFuncId::glClear: {
        GLbitfield a_mask = cur.Read<GLbitfield>();
        g_real.glClear(a_mask);
        break;
    }
    case GLFuncId::glBlendFunc: {
        GLenum a_sfactor = cur.Read<GLenum>();
        GLenum a_dfactor = cur.Read<GLenum>();
        g_real.glBlendFunc(a_sfactor, a_dfactor);
        break;
    }
    case GLFuncId::glDepthFunc: {
        GLenum a_func = cur.Read<GLenum>();
        g_real.glDepthFunc(a_func);
        break;
    }
    case GLFuncId::glDepthMask: {
        GLboolean a_flag = cur.Read<GLboolean>();
        g_real.glDepthMask(a_flag);
        break;
    }
    case GLFuncId::glCullFace: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glCullFace(a_mode);
        break;
    }
    case GLFuncId::glFrontFace: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glFrontFace(a_mode);
        break;
    }
    case GLFuncId::glPolygonMode: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glPolygonMode(a_face, a_mode);
        break;
    }
    case GLFuncId::glLineWidth: {
        GLfloat a_width = cur.Read<GLfloat>();
        g_real.glLineWidth(a_width);
        break;
    }
    case GLFuncId::glPointSize: {
        GLfloat a_size = cur.Read<GLfloat>();
        g_real.glPointSize(a_size);
        break;
    }
    case GLFuncId::glViewport: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_w = cur.Read<GLsizei>();
        GLsizei a_h = cur.Read<GLsizei>();
        g_real.glViewport(a_x, a_y, a_w, a_h);
        break;
    }
    case GLFuncId::glScissor: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_w = cur.Read<GLsizei>();
        GLsizei a_h = cur.Read<GLsizei>();
        g_real.glScissor(a_x, a_y, a_w, a_h);
        break;
    }
    case GLFuncId::glMatrixMode: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glMatrixMode(a_mode);
        break;
    }
    case GLFuncId::glLoadIdentity: {
        g_real.glLoadIdentity();
        break;
    }
    case GLFuncId::glPushMatrix: {
        g_real.glPushMatrix();
        break;
    }
    case GLFuncId::glPopMatrix: {
        g_real.glPopMatrix();
        break;
    }
    case GLFuncId::glTranslatef: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glTranslatef(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glRotatef: {
        GLfloat a_angle = cur.Read<GLfloat>();
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glRotatef(a_angle, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glScalef: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glScalef(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glOrtho: {
        GLdouble a_l = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        GLdouble a_b = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_n = cur.Read<GLdouble>();
        GLdouble a_f = cur.Read<GLdouble>();
        g_real.glOrtho(a_l, a_r, a_b, a_t, a_n, a_f);
        break;
    }
    case GLFuncId::glFrustum: {
        GLdouble a_l = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        GLdouble a_b = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_n = cur.Read<GLdouble>();
        GLdouble a_f = cur.Read<GLdouble>();
        g_real.glFrustum(a_l, a_r, a_b, a_t, a_n, a_f);
        break;
    }
    case GLFuncId::glBegin: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glBegin(a_mode);
        break;
    }
    case GLFuncId::glEnd: {
        g_real.glEnd();
        break;
    }
    case GLFuncId::glVertex2f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        g_real.glVertex2f(a_x, a_y);
        break;
    }
    case GLFuncId::glVertex3f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glVertex3f(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertex4f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        GLfloat a_w = cur.Read<GLfloat>();
        g_real.glVertex4f(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glColor3f: {
        GLfloat a_r = cur.Read<GLfloat>();
        GLfloat a_g = cur.Read<GLfloat>();
        GLfloat a_b = cur.Read<GLfloat>();
        g_real.glColor3f(a_r, a_g, a_b);
        break;
    }
    case GLFuncId::glColor4f: {
        GLfloat a_r = cur.Read<GLfloat>();
        GLfloat a_g = cur.Read<GLfloat>();
        GLfloat a_b = cur.Read<GLfloat>();
        GLfloat a_a = cur.Read<GLfloat>();
        g_real.glColor4f(a_r, a_g, a_b, a_a);
        break;
    }
    case GLFuncId::glNormal3f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glNormal3f(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glTexCoord2f: {
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        g_real.glTexCoord2f(a_s, a_t);
        break;
    }
    case GLFuncId::glEnableClientState: {
        GLenum a_cap = cur.Read<GLenum>();
        g_real.glEnableClientState(a_cap);
        break;
    }
    case GLFuncId::glDisableClientState: {
        GLenum a_cap = cur.Read<GLenum>();
        g_real.glDisableClientState(a_cap);
        break;
    }
    case GLFuncId::glGenBuffers: Replay_glGenBuffers(args, len, remap); break;
    case GLFuncId::glDeleteBuffers: Replay_glDeleteBuffers(args, len, remap); break;
    case GLFuncId::glBindBuffer: Replay_glBindBuffer(args, len, remap); break;
    case GLFuncId::glBufferData: Replay_glBufferData(args, len, remap); break;
    case GLFuncId::glBufferSubData: Replay_glBufferSubData(args, len, remap); break;
    case GLFuncId::glGenVertexArrays: Replay_glGenVertexArrays(args, len, remap); break;
    case GLFuncId::glDeleteVertexArrays: Replay_glDeleteVertexArrays(args, len, remap); break;
    case GLFuncId::glBindVertexArray: {
        GLuint a_array = cur.Read<GLuint>();
        a_array = remap.Get("vertexarray", a_array);
        g_real.glBindVertexArray(a_array);
        break;
    }
    case GLFuncId::glEnableVertexAttribArray: {
        GLuint a_index = cur.Read<GLuint>();
        g_real.glEnableVertexAttribArray(a_index);
        break;
    }
    case GLFuncId::glDisableVertexAttribArray: {
        GLuint a_index = cur.Read<GLuint>();
        g_real.glDisableVertexAttribArray(a_index);
        break;
    }
    case GLFuncId::glVertexAttribPointer: Replay_glVertexAttribPointer(args, len, remap); break;
    case GLFuncId::glVertexPointer: Replay_glVertexPointer(args, len, remap); break;
    case GLFuncId::glColorPointer: Replay_glColorPointer(args, len, remap); break;
    case GLFuncId::glTexCoordPointer: Replay_glTexCoordPointer(args, len, remap); break;
    case GLFuncId::glNormalPointer: Replay_glNormalPointer(args, len, remap); break;
    case GLFuncId::glGenTextures: Replay_glGenTextures(args, len, remap); break;
    case GLFuncId::glDeleteTextures: Replay_glDeleteTextures(args, len, remap); break;
    case GLFuncId::glBindTexture: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        a_texture = remap.Get("texture", a_texture);
        g_real.glBindTexture(a_target, a_texture);
        break;
    }
    case GLFuncId::glActiveTexture: {
        GLenum a_texture = cur.Read<GLenum>();
        g_real.glActiveTexture(a_texture);
        break;
    }
    case GLFuncId::glTexParameteri: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glTexParameteri(a_target, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexParameterf: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glTexParameterf(a_target, a_pname, a_param);
        break;
    }
    case GLFuncId::glPixelStorei: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glPixelStorei(a_pname, a_param);
        break;
    }
    case GLFuncId::glTexImage2D: Replay_glTexImage2D(args, len, remap); break;
    case GLFuncId::glTexSubImage2D: Replay_glTexSubImage2D(args, len, remap); break;
    case GLFuncId::glGenerateMipmap: {
        GLenum a_target = cur.Read<GLenum>();
        g_real.glGenerateMipmap(a_target);
        break;
    }
    case GLFuncId::glCreateShader: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint result = g_real.glCreateShader(a_type);
        GLuint captured_result = cur.Read<GLuint>();
        remap.Map("shader", captured_result, result);
        break;
    }
    case GLFuncId::glDeleteShader: {
        GLuint a_shader = cur.Read<GLuint>();
        a_shader = remap.Get("shader", a_shader);
        g_real.glDeleteShader(a_shader);
        break;
    }
    case GLFuncId::glShaderSource: Replay_glShaderSource(args, len, remap); break;
    case GLFuncId::glCompileShader: {
        GLuint a_shader = cur.Read<GLuint>();
        a_shader = remap.Get("shader", a_shader);
        g_real.glCompileShader(a_shader);
        break;
    }
    case GLFuncId::glCreateProgram: {
        GLuint result = g_real.glCreateProgram();
        GLuint captured_result = cur.Read<GLuint>();
        remap.Map("program", captured_result, result);
        break;
    }
    case GLFuncId::glDeleteProgram: {
        GLuint a_program = cur.Read<GLuint>();
        a_program = remap.Get("program", a_program);
        g_real.glDeleteProgram(a_program);
        break;
    }
    case GLFuncId::glAttachShader: {
        GLuint a_program = cur.Read<GLuint>();
        a_program = remap.Get("program", a_program);
        GLuint a_shader = cur.Read<GLuint>();
        a_shader = remap.Get("shader", a_shader);
        g_real.glAttachShader(a_program, a_shader);
        break;
    }
    case GLFuncId::glDetachShader: {
        GLuint a_program = cur.Read<GLuint>();
        a_program = remap.Get("program", a_program);
        GLuint a_shader = cur.Read<GLuint>();
        a_shader = remap.Get("shader", a_shader);
        g_real.glDetachShader(a_program, a_shader);
        break;
    }
    case GLFuncId::glLinkProgram: {
        GLuint a_program = cur.Read<GLuint>();
        a_program = remap.Get("program", a_program);
        g_real.glLinkProgram(a_program);
        break;
    }
    case GLFuncId::glUseProgram: {
        GLuint a_program = cur.Read<GLuint>();
        a_program = remap.Get("program", a_program);
        g_real.glUseProgram(a_program);
        break;
    }
    case GLFuncId::glBindAttribLocation: Replay_glBindAttribLocation(args, len, remap); break;
    case GLFuncId::glGetUniformLocation: Replay_glGetUniformLocation(args, len, remap); break;
    case GLFuncId::glGetAttribLocation: Replay_glGetAttribLocation(args, len, remap); break;
    case GLFuncId::glUniform1i: {
        GLint a_loc = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        g_real.glUniform1i(a_loc, a_v0);
        break;
    }
    case GLFuncId::glUniform1f: {
        GLint a_loc = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        g_real.glUniform1f(a_loc, a_v0);
        break;
    }
    case GLFuncId::glUniform2f: {
        GLint a_loc = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        g_real.glUniform2f(a_loc, a_v0, a_v1);
        break;
    }
    case GLFuncId::glUniform3f: {
        GLint a_loc = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        g_real.glUniform3f(a_loc, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glUniform4f: {
        GLint a_loc = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        GLfloat a_v3 = cur.Read<GLfloat>();
        g_real.glUniform4f(a_loc, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glUniformMatrix4fv: Replay_glUniformMatrix4fv(args, len, remap); break;
    case GLFuncId::glUniformMatrix3fv: Replay_glUniformMatrix3fv(args, len, remap); break;
    case GLFuncId::glGenFramebuffers: Replay_glGenFramebuffers(args, len, remap); break;
    case GLFuncId::glDeleteFramebuffers: Replay_glDeleteFramebuffers(args, len, remap); break;
    case GLFuncId::glBindFramebuffer: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_fb = cur.Read<GLuint>();
        if (a_fb != 0 && !remap.Has("framebuffer", a_fb) && g_real.glGenFramebuffers) {
            GLuint realFramebuffer = 0;
            g_real.glGenFramebuffers(1, &realFramebuffer);
            remap.Map("framebuffer", a_fb, realFramebuffer);
        }
        a_fb = remap.Get("framebuffer", a_fb);
        g_real.glBindFramebuffer(a_target, a_fb);
        break;
    }
    case GLFuncId::glFramebufferTexture2D: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLenum a_textarget = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        a_texture = remap.Get("texture", a_texture);
        GLint a_level = cur.Read<GLint>();
        g_real.glFramebufferTexture2D(a_target, a_attachment, a_textarget, a_texture, a_level);
        break;
    }
    case GLFuncId::glGenRenderbuffers: Replay_glGenRenderbuffers(args, len, remap); break;
    case GLFuncId::glDeleteRenderbuffers: Replay_glDeleteRenderbuffers(args, len, remap); break;
    case GLFuncId::glBindRenderbuffer: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_rb = cur.Read<GLuint>();
        a_rb = remap.Get("renderbuffer", a_rb);
        g_real.glBindRenderbuffer(a_target, a_rb);
        break;
    }
    case GLFuncId::glRenderbufferStorage: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_w = cur.Read<GLsizei>();
        GLsizei a_h = cur.Read<GLsizei>();
        g_real.glRenderbufferStorage(a_target, a_internalformat, a_w, a_h);
        break;
    }
    case GLFuncId::glFramebufferRenderbuffer: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLenum a_rbtarget = cur.Read<GLenum>();
        GLuint a_rb = cur.Read<GLuint>();
        a_rb = remap.Get("renderbuffer", a_rb);
        g_real.glFramebufferRenderbuffer(a_target, a_attachment, a_rbtarget, a_rb);
        break;
    }
    case GLFuncId::glCheckFramebufferStatus: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum result = g_real.glCheckFramebufferStatus(a_target);
        break;
    }
    case GLFuncId::glDrawArrays: Replay_glDrawArrays(args, len, remap); break;
    case GLFuncId::glDrawElements: Replay_glDrawElements(args, len, remap); break;
    case GLFuncId::glDrawArraysInstanced: Replay_glDrawArraysInstanced(args, len, remap); break;
    case GLFuncId::glDrawElementsInstanced: Replay_glDrawElementsInstanced(args, len, remap); break;
    case GLFuncId::glGetString: Replay_glGetString(args, len, remap); break;
    case GLFuncId::glAccum: {
        GLenum a_op = cur.Read<GLenum>();
        GLfloat a_value = cur.Read<GLfloat>();
        g_real.glAccum(a_op, a_value);
        break;
    }
    case GLFuncId::glAlphaFunc: {
        GLenum a_func = cur.Read<GLenum>();
        GLfloat a_ref = cur.Read<GLfloat>();
        g_real.glAlphaFunc(a_func, a_ref);
        break;
    }
    case GLFuncId::glAreTexturesResident: {
        GLsizei a_n = cur.Read<GLsizei>();
        uint8_t a_textures_present = cur.Read<uint8_t>();
        (void)a_textures_present;
        const GLuint * a_textures = nullptr;
        uint8_t a_residences_present = cur.Read<uint8_t>();
        (void)a_residences_present;
        GLboolean * a_residences = nullptr;
        GLboolean result{};
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glArrayElement: {
        GLint a_i = cur.Read<GLint>();
        g_real.glArrayElement(a_i);
        break;
    }
    case GLFuncId::glBitmap: {
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLfloat a_xorig = cur.Read<GLfloat>();
        GLfloat a_yorig = cur.Read<GLfloat>();
        GLfloat a_xmove = cur.Read<GLfloat>();
        GLfloat a_ymove = cur.Read<GLfloat>();
        uint8_t a_bitmap_present = cur.Read<uint8_t>();
        (void)a_bitmap_present;
        const GLubyte * a_bitmap = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glCallList: {
        GLuint a_list = cur.Read<GLuint>();
        g_real.glCallList(a_list);
        break;
    }
    case GLFuncId::glCallLists: {
        GLsizei a_n = cur.Read<GLsizei>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_lists_present = cur.Read<uint8_t>();
        (void)a_lists_present;
        const void * a_lists = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glClearAccum: {
        GLfloat a_red = cur.Read<GLfloat>();
        GLfloat a_green = cur.Read<GLfloat>();
        GLfloat a_blue = cur.Read<GLfloat>();
        GLfloat a_alpha = cur.Read<GLfloat>();
        g_real.glClearAccum(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glClearIndex: {
        GLfloat a_c = cur.Read<GLfloat>();
        g_real.glClearIndex(a_c);
        break;
    }
    case GLFuncId::glClearStencil: {
        GLint a_s = cur.Read<GLint>();
        g_real.glClearStencil(a_s);
        break;
    }
    case GLFuncId::glClipPlane: {
        GLenum a_plane = cur.Read<GLenum>();
        uint8_t a_equation_present = cur.Read<uint8_t>();
        (void)a_equation_present;
        const GLdouble * a_equation = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3b: {
        GLbyte a_red = cur.Read<GLbyte>();
        GLbyte a_green = cur.Read<GLbyte>();
        GLbyte a_blue = cur.Read<GLbyte>();
        g_real.glColor3b(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3bv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLbyte * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3d: {
        GLdouble a_red = cur.Read<GLdouble>();
        GLdouble a_green = cur.Read<GLdouble>();
        GLdouble a_blue = cur.Read<GLdouble>();
        g_real.glColor3d(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3i: {
        GLint a_red = cur.Read<GLint>();
        GLint a_green = cur.Read<GLint>();
        GLint a_blue = cur.Read<GLint>();
        g_real.glColor3i(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3s: {
        GLshort a_red = cur.Read<GLshort>();
        GLshort a_green = cur.Read<GLshort>();
        GLshort a_blue = cur.Read<GLshort>();
        g_real.glColor3s(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3ub: {
        GLubyte a_red = cur.Read<GLubyte>();
        GLubyte a_green = cur.Read<GLubyte>();
        GLubyte a_blue = cur.Read<GLubyte>();
        g_real.glColor3ub(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3ubv: Replay_glColor3ubv(args, len, remap); break;
    case GLFuncId::glColor3ui: {
        GLuint a_red = cur.Read<GLuint>();
        GLuint a_green = cur.Read<GLuint>();
        GLuint a_blue = cur.Read<GLuint>();
        g_real.glColor3ui(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3uiv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLuint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor3us: {
        GLushort a_red = cur.Read<GLushort>();
        GLushort a_green = cur.Read<GLushort>();
        GLushort a_blue = cur.Read<GLushort>();
        g_real.glColor3us(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glColor3usv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLushort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4b: {
        GLbyte a_red = cur.Read<GLbyte>();
        GLbyte a_green = cur.Read<GLbyte>();
        GLbyte a_blue = cur.Read<GLbyte>();
        GLbyte a_alpha = cur.Read<GLbyte>();
        g_real.glColor4b(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4bv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLbyte * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4d: {
        GLdouble a_red = cur.Read<GLdouble>();
        GLdouble a_green = cur.Read<GLdouble>();
        GLdouble a_blue = cur.Read<GLdouble>();
        GLdouble a_alpha = cur.Read<GLdouble>();
        g_real.glColor4d(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4dv: Replay_glColor4dv(args, len, remap); break;
    case GLFuncId::glColor4fv: Replay_glColor4fv(args, len, remap); break;
    case GLFuncId::glColor4i: {
        GLint a_red = cur.Read<GLint>();
        GLint a_green = cur.Read<GLint>();
        GLint a_blue = cur.Read<GLint>();
        GLint a_alpha = cur.Read<GLint>();
        g_real.glColor4i(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4s: {
        GLshort a_red = cur.Read<GLshort>();
        GLshort a_green = cur.Read<GLshort>();
        GLshort a_blue = cur.Read<GLshort>();
        GLshort a_alpha = cur.Read<GLshort>();
        g_real.glColor4s(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4ub: {
        GLubyte a_red = cur.Read<GLubyte>();
        GLubyte a_green = cur.Read<GLubyte>();
        GLubyte a_blue = cur.Read<GLubyte>();
        GLubyte a_alpha = cur.Read<GLubyte>();
        g_real.glColor4ub(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4ubv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLubyte * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4ui: {
        GLuint a_red = cur.Read<GLuint>();
        GLuint a_green = cur.Read<GLuint>();
        GLuint a_blue = cur.Read<GLuint>();
        GLuint a_alpha = cur.Read<GLuint>();
        g_real.glColor4ui(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4uiv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLuint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glColor4us: {
        GLushort a_red = cur.Read<GLushort>();
        GLushort a_green = cur.Read<GLushort>();
        GLushort a_blue = cur.Read<GLushort>();
        GLushort a_alpha = cur.Read<GLushort>();
        g_real.glColor4us(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColor4usv: Replay_glColor4usv(args, len, remap); break;
    case GLFuncId::glColorMask: {
        GLboolean a_red = cur.Read<GLboolean>();
        GLboolean a_green = cur.Read<GLboolean>();
        GLboolean a_blue = cur.Read<GLboolean>();
        GLboolean a_alpha = cur.Read<GLboolean>();
        g_real.glColorMask(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glColorMaterial: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glColorMaterial(a_face, a_mode);
        break;
    }
    case GLFuncId::glCopyPixels: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLenum a_type = cur.Read<GLenum>();
        g_real.glCopyPixels(a_x, a_y, a_width, a_height, a_type);
        break;
    }
    case GLFuncId::glCopyTexImage1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLint a_border = cur.Read<GLint>();
        g_real.glCopyTexImage1D(a_target, a_level, a_internalformat, a_x, a_y, a_width, a_border);
        break;
    }
    case GLFuncId::glCopyTexImage2D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLint a_border = cur.Read<GLint>();
        g_real.glCopyTexImage2D(a_target, a_level, a_internalformat, a_x, a_y, a_width, a_height, a_border);
        break;
    }
    case GLFuncId::glCopyTexSubImage1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        g_real.glCopyTexSubImage1D(a_target, a_level, a_xoffset, a_x, a_y, a_width);
        break;
    }
    case GLFuncId::glCopyTexSubImage2D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_yoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glCopyTexSubImage2D(a_target, a_level, a_xoffset, a_yoffset, a_x, a_y, a_width, a_height);
        break;
    }
    case GLFuncId::glDeleteLists: {
        GLuint a_list = cur.Read<GLuint>();
        GLsizei a_range = cur.Read<GLsizei>();
        g_real.glDeleteLists(a_list, a_range);
        break;
    }
    case GLFuncId::glDepthRange: {
        GLdouble a_n = cur.Read<GLdouble>();
        GLdouble a_f = cur.Read<GLdouble>();
        g_real.glDepthRange(a_n, a_f);
        break;
    }
    case GLFuncId::glDrawBuffer: {
        GLenum a_buf = cur.Read<GLenum>();
        g_real.glDrawBuffer(a_buf);
        break;
    }
    case GLFuncId::glDrawPixels: {
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLenum a_format = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        (void)a_pixels_present;
        const void * a_pixels = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEdgeFlag: {
        GLboolean a_flag = cur.Read<GLboolean>();
        g_real.glEdgeFlag(a_flag);
        break;
    }
    case GLFuncId::glEdgeFlagPointer: {
        GLsizei a_stride = cur.Read<GLsizei>();
        uint8_t a_pointer_present = cur.Read<uint8_t>();
        (void)a_pointer_present;
        const void * a_pointer = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEdgeFlagv: {
        uint8_t a_flag_present = cur.Read<uint8_t>();
        (void)a_flag_present;
        const GLboolean * a_flag = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEndList: {
        g_real.glEndList();
        break;
    }
    case GLFuncId::glEvalCoord1d: {
        GLdouble a_u = cur.Read<GLdouble>();
        g_real.glEvalCoord1d(a_u);
        break;
    }
    case GLFuncId::glEvalCoord1dv: {
        uint8_t a_u_present = cur.Read<uint8_t>();
        (void)a_u_present;
        const GLdouble * a_u = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEvalCoord1f: {
        GLfloat a_u = cur.Read<GLfloat>();
        g_real.glEvalCoord1f(a_u);
        break;
    }
    case GLFuncId::glEvalCoord1fv: {
        uint8_t a_u_present = cur.Read<uint8_t>();
        (void)a_u_present;
        const GLfloat * a_u = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEvalCoord2d: {
        GLdouble a_u = cur.Read<GLdouble>();
        GLdouble a_v = cur.Read<GLdouble>();
        g_real.glEvalCoord2d(a_u, a_v);
        break;
    }
    case GLFuncId::glEvalCoord2dv: {
        uint8_t a_u_present = cur.Read<uint8_t>();
        (void)a_u_present;
        const GLdouble * a_u = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEvalCoord2f: {
        GLfloat a_u = cur.Read<GLfloat>();
        GLfloat a_v = cur.Read<GLfloat>();
        g_real.glEvalCoord2f(a_u, a_v);
        break;
    }
    case GLFuncId::glEvalCoord2fv: {
        uint8_t a_u_present = cur.Read<uint8_t>();
        (void)a_u_present;
        const GLfloat * a_u = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glEvalMesh1: {
        GLenum a_mode = cur.Read<GLenum>();
        GLint a_i1 = cur.Read<GLint>();
        GLint a_i2 = cur.Read<GLint>();
        g_real.glEvalMesh1(a_mode, a_i1, a_i2);
        break;
    }
    case GLFuncId::glEvalMesh2: {
        GLenum a_mode = cur.Read<GLenum>();
        GLint a_i1 = cur.Read<GLint>();
        GLint a_i2 = cur.Read<GLint>();
        GLint a_j1 = cur.Read<GLint>();
        GLint a_j2 = cur.Read<GLint>();
        g_real.glEvalMesh2(a_mode, a_i1, a_i2, a_j1, a_j2);
        break;
    }
    case GLFuncId::glEvalPoint1: {
        GLint a_i = cur.Read<GLint>();
        g_real.glEvalPoint1(a_i);
        break;
    }
    case GLFuncId::glEvalPoint2: {
        GLint a_i = cur.Read<GLint>();
        GLint a_j = cur.Read<GLint>();
        g_real.glEvalPoint2(a_i, a_j);
        break;
    }
    case GLFuncId::glFeedbackBuffer: {
        GLsizei a_size = cur.Read<GLsizei>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_buffer_present = cur.Read<uint8_t>();
        (void)a_buffer_present;
        GLfloat * a_buffer = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glFinish: {
        g_real.glFinish();
        break;
    }
    case GLFuncId::glFlush: {
        g_real.glFlush();
        break;
    }
    case GLFuncId::glFogf: {
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glFogf(a_pname, a_param);
        break;
    }
    case GLFuncId::glFogfv: {
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glFogi: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glFogi(a_pname, a_param);
        break;
    }
    case GLFuncId::glFogiv: {
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGenLists: {
        GLsizei a_range = cur.Read<GLsizei>();
        GLuint result = g_real.glGenLists(a_range);
        break;
    }
    case GLFuncId::glGetBooleanv: Replay_glGetBooleanv(args, len, remap); break;
    case GLFuncId::glGetClipPlane: {
        GLenum a_plane = cur.Read<GLenum>();
        uint8_t a_equation_present = cur.Read<uint8_t>();
        (void)a_equation_present;
        GLdouble * a_equation = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetDoublev: {
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_data_present = cur.Read<uint8_t>();
        (void)a_data_present;
        GLdouble * a_data = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetError: {
        GLenum result = g_real.glGetError();
        break;
    }
    case GLFuncId::glGetFloatv: Replay_glGetFloatv(args, len, remap); break;
    case GLFuncId::glGetIntegerv: Replay_glGetIntegerv(args, len, remap); break;
    case GLFuncId::glGetLightfv: {
        GLenum a_light = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetLightiv: {
        GLenum a_light = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetMapdv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_query = cur.Read<GLenum>();
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetMapfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_query = cur.Read<GLenum>();
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetMapiv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_query = cur.Read<GLenum>();
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetMaterialfv: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetMaterialiv: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetPixelMapfv: {
        GLenum a_map = cur.Read<GLenum>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        GLfloat * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetPixelMapuiv: {
        GLenum a_map = cur.Read<GLenum>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        GLuint * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetPixelMapusv: {
        GLenum a_map = cur.Read<GLenum>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        GLushort * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetPointerv: {
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        void ** a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetPolygonStipple: {
        uint8_t a_mask_present = cur.Read<uint8_t>();
        (void)a_mask_present;
        GLubyte * a_mask = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexEnvfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexEnviv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexGendv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLdouble * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexGenfv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexGeniv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexImage: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLenum a_format = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        (void)a_pixels_present;
        void * a_pixels = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexLevelParameterfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexLevelParameteriv: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexParameterfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetTexParameteriv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glHint: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glHint(a_target, a_mode);
        break;
    }
    case GLFuncId::glIndexMask: {
        GLuint a_mask = cur.Read<GLuint>();
        g_real.glIndexMask(a_mask);
        break;
    }
    case GLFuncId::glIndexPointer: {
        GLenum a_type = cur.Read<GLenum>();
        GLsizei a_stride = cur.Read<GLsizei>();
        uint8_t a_pointer_present = cur.Read<uint8_t>();
        (void)a_pointer_present;
        const void * a_pointer = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glIndexd: {
        GLdouble a_c = cur.Read<GLdouble>();
        g_real.glIndexd(a_c);
        break;
    }
    case GLFuncId::glIndexdv: {
        uint8_t a_c_present = cur.Read<uint8_t>();
        (void)a_c_present;
        const GLdouble * a_c = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glIndexf: {
        GLfloat a_c = cur.Read<GLfloat>();
        g_real.glIndexf(a_c);
        break;
    }
    case GLFuncId::glIndexfv: {
        uint8_t a_c_present = cur.Read<uint8_t>();
        (void)a_c_present;
        const GLfloat * a_c = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glIndexi: {
        GLint a_c = cur.Read<GLint>();
        g_real.glIndexi(a_c);
        break;
    }
    case GLFuncId::glIndexiv: {
        uint8_t a_c_present = cur.Read<uint8_t>();
        (void)a_c_present;
        const GLint * a_c = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glIndexs: {
        GLshort a_c = cur.Read<GLshort>();
        g_real.glIndexs(a_c);
        break;
    }
    case GLFuncId::glIndexsv: {
        uint8_t a_c_present = cur.Read<uint8_t>();
        (void)a_c_present;
        const GLshort * a_c = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glIndexub: {
        GLubyte a_c = cur.Read<GLubyte>();
        g_real.glIndexub(a_c);
        break;
    }
    case GLFuncId::glIndexubv: {
        uint8_t a_c_present = cur.Read<uint8_t>();
        (void)a_c_present;
        const GLubyte * a_c = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glInitNames: {
        g_real.glInitNames();
        break;
    }
    case GLFuncId::glInterleavedArrays: Replay_glInterleavedArrays(args, len, remap); break;
    case GLFuncId::glIsEnabled: {
        GLenum a_cap = cur.Read<GLenum>();
        GLboolean result = g_real.glIsEnabled(a_cap);
        break;
    }
    case GLFuncId::glIsList: {
        GLuint a_list = cur.Read<GLuint>();
        GLboolean result = g_real.glIsList(a_list);
        break;
    }
    case GLFuncId::glIsTexture: {
        GLuint a_texture = cur.Read<GLuint>();
        GLboolean result = g_real.glIsTexture(a_texture);
        break;
    }
    case GLFuncId::glLightModelf: {
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glLightModelf(a_pname, a_param);
        break;
    }
    case GLFuncId::glLightModelfv: Replay_glLightModelfv(args, len, remap); break;
    case GLFuncId::glLightModeli: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glLightModeli(a_pname, a_param);
        break;
    }
    case GLFuncId::glLightModeliv: {
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glLightf: {
        GLenum a_light = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glLightf(a_light, a_pname, a_param);
        break;
    }
    case GLFuncId::glLightfv: Replay_glLightfv(args, len, remap); break;
    case GLFuncId::glLighti: {
        GLenum a_light = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glLighti(a_light, a_pname, a_param);
        break;
    }
    case GLFuncId::glLightiv: {
        GLenum a_light = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glLineStipple: {
        GLint a_factor = cur.Read<GLint>();
        GLushort a_pattern = cur.Read<GLushort>();
        g_real.glLineStipple(a_factor, a_pattern);
        break;
    }
    case GLFuncId::glListBase: {
        GLuint a_base = cur.Read<GLuint>();
        g_real.glListBase(a_base);
        break;
    }
    case GLFuncId::glLoadMatrixd: Replay_glLoadMatrixd(args, len, remap); break;
    case GLFuncId::glLoadMatrixf: Replay_glLoadMatrixf(args, len, remap); break;
    case GLFuncId::glLoadName: {
        GLuint a_name = cur.Read<GLuint>();
        g_real.glLoadName(a_name);
        break;
    }
    case GLFuncId::glLogicOp: {
        GLenum a_opcode = cur.Read<GLenum>();
        g_real.glLogicOp(a_opcode);
        break;
    }
    case GLFuncId::glMap1d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_u1 = cur.Read<GLdouble>();
        GLdouble a_u2 = cur.Read<GLdouble>();
        GLint a_stride = cur.Read<GLint>();
        GLint a_order = cur.Read<GLint>();
        uint8_t a_points_present = cur.Read<uint8_t>();
        (void)a_points_present;
        const GLdouble * a_points = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMap1f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_u1 = cur.Read<GLfloat>();
        GLfloat a_u2 = cur.Read<GLfloat>();
        GLint a_stride = cur.Read<GLint>();
        GLint a_order = cur.Read<GLint>();
        uint8_t a_points_present = cur.Read<uint8_t>();
        (void)a_points_present;
        const GLfloat * a_points = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMap2d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_u1 = cur.Read<GLdouble>();
        GLdouble a_u2 = cur.Read<GLdouble>();
        GLint a_ustride = cur.Read<GLint>();
        GLint a_uorder = cur.Read<GLint>();
        GLdouble a_v1 = cur.Read<GLdouble>();
        GLdouble a_v2 = cur.Read<GLdouble>();
        GLint a_vstride = cur.Read<GLint>();
        GLint a_vorder = cur.Read<GLint>();
        uint8_t a_points_present = cur.Read<uint8_t>();
        (void)a_points_present;
        const GLdouble * a_points = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMap2f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_u1 = cur.Read<GLfloat>();
        GLfloat a_u2 = cur.Read<GLfloat>();
        GLint a_ustride = cur.Read<GLint>();
        GLint a_uorder = cur.Read<GLint>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        GLint a_vstride = cur.Read<GLint>();
        GLint a_vorder = cur.Read<GLint>();
        uint8_t a_points_present = cur.Read<uint8_t>();
        (void)a_points_present;
        const GLfloat * a_points = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMapGrid1d: {
        GLint a_un = cur.Read<GLint>();
        GLdouble a_u1 = cur.Read<GLdouble>();
        GLdouble a_u2 = cur.Read<GLdouble>();
        g_real.glMapGrid1d(a_un, a_u1, a_u2);
        break;
    }
    case GLFuncId::glMapGrid1f: {
        GLint a_un = cur.Read<GLint>();
        GLfloat a_u1 = cur.Read<GLfloat>();
        GLfloat a_u2 = cur.Read<GLfloat>();
        g_real.glMapGrid1f(a_un, a_u1, a_u2);
        break;
    }
    case GLFuncId::glMapGrid2d: {
        GLint a_un = cur.Read<GLint>();
        GLdouble a_u1 = cur.Read<GLdouble>();
        GLdouble a_u2 = cur.Read<GLdouble>();
        GLint a_vn = cur.Read<GLint>();
        GLdouble a_v1 = cur.Read<GLdouble>();
        GLdouble a_v2 = cur.Read<GLdouble>();
        g_real.glMapGrid2d(a_un, a_u1, a_u2, a_vn, a_v1, a_v2);
        break;
    }
    case GLFuncId::glMapGrid2f: {
        GLint a_un = cur.Read<GLint>();
        GLfloat a_u1 = cur.Read<GLfloat>();
        GLfloat a_u2 = cur.Read<GLfloat>();
        GLint a_vn = cur.Read<GLint>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        g_real.glMapGrid2f(a_un, a_u1, a_u2, a_vn, a_v1, a_v2);
        break;
    }
    case GLFuncId::glMaterialf: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glMaterialf(a_face, a_pname, a_param);
        break;
    }
    case GLFuncId::glMaterialfv: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMateriali: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glMateriali(a_face, a_pname, a_param);
        break;
    }
    case GLFuncId::glMaterialiv: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMultMatrixd: {
        uint8_t a_m_present = cur.Read<uint8_t>();
        (void)a_m_present;
        const GLdouble * a_m = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glMultMatrixf: {
        uint8_t a_m_present = cur.Read<uint8_t>();
        (void)a_m_present;
        const GLfloat * a_m = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glNewList: {
        GLuint a_list = cur.Read<GLuint>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glNewList(a_list, a_mode);
        break;
    }
    case GLFuncId::glNormal3b: {
        GLbyte a_nx = cur.Read<GLbyte>();
        GLbyte a_ny = cur.Read<GLbyte>();
        GLbyte a_nz = cur.Read<GLbyte>();
        g_real.glNormal3b(a_nx, a_ny, a_nz);
        break;
    }
    case GLFuncId::glNormal3bv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLbyte * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glNormal3d: {
        GLdouble a_nx = cur.Read<GLdouble>();
        GLdouble a_ny = cur.Read<GLdouble>();
        GLdouble a_nz = cur.Read<GLdouble>();
        g_real.glNormal3d(a_nx, a_ny, a_nz);
        break;
    }
    case GLFuncId::glNormal3dv: Replay_glNormal3dv(args, len, remap); break;
    case GLFuncId::glNormal3fv: Replay_glNormal3fv(args, len, remap); break;
    case GLFuncId::glNormal3i: {
        GLint a_nx = cur.Read<GLint>();
        GLint a_ny = cur.Read<GLint>();
        GLint a_nz = cur.Read<GLint>();
        g_real.glNormal3i(a_nx, a_ny, a_nz);
        break;
    }
    case GLFuncId::glNormal3iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glNormal3s: {
        GLshort a_nx = cur.Read<GLshort>();
        GLshort a_ny = cur.Read<GLshort>();
        GLshort a_nz = cur.Read<GLshort>();
        g_real.glNormal3s(a_nx, a_ny, a_nz);
        break;
    }
    case GLFuncId::glNormal3sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPassThrough: {
        GLfloat a_token = cur.Read<GLfloat>();
        g_real.glPassThrough(a_token);
        break;
    }
    case GLFuncId::glPixelMapfv: {
        GLenum a_map = cur.Read<GLenum>();
        GLsizei a_mapsize = cur.Read<GLsizei>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        const GLfloat * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPixelMapuiv: {
        GLenum a_map = cur.Read<GLenum>();
        GLsizei a_mapsize = cur.Read<GLsizei>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        const GLuint * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPixelMapusv: {
        GLenum a_map = cur.Read<GLenum>();
        GLsizei a_mapsize = cur.Read<GLsizei>();
        uint8_t a_values_present = cur.Read<uint8_t>();
        (void)a_values_present;
        const GLushort * a_values = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPixelStoref: {
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glPixelStoref(a_pname, a_param);
        break;
    }
    case GLFuncId::glPixelTransferf: {
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glPixelTransferf(a_pname, a_param);
        break;
    }
    case GLFuncId::glPixelTransferi: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glPixelTransferi(a_pname, a_param);
        break;
    }
    case GLFuncId::glPixelZoom: {
        GLfloat a_xfactor = cur.Read<GLfloat>();
        GLfloat a_yfactor = cur.Read<GLfloat>();
        g_real.glPixelZoom(a_xfactor, a_yfactor);
        break;
    }
    case GLFuncId::glPolygonOffset: {
        GLfloat a_factor = cur.Read<GLfloat>();
        GLfloat a_units = cur.Read<GLfloat>();
        g_real.glPolygonOffset(a_factor, a_units);
        break;
    }
    case GLFuncId::glPolygonStipple: {
        uint8_t a_mask_present = cur.Read<uint8_t>();
        (void)a_mask_present;
        const GLubyte * a_mask = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPopAttrib: {
        g_real.glPopAttrib();
        break;
    }
    case GLFuncId::glPopClientAttrib: {
        g_real.glPopClientAttrib();
        break;
    }
    case GLFuncId::glPopName: {
        g_real.glPopName();
        break;
    }
    case GLFuncId::glPrioritizeTextures: {
        GLsizei a_n = cur.Read<GLsizei>();
        uint8_t a_textures_present = cur.Read<uint8_t>();
        (void)a_textures_present;
        const GLuint * a_textures = nullptr;
        uint8_t a_priorities_present = cur.Read<uint8_t>();
        (void)a_priorities_present;
        const GLfloat * a_priorities = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glPushAttrib: {
        GLbitfield a_mask = cur.Read<GLbitfield>();
        g_real.glPushAttrib(a_mask);
        break;
    }
    case GLFuncId::glPushClientAttrib: {
        GLbitfield a_mask = cur.Read<GLbitfield>();
        g_real.glPushClientAttrib(a_mask);
        break;
    }
    case GLFuncId::glPushName: {
        GLuint a_name = cur.Read<GLuint>();
        g_real.glPushName(a_name);
        break;
    }
    case GLFuncId::glRasterPos2d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glRasterPos2d(a_x, a_y);
        break;
    }
    case GLFuncId::glRasterPos2dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos2f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        g_real.glRasterPos2f(a_x, a_y);
        break;
    }
    case GLFuncId::glRasterPos2fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos2i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        g_real.glRasterPos2i(a_x, a_y);
        break;
    }
    case GLFuncId::glRasterPos2iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos2s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        g_real.glRasterPos2s(a_x, a_y);
        break;
    }
    case GLFuncId::glRasterPos2sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos3d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glRasterPos3d(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glRasterPos3dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos3f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glRasterPos3f(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glRasterPos3fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos3i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        g_real.glRasterPos3i(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glRasterPos3iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos3s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        g_real.glRasterPos3s(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glRasterPos3sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos4d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        GLdouble a_w = cur.Read<GLdouble>();
        g_real.glRasterPos4d(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glRasterPos4dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos4f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        GLfloat a_w = cur.Read<GLfloat>();
        g_real.glRasterPos4f(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glRasterPos4fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos4i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        GLint a_w = cur.Read<GLint>();
        g_real.glRasterPos4i(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glRasterPos4iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRasterPos4s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        GLshort a_w = cur.Read<GLshort>();
        g_real.glRasterPos4s(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glRasterPos4sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glReadBuffer: {
        GLenum a_src = cur.Read<GLenum>();
        g_real.glReadBuffer(a_src);
        break;
    }
    case GLFuncId::glReadPixels: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLenum a_format = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        (void)a_pixels_present;
        void * a_pixels = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRectd: {
        GLdouble a_x1 = cur.Read<GLdouble>();
        GLdouble a_y1 = cur.Read<GLdouble>();
        GLdouble a_x2 = cur.Read<GLdouble>();
        GLdouble a_y2 = cur.Read<GLdouble>();
        g_real.glRectd(a_x1, a_y1, a_x2, a_y2);
        break;
    }
    case GLFuncId::glRectdv: {
        uint8_t a_v1_present = cur.Read<uint8_t>();
        (void)a_v1_present;
        const GLdouble * a_v1 = nullptr;
        uint8_t a_v2_present = cur.Read<uint8_t>();
        (void)a_v2_present;
        const GLdouble * a_v2 = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRectf: {
        GLfloat a_x1 = cur.Read<GLfloat>();
        GLfloat a_y1 = cur.Read<GLfloat>();
        GLfloat a_x2 = cur.Read<GLfloat>();
        GLfloat a_y2 = cur.Read<GLfloat>();
        g_real.glRectf(a_x1, a_y1, a_x2, a_y2);
        break;
    }
    case GLFuncId::glRectfv: {
        uint8_t a_v1_present = cur.Read<uint8_t>();
        (void)a_v1_present;
        const GLfloat * a_v1 = nullptr;
        uint8_t a_v2_present = cur.Read<uint8_t>();
        (void)a_v2_present;
        const GLfloat * a_v2 = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRecti: {
        GLint a_x1 = cur.Read<GLint>();
        GLint a_y1 = cur.Read<GLint>();
        GLint a_x2 = cur.Read<GLint>();
        GLint a_y2 = cur.Read<GLint>();
        g_real.glRecti(a_x1, a_y1, a_x2, a_y2);
        break;
    }
    case GLFuncId::glRectiv: {
        uint8_t a_v1_present = cur.Read<uint8_t>();
        (void)a_v1_present;
        const GLint * a_v1 = nullptr;
        uint8_t a_v2_present = cur.Read<uint8_t>();
        (void)a_v2_present;
        const GLint * a_v2 = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRects: {
        GLshort a_x1 = cur.Read<GLshort>();
        GLshort a_y1 = cur.Read<GLshort>();
        GLshort a_x2 = cur.Read<GLshort>();
        GLshort a_y2 = cur.Read<GLshort>();
        g_real.glRects(a_x1, a_y1, a_x2, a_y2);
        break;
    }
    case GLFuncId::glRectsv: {
        uint8_t a_v1_present = cur.Read<uint8_t>();
        (void)a_v1_present;
        const GLshort * a_v1 = nullptr;
        uint8_t a_v2_present = cur.Read<uint8_t>();
        (void)a_v2_present;
        const GLshort * a_v2 = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glRenderMode: {
        GLenum a_mode = cur.Read<GLenum>();
        GLint result = g_real.glRenderMode(a_mode);
        break;
    }
    case GLFuncId::glRotated: {
        GLdouble a_angle = cur.Read<GLdouble>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glRotated(a_angle, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glScaled: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glScaled(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glSelectBuffer: {
        GLsizei a_size = cur.Read<GLsizei>();
        uint8_t a_buffer_present = cur.Read<uint8_t>();
        (void)a_buffer_present;
        GLuint * a_buffer = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glShadeModel: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glShadeModel(a_mode);
        break;
    }
    case GLFuncId::glStencilFunc: {
        GLenum a_func = cur.Read<GLenum>();
        GLint a_ref = cur.Read<GLint>();
        GLuint a_mask = cur.Read<GLuint>();
        g_real.glStencilFunc(a_func, a_ref, a_mask);
        break;
    }
    case GLFuncId::glStencilMask: {
        GLuint a_mask = cur.Read<GLuint>();
        g_real.glStencilMask(a_mask);
        break;
    }
    case GLFuncId::glStencilOp: {
        GLenum a_fail = cur.Read<GLenum>();
        GLenum a_zfail = cur.Read<GLenum>();
        GLenum a_zpass = cur.Read<GLenum>();
        g_real.glStencilOp(a_fail, a_zfail, a_zpass);
        break;
    }
    case GLFuncId::glTexCoord1d: {
        GLdouble a_s = cur.Read<GLdouble>();
        g_real.glTexCoord1d(a_s);
        break;
    }
    case GLFuncId::glTexCoord1dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord1f: {
        GLfloat a_s = cur.Read<GLfloat>();
        g_real.glTexCoord1f(a_s);
        break;
    }
    case GLFuncId::glTexCoord1fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord1i: {
        GLint a_s = cur.Read<GLint>();
        g_real.glTexCoord1i(a_s);
        break;
    }
    case GLFuncId::glTexCoord1iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord1s: {
        GLshort a_s = cur.Read<GLshort>();
        g_real.glTexCoord1s(a_s);
        break;
    }
    case GLFuncId::glTexCoord1sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord2d: {
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        g_real.glTexCoord2d(a_s, a_t);
        break;
    }
    case GLFuncId::glTexCoord2dv: Replay_glTexCoord2dv(args, len, remap); break;
    case GLFuncId::glTexCoord2fv: Replay_glTexCoord2fv(args, len, remap); break;
    case GLFuncId::glTexCoord2i: {
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        g_real.glTexCoord2i(a_s, a_t);
        break;
    }
    case GLFuncId::glTexCoord2iv: Replay_glTexCoord2iv(args, len, remap); break;
    case GLFuncId::glTexCoord2s: {
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        g_real.glTexCoord2s(a_s, a_t);
        break;
    }
    case GLFuncId::glTexCoord2sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord3d: {
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        g_real.glTexCoord3d(a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glTexCoord3dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord3f: {
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        GLfloat a_r = cur.Read<GLfloat>();
        g_real.glTexCoord3f(a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glTexCoord3fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord3i: {
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        GLint a_r = cur.Read<GLint>();
        g_real.glTexCoord3i(a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glTexCoord3iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord3s: {
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        GLshort a_r = cur.Read<GLshort>();
        g_real.glTexCoord3s(a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glTexCoord3sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord4d: {
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        GLdouble a_q = cur.Read<GLdouble>();
        g_real.glTexCoord4d(a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glTexCoord4dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord4f: {
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        GLfloat a_r = cur.Read<GLfloat>();
        GLfloat a_q = cur.Read<GLfloat>();
        g_real.glTexCoord4f(a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glTexCoord4fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord4i: {
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        GLint a_r = cur.Read<GLint>();
        GLint a_q = cur.Read<GLint>();
        g_real.glTexCoord4i(a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glTexCoord4iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexCoord4s: {
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        GLshort a_r = cur.Read<GLshort>();
        GLshort a_q = cur.Read<GLshort>();
        g_real.glTexCoord4s(a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glTexCoord4sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexEnvf: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glTexEnvf(a_target, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexEnvfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexEnvi: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glTexEnvi(a_target, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexEnviv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexGend: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLdouble a_param = cur.Read<GLdouble>();
        g_real.glTexGend(a_coord, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexGendv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLdouble * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexGenf: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glTexGenf(a_coord, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexGenfv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexGeni: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glTexGeni(a_coord, a_pname, a_param);
        break;
    }
    case GLFuncId::glTexGeniv: {
        GLenum a_coord = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexImage1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLint a_internalformat = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLint a_border = cur.Read<GLint>();
        GLenum a_format = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        (void)a_pixels_present;
        const void * a_pixels = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexParameterfv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLfloat * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexParameteriv: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        const GLint * a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTexSubImage1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLenum a_format = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        uint8_t a_pixels_present = cur.Read<uint8_t>();
        (void)a_pixels_present;
        const void * a_pixels = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glTranslated: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glTranslated(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertex2d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glVertex2d(a_x, a_y);
        break;
    }
    case GLFuncId::glVertex2dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex2fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex2i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        g_real.glVertex2i(a_x, a_y);
        break;
    }
    case GLFuncId::glVertex2iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex2s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        g_real.glVertex2s(a_x, a_y);
        break;
    }
    case GLFuncId::glVertex2sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex3d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glVertex3d(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertex3dv: Replay_glVertex3dv(args, len, remap); break;
    case GLFuncId::glVertex3fv: Replay_glVertex3fv(args, len, remap); break;
    case GLFuncId::glVertex3i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        g_real.glVertex3i(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertex3iv: Replay_glVertex3iv(args, len, remap); break;
    case GLFuncId::glVertex3s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        g_real.glVertex3s(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertex3sv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLshort * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex4d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        GLdouble a_w = cur.Read<GLdouble>();
        g_real.glVertex4d(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertex4dv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLdouble * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex4fv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLfloat * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex4i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        GLint a_w = cur.Read<GLint>();
        g_real.glVertex4i(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertex4iv: {
        uint8_t a_v_present = cur.Read<uint8_t>();
        (void)a_v_present;
        const GLint * a_v = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glVertex4s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        GLshort a_w = cur.Read<GLshort>();
        g_real.glVertex4s(a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertex4sv: Replay_glVertex4sv(args, len, remap); break;
    case GLFuncId::glGetShaderiv: {
        GLuint a_shader = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint* a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glGetProgramiv: {
        GLuint a_program = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        uint8_t a_params_present = cur.Read<uint8_t>();
        (void)a_params_present;
        GLint* a_params = nullptr;
        // Pointer payloads are presence-only until a custom decoder is provided.
        break;
    }
    case GLFuncId::glActiveShaderProgram: {
        GLuint a_pipeline = cur.Read<GLuint>();
        GLuint a_program = cur.Read<GLuint>();
        g_real.glActiveShaderProgram(a_pipeline, a_program);
        break;
    }
    case GLFuncId::glBeginConditionalRender: {
        GLuint a_id = cur.Read<GLuint>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glBeginConditionalRender(a_id, a_mode);
        break;
    }
    case GLFuncId::glBeginQuery: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        g_real.glBeginQuery(a_target, a_id);
        break;
    }
    case GLFuncId::glBeginQueryIndexed: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_id = cur.Read<GLuint>();
        g_real.glBeginQueryIndexed(a_target, a_index, a_id);
        break;
    }
    case GLFuncId::glBeginTransformFeedback: {
        GLenum a_primitiveMode = cur.Read<GLenum>();
        g_real.glBeginTransformFeedback(a_primitiveMode);
        break;
    }
    case GLFuncId::glBindBufferBase: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glBindBufferBase(a_target, a_index, a_buffer);
        break;
    }
    case GLFuncId::glBindBufferRange: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glBindBufferRange(a_target, a_index, a_buffer, a_offset, a_size);
        break;
    }
    case GLFuncId::glBindImageTexture: {
        GLuint a_unit = cur.Read<GLuint>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLboolean a_layered = cur.Read<GLboolean>();
        GLint a_layer = cur.Read<GLint>();
        GLenum a_access = cur.Read<GLenum>();
        GLenum a_format = cur.Read<GLenum>();
        g_real.glBindImageTexture(a_unit, a_texture, a_level, a_layered, a_layer, a_access, a_format);
        break;
    }
    case GLFuncId::glBindProgramPipeline: {
        GLuint a_pipeline = cur.Read<GLuint>();
        g_real.glBindProgramPipeline(a_pipeline);
        break;
    }
    case GLFuncId::glBindSampler: {
        GLuint a_unit = cur.Read<GLuint>();
        GLuint a_sampler = cur.Read<GLuint>();
        g_real.glBindSampler(a_unit, a_sampler);
        break;
    }
    case GLFuncId::glBindTextureUnit: {
        GLuint a_unit = cur.Read<GLuint>();
        GLuint a_texture = cur.Read<GLuint>();
        g_real.glBindTextureUnit(a_unit, a_texture);
        break;
    }
    case GLFuncId::glBindTransformFeedback: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        g_real.glBindTransformFeedback(a_target, a_id);
        break;
    }
    case GLFuncId::glBindVertexBuffer: {
        GLuint a_bindingindex = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizei a_stride = cur.Read<GLsizei>();
        g_real.glBindVertexBuffer(a_bindingindex, a_buffer, a_offset, a_stride);
        break;
    }
    case GLFuncId::glBlendColor: {
        GLfloat a_red = cur.Read<GLfloat>();
        GLfloat a_green = cur.Read<GLfloat>();
        GLfloat a_blue = cur.Read<GLfloat>();
        GLfloat a_alpha = cur.Read<GLfloat>();
        g_real.glBlendColor(a_red, a_green, a_blue, a_alpha);
        break;
    }
    case GLFuncId::glBlendEquation: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glBlendEquation(a_mode);
        break;
    }
    case GLFuncId::glBlendEquationSeparate: {
        GLenum a_modeRGB = cur.Read<GLenum>();
        GLenum a_modeAlpha = cur.Read<GLenum>();
        g_real.glBlendEquationSeparate(a_modeRGB, a_modeAlpha);
        break;
    }
    case GLFuncId::glBlendEquationSeparatei: {
        GLuint a_buf = cur.Read<GLuint>();
        GLenum a_modeRGB = cur.Read<GLenum>();
        GLenum a_modeAlpha = cur.Read<GLenum>();
        g_real.glBlendEquationSeparatei(a_buf, a_modeRGB, a_modeAlpha);
        break;
    }
    case GLFuncId::glBlendEquationi: {
        GLuint a_buf = cur.Read<GLuint>();
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glBlendEquationi(a_buf, a_mode);
        break;
    }
    case GLFuncId::glBlendFuncSeparate: {
        GLenum a_sfactorRGB = cur.Read<GLenum>();
        GLenum a_dfactorRGB = cur.Read<GLenum>();
        GLenum a_sfactorAlpha = cur.Read<GLenum>();
        GLenum a_dfactorAlpha = cur.Read<GLenum>();
        g_real.glBlendFuncSeparate(a_sfactorRGB, a_dfactorRGB, a_sfactorAlpha, a_dfactorAlpha);
        break;
    }
    case GLFuncId::glBlendFuncSeparatei: {
        GLuint a_buf = cur.Read<GLuint>();
        GLenum a_srcRGB = cur.Read<GLenum>();
        GLenum a_dstRGB = cur.Read<GLenum>();
        GLenum a_srcAlpha = cur.Read<GLenum>();
        GLenum a_dstAlpha = cur.Read<GLenum>();
        g_real.glBlendFuncSeparatei(a_buf, a_srcRGB, a_dstRGB, a_srcAlpha, a_dstAlpha);
        break;
    }
    case GLFuncId::glBlendFunci: {
        GLuint a_buf = cur.Read<GLuint>();
        GLenum a_src = cur.Read<GLenum>();
        GLenum a_dst = cur.Read<GLenum>();
        g_real.glBlendFunci(a_buf, a_src, a_dst);
        break;
    }
    case GLFuncId::glBlitFramebuffer: {
        GLint a_srcX0 = cur.Read<GLint>();
        GLint a_srcY0 = cur.Read<GLint>();
        GLint a_srcX1 = cur.Read<GLint>();
        GLint a_srcY1 = cur.Read<GLint>();
        GLint a_dstX0 = cur.Read<GLint>();
        GLint a_dstY0 = cur.Read<GLint>();
        GLint a_dstX1 = cur.Read<GLint>();
        GLint a_dstY1 = cur.Read<GLint>();
        GLbitfield a_mask = cur.Read<GLbitfield>();
        GLenum a_filter = cur.Read<GLenum>();
        g_real.glBlitFramebuffer(a_srcX0, a_srcY0, a_srcX1, a_srcY1, a_dstX0, a_dstY0, a_dstX1, a_dstY1, a_mask, a_filter);
        break;
    }
    case GLFuncId::glBlitNamedFramebuffer: {
        GLuint a_readFramebuffer = cur.Read<GLuint>();
        GLuint a_drawFramebuffer = cur.Read<GLuint>();
        GLint a_srcX0 = cur.Read<GLint>();
        GLint a_srcY0 = cur.Read<GLint>();
        GLint a_srcX1 = cur.Read<GLint>();
        GLint a_srcY1 = cur.Read<GLint>();
        GLint a_dstX0 = cur.Read<GLint>();
        GLint a_dstY0 = cur.Read<GLint>();
        GLint a_dstX1 = cur.Read<GLint>();
        GLint a_dstY1 = cur.Read<GLint>();
        GLbitfield a_mask = cur.Read<GLbitfield>();
        GLenum a_filter = cur.Read<GLenum>();
        g_real.glBlitNamedFramebuffer(a_readFramebuffer, a_drawFramebuffer, a_srcX0, a_srcY0, a_srcX1, a_srcY1, a_dstX0, a_dstY0, a_dstX1, a_dstY1, a_mask, a_filter);
        break;
    }
    case GLFuncId::glClampColor: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_clamp = cur.Read<GLenum>();
        g_real.glClampColor(a_target, a_clamp);
        break;
    }
    case GLFuncId::glClearBufferfi: {
        GLenum a_buffer = cur.Read<GLenum>();
        GLint a_drawbuffer = cur.Read<GLint>();
        GLfloat a_depth = cur.Read<GLfloat>();
        GLint a_stencil = cur.Read<GLint>();
        g_real.glClearBufferfi(a_buffer, a_drawbuffer, a_depth, a_stencil);
        break;
    }
    case GLFuncId::glClearDepthf: {
        GLfloat a_d = cur.Read<GLfloat>();
        g_real.glClearDepthf(a_d);
        break;
    }
    case GLFuncId::glClearNamedFramebufferfi: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_buffer = cur.Read<GLenum>();
        GLint a_drawbuffer = cur.Read<GLint>();
        GLfloat a_depth = cur.Read<GLfloat>();
        GLint a_stencil = cur.Read<GLint>();
        g_real.glClearNamedFramebufferfi(a_framebuffer, a_buffer, a_drawbuffer, a_depth, a_stencil);
        break;
    }
    case GLFuncId::glClientActiveTexture: {
        GLenum a_texture = cur.Read<GLenum>();
        g_real.glClientActiveTexture(a_texture);
        break;
    }
    case GLFuncId::glClipControl: {
        GLenum a_origin = cur.Read<GLenum>();
        GLenum a_depth = cur.Read<GLenum>();
        g_real.glClipControl(a_origin, a_depth);
        break;
    }
    case GLFuncId::glColorMaski: {
        GLuint a_index = cur.Read<GLuint>();
        GLboolean a_r = cur.Read<GLboolean>();
        GLboolean a_g = cur.Read<GLboolean>();
        GLboolean a_b = cur.Read<GLboolean>();
        GLboolean a_a = cur.Read<GLboolean>();
        g_real.glColorMaski(a_index, a_r, a_g, a_b, a_a);
        break;
    }
    case GLFuncId::glColorP3ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_color = cur.Read<GLuint>();
        g_real.glColorP3ui(a_type, a_color);
        break;
    }
    case GLFuncId::glColorP4ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_color = cur.Read<GLuint>();
        g_real.glColorP4ui(a_type, a_color);
        break;
    }
    case GLFuncId::glCopyBufferSubData: {
        GLenum a_readTarget = cur.Read<GLenum>();
        GLenum a_writeTarget = cur.Read<GLenum>();
        GLintptr a_readOffset = cur.Read<GLintptr>();
        GLintptr a_writeOffset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glCopyBufferSubData(a_readTarget, a_writeTarget, a_readOffset, a_writeOffset, a_size);
        break;
    }
    case GLFuncId::glCopyImageSubData: {
        GLuint a_srcName = cur.Read<GLuint>();
        GLenum a_srcTarget = cur.Read<GLenum>();
        GLint a_srcLevel = cur.Read<GLint>();
        GLint a_srcX = cur.Read<GLint>();
        GLint a_srcY = cur.Read<GLint>();
        GLint a_srcZ = cur.Read<GLint>();
        GLuint a_dstName = cur.Read<GLuint>();
        GLenum a_dstTarget = cur.Read<GLenum>();
        GLint a_dstLevel = cur.Read<GLint>();
        GLint a_dstX = cur.Read<GLint>();
        GLint a_dstY = cur.Read<GLint>();
        GLint a_dstZ = cur.Read<GLint>();
        GLsizei a_srcWidth = cur.Read<GLsizei>();
        GLsizei a_srcHeight = cur.Read<GLsizei>();
        GLsizei a_srcDepth = cur.Read<GLsizei>();
        g_real.glCopyImageSubData(a_srcName, a_srcTarget, a_srcLevel, a_srcX, a_srcY, a_srcZ, a_dstName, a_dstTarget, a_dstLevel, a_dstX, a_dstY, a_dstZ, a_srcWidth, a_srcHeight, a_srcDepth);
        break;
    }
    case GLFuncId::glCopyNamedBufferSubData: {
        GLuint a_readBuffer = cur.Read<GLuint>();
        GLuint a_writeBuffer = cur.Read<GLuint>();
        GLintptr a_readOffset = cur.Read<GLintptr>();
        GLintptr a_writeOffset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glCopyNamedBufferSubData(a_readBuffer, a_writeBuffer, a_readOffset, a_writeOffset, a_size);
        break;
    }
    case GLFuncId::glCopyTexSubImage3D: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_yoffset = cur.Read<GLint>();
        GLint a_zoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glCopyTexSubImage3D(a_target, a_level, a_xoffset, a_yoffset, a_zoffset, a_x, a_y, a_width, a_height);
        break;
    }
    case GLFuncId::glCopyTextureSubImage1D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        g_real.glCopyTextureSubImage1D(a_texture, a_level, a_xoffset, a_x, a_y, a_width);
        break;
    }
    case GLFuncId::glCopyTextureSubImage2D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_yoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glCopyTextureSubImage2D(a_texture, a_level, a_xoffset, a_yoffset, a_x, a_y, a_width, a_height);
        break;
    }
    case GLFuncId::glCopyTextureSubImage3D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_yoffset = cur.Read<GLint>();
        GLint a_zoffset = cur.Read<GLint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glCopyTextureSubImage3D(a_texture, a_level, a_xoffset, a_yoffset, a_zoffset, a_x, a_y, a_width, a_height);
        break;
    }
    case GLFuncId::glDeleteSync: {
        GLsync a_sync = cur.Read<GLsync>();
        g_real.glDeleteSync(a_sync);
        break;
    }
    case GLFuncId::glDepthRangeIndexed: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_n = cur.Read<GLdouble>();
        GLdouble a_f = cur.Read<GLdouble>();
        g_real.glDepthRangeIndexed(a_index, a_n, a_f);
        break;
    }
    case GLFuncId::glDepthRangef: {
        GLfloat a_n = cur.Read<GLfloat>();
        GLfloat a_f = cur.Read<GLfloat>();
        g_real.glDepthRangef(a_n, a_f);
        break;
    }
    case GLFuncId::glDisableVertexArrayAttrib: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_index = cur.Read<GLuint>();
        g_real.glDisableVertexArrayAttrib(a_vaobj, a_index);
        break;
    }
    case GLFuncId::glDisablei: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        g_real.glDisablei(a_target, a_index);
        break;
    }
    case GLFuncId::glDispatchCompute: {
        GLuint a_num_groups_x = cur.Read<GLuint>();
        GLuint a_num_groups_y = cur.Read<GLuint>();
        GLuint a_num_groups_z = cur.Read<GLuint>();
        g_real.glDispatchCompute(a_num_groups_x, a_num_groups_y, a_num_groups_z);
        break;
    }
    case GLFuncId::glDispatchComputeIndirect: {
        GLintptr a_indirect = cur.Read<GLintptr>();
        g_real.glDispatchComputeIndirect(a_indirect);
        break;
    }
    case GLFuncId::glDrawArraysInstancedBaseInstance: {
        GLenum a_mode = cur.Read<GLenum>();
        GLint a_first = cur.Read<GLint>();
        GLsizei a_count = cur.Read<GLsizei>();
        GLsizei a_instancecount = cur.Read<GLsizei>();
        GLuint a_baseinstance = cur.Read<GLuint>();
        g_real.glDrawArraysInstancedBaseInstance(a_mode, a_first, a_count, a_instancecount, a_baseinstance);
        break;
    }
    case GLFuncId::glDrawTransformFeedback: {
        GLenum a_mode = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        g_real.glDrawTransformFeedback(a_mode, a_id);
        break;
    }
    case GLFuncId::glDrawTransformFeedbackInstanced: {
        GLenum a_mode = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        GLsizei a_instancecount = cur.Read<GLsizei>();
        g_real.glDrawTransformFeedbackInstanced(a_mode, a_id, a_instancecount);
        break;
    }
    case GLFuncId::glDrawTransformFeedbackStream: {
        GLenum a_mode = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_stream = cur.Read<GLuint>();
        g_real.glDrawTransformFeedbackStream(a_mode, a_id, a_stream);
        break;
    }
    case GLFuncId::glDrawTransformFeedbackStreamInstanced: {
        GLenum a_mode = cur.Read<GLenum>();
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_stream = cur.Read<GLuint>();
        GLsizei a_instancecount = cur.Read<GLsizei>();
        g_real.glDrawTransformFeedbackStreamInstanced(a_mode, a_id, a_stream, a_instancecount);
        break;
    }
    case GLFuncId::glEnableVertexArrayAttrib: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_index = cur.Read<GLuint>();
        g_real.glEnableVertexArrayAttrib(a_vaobj, a_index);
        break;
    }
    case GLFuncId::glEnablei: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        g_real.glEnablei(a_target, a_index);
        break;
    }
    case GLFuncId::glEndConditionalRender: {
        g_real.glEndConditionalRender();
        break;
    }
    case GLFuncId::glEndQuery: {
        GLenum a_target = cur.Read<GLenum>();
        g_real.glEndQuery(a_target);
        break;
    }
    case GLFuncId::glEndQueryIndexed: {
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_index = cur.Read<GLuint>();
        g_real.glEndQueryIndexed(a_target, a_index);
        break;
    }
    case GLFuncId::glEndTransformFeedback: {
        g_real.glEndTransformFeedback();
        break;
    }
    case GLFuncId::glFlushMappedBufferRange: {
        GLenum a_target = cur.Read<GLenum>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        g_real.glFlushMappedBufferRange(a_target, a_offset, a_length);
        break;
    }
    case GLFuncId::glFlushMappedNamedBufferRange: {
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        g_real.glFlushMappedNamedBufferRange(a_buffer, a_offset, a_length);
        break;
    }
    case GLFuncId::glFogCoordd: {
        GLdouble a_coord = cur.Read<GLdouble>();
        g_real.glFogCoordd(a_coord);
        break;
    }
    case GLFuncId::glFogCoordf: {
        GLfloat a_coord = cur.Read<GLfloat>();
        g_real.glFogCoordf(a_coord);
        break;
    }
    case GLFuncId::glFramebufferParameteri: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glFramebufferParameteri(a_target, a_pname, a_param);
        break;
    }
    case GLFuncId::glFramebufferTexture: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        g_real.glFramebufferTexture(a_target, a_attachment, a_texture, a_level);
        break;
    }
    case GLFuncId::glFramebufferTexture1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLenum a_textarget = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        g_real.glFramebufferTexture1D(a_target, a_attachment, a_textarget, a_texture, a_level);
        break;
    }
    case GLFuncId::glFramebufferTexture3D: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLenum a_textarget = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_zoffset = cur.Read<GLint>();
        g_real.glFramebufferTexture3D(a_target, a_attachment, a_textarget, a_texture, a_level, a_zoffset);
        break;
    }
    case GLFuncId::glFramebufferTextureLayer: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_layer = cur.Read<GLint>();
        g_real.glFramebufferTextureLayer(a_target, a_attachment, a_texture, a_level, a_layer);
        break;
    }
    case GLFuncId::glGenerateTextureMipmap: {
        GLuint a_texture = cur.Read<GLuint>();
        g_real.glGenerateTextureMipmap(a_texture);
        break;
    }
    case GLFuncId::glGetQueryBufferObjecti64v: {
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLintptr a_offset = cur.Read<GLintptr>();
        g_real.glGetQueryBufferObjecti64v(a_id, a_buffer, a_pname, a_offset);
        break;
    }
    case GLFuncId::glGetQueryBufferObjectiv: {
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLintptr a_offset = cur.Read<GLintptr>();
        g_real.glGetQueryBufferObjectiv(a_id, a_buffer, a_pname, a_offset);
        break;
    }
    case GLFuncId::glGetQueryBufferObjectui64v: {
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLintptr a_offset = cur.Read<GLintptr>();
        g_real.glGetQueryBufferObjectui64v(a_id, a_buffer, a_pname, a_offset);
        break;
    }
    case GLFuncId::glGetQueryBufferObjectuiv: {
        GLuint a_id = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLintptr a_offset = cur.Read<GLintptr>();
        g_real.glGetQueryBufferObjectuiv(a_id, a_buffer, a_pname, a_offset);
        break;
    }
    case GLFuncId::glInvalidateBufferData: {
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glInvalidateBufferData(a_buffer);
        break;
    }
    case GLFuncId::glInvalidateBufferSubData: {
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_length = cur.Read<GLsizeiptr>();
        g_real.glInvalidateBufferSubData(a_buffer, a_offset, a_length);
        break;
    }
    case GLFuncId::glInvalidateTexImage: {
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        g_real.glInvalidateTexImage(a_texture, a_level);
        break;
    }
    case GLFuncId::glInvalidateTexSubImage: {
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_xoffset = cur.Read<GLint>();
        GLint a_yoffset = cur.Read<GLint>();
        GLint a_zoffset = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        g_real.glInvalidateTexSubImage(a_texture, a_level, a_xoffset, a_yoffset, a_zoffset, a_width, a_height, a_depth);
        break;
    }
    case GLFuncId::glMemoryBarrier: {
        GLbitfield a_barriers = cur.Read<GLbitfield>();
        g_real.glMemoryBarrier(a_barriers);
        break;
    }
    case GLFuncId::glMemoryBarrierByRegion: {
        GLbitfield a_barriers = cur.Read<GLbitfield>();
        g_real.glMemoryBarrierByRegion(a_barriers);
        break;
    }
    case GLFuncId::glMinSampleShading: {
        GLfloat a_value = cur.Read<GLfloat>();
        g_real.glMinSampleShading(a_value);
        break;
    }
    case GLFuncId::glMultiTexCoord1d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_s = cur.Read<GLdouble>();
        g_real.glMultiTexCoord1d(a_target, a_s);
        break;
    }
    case GLFuncId::glMultiTexCoord1f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_s = cur.Read<GLfloat>();
        g_real.glMultiTexCoord1f(a_target, a_s);
        break;
    }
    case GLFuncId::glMultiTexCoord1i: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_s = cur.Read<GLint>();
        g_real.glMultiTexCoord1i(a_target, a_s);
        break;
    }
    case GLFuncId::glMultiTexCoord1s: {
        GLenum a_target = cur.Read<GLenum>();
        GLshort a_s = cur.Read<GLshort>();
        g_real.glMultiTexCoord1s(a_target, a_s);
        break;
    }
    case GLFuncId::glMultiTexCoord2d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        g_real.glMultiTexCoord2d(a_target, a_s, a_t);
        break;
    }
    case GLFuncId::glMultiTexCoord2f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        g_real.glMultiTexCoord2f(a_target, a_s, a_t);
        break;
    }
    case GLFuncId::glMultiTexCoord2i: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        g_real.glMultiTexCoord2i(a_target, a_s, a_t);
        break;
    }
    case GLFuncId::glMultiTexCoord2s: {
        GLenum a_target = cur.Read<GLenum>();
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        g_real.glMultiTexCoord2s(a_target, a_s, a_t);
        break;
    }
    case GLFuncId::glMultiTexCoord3d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        g_real.glMultiTexCoord3d(a_target, a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glMultiTexCoord3f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        GLfloat a_r = cur.Read<GLfloat>();
        g_real.glMultiTexCoord3f(a_target, a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glMultiTexCoord3i: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        GLint a_r = cur.Read<GLint>();
        g_real.glMultiTexCoord3i(a_target, a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glMultiTexCoord3s: {
        GLenum a_target = cur.Read<GLenum>();
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        GLshort a_r = cur.Read<GLshort>();
        g_real.glMultiTexCoord3s(a_target, a_s, a_t, a_r);
        break;
    }
    case GLFuncId::glMultiTexCoord4d: {
        GLenum a_target = cur.Read<GLenum>();
        GLdouble a_s = cur.Read<GLdouble>();
        GLdouble a_t = cur.Read<GLdouble>();
        GLdouble a_r = cur.Read<GLdouble>();
        GLdouble a_q = cur.Read<GLdouble>();
        g_real.glMultiTexCoord4d(a_target, a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glMultiTexCoord4f: {
        GLenum a_target = cur.Read<GLenum>();
        GLfloat a_s = cur.Read<GLfloat>();
        GLfloat a_t = cur.Read<GLfloat>();
        GLfloat a_r = cur.Read<GLfloat>();
        GLfloat a_q = cur.Read<GLfloat>();
        g_real.glMultiTexCoord4f(a_target, a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glMultiTexCoord4i: {
        GLenum a_target = cur.Read<GLenum>();
        GLint a_s = cur.Read<GLint>();
        GLint a_t = cur.Read<GLint>();
        GLint a_r = cur.Read<GLint>();
        GLint a_q = cur.Read<GLint>();
        g_real.glMultiTexCoord4i(a_target, a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glMultiTexCoord4s: {
        GLenum a_target = cur.Read<GLenum>();
        GLshort a_s = cur.Read<GLshort>();
        GLshort a_t = cur.Read<GLshort>();
        GLshort a_r = cur.Read<GLshort>();
        GLshort a_q = cur.Read<GLshort>();
        g_real.glMultiTexCoord4s(a_target, a_s, a_t, a_r, a_q);
        break;
    }
    case GLFuncId::glMultiTexCoordP1ui: {
        GLenum a_texture = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glMultiTexCoordP1ui(a_texture, a_type, a_coords);
        break;
    }
    case GLFuncId::glMultiTexCoordP2ui: {
        GLenum a_texture = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glMultiTexCoordP2ui(a_texture, a_type, a_coords);
        break;
    }
    case GLFuncId::glMultiTexCoordP3ui: {
        GLenum a_texture = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glMultiTexCoordP3ui(a_texture, a_type, a_coords);
        break;
    }
    case GLFuncId::glMultiTexCoordP4ui: {
        GLenum a_texture = cur.Read<GLenum>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glMultiTexCoordP4ui(a_texture, a_type, a_coords);
        break;
    }
    case GLFuncId::glNamedFramebufferDrawBuffer: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_buf = cur.Read<GLenum>();
        g_real.glNamedFramebufferDrawBuffer(a_framebuffer, a_buf);
        break;
    }
    case GLFuncId::glNamedFramebufferParameteri: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glNamedFramebufferParameteri(a_framebuffer, a_pname, a_param);
        break;
    }
    case GLFuncId::glNamedFramebufferReadBuffer: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_src = cur.Read<GLenum>();
        g_real.glNamedFramebufferReadBuffer(a_framebuffer, a_src);
        break;
    }
    case GLFuncId::glNamedFramebufferRenderbuffer: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLenum a_renderbuffertarget = cur.Read<GLenum>();
        GLuint a_renderbuffer = cur.Read<GLuint>();
        g_real.glNamedFramebufferRenderbuffer(a_framebuffer, a_attachment, a_renderbuffertarget, a_renderbuffer);
        break;
    }
    case GLFuncId::glNamedFramebufferTexture: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        g_real.glNamedFramebufferTexture(a_framebuffer, a_attachment, a_texture, a_level);
        break;
    }
    case GLFuncId::glNamedFramebufferTextureLayer: {
        GLuint a_framebuffer = cur.Read<GLuint>();
        GLenum a_attachment = cur.Read<GLenum>();
        GLuint a_texture = cur.Read<GLuint>();
        GLint a_level = cur.Read<GLint>();
        GLint a_layer = cur.Read<GLint>();
        g_real.glNamedFramebufferTextureLayer(a_framebuffer, a_attachment, a_texture, a_level, a_layer);
        break;
    }
    case GLFuncId::glNamedRenderbufferStorage: {
        GLuint a_renderbuffer = cur.Read<GLuint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glNamedRenderbufferStorage(a_renderbuffer, a_internalformat, a_width, a_height);
        break;
    }
    case GLFuncId::glNamedRenderbufferStorageMultisample: {
        GLuint a_renderbuffer = cur.Read<GLuint>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glNamedRenderbufferStorageMultisample(a_renderbuffer, a_samples, a_internalformat, a_width, a_height);
        break;
    }
    case GLFuncId::glNormalP3ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glNormalP3ui(a_type, a_coords);
        break;
    }
    case GLFuncId::glPatchParameteri: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_value = cur.Read<GLint>();
        g_real.glPatchParameteri(a_pname, a_value);
        break;
    }
    case GLFuncId::glPauseTransformFeedback: {
        g_real.glPauseTransformFeedback();
        break;
    }
    case GLFuncId::glPointParameterf: {
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glPointParameterf(a_pname, a_param);
        break;
    }
    case GLFuncId::glPointParameteri: {
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glPointParameteri(a_pname, a_param);
        break;
    }
    case GLFuncId::glPolygonOffsetClamp: {
        GLfloat a_factor = cur.Read<GLfloat>();
        GLfloat a_units = cur.Read<GLfloat>();
        GLfloat a_clamp = cur.Read<GLfloat>();
        g_real.glPolygonOffsetClamp(a_factor, a_units, a_clamp);
        break;
    }
    case GLFuncId::glPopDebugGroup: {
        g_real.glPopDebugGroup();
        break;
    }
    case GLFuncId::glPrimitiveRestartIndex: {
        GLuint a_index = cur.Read<GLuint>();
        g_real.glPrimitiveRestartIndex(a_index);
        break;
    }
    case GLFuncId::glProgramParameteri: {
        GLuint a_program = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_value = cur.Read<GLint>();
        g_real.glProgramParameteri(a_program, a_pname, a_value);
        break;
    }
    case GLFuncId::glProgramUniform1d: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLdouble a_v0 = cur.Read<GLdouble>();
        g_real.glProgramUniform1d(a_program, a_location, a_v0);
        break;
    }
    case GLFuncId::glProgramUniform1f: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        g_real.glProgramUniform1f(a_program, a_location, a_v0);
        break;
    }
    case GLFuncId::glProgramUniform1i: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        g_real.glProgramUniform1i(a_program, a_location, a_v0);
        break;
    }
    case GLFuncId::glProgramUniform1ui: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        g_real.glProgramUniform1ui(a_program, a_location, a_v0);
        break;
    }
    case GLFuncId::glProgramUniform2d: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLdouble a_v0 = cur.Read<GLdouble>();
        GLdouble a_v1 = cur.Read<GLdouble>();
        g_real.glProgramUniform2d(a_program, a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glProgramUniform2f: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        g_real.glProgramUniform2f(a_program, a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glProgramUniform2i: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        g_real.glProgramUniform2i(a_program, a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glProgramUniform2ui: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        g_real.glProgramUniform2ui(a_program, a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glProgramUniform3d: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLdouble a_v0 = cur.Read<GLdouble>();
        GLdouble a_v1 = cur.Read<GLdouble>();
        GLdouble a_v2 = cur.Read<GLdouble>();
        g_real.glProgramUniform3d(a_program, a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glProgramUniform3f: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        g_real.glProgramUniform3f(a_program, a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glProgramUniform3i: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        GLint a_v2 = cur.Read<GLint>();
        g_real.glProgramUniform3i(a_program, a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glProgramUniform3ui: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        GLuint a_v2 = cur.Read<GLuint>();
        g_real.glProgramUniform3ui(a_program, a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glProgramUniform4d: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLdouble a_v0 = cur.Read<GLdouble>();
        GLdouble a_v1 = cur.Read<GLdouble>();
        GLdouble a_v2 = cur.Read<GLdouble>();
        GLdouble a_v3 = cur.Read<GLdouble>();
        g_real.glProgramUniform4d(a_program, a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glProgramUniform4f: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLfloat a_v0 = cur.Read<GLfloat>();
        GLfloat a_v1 = cur.Read<GLfloat>();
        GLfloat a_v2 = cur.Read<GLfloat>();
        GLfloat a_v3 = cur.Read<GLfloat>();
        g_real.glProgramUniform4f(a_program, a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glProgramUniform4i: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        GLint a_v2 = cur.Read<GLint>();
        GLint a_v3 = cur.Read<GLint>();
        g_real.glProgramUniform4i(a_program, a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glProgramUniform4ui: {
        GLuint a_program = cur.Read<GLuint>();
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        GLuint a_v2 = cur.Read<GLuint>();
        GLuint a_v3 = cur.Read<GLuint>();
        g_real.glProgramUniform4ui(a_program, a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glProvokingVertex: {
        GLenum a_mode = cur.Read<GLenum>();
        g_real.glProvokingVertex(a_mode);
        break;
    }
    case GLFuncId::glQueryCounter: {
        GLuint a_id = cur.Read<GLuint>();
        GLenum a_target = cur.Read<GLenum>();
        g_real.glQueryCounter(a_id, a_target);
        break;
    }
    case GLFuncId::glReleaseShaderCompiler: {
        g_real.glReleaseShaderCompiler();
        break;
    }
    case GLFuncId::glRenderbufferStorageMultisample: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glRenderbufferStorageMultisample(a_target, a_samples, a_internalformat, a_width, a_height);
        break;
    }
    case GLFuncId::glResumeTransformFeedback: {
        g_real.glResumeTransformFeedback();
        break;
    }
    case GLFuncId::glSampleCoverage: {
        GLfloat a_value = cur.Read<GLfloat>();
        GLboolean a_invert = cur.Read<GLboolean>();
        g_real.glSampleCoverage(a_value, a_invert);
        break;
    }
    case GLFuncId::glSampleMaski: {
        GLuint a_maskNumber = cur.Read<GLuint>();
        GLbitfield a_mask = cur.Read<GLbitfield>();
        g_real.glSampleMaski(a_maskNumber, a_mask);
        break;
    }
    case GLFuncId::glSamplerParameterf: {
        GLuint a_sampler = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glSamplerParameterf(a_sampler, a_pname, a_param);
        break;
    }
    case GLFuncId::glSamplerParameteri: {
        GLuint a_sampler = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glSamplerParameteri(a_sampler, a_pname, a_param);
        break;
    }
    case GLFuncId::glScissorIndexed: {
        GLuint a_index = cur.Read<GLuint>();
        GLint a_left = cur.Read<GLint>();
        GLint a_bottom = cur.Read<GLint>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glScissorIndexed(a_index, a_left, a_bottom, a_width, a_height);
        break;
    }
    case GLFuncId::glSecondaryColor3b: {
        GLbyte a_red = cur.Read<GLbyte>();
        GLbyte a_green = cur.Read<GLbyte>();
        GLbyte a_blue = cur.Read<GLbyte>();
        g_real.glSecondaryColor3b(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3d: {
        GLdouble a_red = cur.Read<GLdouble>();
        GLdouble a_green = cur.Read<GLdouble>();
        GLdouble a_blue = cur.Read<GLdouble>();
        g_real.glSecondaryColor3d(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3f: {
        GLfloat a_red = cur.Read<GLfloat>();
        GLfloat a_green = cur.Read<GLfloat>();
        GLfloat a_blue = cur.Read<GLfloat>();
        g_real.glSecondaryColor3f(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3i: {
        GLint a_red = cur.Read<GLint>();
        GLint a_green = cur.Read<GLint>();
        GLint a_blue = cur.Read<GLint>();
        g_real.glSecondaryColor3i(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3s: {
        GLshort a_red = cur.Read<GLshort>();
        GLshort a_green = cur.Read<GLshort>();
        GLshort a_blue = cur.Read<GLshort>();
        g_real.glSecondaryColor3s(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3ub: {
        GLubyte a_red = cur.Read<GLubyte>();
        GLubyte a_green = cur.Read<GLubyte>();
        GLubyte a_blue = cur.Read<GLubyte>();
        g_real.glSecondaryColor3ub(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3ui: {
        GLuint a_red = cur.Read<GLuint>();
        GLuint a_green = cur.Read<GLuint>();
        GLuint a_blue = cur.Read<GLuint>();
        g_real.glSecondaryColor3ui(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColor3us: {
        GLushort a_red = cur.Read<GLushort>();
        GLushort a_green = cur.Read<GLushort>();
        GLushort a_blue = cur.Read<GLushort>();
        g_real.glSecondaryColor3us(a_red, a_green, a_blue);
        break;
    }
    case GLFuncId::glSecondaryColorP3ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_color = cur.Read<GLuint>();
        g_real.glSecondaryColorP3ui(a_type, a_color);
        break;
    }
    case GLFuncId::glShaderStorageBlockBinding: {
        GLuint a_program = cur.Read<GLuint>();
        GLuint a_storageBlockIndex = cur.Read<GLuint>();
        GLuint a_storageBlockBinding = cur.Read<GLuint>();
        g_real.glShaderStorageBlockBinding(a_program, a_storageBlockIndex, a_storageBlockBinding);
        break;
    }
    case GLFuncId::glStencilFuncSeparate: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_func = cur.Read<GLenum>();
        GLint a_ref = cur.Read<GLint>();
        GLuint a_mask = cur.Read<GLuint>();
        g_real.glStencilFuncSeparate(a_face, a_func, a_ref, a_mask);
        break;
    }
    case GLFuncId::glStencilMaskSeparate: {
        GLenum a_face = cur.Read<GLenum>();
        GLuint a_mask = cur.Read<GLuint>();
        g_real.glStencilMaskSeparate(a_face, a_mask);
        break;
    }
    case GLFuncId::glStencilOpSeparate: {
        GLenum a_face = cur.Read<GLenum>();
        GLenum a_sfail = cur.Read<GLenum>();
        GLenum a_dpfail = cur.Read<GLenum>();
        GLenum a_dppass = cur.Read<GLenum>();
        g_real.glStencilOpSeparate(a_face, a_sfail, a_dpfail, a_dppass);
        break;
    }
    case GLFuncId::glTexBuffer: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glTexBuffer(a_target, a_internalformat, a_buffer);
        break;
    }
    case GLFuncId::glTexBufferRange: {
        GLenum a_target = cur.Read<GLenum>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glTexBufferRange(a_target, a_internalformat, a_buffer, a_offset, a_size);
        break;
    }
    case GLFuncId::glTexCoordP1ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glTexCoordP1ui(a_type, a_coords);
        break;
    }
    case GLFuncId::glTexCoordP2ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glTexCoordP2ui(a_type, a_coords);
        break;
    }
    case GLFuncId::glTexCoordP3ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glTexCoordP3ui(a_type, a_coords);
        break;
    }
    case GLFuncId::glTexCoordP4ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_coords = cur.Read<GLuint>();
        g_real.glTexCoordP4ui(a_type, a_coords);
        break;
    }
    case GLFuncId::glTexImage2DMultisample: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTexImage2DMultisample(a_target, a_samples, a_internalformat, a_width, a_height, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTexImage3DMultisample: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTexImage3DMultisample(a_target, a_samples, a_internalformat, a_width, a_height, a_depth, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTexStorage1D: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        g_real.glTexStorage1D(a_target, a_levels, a_internalformat, a_width);
        break;
    }
    case GLFuncId::glTexStorage2D: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glTexStorage2D(a_target, a_levels, a_internalformat, a_width, a_height);
        break;
    }
    case GLFuncId::glTexStorage2DMultisample: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTexStorage2DMultisample(a_target, a_samples, a_internalformat, a_width, a_height, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTexStorage3D: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        g_real.glTexStorage3D(a_target, a_levels, a_internalformat, a_width, a_height, a_depth);
        break;
    }
    case GLFuncId::glTexStorage3DMultisample: {
        GLenum a_target = cur.Read<GLenum>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTexStorage3DMultisample(a_target, a_samples, a_internalformat, a_width, a_height, a_depth, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTextureBarrier: {
        g_real.glTextureBarrier();
        break;
    }
    case GLFuncId::glTextureBuffer: {
        GLuint a_texture = cur.Read<GLuint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glTextureBuffer(a_texture, a_internalformat, a_buffer);
        break;
    }
    case GLFuncId::glTextureBufferRange: {
        GLuint a_texture = cur.Read<GLuint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glTextureBufferRange(a_texture, a_internalformat, a_buffer, a_offset, a_size);
        break;
    }
    case GLFuncId::glTextureParameterf: {
        GLuint a_texture = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLfloat a_param = cur.Read<GLfloat>();
        g_real.glTextureParameterf(a_texture, a_pname, a_param);
        break;
    }
    case GLFuncId::glTextureParameteri: {
        GLuint a_texture = cur.Read<GLuint>();
        GLenum a_pname = cur.Read<GLenum>();
        GLint a_param = cur.Read<GLint>();
        g_real.glTextureParameteri(a_texture, a_pname, a_param);
        break;
    }
    case GLFuncId::glTextureStorage1D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        g_real.glTextureStorage1D(a_texture, a_levels, a_internalformat, a_width);
        break;
    }
    case GLFuncId::glTextureStorage2D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        g_real.glTextureStorage2D(a_texture, a_levels, a_internalformat, a_width, a_height);
        break;
    }
    case GLFuncId::glTextureStorage2DMultisample: {
        GLuint a_texture = cur.Read<GLuint>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTextureStorage2DMultisample(a_texture, a_samples, a_internalformat, a_width, a_height, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTextureStorage3D: {
        GLuint a_texture = cur.Read<GLuint>();
        GLsizei a_levels = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        g_real.glTextureStorage3D(a_texture, a_levels, a_internalformat, a_width, a_height, a_depth);
        break;
    }
    case GLFuncId::glTextureStorage3DMultisample: {
        GLuint a_texture = cur.Read<GLuint>();
        GLsizei a_samples = cur.Read<GLsizei>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLsizei a_width = cur.Read<GLsizei>();
        GLsizei a_height = cur.Read<GLsizei>();
        GLsizei a_depth = cur.Read<GLsizei>();
        GLboolean a_fixedsamplelocations = cur.Read<GLboolean>();
        g_real.glTextureStorage3DMultisample(a_texture, a_samples, a_internalformat, a_width, a_height, a_depth, a_fixedsamplelocations);
        break;
    }
    case GLFuncId::glTextureView: {
        GLuint a_texture = cur.Read<GLuint>();
        GLenum a_target = cur.Read<GLenum>();
        GLuint a_origtexture = cur.Read<GLuint>();
        GLenum a_internalformat = cur.Read<GLenum>();
        GLuint a_minlevel = cur.Read<GLuint>();
        GLuint a_numlevels = cur.Read<GLuint>();
        GLuint a_minlayer = cur.Read<GLuint>();
        GLuint a_numlayers = cur.Read<GLuint>();
        g_real.glTextureView(a_texture, a_target, a_origtexture, a_internalformat, a_minlevel, a_numlevels, a_minlayer, a_numlayers);
        break;
    }
    case GLFuncId::glTransformFeedbackBufferBase: {
        GLuint a_xfb = cur.Read<GLuint>();
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glTransformFeedbackBufferBase(a_xfb, a_index, a_buffer);
        break;
    }
    case GLFuncId::glTransformFeedbackBufferRange: {
        GLuint a_xfb = cur.Read<GLuint>();
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizeiptr a_size = cur.Read<GLsizeiptr>();
        g_real.glTransformFeedbackBufferRange(a_xfb, a_index, a_buffer, a_offset, a_size);
        break;
    }
    case GLFuncId::glUniform1d: {
        GLint a_location = cur.Read<GLint>();
        GLdouble a_x = cur.Read<GLdouble>();
        g_real.glUniform1d(a_location, a_x);
        break;
    }
    case GLFuncId::glUniform1ui: {
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        g_real.glUniform1ui(a_location, a_v0);
        break;
    }
    case GLFuncId::glUniform2d: {
        GLint a_location = cur.Read<GLint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glUniform2d(a_location, a_x, a_y);
        break;
    }
    case GLFuncId::glUniform2i: {
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        g_real.glUniform2i(a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glUniform2ui: {
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        g_real.glUniform2ui(a_location, a_v0, a_v1);
        break;
    }
    case GLFuncId::glUniform3d: {
        GLint a_location = cur.Read<GLint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glUniform3d(a_location, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glUniform3i: {
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        GLint a_v2 = cur.Read<GLint>();
        g_real.glUniform3i(a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glUniform3ui: {
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        GLuint a_v2 = cur.Read<GLuint>();
        g_real.glUniform3ui(a_location, a_v0, a_v1, a_v2);
        break;
    }
    case GLFuncId::glUniform4d: {
        GLint a_location = cur.Read<GLint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        GLdouble a_w = cur.Read<GLdouble>();
        g_real.glUniform4d(a_location, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glUniform4i: {
        GLint a_location = cur.Read<GLint>();
        GLint a_v0 = cur.Read<GLint>();
        GLint a_v1 = cur.Read<GLint>();
        GLint a_v2 = cur.Read<GLint>();
        GLint a_v3 = cur.Read<GLint>();
        g_real.glUniform4i(a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glUniform4ui: {
        GLint a_location = cur.Read<GLint>();
        GLuint a_v0 = cur.Read<GLuint>();
        GLuint a_v1 = cur.Read<GLuint>();
        GLuint a_v2 = cur.Read<GLuint>();
        GLuint a_v3 = cur.Read<GLuint>();
        g_real.glUniform4ui(a_location, a_v0, a_v1, a_v2, a_v3);
        break;
    }
    case GLFuncId::glUniformBlockBinding: {
        GLuint a_program = cur.Read<GLuint>();
        GLuint a_uniformBlockIndex = cur.Read<GLuint>();
        GLuint a_uniformBlockBinding = cur.Read<GLuint>();
        g_real.glUniformBlockBinding(a_program, a_uniformBlockIndex, a_uniformBlockBinding);
        break;
    }
    case GLFuncId::glUseProgramStages: {
        GLuint a_pipeline = cur.Read<GLuint>();
        GLbitfield a_stages = cur.Read<GLbitfield>();
        GLuint a_program = cur.Read<GLuint>();
        g_real.glUseProgramStages(a_pipeline, a_stages, a_program);
        break;
    }
    case GLFuncId::glValidateProgram: {
        GLuint a_program = cur.Read<GLuint>();
        g_real.glValidateProgram(a_program);
        break;
    }
    case GLFuncId::glValidateProgramPipeline: {
        GLuint a_pipeline = cur.Read<GLuint>();
        g_real.glValidateProgramPipeline(a_pipeline);
        break;
    }
    case GLFuncId::glVertexArrayAttribBinding: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_attribindex = cur.Read<GLuint>();
        GLuint a_bindingindex = cur.Read<GLuint>();
        g_real.glVertexArrayAttribBinding(a_vaobj, a_attribindex, a_bindingindex);
        break;
    }
    case GLFuncId::glVertexArrayAttribFormat: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexArrayAttribFormat(a_vaobj, a_attribindex, a_size, a_type, a_normalized, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexArrayAttribIFormat: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexArrayAttribIFormat(a_vaobj, a_attribindex, a_size, a_type, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexArrayAttribLFormat: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexArrayAttribLFormat(a_vaobj, a_attribindex, a_size, a_type, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexArrayBindingDivisor: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_bindingindex = cur.Read<GLuint>();
        GLuint a_divisor = cur.Read<GLuint>();
        g_real.glVertexArrayBindingDivisor(a_vaobj, a_bindingindex, a_divisor);
        break;
    }
    case GLFuncId::glVertexArrayElementBuffer: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        g_real.glVertexArrayElementBuffer(a_vaobj, a_buffer);
        break;
    }
    case GLFuncId::glVertexArrayVertexBuffer: {
        GLuint a_vaobj = cur.Read<GLuint>();
        GLuint a_bindingindex = cur.Read<GLuint>();
        GLuint a_buffer = cur.Read<GLuint>();
        GLintptr a_offset = cur.Read<GLintptr>();
        GLsizei a_stride = cur.Read<GLsizei>();
        g_real.glVertexArrayVertexBuffer(a_vaobj, a_bindingindex, a_buffer, a_offset, a_stride);
        break;
    }
    case GLFuncId::glVertexAttrib1d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        g_real.glVertexAttrib1d(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttrib1f: {
        GLuint a_index = cur.Read<GLuint>();
        GLfloat a_x = cur.Read<GLfloat>();
        g_real.glVertexAttrib1f(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttrib1s: {
        GLuint a_index = cur.Read<GLuint>();
        GLshort a_x = cur.Read<GLshort>();
        g_real.glVertexAttrib1s(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttrib2d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glVertexAttrib2d(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttrib2f: {
        GLuint a_index = cur.Read<GLuint>();
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        g_real.glVertexAttrib2f(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttrib2s: {
        GLuint a_index = cur.Read<GLuint>();
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        g_real.glVertexAttrib2s(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttrib3d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glVertexAttrib3d(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttrib3f: {
        GLuint a_index = cur.Read<GLuint>();
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glVertexAttrib3f(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttrib3s: {
        GLuint a_index = cur.Read<GLuint>();
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        g_real.glVertexAttrib3s(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttrib4Nub: {
        GLuint a_index = cur.Read<GLuint>();
        GLubyte a_x = cur.Read<GLubyte>();
        GLubyte a_y = cur.Read<GLubyte>();
        GLubyte a_z = cur.Read<GLubyte>();
        GLubyte a_w = cur.Read<GLubyte>();
        g_real.glVertexAttrib4Nub(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttrib4d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        GLdouble a_w = cur.Read<GLdouble>();
        g_real.glVertexAttrib4d(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttrib4f: {
        GLuint a_index = cur.Read<GLuint>();
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        GLfloat a_w = cur.Read<GLfloat>();
        g_real.glVertexAttrib4f(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttrib4s: {
        GLuint a_index = cur.Read<GLuint>();
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        GLshort a_w = cur.Read<GLshort>();
        g_real.glVertexAttrib4s(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttribBinding: {
        GLuint a_attribindex = cur.Read<GLuint>();
        GLuint a_bindingindex = cur.Read<GLuint>();
        g_real.glVertexAttribBinding(a_attribindex, a_bindingindex);
        break;
    }
    case GLFuncId::glVertexAttribDivisor: {
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_divisor = cur.Read<GLuint>();
        g_real.glVertexAttribDivisor(a_index, a_divisor);
        break;
    }
    case GLFuncId::glVertexAttribFormat: {
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexAttribFormat(a_attribindex, a_size, a_type, a_normalized, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexAttribI1i: {
        GLuint a_index = cur.Read<GLuint>();
        GLint a_x = cur.Read<GLint>();
        g_real.glVertexAttribI1i(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttribI1ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_x = cur.Read<GLuint>();
        g_real.glVertexAttribI1ui(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttribI2i: {
        GLuint a_index = cur.Read<GLuint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        g_real.glVertexAttribI2i(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttribI2ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_x = cur.Read<GLuint>();
        GLuint a_y = cur.Read<GLuint>();
        g_real.glVertexAttribI2ui(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttribI3i: {
        GLuint a_index = cur.Read<GLuint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        g_real.glVertexAttribI3i(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttribI3ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_x = cur.Read<GLuint>();
        GLuint a_y = cur.Read<GLuint>();
        GLuint a_z = cur.Read<GLuint>();
        g_real.glVertexAttribI3ui(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttribI4i: {
        GLuint a_index = cur.Read<GLuint>();
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        GLint a_w = cur.Read<GLint>();
        g_real.glVertexAttribI4i(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttribI4ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLuint a_x = cur.Read<GLuint>();
        GLuint a_y = cur.Read<GLuint>();
        GLuint a_z = cur.Read<GLuint>();
        GLuint a_w = cur.Read<GLuint>();
        g_real.glVertexAttribI4ui(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttribIFormat: {
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexAttribIFormat(a_attribindex, a_size, a_type, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexAttribL1d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        g_real.glVertexAttribL1d(a_index, a_x);
        break;
    }
    case GLFuncId::glVertexAttribL2d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glVertexAttribL2d(a_index, a_x, a_y);
        break;
    }
    case GLFuncId::glVertexAttribL3d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glVertexAttribL3d(a_index, a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glVertexAttribL4d: {
        GLuint a_index = cur.Read<GLuint>();
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        GLdouble a_w = cur.Read<GLdouble>();
        g_real.glVertexAttribL4d(a_index, a_x, a_y, a_z, a_w);
        break;
    }
    case GLFuncId::glVertexAttribLFormat: {
        GLuint a_attribindex = cur.Read<GLuint>();
        GLint a_size = cur.Read<GLint>();
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_relativeoffset = cur.Read<GLuint>();
        g_real.glVertexAttribLFormat(a_attribindex, a_size, a_type, a_relativeoffset);
        break;
    }
    case GLFuncId::glVertexAttribP1ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexAttribP1ui(a_index, a_type, a_normalized, a_value);
        break;
    }
    case GLFuncId::glVertexAttribP2ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexAttribP2ui(a_index, a_type, a_normalized, a_value);
        break;
    }
    case GLFuncId::glVertexAttribP3ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexAttribP3ui(a_index, a_type, a_normalized, a_value);
        break;
    }
    case GLFuncId::glVertexAttribP4ui: {
        GLuint a_index = cur.Read<GLuint>();
        GLenum a_type = cur.Read<GLenum>();
        GLboolean a_normalized = cur.Read<GLboolean>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexAttribP4ui(a_index, a_type, a_normalized, a_value);
        break;
    }
    case GLFuncId::glVertexBindingDivisor: {
        GLuint a_bindingindex = cur.Read<GLuint>();
        GLuint a_divisor = cur.Read<GLuint>();
        g_real.glVertexBindingDivisor(a_bindingindex, a_divisor);
        break;
    }
    case GLFuncId::glVertexP2ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexP2ui(a_type, a_value);
        break;
    }
    case GLFuncId::glVertexP3ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexP3ui(a_type, a_value);
        break;
    }
    case GLFuncId::glVertexP4ui: {
        GLenum a_type = cur.Read<GLenum>();
        GLuint a_value = cur.Read<GLuint>();
        g_real.glVertexP4ui(a_type, a_value);
        break;
    }
    case GLFuncId::glViewportIndexedf: {
        GLuint a_index = cur.Read<GLuint>();
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_w = cur.Read<GLfloat>();
        GLfloat a_h = cur.Read<GLfloat>();
        g_real.glViewportIndexedf(a_index, a_x, a_y, a_w, a_h);
        break;
    }
    case GLFuncId::glWaitSync: {
        GLsync a_sync = cur.Read<GLsync>();
        GLbitfield a_flags = cur.Read<GLbitfield>();
        GLuint64 a_timeout = cur.Read<GLuint64>();
        g_real.glWaitSync(a_sync, a_flags, a_timeout);
        break;
    }
    case GLFuncId::glWindowPos2d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        g_real.glWindowPos2d(a_x, a_y);
        break;
    }
    case GLFuncId::glWindowPos2f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        g_real.glWindowPos2f(a_x, a_y);
        break;
    }
    case GLFuncId::glWindowPos2i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        g_real.glWindowPos2i(a_x, a_y);
        break;
    }
    case GLFuncId::glWindowPos2s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        g_real.glWindowPos2s(a_x, a_y);
        break;
    }
    case GLFuncId::glWindowPos3d: {
        GLdouble a_x = cur.Read<GLdouble>();
        GLdouble a_y = cur.Read<GLdouble>();
        GLdouble a_z = cur.Read<GLdouble>();
        g_real.glWindowPos3d(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glWindowPos3f: {
        GLfloat a_x = cur.Read<GLfloat>();
        GLfloat a_y = cur.Read<GLfloat>();
        GLfloat a_z = cur.Read<GLfloat>();
        g_real.glWindowPos3f(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glWindowPos3i: {
        GLint a_x = cur.Read<GLint>();
        GLint a_y = cur.Read<GLint>();
        GLint a_z = cur.Read<GLint>();
        g_real.glWindowPos3i(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glWindowPos3s: {
        GLshort a_x = cur.Read<GLshort>();
        GLshort a_y = cur.Read<GLshort>();
        GLshort a_z = cur.Read<GLshort>();
        g_real.glWindowPos3s(a_x, a_y, a_z);
        break;
    }
    case GLFuncId::glClearBufferfv: Replay_glClearBufferfv(args, len, remap); break;
    case GLFuncId::glCreateBuffers: Replay_glCreateBuffers(args, len, remap); break;
    case GLFuncId::glCreateFramebuffers: Replay_glCreateFramebuffers(args, len, remap); break;
    case GLFuncId::glCreateRenderbuffers: Replay_glCreateRenderbuffers(args, len, remap); break;
    case GLFuncId::glCreateTextures: Replay_glCreateTextures(args, len, remap); break;
    case GLFuncId::glCreateVertexArrays: Replay_glCreateVertexArrays(args, len, remap); break;
    case GLFuncId::glDebugMessageInsert: Replay_glDebugMessageInsert(args, len, remap); break;
    case GLFuncId::glGetProgramInfoLog: Replay_glGetProgramInfoLog(args, len, remap); break;
    case GLFuncId::glGetShaderInfoLog: Replay_glGetShaderInfoLog(args, len, remap); break;
    case GLFuncId::glNamedBufferStorage: Replay_glNamedBufferStorage(args, len, remap); break;
    case GLFuncId::glNamedBufferSubData: Replay_glNamedBufferSubData(args, len, remap); break;
    case GLFuncId::glNamedFramebufferDrawBuffers: Replay_glNamedFramebufferDrawBuffers(args, len, remap); break;
    case GLFuncId::glTextureSubImage2D: Replay_glTextureSubImage2D(args, len, remap); break;
    case GLFuncId::glTextureSubImage3D: Replay_glTextureSubImage3D(args, len, remap); break;
    case GLFuncId::wglCreateContext: Replay_wglCreateContext(args, len, remap); break;
    case GLFuncId::wglDeleteContext: Replay_wglDeleteContext(args, len, remap); break;
    case GLFuncId::wglMakeCurrent: Replay_wglMakeCurrent(args, len, remap); break;
    case GLFuncId::wglShareLists: Replay_wglShareLists(args, len, remap); break;
    case GLFuncId::wglSwapLayerBuffers: Replay_wglSwapLayerBuffers(args, len, remap); break;
    case GLFuncId::wglCreateContextAttribsARB: Replay_wglCreateContextAttribsARB(args, len, remap); break;
    default: break;
    }
}

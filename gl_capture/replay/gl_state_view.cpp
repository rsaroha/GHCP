#include "gl_state_view.h"

#include <cstdarg>
#include <cstdio>
#include <vector>

#include "gl_enum_names.h"
#include "gl_inspect.h"
#include "gl_real_table.h"

namespace {

// Just the GLenum values this file needs -- not worth pulling in a full GL
// header for a couple dozen well-known constants.
constexpr GLenum GL_ARRAY_BUFFER = 0x8892;
constexpr GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
constexpr GLenum GL_ARRAY_BUFFER_BINDING = 0x8894;
constexpr GLenum GL_ELEMENT_ARRAY_BUFFER_BINDING = 0x8895;
constexpr GLenum GL_BUFFER_SIZE = 0x8764;
constexpr GLenum GL_BUFFER_USAGE = 0x8765;

constexpr GLenum GL_TEXTURE0 = 0x84C0;
constexpr GLenum GL_TEXTURE_2D = 0x0DE1;
constexpr GLenum GL_ACTIVE_TEXTURE = 0x84E0;
constexpr GLenum GL_TEXTURE_BINDING_2D = 0x8069;
constexpr GLenum GL_TEXTURE_WIDTH = 0x1000;
constexpr GLenum GL_TEXTURE_HEIGHT = 0x1001;
constexpr GLenum GL_TEXTURE_INTERNAL_FORMAT = 0x1003;

constexpr GLenum GL_FRAMEBUFFER = 0x8D40;
constexpr GLenum GL_FRAMEBUFFER_BINDING = 0x8CA6;
constexpr GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
constexpr GLenum GL_DEPTH_ATTACHMENT = 0x8D00;
constexpr GLenum GL_STENCIL_ATTACHMENT = 0x8D20;
constexpr GLenum GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
constexpr GLenum GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
constexpr GLenum GL_NONE = 0;

constexpr GLenum GL_RENDERBUFFER = 0x8D41;
constexpr GLenum GL_RENDERBUFFER_BINDING = 0x8CA7;
constexpr GLenum GL_RENDERBUFFER_WIDTH = 0x8D42;
constexpr GLenum GL_RENDERBUFFER_HEIGHT = 0x8D43;
constexpr GLenum GL_RENDERBUFFER_INTERNAL_FORMAT = 0x8D44;

constexpr GLenum GL_CURRENT_PROGRAM = 0x8B8D;
constexpr GLenum GL_VERTEX_ARRAY_BINDING = 0x85B5;
constexpr GLenum GL_LINK_STATUS = 0x8B82;
constexpr GLenum GL_ATTACHED_SHADERS = 0x8B85;
constexpr GLenum GL_SHADER_TYPE = 0x8B4F;
constexpr GLenum GL_COMPILE_STATUS = 0x8B81;
constexpr GLenum GL_VERTEX_SHADER = 0x8B31;

constexpr GLenum GL_VIEWPORT = 0x0BA2;
constexpr GLenum GL_COLOR_CLEAR_VALUE = 0x0C22;
constexpr GLenum GL_BLEND = 0x0BE2;
constexpr GLenum GL_DEPTH_TEST = 0x0B71;
constexpr GLenum GL_CULL_FACE = 0x0B44;
constexpr GLenum GL_BLEND_SRC = 0x0BE1;
constexpr GLenum GL_BLEND_DST = 0x0BE0;
constexpr GLenum GL_DEPTH_FUNC = 0x0B74;

GLint GetInt(GLenum pname) {
    GLint v = 0;
    if (g_inspect.glGetIntegerv) g_inspect.glGetIntegerv(pname, &v);
    return v;
}

// Symbolic name for a GLenum value where we have one, else "0x<hex>".
std::string EnumStr(GLenum v) {
    if (const char* nm = LookupEnumName(v)) return nm;
    char buf[16];
    snprintf(buf, sizeof(buf), "0x%X", v);
    return buf;
}

// Appends one plain (non-clickable) line to the report.
void Line(ResourceStateReport& r, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    r.lines.emplace_back(buf);
    r.textureByLine.emplace_back();
    r.shaderByLine.emplace_back();
    r.framebufferByLine.emplace_back();
}

// Appends a texture line, tagging it so the viewer can look up which
// texture (and its dimensions/format) a double-click on this line refers to.
void TextureLine(ResourceStateReport& r, GLuint realId, GLint w, GLint h, GLenum internalFormat, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    r.lines.emplace_back(buf);
    r.textureByLine.push_back(TextureLineInfo{realId, w, h, internalFormat});
    r.shaderByLine.emplace_back();
    r.framebufferByLine.emplace_back();
}

// Appends a shader line, tagging it so the viewer can look up which
// shader's source a double-click on this line should open.
void ShaderLine(ResourceStateReport& r, GLuint realId, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    r.lines.emplace_back(buf);
    r.textureByLine.emplace_back();
    r.shaderByLine.push_back(ShaderLineInfo{realId});
    r.framebufferByLine.emplace_back();
}

void FramebufferLine(ResourceStateReport& r, GLuint realId, uint32_t capturedId, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    r.lines.emplace_back(buf);
    r.textureByLine.emplace_back();
    r.shaderByLine.emplace_back();
    r.framebufferByLine.push_back(FramebufferLineInfo{realId, capturedId});
}

std::string AttachmentName(GLint objType, GLint objName) {
    char buf[64];
    if (objType == GL_NONE) return "none";
    const char* kind = objType == GL_RENDERBUFFER ? "renderbuffer" : "texture";
    snprintf(buf, sizeof(buf), "%s %d", kind, objName);
    return buf;
}

} // namespace

ResourceStateReport RenderResourcesAndState(const IdRemapper& remap) {
    ResourceStateReport r;
    if (!g_inspect.glGetIntegerv) {
        Line(r, "(inspector functions unavailable)");
        return r;
    }

    // ---- current pipeline state ----
    Line(r, "== Current state ==");
    Line(r, "GL_ARRAY_BUFFER_BINDING = %d", GetInt(GL_ARRAY_BUFFER_BINDING));
    Line(r, "GL_ELEMENT_ARRAY_BUFFER_BINDING = %d", GetInt(GL_ELEMENT_ARRAY_BUFFER_BINDING));
    Line(r, "GL_VERTEX_ARRAY_BINDING = %d", GetInt(GL_VERTEX_ARRAY_BINDING));
    Line(r, "GL_CURRENT_PROGRAM = %d", GetInt(GL_CURRENT_PROGRAM));
    {
        GLint boundFbo = GetInt(GL_FRAMEBUFFER_BINDING);
        uint32_t capturedFbo = 0;
        for (auto& [capturedId, realId] : remap.All("framebuffer")) {
            if (static_cast<GLint>(realId) == boundFbo) {
                capturedFbo = capturedId;
                break;
            }
        }
        if (boundFbo == 0) {
            Line(r, "GL_FRAMEBUFFER_BINDING = 0 (default framebuffer)");
        } else if (capturedFbo != 0) {
            Line(r, "GL_FRAMEBUFFER_BINDING = %d (captured id %u)", boundFbo, capturedFbo);
        } else {
            Line(r, "GL_FRAMEBUFFER_BINDING = %d (captured id unknown)", boundFbo);
        }
    }
    Line(r, "GL_ACTIVE_TEXTURE = %s, GL_TEXTURE_BINDING_2D = %d", EnumStr(GetInt(GL_ACTIVE_TEXTURE)).c_str(), GetInt(GL_TEXTURE_BINDING_2D));
    {
        GLint vp[4] = {0, 0, 0, 0};
        g_inspect.glGetIntegerv(GL_VIEWPORT, vp);
        Line(r, "GL_VIEWPORT = (%d, %d, %d, %d)", vp[0], vp[1], vp[2], vp[3]);
    }
    if (g_inspect.glGetFloatv) {
        GLfloat cc[4] = {0, 0, 0, 0};
        g_inspect.glGetFloatv(GL_COLOR_CLEAR_VALUE, cc);
        Line(r, "GL_COLOR_CLEAR_VALUE = (%g, %g, %g, %g)", cc[0], cc[1], cc[2], cc[3]);
    }
    if (g_inspect.glIsEnabled) {
        Line(r, "GL_BLEND = %s (src=%s dst=%s)", g_inspect.glIsEnabled(GL_BLEND) ? "on" : "off",
             EnumStr(GetInt(GL_BLEND_SRC)).c_str(), EnumStr(GetInt(GL_BLEND_DST)).c_str());
        Line(r, "GL_DEPTH_TEST = %s (func=%s)", g_inspect.glIsEnabled(GL_DEPTH_TEST) ? "on" : "off", EnumStr(GetInt(GL_DEPTH_FUNC)).c_str());
        Line(r, "GL_CULL_FACE = %s", g_inspect.glIsEnabled(GL_CULL_FACE) ? "on" : "off");
    }
    Line(r, "");

    // ---- buffers (vertex/index -- both are just GL buffer objects) ----
    Line(r, "== Buffers (%zu) ==", remap.All("buffer").size());
    if (g_real.glBindBuffer && g_inspect.glGetBufferParameteriv) {
        GLint prevArray = GetInt(GL_ARRAY_BUFFER_BINDING);
        for (auto& [capturedId, realId] : remap.All("buffer")) {
            g_real.glBindBuffer(GL_ARRAY_BUFFER, realId);
            GLint size = 0, usage = 0;
            g_inspect.glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
            g_inspect.glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_USAGE, &usage);
            Line(r, "  buffer %u (captured id %u): size=%d bytes, usage=%s", realId, capturedId, size, EnumStr(usage).c_str());
        }
        g_real.glBindBuffer(GL_ARRAY_BUFFER, prevArray);
    }
    Line(r, "");

    // ---- textures (double-click a line to view its pixels) ----
    Line(r, "== Textures (%zu) -- double-click to view ==", remap.All("texture").size());
    if (g_real.glBindTexture && g_real.glActiveTexture && g_inspect.glGetTexLevelParameteriv) {
        GLint prevActive = GetInt(GL_ACTIVE_TEXTURE);
        g_real.glActiveTexture(GL_TEXTURE0);
        GLint prevTex = GetInt(GL_TEXTURE_BINDING_2D);
        for (auto& [capturedId, realId] : remap.All("texture")) {
            g_real.glBindTexture(GL_TEXTURE_2D, realId);
            GLint w = 0, h = 0, ifmt = 0;
            g_inspect.glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
            g_inspect.glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
            g_inspect.glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &ifmt);
            TextureLine(r, realId, w, h, static_cast<GLenum>(ifmt),
                        "  texture %u (captured id %u): %dx%d, internalformat=%s", realId, capturedId, w, h, EnumStr(ifmt).c_str());
        }
        g_real.glBindTexture(GL_TEXTURE_2D, prevTex);
        g_real.glActiveTexture(static_cast<GLenum>(prevActive));
    }
    Line(r, "");

    // ---- framebuffers ----
    Line(r, "== Framebuffers (%zu) ==", remap.All("framebuffer").size());
    if (g_real.glBindFramebuffer && g_inspect.glGetFramebufferAttachmentParameteriv) {
        GLint prevFbo = GetInt(GL_FRAMEBUFFER_BINDING);
        for (auto& [capturedId, realId] : remap.All("framebuffer")) {
            g_real.glBindFramebuffer(GL_FRAMEBUFFER, realId);
            FramebufferLine(r, realId, capturedId, "  framebuffer %u (captured id %u):", realId, capturedId);
            struct { GLenum point; const char* name; } kAttachments[] = {
                {GL_COLOR_ATTACHMENT0, "COLOR_ATTACHMENT0"},
                {GL_DEPTH_ATTACHMENT, "DEPTH_ATTACHMENT"},
                {GL_STENCIL_ATTACHMENT, "STENCIL_ATTACHMENT"},
            };
            for (auto& a : kAttachments) {
                GLint objType = GL_NONE, objName = 0;
                g_inspect.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, a.point, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &objType);
                g_inspect.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, a.point, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &objName);
                if (objType != GL_NONE) Line(r, "    %s -> %s", a.name, AttachmentName(objType, objName).c_str());
            }
        }
        g_real.glBindFramebuffer(GL_FRAMEBUFFER, prevFbo);
    }
    Line(r, "");

    // ---- renderbuffers ----
    Line(r, "== Renderbuffers (%zu) ==", remap.All("renderbuffer").size());
    if (g_real.glBindRenderbuffer && g_inspect.glGetRenderbufferParameteriv) {
        GLint prevRb = GetInt(GL_RENDERBUFFER_BINDING);
        for (auto& [capturedId, realId] : remap.All("renderbuffer")) {
            g_real.glBindRenderbuffer(GL_RENDERBUFFER, realId);
            GLint w = 0, h = 0, ifmt = 0;
            g_inspect.glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &w);
            g_inspect.glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &h);
            g_inspect.glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &ifmt);
            Line(r, "  renderbuffer %u (captured id %u): %dx%d, internalformat=%s", realId, capturedId, w, h, EnumStr(ifmt).c_str());
        }
        g_real.glBindRenderbuffer(GL_RENDERBUFFER, prevRb);
    }
    Line(r, "");

    // ---- vertex array objects (existence only -- no per-attribute dump) ----
    Line(r, "== Vertex array objects (%zu) ==", remap.All("vertexarray").size());
    for (auto& [capturedId, realId] : remap.All("vertexarray")) {
        Line(r, "  vertex array %u (captured id %u)", realId, capturedId);
    }
    Line(r, "");

    // ---- programs / shaders ----
    Line(r, "== Programs (%zu) ==", remap.All("program").size());
    if (g_inspect.glGetProgramiv) {
        for (auto& [capturedId, realId] : remap.All("program")) {
            GLint linked = 0, attached = 0;
            g_inspect.glGetProgramiv(realId, GL_LINK_STATUS, &linked);
            g_inspect.glGetProgramiv(realId, GL_ATTACHED_SHADERS, &attached);
            Line(r, "  program %u (captured id %u): linked=%d, attached shaders=%d", realId, capturedId, linked, attached);
        }
    }
    Line(r, "== Shaders (%zu) -- double-click to view source ==", remap.All("shader").size());
    if (g_inspect.glGetShaderiv) {
        for (auto& [capturedId, realId] : remap.All("shader")) {
            GLint type = 0, compiled = 0;
            g_inspect.glGetShaderiv(realId, GL_SHADER_TYPE, &type);
            g_inspect.glGetShaderiv(realId, GL_COMPILE_STATUS, &compiled);
            ShaderLine(r, realId, "  shader %u (captured id %u): type=%s, compiled=%d", realId, capturedId,
                       type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT/OTHER", compiled);
        }
    }

    return r;
}

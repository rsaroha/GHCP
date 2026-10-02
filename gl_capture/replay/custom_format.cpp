// Hand-written call-list formatters for functions with pointer/array args
// -- mirrors the exact byte layout interceptor/custom_wrappers.cpp wrote,
// but builds a display string instead of replaying the call. Data blobs
// (buffer contents, pixels, vertex arrays) are summarized by length rather
// than dumped in full.
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "byte_cursor.h"
#include "gl_enum_names.h"
#include "gl_format_calls.h"
#include "gl_types_min.h"

namespace {

// Symbolic name for a GLenum value where we have one, else "0x<hex>".
std::string EnumStr(GLenum v) {
    if (const char* nm = LookupEnumName(v)) return nm;
    char buf[16];
    snprintf(buf, sizeof(buf), "0x%X", v);
    return buf;
}

void Append(std::string& s, const char* fmt, ...) {
    char buf[512];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    s += buf;
}

std::string ReadIdArrayStr(ByteCursor& cur) {
    GLsizei n = cur.Read<GLsizei>();
    std::string s;
    Append(s, "n=%d, ids=[", n);
    for (GLsizei i = 0; i < n; ++i) {
        GLuint id = cur.Read<GLuint>();
        Append(s, i ? ", %u" : "%u", id);
    }
    s += "]";
    return s;
}

std::string ReadCStringStr(ByteCursor& cur) {
    uint32_t len = cur.Read<uint32_t>();
    const uint8_t* bytes = cur.ReadBytes(len);
    return std::string(reinterpret_cast<const char*>(bytes), len);
}

std::string EscapeMessage(const uint8_t* bytes, size_t len) {
    std::string out;
    out.reserve(len);
    static constexpr char kHex[] = "0123456789ABCDEF";
    for (size_t i = 0; i < len; ++i) {
        const uint8_t c = bytes[i];
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c >= 0x20 && c <= 0x7E) {
                    out.push_back(static_cast<char>(c));
                } else {
                    out += "\\x";
                    out.push_back(kHex[c >> 4]);
                    out.push_back(kHex[c & 0x0F]);
                }

                break;
        }
    }
    return out;
}

std::string FormatFixedPointer(const char* name, const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    const uint32_t byteLen = cur.Read<uint32_t>();
    const uint8_t* bytes = nullptr;
    if (byteLen <= cur.remaining) bytes = cur.ReadBytes(byteLen);
    uint64_t pointerValue = 0;
    if (cur.remaining >= sizeof(uint64_t)) pointerValue = cur.Read<uint64_t>();

    std::string out = name;
    Append(out, "(ptr=0x%llX, data=%s, bytes=%u)",
           static_cast<unsigned long long>(pointerValue), byteLen ? "present" : "null", byteLen);

    if (!bytes || byteLen == 0) return out;

    const size_t previewBytes = byteLen < 24 ? byteLen : 24;
    out += ", raw=[";
    for (size_t i = 0; i < previewBytes; ++i) {
        Append(out, i ? " %02X" : "%02X", bytes[i]);
    }
    if (previewBytes < byteLen) out += " ...";
    out += "]";
    return out;
}

template <typename T>
void AppendNumeric(std::string& out, T value) {
    if constexpr (std::is_same_v<T, GLboolean>) {
        out += value ? "GL_TRUE" : "GL_FALSE";
    } else if constexpr (std::is_floating_point_v<T>) {
        Append(out, "%g", static_cast<double>(value));
    } else if constexpr (std::is_signed_v<T>) {
        Append(out, "%lld", static_cast<long long>(value));
    } else {
        Append(out, "%llu", static_cast<unsigned long long>(value));
    }
}

template <typename T>
std::string FormatTypedFixedPointer(const char* name, const uint8_t* args, size_t len, size_t expectedCount) {
    ByteCursor cur{args, len};
    if (cur.remaining < sizeof(uint32_t)) return std::string(name) + "(malformed)";
    const uint32_t byteLen = cur.Read<uint32_t>();
    const uint8_t* bytes = nullptr;
    if (byteLen <= cur.remaining) bytes = cur.ReadBytes(byteLen);
    uint64_t pointerValue = 0;
    if (cur.remaining >= sizeof(uint64_t)) pointerValue = cur.Read<uint64_t>();

    std::string out = name;
    Append(out, "(ptr=0x%llX, data=%s, bytes=%u",
           static_cast<unsigned long long>(pointerValue), byteLen ? "present" : "null", byteLen);
    if (!bytes || byteLen == 0) {
        out += ")";
        return out;
    }

    const size_t actualCount = byteLen / sizeof(T);
    const size_t previewCount = actualCount < 8 ? actualCount : 8;
    out += ", values=[";
    for (size_t i = 0; i < previewCount; ++i) {
        T value{};
        std::memcpy(&value, bytes + i * sizeof(T), sizeof(T));
        if (i) out += ", ";
        AppendNumeric(out, value);
    }
    if (previewCount < actualCount) out += ", ...";
    out += "]";
    if (actualCount != expectedCount) Append(out, ", expected=%u", static_cast<unsigned>(expectedCount));
    out += ")";
    return out;
}

template <typename T>
void AppendTypedPointerFromCursor(std::string& out, ByteCursor& cur, size_t expectedCount) {
    if (cur.remaining < sizeof(uint32_t)) {
        out += ", data=malformed";
        return;
    }
    const uint32_t byteLen = cur.Read<uint32_t>();
    const uint8_t* bytes = nullptr;
    if (byteLen <= cur.remaining) bytes = cur.ReadBytes(byteLen);
    uint64_t pointerValue = 0;
    if (cur.remaining >= sizeof(uint64_t)) pointerValue = cur.Read<uint64_t>();

    Append(out, ", ptr=0x%llX, data=%s, bytes=%u",
           static_cast<unsigned long long>(pointerValue), byteLen ? "present" : "null", byteLen);

    if (!bytes || byteLen == 0) return;

    const size_t actualCount = byteLen / sizeof(T);
    const size_t previewCount = actualCount < 8 ? actualCount : 8;
    out += ", values=[";
    for (size_t i = 0; i < previewCount; ++i) {
        T value{};
        std::memcpy(&value, bytes + i * sizeof(T), sizeof(T));
        if (i) out += ", ";
        AppendNumeric(out, value);
    }
    if (previewCount < actualCount) out += ", ...";
    out += "]";
    if (actualCount != expectedCount) Append(out, ", expected=%u", static_cast<unsigned>(expectedCount));
}

template <typename T>
std::string FormatQueryPointer(const char* name, const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    if (cur.remaining < sizeof(GLenum) + sizeof(uint32_t)) return std::string(name) + "(malformed)";
    const GLenum pname = cur.Read<GLenum>();
    const uint32_t count = cur.Read<uint32_t>();
    const size_t byteLen = static_cast<size_t>(count) * sizeof(T);
    const uint8_t* bytes = nullptr;
    if (byteLen <= cur.remaining) bytes = cur.ReadBytes(byteLen);
    uint64_t pointerValue = 0;
    if (cur.remaining >= sizeof(uint64_t)) pointerValue = cur.Read<uint64_t>();

    std::string out = name;
    Append(out, "(pname=%s, ptr=0x%llX, count=%u",
           EnumStr(pname).c_str(), static_cast<unsigned long long>(pointerValue), count);

    if (bytes && count) {
        const size_t previewCount = count < 8 ? count : 8;
        out += ", values=[";
        for (size_t i = 0; i < previewCount; ++i) {
            T value{};
            std::memcpy(&value, bytes + i * sizeof(T), sizeof(T));
            if (i) out += ", ";
            AppendNumeric(out, value);
        }
        if (previewCount < count) out += ", ...";
        out += "]";
    }
    out += ")";
    return out;
}

std::string ClientArraySlotName(uint32_t slot) {
    switch (slot) {
        case 0: return "Vertex";
        case 1: return "Color";
        case 2: return "TexCoord";
        case 3: return "Normal";
        case 4: return "Generic";
        default: return "?";
    }
}

std::string FormatClientArrays(ByteCursor& cur) {
    uint32_t n = cur.Read<uint32_t>();
    std::string s;
    Append(s, ", clientArrays=%u", n);
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t slot = cur.Read<uint32_t>();
        uint32_t attribIndex = cur.Read<uint32_t>();
        GLint size = cur.Read<GLint>();
        GLenum type = cur.Read<GLenum>();
        GLsizei stride = cur.Read<GLsizei>();
        uint32_t byteLen = cur.Read<uint32_t>();
        cur.ReadBytes(byteLen);
        Append(s, " [%s idx=%u size=%d type=%s stride=%d bytes=%u]",
               ClientArraySlotName(slot).c_str(), attribIndex, size, EnumStr(type).c_str(), stride, byteLen);
    }
    return s;
}

} // namespace

std::string Format_glGenBuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glGenBuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDeleteBuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glDeleteBuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glBindBuffer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLuint buffer = cur.Read<GLuint>();
    std::string s;
    Append(s, "glBindBuffer(target=%s, buffer=%u)", EnumStr(target).c_str(), buffer);
    return s;
}

std::string Format_glColor4dv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLdouble>("glColor4dv", a, n, 4); }
std::string Format_glColor3ubv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLubyte>("glColor3ubv", a, n, 3); }
std::string Format_glLoadMatrixf(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLfloat>("glLoadMatrixf", a, n, 16); }
std::string Format_glGetBooleanv(const uint8_t* a, size_t n) { return FormatQueryPointer<GLboolean>("glGetBooleanv", a, n); }
std::string Format_glGetFloatv(const uint8_t* a, size_t n) { return FormatQueryPointer<GLfloat>("glGetFloatv", a, n); }
std::string Format_glGetIntegerv(const uint8_t* a, size_t n) { return FormatQueryPointer<GLint>("glGetIntegerv", a, n); }
std::string Format_glLoadMatrixd(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLdouble>("glLoadMatrixd", a, n, 16); }
std::string Format_glColor4usv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLushort>("glColor4usv", a, n, 4); }
std::string Format_glVertex4sv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLshort>("glVertex4sv", a, n, 4); }
std::string Format_glLightfv(const uint8_t* a, size_t n) {
    ByteCursor cur{a, n};
    GLenum light = cur.Read<GLenum>();
    GLenum pname = cur.Read<GLenum>();
    const size_t expected = pname == 0x1204 ? 3 : (pname >= 0x1200 && pname <= 0x1203 ? 4 : 1);
    std::string s;
    Append(s, "glLightfv(light=%s, pname=%s", EnumStr(light).c_str(), EnumStr(pname).c_str());
    AppendTypedPointerFromCursor<GLfloat>(s, cur, expected);
    s += ")";
    return s;
}
std::string Format_glLightModelfv(const uint8_t* a, size_t n) {
    ByteCursor cur{a, n};
    GLenum pname = cur.Read<GLenum>();
    const size_t expected = pname == 0x0B53 ? 4 : 1;
    std::string s;
    Append(s, "glLightModelfv(pname=%s", EnumStr(pname).c_str());
    AppendTypedPointerFromCursor<GLfloat>(s, cur, expected);
    s += ")";
    return s;
}
std::string Format_glInterleavedArrays(const uint8_t* a, size_t n) {
    ByteCursor cur{a, n};
    GLenum format = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    uint8_t present = cur.Read<uint8_t>();
    std::string s;
    Append(s, "glInterleavedArrays(format=%s, stride=%d, ptr=%s)",
           EnumStr(format).c_str(), stride, present ? "present" : "null");
    return s;
}
std::string Format_glColor4fv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLfloat>("glColor4fv", a, n, 4); }
std::string Format_glNormal3dv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLdouble>("glNormal3dv", a, n, 3); }
std::string Format_glNormal3fv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLfloat>("glNormal3fv", a, n, 3); }
std::string Format_glTexCoord2dv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLdouble>("glTexCoord2dv", a, n, 2); }
std::string Format_glTexCoord2fv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLfloat>("glTexCoord2fv", a, n, 2); }
std::string Format_glTexCoord2iv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLint>("glTexCoord2iv", a, n, 2); }
std::string Format_glVertex3dv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLdouble>("glVertex3dv", a, n, 3); }
std::string Format_glVertex3fv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLfloat>("glVertex3fv", a, n, 3); }
std::string Format_glVertex3iv(const uint8_t* a, size_t n) { return FormatTypedFixedPointer<GLint>("glVertex3iv", a, n, 3); }

std::string Format_glBufferData(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    GLenum usage = cur.Read<GLenum>();
    std::string s;
    Append(s, "glBufferData(target=%s, size=%lld, data=%u bytes, usage=%s)",
           EnumStr(target).c_str(), (long long)size, dataLen, EnumStr(usage).c_str());
    return s;
}

std::string Format_glBufferSubData(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLintptr offset = cur.Read<GLintptr>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    std::string s;
    Append(s, "glBufferSubData(target=%s, offset=%lld, size=%lld, data=%u bytes)",
           EnumStr(target).c_str(), (long long)offset, (long long)size, dataLen);
    return s;
}

std::string Format_glClearBufferfv(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum buffer = cur.Read<GLenum>();
    GLint drawbuffer = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    cur.ReadBytes(sizeof(GLfloat) * count);
    std::string s;
    Append(s, "glClearBufferfv(buffer=%s, drawbuffer=%d, values=%d)", EnumStr(buffer).c_str(), drawbuffer, count);
    return s;
}

std::string Format_glCreateBuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glCreateBuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glCreateFramebuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glCreateFramebuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glCreateRenderbuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glCreateRenderbuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glCreateTextures(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    std::string s = "glCreateTextures(target=" + EnumStr(target) + ", ";
    s += ReadIdArrayStr(cur) + ")";
    return s;
}

std::string Format_glCreateVertexArrays(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glCreateVertexArrays(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDebugMessageInsert(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum source = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    GLuint id = cur.Read<GLuint>();
    GLenum severity = cur.Read<GLenum>();
    uint32_t messageLen = cur.Read<uint32_t>();
    const uint8_t* message = cur.ReadBytes(messageLen);
    const std::string escapedMessage = EscapeMessage(message, messageLen);
    std::string s;
    Append(s, "glDebugMessageInsert(source=%s, type=%s, id=%u, severity=%s, message=\"%s\")",
           EnumStr(source).c_str(), EnumStr(type).c_str(), id, EnumStr(severity).c_str(),
           escapedMessage.c_str());
    return s;
}

std::string Format_glGetProgramInfoLog(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint program = cur.Read<GLuint>();
    GLsizei bufSize = cur.Read<GLsizei>();
    GLsizei capturedLength = cur.Read<GLsizei>();
    cur.ReadBytes(static_cast<size_t>(capturedLength));
    std::string s;
    Append(s, "glGetProgramInfoLog(program=%u, bufSize=%d, log=%d bytes)", program, bufSize, capturedLength);
    return s;
}

std::string Format_glGetShaderInfoLog(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint shader = cur.Read<GLuint>();
    GLsizei bufSize = cur.Read<GLsizei>();
    GLsizei capturedLength = cur.Read<GLsizei>();
    cur.ReadBytes(static_cast<size_t>(capturedLength));
    std::string s;
    Append(s, "glGetShaderInfoLog(shader=%u, bufSize=%d, log=%d bytes)", shader, bufSize, capturedLength);
    return s;
}

std::string Format_glNamedBufferStorage(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint buffer = cur.Read<GLuint>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    GLbitfield flags = cur.Read<GLbitfield>();
    std::string s;
    Append(s, "glNamedBufferStorage(buffer=%u, size=%lld, data=%u bytes, flags=0x%X)",
           buffer, (long long)size, dataLen, flags);
    return s;
}

std::string Format_glNamedBufferSubData(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint buffer = cur.Read<GLuint>();
    GLintptr offset = cur.Read<GLintptr>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    std::string s;
    Append(s, "glNamedBufferSubData(buffer=%u, offset=%lld, size=%lld, data=%u bytes)",
           buffer, (long long)offset, (long long)size, dataLen);
    return s;
}

std::string Format_glNamedFramebufferDrawBuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint framebuffer = cur.Read<GLuint>();
    GLsizei n = cur.Read<GLsizei>();
    cur.ReadBytes(sizeof(GLenum) * static_cast<size_t>(n));
    std::string s;
    Append(s, "glNamedFramebufferDrawBuffers(framebuffer=%u, buffers=%d)", framebuffer, n);
    return s;
}

std::string Format_glTextureSubImage2D(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint texture = cur.Read<GLuint>();
    GLint level = cur.Read<GLint>();
    GLint xoffset = cur.Read<GLint>();
    GLint yoffset = cur.Read<GLint>();
    GLsizei width = cur.Read<GLsizei>();
    GLsizei height = cur.Read<GLsizei>();
    GLenum format = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    std::string s;
    Append(s, "glTextureSubImage2D(texture=%u, level=%d, offset=(%d,%d), size=%dx%d, format=%s, type=%s, data=%u bytes)",
           texture, level, xoffset, yoffset, width, height, EnumStr(format).c_str(), EnumStr(type).c_str(), dataLen);
    return s;
}

std::string Format_glTextureSubImage3D(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint texture = cur.Read<GLuint>();
    GLint level = cur.Read<GLint>();
    GLint xoffset = cur.Read<GLint>();
    GLint yoffset = cur.Read<GLint>();
    GLint zoffset = cur.Read<GLint>();
    GLsizei width = cur.Read<GLsizei>();
    GLsizei height = cur.Read<GLsizei>();
    GLsizei depth = cur.Read<GLsizei>();
    GLenum format = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    uint32_t dataLen = cur.Read<uint32_t>();
    cur.ReadBytes(dataLen);
    std::string s;
    Append(s, "glTextureSubImage3D(texture=%u, level=%d, offset=(%d,%d,%d), size=%dx%dx%d, format=%s, type=%s, data=%u bytes)",
           texture, level, xoffset, yoffset, zoffset, width, height, depth,
           EnumStr(format).c_str(), EnumStr(type).c_str(), dataLen);
    return s;
}

std::string Format_glGenVertexArrays(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glGenVertexArrays(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDeleteVertexArrays(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glDeleteVertexArrays(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glVertexAttribPointer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint index = cur.Read<GLuint>();
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLboolean normalized = cur.Read<GLboolean>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    std::string s;
    Append(s, "glVertexAttribPointer(index=%u, size=%d, type=%s, normalized=%d, stride=%d, %s=%llu)",
           index, size, EnumStr(type).c_str(), normalized, stride, clientBacked ? "clientBytes" : "offset", (unsigned long long)offset);
    return s;
}

std::string Format_glVertexPointer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    std::string s;
    Append(s, "glVertexPointer(size=%d, type=%s, stride=%d, %s=%llu)",
           size, EnumStr(type).c_str(), stride, clientBacked ? "client" : "offset", (unsigned long long)offset);
    return s;
}

std::string Format_glColorPointer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    std::string s;
    Append(s, "glColorPointer(size=%d, type=%s, stride=%d, %s=%llu)",
           size, EnumStr(type).c_str(), stride, clientBacked ? "client" : "offset", (unsigned long long)offset);
    return s;
}

std::string Format_glTexCoordPointer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    std::string s;
    Append(s, "glTexCoordPointer(size=%d, type=%s, stride=%d, %s=%llu)",
           size, EnumStr(type).c_str(), stride, clientBacked ? "client" : "offset", (unsigned long long)offset);
    return s;
}

std::string Format_glNormalPointer(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    std::string s;
    Append(s, "glNormalPointer(type=%s, stride=%d, %s=%llu)",
           EnumStr(type).c_str(), stride, clientBacked ? "client" : "offset", (unsigned long long)offset);
    return s;
}

std::string Format_glGenTextures(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glGenTextures(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDeleteTextures(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glDeleteTextures(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glTexImage2D(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLint level = cur.Read<GLint>();
    GLint internalformat = cur.Read<GLint>();
    GLsizei width = cur.Read<GLsizei>();
    GLsizei height = cur.Read<GLsizei>();
    GLint border = cur.Read<GLint>();
    GLenum format = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    uint32_t pixLen = cur.Read<uint32_t>();
    cur.ReadBytes(pixLen);
    std::string s;
    Append(s, "glTexImage2D(target=%s, level=%d, internalformat=%d, width=%d, height=%d, border=%d, format=%s, type=%s, pixels=%u bytes)",
           EnumStr(target).c_str(), level, internalformat, width, height, border, EnumStr(format).c_str(), EnumStr(type).c_str(), pixLen);
    return s;
}

std::string Format_glTexSubImage2D(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLint level = cur.Read<GLint>();
    GLint xoffset = cur.Read<GLint>();
    GLint yoffset = cur.Read<GLint>();
    GLsizei width = cur.Read<GLsizei>();
    GLsizei height = cur.Read<GLsizei>();
    GLenum format = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    uint32_t pixLen = cur.Read<uint32_t>();
    cur.ReadBytes(pixLen);
    std::string s;
    Append(s, "glTexSubImage2D(target=%s, level=%d, xoffset=%d, yoffset=%d, width=%d, height=%d, format=%s, type=%s, pixels=%u bytes)",
           EnumStr(target).c_str(), level, xoffset, yoffset, width, height, EnumStr(format).c_str(), EnumStr(type).c_str(), pixLen);
    return s;
}

std::string Format_glShaderSource(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint shader = cur.Read<GLuint>();
    GLsizei count = cur.Read<GLsizei>();
    std::string s;
    Append(s, "glShaderSource(shader=%u, count=%d, src=", shader, count);
    for (GLsizei i = 0; i < count; ++i) {
        uint32_t l = cur.Read<uint32_t>();
        const uint8_t* bytes = cur.ReadBytes(l);
        if (i) s += "|";
        std::string piece(reinterpret_cast<const char*>(bytes), l);
        if (piece.size() > 60) piece = piece.substr(0, 60) + "...";
        for (char& c : piece) if (c == '\n' || c == '\r') c = ' ';
        s += "\"" + piece + "\"";
    }
    s += ")";
    return s;
}

std::string Format_glBindAttribLocation(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint program = cur.Read<GLuint>();
    GLuint index = cur.Read<GLuint>();
    std::string name = ReadCStringStr(cur);
    std::string s;
    Append(s, "glBindAttribLocation(program=%u, index=%u, name=\"%s\")", program, index, name.c_str());
    return s;
}

std::string Format_glGetUniformLocation(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint program = cur.Read<GLuint>();
    std::string name = ReadCStringStr(cur);
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "glGetUniformLocation(program=%u, name=\"%s\") -> %d", program, name.c_str(), result);
    return s;
}

std::string Format_glGetAttribLocation(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLuint program = cur.Read<GLuint>();
    std::string name = ReadCStringStr(cur);
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "glGetAttribLocation(program=%u, name=\"%s\") -> %d", program, name.c_str(), result);
    return s;
}

std::string Format_glUniformMatrix4fv(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLint location = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLboolean transpose = cur.Read<GLboolean>();
    cur.ReadBytes(sizeof(GLfloat) * 16 * count);
    std::string s;
    Append(s, "glUniformMatrix4fv(location=%d, count=%d, transpose=%d)", location, count, transpose);
    return s;
}

std::string Format_glUniformMatrix3fv(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLint location = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLboolean transpose = cur.Read<GLboolean>();
    cur.ReadBytes(sizeof(GLfloat) * 9 * count);
    std::string s;
    Append(s, "glUniformMatrix3fv(location=%d, count=%d, transpose=%d)", location, count, transpose);
    return s;
}

std::string Format_glGenFramebuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glGenFramebuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDeleteFramebuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glDeleteFramebuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glGenRenderbuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glGenRenderbuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDeleteRenderbuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    return "glDeleteRenderbuffers(" + ReadIdArrayStr(cur) + ")";
}

std::string Format_glDrawArrays(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLint first = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    std::string s;
    Append(s, "glDrawArrays(mode=%s, first=%d, count=%d", EnumStr(mode).c_str(), first, count);
    s += FormatClientArrays(cur);
    s += ")";
    return s;
}

std::string Format_glDrawArraysInstanced(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLint first = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLsizei instancecount = cur.Read<GLsizei>();
    std::string s;
    Append(s, "glDrawArraysInstanced(mode=%s, first=%d, count=%d, instancecount=%d", EnumStr(mode).c_str(), first, count, instancecount);
    s += FormatClientArrays(cur);
    s += ")";
    return s;
}

std::string Format_glDrawElements(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLsizei count = cur.Read<GLsizei>();
    GLenum type = cur.Read<GLenum>();
    bool indicesClient = cur.Read<bool>();
    std::string s;
    Append(s, "glDrawElements(mode=%s, count=%d, type=%s", EnumStr(mode).c_str(), count, EnumStr(type).c_str());
    if (indicesClient) {
        uint32_t idxLen = cur.Read<uint32_t>();
        cur.ReadBytes(idxLen);
        Append(s, ", indices=%u client bytes", idxLen);
        s += FormatClientArrays(cur);
    } else {
        uint64_t offset = cur.Read<uint64_t>();
        cur.Read<uint32_t>();
        Append(s, ", indices offset=%llu", (unsigned long long)offset);
    }
    s += ")";
    return s;
}

std::string Format_glDrawElementsInstanced(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLsizei count = cur.Read<GLsizei>();
    GLenum type = cur.Read<GLenum>();
    GLsizei instancecount = cur.Read<GLsizei>();
    bool indicesClient = cur.Read<bool>();
    std::string s;
    Append(s, "glDrawElementsInstanced(mode=%s, count=%d, type=%s, instancecount=%d", EnumStr(mode).c_str(), count, EnumStr(type).c_str(), instancecount);
    if (indicesClient) {
        uint32_t idxLen = cur.Read<uint32_t>();
        cur.ReadBytes(idxLen);
        Append(s, ", indices=%u client bytes", idxLen);
        s += FormatClientArrays(cur);
    } else {
        uint64_t offset = cur.Read<uint64_t>();
        cur.Read<uint32_t>();
        Append(s, ", indices offset=%llu", (unsigned long long)offset);
    }
    s += ")";
    return s;
}

std::string Format_glGetString(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    GLenum name = cur.Read<GLenum>();
    std::string str = ReadCStringStr(cur);
    std::string s;
    Append(s, "glGetString(name=%s) -> \"%s\"", EnumStr(name).c_str(), str.c_str());
    return s;
}

std::string Format_wglCreateContext(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hdc = cur.Read<uint64_t>();
    uint64_t result = cur.Read<uint64_t>();
    std::string s;
    Append(s, "wglCreateContext(hdc=0x%llX) -> 0x%llX",
           static_cast<unsigned long long>(hdc), static_cast<unsigned long long>(result));
    return s;
}

std::string Format_wglDeleteContext(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hglrc = cur.Read<uint64_t>();
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "wglDeleteContext(hglrc=0x%llX) -> %d",
           static_cast<unsigned long long>(hglrc), result);
    return s;
}

std::string Format_wglMakeCurrent(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hdc = cur.Read<uint64_t>();
    uint64_t hglrc = cur.Read<uint64_t>();
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "wglMakeCurrent(hdc=0x%llX, hglrc=0x%llX) -> %d",
           static_cast<unsigned long long>(hdc), static_cast<unsigned long long>(hglrc), result);
    return s;
}

std::string Format_wglShareLists(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hglrc1 = cur.Read<uint64_t>();
    uint64_t hglrc2 = cur.Read<uint64_t>();
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "wglShareLists(hglrc1=0x%llX, hglrc2=0x%llX) -> %d",
           static_cast<unsigned long long>(hglrc1), static_cast<unsigned long long>(hglrc2), result);
    return s;
}

std::string Format_wglSwapLayerBuffers(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hdc = cur.Read<uint64_t>();
    GLbitfield planes = cur.Read<GLbitfield>();
    GLint result = cur.Read<GLint>();
    std::string s;
    Append(s, "wglSwapLayerBuffers(hdc=0x%llX, planes=0x%X) -> %d",
           static_cast<unsigned long long>(hdc), planes, result);
    return s;
}

std::string Format_wglCreateContextAttribsARB(const uint8_t* args, size_t len) {
    ByteCursor cur{args, len};
    uint64_t hdc = cur.Read<uint64_t>();
    uint64_t shareContext = cur.Read<uint64_t>();
    uint32_t count = cur.Read<uint32_t>();
    const GLint* attribs = reinterpret_cast<const GLint*>(cur.ReadBytes(sizeof(GLint) * count));
    uint64_t result = cur.Read<uint64_t>();
    std::string s;
    Append(s, "wglCreateContextAttribsARB(hdc=0x%llX, share=0x%llX, attribs=[",
           static_cast<unsigned long long>(hdc), static_cast<unsigned long long>(shareContext));
    for (uint32_t i = 0; i < count; ++i) {
        Append(s, i ? ", %d" : "%d", attribs[i]);
    }
    Append(s, "]) -> 0x%llX", static_cast<unsigned long long>(result));
    return s;
}

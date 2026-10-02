// Hand-written replay-side counterparts to interceptor/custom_wrappers.cpp.
// Each Replay_glXxx here decodes exactly the byte layout its capture-side
// twin wrote, then re-issues the call against the real driver loaded by
// this replay process, remapping object ids as needed.
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>

#include "byte_cursor.h"
#include "gl_real_table.h"
#include "gl_replay_decode.h"
#include "shader_registry.h"

namespace {

size_t GLTypeSize(GLenum type) {
    switch (type) {
        case 0x1400: return 1;
        case 0x1401: return 1;
        case 0x1402: return 2;
        case 0x1403: return 2;
        case 0x1404: return 4;
        case 0x1405: return 4;
        case 0x1406: return 4;
        case 0x140A: return 8;
        default: return 4;
    }
}

enum class ClientArraySlot : uint32_t { Vertex = 0, Color = 1, TexCoord = 2, Normal = 3, Generic = 4 };

struct DecodedClientArray {
    ClientArraySlot slot;
    uint32_t attribIndex;
    GLint size;
    GLenum type;
    GLsizei stride;
    std::vector<uint8_t> data;
};

std::vector<DecodedClientArray> DecodeClientArrays(ByteCursor& cur) {
    uint32_t n = cur.Read<uint32_t>();
    std::vector<DecodedClientArray> out(n);
    for (uint32_t i = 0; i < n; ++i) {
        out[i].slot = static_cast<ClientArraySlot>(cur.Read<uint32_t>());
        out[i].attribIndex = cur.Read<uint32_t>();
        out[i].size = cur.Read<GLint>();
        out[i].type = cur.Read<GLenum>();
        out[i].stride = cur.Read<GLsizei>();
        uint32_t byteLen = cur.Read<uint32_t>();
        const uint8_t* bytes = cur.ReadBytes(byteLen);
        out[i].data.assign(bytes, bytes + byteLen);
    }

    return out;
}

template <typename T>
const T* ReadFixedPointer(ByteCursor& cur, size_t count, std::vector<T>& storage) {
    if (cur.remaining < sizeof(uint32_t)) return nullptr;
    uint32_t byteLen = cur.Read<uint32_t>();
    if (byteLen == 0) return nullptr;
    if (byteLen > cur.remaining) {
        cur.ReadBytes(cur.remaining);
        return nullptr;
    }
    if (byteLen != sizeof(T) * count) {
        cur.ReadBytes(byteLen);
        return nullptr;
    }
    const uint8_t* bytes = cur.ReadBytes(byteLen);
    storage.resize(count);
    std::memcpy(storage.data(), bytes, byteLen);
    return storage.data();
}

// Binds each decoded client array's replay-owned backing memory as the
// real vertex-array pointer for this draw. Must stay alive until after
// the draw call is issued.
void ApplyClientArrays(std::vector<DecodedClientArray>& arrays) {
    for (auto& a : arrays) {
        const void* ptr = a.data.data();
        switch (a.slot) {
            case ClientArraySlot::Vertex:
                g_real.glVertexPointer(a.size, a.type, a.stride, ptr);
                break;
            case ClientArraySlot::Color:
                g_real.glColorPointer(a.size, a.type, a.stride, ptr);
                break;
            case ClientArraySlot::TexCoord:
                g_real.glTexCoordPointer(a.size, a.type, a.stride, ptr);
                break;
            case ClientArraySlot::Normal:
                g_real.glNormalPointer(a.type, a.stride, ptr);
                break;
            case ClientArraySlot::Generic:
                g_real.glVertexAttribPointer(a.attribIndex, a.size, a.type, 0, a.stride, ptr);
                break;
        }
    }
}

template <typename T>
void ReplayQuery(const uint8_t* args, size_t len, void* output, size_t outputBytes) {
    ByteCursor cur{args, len};
    if (cur.remaining < sizeof(GLenum) + sizeof(uint32_t)) return;
    (void)cur.Read<GLenum>();
    uint32_t count = cur.Read<uint32_t>();
    size_t bytes = std::min<size_t>(outputBytes, static_cast<size_t>(count) * sizeof(T));
    if (bytes <= cur.remaining) std::memcpy(output, cur.ReadBytes(bytes), bytes);
}

} // namespace

extern "C" {

void Replay_glColor4dv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLdouble> v;
    if (const GLdouble* p = ReadFixedPointer(cur, 4, v)) g_real.glColor4dv(p);
}
void Replay_glColor3ubv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLubyte> v;
    if (const GLubyte* p = ReadFixedPointer(cur, 3, v)) g_real.glColor3ubv(p);
}
void Replay_glLoadMatrixf(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLfloat> matrix;
    if (const GLfloat* p = ReadFixedPointer(cur, 16, matrix)) g_real.glLoadMatrixf(p);
}
void Replay_glGetBooleanv(const uint8_t* args, size_t len, IdRemapper&) {
    std::vector<GLboolean> values(16); ReplayQuery<GLboolean>(args, len, values.data(), values.size() * sizeof(GLboolean));
}
void Replay_glGetFloatv(const uint8_t* args, size_t len, IdRemapper&) {
    std::vector<GLfloat> values(16); ReplayQuery<GLfloat>(args, len, values.data(), values.size() * sizeof(GLfloat));
}
void Replay_glGetIntegerv(const uint8_t* args, size_t len, IdRemapper&) {
    std::vector<GLint> values(16); ReplayQuery<GLint>(args, len, values.data(), values.size() * sizeof(GLint));
}
void Replay_glLoadMatrixd(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLdouble> matrix;
    if (const GLdouble* p = ReadFixedPointer(cur, 16, matrix)) g_real.glLoadMatrixd(p);
}
void Replay_glColor4usv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLushort> values;
    if (const GLushort* p = ReadFixedPointer(cur, 4, values)) g_real.glColor4usv(p);
}
void Replay_glVertex4sv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLshort> values;
    if (const GLshort* p = ReadFixedPointer(cur, 4, values)) g_real.glVertex4sv(p);
}
void Replay_glLightfv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum light = cur.Read<GLenum>();
    GLenum pname = cur.Read<GLenum>();
    std::vector<GLfloat> values;
    size_t count = pname == 0x1204 ? 3 : (pname >= 0x1200 && pname <= 0x1203 ? 4 : 1);
    if (const GLfloat* p = ReadFixedPointer(cur, count, values)) g_real.glLightfv(light, pname, p);
}
void Replay_glLightModelfv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum pname = cur.Read<GLenum>();
    std::vector<GLfloat> values;
    size_t count = pname == 0x0B53 ? 4 : 1;
    if (const GLfloat* p = ReadFixedPointer(cur, count, values)) g_real.glLightModelfv(pname, p);
}
void Replay_glInterleavedArrays(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    (void)cur.Read<GLenum>();
    (void)cur.Read<GLsizei>();
    if (cur.remaining) (void)cur.Read<uint8_t>();
}
void Replay_glColor4fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLfloat> v;
    if (const GLfloat* p = ReadFixedPointer(cur, 4, v)) g_real.glColor4fv(p);
}
void Replay_glNormal3dv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLdouble> v;
    if (const GLdouble* p = ReadFixedPointer(cur, 3, v)) g_real.glNormal3dv(p);
}
void Replay_glNormal3fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLfloat> v;
    if (const GLfloat* p = ReadFixedPointer(cur, 3, v)) g_real.glNormal3fv(p);
}
void Replay_glTexCoord2dv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLdouble> v;
    if (const GLdouble* p = ReadFixedPointer(cur, 2, v)) g_real.glTexCoord2dv(p);
}
void Replay_glTexCoord2fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLfloat> v;
    if (const GLfloat* p = ReadFixedPointer(cur, 2, v)) g_real.glTexCoord2fv(p);
}
void Replay_glTexCoord2iv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLint> v;
    if (const GLint* p = ReadFixedPointer(cur, 2, v)) g_real.glTexCoord2iv(p);
}
void Replay_glVertex3dv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLdouble> v;
    if (const GLdouble* p = ReadFixedPointer(cur, 3, v)) g_real.glVertex3dv(p);
}
void Replay_glVertex3fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLfloat> v;
    if (const GLfloat* p = ReadFixedPointer(cur, 3, v)) g_real.glVertex3fv(p);
}
void Replay_glVertex3iv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len}; std::vector<GLint> v;
    if (const GLint* p = ReadFixedPointer(cur, 3, v)) g_real.glVertex3iv(p);
}

void Replay_glClearBufferfv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum buffer = cur.Read<GLenum>();
    GLint drawbuffer = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    const GLfloat* value = reinterpret_cast<const GLfloat*>(cur.ReadBytes(sizeof(GLfloat) * count));
    g_real.glClearBufferfv(buffer, drawbuffer, value);
}

void Replay_glCreateBuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n), real(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    g_real.glCreateBuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("buffer", captured[i], real[i]);
}

void Replay_glCreateFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n), real(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    g_real.glCreateFramebuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("framebuffer", captured[i], real[i]);
}

void Replay_glCreateRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n), real(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    g_real.glCreateRenderbuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("renderbuffer", captured[i], real[i]);
}

void Replay_glCreateTextures(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n), real(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    g_real.glCreateTextures(target, n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("texture", captured[i], real[i]);
}

void Replay_glCreateVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n), real(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    g_real.glCreateVertexArrays(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("vertexarray", captured[i], real[i]);
}

void Replay_glDebugMessageInsert(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum source = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    GLuint id = cur.Read<GLuint>();
    GLenum severity = cur.Read<GLenum>();
    uint32_t messageLen = cur.Read<uint32_t>();
    const GLchar* message = reinterpret_cast<const GLchar*>(cur.ReadBytes(messageLen));
    g_real.glDebugMessageInsert(source, type, id, severity, static_cast<GLsizei>(messageLen), message);
}

void Replay_glGetProgramInfoLog(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint program = remap.Get("program", cur.Read<GLuint>());
    GLsizei bufSize = cur.Read<GLsizei>();
    GLsizei capturedLength = cur.Read<GLsizei>();
    cur.ReadBytes(static_cast<size_t>(capturedLength));
    std::vector<GLchar> output(bufSize > 0 ? static_cast<size_t>(bufSize) : 0);
    g_real.glGetProgramInfoLog(program, bufSize, nullptr, output.data());
}

void Replay_glGetShaderInfoLog(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint shader = remap.Get("shader", cur.Read<GLuint>());
    GLsizei bufSize = cur.Read<GLsizei>();
    GLsizei capturedLength = cur.Read<GLsizei>();
    cur.ReadBytes(static_cast<size_t>(capturedLength));
    std::vector<GLchar> output(bufSize > 0 ? static_cast<size_t>(bufSize) : 0);
    g_real.glGetShaderInfoLog(shader, bufSize, nullptr, output.data());
}

void Replay_glNamedBufferStorage(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint buffer = remap.Get("buffer", cur.Read<GLuint>());
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    const void* data = cur.ReadBytes(dataLen);
    GLbitfield flags = cur.Read<GLbitfield>();
    g_real.glNamedBufferStorage(buffer, size, dataLen ? data : nullptr, flags);
}

void Replay_glNamedBufferSubData(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint buffer = remap.Get("buffer", cur.Read<GLuint>());
    GLintptr offset = cur.Read<GLintptr>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    const void* data = cur.ReadBytes(dataLen);
    g_real.glNamedBufferSubData(buffer, offset, size, dataLen ? data : nullptr);
}

void Replay_glNamedFramebufferDrawBuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint framebuffer = remap.Get("framebuffer", cur.Read<GLuint>());
    GLsizei n = cur.Read<GLsizei>();
    const GLenum* bufs = reinterpret_cast<const GLenum*>(cur.ReadBytes(sizeof(GLenum) * static_cast<size_t>(n)));
    g_real.glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

void Replay_glTextureSubImage2D(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint texture = remap.Get("texture", cur.Read<GLuint>());
    GLint level = cur.Read<GLint>();
    GLint xoffset = cur.Read<GLint>();
    GLint yoffset = cur.Read<GLint>();
    GLsizei width = cur.Read<GLsizei>();
    GLsizei height = cur.Read<GLsizei>();
    GLenum format = cur.Read<GLenum>();
    GLenum type = cur.Read<GLenum>();
    uint32_t dataLen = cur.Read<uint32_t>();
    const void* pixels = cur.ReadBytes(dataLen);
    g_real.glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type,
                               dataLen ? pixels : nullptr);
}

void Replay_glTextureSubImage3D(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint texture = remap.Get("texture", cur.Read<GLuint>());
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
    const void* pixels = cur.ReadBytes(dataLen);
    g_real.glTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth,
                               format, type, dataLen ? pixels : nullptr);
}

void Replay_glGenBuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    std::vector<GLuint> real(n);
    g_real.glGenBuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("buffer", captured[i], real[i]);
}

void Replay_glDeleteBuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    std::vector<GLuint> real(n);
    for (GLsizei i = 0; i < n; ++i) {
        captured[i] = cur.Read<GLuint>();
        real[i] = remap.Get("buffer", captured[i]);
    }
    g_real.glDeleteBuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Unmap("buffer", captured[i]);
}

void Replay_glBindBuffer(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLuint buffer = remap.Get("buffer", cur.Read<GLuint>());
    g_real.glBindBuffer(target, buffer);
}

void Replay_glBufferData(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    const uint8_t* data = cur.ReadBytes(dataLen);
    GLenum usage = cur.Read<GLenum>();
    g_real.glBufferData(target, size, dataLen ? data : nullptr, usage);
}

void Replay_glBufferSubData(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum target = cur.Read<GLenum>();
    GLintptr offset = cur.Read<GLintptr>();
    GLsizeiptr size = cur.Read<GLsizeiptr>();
    uint32_t dataLen = cur.Read<uint32_t>();
    const uint8_t* data = cur.ReadBytes(dataLen);
    g_real.glBufferSubData(target, offset, size, dataLen ? data : nullptr);
}

void Replay_glGenVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    std::vector<GLuint> real(n);
    g_real.glGenVertexArrays(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("vertexarray", captured[i], real[i]);
}

void Replay_glDeleteVertexArrays(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    std::vector<GLuint> real(n);
    for (GLsizei i = 0; i < n; ++i) {
        captured[i] = cur.Read<GLuint>();
        real[i] = remap.Get("vertexarray", captured[i]);
    }
    g_real.glDeleteVertexArrays(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Unmap("vertexarray", captured[i]);
}

// Client-backed *Pointer/VertexAttribPointer calls are no-ops here: the
// real pointer+data get applied right before the draw call that uses them
// (see ApplyClientArrays), since the traced process's memory doesn't
// exist in this process. VBO-backed calls forward the byte offset as-is.

void Replay_glVertexAttribPointer(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLuint index = cur.Read<GLuint>();
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLboolean normalized = cur.Read<GLboolean>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    if (!clientBacked) {
        g_real.glVertexAttribPointer(index, size, type, normalized, stride, reinterpret_cast<const void*>(offset));
    }
}

void Replay_glVertexPointer(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    if (!clientBacked) g_real.glVertexPointer(size, type, stride, reinterpret_cast<const void*>(offset));
}

void Replay_glColorPointer(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    if (!clientBacked) g_real.glColorPointer(size, type, stride, reinterpret_cast<const void*>(offset));
}

void Replay_glTexCoordPointer(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLint size = cur.Read<GLint>();
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    if (!clientBacked) g_real.glTexCoordPointer(size, type, stride, reinterpret_cast<const void*>(offset));
}

void Replay_glNormalPointer(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum type = cur.Read<GLenum>();
    GLsizei stride = cur.Read<GLsizei>();
    bool clientBacked = cur.Read<bool>();
    uint64_t offset = cur.Read<uint64_t>();
    if (!clientBacked) g_real.glNormalPointer(type, stride, reinterpret_cast<const void*>(offset));
}

void Replay_glGenTextures(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    std::vector<GLuint> real(n);
    g_real.glGenTextures(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("texture", captured[i], real[i]);
}

void Replay_glDeleteTextures(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    std::vector<GLuint> real(n);
    for (GLsizei i = 0; i < n; ++i) {
        captured[i] = cur.Read<GLuint>();
        real[i] = remap.Get("texture", captured[i]);
    }
    g_real.glDeleteTextures(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Unmap("texture", captured[i]);
}

void Replay_glTexImage2D(const uint8_t* args, size_t len, IdRemapper&) {
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
    const uint8_t* pixels = cur.ReadBytes(pixLen);
    g_real.glTexImage2D(target, level, internalformat, width, height, border, format, type, pixLen ? pixels : nullptr);
}

void Replay_glTexSubImage2D(const uint8_t* args, size_t len, IdRemapper&) {
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
    const uint8_t* pixels = cur.ReadBytes(pixLen);
    g_real.glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixLen ? pixels : nullptr);
}

void Replay_glShaderSource(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint shader = remap.Get("shader", cur.Read<GLuint>());
    GLsizei count = cur.Read<GLsizei>();
    std::vector<std::vector<char>> strings(count);
    std::vector<const GLchar*> ptrs(count);
    std::vector<GLint> lens(count);
    std::string joined;
    for (GLsizei i = 0; i < count; ++i) {
        uint32_t l = cur.Read<uint32_t>();
        const uint8_t* bytes = cur.ReadBytes(l);
        strings[i].assign(bytes, bytes + l);
        ptrs[i] = strings[i].data();
        lens[i] = static_cast<GLint>(l);
        joined.append(reinterpret_cast<const char*>(bytes), l);
    }
    RegisterShaderSource(shader, std::move(joined));
    g_real.glShaderSource(shader, count, ptrs.data(), lens.data());
}

void Replay_glBindAttribLocation(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint program = remap.Get("program", cur.Read<GLuint>());
    GLuint index = cur.Read<GLuint>();
    uint32_t nameLen = cur.Read<uint32_t>();
    const uint8_t* nameBytes = cur.ReadBytes(nameLen);
    std::vector<char> name(nameBytes, nameBytes + nameLen);
    name.push_back('\0');
    g_real.glBindAttribLocation(program, index, name.data());
}

void Replay_glGetUniformLocation(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint program = remap.Get("program", cur.Read<GLuint>());
    uint32_t nameLen = cur.Read<uint32_t>();
    const uint8_t* nameBytes = cur.ReadBytes(nameLen);
    std::vector<char> name(nameBytes, nameBytes + nameLen);
    name.push_back('\0');
    cur.Read<GLint>(); // captured return value; replay doesn't need to remap uniform locations
    g_real.glGetUniformLocation(program, name.data());
}

void Replay_glGetAttribLocation(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLuint program = remap.Get("program", cur.Read<GLuint>());
    uint32_t nameLen = cur.Read<uint32_t>();
    const uint8_t* nameBytes = cur.ReadBytes(nameLen);
    std::vector<char> name(nameBytes, nameBytes + nameLen);
    name.push_back('\0');
    cur.Read<GLint>();
    g_real.glGetAttribLocation(program, name.data());
}

void Replay_glUniformMatrix4fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLint location = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLboolean transpose = cur.Read<GLboolean>();
    const uint8_t* bytes = cur.ReadBytes(sizeof(GLfloat) * 16 * count);
    g_real.glUniformMatrix4fv(location, count, transpose, reinterpret_cast<const GLfloat*>(bytes));
}

void Replay_glUniformMatrix3fv(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLint location = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLboolean transpose = cur.Read<GLboolean>();
    const uint8_t* bytes = cur.ReadBytes(sizeof(GLfloat) * 9 * count);
    g_real.glUniformMatrix3fv(location, count, transpose, reinterpret_cast<const GLfloat*>(bytes));
}

void Replay_glGenFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    std::vector<GLuint> real(n);
    g_real.glGenFramebuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("framebuffer", captured[i], real[i]);
}

void Replay_glDeleteFramebuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    std::vector<GLuint> real(n);
    for (GLsizei i = 0; i < n; ++i) {
        captured[i] = cur.Read<GLuint>();
        real[i] = remap.Get("framebuffer", captured[i]);
    }
    g_real.glDeleteFramebuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Unmap("framebuffer", captured[i]);
}

void Replay_glGenRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    for (GLsizei i = 0; i < n; ++i) captured[i] = cur.Read<GLuint>();
    std::vector<GLuint> real(n);
    g_real.glGenRenderbuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Map("renderbuffer", captured[i], real[i]);
}

void Replay_glDeleteRenderbuffers(const uint8_t* args, size_t len, IdRemapper& remap) {
    ByteCursor cur{args, len};
    GLsizei n = cur.Read<GLsizei>();
    std::vector<GLuint> captured(n);
    std::vector<GLuint> real(n);
    for (GLsizei i = 0; i < n; ++i) {
        captured[i] = cur.Read<GLuint>();
        real[i] = remap.Get("renderbuffer", captured[i]);
    }
    g_real.glDeleteRenderbuffers(n, real.data());
    for (GLsizei i = 0; i < n; ++i) remap.Unmap("renderbuffer", captured[i]);
}

void Replay_glDrawArrays(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLint first = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    auto arrays = DecodeClientArrays(cur);
    ApplyClientArrays(arrays);
    g_real.glDrawArrays(mode, first, count);
}

void Replay_glDrawArraysInstanced(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLint first = cur.Read<GLint>();
    GLsizei count = cur.Read<GLsizei>();
    GLsizei instancecount = cur.Read<GLsizei>();
    auto arrays = DecodeClientArrays(cur);
    ApplyClientArrays(arrays);
    g_real.glDrawArraysInstanced(mode, first, count, instancecount);
}

void Replay_glDrawElements(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLsizei count = cur.Read<GLsizei>();
    GLenum type = cur.Read<GLenum>();
    bool indicesClient = cur.Read<bool>();
    if (indicesClient) {
        uint32_t idxLen = cur.Read<uint32_t>();
        const uint8_t* idxBytes = cur.ReadBytes(idxLen); // valid for the rest of this call
        auto arrays = DecodeClientArrays(cur);
        ApplyClientArrays(arrays);
        g_real.glDrawElements(mode, count, type, idxBytes);
    } else {
        uint64_t offset = cur.Read<uint64_t>();
        cur.Read<uint32_t>(); // always 0: no client-array snapshot in this branch (see capture-side note)
        g_real.glDrawElements(mode, count, type, reinterpret_cast<const void*>(offset));
    }
}

void Replay_glDrawElementsInstanced(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    GLenum mode = cur.Read<GLenum>();
    GLsizei count = cur.Read<GLsizei>();
    GLenum type = cur.Read<GLenum>();
    GLsizei instancecount = cur.Read<GLsizei>();
    bool indicesClient = cur.Read<bool>();
    if (indicesClient) {
        uint32_t idxLen = cur.Read<uint32_t>();
        const uint8_t* idxBytes = cur.ReadBytes(idxLen);
        auto arrays = DecodeClientArrays(cur);
        ApplyClientArrays(arrays);
        g_real.glDrawElementsInstanced(mode, count, type, idxBytes, instancecount);
    } else {
        uint64_t offset = cur.Read<uint64_t>();
        cur.Read<uint32_t>();
        g_real.glDrawElementsInstanced(mode, count, type, reinterpret_cast<const void*>(offset), instancecount);
    }
}

void Replay_glGetString(const uint8_t* args, size_t len, IdRemapper&) {
    // Informational only (GL_VERSION/GL_VENDOR/...); doesn't affect replay state.
    ByteCursor cur{args, len};
    cur.Read<GLenum>();
    uint32_t strLen = cur.Read<uint32_t>();
    cur.ReadBytes(strLen);
}

void Replay_wglCreateContext(const uint8_t* args, size_t len, IdRemapper&) {
    // Replay owns the GL context lifecycle itself; traced WGL context
    // management is captured for diagnostics only.
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hdc
    cur.Read<uint64_t>(); // result context
}

void Replay_wglDeleteContext(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hglrc
    cur.Read<GLint>();    // result
}

void Replay_wglMakeCurrent(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hdc
    cur.Read<uint64_t>(); // hglrc
    cur.Read<GLint>();    // result
}

void Replay_wglShareLists(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hglrc1
    cur.Read<uint64_t>(); // hglrc2
    cur.Read<GLint>();    // result
}

void Replay_wglSwapLayerBuffers(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hdc
    cur.Read<GLbitfield>();
    cur.Read<GLint>(); // result
}

void Replay_wglCreateContextAttribsARB(const uint8_t* args, size_t len, IdRemapper&) {
    ByteCursor cur{args, len};
    cur.Read<uint64_t>(); // hdc
    cur.Read<uint64_t>(); // share context
    uint32_t count = cur.Read<uint32_t>();
    cur.ReadBytes(sizeof(GLint) * count);
    cur.Read<uint64_t>(); // result context
}

} // extern "C"

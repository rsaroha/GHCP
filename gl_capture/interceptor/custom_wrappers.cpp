// Hand-written capture-side wrappers for GL functions whose arguments
// include pointers/arrays -- these need real logic (dereferencing,
// object-id bookkeeping, client-array snapshotting), unlike the
// mechanically generated value-only wrappers in
// generated/gl_wrappers_generated.cpp.
#include <windows.h>

#include <cstdint>
#include <cstring>
#include <vector>

#include "client_array_state.h"
#include "gl_custom_wrappers.h"
#include "gl_ids.h"
#include "gl_real_table.h"
#include "trace_writer.h"

extern TraceWriter g_trace;
ClientArrayState g_clientArrays;

namespace {

void WriteIdArray(TraceCall& call, GLsizei n, const GLuint* ids) {
    // n then the raw ids (real ids at capture time; the replay side
    // remaps each one to whatever the real driver handed back when it
    // re-issued the matching glGen*/glCreate* call).
    g_trace.WriteVal(call, n);
    for (GLsizei i = 0; i < n; ++i) g_trace.WriteVal(call, ids[i]);
}

void WriteCString(TraceCall& call, const char* s) {
    uint32_t len = s ? static_cast<uint32_t>(strlen(s)) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, s, len);
}

template <typename T>
void WriteFixedPointer(TraceCall& call, const T* values, size_t count) {
    uint32_t byteLen = values ? static_cast<uint32_t>(sizeof(T) * count) : 0;
    g_trace.WriteVal(call, byteLen);
    if (byteLen) g_trace.WriteBlob(call, values, byteLen);
    uint64_t pointerValue = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(values));
    g_trace.WriteVal(call, pointerValue);
}

size_t LightValueCount(GLenum pname) {
    switch (pname) {
        case 0x1204: return 3; // GL_SPOT_DIRECTION
        case 0x1200: case 0x1201: case 0x1202: case 0x1203: return 4;
        default: return 1;
    }
}

size_t LightModelValueCount(GLenum pname) {
    return pname == 0x0B53 ? 4 : 1; // GL_LIGHT_MODEL_AMBIENT
}

size_t QueryValueCount(GLenum pname) {
    // Most legacy state pnames are scalar. Keep the vector-valued exceptions
    // explicit so callers are not overrun when querying a scalar state.
    switch (pname) {
        case 0x0BA2: case 0x0C10: return 4; // viewport, scissor box
        case 0x0BA6: case 0x0BA7: case 0x0BA8: return 16; // matrices
        case 0x0B70: return 2; // depth range
        case 0x0B12: case 0x0B22: return 2; // point/line size ranges
        case 0x0D3A: return 2; // maximum viewport dimensions
        case 0x0B00: case 0x0B03: case 0x0B04: case 0x0B66: return 4;
        case 0x0B02: return 3; // current normal
        case 0x0C22: case 0x0C23: return 4; // clear color, color write mask
        default: break;
    }
    if (pname >= 0x0B00 && pname <= 0x0BA1) return 1;
    switch (pname) {
        case 0x0BA2: case 0x0C10: case 0x0BA6: case 0x0B00:
        case 0x0B01: case 0x0B02: case 0x0B03: case 0x0B04:
        case 0x0B05: case 0x0B06: case 0x0B07: case 0x0B08:
        case 0x0B09: case 0x0B0A: case 0x0B0B: case 0x0B0C:
        case 0x0B0D: case 0x0B0E: case 0x0B0F: case 0x0B10:
        case 0x0B11: case 0x0B12: case 0x0B13: case 0x0B14:
        case 0x0B15: case 0x0B16: case 0x0B17: case 0x0B18:
        case 0x0B19: case 0x0B1A: case 0x0B1B: case 0x0B1C:
        case 0x0B1D: case 0x0B1E: case 0x0B1F: case 0x0B20:
        case 0x0B21: case 0x0B22: case 0x0B23: case 0x0B24:
        case 0x0B25: case 0x0B26: case 0x0B27: case 0x0B28:
        case 0x0B29: case 0x0B2A: case 0x0B2B: case 0x0B2C:
        case 0x0B2D: case 0x0B2E: case 0x0B2F: case 0x0B30:
        case 0x0B31: case 0x0B32: case 0x0B33: case 0x0B34:
        case 0x0B35: case 0x0B36: case 0x0B37: case 0x0B38:
        case 0x0B39: case 0x0B3A: case 0x0B3B: case 0x0B3C:
        case 0x0B3D: case 0x0B3E: case 0x0B3F: case 0x0B40:
        case 0x0B41: case 0x0B42: case 0x0B43: case 0x0B44:
        case 0x0B45: case 0x0B46: case 0x0B47: case 0x0B48:
        case 0x0B49: case 0x0B4A: case 0x0B4B: case 0x0B4C:
        case 0x0B4D: case 0x0B4E: case 0x0B4F: case 0x0B50:
        case 0x0B51: case 0x0B52: case 0x0B53: case 0x0B54:
        case 0x0B55: case 0x0B56: case 0x0B57: case 0x0B58:
        case 0x0B59: case 0x0B5A: case 0x0B5B: case 0x0B5C:
        case 0x0B5D: case 0x0B5E: case 0x0B5F: case 0x0B60:
        case 0x0B61: case 0x0B62: case 0x0B63: case 0x0B64:
        case 0x0B65: case 0x0B66: case 0x0B67: case 0x0B68:
        case 0x0B69: case 0x0B6A: case 0x0B6B: case 0x0B6C:
        case 0x0B6D: case 0x0B6E: case 0x0B6F: case 0x0B70:
        case 0x0B71: case 0x0B72: case 0x0B73: case 0x0B74:
        case 0x0B75: case 0x0B76: case 0x0B77: case 0x0B78:
        case 0x0B79: case 0x0B7A: case 0x0B7B: case 0x0B7C:
        case 0x0B7D: case 0x0B7E: case 0x0B7F: case 0x0B80:
        case 0x0B81: case 0x0B82: case 0x0B83: case 0x0B84:
        case 0x0B85: case 0x0B86: case 0x0B87: case 0x0B88:
        case 0x0B89: case 0x0B8A: case 0x0B8B: case 0x0B8C:
        case 0x0B8D: case 0x0B8E: case 0x0B8F: case 0x0B90:
        case 0x0B91: case 0x0B92: case 0x0B93: case 0x0B94:
        case 0x0B95: case 0x0B96: case 0x0B97: case 0x0B98:
        case 0x0B99: case 0x0B9A: case 0x0B9B: case 0x0B9C:
        case 0x0B9D: case 0x0B9E: case 0x0B9F: case 0x0BA0:
        case 0x0BA1: return 4;
        case 0x0BA3: case 0x0BA4: return 2;
        default: return 1;
    }
}

template <typename T, typename Fn>
void CaptureQuery(TraceCall& call, GLenum pname, T* data, Fn query) {
    const size_t count = QueryValueCount(pname);
    std::vector<T> values(count);
    query(pname, values.data());
    g_trace.WriteVal(call, pname);
    g_trace.WriteVal(call, static_cast<uint32_t>(count));
    g_trace.WriteBlob(call, values.data(), values.size() * sizeof(T));
    uint64_t pointerValue = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(data));
    g_trace.WriteVal(call, pointerValue);
}

struct PendingClientArray {
    ClientArraySlot slot;
    GLuint attribIndex;
    GLint size;
    GLenum type;
    GLsizei stride;
    const void* pointer;
    size_t byteLen;
};

void CollectClientArrays(std::vector<PendingClientArray>& out, GLint first, GLsizei count) {
    auto consider = [&](ClientArraySlot slot, GLuint attribIndex, const ClientArrayDesc& d, GLint fixedSize) {
        if (!d.set || !d.clientBacked || !d.pointer) return;
        size_t len = ClientArrayByteLength(d, first, count, fixedSize);
        if (len == 0) return;
        out.push_back({slot, attribIndex, fixedSize ? fixedSize : d.size, d.type, d.stride, d.pointer, len});
    };
    consider(ClientArraySlot::Vertex, 0, g_clientArrays.vertex, 0);
    consider(ClientArraySlot::Color, 0, g_clientArrays.color, 0);
    consider(ClientArraySlot::TexCoord, 0, g_clientArrays.texCoord, 0);
    consider(ClientArraySlot::Normal, 0, g_clientArrays.normal, 3);
    for (auto& kv : g_clientArrays.generic) consider(ClientArraySlot::Generic, kv.first, kv.second, 0);
}

void EmitClientArrays(TraceCall& call, const std::vector<PendingClientArray>& arrays) {
    g_trace.WriteVal(call, static_cast<uint32_t>(arrays.size()));
    for (auto& a : arrays) {
        g_trace.WriteVal(call, static_cast<uint32_t>(a.slot));
        g_trace.WriteVal(call, static_cast<uint32_t>(a.attribIndex));
        g_trace.WriteVal(call, a.size);
        g_trace.WriteVal(call, a.type);
        g_trace.WriteVal(call, a.stride);
        g_trace.WriteVal(call, static_cast<uint32_t>(a.byteLen));
        g_trace.WriteBlob(call, a.pointer, a.byteLen);
    }
}

// Max index value found in a captured client-memory index buffer, so we
// know how much of the (also client-memory) vertex arrays are reachable.
GLuint MaxIndex(const void* indices, GLsizei count, GLenum type) {
    GLuint maxIdx = 0;
    for (GLsizei i = 0; i < count; ++i) {
        GLuint v = 0;
        switch (type) {
            case 0x1401: v = static_cast<const uint8_t*>(indices)[i]; break;               // GL_UNSIGNED_BYTE
            case 0x1403: v = static_cast<const uint16_t*>(indices)[i]; break;              // GL_UNSIGNED_SHORT
            case 0x1405: v = static_cast<const uint32_t*>(indices)[i]; break;              // GL_UNSIGNED_INT
            default: break;
        }
        if (v > maxIdx) maxIdx = v;
    }
    return maxIdx;
}

// Whether an element array buffer is actually bound *right now*, per the
// real driver -- queried directly rather than shadowed through our own
// glBindBuffer/glBindVertexArray wrappers, because GL_ELEMENT_ARRAY_BUFFER
// can legitimately end up bound through calls we never see at all: the
// DSA entry points (glVertexArrayElementBuffer et al.) set a VAO's element
// buffer without ever calling glBindBuffer or glBindVertexArray, and
// aren't in functions.json. A shadow copy can only ever reflect the calls
// it's told about; asking the driver is correct regardless of how the
// binding got there. (Real cost: one cheap driver-side query per indexed
// draw call, not a GPU sync -- negligible next to everything else this
// interceptor already does per call.)
bool RealElementArrayBufferIsBound() {
    typedef void(APIENTRY * PFN_glGetIntegerv)(GLenum, GLint*);
    static PFN_glGetIntegerv realGetIntegerv = reinterpret_cast<PFN_glGetIntegerv>(
        GetProcAddress(GetModuleHandleA("opengl32.dll"), "glGetIntegerv"));
    if (!realGetIntegerv) return g_clientArrays.elementArrayBufferBinding != 0; // fallback if never resolved
    constexpr GLenum kElementArrayBufferBinding = 0x8895;
    GLint bound = 0;
    realGetIntegerv(kElementArrayBufferBinding, &bound);
    return bound != 0;
}

} // namespace

extern "C" {

void APIENTRYGEN glColor4dv(const GLdouble* v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4dv);
    WriteFixedPointer(call, v, 4);
    g_trace.EndCall(call);
    if (g_real.glColor4dv) g_real.glColor4dv(v);
}

void APIENTRYGEN glColor3ubv(const GLubyte* v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor3ubv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glColor3ubv) g_real.glColor3ubv(v);
}

void APIENTRYGEN glLoadMatrixf(const GLfloat* m) {
    auto call = g_trace.BeginCall(GLFuncId::glLoadMatrixf);
    WriteFixedPointer(call, m, 16);
    g_trace.EndCall(call);
    if (g_real.glLoadMatrixf) g_real.glLoadMatrixf(m);
}

void APIENTRYGEN glGetBooleanv(GLenum pname, GLboolean* data) {
    auto call = g_trace.BeginCall(GLFuncId::glGetBooleanv);
    if (g_real.glGetBooleanv && data) {
        CaptureQuery<GLboolean>(call, pname, data, g_real.glGetBooleanv);
        const size_t count = QueryValueCount(pname);
        std::memcpy(data, call.data.data() + sizeof(GLenum) + sizeof(uint32_t), count * sizeof(GLboolean));
    } else {
        g_trace.WriteVal(call, pname);
        g_trace.WriteVal(call, static_cast<uint32_t>(0));
        uint64_t pointerValue = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(data));
        g_trace.WriteVal(call, pointerValue);
    }
    g_trace.EndCall(call);
}

void APIENTRYGEN glGetFloatv(GLenum pname, GLfloat* data) {
    auto call = g_trace.BeginCall(GLFuncId::glGetFloatv);
    if (g_real.glGetFloatv && data) {
        CaptureQuery<GLfloat>(call, pname, data, g_real.glGetFloatv);
        const size_t count = QueryValueCount(pname);
        std::memcpy(data, call.data.data() + sizeof(GLenum) + sizeof(uint32_t), count * sizeof(GLfloat));
    } else {
        g_trace.WriteVal(call, pname);
        g_trace.WriteVal(call, static_cast<uint32_t>(0));
        uint64_t pointerValue = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(data));
        g_trace.WriteVal(call, pointerValue);
    }
    g_trace.EndCall(call);
}

void APIENTRYGEN glGetIntegerv(GLenum pname, GLint* data) {
    auto call = g_trace.BeginCall(GLFuncId::glGetIntegerv);
    if (g_real.glGetIntegerv && data) {
        CaptureQuery<GLint>(call, pname, data, g_real.glGetIntegerv);
        const size_t count = QueryValueCount(pname);
        std::memcpy(data, call.data.data() + sizeof(GLenum) + sizeof(uint32_t), count * sizeof(GLint));
    } else {
        g_trace.WriteVal(call, pname);
        g_trace.WriteVal(call, static_cast<uint32_t>(0));
        uint64_t pointerValue = static_cast<uint64_t>(reinterpret_cast<uintptr_t>(data));
        g_trace.WriteVal(call, pointerValue);
    }
    g_trace.EndCall(call);
}

void APIENTRYGEN glLoadMatrixd(const GLdouble* m) {
    auto call = g_trace.BeginCall(GLFuncId::glLoadMatrixd);
    WriteFixedPointer(call, m, 16);
    g_trace.EndCall(call);
    if (g_real.glLoadMatrixd) g_real.glLoadMatrixd(m);
}

void APIENTRYGEN glColor4usv(const GLushort* v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4usv);
    WriteFixedPointer(call, v, 4);
    g_trace.EndCall(call);
    if (g_real.glColor4usv) g_real.glColor4usv(v);
}

void APIENTRYGEN glVertex4sv(const GLshort* v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex4sv);
    WriteFixedPointer(call, v, 4);
    g_trace.EndCall(call);
    if (g_real.glVertex4sv) g_real.glVertex4sv(v);
}

void APIENTRYGEN glLightfv(GLenum light, GLenum pname, const GLfloat* params) {
    auto call = g_trace.BeginCall(GLFuncId::glLightfv);
    g_trace.WriteVal(call, light);
    g_trace.WriteVal(call, pname);
    WriteFixedPointer(call, params, LightValueCount(pname));
    g_trace.EndCall(call);
    if (g_real.glLightfv) g_real.glLightfv(light, pname, params);
}

void APIENTRYGEN glLightModelfv(GLenum pname, const GLfloat* params) {
    auto call = g_trace.BeginCall(GLFuncId::glLightModelfv);
    g_trace.WriteVal(call, pname);
    WriteFixedPointer(call, params, LightModelValueCount(pname));
    g_trace.EndCall(call);
    if (g_real.glLightModelfv) g_real.glLightModelfv(pname, params);
}

void APIENTRYGEN glInterleavedArrays(GLenum format, GLsizei stride, const void* pointer) {
    auto call = g_trace.BeginCall(GLFuncId::glInterleavedArrays);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, static_cast<uint8_t>(pointer != nullptr));
    g_trace.EndCall(call);
    if (g_real.glInterleavedArrays) g_real.glInterleavedArrays(format, stride, pointer);
}

void APIENTRYGEN glColor4fv(const GLfloat* v) {
    auto call = g_trace.BeginCall(GLFuncId::glColor4fv);
    WriteFixedPointer(call, v, 4);
    g_trace.EndCall(call);
    if (g_real.glColor4fv) g_real.glColor4fv(v);
}

void APIENTRYGEN glNormal3dv(const GLdouble* v) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3dv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glNormal3dv) g_real.glNormal3dv(v);
}

void APIENTRYGEN glNormal3fv(const GLfloat* v) {
    auto call = g_trace.BeginCall(GLFuncId::glNormal3fv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glNormal3fv) g_real.glNormal3fv(v);
}

void APIENTRYGEN glTexCoord2dv(const GLdouble* v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2dv);
    WriteFixedPointer(call, v, 2);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2dv) g_real.glTexCoord2dv(v);
}

void APIENTRYGEN glTexCoord2fv(const GLfloat* v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2fv);
    WriteFixedPointer(call, v, 2);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2fv) g_real.glTexCoord2fv(v);
}

void APIENTRYGEN glTexCoord2iv(const GLint* v) {
    auto call = g_trace.BeginCall(GLFuncId::glTexCoord2iv);
    WriteFixedPointer(call, v, 2);
    g_trace.EndCall(call);
    if (g_real.glTexCoord2iv) g_real.glTexCoord2iv(v);
}

void APIENTRYGEN glVertex3dv(const GLdouble* v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3dv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glVertex3dv) g_real.glVertex3dv(v);
}

void APIENTRYGEN glVertex3fv(const GLfloat* v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3fv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glVertex3fv) g_real.glVertex3fv(v);
}

void APIENTRYGEN glVertex3iv(const GLint* v) {
    auto call = g_trace.BeginCall(GLFuncId::glVertex3iv);
    WriteFixedPointer(call, v, 3);
    g_trace.EndCall(call);
    if (g_real.glVertex3iv) g_real.glVertex3iv(v);
}

// ---- buffers ----

void APIENTRYGEN glGenBuffers(GLsizei n, GLuint* buffers) {
    if (g_real.glGenBuffers) g_real.glGenBuffers(n, buffers);
    auto call = g_trace.BeginCall(GLFuncId::glGenBuffers);
    WriteIdArray(call, n, buffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDeleteBuffers(GLsizei n, const GLuint* buffers) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteBuffers);
    WriteIdArray(call, n, buffers);
    g_trace.EndCall(call);
    if (g_real.glDeleteBuffers) g_real.glDeleteBuffers(n, buffers);
}

void APIENTRYGEN glBindBuffer(GLenum target, GLuint buffer) {
    if (target == 0x8892) g_clientArrays.arrayBufferBinding = buffer;         // GL_ARRAY_BUFFER
    else if (target == 0x8893) g_clientArrays.elementArrayBufferBinding = buffer; // GL_ELEMENT_ARRAY_BUFFER
    auto call = g_trace.BeginCall(GLFuncId::glBindBuffer);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, buffer);
    g_trace.EndCall(call);
    if (g_real.glBindBuffer) g_real.glBindBuffer(target, buffer);
}

void APIENTRYGEN glBufferData(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
    auto call = g_trace.BeginCall(GLFuncId::glBufferData);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, size);
    uint32_t len = data ? static_cast<uint32_t>(size) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, data, len);
    g_trace.WriteVal(call, usage);
    g_trace.EndCall(call);
    if (g_real.glBufferData) g_real.glBufferData(target, size, data, usage);
}

void APIENTRYGEN glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void* data) {
    auto call = g_trace.BeginCall(GLFuncId::glBufferSubData);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    uint32_t len = data ? static_cast<uint32_t>(size) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, data, len);
    g_trace.EndCall(call);
    if (g_real.glBufferSubData) g_real.glBufferSubData(target, offset, size, data);
}

// ---- vertex arrays ----

void APIENTRYGEN glGenVertexArrays(GLsizei n, GLuint* arrays) {
    if (g_real.glGenVertexArrays) g_real.glGenVertexArrays(n, arrays);
    auto call = g_trace.BeginCall(GLFuncId::glGenVertexArrays);
    WriteIdArray(call, n, arrays);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDeleteVertexArrays(GLsizei n, const GLuint* arrays) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteVertexArrays);
    WriteIdArray(call, n, arrays);
    g_trace.EndCall(call);
    if (g_real.glDeleteVertexArrays) g_real.glDeleteVertexArrays(n, arrays);
}

void APIENTRYGEN glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    bool clientBacked = g_clientArrays.arrayBufferBinding == 0;
    g_clientArrays.generic[index] = ClientArrayDesc{true, clientBacked, size, type, stride, pointer};

    auto call = g_trace.BeginCall(GLFuncId::glVertexAttribPointer);
    g_trace.WriteVal(call, index);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, normalized);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, clientBacked);
    // When VBO-backed, `pointer` is really a small integer byte offset --
    // safe to log and replay verbatim. When client-backed, the real
    // snapshot travels with the draw call instead, so we don't need (and
    // can't safely keep) the pointer itself here.
    uint64_t offsetOrZero = clientBacked ? 0 : reinterpret_cast<uint64_t>(pointer);
    g_trace.WriteVal(call, offsetOrZero);
    g_trace.EndCall(call);

    if (g_real.glVertexAttribPointer) g_real.glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void APIENTRYGEN glVertexPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
    bool clientBacked = g_clientArrays.arrayBufferBinding == 0;
    g_clientArrays.vertex = ClientArrayDesc{true, clientBacked, size, type, stride, pointer};
    auto call = g_trace.BeginCall(GLFuncId::glVertexPointer);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, clientBacked);
    uint64_t offsetOrZero = clientBacked ? 0 : reinterpret_cast<uint64_t>(pointer);
    g_trace.WriteVal(call, offsetOrZero);
    g_trace.EndCall(call);
    if (g_real.glVertexPointer) g_real.glVertexPointer(size, type, stride, pointer);
}

void APIENTRYGEN glColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
    bool clientBacked = g_clientArrays.arrayBufferBinding == 0;
    g_clientArrays.color = ClientArrayDesc{true, clientBacked, size, type, stride, pointer};
    auto call = g_trace.BeginCall(GLFuncId::glColorPointer);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, clientBacked);
    uint64_t offsetOrZero = clientBacked ? 0 : reinterpret_cast<uint64_t>(pointer);
    g_trace.WriteVal(call, offsetOrZero);
    g_trace.EndCall(call);
    if (g_real.glColorPointer) g_real.glColorPointer(size, type, stride, pointer);
}

void APIENTRYGEN glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) {
    bool clientBacked = g_clientArrays.arrayBufferBinding == 0;
    g_clientArrays.texCoord = ClientArrayDesc{true, clientBacked, size, type, stride, pointer};
    auto call = g_trace.BeginCall(GLFuncId::glTexCoordPointer);
    g_trace.WriteVal(call, size);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, clientBacked);
    uint64_t offsetOrZero = clientBacked ? 0 : reinterpret_cast<uint64_t>(pointer);
    g_trace.WriteVal(call, offsetOrZero);
    g_trace.EndCall(call);
    if (g_real.glTexCoordPointer) g_real.glTexCoordPointer(size, type, stride, pointer);
}

void APIENTRYGEN glNormalPointer(GLenum type, GLsizei stride, const void* pointer) {
    bool clientBacked = g_clientArrays.arrayBufferBinding == 0;
    g_clientArrays.normal = ClientArrayDesc{true, clientBacked, 3, type, stride, pointer};
    auto call = g_trace.BeginCall(GLFuncId::glNormalPointer);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, stride);
    g_trace.WriteVal(call, clientBacked);
    uint64_t offsetOrZero = clientBacked ? 0 : reinterpret_cast<uint64_t>(pointer);
    g_trace.WriteVal(call, offsetOrZero);
    g_trace.EndCall(call);
    if (g_real.glNormalPointer) g_real.glNormalPointer(type, stride, pointer);
}

// ---- textures ----

void APIENTRYGEN glGenTextures(GLsizei n, GLuint* textures) {
    if (g_real.glGenTextures) g_real.glGenTextures(n, textures);
    auto call = g_trace.BeginCall(GLFuncId::glGenTextures);
    WriteIdArray(call, n, textures);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDeleteTextures(GLsizei n, const GLuint* textures) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteTextures);
    WriteIdArray(call, n, textures);
    g_trace.EndCall(call);
    if (g_real.glDeleteTextures) g_real.glDeleteTextures(n, textures);
}

namespace {
size_t TexelSize(GLenum format, GLenum type) {
    size_t comps = 4;
    switch (format) {
        case 0x1906: comps = 1; break; // GL_ALPHA
        case 0x1909: comps = 1; break; // GL_LUMINANCE
        case 0x1907: comps = 3; break; // GL_RGB
        case 0x1908: comps = 4; break; // GL_RGBA
        case 0x1902: comps = 1; break; // GL_DEPTH_COMPONENT
        default: comps = 4; break;
    }
    return comps * GLTypeSize(type);
}
} // namespace

void APIENTRYGEN glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTexImage2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, internalformat);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, border);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    uint32_t len = pixels ? static_cast<uint32_t>(TexelSize(format, type) * width * height) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, pixels, len);
    g_trace.EndCall(call);
    if (g_real.glTexImage2D) g_real.glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void APIENTRYGEN glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTexSubImage2D);
    g_trace.WriteVal(call, target);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    uint32_t len = pixels ? static_cast<uint32_t>(TexelSize(format, type) * width * height) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, pixels, len);
    g_trace.EndCall(call);
    if (g_real.glTexSubImage2D) g_real.glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void APIENTRYGEN glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat* value) {
    GLsizei count = buffer == 0x1800 ? 4 : 1; // GL_COLOR, otherwise depth/stencil
    auto call = g_trace.BeginCall(GLFuncId::glClearBufferfv);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, drawbuffer);
    g_trace.WriteVal(call, count);
    if (value) g_trace.WriteBlob(call, value, sizeof(GLfloat) * count);
    g_trace.EndCall(call);
    if (g_real.glClearBufferfv) g_real.glClearBufferfv(buffer, drawbuffer, value);
}

void APIENTRYGEN glCreateBuffers(GLsizei n, GLuint* buffers) {
    if (g_real.glCreateBuffers) g_real.glCreateBuffers(n, buffers);
    auto call = g_trace.BeginCall(GLFuncId::glCreateBuffers);
    WriteIdArray(call, n, buffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glCreateFramebuffers(GLsizei n, GLuint* framebuffers) {
    if (g_real.glCreateFramebuffers) g_real.glCreateFramebuffers(n, framebuffers);
    auto call = g_trace.BeginCall(GLFuncId::glCreateFramebuffers);
    WriteIdArray(call, n, framebuffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glCreateRenderbuffers(GLsizei n, GLuint* renderbuffers) {
    if (g_real.glCreateRenderbuffers) g_real.glCreateRenderbuffers(n, renderbuffers);
    auto call = g_trace.BeginCall(GLFuncId::glCreateRenderbuffers);
    WriteIdArray(call, n, renderbuffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glCreateTextures(GLenum target, GLsizei n, GLuint* textures) {
    if (g_real.glCreateTextures) g_real.glCreateTextures(target, n, textures);
    auto call = g_trace.BeginCall(GLFuncId::glCreateTextures);
    g_trace.WriteVal(call, target);
    WriteIdArray(call, n, textures);
    g_trace.EndCall(call);
}

void APIENTRYGEN glCreateVertexArrays(GLsizei n, GLuint* arrays) {
    if (g_real.glCreateVertexArrays) g_real.glCreateVertexArrays(n, arrays);
    auto call = g_trace.BeginCall(GLFuncId::glCreateVertexArrays);
    WriteIdArray(call, n, arrays);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity,
                                      GLsizei length, const GLchar* buf) {
    auto call = g_trace.BeginCall(GLFuncId::glDebugMessageInsert);
    g_trace.WriteVal(call, source);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, id);
    g_trace.WriteVal(call, severity);
    uint32_t len = length < 0 && buf ? static_cast<uint32_t>(strlen(buf)) :
                   (length > 0 ? static_cast<uint32_t>(length) : 0);
    g_trace.WriteVal(call, len);
    if (len && buf) g_trace.WriteBlob(call, buf, len);
    g_trace.EndCall(call);
    if (g_real.glDebugMessageInsert) g_real.glDebugMessageInsert(source, type, id, severity, length, buf);
}

void APIENTRYGEN glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    if (g_real.glGetProgramInfoLog) g_real.glGetProgramInfoLog(program, bufSize, length, infoLog);
    auto call = g_trace.BeginCall(GLFuncId::glGetProgramInfoLog);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, bufSize);
    GLsizei actual = length ? *length : (infoLog ? static_cast<GLsizei>(strlen(infoLog)) : 0);
    actual = actual < 0 ? 0 : (actual > bufSize ? bufSize : actual);
    g_trace.WriteVal(call, actual);
    if (actual && infoLog) g_trace.WriteBlob(call, infoLog, actual);
    g_trace.EndCall(call);
}

void APIENTRYGEN glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog) {
    if (g_real.glGetShaderInfoLog) g_real.glGetShaderInfoLog(shader, bufSize, length, infoLog);
    auto call = g_trace.BeginCall(GLFuncId::glGetShaderInfoLog);
    g_trace.WriteVal(call, shader);
    g_trace.WriteVal(call, bufSize);
    GLsizei actual = length ? *length : (infoLog ? static_cast<GLsizei>(strlen(infoLog)) : 0);
    actual = actual < 0 ? 0 : (actual > bufSize ? bufSize : actual);
    g_trace.WriteVal(call, actual);
    if (actual && infoLog) g_trace.WriteBlob(call, infoLog, actual);
    g_trace.EndCall(call);
}

void APIENTRYGEN glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void* data, GLbitfield flags) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedBufferStorage);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, size);
    uint32_t len = data && size > 0 ? static_cast<uint32_t>(size) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, data, len);
    g_trace.WriteVal(call, flags);
    g_trace.EndCall(call);
    if (g_real.glNamedBufferStorage) g_real.glNamedBufferStorage(buffer, size, data, flags);
}

void APIENTRYGEN glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void* data) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedBufferSubData);
    g_trace.WriteVal(call, buffer);
    g_trace.WriteVal(call, offset);
    g_trace.WriteVal(call, size);
    uint32_t len = data && size > 0 ? static_cast<uint32_t>(size) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, data, len);
    g_trace.EndCall(call);
    if (g_real.glNamedBufferSubData) g_real.glNamedBufferSubData(buffer, offset, size, data);
}

void APIENTRYGEN glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum* bufs) {
    auto call = g_trace.BeginCall(GLFuncId::glNamedFramebufferDrawBuffers);
    g_trace.WriteVal(call, framebuffer);
    g_trace.WriteVal(call, n);
    if (n > 0 && bufs) g_trace.WriteBlob(call, bufs, sizeof(GLenum) * static_cast<size_t>(n));
    g_trace.EndCall(call);
    if (g_real.glNamedFramebufferDrawBuffers) g_real.glNamedFramebufferDrawBuffers(framebuffer, n, bufs);
}

void APIENTRYGEN glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                                     GLsizei width, GLsizei height, GLenum format, GLenum type,
                                     const void* pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureSubImage2D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    uint32_t len = pixels ? static_cast<uint32_t>(TexelSize(format, type) * width * height) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, pixels, len);
    g_trace.EndCall(call);
    if (g_real.glTextureSubImage2D) g_real.glTextureSubImage2D(texture, level, xoffset, yoffset,
                                                                width, height, format, type, pixels);
}

void APIENTRYGEN glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                                     GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                                     GLenum format, GLenum type, const void* pixels) {
    auto call = g_trace.BeginCall(GLFuncId::glTextureSubImage3D);
    g_trace.WriteVal(call, texture);
    g_trace.WriteVal(call, level);
    g_trace.WriteVal(call, xoffset);
    g_trace.WriteVal(call, yoffset);
    g_trace.WriteVal(call, zoffset);
    g_trace.WriteVal(call, width);
    g_trace.WriteVal(call, height);
    g_trace.WriteVal(call, depth);
    g_trace.WriteVal(call, format);
    g_trace.WriteVal(call, type);
    uint32_t len = pixels ? static_cast<uint32_t>(TexelSize(format, type) * width * height * depth) : 0;
    g_trace.WriteVal(call, len);
    if (len) g_trace.WriteBlob(call, pixels, len);
    g_trace.EndCall(call);
    if (g_real.glTextureSubImage3D) g_real.glTextureSubImage3D(texture, level, xoffset, yoffset,
                                                                zoffset, width, height, depth, format, type, pixels);
}

// ---- shaders / programs ----

void APIENTRYGEN glShaderSource(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length) {
    auto call = g_trace.BeginCall(GLFuncId::glShaderSource);
    g_trace.WriteVal(call, shader);
    g_trace.WriteVal(call, count);
    for (GLsizei i = 0; i < count; ++i) {
        uint32_t len = length ? static_cast<uint32_t>(length[i]) : static_cast<uint32_t>(strlen(string[i]));
        g_trace.WriteVal(call, len);
        g_trace.WriteBlob(call, string[i], len);
    }
    g_trace.EndCall(call);
    if (g_real.glShaderSource) g_real.glShaderSource(shader, count, string, length);
}

void APIENTRYGEN glBindAttribLocation(GLuint program, GLuint index, const GLchar* name) {
    auto call = g_trace.BeginCall(GLFuncId::glBindAttribLocation);
    g_trace.WriteVal(call, program);
    g_trace.WriteVal(call, index);
    WriteCString(call, name);
    g_trace.EndCall(call);
    if (g_real.glBindAttribLocation) g_real.glBindAttribLocation(program, index, name);
}

GLint APIENTRYGEN glGetUniformLocation(GLuint program, const GLchar* name) {
    GLint result = g_real.glGetUniformLocation ? g_real.glGetUniformLocation(program, name) : -1;
    auto call = g_trace.BeginCall(GLFuncId::glGetUniformLocation);
    g_trace.WriteVal(call, program);
    WriteCString(call, name);
    g_trace.WriteVal(call, result);
    g_trace.EndCall(call);
    return result;
}

GLint APIENTRYGEN glGetAttribLocation(GLuint program, const GLchar* name) {
    GLint result = g_real.glGetAttribLocation ? g_real.glGetAttribLocation(program, name) : -1;
    auto call = g_trace.BeginCall(GLFuncId::glGetAttribLocation);
    g_trace.WriteVal(call, program);
    WriteCString(call, name);
    g_trace.WriteVal(call, result);
    g_trace.EndCall(call);
    return result;
}

void APIENTRYGEN glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    auto call = g_trace.BeginCall(GLFuncId::glUniformMatrix4fv);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, transpose);
    g_trace.WriteBlob(call, value, sizeof(GLfloat) * 16 * count);
    g_trace.EndCall(call);
    if (g_real.glUniformMatrix4fv) g_real.glUniformMatrix4fv(location, count, transpose, value);
}

void APIENTRYGEN glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value) {
    auto call = g_trace.BeginCall(GLFuncId::glUniformMatrix3fv);
    g_trace.WriteVal(call, location);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, transpose);
    g_trace.WriteBlob(call, value, sizeof(GLfloat) * 9 * count);
    g_trace.EndCall(call);
    if (g_real.glUniformMatrix3fv) g_real.glUniformMatrix3fv(location, count, transpose, value);
}

// ---- framebuffers / renderbuffers ----

void APIENTRYGEN glGenFramebuffers(GLsizei n, GLuint* framebuffers) {
    if (g_real.glGenFramebuffers) g_real.glGenFramebuffers(n, framebuffers);
    auto call = g_trace.BeginCall(GLFuncId::glGenFramebuffers);
    WriteIdArray(call, n, framebuffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteFramebuffers);
    WriteIdArray(call, n, framebuffers);
    g_trace.EndCall(call);
    if (g_real.glDeleteFramebuffers) g_real.glDeleteFramebuffers(n, framebuffers);
}

void APIENTRYGEN glGenRenderbuffers(GLsizei n, GLuint* renderbuffers) {
    if (g_real.glGenRenderbuffers) g_real.glGenRenderbuffers(n, renderbuffers);
    auto call = g_trace.BeginCall(GLFuncId::glGenRenderbuffers);
    WriteIdArray(call, n, renderbuffers);
    g_trace.EndCall(call);
}

void APIENTRYGEN glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers) {
    auto call = g_trace.BeginCall(GLFuncId::glDeleteRenderbuffers);
    WriteIdArray(call, n, renderbuffers);
    g_trace.EndCall(call);
    if (g_real.glDeleteRenderbuffers) g_real.glDeleteRenderbuffers(n, renderbuffers);
}

// ---- draw calls ----
// These embed a snapshot of any *client-memory* (non-VBO) vertex arrays
// reachable by the draw, since replay has no access to the traced
// process's memory. VBO-backed arrays need no snapshot here -- their data
// was already captured by glBufferData/glBufferSubData.

void APIENTRYGEN glDrawArrays(GLenum mode, GLint first, GLsizei count) {
    std::vector<PendingClientArray> arrays;
    CollectClientArrays(arrays, first, count);

    auto call = g_trace.BeginCall(GLFuncId::glDrawArrays);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, first);
    g_trace.WriteVal(call, count);
    EmitClientArrays(call, arrays);
    g_trace.EndCall(call);

    if (g_real.glDrawArrays) g_real.glDrawArrays(mode, first, count);
}

void APIENTRYGEN glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) {
    std::vector<PendingClientArray> arrays;
    CollectClientArrays(arrays, first, count);

    auto call = g_trace.BeginCall(GLFuncId::glDrawArraysInstanced);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, first);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, instancecount);
    EmitClientArrays(call, arrays);
    g_trace.EndCall(call);

    if (g_real.glDrawArraysInstanced) g_real.glDrawArraysInstanced(mode, first, count, instancecount);
}

void APIENTRYGEN glDrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) {
    bool indicesClient = !RealElementArrayBufferIsBound();

    auto call = g_trace.BeginCall(GLFuncId::glDrawElements);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, indicesClient);
    if (indicesClient) {
        size_t idxLen = static_cast<size_t>(count) * GLTypeSize(type);
        g_trace.WriteVal(call, static_cast<uint32_t>(idxLen));
        g_trace.WriteBlob(call, indices, idxLen);

        std::vector<PendingClientArray> arrays;
        GLuint maxIdx = MaxIndex(indices, count, type);
        CollectClientArrays(arrays, 0, static_cast<GLsizei>(maxIdx) + 1);
        EmitClientArrays(call, arrays);
    } else {
        g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(indices)));
        // Vertex-array-from-client-memory + indices-from-VBO is not
        // captured (see interceptor/README limitation note).
        g_trace.WriteVal(call, static_cast<uint32_t>(0));
    }
    g_trace.EndCall(call);

    if (g_real.glDrawElements) g_real.glDrawElements(mode, count, type, indices);
}

void APIENTRYGEN glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount) {
    bool indicesClient = !RealElementArrayBufferIsBound();

    auto call = g_trace.BeginCall(GLFuncId::glDrawElementsInstanced);
    g_trace.WriteVal(call, mode);
    g_trace.WriteVal(call, count);
    g_trace.WriteVal(call, type);
    g_trace.WriteVal(call, instancecount);
    g_trace.WriteVal(call, indicesClient);
    if (indicesClient) {
        size_t idxLen = static_cast<size_t>(count) * GLTypeSize(type);
        g_trace.WriteVal(call, static_cast<uint32_t>(idxLen));
        g_trace.WriteBlob(call, indices, idxLen);

        std::vector<PendingClientArray> arrays;
        GLuint maxIdx = MaxIndex(indices, count, type);
        CollectClientArrays(arrays, 0, static_cast<GLsizei>(maxIdx) + 1);
        EmitClientArrays(call, arrays);
    } else {
        g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(indices)));
        g_trace.WriteVal(call, static_cast<uint32_t>(0));
    }
    g_trace.EndCall(call);

    if (g_real.glDrawElementsInstanced) g_real.glDrawElementsInstanced(mode, count, type, indices, instancecount);
}

const GLubyte* APIENTRYGEN glGetString(GLenum name) {
    const GLubyte* result = g_real.glGetString ? g_real.glGetString(name) : nullptr;
    auto call = g_trace.BeginCall(GLFuncId::glGetString);
    g_trace.WriteVal(call, name);
    WriteCString(call, reinterpret_cast<const char*>(result));
    g_trace.EndCall(call);
    return result;
}

HGLRC APIENTRYGEN wglCreateContext(HDC hdc) {
    HGLRC result = g_real.wglCreateContext ? g_real.wglCreateContext(hdc) : nullptr;
    auto call = g_trace.BeginCall(GLFuncId::wglCreateContext);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hdc)));
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(result)));
    g_trace.EndCall(call);
    return result;
}

BOOL APIENTRYGEN wglDeleteContext(HGLRC hglrc) {
    BOOL result = g_real.wglDeleteContext ? g_real.wglDeleteContext(hglrc) : FALSE;
    auto call = g_trace.BeginCall(GLFuncId::wglDeleteContext);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hglrc)));
    g_trace.WriteVal(call, static_cast<GLint>(result));
    g_trace.EndCall(call);
    return result;
}

BOOL APIENTRYGEN wglMakeCurrent(HDC hdc, HGLRC hglrc) {
    BOOL result = g_real.wglMakeCurrent ? g_real.wglMakeCurrent(hdc, hglrc) : FALSE;
    auto call = g_trace.BeginCall(GLFuncId::wglMakeCurrent);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hdc)));
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hglrc)));
    g_trace.WriteVal(call, static_cast<GLint>(result));
    g_trace.EndCall(call);
    return result;
}

BOOL APIENTRYGEN wglShareLists(HGLRC hglrc1, HGLRC hglrc2) {
    BOOL result = g_real.wglShareLists ? g_real.wglShareLists(hglrc1, hglrc2) : FALSE;
    auto call = g_trace.BeginCall(GLFuncId::wglShareLists);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hglrc1)));
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hglrc2)));
    g_trace.WriteVal(call, static_cast<GLint>(result));
    g_trace.EndCall(call);
    return result;
}

BOOL APIENTRYGEN wglSwapLayerBuffers(HDC hdc, UINT planes) {
    BOOL result = g_real.wglSwapLayerBuffers ? g_real.wglSwapLayerBuffers(hdc, planes) : FALSE;
    auto call = g_trace.BeginCall(GLFuncId::wglSwapLayerBuffers);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hdc)));
    g_trace.WriteVal(call, planes);
    g_trace.WriteVal(call, static_cast<GLint>(result));
    g_trace.EndCall(call);
    return result;
}

HGLRC APIENTRYGEN wglCreateContextAttribsARB(HDC hdc, HGLRC shareContext, const GLint* attribList) {
    HGLRC result = g_real.wglCreateContextAttribsARB ? g_real.wglCreateContextAttribsARB(hdc, shareContext, attribList) : nullptr;
    auto call = g_trace.BeginCall(GLFuncId::wglCreateContextAttribsARB);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(hdc)));
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(shareContext)));
    uint32_t count = 0;
    if (attribList) {
        while (count < 256) {
            GLint v = attribList[count];
            ++count;
            if (v == 0) break;
        }
    }
    g_trace.WriteVal(call, count);
    if (count) g_trace.WriteBlob(call, attribList, sizeof(GLint) * count);
    g_trace.WriteVal(call, static_cast<uint64_t>(reinterpret_cast<uintptr_t>(result)));
    g_trace.EndCall(call);
    return result;
}

} // extern "C"

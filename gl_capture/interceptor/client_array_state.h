#pragma once
#include <cstdint>
#include <unordered_map>

#include "gl_types_min.h"

// Tracks enough state on the capture side to know, for each vertex-array
// slot, whether its last-set pointer is real client memory (needs to be
// snapshotted at draw time) or a byte offset into a bound VBO (whose
// contents were already captured via glBufferData/glBufferSubData).
//
// GL fixes the address-vs-offset interpretation of a *Pointer call's
// `pointer` argument at the time that call is made (based on the
// GL_ARRAY_BUFFER binding then), not at draw time -- so `clientBacked` is
// latched when the pointer is set, not re-derived later.
//
// `elementArrayBufferBinding` is a best-effort shadow of
// GL_ELEMENT_ARRAY_BUFFER, updated only by our own glBindBuffer wrapper --
// it's used only as a fallback if the real driver can't be queried
// directly (see RealElementArrayBufferIsBound in custom_wrappers.cpp).
// The real query exists because this binding can end up set through calls
// we never see at all: it's part of a VAO's own state, and the DSA entry
// points (glVertexArrayElementBuffer et al.) set it without ever calling
// glBindBuffer or glBindVertexArray. A shadow copy can only reflect the
// calls it's told about, so it can't be made reliable here no matter how
// it's updated -- getting it wrong makes a real, VBO-backed indexed draw
// look client-memory-backed, which segfaults trying to snapshot/memcpy a
// small integer byte offset as if it were a real pointer.

enum class ClientArraySlot : uint32_t { Vertex = 0, Color = 1, TexCoord = 2, Normal = 3, Generic = 4 };

struct ClientArrayDesc {
    bool set = false;
    bool clientBacked = false;
    GLint size = 0;
    GLenum type = 0;
    GLsizei stride = 0;
    const void* pointer = nullptr;
};

struct ClientArrayState {
    GLuint arrayBufferBinding = 0;
    GLuint elementArrayBufferBinding = 0;

    ClientArrayDesc vertex, color, texCoord, normal;
    std::unordered_map<GLuint, ClientArrayDesc> generic; // keyed by attrib index
};

extern ClientArrayState g_clientArrays;

inline size_t GLTypeSize(GLenum type) {
    switch (type) {
        case 0x1400: return 1; // GL_BYTE
        case 0x1401: return 1; // GL_UNSIGNED_BYTE
        case 0x1402: return 2; // GL_SHORT
        case 0x1403: return 2; // GL_UNSIGNED_SHORT
        case 0x1404: return 4; // GL_INT
        case 0x1405: return 4; // GL_UNSIGNED_INT
        case 0x1406: return 4; // GL_FLOAT
        case 0x140A: return 8; // GL_DOUBLE
        default: return 4;
    }
}

// Exact byte length reachable through `desc` for a non-indexed draw of
// [first, first+count), per GL's stride/size rules.
inline size_t ClientArrayByteLength(const ClientArrayDesc& desc, GLint first, GLsizei count, GLint fixedSize = 0) {
    if (count <= 0) return 0;
    GLint size = fixedSize ? fixedSize : desc.size;
    size_t elem = static_cast<size_t>(size) * GLTypeSize(desc.type);
    size_t effStride = desc.stride != 0 ? static_cast<size_t>(desc.stride) : elem;
    size_t lastIndex = static_cast<size_t>(first) + static_cast<size_t>(count) - 1;
    return lastIndex * effStride + elem;
}

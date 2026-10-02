#pragma once
#include <string>
#include <vector>

#include "gl_types_min.h"
#include "id_remapper.h"

// Non-zero realId marks a line as a texture entry (double-clickable in the
// resources/state list to view its pixels); realId 0 means "not a texture
// line". Parallel to ResourceStateReport::lines (same index, same size).
struct TextureLineInfo {
    GLuint realId = 0;
    GLint width = 0;
    GLint height = 0;
    GLenum internalFormat = 0;
};

// Non-zero realId marks a line as a shader entry (double-clickable to view
// its source); realId 0 means "not a shader line".
struct ShaderLineInfo {
    GLuint realId = 0;
};

// Non-zero realId marks a line as a framebuffer entry (double-clickable to
// open a dedicated attachment view window).
struct FramebufferLineInfo {
    GLuint realId = 0;
    uint32_t capturedId = 0;
};

struct ResourceStateReport {
    std::vector<std::string> lines;
    std::vector<TextureLineInfo> textureByLine;
    std::vector<ShaderLineInfo> shaderByLine;
    std::vector<FramebufferLineInfo> framebufferByLine;
};

// Dumps every known buffer/texture/framebuffer/renderbuffer/program/shader
// (from what's been created so far in the replay) plus current GL binding
// state, by querying the live context the replay just stopped at.
ResourceStateReport RenderResourcesAndState(const IdRemapper& remap);

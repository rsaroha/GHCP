#include "shader_registry.h"

#include <unordered_map>

namespace {
std::unordered_map<GLuint, std::string> g_sources;
} // namespace

void ClearShaderSources() {
    g_sources.clear();
}

void RegisterShaderSource(GLuint realId, std::string source) {
    g_sources[realId] = std::move(source);
}

const std::string* GetShaderSource(GLuint realId) {
    auto it = g_sources.find(realId);
    return it == g_sources.end() ? nullptr : &it->second;
}

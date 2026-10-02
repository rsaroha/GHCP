#pragma once
#include <string>

#include "gl_types_min.h"

// Remembers captured shader source by real (replay-time) shader id, so
// the resources/state viewer can show it when a shader entry is
// double-clicked. Reset at the start of every RunToIndex (a fresh replay
// context means old ids may be reused for different shaders).
void ClearShaderSources();
void RegisterShaderSource(GLuint realId, std::string source);
// Returns nullptr if nothing is registered for this id.
const std::string* GetShaderSource(GLuint realId);

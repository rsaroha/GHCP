#pragma once
#include "gl_types_min.h"

// Shows shader `realId`'s captured source (see shader_registry.h) in a
// read-only text window, creating one on first use and reusing/updating
// it on subsequent calls.
void ShowShaderSource(GLuint realId);

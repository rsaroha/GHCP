#pragma once
#include "gl_types_min.h"

// Reads back `realId`'s pixel data from the live GL context (as it
// currently stands) and displays it in a window, creating one on first
// use and reusing/updating it on subsequent calls. `internalFormat` (as
// reported by GL_TEXTURE_INTERNAL_FORMAT) picks the readback: ordinary
// color formats read back as RGBA; depth and depth-stencil formats read
// back their depth (and stencil, if present) instead, visualized as
// grayscale, with the exact per-pixel value(s) shown as the mouse moves
// over the image.
void ShowTextureImage(GLuint realId, GLint width, GLint height, GLenum internalFormat);

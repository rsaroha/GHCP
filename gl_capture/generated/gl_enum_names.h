// GENERATED FILE - do not edit by hand. See codegen/generate.py
#pragma once
#include <cstdint>
#include <string>

// Symbolic name for a GLenum value, or nullptr if unknown.
const char* LookupEnumName(uint32_t value);

// Decomposes a GLbitfield into its known flag names joined by
// " | " (e.g. "GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT");
// any bits that don't match a known flag are appended as hex.
// Returns "0" for a value of 0.
std::string FormatBitfield(uint32_t value);


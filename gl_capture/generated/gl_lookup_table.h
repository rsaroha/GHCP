// GENERATED FILE - do not edit by hand. See codegen/generate.py
#pragma once

// Returns our wrapper's address for a known GL/WGL function name,
// or nullptr if `name` isn't one we know about (caller should leave
// that import/lookup untouched in that case).
void* LookupWrapper(const char* name);


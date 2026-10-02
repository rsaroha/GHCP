#!/usr/bin/env python3
"""Generates trace/replay glue code from functions.json.

functions.json is the source of truth for which GL functions the
interceptor/replay tool know about. Re-run this script after editing it:

    python generate.py

Output lands in gl_capture/generated/ and is checked into the repo (it's
generated but small and reviewable, and this avoids wiring Python into the
CMake build).
"""
import json
import os

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
OUT = os.path.join(ROOT, "generated")

# type -> (is_pointer, byte size for value types)
VALUE_SIZES = {
    "GLenum": 4, "GLboolean": 1, "GLbitfield": 4,
    "GLint": 4, "GLuint": 4, "GLsizei": 4,
    "GLfloat": 4, "GLdouble": 8,
    "GLbyte": 1, "GLshort": 2, "GLushort": 2, "GLubyte": 1,
    "GLuint64": 8, "GLintptr": 8, "GLsizeiptr": 8, "GLsync": 8,
}


def is_pointer(t):
    return "*" in t


def load():
    with open(os.path.join(HERE, "functions.json")) as f:
        return json.load(f)


def sig_params(fn):
    return ", ".join(f'{p["t"]} {p["n"]}' for p in fn["params"]) or "void"


def sig_types(fn):
    return ", ".join(p["t"] for p in fn["params"]) or "void"


def call_args(fn):
    return ", ".join(p["n"] for p in fn["params"])


def gen_ids(funcs):
    lines = []
    lines.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    lines.append("#pragma once")
    lines.append("#include <cstdint>")
    lines.append("")
    lines.append("enum class GLFuncId : uint16_t {")
    for fn in funcs:
        lines.append(f'    {fn["name"]},')
    lines.append("    Count")
    lines.append("};")
    lines.append("")
    lines.append("extern const char* const kGLFuncNames[];")
    lines.append("")
    with open(os.path.join(OUT, "gl_ids.h"), "w") as f:
        f.write("\n".join(lines) + "\n")

    lines = ['#include "gl_ids.h"', "", "const char* const kGLFuncNames[] = {"]
    for fn in funcs:
        lines.append(f'    "{fn["name"]}",')
    lines.append("};")
    with open(os.path.join(OUT, "gl_ids.cpp"), "w") as f:
        f.write("\n".join(lines) + "\n")


def gen_real_table(funcs):
    h = []
    h.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    h.append("#pragma once")
    h.append('#include "gl_types_min.h"')
    h.append("")
    h.append("#ifndef APIENTRYGEN")
    h.append("#define APIENTRYGEN APIENTRY")
    h.append("#endif")
    h.append("")
    for fn in funcs:
        ret = fn.get("ret", "void")
        h.append(f'typedef {ret} (APIENTRYGEN *PFN_{fn["name"]})({sig_types(fn)});')
    h.append("")
    h.append("struct RealGLFunctions {")
    for fn in funcs:
        h.append(f'    PFN_{fn["name"]} {fn["name"]} = nullptr;')
    h.append("};")
    h.append("")
    h.append("extern RealGLFunctions g_real;")
    h.append("")
    h.append("// getProcFn: typically wglGetProcAddress (only valid with a current context;")
    h.append("// returns null for GL1.1 core functions, which are resolved from moduleHandle instead).")
    h.append("void LoadRealGLFunctions(void* moduleHandle, void* (*getProcFn)(const char*));")
    h.append("")
    h.append("// Assigns g_real.<name> = addr for whichever known function `name` is --")
    h.append("// used by the IAT patcher (for statically-imported names) and by the")
    h.append("// hooked wglGetProcAddress (for extension names resolved at runtime).")
    h.append("// No-op if `name` isn't one of the known functions.")
    h.append("void StoreRealPointer(const char* name, void* addr);")
    h.append("")
    with open(os.path.join(OUT, "gl_real_table.h"), "w") as f:
        f.write("\n".join(h) + "\n")

    c = []
    c.append("#include <windows.h>")
    c.append('#include "gl_real_table.h"')
    c.append("#include <cstring>")
    c.append("")
    c.append("RealGLFunctions g_real;")
    c.append("")
    c.append("void LoadRealGLFunctions(void* moduleHandle, void* (*getProcFn)(const char*)) {")
    c.append("    HMODULE mod = (HMODULE)moduleHandle;")
    for fn in funcs:
        name = fn["name"]
        c.append(f'    g_real.{name} = (PFN_{name})GetProcAddress(mod, "{name}");')
        c.append(f'    if (!g_real.{name} && getProcFn) g_real.{name} = (PFN_{name})getProcFn("{name}");')
    c.append("}")
    c.append("")
    c.append("void StoreRealPointer(const char* name, void* addr) {")
    for fn in funcs:
        name = fn["name"]
        c.append(f'    if (strcmp(name, "{name}") == 0) {{ g_real.{name} = (PFN_{name})addr; return; }}')
    c.append("}")
    with open(os.path.join(OUT, "gl_real_table.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def gen_wrappers(funcs):
    """Interceptor-side exported wrapper bodies for non-custom functions."""
    c = []
    c.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    c.append('#include "gl_real_table.h"')
    c.append('#include "gl_ids.h"')
    c.append('#include "trace_writer.h"')
    c.append("")
    c.append("extern TraceWriter g_trace;")
    c.append("")
    for fn in funcs:
        if fn.get("custom"):
            continue
        name = fn["name"]
        ret = fn.get("ret", "void")
        c.append(f'extern "C" {ret} APIENTRYGEN {name}({sig_params(fn)}) {{')
        c.append(f'    auto call = g_trace.BeginCall(GLFuncId::{name});')
        for p in fn["params"]:
            if is_pointer(p["t"]):
                # Generic pointer tracing records presence without retaining
                # an address that is meaningless in a replay process. APIs
                # whose pointed-to data has a discoverable layout are marked
                # custom and serialize that data explicitly.
                c.append(f'    g_trace.WriteVal(call, static_cast<uint8_t>({p["n"]} != nullptr));')
            else:
                if p["t"] not in VALUE_SIZES:
                    raise SystemExit(f"{name}: unsupported non-value param {p}")
                c.append(f'    g_trace.WriteVal(call, {p["n"]});')
        if ret == "void":
            c.append(f'    g_trace.EndCall(call);')
            c.append(f'    if (g_real.{name}) g_real.{name}({call_args(fn)});')
        else:
            c.append(f'    {ret} result = g_real.{name} ? g_real.{name}({call_args(fn)}) : {ret}{{}};')
            if fn.get("ret_id"):
                c.append(f'    g_trace.WriteVal(call, result);')
            c.append(f'    g_trace.EndCall(call);')
            c.append(f'    return result;')
        c.append("}")
        c.append("")
    with open(os.path.join(OUT, "gl_wrappers_generated.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def gen_passthrough_wrappers(funcs):
    """Compatibility output retained for old build layouts.

    Passthrough metadata is now migrated to normal generated wrappers, so
    this translation unit is intentionally empty.
    """
    c = []
    c.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    c.append('#include "gl_real_table.h"')
    c.append("")
    c.append('extern "C" {')
    c.append("")
    c.append('} // extern "C"')
    with open(os.path.join(OUT, "gl_passthrough_wrappers.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def gen_custom_stub_header(funcs):
    """Declares the hand-written custom wrapper functions, so dllmain/exports
    can reference them, and documents the expected signature."""
    h = []
    h.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    h.append("// Hand-written implementations live in interceptor/custom_wrappers.cpp")
    h.append("#pragma once")
    h.append('#include "gl_types_min.h"')
    h.append('#include "gl_real_table.h"  // defines APIENTRYGEN')
    h.append("")
    h.append('extern "C" {')
    for fn in funcs:
        if not fn.get("custom"):
            continue
        ret = fn.get("ret", "void")
        h.append(f'{ret} APIENTRYGEN {fn["name"]}({sig_params(fn)});')
    h.append("}")
    with open(os.path.join(OUT, "gl_custom_wrappers.h"), "w") as f:
        f.write("\n".join(h) + "\n")


def gen_replay_decode(funcs):
    """Replay-side generic decoder for non-custom calls, plus dispatch
    declarations for custom calls (hand-written in replay/custom_replay.cpp)."""
    h = []
    h.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    h.append("#pragma once")
    h.append('#include "gl_ids.h"')
    h.append('#include "id_remapper.h"')
    h.append("#include <cstdint>")
    h.append("#include <cstddef>")
    h.append("")
    h.append("// Dispatches one decoded call. `args`/`len` is the raw argument")
    h.append("// blob written by the interceptor for this call.")
    h.append("void ReplayDispatch(GLFuncId id, const uint8_t* args, size_t len, IdRemapper& remap);")
    h.append("")
    h.append('extern "C" {')
    for fn in funcs:
        if not fn.get("custom"):
            continue
        h.append(f'void Replay_{fn["name"]}(const uint8_t* args, size_t len, IdRemapper& remap);')
    h.append("}")
    with open(os.path.join(OUT, "gl_replay_decode.h"), "w") as f:
        f.write("\n".join(h) + "\n")

    c = []
    c.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    c.append('#include "gl_replay_decode.h"')
    c.append('#include "gl_real_table.h"')
    c.append('#include "byte_cursor.h"')
    c.append("")
    c.append("void ReplayDispatch(GLFuncId id, const uint8_t* args, size_t len, IdRemapper& remap) {")
    c.append("    ByteCursor cur{args, len};")
    c.append("    switch (id) {")
    for fn in funcs:
        name = fn["name"]
        if fn.get("custom"):
            c.append(f'    case GLFuncId::{name}: Replay_{name}(args, len, remap); break;')
            continue
        ret = fn.get("ret", "void")
        c.append(f'    case GLFuncId::{name}: {{')
        argnames = []
        for p in fn["params"]:
            t = p["t"]
            var = f'a_{p["n"]}'
            if is_pointer(t):
                c.append(f'        uint8_t {var}_present = cur.Read<uint8_t>();')
                c.append(f'        (void){var}_present;')
                c.append(f'        {t} {var} = nullptr;')
            else:
                c.append(f'        {t} {var} = cur.Read<{t}>();')
            if p.get("id"):
                if name == "glBindFramebuffer" and p["n"] == "fb":
                    c.append(f'        if ({var} != 0 && !remap.Has("framebuffer", {var}) && g_real.glGenFramebuffers) {{')
                    c.append(f'            GLuint realFramebuffer = 0;')
                    c.append(f'            g_real.glGenFramebuffers(1, &realFramebuffer);')
                    c.append(f'            remap.Map("framebuffer", {var}, realFramebuffer);')
                    c.append(f'        }}')
                c.append(f'        {var} = remap.Get("{p.get("ns","")}", {var});')
            argnames.append(var)
        call = f'g_real.{name}({", ".join(argnames)})'
        pointer_names = [f'a_{p["n"]}_present' for p in fn["params"] if is_pointer(p["t"])]
        if ret != "void":
            if pointer_names:
                c.append(f'        {ret} result{{}};')
                c.append('        // Pointer payloads are presence-only until a custom decoder is provided.')
            else:
                c.append(f'        {ret} result = {call};')
            if fn.get("ret_id"):
                c.append(f'        {ret} captured_result = cur.Read<{ret}>();')
                c.append(f'        remap.Map("{"shader" if name=="glCreateShader" else "program"}", captured_result, result);')
        else:
            if pointer_names:
                c.append('        // Pointer payloads are presence-only until a custom decoder is provided.')
            else:
                c.append(f'        {call};')
        c.append('        break;')
        c.append('    }')
    c.append("    default: break;")
    c.append("    }")
    c.append("}")
    with open(os.path.join(OUT, "gl_replay_decode.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


TYPE_FMT = {
    "GLenum": "0x%X", "GLboolean": "%d", "GLbitfield": "0x%X",
    "GLint": "%d", "GLuint": "%u", "GLsizei": "%d",
    "GLfloat": "%g", "GLdouble": "%g",
    "GLbyte": "%d", "GLshort": "%d", "GLushort": "%u", "GLubyte": "%u",
    "GLuint64": "%llu", "GLintptr": "%lld", "GLsizeiptr": "%lld",
    "GLsync": "%p",
}


def gen_format_calls(funcs):
    """Human-readable rendering of each decoded call, for the replay
    call-list viewer window. Mirrors gen_replay_decode's byte layout but
    builds a display string instead of calling the real GL function."""
    h = []
    h.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    h.append("#pragma once")
    h.append('#include "gl_ids.h"')
    h.append("#include <cstdint>")
    h.append("#include <cstddef>")
    h.append("#include <string>")
    h.append("")
    h.append("std::string FormatCall(GLFuncId id, const uint8_t* args, size_t len);")
    h.append("")
    h.append("// Hand-written in replay/custom_format.cpp, for calls with pointer/array args.")
    for fn in funcs:
        if fn.get("custom"):
            h.append(f'std::string Format_{fn["name"]}(const uint8_t* args, size_t len);')
    h.append("")
    with open(os.path.join(OUT, "gl_format_calls.h"), "w") as f:
        f.write("\n".join(h) + "\n")

    c = []
    c.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    c.append('#include "gl_format_calls.h"')
    c.append('#include "gl_enum_names.h"')
    c.append('#include "gl_types_min.h"')
    c.append('#include "byte_cursor.h"')
    c.append("#include <cstdio>")
    c.append("")
    c.append("std::string FormatCall(GLFuncId id, const uint8_t* args, size_t len) {")
    c.append("    ByteCursor cur{args, len};")
    c.append("    char buf[256];")
    c.append("    switch (id) {")
    for fn in funcs:
        name = fn["name"]
        if fn.get("custom"):
            c.append(f'    case GLFuncId::{name}: return Format_{name}(args, len);')
            continue
        ret = fn.get("ret", "void")
        c.append(f'    case GLFuncId::{name}: {{')
        c.append(f'        std::string s = "{name}(";')
        for i, p in enumerate(fn["params"]):
            t, n = p["t"], p["n"]
            sep = ", " if i > 0 else ""
            if is_pointer(t):
                c.append(f'        uint8_t a_{n}_present = cur.Read<uint8_t>();')
                c.append(f'        s += "{sep}{n}="; s += (a_{n}_present ? "present" : "null");')
                continue
            c.append(f'        {t} a_{n} = cur.Read<{t}>();')
            if t == "GLenum":
                c.append(f'        s += "{sep}{n}=";')
                c.append(f'        if (const char* nm = LookupEnumName(a_{n})) s += nm;')
                c.append(f'        else {{ snprintf(buf, sizeof(buf), "0x%X", a_{n}); s += buf; }}')
            elif t == "GLbitfield":
                c.append(f'        s += "{sep}{n}="; s += FormatBitfield(a_{n});')
            else:
                fmt = TYPE_FMT[t]
                c.append(f'        snprintf(buf, sizeof(buf), "{sep}{n}={fmt}", a_{n}); s += buf;')
        c.append('        s += ")";')
        if fn.get("ret_id"):
            fmt = TYPE_FMT[ret]
            c.append(f'        {ret} a_ret = cur.Read<{ret}>();')
            c.append(f'        snprintf(buf, sizeof(buf), " -> {fmt}", a_ret); s += buf;')
        c.append('        return s;')
        c.append('    }')
    c.append('    default: return "?";')
    c.append("    }")
    c.append("}")
    with open(os.path.join(OUT, "gl_format_calls.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def gen_enum_names():
    """Symbolic names for GLenum/GLbitfield values in the call-list viewer
    (e.g. `GL_ARRAY_BUFFER` instead of `0x8892`, `GL_COLOR_BUFFER_BIT |
    GL_DEPTH_BUFFER_BIT` instead of `0x4100`). Built from gl_enums.json,
    itself extracted once from the Khronos gl.xml registry (see the
    extraction snippet in this function's docstring history / commit --
    it's a static, checked-in file, not fetched at generate time).

    Many GL enums share the same numeric value across unrelated purposes
    (e.g. 0 is both GL_POINTS and GL_ZERO), so a single global value->name
    table can occasionally show a plausible-but-wrong name for an
    ambiguous value; full disambiguation would need per-parameter enum
    group tracking, which isn't worth the complexity here.
    """
    with open(os.path.join(HERE, "gl_enums.json")) as f:
        enums = json.load(f)
    enum_table = enums["enum_table"]
    bitmask_table = enums["bitmask_table"]

    h = ["// GENERATED FILE - do not edit by hand. See codegen/generate.py",
         "#pragma once", "#include <cstdint>", "#include <string>", "",
         "// Symbolic name for a GLenum value, or nullptr if unknown.",
         "const char* LookupEnumName(uint32_t value);", "",
         "// Decomposes a GLbitfield into its known flag names joined by",
         "// \" | \" (e.g. \"GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT\");",
         "// any bits that don't match a known flag are appended as hex.",
         "// Returns \"0\" for a value of 0.",
         "std::string FormatBitfield(uint32_t value);", ""]
    with open(os.path.join(OUT, "gl_enum_names.h"), "w") as f:
        f.write("\n".join(h) + "\n")

    c = ["// GENERATED FILE - do not edit by hand. See codegen/generate.py",
         '#include "gl_enum_names.h"',
         "#include <cstdio>", "#include <unordered_map>", ""]
    c.append("namespace {")
    c.append("const std::unordered_map<uint32_t, const char*> kEnumNames = {")
    for val_str, name in enum_table.items():
        c.append(f'    {{ {val_str}u, "{name}" }},')
    c.append("};")
    c.append("struct BitFlag { uint32_t value; const char* name; };")
    c.append("const BitFlag kBitFlags[] = {")
    for val_str, name in bitmask_table.items():
        if int(val_str) == 0:
            continue
        c.append(f'    {{ {val_str}u, "{name}" }},')
    c.append("};")
    c.append("} // namespace")
    c.append("")
    c.append("const char* LookupEnumName(uint32_t value) {")
    c.append("    auto it = kEnumNames.find(value);")
    c.append("    return it == kEnumNames.end() ? nullptr : it->second;")
    c.append("}")
    c.append("")
    c.append("std::string FormatBitfield(uint32_t value) {")
    c.append("    if (value == 0) return \"0\";")
    c.append("    std::string s;")
    c.append("    uint32_t remaining = value;")
    c.append("    for (const auto& flag : kBitFlags) {")
    c.append("        if ((remaining & flag.value) == flag.value) {")
    c.append("            if (!s.empty()) s += \" | \";")
    c.append("            s += flag.name;")
    c.append("            remaining &= ~flag.value;")
    c.append("        }")
    c.append("    }")
    c.append("    if (remaining != 0) {")
    c.append("        char buf[16];")
    c.append('        snprintf(buf, sizeof(buf), "0x%X", remaining);')
    c.append("        if (!s.empty()) s += \" | \";")
    c.append("        s += buf;")
    c.append("    }")
    c.append("    return s;")
    c.append("}")
    with open(os.path.join(OUT, "gl_enum_names.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def gen_all_prototypes(funcs):
    """One prototype per known function (custom, generated, and passthrough
    alike), so gl_lookup_table.cpp can take each wrapper's address without
    needing to see its full definition."""
    h = []
    h.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    h.append("#pragma once")
    h.append('#include "gl_types_min.h"')
    h.append('#include "gl_real_table.h"  // defines APIENTRYGEN')
    h.append("")
    h.append('extern "C" {')
    for fn in funcs:
        ret = fn.get("ret", "void")
        h.append(f'{ret} APIENTRYGEN {fn["name"]}({sig_params(fn)});')
    h.append("}")
    with open(os.path.join(OUT, "gl_all_prototypes.h"), "w") as f:
        f.write("\n".join(h) + "\n")


def gen_lookup_table(funcs):
    """Maps a function name to our wrapper's address -- used both by the
    IAT patcher (to redirect statically-imported entries) and by the
    hooked wglGetProcAddress (to hand back our wrapper instead of the real
    address for names fetched dynamically)."""
    h = ["// GENERATED FILE - do not edit by hand. See codegen/generate.py",
         "#pragma once", "",
         "// Returns our wrapper's address for a known GL/WGL function name,",
         "// or nullptr if `name` isn't one we know about (caller should leave",
         "// that import/lookup untouched in that case).",
         "void* LookupWrapper(const char* name);", ""]
    with open(os.path.join(OUT, "gl_lookup_table.h"), "w") as f:
        f.write("\n".join(h) + "\n")

    c = []
    c.append("// GENERATED FILE - do not edit by hand. See codegen/generate.py")
    c.append('#include "gl_lookup_table.h"')
    c.append('#include "gl_all_prototypes.h"')
    c.append("#include <cstring>")
    c.append("")
    c.append("void* LookupWrapper(const char* name) {")
    for fn in funcs:
        name = fn["name"]
        c.append(f'    if (strcmp(name, "{name}") == 0) return (void*)&{name};')
    c.append("    return nullptr;")
    c.append("}")
    with open(os.path.join(OUT, "gl_lookup_table.cpp"), "w") as f:
        f.write("\n".join(c) + "\n")


def main():
    os.makedirs(OUT, exist_ok=True)
    funcs = load()
    gen_ids(funcs)
    gen_real_table(funcs)
    gen_wrappers(funcs)
    gen_passthrough_wrappers(funcs)
    gen_custom_stub_header(funcs)
    gen_replay_decode(funcs)
    gen_enum_names()
    gen_format_calls(funcs)
    gen_all_prototypes(funcs)
    gen_lookup_table(funcs)
    print(f"Generated {len(funcs)} functions -> {OUT}")


if __name__ == "__main__":
    main()

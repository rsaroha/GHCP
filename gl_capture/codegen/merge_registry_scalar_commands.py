#!/usr/bin/env python3
"""Add replay-safe scalar void commands from registry metadata.

Pointer-bearing and result-returning commands stay out of the active table
until their byte-count, output, and object-remapping policies are implemented.
"""
import json
from pathlib import Path

HERE = Path(__file__).resolve().parent
FUNCTIONS = HERE / "functions.json"
REGISTRY = HERE / "registry_commands.json"

VALUE_TYPES = {
    "GLenum", "GLboolean", "GLbitfield", "GLint", "GLuint", "GLsizei",
    "GLfloat", "GLdouble", "GLbyte", "GLshort", "GLushort", "GLubyte",
    "GLuint64", "GLintptr", "GLsizeiptr", "GLsync",
}


def main():
    functions = json.loads(FUNCTIONS.read_text())
    existing = {fn["name"] for fn in functions}
    registry = json.loads(REGISTRY.read_text())["commands"]
    added = []
    for command in registry:
        if command["name"] in existing or command["return_type"] != "void":
            continue
        if any(param["pointer"] or param["type"] not in VALUE_TYPES
               for param in command["params"]):
            continue
        functions.append({
            "name": command["name"],
            "params": [
                {"n": param["name"], "t": param["type"]}
                for param in command["params"]
            ],
            "registry_scalar": True,
        })
        added.append(command["name"])

    FUNCTIONS.write_text(json.dumps(functions, indent=2) + "\n")
    print(f"Added {len(added)} registry scalar commands to {FUNCTIONS}")


if __name__ == "__main__":
    main()

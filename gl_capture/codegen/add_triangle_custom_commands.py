#!/usr/bin/env python3
import json
from pathlib import Path

p = Path(__file__).resolve().parent / "functions.json"
data = json.loads(p.read_text())
names = {
    "glClearBufferfv", "glCreateBuffers", "glCreateFramebuffers",
    "glCreateRenderbuffers", "glCreateTextures", "glCreateVertexArrays",
    "glDebugMessageInsert", "glGetProgramInfoLog", "glGetShaderInfoLog",
    "glNamedBufferStorage", "glNamedBufferSubData",
    "glNamedFramebufferDrawBuffers", "glTextureSubImage2D",
    "glTextureSubImage3D",
}
registry = {
    x["name"]: x for x in json.loads(
        (p.parent / "registry_commands.json").read_text()
    )["commands"]
}
existing = {x["name"] for x in data}
for name in sorted(names - existing):
    command = registry[name]
    data.append({
        "name": name,
        "params": [{"n": x["name"], "t": x["type"]} for x in command["params"]],
        "custom": True,
    })
p.write_text(json.dumps(data, indent=2) + "\n")
print(f"Added {len(names - existing)} custom commands")

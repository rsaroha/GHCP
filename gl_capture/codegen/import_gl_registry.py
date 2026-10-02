#!/usr/bin/env python3
"""Import desktop OpenGL 1.0-4.6 commands from Khronos gl.xml.

The generated JSON is metadata for the typed trace generator. It intentionally
does not emit wrappers yet: pointer direction and byte-count rules must be
reviewed before a command can be replayed safely.
"""
import json
import sys
import xml.etree.ElementTree as ET
from pathlib import Path

HERE = Path(__file__).resolve().parent
REGISTRY = HERE / "gl.xml"
OUTPUT = HERE / "registry_commands.json"


def type_text(node):
    ptype = node.find("ptype")
    if ptype is None:
        return (node.text or "").strip()
    return ((node.text or "") + (ptype.text or "") + (ptype.tail or "")).strip()


def command_info(command):
    proto = command.find("proto")
    name = proto.findtext("name")
    ret = type_text(proto)
    params = []
    for param in command.findall("param"):
        param_name = param.findtext("name")
        param_type = type_text(param)
        pointer = "*" in param_type
        params.append({
            "name": param_name,
            "type": param_type,
            "pointer": pointer,
            "const": "const" in param_type,
            "len": param.get("len"),
            "altlen": param.get("altlen"),
            "optional": param.get("optional") == "true",
            "group": param.get("group"),
        })
    return {"name": name, "return_type": ret, "params": params}


def main():
    if not REGISTRY.exists():
        raise SystemExit(f"missing registry: {REGISTRY}")
    root = ET.parse(REGISTRY).getroot()
    selected = {}
    for feature in root.findall("feature"):
        if feature.get("api") != "gl":
            continue
        try:
            version = float(feature.get("number", "0"))
        except ValueError:
            continue
        if not 1.0 <= version <= 4.6:
            continue
        for require in feature.findall("require"):
            for command in require.findall("command"):
                name = command.get("name")
                if name:
                    selected[name] = version

    commands = {c.findtext("proto/name"): c for c in root.findall("./commands/command")}
    result = []
    for name in sorted(selected):
        command = commands.get(name)
        if command is None:
            continue
        info = command_info(command)
        info["introduced_in"] = selected[name]
        result.append(info)

    OUTPUT.write_text(json.dumps({
        "source": "Khronos OpenGL Registry gl.xml",
        "scope": "desktop OpenGL 1.0-4.6 core and compatibility profiles",
        "commands": result,
    }, indent=2) + "\n")
    print(f"Imported {len(result)} desktop OpenGL commands -> {OUTPUT}")


if __name__ == "__main__":
    main()

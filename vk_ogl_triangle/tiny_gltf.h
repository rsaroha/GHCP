#pragma once
// Stub for tiny_gltf.h - minimal compatibility
#include <vector>
#include <string>
#include <map>
namespace tinygltf {
    struct Accessor {};
    struct Mesh {};
    struct Node {};
    struct Model {
        std::vector<Mesh> meshes;
        std::vector<Node> nodes;
        std::vector<Accessor> accessors;
    };
    bool LoadASCIIFromFile(Model*, const char*) { return false; }
    bool LoadBinaryFromFile(Model*, const char*) { return false; }
}

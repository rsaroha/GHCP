#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_IMPLEMENTATION
#include <tiny_gltf.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "mesh_loader.h"
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <tuple>

bool parseMeshGltf(const std::string& path,
                   std::vector<Vertex>& verts,
                   std::vector<uint32_t>& idxs,
                   std::string& error)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err, warn;

    bool ok = (path.size() >= 4 && path.substr(path.size() - 4) == ".glb")
        ? loader.LoadBinaryFromFile(&model, &err, &warn, path)
        : loader.LoadASCIIFromFile(&model, &err, &warn, path);

    if (!ok) { error = err.empty() ? "Failed to load" : err; return false; }
    if (model.meshes.empty()) { error = "No meshes found"; return false; }

    auto& prim = model.meshes[0].primitives[0];

    // ── POSITION ──────────────────────────────────────────────────────────────
    auto posIt = prim.attributes.find("POSITION");
    if (posIt == prim.attributes.end()) { error = "No POSITION attribute"; return false; }
    auto& posAcc  = model.accessors[posIt->second];
    auto& posView = model.bufferViews[posAcc.bufferView];
    const uint8_t* posPtr = model.buffers[posView.buffer].data.data()
                          + posView.byteOffset + posAcc.byteOffset;
    int posStride = posView.byteStride ? (int)posView.byteStride : 12;

    verts.resize(posAcc.count);
    for (size_t i = 0; i < posAcc.count; i++) {
        const float* p = reinterpret_cast<const float*>(posPtr + i * posStride);
        verts[i] = {{ p[0], p[1], p[2] }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }};
    }

    // ── NORMAL ────────────────────────────────────────────────────────────────
    auto nrmIt = prim.attributes.find("NORMAL");
    if (nrmIt != prim.attributes.end()) {
        auto& nrmAcc  = model.accessors[nrmIt->second];
        auto& nrmView = model.bufferViews[nrmAcc.bufferView];
        const uint8_t* nrmPtr = model.buffers[nrmView.buffer].data.data()
                              + nrmView.byteOffset + nrmAcc.byteOffset;
        int nrmStride = nrmView.byteStride ? (int)nrmView.byteStride : 12;
        for (size_t i = 0; i < nrmAcc.count && i < verts.size(); i++) {
            const float* n = reinterpret_cast<const float*>(nrmPtr + i * nrmStride);
            verts[i].nrm[0] = n[0]; verts[i].nrm[1] = n[1]; verts[i].nrm[2] = n[2];
        }
    }

    // ── TEXCOORD_0 ────────────────────────────────────────────────────────────
    auto uvIt = prim.attributes.find("TEXCOORD_0");
    if (uvIt != prim.attributes.end()) {
        auto& uvAcc  = model.accessors[uvIt->second];
        auto& uvView = model.bufferViews[uvAcc.bufferView];
        const uint8_t* uvPtr = model.buffers[uvView.buffer].data.data()
                             + uvView.byteOffset + uvAcc.byteOffset;
        for (size_t i = 0; i < uvAcc.count && i < verts.size(); i++) {
            if (uvAcc.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT) {
                int stride = uvView.byteStride ? (int)uvView.byteStride : 8;
                const float* t = reinterpret_cast<const float*>(uvPtr + i * stride);
                verts[i].uv[0] = t[0];
                verts[i].uv[1] = t[1];
            } else if (uvAcc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE) {
                int stride = uvView.byteStride ? (int)uvView.byteStride : 2;
                const uint8_t* t = uvPtr + i * stride;
                verts[i].uv[0] = t[0] / 255.0f;
                verts[i].uv[1] = t[1] / 255.0f;
            } else if (uvAcc.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                int stride = uvView.byteStride ? (int)uvView.byteStride : 4;
                const uint16_t* t = reinterpret_cast<const uint16_t*>(uvPtr + i * stride);
                verts[i].uv[0] = t[0] / 65535.0f;
                verts[i].uv[1] = t[1] / 65535.0f;
            }
        }
    }

    // ── INDICES ───────────────────────────────────────────────────────────────
    if (prim.indices >= 0) {
        auto& idxAcc  = model.accessors[prim.indices];
        auto& idxView = model.bufferViews[idxAcc.bufferView];
        const uint8_t* idxPtr = model.buffers[idxView.buffer].data.data()
                              + idxView.byteOffset + idxAcc.byteOffset;
        idxs.resize(idxAcc.count);
        for (size_t i = 0; i < idxAcc.count; i++) {
            switch (idxAcc.componentType) {
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
                idxs[i] = idxPtr[i]; break;
            case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
                idxs[i] = reinterpret_cast<const uint16_t*>(idxPtr)[i]; break;
            default:
                idxs[i] = reinterpret_cast<const uint32_t*>(idxPtr)[i]; break;
            }
        }
    } else {
        idxs.resize(verts.size());
        std::iota(idxs.begin(), idxs.end(), 0u);
    }

    // ── Per-face normal generation if NORMAL was absent ───────────────────────
    if (nrmIt == prim.attributes.end()) {
        for (size_t i = 0; i + 2 < idxs.size(); i += 3) {
            uint32_t i0 = idxs[i], i1 = idxs[i+1], i2 = idxs[i+2];
            float* p0 = verts[i0].pos; float* p1 = verts[i1].pos; float* p2 = verts[i2].pos;
            float e1[3] = {p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2]};
            float e2[3] = {p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2]};
            float fn[3] = { e1[1]*e2[2]-e1[2]*e2[1], e1[2]*e2[0]-e1[0]*e2[2], e1[0]*e2[1]-e1[1]*e2[0] };
            for (uint32_t idx : {i0, i1, i2}) {
                verts[idx].nrm[0]+=fn[0]; verts[idx].nrm[1]+=fn[1]; verts[idx].nrm[2]+=fn[2];
            }
        }
        for (auto& v : verts) {
            float len = std::sqrt(v.nrm[0]*v.nrm[0]+v.nrm[1]*v.nrm[1]+v.nrm[2]*v.nrm[2]);
            if (len > 1e-6f) { v.nrm[0]/=len; v.nrm[1]/=len; v.nrm[2]/=len; }
        }
    }

    error.clear();
    return true;
}

bool parseMeshObj(const std::string& path,
                  std::vector<Vertex>& verts,
                  std::vector<uint32_t>& idxs,
                  std::string& error)
{
    tinyobj::ObjReaderConfig cfg; cfg.triangulate = true;
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(path, cfg)) {
        error = reader.Error().empty() ? "OBJ parse failed" : reader.Error();
        return false;
    }
    if (!reader.Warning().empty())
        std::cerr << "OBJ warning: " << reader.Warning() << "\n";

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();

    bool hasNrm = !attrib.normals.empty();
    bool hasTex = !attrib.texcoords.empty();

    // OBJ uses separate indices per attribute — rebuild a unified vertex list
    using Key = std::tuple<int,int,int>;   // (pos_idx, nrm_idx, tex_idx)
    std::map<Key, uint32_t> cache;

    for (auto& shape : shapes) {
        for (auto& idx : shape.mesh.indices) {
            int ni = (hasNrm && idx.normal_index >= 0)    ? idx.normal_index    : -1;
            int ti = (hasTex && idx.texcoord_index >= 0)  ? idx.texcoord_index  : -1;
            Key k{idx.vertex_index, ni, ti};
            auto it = cache.find(k);
            if (it == cache.end()) {
                Vertex v{};
                int vi = idx.vertex_index;
                v.pos[0] = attrib.vertices[3*vi+0];
                v.pos[1] = attrib.vertices[3*vi+1];
                v.pos[2] = attrib.vertices[3*vi+2];
                if (ni >= 0) {
                    v.nrm[0] = attrib.normals[3*ni+0];
                    v.nrm[1] = attrib.normals[3*ni+1];
                    v.nrm[2] = attrib.normals[3*ni+2];
                }
                if (ti >= 0) {
                    v.uv[0] = attrib.texcoords[2*ti+0];
                    v.uv[1] = 1.0f - attrib.texcoords[2*ti+1];  // flip Y for OpenGL convention
                }
                uint32_t newIdx = (uint32_t)verts.size();
                verts.push_back(v);
                cache[k] = newIdx;
                idxs.push_back(newIdx);
            } else {
                idxs.push_back(it->second);
            }
        }
    }

    // If no normals in the file, compute smooth per-face normals
    if (!hasNrm) {
        for (size_t i = 0; i + 2 < idxs.size(); i += 3) {
            uint32_t i0 = idxs[i], i1 = idxs[i+1], i2 = idxs[i+2];
            float* p0 = verts[i0].pos; float* p1 = verts[i1].pos; float* p2 = verts[i2].pos;
            float e1[3] = {p1[0]-p0[0], p1[1]-p0[1], p1[2]-p0[2]};
            float e2[3] = {p2[0]-p0[0], p2[1]-p0[1], p2[2]-p0[2]};
            float fn[3] = { e1[1]*e2[2]-e1[2]*e2[1], e1[2]*e2[0]-e1[0]*e2[2], e1[0]*e2[1]-e1[1]*e2[0] };
            for (uint32_t idx : {i0, i1, i2}) {
                verts[idx].nrm[0]+=fn[0]; verts[idx].nrm[1]+=fn[1]; verts[idx].nrm[2]+=fn[2];
            }
        }
        for (auto& v : verts) {
            float len = std::sqrt(v.nrm[0]*v.nrm[0]+v.nrm[1]*v.nrm[1]+v.nrm[2]*v.nrm[2]);
            if (len > 1e-6f) { v.nrm[0]/=len; v.nrm[1]/=len; v.nrm[2]/=len; }
        }
    }

    error.clear();
    return true;
}

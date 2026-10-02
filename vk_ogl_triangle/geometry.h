#pragma once

#include <array>
#include <cmath>
#include <vector>
#include <cstdint>

#include "config.h"
#include "math_types.h"

// ─── Geometry ────────────────────────────────────────────────────────────────
struct Vertex { float pos[3]; float nrm[3]; float uv[2]; };  // 32 bytes

inline constexpr Vertex CUBE_VERTS[] = {
    {{-0.5f,-0.5f,-0.5f}},   // 0
    {{ 0.5f,-0.5f,-0.5f}},   // 1
    {{ 0.5f, 0.5f,-0.5f}},   // 2
    {{-0.5f, 0.5f,-0.5f}},   // 3
    {{-0.5f,-0.5f, 0.5f}},   // 4
    {{ 0.5f,-0.5f, 0.5f}},   // 5
    {{ 0.5f, 0.5f, 0.5f}},   // 6
    {{-0.5f, 0.5f, 0.5f}},   // 7
};
inline constexpr uint16_t CUBE_IDX[] = {
    4,5,6, 4,6,7,   // front  (+Z)
    1,0,3, 1,3,2,   // back   (-Z)
    0,4,7, 0,7,3,   // left   (-X)
    5,1,2, 5,2,6,   // right  (+X)
    7,6,2, 7,2,3,   // top    (+Y)
    0,1,5, 0,5,4,   // bottom (-Y)
};

// Generate a rounded cube with adaptive tessellation:
//   - More triangles near the curved edges/corners (high curvature)
//   - Fewer triangles on the flat face centers (low curvature)
// N  = subdivision count per face edge (total grid per face = N×N quads)
// r  = corner radius (0 = sharp cube, ~0.48 = nearly sphere)
// edgeBias = power exponent for parameter remapping (< 1 concentrates verts at edges)
inline void generateRoundedCube(std::vector<Vertex>& verts,
                                 std::vector<uint16_t>& idxs,
                                 int N = 20, float r = 0.10f,
                                 float edgeBias = 0.38f)
{
    verts.clear(); idxs.clear();

    // Remap a linear parameter t ∈ [-1,1] so samples cluster near ±1 (the face edges).
    // edgeBias < 1: pushes values outward → dense at edges, sparse at center.
    auto bias = [edgeBias](float t) -> float {
        return t >= 0.0f ?  std::pow( t, edgeBias)
                         : -std::pow(-t, edgeBias);
    };

    // 6 faces defined by (right, up, outward-normal) axes
    struct Face { float rx,ry,rz, ux,uy,uz, nx,ny,nz; };
    const Face faces[6] = {
        { 0, 0,-1,  0, 1, 0,  1, 0, 0 },  // +X
        { 0, 0, 1,  0, 1, 0, -1, 0, 0 },  // -X
        { 1, 0, 0,  0, 0,-1,  0, 1, 0 },  // +Y
        { 1, 0, 0,  0, 0, 1,  0,-1, 0 },  // -Y
        { 1, 0, 0,  0, 1, 0,  0, 0, 1 },  // +Z
        {-1, 0, 0,  0, 1, 0,  0, 0,-1 },  // -Z
    };

    const float s     = 0.5f;
    const float inner = s - r;

    for (const auto& f : faces) {
        auto base = (uint16_t)verts.size();

        for (int j = 0; j <= N; j++) {
            for (int i = 0; i <= N; i++) {
                // Linear params in [-1, 1], then bias toward ±1
                float u = bias((float)i / N * 2.0f - 1.0f);
                float v = bias((float)j / N * 2.0f - 1.0f);

                // Flat point on the cube face
                float px = f.rx*u*s + f.ux*v*s + f.nx*s;
                float py = f.ry*u*s + f.uy*v*s + f.ny*s;
                float pz = f.rz*u*s + f.uz*v*s + f.nz*s;

                // Nearest point on inner box (clamp each axis)
                float cx = px < -inner ? -inner : (px > inner ? inner : px);
                float cy = py < -inner ? -inner : (py > inner ? inner : py);
                float cz = pz < -inner ? -inner : (pz > inner ? inner : pz);

                // Push outward from inner box surface by radius r
                float dx = px - cx, dy = py - cy, dz = pz - cz;
                float len = std::sqrt(dx*dx + dy*dy + dz*dz);

                float fx, fy, fz, nx, ny, nz;
                if (len > 1e-6f) {
                    float inv = 1.0f / len;
                    fx = cx + dx*inv * r;  fy = cy + dy*inv * r;  fz = cz + dz*inv * r;
                    nx = dx*inv;           ny = dy*inv;           nz = dz*inv;
                } else {
                    // Degenerate: fall back to the face normal direction
                    fx = px; fy = py; fz = pz;
                    nx = f.nx; ny = f.ny; nz = f.nz;
                }

                float tu = (u + 1.0f) * 0.5f;
                float tv = (v + 1.0f) * 0.5f;
                verts.push_back({{fx, fy, fz}, {nx, ny, nz}, {tu, tv}});
            }
        }

        // Two triangles per quad
        for (int j = 0; j < N; j++) {
            for (int i = 0; i < N; i++) {
                uint16_t a = base + (uint16_t)(j * (N+1) + i);
                uint16_t b = a + 1;
                uint16_t c = a + (uint16_t)(N+1);
                uint16_t d = c + 1;
                idxs.push_back(a); idxs.push_back(b); idxs.push_back(d);
                idxs.push_back(a); idxs.push_back(d); idxs.push_back(c);
            }
        }
    }
}

// Shared material description (used as default and per-cube override)
struct Material {
    float color[3]  = {0.80f, 0.80f, 0.82f};
    float alpha     = 1.0f;     // opacity (OIT)
    float ambient   = 0.32f;
    float diffuse   = 0.68f;
    float specular  = 0.8f;
    float shininess = 128.0f;
    int   materialType = 0;     // MAT_* constant
    float p0 = 0.0f;            // material-type-specific params
    float p1 = 0.0f;
    float p2 = 0.0f;
    float p3 = 0.0f;
};

// Per-instance data: world transform + material (116 bytes)
struct InstanceData {
    Mat4  transform;      // 64 bytes, offset 0
    float color[4];       // 16 bytes, offset 64  (rgb + alpha)
    float ambient;        //  4 bytes, offset 80
    float diffuse;        //  4 bytes, offset 84
    float specular;       //  4 bytes, offset 88
    float shininess;      //  4 bytes, offset 92
    int   materialType;   //  4 bytes, offset 96  (MAT_*)
    float p0, p1, p2, p3; // 16 bytes, offset 100 (type-specific params)
};
static_assert(sizeof(InstanceData) == 116);

inline Mat4 translation(float x, float y, float z) {
    Mat4 m{}; m[0]=m[5]=m[10]=m[15]=1.0f;
    m[12]=x; m[13]=y; m[14]=z;
    return m;
}

// HSV → RGB helper for generating distinct per-cube colors
inline std::array<float,3> hsvToRgb(float h, float s, float v) {
    float r = 0, g = 0, b = 0;
    int   i = (int)(h * 6.0f);
    float f = h * 6.0f - i;
    float p = v * (1.0f - s);
    float q = v * (1.0f - f * s);
    float t = v * (1.0f - (1.0f - f) * s);
    switch (i % 6) {
        case 0: r=v; g=t; b=p; break;
        case 1: r=q; g=v; b=p; break;
        case 2: r=p; g=v; b=t; break;
        case 3: r=p; g=q; b=v; break;
        case 4: r=t; g=p; b=v; break;
        case 5: r=v; g=p; b=q; break;
    }
    return {r, g, b};
}

// 100 instance records placed on a Fibonacci sphere, all sharing the same material
inline std::array<InstanceData, INSTANCE_COUNT> buildInstanceData(const Material& mat = {}) {
    std::array<InstanceData, INSTANCE_COUNT> data;
    const float golden = (1.0f + std::sqrt(5.0f)) / 2.0f;
    const float pi = 3.14159265358979f;
    for (int i = 0; i < INSTANCE_COUNT; ++i) {
        float theta = 2.0f * pi * (float)i / golden;
        float phi   = std::acos(1.0f - 2.0f * (i + 0.5f) / INSTANCE_COUNT);
        float x = SPHERE_RADIUS * std::sin(phi) * std::cos(theta);
        float y = SPHERE_RADIUS * std::sin(phi) * std::sin(theta);
        float z = SPHERE_RADIUS * std::cos(phi);
        data[i].transform  = translation(x, y, z);
        data[i].color[0]   = mat.color[0];
        data[i].color[1]   = mat.color[1];
        data[i].color[2]   = mat.color[2];
        data[i].color[3]      = mat.alpha;
        data[i].ambient       = mat.ambient;
        data[i].diffuse       = mat.diffuse;
        data[i].specular      = mat.specular;
        data[i].shininess     = mat.shininess;
        data[i].materialType  = mat.materialType;
        data[i].p0            = mat.p0;
        data[i].p1            = mat.p1;
        data[i].p2            = mat.p2;
        data[i].p3            = mat.p3;
    }
    return data;
}

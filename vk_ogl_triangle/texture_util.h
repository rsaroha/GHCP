#pragma once
// CPU-side image loading and IBL precomputation utilities.
// stb_image implementation lives in stb_image_impl.cpp.
// tinyexr implementation lives in tinyexr_impl.cpp.

// Suppress Windows min/max macros that break std::min/max/clamp
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <stb_image.h>
#include <tinyexr.h>

#include <cmath>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

// ─── Simple float3 ────────────────────────────────────────────────────────────
struct F3 { float x, y, z; };
static inline F3    f3(float x, float y, float z) { return {x, y, z}; }
static inline F3    f3add(F3 a, F3 b) { return {a.x+b.x, a.y+b.y, a.z+b.z}; }
static inline F3    f3mul(F3 a, float s) { return {a.x*s, a.y*s, a.z*s}; }
static inline float f3dot(F3 a, F3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
static inline F3    f3norm(F3 v) { float l = std::sqrt(f3dot(v,v)); return l > 0 ? f3mul(v, 1.f/l) : v; }

// ─── Image data ───────────────────────────────────────────────────────────────
struct TexImage {
    int w = 0, h = 0;
    std::vector<float> data;  // RGBA32F, w*h*4 floats
};

// Up to 6 faces, each size*size*4 floats (RGBA32F)
struct CubeImage {
    int size = 0;
    std::vector<float> faces[6];
};

// ─── Load LDR image (PNG/JPG etc) → RGBA32F ──────────────────────────────────
inline TexImage loadImageLDR(const char* path) {
    TexImage out;
    int c;
    stbi_set_flip_vertically_on_load(0);
    unsigned char* px = stbi_load(path, &out.w, &out.h, &c, 4);
    if (!px) return {};
    out.data.resize((size_t)out.w * out.h * 4);
    for (size_t i = 0; i < out.data.size(); i++)
        out.data[i] = px[i] / 255.f;
    stbi_image_free(px);
    return out;
}

// ─── Load EXR image → RGBA32F (via tinyexr) ──────────────────────────────────
inline TexImage loadImageEXR(const char* path) {
    float* rgba = nullptr; int w, h;
    const char* err = nullptr;
    int ret = LoadEXR(&rgba, &w, &h, path, &err);
    if (ret != TINYEXR_SUCCESS) {
        if (err) FreeEXRErrorMessage(err);
        return {};
    }
    TexImage out; out.w = w; out.h = h;
    out.data.assign(rgba, rgba + (size_t)w * h * 4);
    free(rgba);
    return out;
}

// ─── Load HDR image (.hdr or .exr equirectangular) → RGBA32F ─────────────────
inline TexImage loadImageHDR(const char* path) {
    // Dispatch .exr to tinyexr, everything else to stb_image
    std::string s(path);
    auto dot = s.rfind('.');
    if (dot != std::string::npos) {
        std::string ext = s.substr(dot + 1);
        for (auto& c : ext) c = (char)std::tolower((unsigned char)c);
        if (ext == "exr") return loadImageEXR(path);
    }
    TexImage out;
    int c;
    stbi_set_flip_vertically_on_load(0);
    float* px = stbi_loadf(path, &out.w, &out.h, &c, 4);
    if (!px) return {};
    out.data.assign(px, px + (size_t)out.w * out.h * 4);
    stbi_image_free(px);
    return out;
}

// ─── Equirectangular direction helpers ────────────────────────────────────────
static constexpr float F_PI = 3.14159265f;

static inline F3 equirectDir(float u, float v) {
    float phi   = (1.f - v) * F_PI;
    float theta = u * 2.f * F_PI - F_PI;
    return {std::sin(phi)*std::cos(theta), std::cos(phi), std::sin(phi)*std::sin(theta)};
}
static inline void dirToEquirect(F3 d, float& u, float& v) {
    u = (std::atan2(d.z, d.x) + F_PI) / (2.f * F_PI);
    v = 1.f - std::acos((d.y < -1.f ? -1.f : d.y > 1.f ? 1.f : d.y)) / F_PI;
}
static inline F3 sampleEquirect(const TexImage& img, F3 d) {
    float u, v; dirToEquirect(d, u, v);
    float px = u * (img.w - 1), py = v * (img.h - 1);
    int x0 = (int)px, y0 = (int)py;
    int x1 = (x0 + 1 < img.w - 1) ? x0 + 1 : img.w - 1;
    int y1 = (y0 + 1 < img.h - 1) ? y0 + 1 : img.h - 1;
    float fx = px - x0, fy = py - y0;
    auto get = [&](int x, int y) -> F3 {
        const float* p = &img.data[((size_t)y * img.w + x) * 4];
        return {p[0], p[1], p[2]};
    };
    auto lerp = [](F3 a, F3 b, float t) { return f3add(f3mul(a, 1-t), f3mul(b, t)); };
    return lerp(lerp(get(x0,y0), get(x1,y0), fx), lerp(get(x0,y1), get(x1,y1), fx), fy);
}

// ─── Cubemap face directions (+X,-X,+Y,-Y,+Z,-Z) ─────────────────────────────
static inline F3 cubeFaceDir(int face, float s, float t) {
    switch (face) {
    case 0: return f3norm({ 1, t,-s}); // +X
    case 1: return f3norm({-1, t, s}); // -X
    case 2: return f3norm({ s, 1,-t}); // +Y
    case 3: return f3norm({ s,-1, t}); // -Y
    case 4: return f3norm({ s, t, 1}); // +Z
    default:return f3norm({-s, t,-1}); // -Z
    }
}
static inline F3 sampleCubemap(const CubeImage& cube, F3 d) {
    float ax = std::abs(d.x), ay = std::abs(d.y), az = std::abs(d.z);
    int face; float s, t;
    if (ax >= ay && ax >= az) {
        if (d.x > 0) { face = 0; s = -d.z/d.x; t =  d.y/d.x; }
        else          { face = 1; s =  d.z/d.x; t =  d.y/d.x; }
    } else if (ay >= az) {
        if (d.y > 0) { face = 2; s =  d.x/d.y; t = -d.z/d.y; }
        else          { face = 3; s =  d.x/d.y; t =  d.z/d.y; }
    } else {
        if (d.z > 0) { face = 4; s =  d.x/d.z; t =  d.y/d.z; }
        else          { face = 5; s = -d.x/d.z; t =  d.y/d.z; }
    }
    int sz = cube.size;
    float px = (s + 1.f) * 0.5f * (sz - 1), py = (t + 1.f) * 0.5f * (sz - 1);
    int x0 = (int)px; if (x0 < 0) x0 = 0; if (x0 > sz-1) x0 = sz-1;
    int y0 = (int)py; if (y0 < 0) y0 = 0; if (y0 > sz-1) y0 = sz-1;
    int x1 = (x0 + 1 < sz) ? x0 + 1 : sz - 1;
    int y1 = (y0 + 1 < sz) ? y0 + 1 : sz - 1;
    float fx = px - x0, fy = py - y0;
    auto get = [&](int x, int y) -> F3 {
        const float* p = &cube.faces[face][((size_t)y * sz + x) * 4];
        return {p[0], p[1], p[2]};
    };
    auto lerp = [](F3 a, F3 b, float t) { return f3add(f3mul(a, 1-t), f3mul(b, t)); };
    return lerp(lerp(get(x0,y0), get(x1,y0), fx), lerp(get(x0,y1), get(x1,y1), fx), fy);
}

// ─── Equirect → cubemap ───────────────────────────────────────────────────────
inline CubeImage equirectToCubemap(const TexImage& eq, int size) {
    CubeImage cube; cube.size = size;
    for (int f = 0; f < 6; f++) {
        cube.faces[f].resize((size_t)size * size * 4);
        for (int y = 0; y < size; y++) for (int x = 0; x < size; x++) {
            float s = (x + .5f) / size * 2.f - 1.f, t = (y + .5f) / size * 2.f - 1.f;
            F3 d = cubeFaceDir(f, s, t);
            F3 c = sampleEquirect(eq, d);
            float* p = &cube.faces[f][((size_t)y * size + x) * 4];
            p[0] = c.x; p[1] = c.y; p[2] = c.z; p[3] = 1.f;
        }
    }
    return cube;
}

// ─── Hammersley low-discrepancy sequence ─────────────────────────────────────
static inline float radInverse(uint32_t bits) {
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10f;
}
static inline void hammersley(uint32_t i, uint32_t N, float& xi1, float& xi2) {
    xi1 = float(i) / float(N); xi2 = radInverse(i);
}

// ─── GGX importance sampling ─────────────────────────────────────────────────
static inline F3 importanceSampleGGX(float xi1, float xi2, float roughness, F3 N) {
    float a   = roughness * roughness;
    float phi = 2.f * F_PI * xi1;
    float cosT = std::sqrt((1.f - xi2) / (1.f + (a*a - 1.f) * xi2));
    float sinT = std::sqrt(1.f - cosT * cosT);
    F3 H = {sinT * std::cos(phi), sinT * std::sin(phi), cosT};
    F3 up = std::abs(N.z) < 0.999f ? F3{0, 0, 1} : F3{1, 0, 0};
    F3 T = f3norm({up.y*N.z - up.z*N.y, up.z*N.x - up.x*N.z, up.x*N.y - up.y*N.x});
    F3 B = {N.y*T.z - N.z*T.y, N.z*T.x - N.x*T.z, N.x*T.y - N.y*T.x};
    return f3norm({T.x*H.x + B.x*H.y + N.x*H.z,
                   T.y*H.x + B.y*H.y + N.y*H.z,
                   T.z*H.x + B.z*H.y + N.z*H.z});
}

// ─── Irradiance (diffuse IBL) by hemisphere integration ──────────────────────
inline CubeImage computeIrradiance(const CubeImage& env, int irrSize = 32) {
    const int N_PHI = 64, N_THETA = 32;
    CubeImage irr; irr.size = irrSize;
    for (int f = 0; f < 6; f++) {
        irr.faces[f].resize((size_t)irrSize * irrSize * 4, 0.f);
        for (int y = 0; y < irrSize; y++) for (int x = 0; x < irrSize; x++) {
            float s = (x + .5f) / irrSize * 2.f - 1.f, t = (y + .5f) / irrSize * 2.f - 1.f;
            F3 N = cubeFaceDir(f, s, t);
            F3 up = std::abs(N.z) < 0.999f ? F3{0, 0, 1} : F3{1, 0, 0};
            F3 T = f3norm({up.y*N.z - up.z*N.y, up.z*N.x - up.x*N.z, up.x*N.y - up.y*N.x});
            F3 B = {N.y*T.z - N.z*T.y, N.z*T.x - N.x*T.z, N.x*T.y - N.y*T.x};
            F3 acc{0, 0, 0}; float totalW = 0.f;
            for (int ip = 0; ip < N_PHI; ip++) for (int it = 0; it < N_THETA; it++) {
                float phi   = 2.f * F_PI * ip / N_PHI;
                float theta = 0.5f * F_PI * it / N_THETA;
                float sT = std::sin(theta), cT = std::cos(theta);
                float sP = std::sin(phi),   cP = std::cos(phi);
                F3 L = {sT*cP*T.x + sT*sP*B.x + cT*N.x,
                        sT*cP*T.y + sT*sP*B.y + cT*N.y,
                        sT*cP*T.z + sT*sP*B.z + cT*N.z};
                F3 c = sampleCubemap(env, L);
                float w = cT * sT;
                acc.x += c.x * w; acc.y += c.y * w; acc.z += c.z * w; totalW += w;
            }
            float sc = (totalW > 0) ? F_PI / totalW : 0.f;
            float* p = &irr.faces[f][((size_t)y * irrSize + x) * 4];
            p[0] = acc.x * sc; p[1] = acc.y * sc; p[2] = acc.z * sc; p[3] = 1.f;
        }
    }
    return irr;
}

// ─── Prefiltered specular environment (one CubeImage per mip level) ──────────
inline std::vector<CubeImage> computePrefilteredEnv(
    const CubeImage& env, int baseSize = 128, int numMips = 5, int numSamples = 128)
{
    std::vector<CubeImage> mips(numMips);
    for (int mip = 0; mip < numMips; mip++) {
        float roughness = (numMips > 1) ? float(mip) / float(numMips - 1) : 0.f;
        int sz = baseSize >> mip; if (sz < 1) sz = 1;
        mips[mip].size = sz;
        for (int f = 0; f < 6; f++) {
            mips[mip].faces[f].resize((size_t)sz * sz * 4, 0.f);
            for (int y = 0; y < sz; y++) for (int x = 0; x < sz; x++) {
                float s = (x + .5f) / sz * 2.f - 1.f, t = (y + .5f) / sz * 2.f - 1.f;
                F3 N = cubeFaceDir(f, s, t);
                F3 acc{0, 0, 0}; float totalW = 0.f;
                for (int i = 0; i < numSamples; i++) {
                    float xi1, xi2; hammersley((uint32_t)i, (uint32_t)numSamples, xi1, xi2);
                    F3 H = importanceSampleGGX(xi1, xi2, roughness, N);
                    float NdotH = f3dot(N, H); if (NdotH < 0.f) NdotH = 0.f;
                    F3 L = f3norm(f3add(f3mul(H, 2.f * NdotH), f3mul(N, -1.f)));
                    float NdotL = f3dot(N, L); if (NdotL < 0.f) NdotL = 0.f;
                    if (NdotL > 0.f) {
                        F3 c = sampleCubemap(env, L);
                        acc.x += c.x * NdotL; acc.y += c.y * NdotL; acc.z += c.z * NdotL;
                        totalW += NdotL;
                    }
                }
                if (totalW > 0) { acc.x /= totalW; acc.y /= totalW; acc.z /= totalW; }
                float* p = &mips[mip].faces[f][((size_t)y * sz + x) * 4];
                p[0] = acc.x; p[1] = acc.y; p[2] = acc.z; p[3] = 1.f;
            }
        }
    }
    return mips;
}

// ─── BRDF integration LUT (split-sum: R=F0 scale, G=F0 bias) ─────────────────
inline TexImage computeBRDFLUT(int size = 256, int numSamples = 512) {
    TexImage lut; lut.w = lut.h = size;
    lut.data.resize((size_t)size * size * 4, 0.f);
    for (int j = 0; j < size; j++) {
        float roughness = (j + .5f) / size;
        for (int i = 0; i < size; i++) {
            float NdotV = (i + .5f) / size;
            F3 V = {std::sqrt(1.f - NdotV * NdotV), 0.f, NdotV};
            F3 N = {0, 0, 1};
            float A = 0, B = 0;
            for (int smp = 0; smp < numSamples; smp++) {
                float xi1, xi2; hammersley((uint32_t)smp, (uint32_t)numSamples, xi1, xi2);
                F3 H = importanceSampleGGX(xi1, xi2, roughness, N);
                float VdotH = f3dot(V, H); if (VdotH < 0.f) VdotH = 0.f;
                F3 L = f3norm(f3add(f3mul(H, 2.f * VdotH), f3mul(V, -1.f)));
                float NdotL = L.z > 0.f ? L.z : 0.f;
                float NdotH = H.z > 0.f ? H.z : 0.f;
                if (NdotL > 0.f) {
                    float r2   = roughness * roughness;
                    float Gv   = NdotV / (NdotV * (1.f - r2 / 2.f) + r2 / 2.f);
                    float Gl   = NdotL / (NdotL * (1.f - r2 / 2.f) + r2 / 2.f);
                    float Gvis = Gv * Gl * VdotH / (NdotH * NdotV + 1e-5f);
                    float Fc   = std::pow(1.f - VdotH, 5.f);
                    A += (1.f - Fc) * Gvis; B += Fc * Gvis;
                }
            }
            float* p = &lut.data[((size_t)j * size + i) * 4];
            p[0] = A / numSamples; p[1] = B / numSamples; p[2] = 0.f; p[3] = 1.f;
        }
    }
    return lut;
}

// How many prefiltered mip levels are generated (matches shader constant)
static constexpr int NUM_ENV_MIPS = 5;

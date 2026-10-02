#pragma once

constexpr int   WIDTH                = 1500;
constexpr int   HEIGHT               = 1500;
constexpr int   MAX_FRAMES_IN_FLIGHT = 2;
constexpr int   INSTANCE_COUNT       = 100;
constexpr float SPHERE_RADIUS        = 5.0f;

enum class DisplayMode {
    Solid         = 0,
    Wireframe     = 1,
    SolidWireframe= 2,
    Unlit         = 3,
    Normals       = 4,
};

// Shader-side display-mode values passed via push constant
constexpr int SHADER_MODE_SOLID      = 0;
constexpr int SHADER_MODE_WIREFRAME  = 1;
constexpr int SHADER_MODE_UNLIT      = 2;
constexpr int SHADER_MODE_NORMALS    = 3;

// Per-cube material types (instanced; used only when shaderMode == SOLID)
constexpr int MAT_PHONG       = 0;  // Blinn-Phong
constexpr int MAT_TOON        = 1;  // Cel / toon shading
constexpr int MAT_GOOCH       = 2;  // Warm-to-cool (technical illustration)
constexpr int MAT_RIM         = 3;  // Fresnel / rim-light
constexpr int MAT_OREN_NAYAR  = 4;  // Rough-diffuse (clay / chalk)
constexpr int MAT_MINNAERT    = 5;  // Velvet / lunar surface
constexpr int MAT_PBR         = 6;  // Cook-Torrance GGX PBR
constexpr int MAT_ANISOTROPIC = 7;  // Ward anisotropic (brushed metal)
constexpr int MAT_SSS         = 8;  // Subsurface scattering (wrap-diffuse approx)
constexpr int MAT_COUNT       = 9;

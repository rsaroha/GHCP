#pragma once

#include <vulkan/vulkan.h>
#include <array>
#include <set>
#include <string>

#include "config.h"
#include "math_types.h"
#include "geometry.h"

// ─── Light parameters ────────────────────────────────────────────────────────
struct LightParams {
    float pos[3]    = {-6.0f, 14.0f, -10.0f};  // world-space position
    float color[3]  = {1.0f, 1.0f, 1.0f};
    float intensity =  1.0f;
};

// ─── Scene input state ───────────────────────────────────────────────────────
struct SceneInput {
    Arcball          arcball;
    Arcball          envArcball;              // environment rotation (Alt+MMB / Alt+Shift+MMB)
    Vec3             camTarget{0, 0, 0};
    float            zoomDist      = 14.0f;
    float            envZoom       = 1.0f;   // environment zoom (Alt+Ctrl+MMB)
    std::set<int>    selectedCubes;
    bool             meshSelected  = false;
    DisplayMode      displayMode   = DisplayMode::Solid;
    Material         defaultMaterial{};        // persists across renderer switches
    bool             switchRenderer  = false;  // set by UI to request renderer swap
    bool             useOpenGL       = false;  // which renderer is currently active
    Vec3             selectionColor{0.0f, 0.5f, 1.0f};
    Vec3             outlineColor{1.0f, 0.0f, 0.0f};
    float            outlineThickness  = 2.0f;
    bool             outlineAntialiased = false;
    float            occlusionAlpha    = 0.25f;  // masking pass: outline alpha where occluded
    LightParams      light;
    std::string      albedoTexPath;            // persists across renderer switches
    std::string      envMapPath;
    float            iblIntensity    = 1.0f;
};

// ─── InputHandler ────────────────────────────────────────────────────────────
class InputHandler {
public:
    SceneInput state;

    void setPickContext(const VkExtent2D* ext,
                        const std::array<Vec3, INSTANCE_COUNT>* pos);
    void setMeshPickContext(Vec3 center, float radius, bool loaded);

    void onMouseButton(int button, int action, int mods, double mx, double my);
    void onCursorPos(double mx, double my);

private:
    int  pickCube(double mx, double my) const;
    bool pickMesh(double mx, double my) const;

    // Middle-mouse-button state
    bool   _mmbDown = false;
    int    _mmbMods = 0;
    double _lastMX  = 0;
    double _lastMY  = 0;

    // Cube pick context
    const VkExtent2D*                        _ext = nullptr;
    const std::array<Vec3, INSTANCE_COUNT>*  _pos = nullptr;

    // Mesh pick context
    Vec3  _meshCenter{};
    float _meshRadius = 0.0f;
    bool  _meshLoaded = false;
};

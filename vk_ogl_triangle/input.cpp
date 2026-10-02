#include "input.h"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <cmath>

void InputHandler::setPickContext(const VkExtent2D* ext,
                                   const std::array<Vec3, INSTANCE_COUNT>* pos)
{
    _ext = ext;
    _pos = pos;
}

void InputHandler::setMeshPickContext(Vec3 center, float radius, bool loaded)
{
    _meshCenter = center;
    _meshRadius = radius;
    _meshLoaded = loaded;
    if (!loaded) state.meshSelected = false;
}

int InputHandler::pickCube(double mx, double my) const
{
    if (!_ext || !_pos) return -1;
    int fw = (int)_ext->width;
    int fh = (int)_ext->height;
    if (!fw || !fh) return -1;

    constexpr float fovY  = 1.0472f;
    float aspect   = (float)fw / fh;
    float tanHalf  = std::tan(fovY * 0.5f);
    float nx = 2.0f*(float)mx/fw - 1.0f;
    float ny = 2.0f*(float)my/fh - 1.0f;
    Vec3 rayDir  = v3norm({nx * tanHalf * aspect, -ny * tanHalf, 1.0f});
    Vec3 rayOrig = {state.camTarget.x, state.camTarget.y, state.camTarget.z - state.zoomDist};

    Mat4 arc = state.arcball.matrix();
    int  best = -1;
    float minT = 1e9f;
    constexpr float pickRadius = 0.92f;

    for (int i = 0; i < INSTANCE_COUNT; i++) {
        Vec3 p = (*_pos)[i];
        Vec3 wc = {
            arc[0]*p.x + arc[4]*p.y + arc[8]*p.z,
            arc[1]*p.x + arc[5]*p.y + arc[9]*p.z,
            arc[2]*p.x + arc[6]*p.y + arc[10]*p.z
        };
        Vec3 oc = {wc.x-rayOrig.x, wc.y-rayOrig.y, wc.z-rayOrig.z};
        float b    = v3dot(oc, rayDir);
        float disc = b*b - v3dot(oc,oc) + pickRadius*pickRadius;
        if (disc >= 0.0f && b > 0.0f) {
            float t = b - std::sqrt(disc);
            if (t < minT) { minT = t; best = i; }
        }
    }
    return best;
}

bool InputHandler::pickMesh(double mx, double my) const
{
    if (!_meshLoaded || !_ext) return false;
    int fw = (int)_ext->width;
    int fh = (int)_ext->height;
    if (!fw || !fh) return false;

    constexpr float fovY  = 1.0472f;
    float aspect   = (float)fw / fh;
    float tanHalf  = std::tan(fovY * 0.5f);
    float nx = 2.0f*(float)mx/fw - 1.0f;
    float ny = 2.0f*(float)my/fh - 1.0f;
    Vec3 rayDir  = v3norm({nx * tanHalf * aspect, -ny * tanHalf, 1.0f});
    Vec3 rayOrig = {state.camTarget.x, state.camTarget.y, state.camTarget.z - state.zoomDist};

    // Apply arcball to mesh center (identity instance transform → center is in world space)
    Mat4 arc = state.arcball.matrix();
    Vec3 c = _meshCenter;
    Vec3 wc = {
        arc[0]*c.x + arc[4]*c.y + arc[8]*c.z,
        arc[1]*c.x + arc[5]*c.y + arc[9]*c.z,
        arc[2]*c.x + arc[6]*c.y + arc[10]*c.z
    };
    Vec3 oc = {wc.x - rayOrig.x, wc.y - rayOrig.y, wc.z - rayOrig.z};
    float b    = v3dot(oc, rayDir);
    float disc = b*b - v3dot(oc, oc) + _meshRadius * _meshRadius;
    return disc >= 0.0f && b > 0.0f;
}

void InputHandler::onMouseButton(int button, int action, int mods, double mx, double my)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        int  cubeHit = pickCube(mx, my);
        bool meshHit = pickMesh(mx, my);

        // Cubes take priority over mesh when both hit (cubes are smaller targets)
        if (cubeHit >= 0) meshHit = false;

        if (mods & GLFW_MOD_CONTROL) {
            if (cubeHit >= 0) {
                if (state.selectedCubes.count(cubeHit)) state.selectedCubes.erase(cubeHit);
                else                                     state.selectedCubes.insert(cubeHit);
            }
            if (meshHit) state.meshSelected = !state.meshSelected;
        } else {
            if (cubeHit >= 0) {
                if (state.selectedCubes.size() == 1 && state.selectedCubes.count(cubeHit))
                    state.selectedCubes.clear();
                else
                    state.selectedCubes = {cubeHit};
                state.meshSelected = false;
            } else if (meshHit) {
                state.meshSelected = !state.meshSelected;
                state.selectedCubes.clear();
            } else {
                state.selectedCubes.clear();
                state.meshSelected = false;
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        if (action == GLFW_PRESS) {
            _mmbDown = true;
            _mmbMods = mods;
            _lastMX  = mx;
            _lastMY  = my;
            if (_ext) {
                int w = (int)_ext->width, h = (int)_ext->height;
                if (_mmbMods & GLFW_MOD_ALT) {
                    if (!(_mmbMods & (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL)))
                        state.envArcball.beginDrag(mx, my, w, h);
                } else if (!(_mmbMods & (GLFW_MOD_SHIFT | GLFW_MOD_CONTROL))) {
                    state.arcball.beginDrag(mx, my, w, h);
                }
            }
        } else {
            _mmbDown = false;
            state.arcball.dragging    = false;
            state.envArcball.dragging = false;
        }
    }
}

void InputHandler::onCursorPos(double mx, double my)
{
    if (!_mmbDown) return;

    double dx = mx - _lastMX;
    double dy = my - _lastMY;
    _lastMX = mx;
    _lastMY = my;

    int fw = _ext ? (int)_ext->width  : 1;
    int fh = _ext ? (int)_ext->height : 1;

    if (_mmbMods & GLFW_MOD_ALT) {
        if (_mmbMods & GLFW_MOD_CONTROL) {
            // Alt+Ctrl: zoom environment
            state.envZoom += (float)dy * state.envZoom * 0.005f;
            state.envZoom  = std::clamp(state.envZoom, 0.1f, 10.0f);
        } else if (_mmbMods & GLFW_MOD_SHIFT) {
            // Alt+Shift: pan environment (yaw/pitch applied as incremental rotation)
            float yawAngle   = -(float)dx * 0.005f;
            float pitchAngle =  (float)dy * 0.005f;
            Quat  yaw   = {std::cos(yawAngle   * 0.5f), 0.0f, std::sin(yawAngle   * 0.5f), 0.0f};
            Quat  pitch = {std::cos(pitchAngle * 0.5f), std::sin(pitchAngle * 0.5f), 0.0f, 0.0f};
            state.envArcball.current = qnorm(qmul(qmul(yaw, pitch), state.envArcball.current));
            state.envArcball.saved   = state.envArcball.current;
        } else {
            // Alt only: rotate environment (arcball)
            state.envArcball.drag(mx, my, fw, fh);
        }
    } else if (_mmbMods & GLFW_MOD_CONTROL) {
        // Ctrl: zoom scene
        state.zoomDist += (float)dy * state.zoomDist * 0.005f;
        state.zoomDist  = std::clamp(state.zoomDist, 1.0f, 80.0f);
    } else if (_mmbMods & GLFW_MOD_SHIFT) {
        // Shift: pan scene
        constexpr float fovY = 1.0472f;
        float worldPerPx = 2.0f * state.zoomDist * std::tan(fovY * 0.5f) / fh;
        state.camTarget.x -= (float)dx * worldPerPx;
        state.camTarget.y += (float)dy * worldPerPx;
    } else {
        // Plain MMB: rotate scene (arcball)
        state.arcball.drag(mx, my, fw, fh);
    }
}

#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>   // for VkExtent2D used by InputHandler

#include <array>
#include <string>
#include <vector>

#include "config.h"
#include "math_types.h"
#include "geometry.h"
#include "input.h"

struct SceneUBO {
    float    mvp[16];        // offset   0
    float    mv[16];         // offset  64
    float    selColor[4];    // offset 128
    float    lightPos[4];    // offset 144
    float    lightColor[4];  // offset 160
    int32_t  shaderMode;     // offset 176
    int32_t  hasAlbedoTex;   // offset 180  (was _pad[0])
    int32_t  hasEnvMap;      // offset 184  (was _pad[1])
    float    iblIntensity;   // offset 188  (was _pad[2])
    uint32_t selMask[4];     // offset 192
};
static_assert(sizeof(SceneUBO) == 208);

class RendererGL {
public:
    void run(InputHandler& input);

private:
    InputHandler* _input = nullptr;
    GLFWwindow*   window{};

    // GLSL programs
    GLuint progMain{};
    GLuint progOit{};
    GLuint progComposite{};
    GLuint progSkybox{};
    GLint  skyboxLocInvPVR = -1;
    GLint  skyboxLocIBL    = -1;
    GLuint progHighlight{};                   // renders selected objects as RGBA mask
    GLuint progMasking{};                     // dims alpha where occluded by main scene
    GLint  maskingLocAlpha      = -1;
    GLuint progOutline{};                     // dilation → outline image
    GLint  outlineLocTexelSize    = -1;
    GLint  outlineLocColor        = -1;
    GLint  outlineLocThickness    = -1;
    GLint  outlineLocAntialiased  = -1;
    GLuint progBlend{};                       // blends outline image onto main FBO
    GLint  blendLocTexelSize    = -1;

    // Cube geometry (rounded)
    GLuint cubeVao{};
    GLuint cubeVbo{};
    GLuint cubeIbo{};
    GLuint cubeInstanceVbo{};
    uint32_t cubeIndexCount = 0;

    // Loaded mesh (optional)
    GLuint meshVao{};
    GLuint meshVbo{};
    GLuint meshIbo{};
    GLuint meshInstanceVbo{};
    uint32_t meshIndexCount = 0;
    bool     meshLoaded = false;
    std::string meshError;
    Material    meshMaterial{};
    InstanceData meshInstanceData{};

    // UBO
    GLuint sceneUbo{};

    // Textures (bound to units 2-5 during scene rendering)
    GLuint albedoTex      = 0;   // unit 2: per-mesh diffuse/albedo
    GLuint irradianceCube = 0;   // unit 3: diffuse IBL cubemap
    GLuint prefilteredEnv = 0;   // unit 4: specular prefiltered env cubemap (mipped)
    GLuint brdfLUT        = 0;   // unit 5: BRDF integration LUT
    GLuint equirectTex2D  = 0;   // unit 6: original equirect HDR (skybox background)
    GLuint highlightTex      = 0;   // RGBA8 selection mask (raw, written by highlight pass)
    GLuint highlightDepthTex = 0;   // depth texture for highlight pass (selected objects' depths)
    GLuint maskedHighlightTex= 0;   // RGBA8 dimmed mask output of masking pass (fed to outline)
    GLuint outlineTex        = 0;   // RGBA8 outline image output of outline pass (fed to blend)
    GLuint highlightFbo      = 0;
    GLuint maskingFbo        = 0;
    GLuint outlineFbo        = 0;
    bool   albedoLoaded   = false;
    bool   envLoaded      = false;

    // FBOs for OIT (recreated on resize)
    GLuint mainFbo{};
    GLuint oitFbo{};
    GLuint mainColorTex{};
    GLuint accumTex{};
    GLuint revealTex{};
    GLuint depthTex{};    // main scene depth texture (1x, shared by mainFbo + oitFbo)
    int    fbWidth = 0, fbHeight = 0;

    // MSAA
    bool   msaa8         = true;
    GLuint msaaFbo       = 0;
    GLuint msaaColorRbo  = 0;
    GLuint msaaDepthRbo  = 0;

    // Fullscreen quad VAO (no VBO; uses gl_VertexID trick)
    GLuint quadVao{};

    // Host-side scene data
    std::array<Vec3, INSTANCE_COUNT>         cubePositions{};
    std::array<InstanceData, INSTANCE_COUNT> instanceData{};

    // Pick extent (reuses VkExtent2D since InputHandler requires it)
    VkExtent2D glExtent{};

    // Init
    void initWindow();
    void initGL();
    void initImGui();
    void createPrograms();
    void createGeometry();
    void createSceneUbo();
    void createFbos(int w, int h);
    void cleanupFbos();

    // Helpers
    GLuint compileShader(GLenum type, const char* src);
    GLuint linkProgram(GLuint vs, GLuint fs);
    void   setupInstanceAttribs(GLuint vao, GLuint instanceVbo);
    void   uploadUBO(int shaderMode, const uint32_t selMask[4], bool hasAlbedo=false);

    // Per-frame
    void mainLoop();
    void drawFrame();
    void drawScene(int shaderMode, bool oitPass);

    // UI
    void renderUI();
    void loadMesh(const std::string& path);
    void uploadMeshBuffers(const std::vector<Vertex>& verts, const std::vector<uint32_t>& idxs);
    void unloadMesh();
    void loadAlbedoTexture(const std::string& path);
    void loadEnvMap(const std::string& path);
    void createDefaultTextures();

    // Cleanup
    void cleanup();
};

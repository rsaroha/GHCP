#pragma once

#define GLFW_INCLUDE_NONE  // prevent GLFW from pulling in system OpenGL headers
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <array>
#include <optional>
#include <string>
#include <vector>

#include "config.h"
#include "math_types.h"
#include "geometry.h"
#include "input.h"

// ─── Vulkan texture bundle ────────────────────────────────────────────────────
struct VkTex {
    VkImage        image  = VK_NULL_HANDLE;
    VkDeviceMemory memory = VK_NULL_HANDLE;
    VkImageView    view   = VK_NULL_HANDLE;
    VkSampler      sampler= VK_NULL_HANDLE;
    bool valid() const { return image != VK_NULL_HANDLE; }
};

// ─── Helpers (internal) ───────────────────────────────────────────────────────
struct QueueFamilyIndices {
    std::optional<uint32_t> graphics, present;
    bool complete() const { return graphics && present; }
};

struct SwapchainSupport {
    VkSurfaceCapabilitiesKHR caps;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

// ─── Renderer ────────────────────────────────────────────────────────────────
class Renderer {
public:
    void run(InputHandler& input);

private:
    // Pointer set at the start of run()
    InputHandler* _input = nullptr;

    GLFWwindow*               window{};
    VkInstance                instance{};
    VkDebugUtilsMessengerEXT  debugMessenger{};
    VkSurfaceKHR              surface{};
    VkPhysicalDevice          physicalDevice{};
    VkDevice                  device{};
    VkQueue                   graphicsQueue{}, presentQueue{};
    PFN_vkCmdInsertDebugUtilsLabelEXT pfnCmdInsertLabel{};
    VkSwapchainKHR            swapchain{};
    std::vector<VkImage>      swapImages;
    VkFormat                  swapFormat{};
    VkExtent2D                swapExtent{};
    std::vector<VkImageView>  swapImageViews;
    VkImage                   depthImage{};
    VkDeviceMemory            depthMemory{};
    VkImageView               depthImageView{};
    // MSAA state
    bool                      msaa8 = true;
    bool                      msaaChanged = false;

    VkRenderPass              opaqueRenderPass{};    // geometry (MSAA-dependent)
    VkRenderPass              oitRenderPass{};        // OIT accum (persistent, 1x)
    VkRenderPass              compositeRenderPass{};  // OIT composite (persistent, 1x)
    VkRenderPass              depthPrepassRenderPass{}; // depth-only prepass (MSAA only)
    VkPipelineLayout          pipelineLayout{};
    VkPipeline                graphicsPipeline{};
    VkPipeline                wireframePipeline{};
    VkPipeline                skyboxPipeline{};
    VkPipeline                depthPrepassPipeline{};   // depth prepass (MSAA only)
    VkDescriptorPool          imguiPool{};
    uint32_t                  graphicsQueueFamily = 0;

    // OIT images — one set per swapchain image (extent-dependent)
    std::vector<VkImage>       accumImages, revealImages;
    std::vector<VkDeviceMemory> accumMemories, revealMemories;
    std::vector<VkImageView>   accumImageViews, revealImageViews;

    // OIT pipelines and layouts (persistent)
    VkPipeline                oitPipeline{};
    VkPipeline                compositePipeline{};
    VkPipelineLayout          compositePipelineLayout{};
    VkDescriptorSetLayout     compositeDescLayout{};

    // OIT descriptor pool+sets (per-swapchain, recreated on resize)
    VkDescriptorPool          oitDescPool{};
    std::vector<VkDescriptorSet> compositeDescSets;
    VkSampler                 oitCompositeSampler{};   // persistent, for composite desc sets

    // Per-swapchain framebuffers
    std::vector<VkFramebuffer> opaqueFramebuffers;
    std::vector<VkFramebuffer> oitFramebuffers;
    std::vector<VkFramebuffer> compositeFramebuffers;
    std::vector<VkFramebuffer> depthPrepassFramebuffers;  // MSAA only

    // MSAA images (per-swapchain-image, created when msaa8=true)
    std::vector<VkImage>       msaaColorImages;
    std::vector<VkDeviceMemory> msaaColorMemories;
    std::vector<VkImageView>   msaaColorImageViews;
    VkImage                   msaaDepthImage{};
    VkDeviceMemory            msaaDepthMemory{};
    VkImageView               msaaDepthImageView{};
    VkCommandPool             commandPool{};
    std::vector<VkCommandBuffer> commandBuffers;
    VkBuffer                  vertexBuffer{}, indexBuffer{}, instanceBuffer{};
    VkDeviceMemory            vertexMemory{}, indexMemory{}, instanceMemory{};
    void*                     instanceMapped{};   // persistent host mapping
    uint32_t                  cubeIndexCount = 0;

    // GLTF/OBJ mesh (optional, loaded at runtime)
    VkBuffer                  gltfVertexBuffer{}, gltfIndexBuffer{}, gltfInstanceBuffer{};
    VkDeviceMemory            gltfVertexMemory{}, gltfIndexMemory{}, gltfInstanceMemory{};
    void*                     gltfInstanceMapped{};  // persistent mapping
    uint32_t                  gltfIndexCount = 0;
    bool                      gltfLoaded = false;
    std::string               gltfError;
    Material                  gltfMaterial{};

    std::vector<VkSemaphore>  imageAvailable, renderFinished;
    std::vector<VkFence>      inFlight;
    uint32_t                  currentFrame = 0;
    bool                      framebufferResized = false;

    // ── Texture resources
    VkTex                     albedoTex{};        // per-mesh diffuse/albedo
    VkTex                     irradianceTex{};    // diffuse IBL cubemap
    VkTex                     prefilteredEnvTex{};// specular prefiltered env cubemap
    VkTex                     brdfLutTex{};       // BRDF integration LUT
    VkTex                     equirectTex{};      // original equirect HDR (skybox background)
    bool                      albedoLoaded   = false;
    bool                      envLoaded      = false;

    // ── Selection outline resources
    // Per-swapchain-image (recreated on resize)
    std::vector<VkImage>       highlightImages;
    std::vector<VkDeviceMemory> highlightMemories;
    std::vector<VkImageView>   highlightImageViews;
    std::vector<VkFramebuffer> highlightFramebuffers;
    std::vector<VkFramebuffer> outlineFramebuffers;
    VkDescriptorPool           outlineDescPool{};
    std::vector<VkDescriptorSet> outlineDescSets;
    // Masking pass resources (per-swapchain-image)
    std::vector<VkImage>       maskDepthImages;
    std::vector<VkDeviceMemory> maskDepthMemories;
    std::vector<VkImageView>   maskDepthImageViews;
    std::vector<VkImage>       maskedHighlightImages;
    std::vector<VkDeviceMemory> maskedHighlightMemories;
    std::vector<VkImageView>   maskedHighlightImageViews;
    std::vector<VkFramebuffer> maskingFramebuffers;
    VkDescriptorPool           maskingDescPool{};
    std::vector<VkDescriptorSet> maskingDescSets;
    // Outline image (per-swapchain-image, written by outline pass, read by blend pass)
    std::vector<VkImage>       outlineImages;
    std::vector<VkDeviceMemory> outlineMemories;
    std::vector<VkImageView>   outlineImageViews;
    // Blend pass resources (per-swapchain-image)
    std::vector<VkFramebuffer> blendFramebuffers;
    VkDescriptorPool           blendDescPool{};
    std::vector<VkDescriptorSet> blendDescSets;
    // Persistent (created once)
    VkSampler                  highlightSampler{};
    VkSampler                  maskingSampler{};
    VkDescriptorSetLayout      outlineDescLayout{};
    VkDescriptorSetLayout      maskingDescLayout{};
    VkDescriptorSetLayout      blendDescLayout{};
    VkRenderPass               highlightRenderPass{};
    VkRenderPass               outlineRenderPass{};
    VkRenderPass               maskingRenderPass{};
    VkRenderPass               blendRenderPass{};
    VkPipeline                 highlightPipeline{};
    VkPipelineLayout           outlinePipelineLayout{};
    VkPipeline                 outlinePipeline{};
    VkPipelineLayout           maskingPipelineLayout{};
    VkPipeline                 maskingPipeline{};
    VkPipelineLayout           blendPipelineLayout{};
    VkPipeline                 blendPipeline{};

    // ── Texture descriptor set (set=0)
    VkDescriptorSetLayout     texDescLayout{};
    VkDescriptorPool          texDescPool{};
    VkDescriptorSet           texDescSet{};

    // ── Physical device features
    bool                      anisotropySupported = false;
    float                     maxAnisotropy       = 1.0f;

    std::array<Vec3, INSTANCE_COUNT>          cubePositions{};
    std::array<InstanceData, INSTANCE_COUNT>  instanceData{};

    // ── Init / loop / cleanup
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    // ── Instance
    void createInstance();
    bool checkValidationSupport();
    std::vector<const char*> getRequiredExtensions();
    void populateDebugCI(VkDebugUtilsMessengerCreateInfoEXT& ci);
    void setupDebugMessenger();

    // ── Surface / devices
    void createSurface();
    void pickPhysicalDevice();
    bool isSuitable(VkPhysicalDevice dev);
    void createLogicalDevice();

    // ── Swapchain
    VkSurfaceFormatKHR chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& fmts);
    VkPresentModeKHR   choosePresentMode(const std::vector<VkPresentModeKHR>& modes);
    VkExtent2D         chooseExtent(const VkSurfaceCapabilitiesKHR& caps);
    void createSwapchain();
    void createImageViews();

    // ── Memory helpers
    uint32_t findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags props);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                      VkMemoryPropertyFlags props, VkBuffer& buf, VkDeviceMemory& mem);

    // ── Depth
    void createDepthResources();

    // ── OIT resources
    void createOITImage(VkFormat fmt, VkImage& image, VkDeviceMemory& mem, VkImageView& view);
    void createOITImages();
    void createOITDescriptorSets();
    void createOITPipelines();

    // ── Render pass / pipeline
    void createOpaqueRenderPass();
    void createOITAccumRenderPass();
    void createCompositeRenderPass();
    void createDepthPrepassRenderPass();
    void createDepthPrepassPipeline();
    void createMSAAImages();
    void cleanupMSAAImages();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createGraphicsPipeline();
    void createSkyboxPipeline();
    void uploadEquirectTexture(VkTex& tex, const float* rgba32f, uint32_t w, uint32_t h);
    void createHighlightRenderPass();
    void createOutlineRenderPass();
    void createMaskingRenderPass();
    void createBlendRenderPass();
    void createHighlightPipeline();
    void createOutlinePipeline();
    void createMaskingPipeline();
    void createBlendPipeline();
    void createHighlightImages();
    void createHighlightFramebuffers();
    void createOutlineFramebuffers();
    void createMaskingFramebuffers();
    void createBlendFramebuffers();
    void createOutlineDescriptorSets();
    void createMaskingDescriptorSets();
    void createBlendDescriptorSets();

    // ── Texture helpers
    VkCommandBuffer beginSingleTimeCommands();
    void            endSingleTimeCommands(VkCommandBuffer cb);
    void            createVkImage(uint32_t w, uint32_t h, uint32_t layers, uint32_t mipLevels,
                                  VkFormat fmt, VkImageCreateFlags flags,
                                  VkImage& img, VkDeviceMemory& mem);
    void            uploadTexture2D(VkTex& tex, const float* rgba32f, uint32_t w, uint32_t h,
                                    bool genMips, bool srgb);
    void            uploadCubemapMipped(VkTex& tex, const std::vector<std::vector<std::vector<float>>>& facesMips,
                                        uint32_t baseW, uint32_t baseH, uint32_t mipLevels);
    void            destroyVkTex(VkTex& tex);
    void            createTextureDescriptorLayout();
    void            createDefaultTextures();
    void            createTextureDescriptorSet();
    void            loadAlbedoTexture(const std::string& path);
    void            loadEnvMap(const std::string& path);

    // ── ImGui
    void initImGui();
    void cleanupImGui();
    void renderUI();
    void loadGltf(const std::string& path);
    void loadObj(const std::string& path);
    void uploadMeshBuffers(const std::vector<Vertex>& verts, const std::vector<uint32_t>& idxs);

    // ── Framebuffers
    void createOpaqueFramebuffers();
    void createOITFramebuffers();
    void createCompositeFramebuffers();
    void createDepthPrepassFramebuffers();

    // ── Geometry buffers
    void createVertexBuffer();
    void createIndexBuffer();
    void createInstanceBuffer();

    // ── Command pool / buffers
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer cb, uint32_t imageIndex);

    // ── Sync
    void createSyncObjects();

    // ── Swapchain recreation
    void cleanupSwapchain();
    void recreateSwapchain();

    // ── Draw
    void drawFrame();
};

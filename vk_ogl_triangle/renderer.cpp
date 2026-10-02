#include "renderer.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_vulkan.h>

#include "mesh_loader.h"
#include "texture_util.h"
#include "ui_helpers.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
#include <stdexcept>
#include <vector>

#ifdef NDEBUG
constexpr bool ENABLE_VALIDATION = false;
#else
constexpr bool ENABLE_VALIDATION = true;
#endif

static const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
static const std::vector<const char*> deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

// ─── File / debug helpers ─────────────────────────────────────────────────────
static std::vector<char> readFile(const std::string& path) {
    std::ifstream f(path, std::ios::ate | std::ios::binary);
    if (!f) throw std::runtime_error("Failed to open: " + path);
    size_t sz = (size_t)f.tellg();
    std::vector<char> buf(sz);
    f.seekg(0); f.read(buf.data(), sz);
    return buf;
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT,
    const VkDebugUtilsMessengerCallbackDataEXT* d, void*)
{ std::cerr << "[VK] " << d->pMessage << "\n"; return VK_FALSE; }

static QueueFamilyIndices findQueueFamilies(VkPhysicalDevice dev, VkSurfaceKHR surface) {
    QueueFamilyIndices idx;
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &count, nullptr);
    std::vector<VkQueueFamilyProperties> families(count);
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &count, families.data());
    for (uint32_t i = 0; i < count; ++i) {
        if (families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) idx.graphics = i;
        VkBool32 p = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(dev, i, surface, &p);
        if (p) idx.present = i;
        if (idx.complete()) break;
    }
    return idx;
}

static SwapchainSupport querySwapchainSupport(VkPhysicalDevice dev, VkSurfaceKHR surface) {
    SwapchainSupport s;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface, &s.caps);
    uint32_t cnt;
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &cnt, nullptr);
    s.formats.resize(cnt);
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface, &cnt, s.formats.data());
    vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &cnt, nullptr);
    s.presentModes.resize(cnt);
    vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface, &cnt, s.presentModes.data());
    return s;
}

// ─── Public entry point ───────────────────────────────────────────────────────
void Renderer::run(InputHandler& input) {
    _input = &input;
    initWindow();
    initVulkan();
    // Restore textures if switching from GL renderer
    if (!_input->state.albedoTexPath.empty())
        loadAlbedoTexture(_input->state.albedoTexPath);
    if (!_input->state.envMapPath.empty())
        loadEnvMap(_input->state.envMapPath);
    mainLoop();
    cleanup();
}

// ─── Window ───────────────────────────────────────────────────────────────────
void Renderer::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan Renderer", nullptr, nullptr);
    glfwSetWindowPos(window, 100, 50);
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int, int) {
        static_cast<Renderer*>(glfwGetWindowUserPointer(w))->framebufferResized = true;
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* w, int button, int action, int mods) {
        if (ImGui::GetIO().WantCaptureMouse) return;
        auto* r = static_cast<Renderer*>(glfwGetWindowUserPointer(w));
        double mx, my; glfwGetCursorPos(w, &mx, &my);
        r->_input->onMouseButton(button, action, mods, mx, my);
    });

    glfwSetCursorPosCallback(window, [](GLFWwindow* w, double mx, double my) {
        if (ImGui::GetIO().WantCaptureMouse) return;
        auto* r = static_cast<Renderer*>(glfwGetWindowUserPointer(w));
        r->_input->onCursorPos(mx, my);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int /*scancode*/, int action, int /*mods*/) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(w, GLFW_TRUE);
    });
}

// ─── Instance ─────────────────────────────────────────────────────────────────
void Renderer::createInstance() {
    if (ENABLE_VALIDATION && !checkValidationSupport())
        throw std::runtime_error("Validation layers not available");
    VkApplicationInfo app{};
    app.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app.pApplicationName = "Cube"; app.apiVersion = VK_API_VERSION_1_0;
    auto exts = getRequiredExtensions();
    VkInstanceCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    ci.pApplicationInfo = &app;
    ci.enabledExtensionCount = (uint32_t)exts.size();
    ci.ppEnabledExtensionNames = exts.data();
    VkDebugUtilsMessengerCreateInfoEXT dbg{};
    if (ENABLE_VALIDATION) {
        ci.enabledLayerCount = (uint32_t)validationLayers.size();
        ci.ppEnabledLayerNames = validationLayers.data();
        populateDebugCI(dbg); ci.pNext = &dbg;
    }
    if (vkCreateInstance(&ci, nullptr, &instance) != VK_SUCCESS)
        throw std::runtime_error("vkCreateInstance failed");
}

bool Renderer::checkValidationSupport() {
    uint32_t cnt; vkEnumerateInstanceLayerProperties(&cnt, nullptr);
    std::vector<VkLayerProperties> layers(cnt);
    vkEnumerateInstanceLayerProperties(&cnt, layers.data());
    for (const char* name : validationLayers) {
        bool found = false;
        for (auto& l : layers) if (!strcmp(l.layerName, name)) { found=true; break; }
        if (!found) return false;
    }
    return true;
}

std::vector<const char*> Renderer::getRequiredExtensions() {
    uint32_t cnt; const char** g = glfwGetRequiredInstanceExtensions(&cnt);
    std::vector<const char*> exts(g, g+cnt);
    if (ENABLE_VALIDATION) exts.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    return exts;
}

void Renderer::populateDebugCI(VkDebugUtilsMessengerCreateInfoEXT& ci) {
    ci = {}; ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    ci.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    ci.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                         VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    ci.pfnUserCallback = debugCallback;
}

void Renderer::setupDebugMessenger() {
    if (!ENABLE_VALIDATION) return;
    VkDebugUtilsMessengerCreateInfoEXT ci{}; populateDebugCI(ci);
    auto fn = (PFN_vkCreateDebugUtilsMessengerEXT)
        vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (!fn || fn(instance, &ci, nullptr, &debugMessenger) != VK_SUCCESS)
        throw std::runtime_error("Failed to set up debug messenger");
}

// ─── Surface / devices ────────────────────────────────────────────────────────
void Renderer::createSurface() {
    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        throw std::runtime_error("Failed to create window surface");
}

void Renderer::pickPhysicalDevice() {
    uint32_t cnt; vkEnumeratePhysicalDevices(instance, &cnt, nullptr);
    if (!cnt) throw std::runtime_error("No Vulkan GPU");
    std::vector<VkPhysicalDevice> devs(cnt);
    vkEnumeratePhysicalDevices(instance, &cnt, devs.data());
    for (auto& d : devs) if (isSuitable(d)) { physicalDevice = d; return; }
    throw std::runtime_error("No suitable GPU");
}

bool Renderer::isSuitable(VkPhysicalDevice dev) {
    if (!findQueueFamilies(dev, surface).complete()) return false;
    uint32_t cnt; vkEnumerateDeviceExtensionProperties(dev, nullptr, &cnt, nullptr);
    std::vector<VkExtensionProperties> exts(cnt);
    vkEnumerateDeviceExtensionProperties(dev, nullptr, &cnt, exts.data());
    std::set<std::string> required(deviceExtensions.begin(), deviceExtensions.end());
    for (auto& e : exts) required.erase(e.extensionName);
    if (!required.empty()) return false;
    auto sc = querySwapchainSupport(dev, surface);
    return !sc.formats.empty() && !sc.presentModes.empty();
}

void Renderer::createLogicalDevice() {
    auto idx = findQueueFamilies(physicalDevice, surface);
    std::set<uint32_t> families = { *idx.graphics, *idx.present };
    float priority = 1.0f;
    std::vector<VkDeviceQueueCreateInfo> qcis;
    for (uint32_t f : families) {
        VkDeviceQueueCreateInfo qci{};
        qci.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        qci.queueFamilyIndex = f; qci.queueCount = 1; qci.pQueuePriorities = &priority;
        qcis.push_back(qci);
    }
    graphicsQueueFamily = *idx.graphics;

    VkPhysicalDeviceProperties devProps{};
    vkGetPhysicalDeviceProperties(physicalDevice, &devProps);

    VkPhysicalDeviceFeatures devFeatures{};
    vkGetPhysicalDeviceFeatures(physicalDevice, &devFeatures);
    anisotropySupported = devFeatures.samplerAnisotropy == VK_TRUE;
    maxAnisotropy = std::min(devProps.limits.maxSamplerAnisotropy, 16.0f);

    VkPhysicalDeviceFeatures features{};
    features.fillModeNonSolid  = VK_TRUE;   // required for wireframe mode
    features.samplerAnisotropy = anisotropySupported ? VK_TRUE : VK_FALSE;
    VkDeviceCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    ci.queueCreateInfoCount = (uint32_t)qcis.size(); ci.pQueueCreateInfos = qcis.data();
    ci.enabledExtensionCount = (uint32_t)deviceExtensions.size();
    ci.ppEnabledExtensionNames = deviceExtensions.data();
    ci.pEnabledFeatures = &features;
    if (ENABLE_VALIDATION) {
        ci.enabledLayerCount = (uint32_t)validationLayers.size();
        ci.ppEnabledLayerNames = validationLayers.data();
    }
    if (vkCreateDevice(physicalDevice, &ci, nullptr, &device) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDevice failed");
    vkGetDeviceQueue(device, *idx.graphics, 0, &graphicsQueue);
    vkGetDeviceQueue(device, *idx.present,  0, &presentQueue);
}

// ─── Swapchain ────────────────────────────────────────────────────────────────
VkSurfaceFormatKHR Renderer::chooseSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& fmts) {
    // Prefer UNORM so Vulkan does not apply automatic linear→sRGB gamma encoding.
    // Both renderers write linear shader output; neither applies gamma, so they match.
    for (auto& f : fmts)
        if (f.format == VK_FORMAT_B8G8R8A8_UNORM &&
            f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) return f;
    for (auto& f : fmts)
        if (f.format == VK_FORMAT_R8G8B8A8_UNORM &&
            f.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) return f;
    return fmts[0];
}

VkPresentModeKHR Renderer::choosePresentMode(const std::vector<VkPresentModeKHR>& modes) {
    for (auto& m : modes) if (m == VK_PRESENT_MODE_MAILBOX_KHR) return m;
    return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Renderer::chooseExtent(const VkSurfaceCapabilitiesKHR& caps) {
    if (caps.currentExtent.width != UINT32_MAX) return caps.currentExtent;
    int w, h; glfwGetFramebufferSize(window, &w, &h);
    return { std::clamp((uint32_t)w, caps.minImageExtent.width,  caps.maxImageExtent.width),
             std::clamp((uint32_t)h, caps.minImageExtent.height, caps.maxImageExtent.height) };
}

void Renderer::createSwapchain() {
    auto sc  = querySwapchainSupport(physicalDevice, surface);
    auto fmt = chooseSurfaceFormat(sc.formats);
    auto pm  = choosePresentMode(sc.presentModes);
    auto ext = chooseExtent(sc.caps);
    uint32_t imgCount = sc.caps.minImageCount + 1;
    if (sc.caps.maxImageCount && imgCount > sc.caps.maxImageCount) imgCount = sc.caps.maxImageCount;
    VkSwapchainCreateInfoKHR ci{};
    ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    ci.surface = surface; ci.minImageCount = imgCount;
    ci.imageFormat = fmt.format; ci.imageColorSpace = fmt.colorSpace;
    ci.imageExtent = ext; ci.imageArrayLayers = 1;
    ci.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    auto idx = findQueueFamilies(physicalDevice, surface);
    uint32_t qfamilies[] = { *idx.graphics, *idx.present };
    if (*idx.graphics != *idx.present) {
        ci.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        ci.queueFamilyIndexCount = 2; ci.pQueueFamilyIndices = qfamilies;
    } else { ci.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; }
    ci.preTransform = sc.caps.currentTransform;
    ci.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    ci.presentMode = pm; ci.clipped = VK_TRUE;
    if (vkCreateSwapchainKHR(device, &ci, nullptr, &swapchain) != VK_SUCCESS)
        throw std::runtime_error("vkCreateSwapchainKHR failed");
    vkGetSwapchainImagesKHR(device, swapchain, &imgCount, nullptr);
    swapImages.resize(imgCount);
    vkGetSwapchainImagesKHR(device, swapchain, &imgCount, swapImages.data());
    swapFormat = fmt.format; swapExtent = ext;
}

void Renderer::createImageViews() {
    swapImageViews.resize(swapImages.size());
    for (size_t i = 0; i < swapImages.size(); ++i) {
        VkImageViewCreateInfo ci{};
        ci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        ci.image = swapImages[i]; ci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        ci.format = swapFormat; ci.components = { VK_COMPONENT_SWIZZLE_IDENTITY };
        ci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        ci.subresourceRange.levelCount = 1; ci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(device, &ci, nullptr, &swapImageViews[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateImageView failed");
    }
}

// ─── Memory helpers ───────────────────────────────────────────────────────────
uint32_t Renderer::findMemoryType(uint32_t typeBits, VkMemoryPropertyFlags props) {
    VkPhysicalDeviceMemoryProperties memProps;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);
    for (uint32_t i = 0; i < memProps.memoryTypeCount; i++)
        if ((typeBits & (1<<i)) && (memProps.memoryTypes[i].propertyFlags & props) == props)
            return i;
    throw std::runtime_error("No suitable memory type");
}

void Renderer::createBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                             VkMemoryPropertyFlags props, VkBuffer& buf, VkDeviceMemory& mem) {
    VkBufferCreateInfo bci{};
    bci.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bci.size = size; bci.usage = usage; bci.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(device, &bci, nullptr, &buf) != VK_SUCCESS)
        throw std::runtime_error("vkCreateBuffer failed");
    VkMemoryRequirements req; vkGetBufferMemoryRequirements(device, buf, &req);
    VkMemoryAllocateInfo mai{};
    mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mai.allocationSize = req.size; mai.memoryTypeIndex = findMemoryType(req.memoryTypeBits, props);
    if (vkAllocateMemory(device, &mai, nullptr, &mem) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateMemory failed");
    vkBindBufferMemory(device, buf, mem, 0);
}

// ─── Depth resources ──────────────────────────────────────────────────────────
void Renderer::createDepthResources() {
    constexpr VkFormat depthFmt = VK_FORMAT_D32_SFLOAT;
    VkImageCreateInfo ici{};
    ici.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ici.imageType = VK_IMAGE_TYPE_2D;
    ici.format = depthFmt;
    ici.extent = { swapExtent.width, swapExtent.height, 1 };
    ici.mipLevels = 1; ici.arrayLayers = 1;
    ici.samples = VK_SAMPLE_COUNT_1_BIT;
    ici.tiling = VK_IMAGE_TILING_OPTIMAL;
    ici.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(device, &ici, nullptr, &depthImage) != VK_SUCCESS)
        throw std::runtime_error("vkCreateImage (depth) failed");
    VkMemoryRequirements req; vkGetImageMemoryRequirements(device, depthImage, &req);
    VkMemoryAllocateInfo mai{};
    mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mai.allocationSize = req.size;
    mai.memoryTypeIndex = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(device, &mai, nullptr, &depthMemory) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateMemory (depth) failed");
    vkBindImageMemory(device, depthImage, depthMemory, 0);
    VkImageViewCreateInfo vci{};
    vci.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image = depthImage; vci.viewType = VK_IMAGE_VIEW_TYPE_2D; vci.format = depthFmt;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    vci.subresourceRange.levelCount = 1; vci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(device, &vci, nullptr, &depthImageView) != VK_SUCCESS)
        throw std::runtime_error("vkCreateImageView (depth) failed");
}

// ─── OIT image resources ──────────────────────────────────────────────────────
void Renderer::createOITImage(VkFormat fmt, VkImage& image, VkDeviceMemory& mem, VkImageView& view) {
    VkImageCreateInfo ici{};
    ici.sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ici.imageType   = VK_IMAGE_TYPE_2D;
    ici.format      = fmt;
    ici.extent      = { swapExtent.width, swapExtent.height, 1 };
    ici.mipLevels   = 1; ici.arrayLayers = 1;
    ici.samples     = VK_SAMPLE_COUNT_1_BIT;
    ici.tiling      = VK_IMAGE_TILING_OPTIMAL;
    ici.usage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
    ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(device, &ici, nullptr, &image) != VK_SUCCESS)
        throw std::runtime_error("vkCreateImage (OIT) failed");

    VkMemoryRequirements req; vkGetImageMemoryRequirements(device, image, &req);
    VkMemoryAllocateInfo mai{};
    mai.sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mai.allocationSize  = req.size;
    mai.memoryTypeIndex = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(device, &mai, nullptr, &mem) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateMemory (OIT) failed");
    vkBindImageMemory(device, image, mem, 0);

    VkImageViewCreateInfo vci{};
    vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image    = image; vci.viewType = VK_IMAGE_VIEW_TYPE_2D; vci.format = fmt;
    vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    vci.subresourceRange.levelCount = 1; vci.subresourceRange.layerCount = 1;
    if (vkCreateImageView(device, &vci, nullptr, &view) != VK_SUCCESS)
        throw std::runtime_error("vkCreateImageView (OIT) failed");
}

void Renderer::createOITImages() {
    size_t n = swapImageViews.size();
    accumImages.resize(n); accumMemories.resize(n); accumImageViews.resize(n);
    revealImages.resize(n); revealMemories.resize(n); revealImageViews.resize(n);
    for (size_t i = 0; i < n; ++i) {
        createOITImage(VK_FORMAT_R16G16B16A16_SFLOAT, accumImages[i],  accumMemories[i],  accumImageViews[i]);
        createOITImage(VK_FORMAT_R16_SFLOAT,           revealImages[i], revealMemories[i], revealImageViews[i]);
    }
}

void Renderer::createOITDescriptorSets() {
    size_t n = swapImageViews.size();

    VkDescriptorPoolSize poolSize{};
    poolSize.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSize.descriptorCount = (uint32_t)(2 * n);
    VkDescriptorPoolCreateInfo pci{};
    pci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pci.maxSets       = (uint32_t)n;
    pci.poolSizeCount = 1; pci.pPoolSizes = &poolSize;
    if (vkCreateDescriptorPool(device, &pci, nullptr, &oitDescPool) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDescriptorPool (OIT) failed");

    std::vector<VkDescriptorSetLayout> layouts(n, compositeDescLayout);
    VkDescriptorSetAllocateInfo ai{};
    ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    ai.descriptorPool     = oitDescPool;
    ai.descriptorSetCount = (uint32_t)n;
    ai.pSetLayouts        = layouts.data();
    compositeDescSets.resize(n);
    if (vkAllocateDescriptorSets(device, &ai, compositeDescSets.data()) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateDescriptorSets (OIT) failed");

    for (size_t i = 0; i < n; ++i) {
        VkDescriptorImageInfo accumInfo{};
        accumInfo.sampler     = oitCompositeSampler;
        accumInfo.imageView   = accumImageViews[i];
        accumInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        VkDescriptorImageInfo revealInfo{};
        revealInfo.sampler    = oitCompositeSampler;
        revealInfo.imageView  = revealImageViews[i];
        revealInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet writes[2] = {};
        writes[0].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[0].dstSet          = compositeDescSets[i];
        writes[0].dstBinding      = 0;
        writes[0].descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[0].descriptorCount = 1;
        writes[0].pImageInfo      = &accumInfo;
        writes[1].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        writes[1].dstSet          = compositeDescSets[i];
        writes[1].dstBinding      = 1;
        writes[1].descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        writes[1].descriptorCount = 1;
        writes[1].pImageInfo      = &revealInfo;
        vkUpdateDescriptorSets(device, 2, writes, 0, nullptr);
    }
}

void Renderer::createOITPipelines() {
    // ── Composite descriptor set layout (2 combined image sampler bindings) ─────
    VkDescriptorSetLayoutBinding bindings[2] = {};
    bindings[0].binding        = 0;
    bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags     = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[1].binding        = 1;
    bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[1].descriptorCount = 1;
    bindings[1].stageFlags     = VK_SHADER_STAGE_FRAGMENT_BIT;
    VkDescriptorSetLayoutCreateInfo dlci{};
    dlci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    dlci.bindingCount = 2; dlci.pBindings = bindings;
    if (vkCreateDescriptorSetLayout(device, &dlci, nullptr, &compositeDescLayout) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDescriptorSetLayout (composite) failed");

    // ── OIT composite sampler (nearest, for texelFetch) ───────────────────────
    VkSamplerCreateInfo sci{};
    sci.sType        = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sci.magFilter    = VK_FILTER_NEAREST;
    sci.minFilter    = VK_FILTER_NEAREST;
    sci.mipmapMode   = VK_SAMPLER_MIPMAP_MODE_NEAREST;
    sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    if (vkCreateSampler(device, &sci, nullptr, &oitCompositeSampler) != VK_SUCCESS)
        throw std::runtime_error("vkCreateSampler (OIT composite) failed");

    VkPipelineLayoutCreateInfo clci{};
    clci.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    clci.setLayoutCount         = 1;
    clci.pSetLayouts            = &compositeDescLayout;
    if (vkCreatePipelineLayout(device, &clci, nullptr, &compositePipelineLayout) != VK_SUCCESS)
        throw std::runtime_error("vkCreatePipelineLayout (composite) failed");

    // ── Shared vertex input / assembly / viewport / raster / multisample ───────
    VkPipelineVertexInputStateCreateInfo emptyVI{};
    emptyVI.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkPipelineInputAssemblyStateCreateInfo ia{};
    ia.sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineViewportStateCreateInfo vp{};
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1; vp.scissorCount = 1;

    VkDynamicState dynStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn{};
    dyn.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkPipelineRasterizationStateCreateInfo raster{};
    raster.sType       = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.cullMode    = VK_CULL_MODE_NONE;
    raster.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    raster.lineWidth   = 1.0f;

    VkPipelineMultisampleStateCreateInfo ms{};
    ms.sType                = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // ── OIT accumulation pipeline (subpass 1) ──────────────────────────────────
    auto oitVertMod = createShaderModule(readFile("shaders/vert.spv"));
    auto oitFragMod = createShaderModule(readFile("shaders/oitaccum.spv"));
    VkPipelineShaderStageCreateInfo oitStages[2] = {};
    oitStages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    oitStages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   oitStages[0].module = oitVertMod; oitStages[0].pName = "main";
    oitStages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    oitStages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; oitStages[1].module = oitFragMod; oitStages[1].pName = "main";

    // Reuse vertex input from createGraphicsPipeline (instance data bindings)
    VkVertexInputBindingDescription oitBindings[2] = {};
    oitBindings[0].binding = 0; oitBindings[0].stride = sizeof(Vertex);       oitBindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    oitBindings[1].binding = 1; oitBindings[1].stride = sizeof(InstanceData); oitBindings[1].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
    VkVertexInputAttributeDescription oitAttrs[11] = {};
    oitAttrs[0].binding = 0; oitAttrs[0].location = 0; oitAttrs[0].format = VK_FORMAT_R32G32B32_SFLOAT; oitAttrs[0].offset = offsetof(Vertex, pos);
    oitAttrs[9].binding = 0; oitAttrs[9].location = 9; oitAttrs[9].format = VK_FORMAT_R32G32B32_SFLOAT; oitAttrs[9].offset = offsetof(Vertex, nrm);
    oitAttrs[10].binding = 0; oitAttrs[10].location = 10; oitAttrs[10].format = VK_FORMAT_R32G32_SFLOAT; oitAttrs[10].offset = offsetof(Vertex, uv);
    for (int i = 0; i < 4; ++i) {
        oitAttrs[1+i].binding  = 1;
        oitAttrs[1+i].location = 1 + i;
        oitAttrs[1+i].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
        oitAttrs[1+i].offset   = (uint32_t)(offsetof(InstanceData, transform) + i * sizeof(float) * 4);
    }
    oitAttrs[5].binding = 1; oitAttrs[5].location = 5; oitAttrs[5].format = VK_FORMAT_R32G32B32A32_SFLOAT; oitAttrs[5].offset = (uint32_t)offsetof(InstanceData, color);
    oitAttrs[6].binding = 1; oitAttrs[6].location = 6; oitAttrs[6].format = VK_FORMAT_R32G32B32A32_SFLOAT; oitAttrs[6].offset = (uint32_t)offsetof(InstanceData, ambient);
    oitAttrs[7].binding = 1; oitAttrs[7].location = 7; oitAttrs[7].format = VK_FORMAT_R32_SINT;            oitAttrs[7].offset = (uint32_t)offsetof(InstanceData, materialType);
    oitAttrs[8].binding = 1; oitAttrs[8].location = 8; oitAttrs[8].format = VK_FORMAT_R32G32B32A32_SFLOAT; oitAttrs[8].offset = (uint32_t)offsetof(InstanceData, p0);
    VkPipelineVertexInputStateCreateInfo oitVI{};
    oitVI.sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    oitVI.vertexBindingDescriptionCount   = 2; oitVI.pVertexBindingDescriptions   = oitBindings;
    oitVI.vertexAttributeDescriptionCount = 11; oitVI.pVertexAttributeDescriptions = oitAttrs;

    // Depth test (against opaque) but NO depth write
    VkPipelineDepthStencilStateCreateInfo oitDS{};
    oitDS.sType            = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    oitDS.depthTestEnable  = VK_TRUE;
    oitDS.depthWriteEnable = VK_FALSE;
    oitDS.depthCompareOp   = VK_COMPARE_OP_LESS;

    // Two-target blend: accum=additive, reveal=multiplicative (1-alpha)
    VkPipelineColorBlendAttachmentState oitBlend[2] = {};
    oitBlend[0].blendEnable         = VK_TRUE;
    oitBlend[0].srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    oitBlend[0].dstColorBlendFactor = VK_BLEND_FACTOR_ONE;
    oitBlend[0].colorBlendOp        = VK_BLEND_OP_ADD;
    oitBlend[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    oitBlend[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    oitBlend[0].alphaBlendOp        = VK_BLEND_OP_ADD;
    oitBlend[0].colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                      VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    oitBlend[1].blendEnable         = VK_TRUE;
    oitBlend[1].srcColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    oitBlend[1].dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_COLOR;  // reveal *= (1-alpha)
    oitBlend[1].colorBlendOp        = VK_BLEND_OP_ADD;
    oitBlend[1].srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    oitBlend[1].dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    oitBlend[1].alphaBlendOp        = VK_BLEND_OP_ADD;
    oitBlend[1].colorWriteMask      = VK_COLOR_COMPONENT_R_BIT;

    VkPipelineColorBlendStateCreateInfo oitBlendCI{};
    oitBlendCI.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    oitBlendCI.attachmentCount = 2; oitBlendCI.pAttachments = oitBlend;

    VkGraphicsPipelineCreateInfo oitPCI{};
    oitPCI.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    oitPCI.stageCount          = 2;         oitPCI.pStages             = oitStages;
    oitPCI.pVertexInputState   = &oitVI;    oitPCI.pInputAssemblyState = &ia;
    oitPCI.pViewportState      = &vp;       oitPCI.pRasterizationState = &raster;
    oitPCI.pMultisampleState   = &ms;       oitPCI.pDepthStencilState  = &oitDS;
    oitPCI.pColorBlendState    = &oitBlendCI; oitPCI.pDynamicState     = &dyn;
    oitPCI.layout              = pipelineLayout;
    oitPCI.renderPass          = oitRenderPass;
    oitPCI.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &oitPCI, nullptr, &oitPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (OIT accum) failed");

    vkDestroyShaderModule(device, oitVertMod, nullptr);
    vkDestroyShaderModule(device, oitFragMod, nullptr);

    // ── Composite pipeline (subpass 2) ─────────────────────────────────────────
    auto compVertMod = createShaderModule(readFile("shaders/composite_vert.spv"));
    auto compFragMod = createShaderModule(readFile("shaders/composite_frag.spv"));
    VkPipelineShaderStageCreateInfo compStages[2] = {};
    compStages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    compStages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   compStages[0].module = compVertMod; compStages[0].pName = "main";
    compStages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    compStages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; compStages[1].module = compFragMod; compStages[1].pName = "main";

    // No depth test in composite pass
    VkPipelineDepthStencilStateCreateInfo compDS{};
    compDS.sType           = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    compDS.depthTestEnable = VK_FALSE; compDS.depthWriteEnable = VK_FALSE;

    // Blend OIT result over opaque scene with standard alpha blending
    VkPipelineColorBlendAttachmentState compBlend{};
    compBlend.blendEnable         = VK_TRUE;
    compBlend.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    compBlend.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    compBlend.colorBlendOp        = VK_BLEND_OP_ADD;
    compBlend.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    compBlend.dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    compBlend.alphaBlendOp        = VK_BLEND_OP_ADD;
    compBlend.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                    VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo compBlendCI{};
    compBlendCI.sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    compBlendCI.attachmentCount = 1; compBlendCI.pAttachments = &compBlend;

    VkGraphicsPipelineCreateInfo compPCI{};
    compPCI.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    compPCI.stageCount          = 2;           compPCI.pStages             = compStages;
    compPCI.pVertexInputState   = &emptyVI;    compPCI.pInputAssemblyState = &ia;
    compPCI.pViewportState      = &vp;         compPCI.pRasterizationState = &raster;
    compPCI.pMultisampleState   = &ms;         compPCI.pDepthStencilState  = &compDS;
    compPCI.pColorBlendState    = &compBlendCI; compPCI.pDynamicState      = &dyn;
    compPCI.layout              = compositePipelineLayout;
    compPCI.renderPass          = compositeRenderPass;
    compPCI.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &compPCI, nullptr, &compositePipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (composite) failed");

    vkDestroyShaderModule(device, compVertMod, nullptr);
    vkDestroyShaderModule(device, compFragMod, nullptr);
}

// ─── Opaque render pass (geometry, MSAA-conditional) ─────────────────────────
void Renderer::createOpaqueRenderPass() {
    VkSampleCountFlagBits samples = msaa8 ? VK_SAMPLE_COUNT_8_BIT : VK_SAMPLE_COUNT_1_BIT;

    if (!msaa8) {
        // Non-MSAA: swapchain color + depth
        VkAttachmentDescription atts[2] = {};
        atts[0].format        = swapFormat;
        atts[0].samples       = VK_SAMPLE_COUNT_1_BIT;
        atts[0].loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[0].storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
        atts[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[0].finalLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        atts[1].format         = VK_FORMAT_D32_SFLOAT;
        atts[1].samples        = VK_SAMPLE_COUNT_1_BIT;
        atts[1].loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[1].storeOp        = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[1].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorRef{ 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
        VkAttachmentReference depthRef{ 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

        VkSubpassDescription sp{};
        sp.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
        sp.colorAttachmentCount    = 1; sp.pColorAttachments    = &colorRef;
        sp.pDepthStencilAttachment = &depthRef;

        VkSubpassDependency dep{};
        dep.srcSubpass    = VK_SUBPASS_EXTERNAL; dep.dstSubpass = 0;
        dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dep.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dep.srcAccessMask = 0;
        dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                            VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo ci{};
        ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        ci.attachmentCount = 2;  ci.pAttachments  = atts;
        ci.subpassCount    = 1;  ci.pSubpasses    = &sp;
        ci.dependencyCount = 1;  ci.pDependencies = &dep;
        if (vkCreateRenderPass(device, &ci, nullptr, &opaqueRenderPass) != VK_SUCCESS)
            throw std::runtime_error("vkCreateRenderPass (opaque) failed");
    } else {
        // MSAA: att0=swapchain 1x (resolve), att1=MSAA depth 8x, att2=MSAA color 8x
        VkAttachmentDescription atts[3] = {};
        atts[0].format        = swapFormat;
        atts[0].samples       = VK_SAMPLE_COUNT_1_BIT;
        atts[0].loadOp        = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[0].storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
        atts[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[0].finalLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        atts[1].format         = VK_FORMAT_D32_SFLOAT;
        atts[1].samples        = samples;
        atts[1].loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[1].storeOp        = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[1].initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[1].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        atts[2].format        = swapFormat;
        atts[2].samples       = samples;
        atts[2].loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
        atts[2].storeOp       = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        atts[2].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        atts[2].finalLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference msaaColorRef{ 2, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
        VkAttachmentReference depthRef    { 1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };
        VkAttachmentReference resolveRef  { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

        VkSubpassDescription sp{};
        sp.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
        sp.colorAttachmentCount    = 1;  sp.pColorAttachments    = &msaaColorRef;
        sp.pDepthStencilAttachment = &depthRef;
        sp.pResolveAttachments     = &resolveRef;

        VkSubpassDependency dep{};
        dep.srcSubpass    = VK_SUBPASS_EXTERNAL; dep.dstSubpass = 0;
        dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dep.dstStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT |
                            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dep.srcAccessMask = 0;
        dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT |
                            VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo ci{};
        ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        ci.attachmentCount = 3;  ci.pAttachments  = atts;
        ci.subpassCount    = 1;  ci.pSubpasses    = &sp;
        ci.dependencyCount = 1;  ci.pDependencies = &dep;
        if (vkCreateRenderPass(device, &ci, nullptr, &opaqueRenderPass) != VK_SUCCESS)
            throw std::runtime_error("vkCreateRenderPass (opaque MSAA) failed");
    }
}

// ─── OIT accumulation render pass (persistent, 1x) ───────────────────────────
void Renderer::createOITAccumRenderPass() {
    // att0=accum, att1=reveal, att2=depth(read-only from opaque/prepass)
    VkAttachmentDescription atts[3] = {};
    atts[0].format        = VK_FORMAT_R16G16B16A16_SFLOAT;
    atts[0].samples       = VK_SAMPLE_COUNT_1_BIT;
    atts[0].loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
    atts[0].storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    atts[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[0].finalLayout   = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    atts[1].format        = VK_FORMAT_R16_SFLOAT;
    atts[1].samples       = VK_SAMPLE_COUNT_1_BIT;
    atts[1].loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
    atts[1].storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    atts[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[1].finalLayout   = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    atts[2].format         = VK_FORMAT_D32_SFLOAT;
    atts[2].samples        = VK_SAMPLE_COUNT_1_BIT;
    atts[2].loadOp         = VK_ATTACHMENT_LOAD_OP_LOAD;
    atts[2].storeOp        = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[2].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[2].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[2].initialLayout  = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
    atts[2].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference colors[2] = {
        { 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL },
        { 1, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL },
    };
    VkAttachmentReference depthRef{ 2, VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL };

    VkSubpassDescription sp{};
    sp.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount    = 2; sp.pColorAttachments    = colors;
    sp.pDepthStencilAttachment = &depthRef;

    // External → sp0: wait for depth writes from opaque/prepass
    VkSubpassDependency deps[2] = {};
    deps[0].srcSubpass    = VK_SUBPASS_EXTERNAL; deps[0].dstSubpass = 0;
    deps[0].srcStageMask  = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    deps[0].dstStageMask  = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    deps[0].srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    deps[0].dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
    // sp0 → External: accum/reveal color writes visible to composite fragment shader
    deps[1].srcSubpass    = 0; deps[1].dstSubpass = VK_SUBPASS_EXTERNAL;
    deps[1].srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    deps[1].dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    deps[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    deps[1].dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    VkRenderPassCreateInfo ci{};
    ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 3; ci.pAttachments  = atts;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 2; ci.pDependencies = deps;
    if (vkCreateRenderPass(device, &ci, nullptr, &oitRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (OIT accum) failed");
}

// ─── Composite render pass (persistent, 1x, reads accum/reveal via sampler) ──
void Renderer::createCompositeRenderPass() {
    VkAttachmentDescription att{};
    att.format        = swapFormat;
    att.samples       = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp        = VK_ATTACHMENT_LOAD_OP_LOAD;
    att.storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    att.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    att.finalLayout   = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorRef{ 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

    VkSubpassDescription sp{};
    sp.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1; sp.pColorAttachments = &colorRef;

    // External → sp0: wait for accum/reveal writes from OIT pass
    VkSubpassDependency dep{};
    dep.srcSubpass    = VK_SUBPASS_EXTERNAL; dep.dstSubpass = 0;
    dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dep.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    VkRenderPassCreateInfo ci{};
    ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 1; ci.pAttachments  = &att;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 1; ci.pDependencies = &dep;
    if (vkCreateRenderPass(device, &ci, nullptr, &compositeRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (composite) failed");
}

// ─── Depth prepass render pass (MSAA only, depth-only) ───────────────────────
void Renderer::createDepthPrepassRenderPass() {
    VkAttachmentDescription att{};
    att.format         = VK_FORMAT_D32_SFLOAT;
    att.samples        = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    att.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    att.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    att.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthRef{ 0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL };

    VkSubpassDescription sp{};
    sp.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.pDepthStencilAttachment = &depthRef;

    VkSubpassDependency dep{};
    dep.srcSubpass    = VK_SUBPASS_EXTERNAL; dep.dstSubpass = 0;
    dep.srcStageMask  = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.dstStageMask  = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dep.srcAccessMask = 0;
    dep.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo ci{};
    ci.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    ci.attachmentCount = 1; ci.pAttachments  = &att;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 1; ci.pDependencies = &dep;
    if (vkCreateRenderPass(device, &ci, nullptr, &depthPrepassRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (depth prepass) failed");
}

// ─── Depth prepass pipeline (MSAA only, vertex-only depth fill) ──────────────
void Renderer::createDepthPrepassPipeline() {
    auto vertMod = createShaderModule(readFile("shaders/vert.spv"));

    VkPipelineShaderStageCreateInfo stage{};
    stage.sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stage.stage  = VK_SHADER_STAGE_VERTEX_BIT;
    stage.module = vertMod; stage.pName = "main";

    VkVertexInputBindingDescription binds[2] = {};
    binds[0].binding = 0; binds[0].stride = sizeof(Vertex);       binds[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    binds[1].binding = 1; binds[1].stride = sizeof(InstanceData); binds[1].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;

    VkVertexInputAttributeDescription attrs[11] = {};
    attrs[0].binding = 0; attrs[0].location = 0; attrs[0].format = VK_FORMAT_R32G32B32_SFLOAT; attrs[0].offset = offsetof(Vertex, pos);
    attrs[9].binding = 0; attrs[9].location = 9; attrs[9].format = VK_FORMAT_R32G32B32_SFLOAT; attrs[9].offset = offsetof(Vertex, nrm);
    attrs[10].binding = 0; attrs[10].location = 10; attrs[10].format = VK_FORMAT_R32G32_SFLOAT; attrs[10].offset = offsetof(Vertex, uv);
    for (int i = 0; i < 4; ++i) {
        attrs[1+i].binding = 1; attrs[1+i].location = 1+i;
        attrs[1+i].format  = VK_FORMAT_R32G32B32A32_SFLOAT;
        attrs[1+i].offset  = (uint32_t)(offsetof(InstanceData, transform) + i * sizeof(float) * 4);
    }
    attrs[5].binding = 1; attrs[5].location = 5; attrs[5].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[5].offset = (uint32_t)offsetof(InstanceData, color);
    attrs[6].binding = 1; attrs[6].location = 6; attrs[6].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[6].offset = (uint32_t)offsetof(InstanceData, ambient);
    attrs[7].binding = 1; attrs[7].location = 7; attrs[7].format = VK_FORMAT_R32_SINT;            attrs[7].offset = (uint32_t)offsetof(InstanceData, materialType);
    attrs[8].binding = 1; attrs[8].location = 8; attrs[8].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[8].offset = (uint32_t)offsetof(InstanceData, p0);

    VkPipelineVertexInputStateCreateInfo vi{};
    vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vi.vertexBindingDescriptionCount   = 2;  vi.pVertexBindingDescriptions   = binds;
    vi.vertexAttributeDescriptionCount = 11; vi.pVertexAttributeDescriptions = attrs;

    VkPipelineInputAssemblyStateCreateInfo ia{};
    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineViewportStateCreateInfo vp{};
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1; vp.scissorCount = 1;

    VkDynamicState dynStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn{};
    dyn.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkPipelineRasterizationStateCreateInfo raster{};
    raster.sType     = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.cullMode    = VK_CULL_MODE_NONE;
    raster.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    raster.lineWidth   = 1.0f;

    VkPipelineMultisampleStateCreateInfo ms{};
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineDepthStencilStateCreateInfo ds{};
    ds.sType            = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    ds.depthTestEnable  = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    ds.depthCompareOp   = VK_COMPARE_OP_LESS;

    // No color attachments in depth-prepass render pass
    VkPipelineColorBlendStateCreateInfo blend{};
    blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend.attachmentCount = 0;

    VkGraphicsPipelineCreateInfo pci{};
    pci.sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pci.stageCount          = 1;         pci.pStages             = &stage;
    pci.pVertexInputState   = &vi;       pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vp;       pci.pRasterizationState = &raster;
    pci.pMultisampleState   = &ms;       pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &blend;    pci.pDynamicState       = &dyn;
    pci.layout              = pipelineLayout;
    pci.renderPass          = depthPrepassRenderPass;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &depthPrepassPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (depth prepass) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
}

// ─── MSAA images (per-swapchain-image color + single depth at 8x) ─────────────
void Renderer::createMSAAImages() {
    size_t n = swapImageViews.size();
    msaaColorImages.resize(n); msaaColorMemories.resize(n); msaaColorImageViews.resize(n);

    for (size_t i = 0; i < n; ++i) {
        VkImageCreateInfo ici{};
        ici.sType       = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ici.imageType   = VK_IMAGE_TYPE_2D;
        ici.format      = swapFormat;
        ici.extent      = { swapExtent.width, swapExtent.height, 1 };
        ici.mipLevels   = 1; ici.arrayLayers = 1;
        ici.samples     = VK_SAMPLE_COUNT_8_BIT;
        ici.tiling      = VK_IMAGE_TILING_OPTIMAL;
        ici.usage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
        if (vkCreateImage(device, &ici, nullptr, &msaaColorImages[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateImage (MSAA color) failed");

        VkMemoryRequirements req; vkGetImageMemoryRequirements(device, msaaColorImages[i], &req);
        VkMemoryAllocateInfo mai{};
        mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize  = req.size;
        mai.memoryTypeIndex = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        if (vkAllocateMemory(device, &mai, nullptr, &msaaColorMemories[i]) != VK_SUCCESS)
            throw std::runtime_error("vkAllocateMemory (MSAA color) failed");
        vkBindImageMemory(device, msaaColorImages[i], msaaColorMemories[i], 0);

        VkImageViewCreateInfo vci{};
        vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image    = msaaColorImages[i]; vci.viewType = VK_IMAGE_VIEW_TYPE_2D; vci.format = swapFormat;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        vci.subresourceRange.levelCount = 1; vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(device, &vci, nullptr, &msaaColorImageViews[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateImageView (MSAA color) failed");
    }

    // Single MSAA depth image (transient, one per swapchain image)
    {
        VkImageCreateInfo ici{};
        ici.sType     = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ici.imageType = VK_IMAGE_TYPE_2D;
        ici.format    = VK_FORMAT_D32_SFLOAT;
        ici.extent    = { swapExtent.width, swapExtent.height, 1 };
        ici.mipLevels = 1; ici.arrayLayers = 1;
        ici.samples   = VK_SAMPLE_COUNT_8_BIT;
        ici.tiling    = VK_IMAGE_TILING_OPTIMAL;
        ici.usage     = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
        if (vkCreateImage(device, &ici, nullptr, &msaaDepthImage) != VK_SUCCESS)
            throw std::runtime_error("vkCreateImage (MSAA depth) failed");

        VkMemoryRequirements req; vkGetImageMemoryRequirements(device, msaaDepthImage, &req);
        VkMemoryAllocateInfo mai{};
        mai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mai.allocationSize  = req.size;
        mai.memoryTypeIndex = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        if (vkAllocateMemory(device, &mai, nullptr, &msaaDepthMemory) != VK_SUCCESS)
            throw std::runtime_error("vkAllocateMemory (MSAA depth) failed");
        vkBindImageMemory(device, msaaDepthImage, msaaDepthMemory, 0);

        VkImageViewCreateInfo vci{};
        vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        vci.image    = msaaDepthImage; vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
        vci.format   = VK_FORMAT_D32_SFLOAT;
        vci.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
        vci.subresourceRange.levelCount = 1; vci.subresourceRange.layerCount = 1;
        if (vkCreateImageView(device, &vci, nullptr, &msaaDepthImageView) != VK_SUCCESS)
            throw std::runtime_error("vkCreateImageView (MSAA depth) failed");
    }
}

void Renderer::cleanupMSAAImages() {
    for (size_t i = 0; i < msaaColorImages.size(); ++i) {
        vkDestroyImageView(device, msaaColorImageViews[i], nullptr);
        vkDestroyImage(device, msaaColorImages[i], nullptr);
        vkFreeMemory(device, msaaColorMemories[i], nullptr);
    }
    msaaColorImages.clear(); msaaColorMemories.clear(); msaaColorImageViews.clear();
    if (msaaDepthImageView) { vkDestroyImageView(device, msaaDepthImageView, nullptr); msaaDepthImageView = VK_NULL_HANDLE; }
    if (msaaDepthImage)     { vkDestroyImage(device, msaaDepthImage, nullptr);         msaaDepthImage = VK_NULL_HANDLE; }
    if (msaaDepthMemory)    { vkFreeMemory(device, msaaDepthMemory, nullptr);          msaaDepthMemory = VK_NULL_HANDLE; }
}

// ─── Graphics pipeline ────────────────────────────────────────────────────────
VkShaderModule Renderer::createShaderModule(const std::vector<char>& code) {
    VkShaderModuleCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    ci.codeSize = code.size(); ci.pCode = reinterpret_cast<const uint32_t*>(code.data());
    VkShaderModule mod;
    if (vkCreateShaderModule(device, &ci, nullptr, &mod) != VK_SUCCESS)
        throw std::runtime_error("vkCreateShaderModule failed");
    return mod;
}

void Renderer::createGraphicsPipeline() {
    auto vertMod = createShaderModule(readFile("shaders/vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2] = {};
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    // Vertex input: binding 0 = per-vertex pos, binding 1 = per-instance InstanceData
    VkVertexInputBindingDescription bindings[2] = {};
    bindings[0].binding = 0; bindings[0].stride = sizeof(Vertex);        bindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindings[1].binding = 1; bindings[1].stride = sizeof(InstanceData);  bindings[1].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;

    // 11 attributes: pos(0), normal(9), uv(10), mat4 cols(1-4), color(5), Phong(6), matType(7), matParams(8)
    VkVertexInputAttributeDescription attrs[11] = {};
    attrs[0].binding = 0; attrs[0].location = 0; attrs[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attrs[0].offset = offsetof(Vertex, pos);
    attrs[9].binding = 0; attrs[9].location = 9; attrs[9].format = VK_FORMAT_R32G32B32_SFLOAT;
    attrs[9].offset = offsetof(Vertex, nrm);
    attrs[10].binding = 0; attrs[10].location = 10; attrs[10].format = VK_FORMAT_R32G32_SFLOAT;
    attrs[10].offset = offsetof(Vertex, uv);
    for (int i = 0; i < 4; ++i) {
        attrs[1+i].binding  = 1;
        attrs[1+i].location = 1 + i;
        attrs[1+i].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
        attrs[1+i].offset   = (uint32_t)(offsetof(InstanceData, transform) + i * sizeof(float) * 4);
    }
    attrs[5].binding  = 1; attrs[5].location = 5;
    attrs[5].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    attrs[5].offset   = (uint32_t)offsetof(InstanceData, color);
    attrs[6].binding  = 1; attrs[6].location = 6;
    attrs[6].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    attrs[6].offset   = (uint32_t)offsetof(InstanceData, ambient);
    attrs[7].binding  = 1; attrs[7].location = 7;
    attrs[7].format   = VK_FORMAT_R32_SINT;
    attrs[7].offset   = (uint32_t)offsetof(InstanceData, materialType);
    attrs[8].binding  = 1; attrs[8].location = 8;
    attrs[8].format   = VK_FORMAT_R32G32B32A32_SFLOAT;
    attrs[8].offset   = (uint32_t)offsetof(InstanceData, p0);

    VkPipelineVertexInputStateCreateInfo vi{};
    vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vi.vertexBindingDescriptionCount   = 2; vi.pVertexBindingDescriptions   = bindings;
    vi.vertexAttributeDescriptionCount = 11; vi.pVertexAttributeDescriptions = attrs;

    VkPipelineInputAssemblyStateCreateInfo ia{};
    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineViewportStateCreateInfo vp{};
    vp.sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1;   // counts required even with dynamic state
    vp.scissorCount  = 1;

    VkDynamicState dynStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn{};
    dyn.sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = 2;
    dyn.pDynamicStates    = dynStates;

    VkPipelineRasterizationStateCreateInfo raster{};
    raster.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.cullMode    = VK_CULL_MODE_NONE;       // see all faces while rotating
    raster.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    raster.lineWidth   = 1.0f;

    VkPipelineMultisampleStateCreateInfo ms{};
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.rasterizationSamples = msaa8 ? VK_SAMPLE_COUNT_8_BIT : VK_SAMPLE_COUNT_1_BIT;

    VkPipelineDepthStencilStateCreateInfo ds{};
    ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    ds.depthTestEnable  = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    ds.depthCompareOp   = VK_COMPARE_OP_LESS;

    VkPipelineColorBlendAttachmentState blendAttach{};
    blendAttach.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                 VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo blend{};
    blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend.attachmentCount = 1; blend.pAttachments = &blendAttach;

    VkPushConstantRange pcRange{};
    pcRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pcRange.offset = 0;
    pcRange.size   = 208;  // 2*Mat4 + 3*vec4 + shaderMode + hasAlbedoTex + hasEnvMap + iblIntensity + selMask[4]

    VkPipelineLayoutCreateInfo layoutCI{};
    layoutCI.sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    layoutCI.setLayoutCount         = 1;
    layoutCI.pSetLayouts            = &texDescLayout;
    layoutCI.pushConstantRangeCount = 1; layoutCI.pPushConstantRanges = &pcRange;
    if (vkCreatePipelineLayout(device, &layoutCI, nullptr, &pipelineLayout) != VK_SUCCESS)
        throw std::runtime_error("vkCreatePipelineLayout failed");

    VkGraphicsPipelineCreateInfo pci{};
    pci.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pci.stageCount = 2;           pci.pStages             = stages;
    pci.pVertexInputState   = &vi; pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vp;  pci.pRasterizationState = &raster;
    pci.pMultisampleState   = &ms;  pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &blend; pci.pDynamicState     = &dyn;
    pci.layout = pipelineLayout;  pci.renderPass = opaqueRenderPass;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &graphicsPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines failed");

    // Wireframe pipeline: polygon mode LINE + depth bias so overlay sits in front of solid
    VkPipelineRasterizationStateCreateInfo wfRaster = raster;
    wfRaster.polygonMode             = VK_POLYGON_MODE_LINE;
    wfRaster.depthBiasEnable         = VK_TRUE;
    wfRaster.depthBiasConstantFactor = -2.0f;
    wfRaster.depthBiasSlopeFactor    = -1.0f;
    wfRaster.lineWidth               = 1.5f;
    pci.pRasterizationState = &wfRaster;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &wireframePipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (wireframe) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

// ─── Skybox pipeline ──────────────────────────────────────────────────────────
void Renderer::createSkyboxPipeline() {
    auto vertMod = createShaderModule(readFile("shaders/skybox_vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/skybox_frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2] = {};
    stages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    // No vertex input — vertex index drives the fullscreen triangle
    VkPipelineVertexInputStateCreateInfo vi{};
    vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkPipelineInputAssemblyStateCreateInfo ia{};
    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineViewportStateCreateInfo vp{};
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.viewportCount = 1; vp.scissorCount = 1;

    VkDynamicState dynStates[] = { VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR };
    VkPipelineDynamicStateCreateInfo dyn{};
    dyn.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkPipelineRasterizationStateCreateInfo raster{};
    raster.sType     = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.polygonMode = VK_POLYGON_MODE_FILL;
    raster.cullMode    = VK_CULL_MODE_NONE;
    raster.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    raster.lineWidth   = 1.0f;

    VkPipelineMultisampleStateCreateInfo ms{};
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.rasterizationSamples = msaa8 ? VK_SAMPLE_COUNT_8_BIT : VK_SAMPLE_COUNT_1_BIT;

    // No depth test/write — skybox is pure background, geometry renders over it
    VkPipelineDepthStencilStateCreateInfo ds{};
    ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    ds.depthTestEnable  = VK_FALSE;
    ds.depthWriteEnable = VK_FALSE;

    VkPipelineColorBlendAttachmentState blendAttach{};
    blendAttach.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                                 VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo blend{};
    blend.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    blend.attachmentCount = 1; blend.pAttachments = &blendAttach;

    VkGraphicsPipelineCreateInfo pci{};
    pci.sType            = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pci.stageCount       = 2;   pci.pStages             = stages;
    pci.pVertexInputState   = &vi;  pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vp;  pci.pRasterizationState = &raster;
    pci.pMultisampleState   = &ms;  pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &blend; pci.pDynamicState     = &dyn;
    pci.layout    = pipelineLayout;
    pci.renderPass = opaqueRenderPass;
    pci.subpass   = 0;

    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &skyboxPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (skybox) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

// ─── Framebuffers ─────────────────────────────────────────────────────────────
void Renderer::createOpaqueFramebuffers() {
    size_t n = swapImageViews.size();
    opaqueFramebuffers.resize(n);
    for (size_t i = 0; i < n; ++i) {
        VkFramebufferCreateInfo ci{};
        ci.sType      = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass = opaqueRenderPass;
        ci.width = swapExtent.width; ci.height = swapExtent.height; ci.layers = 1;
        if (!msaa8) {
            VkImageView atts[] = { swapImageViews[i], depthImageView };
            ci.attachmentCount = 2; ci.pAttachments = atts;
            if (vkCreateFramebuffer(device, &ci, nullptr, &opaqueFramebuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("vkCreateFramebuffer (opaque) failed");
        } else {
            // att0=swap(resolve), att1=msaaDepth, att2=msaaColor
            VkImageView atts[] = { swapImageViews[i], msaaDepthImageView, msaaColorImageViews[i] };
            ci.attachmentCount = 3; ci.pAttachments = atts;
            if (vkCreateFramebuffer(device, &ci, nullptr, &opaqueFramebuffers[i]) != VK_SUCCESS)
                throw std::runtime_error("vkCreateFramebuffer (opaque MSAA) failed");
        }
    }
}

void Renderer::createOITFramebuffers() {
    size_t n = swapImageViews.size();
    oitFramebuffers.resize(n);
    for (size_t i = 0; i < n; ++i) {
        VkImageView atts[] = { accumImageViews[i], revealImageViews[i], depthImageView };
        VkFramebufferCreateInfo ci{};
        ci.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass      = oitRenderPass;
        ci.attachmentCount = 3; ci.pAttachments = atts;
        ci.width = swapExtent.width; ci.height = swapExtent.height; ci.layers = 1;
        if (vkCreateFramebuffer(device, &ci, nullptr, &oitFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (OIT) failed");
    }
}

void Renderer::createCompositeFramebuffers() {
    size_t n = swapImageViews.size();
    compositeFramebuffers.resize(n);
    for (size_t i = 0; i < n; ++i) {
        VkImageView atts[] = { swapImageViews[i] };
        VkFramebufferCreateInfo ci{};
        ci.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass      = compositeRenderPass;
        ci.attachmentCount = 1; ci.pAttachments = atts;
        ci.width = swapExtent.width; ci.height = swapExtent.height; ci.layers = 1;
        if (vkCreateFramebuffer(device, &ci, nullptr, &compositeFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (composite) failed");
    }
}

void Renderer::createDepthPrepassFramebuffers() {
    size_t n = swapImageViews.size();
    depthPrepassFramebuffers.resize(n);
    for (size_t i = 0; i < n; ++i) {
        VkImageView atts[] = { depthImageView };
        VkFramebufferCreateInfo ci{};
        ci.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        ci.renderPass      = depthPrepassRenderPass;
        ci.attachmentCount = 1; ci.pAttachments = atts;
        ci.width = swapExtent.width; ci.height = swapExtent.height; ci.layers = 1;
        if (vkCreateFramebuffer(device, &ci, nullptr, &depthPrepassFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (depth prepass) failed");
    }
}

// ─── Geometry buffers ─────────────────────────────────────────────────────────
static std::vector<Vertex>   g_roundedVerts;
static std::vector<uint16_t> g_roundedIdxs;

void Renderer::createVertexBuffer() {
    generateRoundedCube(g_roundedVerts, g_roundedIdxs);
    VkDeviceSize size = g_roundedVerts.size() * sizeof(Vertex);
    createBuffer(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 vertexBuffer, vertexMemory);
    void* data; vkMapMemory(device, vertexMemory, 0, size, 0, &data);
    memcpy(data, g_roundedVerts.data(), size); vkUnmapMemory(device, vertexMemory);
}

void Renderer::createIndexBuffer() {
    cubeIndexCount = (uint32_t)g_roundedIdxs.size();
    VkDeviceSize size = g_roundedIdxs.size() * sizeof(uint16_t);
    createBuffer(size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 indexBuffer, indexMemory);
    void* data; vkMapMemory(device, indexMemory, 0, size, 0, &data);
    memcpy(data, g_roundedIdxs.data(), size); vkUnmapMemory(device, indexMemory);
}

void Renderer::loadGltf(const std::string& path) {
    if (gltfLoaded) {
        vkDeviceWaitIdle(device);
        if (gltfInstanceMapped) { vkUnmapMemory(device, gltfInstanceMemory); gltfInstanceMapped = nullptr; }
        vkDestroyBuffer(device, gltfVertexBuffer,   nullptr); vkFreeMemory(device, gltfVertexMemory,   nullptr);
        vkDestroyBuffer(device, gltfIndexBuffer,    nullptr); vkFreeMemory(device, gltfIndexMemory,    nullptr);
        vkDestroyBuffer(device, gltfInstanceBuffer, nullptr); vkFreeMemory(device, gltfInstanceMemory, nullptr);
        gltfVertexBuffer = gltfIndexBuffer = gltfInstanceBuffer = VK_NULL_HANDLE;
        gltfLoaded = false;
        if (_input) _input->setMeshPickContext({}, 0.0f, false);
    }
    std::vector<Vertex> gverts; std::vector<uint32_t> gidxs;
    if (!parseMeshGltf(path, gverts, gidxs, gltfError)) return;
    uploadMeshBuffers(gverts, gidxs);
}

// Shared GPU upload used by both loadGltf and loadObj
void Renderer::uploadMeshBuffers(const std::vector<Vertex>& gverts,
                                  const std::vector<uint32_t>& gidxs) {
    {
        VkDeviceSize sz = gverts.size() * sizeof(Vertex);
        createBuffer(sz, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     gltfVertexBuffer, gltfVertexMemory);
        void* d; vkMapMemory(device, gltfVertexMemory, 0, sz, 0, &d);
        memcpy(d, gverts.data(), sz); vkUnmapMemory(device, gltfVertexMemory);
    }
    gltfIndexCount = (uint32_t)gidxs.size();
    {
        VkDeviceSize sz = gidxs.size() * sizeof(uint32_t);
        createBuffer(sz, VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     gltfIndexBuffer, gltfIndexMemory);
        void* d; vkMapMemory(device, gltfIndexMemory, 0, sz, 0, &d);
        memcpy(d, gidxs.data(), sz); vkUnmapMemory(device, gltfIndexMemory);
    }
    {
        gltfMaterial = _input->state.defaultMaterial;
        InstanceData inst{};
        inst.transform[0] = inst.transform[5] = inst.transform[10] = inst.transform[15] = 1.0f;
        inst.color[0]    = gltfMaterial.color[0];
        inst.color[1]    = gltfMaterial.color[1];
        inst.color[2]    = gltfMaterial.color[2];
        inst.color[3]    = gltfMaterial.alpha;
        inst.ambient     = gltfMaterial.ambient;
        inst.diffuse     = gltfMaterial.diffuse;
        inst.specular    = gltfMaterial.specular;
        inst.shininess   = gltfMaterial.shininess;
        inst.materialType= gltfMaterial.materialType;
        inst.p0 = gltfMaterial.p0; inst.p1 = gltfMaterial.p1;
        inst.p2 = gltfMaterial.p2; inst.p3 = gltfMaterial.p3;
        VkDeviceSize sz = sizeof(InstanceData);
        createBuffer(sz, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                     gltfInstanceBuffer, gltfInstanceMemory);
        vkMapMemory(device, gltfInstanceMemory, 0, sz, 0, &gltfInstanceMapped);
        memcpy(gltfInstanceMapped, &inst, sz);
    }
    gltfLoaded = true;
    gltfError.clear();

    // Compute bounding sphere for mouse picking
    if (!gverts.empty()) {
        Vec3 center{0, 0, 0};
        for (const auto& v : gverts) {
            center.x += v.pos[0]; center.y += v.pos[1]; center.z += v.pos[2];
        }
        float inv = 1.0f / (float)gverts.size();
        center.x *= inv; center.y *= inv; center.z *= inv;
        float radius = 0.0f;
        for (const auto& v : gverts) {
            float dx = v.pos[0]-center.x, dy = v.pos[1]-center.y, dz = v.pos[2]-center.z;
            float d = std::sqrt(dx*dx + dy*dy + dz*dz);
            if (d > radius) radius = d;
        }
        if (_input) _input->setMeshPickContext(center, radius, true);
    }
}

void Renderer::loadObj(const std::string& path) {
    if (gltfLoaded) {
        vkDeviceWaitIdle(device);
        if (gltfInstanceMapped) { vkUnmapMemory(device, gltfInstanceMemory); gltfInstanceMapped = nullptr; }
        vkDestroyBuffer(device, gltfVertexBuffer,   nullptr); vkFreeMemory(device, gltfVertexMemory,   nullptr);
        vkDestroyBuffer(device, gltfIndexBuffer,    nullptr); vkFreeMemory(device, gltfIndexMemory,    nullptr);
        vkDestroyBuffer(device, gltfInstanceBuffer, nullptr); vkFreeMemory(device, gltfInstanceMemory, nullptr);
        gltfVertexBuffer = gltfIndexBuffer = gltfInstanceBuffer = VK_NULL_HANDLE;
        gltfLoaded = false;
        if (_input) _input->setMeshPickContext({}, 0.0f, false);
    }
    std::vector<Vertex> gverts; std::vector<uint32_t> gidxs;
    if (!parseMeshObj(path, gverts, gidxs, gltfError)) return;
    uploadMeshBuffers(gverts, gidxs);
}

void Renderer::createInstanceBuffer() {
    instanceData = buildInstanceData(_input->state.defaultMaterial);
    // Cache positions for ray picking (extracted from transforms)
    for (int i = 0; i < INSTANCE_COUNT; i++) {
        const Mat4& m = instanceData[i].transform;
        cubePositions[i] = { m[12], m[13], m[14] };
    }
    VkDeviceSize size = sizeof(instanceData);
    createBuffer(size, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 instanceBuffer, instanceMemory);
    // Persistently mapped — host-coherent so no explicit flush needed
    vkMapMemory(device, instanceMemory, 0, size, 0, &instanceMapped);
    memcpy(instanceMapped, instanceData.data(), size);

    _input->setPickContext(&swapExtent, &cubePositions);
}

// ─── Command pool / buffers ───────────────────────────────────────────────────
void Renderer::createCommandPool() {
    auto idx = findQueueFamilies(physicalDevice, surface);
    VkCommandPoolCreateInfo ci{};
    ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    ci.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    ci.queueFamilyIndex = *idx.graphics;
    if (vkCreateCommandPool(device, &ci, nullptr, &commandPool) != VK_SUCCESS)
        throw std::runtime_error("vkCreateCommandPool failed");
}

void Renderer::createCommandBuffers() {
    commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    VkCommandBufferAllocateInfo ai{};
    ai.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    ai.commandPool = commandPool; ai.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    ai.commandBufferCount = (uint32_t)commandBuffers.size();
    if (vkAllocateCommandBuffers(device, &ai, commandBuffers.data()) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateCommandBuffers failed");
}

void Renderer::recordCommandBuffer(VkCommandBuffer cb, uint32_t imageIndex) {
    VkCommandBufferBeginInfo bi{};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    vkBeginCommandBuffer(cb, &bi);

    VkViewport viewport{ 0, 0, (float)swapExtent.width, (float)swapExtent.height, 0, 1 };
    VkRect2D   scissor { {0, 0}, swapExtent };

    auto insertLabel = [&](const char* name) {
        if (pfnCmdInsertLabel) {
            VkDebugUtilsLabelEXT lbl{VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT};
            lbl.pLabelName = name;
            pfnCmdInsertLabel(cb, &lbl);
        }
    };

    // Read scene state from input handler (needed for mvp in depth prepass)
    const SceneInput& s = _input->state;
    float aspect = (float)swapExtent.width / (float)swapExtent.height;
    Mat4 proj  = perspective(1.0472f, aspect, 0.1f, 100.0f);
    Vec3 eye   = {s.camTarget.x, s.camTarget.y, s.camTarget.z - s.zoomDist};
    Mat4 view  = lookAt(eye, s.camTarget, {0.0f, 1.0f, 0.0f});
    Mat4 model = s.arcball.matrix();
    Mat4 mv    = mat4mul(view, model);
    Mat4 mvp   = mat4mul(proj, mv);

    // ── Depth prepass (MSAA only) ─────────────────────────────────────────────
    if (msaa8) {
        insertLabel("Depth Prepass");
        VkClearValue depthClear{}; depthClear.depthStencil = {1.0f, 0};
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = depthPrepassRenderPass;
        rpi.framebuffer       = depthPrepassFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount   = 1; rpi.pClearValues = &depthClear;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, depthPrepassPipeline);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        // Draw all geometry for depth (same push constants as opaque below)
        VkBuffer     prepassVbufs[]   = { vertexBuffer, instanceBuffer };
        VkDeviceSize prepassOffsets[] = { 0, 0 };
        struct alignas(4) DepthPC { Mat4 mvp; Mat4 mv; float rest[208/4 - 32]; } depthPC{};
        depthPC.mvp = mvp; depthPC.mv = mv;
        vkCmdPushConstants(cb, pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, 208, &depthPC);
        vkCmdBindVertexBuffers(cb, 0, 2, prepassVbufs, prepassOffsets);
        vkCmdBindIndexBuffer(cb, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        vkCmdDrawIndexed(cb, cubeIndexCount, INSTANCE_COUNT, 0, 0, 0);
        if (gltfLoaded) {
            VkBuffer gbufsD[2]      = { gltfVertexBuffer, gltfInstanceBuffer };
            VkDeviceSize goffsD[2]  = { 0, 0 };
            vkCmdBindVertexBuffers(cb, 0, 2, gbufsD, goffsD);
            vkCmdBindIndexBuffer(cb, gltfIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(cb, gltfIndexCount, 1, 0, 0, 0);
        }
        vkCmdEndRenderPass(cb);

        // Barrier: depth prepass write → OIT depth read
        VkImageMemoryBarrier db{VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
        db.oldLayout           = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        db.newLayout           = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        db.srcAccessMask       = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        db.dstAccessMask       = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
        db.image               = depthImage;
        db.subresourceRange    = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};
        vkCmdPipelineBarrier(cb,
            VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            0, 0, nullptr, 0, nullptr, 1, &db);
    }

    // ── Opaque render pass ────────────────────────────────────────────────────
    insertLabel("Opaque Pass");
    VkClearValue opaqueClearColor{};  opaqueClearColor.color = {0.87f, 0.89f, 0.92f, 1.0f};
    VkClearValue opaqueClearDepth{};  opaqueClearDepth.depthStencil = {1.0f, 0};
    VkClearValue opaqueClears[3] = { opaqueClearColor, opaqueClearDepth, opaqueClearColor };
    uint32_t opaqueClearCount = msaa8 ? 3 : 2;  // MSAA: swap(resolve) + msaaDepth + msaaColor
    // For MSAA, order is att0=swap att1=depth att2=msaaColor; clear[0]=swap(unused), [1]=depth, [2]=msaaColor
    opaqueClears[0].color = {0.87f, 0.89f, 0.92f, 1.0f};  // att0: swap resolve (unused for MSAA clear)
    opaqueClears[1].depthStencil = {1.0f, 0};              // att1: depth
    opaqueClears[2].color = {0.87f, 0.89f, 0.92f, 1.0f};  // att2: msaaColor (MSAA only)

    {
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass      = opaqueRenderPass;
        rpi.framebuffer     = opaqueFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount = opaqueClearCount;
        rpi.pClearValues    = opaqueClears;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
    }
    vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);

    // Bind texture descriptor set (set=0) once for all subpasses
    vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout,
        0, 1, &texDescSet, 0, nullptr);
    vkCmdSetViewport(cb, 0, 1, &viewport);
    vkCmdSetScissor(cb, 0, 1, &scissor);

    VkBuffer     vbufs[]   = { vertexBuffer, instanceBuffer };
    VkDeviceSize offsets[] = { 0, 0 };

    // Push constant layout (std430, 208 bytes):
    //   mvp(64) + mv(64) + selColor(16) + lightPos(16) + lightColor(16)
    //   + shaderMode(4) + hasAlbedoTex(4) + hasEnvMap(4) + iblIntensity(4) + selMask[4](16) = 208 bytes
    struct PushConst {
        Mat4     mvp;
        Mat4     mv;
        float    selColor[4];
        float    lightPos[4];    // xyz = view-space light position (world-fixed), w unused
        float    lightColor[4];  // xyz = rgb * intensity, w unused
        int      shaderMode;
        int      hasAlbedoTex;
        int      hasEnvMap;
        float    iblIntensity;
        uint32_t selectionMask[4];
    };
    static_assert(sizeof(PushConst) == 208);

    // ── Skybox: draw before geometry so it sits behind everything ────────────
    if (envLoaded) {
        // Strip translation from mv to get pure view-rotation, then invert the
        // combined proj×rotation to build a clip→world direction matrix.
        Mat4 viewRot = mv;
        viewRot[12] = viewRot[13] = viewRot[14] = 0.0f;
        Mat4 envProj = proj;
        envProj[0] *= s.envZoom; envProj[5] *= s.envZoom; // scale focal lengths (Alt+Ctrl zoom)
        Mat4 envRot  = quatToMat4(s.envArcball.current);  // Alt+MMB rotate/pan
        PushConst skyPC{};
        skyPC.mvp          = mat4mul(envRot, mat4inverse(mat4mul(envProj, viewRot))); // repurposes mvp slot
        skyPC.hasEnvMap    = 1;
        skyPC.iblIntensity = s.iblIntensity;
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, skyboxPipeline);
        vkCmdPushConstants(cb, pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0, sizeof(skyPC), &skyPC);
        vkCmdDraw(cb, 3, 1, 0, 0);
        // Geometry pipeline restored by the draw() lambda below
    }

    // Selection bitmask
    uint32_t selMask[4] = {};
    for (int idx : s.selectedCubes)
        if (idx >= 0 && idx < INSTANCE_COUNT)
            selMask[idx / 32] |= (1u << (idx % 32));

    // Transform world-space light position to view space using view matrix only
    // (w=1 for position; NOT multiplied by model/arcball so light stays world-fixed)
    const LightParams& lp = s.light;
    float wpx = lp.pos[0], wpy = lp.pos[1], wpz = lp.pos[2];
    float vpx = view[0]*wpx + view[4]*wpy + view[8]*wpz  + view[12];
    float vpy = view[1]*wpx + view[5]*wpy + view[9]*wpz  + view[13];
    float vpz = view[2]*wpx + view[6]*wpy + view[10]*wpz + view[14];

    const Vec3& sc = s.selectionColor;

    auto draw = [&](VkPipeline pipe, int shaderMode) {
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, pipe);
        PushConst pc{};
        pc.mvp         = mvp;
        pc.mv          = mv;
        pc.selColor[0] = sc.x; pc.selColor[1] = sc.y; pc.selColor[2] = sc.z; pc.selColor[3] = 1.0f;
        pc.lightPos[0] = vpx;  pc.lightPos[1] = vpy;  pc.lightPos[2] = vpz;  pc.lightPos[3] = 1.0f;
        pc.lightColor[0] = lp.color[0]*lp.intensity;
        pc.lightColor[1] = lp.color[1]*lp.intensity;
        pc.lightColor[2] = lp.color[2]*lp.intensity;
        pc.lightColor[3] = 0.0f;
        pc.shaderMode    = shaderMode;
        pc.hasAlbedoTex  = albedoLoaded ? 1 : 0;
        pc.hasEnvMap     = envLoaded ? 1 : 0;
        pc.iblIntensity  = s.iblIntensity;
        pc.selectionMask[0] = selMask[0]; pc.selectionMask[1] = selMask[1];
        pc.selectionMask[2] = selMask[2]; pc.selectionMask[3] = selMask[3];

        vkCmdPushConstants(cb, pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(pc), &pc);
        vkCmdBindVertexBuffers(cb, 0, 2, vbufs, offsets);
        vkCmdBindIndexBuffer(cb, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        vkCmdDrawIndexed(cb, cubeIndexCount, INSTANCE_COUNT, 0, 0, 0);

        // Draw GLTF/OBJ mesh with its own push constant (may have albedo texture)
        if (gltfLoaded) {
            PushConst meshPC = pc;
            bool sel = _input && _input->state.meshSelected;
            meshPC.selectionMask[0] = sel ? 0xFFFFFFFFu : 0u;
            meshPC.selectionMask[1] = meshPC.selectionMask[2] = meshPC.selectionMask[3] = 0u;
            meshPC.hasAlbedoTex = albedoLoaded ? 1 : 0;
            vkCmdPushConstants(cb, pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(meshPC), &meshPC);
            VkBuffer gbufs[2] = { gltfVertexBuffer, gltfInstanceBuffer };
            VkDeviceSize goffs[2] = { 0, 0 };
            vkCmdBindVertexBuffers(cb, 0, 2, gbufs, goffs);
            vkCmdBindIndexBuffer(cb, gltfIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(cb, gltfIndexCount, 1, 0, 0, 0);
        }
    };

    // ── Subpass 0: opaque geometry (transparent fragments discarded in shader) ──
    switch (s.displayMode) {
        case DisplayMode::Solid:          draw(graphicsPipeline,   SHADER_MODE_SOLID);     break;
        case DisplayMode::Wireframe:      draw(wireframePipeline,  SHADER_MODE_WIREFRAME); break;
        case DisplayMode::SolidWireframe: draw(graphicsPipeline,   SHADER_MODE_SOLID);
                                          draw(wireframePipeline,  SHADER_MODE_WIREFRAME); break;
        case DisplayMode::Unlit:          draw(graphicsPipeline,   SHADER_MODE_UNLIT);     break;
        case DisplayMode::Normals:        draw(graphicsPipeline,   SHADER_MODE_NORMALS);   break;
    }
    ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), cb);
    vkCmdEndRenderPass(cb);

    // ── Depth barrier: opaque depth write → OIT depth read (non-MSAA path) ────
    // (MSAA path already did the barrier after depth prepass above)
    if (!msaa8) {
        VkImageMemoryBarrier b{VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
        b.oldLayout        = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
        b.newLayout        = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        b.srcAccessMask    = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        b.dstAccessMask    = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
        b.image            = depthImage;
        b.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};
        vkCmdPipelineBarrier(cb,
            VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
            0, 0, nullptr, 0, nullptr, 1, &b);
    }

    // ── OIT accumulation render pass ──────────────────────────────────────────
    insertLabel("OIT Accum Pass");
    {
        VkClearValue oitClears[3] = {};
        oitClears[0].color = {0.0f, 0.0f, 0.0f, 0.0f};  // accum: start at 0
        oitClears[1].color = {1.0f, 0.0f, 0.0f, 0.0f};  // reveal: start at 1
        // oitClears[2] is unused (depth uses LOAD_OP_LOAD) but index still needed
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = oitRenderPass;
        rpi.framebuffer       = oitFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount   = 3; rpi.pClearValues = oitClears;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout,
            0, 1, &texDescSet, 0, nullptr);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        {
            int oitMode = (s.displayMode == DisplayMode::Wireframe) ? SHADER_MODE_WIREFRAME
                        : (s.displayMode == DisplayMode::Unlit)     ? SHADER_MODE_UNLIT
                        : (s.displayMode == DisplayMode::Normals)   ? SHADER_MODE_NORMALS
                        : SHADER_MODE_SOLID;
            draw(oitPipeline, oitMode);
        }
        vkCmdEndRenderPass(cb);
    }

    // ── Composite render pass (blends OIT over opaque via sampler2D) ──────────
    insertLabel("OIT Composite Pass");
    {
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = compositeRenderPass;
        rpi.framebuffer       = compositeFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, compositePipeline);
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, compositePipelineLayout,
            0, 1, &compositeDescSets[imageIndex], 0, nullptr);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        vkCmdDraw(cb, 3, 1, 0, 0);
        vkCmdEndRenderPass(cb);
    }

    // ── Highlight pass: render selected objects into R8 mask + own depth ────────
    insertLabel("Highlight Pass");
    // Uses its own depth buffer so occluded objects are still recorded in the mask.
    // The masking pass will compare against main scene depth to dim occluded regions.
    {
        VkClearValue hlClears[2] = {};
        hlClears[0].color        = {};          // R8 mask = 0.0
        hlClears[1].depthStencil = {1.0f, 0};  // depth = far
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = highlightRenderPass;
        rpi.framebuffer       = highlightFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount   = 2; rpi.pClearValues = hlClears;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, highlightPipeline);
        // Rebind IBL descriptor set (may be invalidated by composite pass using a different layout)
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout,
            0, 1, &texDescSet, 0, nullptr);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);

        // Cubes: highlight shader discards non-selected via selectionMask
        PushConst hlPC{};
        hlPC.mvp = mvp; hlPC.mv = mv;
        hlPC.selColor[0] = sc.x; hlPC.selColor[1] = sc.y; hlPC.selColor[2] = sc.z; hlPC.selColor[3] = 1.0f;
        hlPC.lightPos[0] = vpx;  hlPC.lightPos[1] = vpy;  hlPC.lightPos[2] = vpz;  hlPC.lightPos[3] = 1.0f;
        hlPC.lightColor[0] = lp.color[0]*lp.intensity;
        hlPC.lightColor[1] = lp.color[1]*lp.intensity;
        hlPC.lightColor[2] = lp.color[2]*lp.intensity;
        hlPC.lightColor[3] = 0.0f;
        hlPC.hasAlbedoTex  = 0;
        hlPC.hasEnvMap     = envLoaded ? 1 : 0;
        hlPC.iblIntensity  = s.iblIntensity;
        hlPC.selectionMask[0] = selMask[0]; hlPC.selectionMask[1] = selMask[1];
        hlPC.selectionMask[2] = selMask[2]; hlPC.selectionMask[3] = selMask[3];
        vkCmdPushConstants(cb, pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(hlPC), &hlPC);
        vkCmdBindVertexBuffers(cb, 0, 2, vbufs, offsets);
        vkCmdBindIndexBuffer(cb, indexBuffer, 0, VK_INDEX_TYPE_UINT16);
        vkCmdDrawIndexed(cb, cubeIndexCount, INSTANCE_COUNT, 0, 0, 0);

        // Mesh: draw only if selected (use all-selected mask so frag passes for instance 0)
        if (gltfLoaded && s.meshSelected) {
            PushConst meshHlPC = hlPC;
            meshHlPC.selectionMask[0] = 0xFFFFFFFFu;
            meshHlPC.selectionMask[1] = meshHlPC.selectionMask[2] = meshHlPC.selectionMask[3] = 0u;
            vkCmdPushConstants(cb, pipelineLayout,
                VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(meshHlPC), &meshHlPC);
            VkBuffer gbufs2[2]      = { gltfVertexBuffer, gltfInstanceBuffer };
            VkDeviceSize goffs2[2]  = { 0, 0 };
            vkCmdBindVertexBuffers(cb, 0, 2, gbufs2, goffs2);
            vkCmdBindIndexBuffer(cb, gltfIndexBuffer, 0, VK_INDEX_TYPE_UINT32);
            vkCmdDrawIndexed(cb, gltfIndexCount, 1, 0, 0, 0);
        }
        vkCmdEndRenderPass(cb);
    }

    // ── Barrier: highlight color+depth visible to masking pass; main depth visible ──
    {
        VkImageMemoryBarrier barriers[2]{};
        // highlightImages[i]: COLOR_ATTACHMENT_OPTIMAL→SHADER_READ_ONLY (color write → shader read)
        barriers[0].sType            = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barriers[0].oldLayout        = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barriers[0].newLayout        = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barriers[0].srcAccessMask    = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barriers[0].dstAccessMask    = VK_ACCESS_SHADER_READ_BIT;
        barriers[0].image            = highlightImages[imageIndex];
        barriers[0].subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
        // depthImage (main scene): already READ_ONLY after OIT, ensure visible to masking frag
        barriers[1].sType            = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barriers[1].oldLayout        = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        barriers[1].newLayout        = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        barriers[1].srcAccessMask    = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
        barriers[1].dstAccessMask    = VK_ACCESS_SHADER_READ_BIT;
        barriers[1].image            = depthImage;
        barriers[1].subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};
        vkCmdPipelineBarrier(cb,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, nullptr, 0, nullptr, 2, barriers);
    }

    // ── Masking pass: dim highlight mask where selected object is occluded ────
    insertLabel("Masking Pass");
    {
        VkClearValue mClear{};  // R8 = 0.0
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = maskingRenderPass;
        rpi.framebuffer       = maskingFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount   = 1; rpi.pClearValues = &mClear;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, maskingPipeline);
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS,
            maskingPipelineLayout, 0, 1, &maskingDescSets[imageIndex], 0, nullptr);
        float occAlpha = s.occlusionAlpha;
        vkCmdPushConstants(cb, maskingPipelineLayout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(float), &occAlpha);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        vkCmdDraw(cb, 3, 1, 0, 0);
        vkCmdEndRenderPass(cb);
    }

    // ── Barrier: masked highlight visible to outline frag shader reads ────────
    {
        VkImageMemoryBarrier b{VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER};
        b.sType            = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        b.oldLayout        = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        b.newLayout        = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        b.srcAccessMask    = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        b.dstAccessMask    = VK_ACCESS_SHADER_READ_BIT;
        b.image            = maskedHighlightImages[imageIndex];
        b.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
        vkCmdPipelineBarrier(cb,
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
            0, 0, nullptr, 0, nullptr, 1, &b);
    }

    // ── Outline pass: dilation → outline image ────────────────────────────────
    insertLabel("Outline Pass");
    {
        VkClearValue clr{}; // zero RGBA
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = outlineRenderPass;
        rpi.framebuffer       = outlineFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        rpi.clearValueCount   = 1; rpi.pClearValues = &clr;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, outlinePipeline);
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS,
            outlinePipelineLayout, 0, 1, &outlineDescSets[imageIndex], 0, nullptr);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        struct OutlinePC { float texelX, texelY, thickness, antialiased, r, g, b, a; } opc{};
        opc.texelX      = 1.0f / (float)swapExtent.width;
        opc.texelY      = 1.0f / (float)swapExtent.height;
        opc.thickness   = s.outlineThickness;
        opc.antialiased = s.outlineAntialiased ? 1.0f : 0.0f;
        const Vec3& oc = s.outlineColor;
        opc.r = oc.x; opc.g = oc.y; opc.b = oc.z; opc.a = 1.0f;
        vkCmdPushConstants(cb, outlinePipelineLayout,
            VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(opc), &opc);
        vkCmdDraw(cb, 3, 1, 0, 0);
        vkCmdEndRenderPass(cb);
    }

    // ── Blend pass: alpha-blend outline image onto swapchain ─────────────────
    insertLabel("Blend Pass");
    {
        VkRenderPassBeginInfo rpi{VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
        rpi.renderPass        = blendRenderPass;
        rpi.framebuffer       = blendFramebuffers[imageIndex];
        rpi.renderArea.extent = swapExtent;
        vkCmdBeginRenderPass(cb, &rpi, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(cb, VK_PIPELINE_BIND_POINT_GRAPHICS, blendPipeline);
        vkCmdBindDescriptorSets(cb, VK_PIPELINE_BIND_POINT_GRAPHICS,
            blendPipelineLayout, 0, 1, &blendDescSets[imageIndex], 0, nullptr);
        vkCmdSetViewport(cb, 0, 1, &viewport);
        vkCmdSetScissor(cb, 0, 1, &scissor);
        float texelSize[2] = { 1.0f / (float)swapExtent.width, 1.0f / (float)swapExtent.height };
        vkCmdPushConstants(cb, blendPipelineLayout,
            VK_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(texelSize), texelSize);
        vkCmdDraw(cb, 3, 1, 0, 0);
        vkCmdEndRenderPass(cb);
    }

    vkEndCommandBuffer(cb);
}

// ─── Sync objects ─────────────────────────────────────────────────────────────
void Renderer::createSyncObjects() {
    imageAvailable.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinished.resize(MAX_FRAMES_IN_FLIGHT);
    inFlight.resize(MAX_FRAMES_IN_FLIGHT);
    VkSemaphoreCreateInfo sci{ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    VkFenceCreateInfo fci{ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    fci.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        if (vkCreateSemaphore(device, &sci, nullptr, &imageAvailable[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device, &sci, nullptr, &renderFinished[i]) != VK_SUCCESS ||
            vkCreateFence(device, &fci, nullptr, &inFlight[i]) != VK_SUCCESS)
            throw std::runtime_error("Failed to create sync objects");
    }
}

// ─── Swapchain recreation ─────────────────────────────────────────────────────
void Renderer::cleanupSwapchain() {
    // Outline/masking resources (per-swapchain-image)
    vkDestroyDescriptorPool(device, blendDescPool, nullptr);
    blendDescPool = VK_NULL_HANDLE; blendDescSets.clear();
    vkDestroyDescriptorPool(device, outlineDescPool, nullptr);
    outlineDescPool = VK_NULL_HANDLE; outlineDescSets.clear();
    vkDestroyDescriptorPool(device, maskingDescPool, nullptr);
    maskingDescPool = VK_NULL_HANDLE; maskingDescSets.clear();
    for (auto fb : blendFramebuffers)     vkDestroyFramebuffer(device, fb, nullptr);
    for (auto fb : outlineFramebuffers)   vkDestroyFramebuffer(device, fb, nullptr);
    for (auto fb : highlightFramebuffers) vkDestroyFramebuffer(device, fb, nullptr);
    for (auto fb : maskingFramebuffers)   vkDestroyFramebuffer(device, fb, nullptr);
    blendFramebuffers.clear(); outlineFramebuffers.clear();
    highlightFramebuffers.clear(); maskingFramebuffers.clear();
    for (size_t i = 0; i < highlightImages.size(); i++) {
        vkDestroyImageView(device, highlightImageViews[i], nullptr);
        vkDestroyImage(device, highlightImages[i], nullptr);
        vkFreeMemory(device, highlightMemories[i], nullptr);
        vkDestroyImageView(device, maskDepthImageViews[i], nullptr);
        vkDestroyImage(device, maskDepthImages[i], nullptr);
        vkFreeMemory(device, maskDepthMemories[i], nullptr);
        vkDestroyImageView(device, maskedHighlightImageViews[i], nullptr);
        vkDestroyImage(device, maskedHighlightImages[i], nullptr);
        vkFreeMemory(device, maskedHighlightMemories[i], nullptr);
        vkDestroyImageView(device, outlineImageViews[i], nullptr);
        vkDestroyImage(device, outlineImages[i], nullptr);
        vkFreeMemory(device, outlineMemories[i], nullptr);
    }
    highlightImages.clear(); highlightMemories.clear(); highlightImageViews.clear();
    maskDepthImages.clear(); maskDepthMemories.clear(); maskDepthImageViews.clear();
    maskedHighlightImages.clear(); maskedHighlightMemories.clear(); maskedHighlightImageViews.clear();
    outlineImages.clear(); outlineMemories.clear(); outlineImageViews.clear();

    // OIT descriptor pool also frees the descriptor sets
    vkDestroyDescriptorPool(device, oitDescPool, nullptr);
    oitDescPool = VK_NULL_HANDLE; compositeDescSets.clear();

    for (size_t i = 0; i < accumImages.size(); ++i) {
        vkDestroyImageView(device, accumImageViews[i], nullptr);
        vkDestroyImage(device, accumImages[i], nullptr);
        vkFreeMemory(device, accumMemories[i], nullptr);
        vkDestroyImageView(device, revealImageViews[i], nullptr);
        vkDestroyImage(device, revealImages[i], nullptr);
        vkFreeMemory(device, revealMemories[i], nullptr);
    }
    accumImages.clear(); accumMemories.clear(); accumImageViews.clear();
    revealImages.clear(); revealMemories.clear(); revealImageViews.clear();

    // MSAA images
    cleanupMSAAImages();

    vkDestroyImageView(device, depthImageView, nullptr);
    vkDestroyImage(device, depthImage, nullptr);
    vkFreeMemory(device, depthMemory, nullptr);
    for (auto fb : depthPrepassFramebuffers) vkDestroyFramebuffer(device, fb, nullptr);
    depthPrepassFramebuffers.clear();
    for (auto fb : compositeFramebuffers)    vkDestroyFramebuffer(device, fb, nullptr);
    compositeFramebuffers.clear();
    for (auto fb : oitFramebuffers)          vkDestroyFramebuffer(device, fb, nullptr);
    oitFramebuffers.clear();
    for (auto fb : opaqueFramebuffers)       vkDestroyFramebuffer(device, fb, nullptr);
    opaqueFramebuffers.clear();
    if (opaqueRenderPass) {
        vkDestroyRenderPass(device, opaqueRenderPass, nullptr);
        opaqueRenderPass = VK_NULL_HANDLE;
    }
    for (auto iv : swapImageViews) vkDestroyImageView(device, iv, nullptr);
    vkDestroySwapchainKHR(device, swapchain, nullptr);
}

void Renderer::recreateSwapchain() {
    int w = 0, h = 0;
    while (!w || !h) { glfwGetFramebufferSize(window, &w, &h); glfwWaitEvents(); }
    vkDeviceWaitIdle(device);
    cleanupSwapchain();
    createSwapchain(); createImageViews(); createDepthResources();
    if (msaa8) createMSAAImages();
    createOpaqueRenderPass();
    createOITImages(); createOITDescriptorSets();
    createOpaqueFramebuffers(); createOITFramebuffers(); createCompositeFramebuffers();
    if (msaa8) createDepthPrepassFramebuffers();
    createHighlightImages(); createHighlightFramebuffers(); createOutlineFramebuffers();
    createMaskingFramebuffers(); createMaskingDescriptorSets();
    createOutlineDescriptorSets();
    createBlendFramebuffers(); createBlendDescriptorSets();
}

// ─── Draw frame ───────────────────────────────────────────────────────────────
void Renderer::drawFrame() {
    vkWaitForFences(device, 1, &inFlight[currentFrame], VK_TRUE, UINT64_MAX);
    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(device, swapchain, UINT64_MAX,
        imageAvailable[currentFrame], VK_NULL_HANDLE, &imageIndex);
    if (result == VK_ERROR_OUT_OF_DATE_KHR) { recreateSwapchain(); return; }
    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        throw std::runtime_error("vkAcquireNextImageKHR failed");
    vkResetFences(device, 1, &inFlight[currentFrame]);
    vkResetCommandBuffer(commandBuffers[currentFrame], 0);
    renderUI();
    recordCommandBuffer(commandBuffers[currentFrame], imageIndex);

    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo si{};
    si.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.waitSemaphoreCount = 1;   si.pWaitSemaphores   = &imageAvailable[currentFrame];
    si.pWaitDstStageMask  = &waitStage;
    si.commandBufferCount = 1;   si.pCommandBuffers   = &commandBuffers[currentFrame];
    si.signalSemaphoreCount = 1; si.pSignalSemaphores = &renderFinished[currentFrame];
    if (vkQueueSubmit(graphicsQueue, 1, &si, inFlight[currentFrame]) != VK_SUCCESS)
        throw std::runtime_error("vkQueueSubmit failed");

    VkPresentInfoKHR pi{};
    pi.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    pi.waitSemaphoreCount = 1; pi.pWaitSemaphores = &renderFinished[currentFrame];
    pi.swapchainCount = 1;     pi.pSwapchains     = &swapchain;
    pi.pImageIndices  = &imageIndex;
    result = vkQueuePresentKHR(presentQueue, &pi);
    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
        framebufferResized = false; recreateSwapchain();
    }
    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

// ─── ImGui ────────────────────────────────────────────────────────────────────
void Renderer::initImGui() {
    // imgui 1.92+ manages its own descriptor pool when DescriptorPoolSize > 0
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;   // don't write imgui.ini

    ImGui_ImplGlfw_InitForVulkan(window, true);

    ImGui_ImplVulkan_InitInfo initInfo{};
    initInfo.ApiVersion            = VK_API_VERSION_1_0;
    initInfo.Instance              = instance;
    initInfo.PhysicalDevice        = physicalDevice;
    initInfo.Device                = device;
    initInfo.QueueFamily           = graphicsQueueFamily;
    initInfo.Queue                 = graphicsQueue;
    initInfo.DescriptorPoolSize    = 8;  // let imgui manage its own pool
    initInfo.MinImageCount         = 2;
    initInfo.ImageCount            = (uint32_t)swapImages.size();
    initInfo.PipelineInfoMain.RenderPass  = opaqueRenderPass;
    initInfo.PipelineInfoMain.MSAASamples = msaa8 ? VK_SAMPLE_COUNT_8_BIT : VK_SAMPLE_COUNT_1_BIT;
    ImGui_ImplVulkan_Init(&initInfo);
    // Font textures are uploaded automatically in imgui 1.92+
}

void Renderer::cleanupImGui() {
    vkDeviceWaitIdle(device);
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::renderUI() {
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos (ImVec2(10, 10),  ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(260, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene");

    // ── Renderer ──────────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::TextDisabled("Active: Vulkan");
        if (ImGui::Button("Switch to OpenGL"))
            _input->state.switchRenderer = true;
        bool msaaCheck = msaa8;
        if (ImGui::Checkbox("MSAA 8x", &msaaCheck) && msaaCheck != msaa8) {
            msaa8 = msaaCheck;
            msaaChanged = true;
        }
    }

    // ── Display mode ─────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Display Mode", ImGuiTreeNodeFlags_DefaultOpen)) {
        int mode = (int)_input->state.displayMode;
        ImGui::RadioButton("Solid",           &mode, (int)DisplayMode::Solid);
        ImGui::RadioButton("Wireframe",       &mode, (int)DisplayMode::Wireframe);
        ImGui::RadioButton("Solid+Wireframe", &mode, (int)DisplayMode::SolidWireframe);
        ImGui::RadioButton("Unlit",           &mode, (int)DisplayMode::Unlit);
        ImGui::RadioButton("Normals",         &mode, (int)DisplayMode::Normals);
        _input->state.displayMode = (DisplayMode)mode;

        ImGui::Spacing();
        Vec3& sc = _input->state.selectionColor;
        float hcol[3] = { sc.x, sc.y, sc.z };
        ImGui::Text("Highlight"); ImGui::SameLine();
        if (ImGui::ColorEdit3("##selcolor", hcol,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_PickerHueWheel |
                ImGuiColorEditFlags_NoLabel))
            sc = { hcol[0], hcol[1], hcol[2] };
        Vec3& oc = _input->state.outlineColor;
        float ocol[3] = { oc.x, oc.y, oc.z };
        ImGui::Text("Outline"); ImGui::SameLine();
        if (ImGui::ColorEdit3("##outcolor", ocol,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_PickerHueWheel |
                ImGuiColorEditFlags_NoLabel))
            oc = { ocol[0], ocol[1], ocol[2] };
        ImGui::SliderFloat("Outline Thickness", &_input->state.outlineThickness, 1.0f, 8.0f, "%.1f");
        ImGui::Checkbox("Antialiased Outline", &_input->state.outlineAntialiased);
        ImGui::SliderFloat("Occluded Alpha",    &_input->state.occlusionAlpha,   0.0f, 1.0f, "%.2f");
    }

    // ── Lighting ─────────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_DefaultOpen)) {
        LightParams& lp = _input->state.light;
        ImGui::SliderFloat("X##lx", &lp.pos[0], -20.0f, 20.0f, "%.1f");
        ImGui::SliderFloat("Y##ly", &lp.pos[1], -20.0f, 20.0f, "%.1f");
        ImGui::SliderFloat("Z##lz", &lp.pos[2], -20.0f, 20.0f, "%.1f");
        ImGui::Text("Color");    ImGui::SameLine();
        ImGui::ColorEdit3("##lcolor", lp.color,
            ImGuiColorEditFlags_NoInputs |
            ImGuiColorEditFlags_PickerHueWheel |
            ImGuiColorEditFlags_NoLabel);
        ImGui::SliderFloat("Intensity", &lp.intensity, 0.0f, 5.0f, "%.2f");
    }

    // ── Material ─────────────────────────────────────────────────────────────
    {
        bool meshSel     = gltfLoaded && _input->state.meshSelected;
        const auto& csel = _input->state.selectedCubes;

        char matHeader[64];
        if (meshSel)
            snprintf(matHeader, sizeof(matHeader), "Material (Loaded Model)");
        else if (csel.size() == 1)
            snprintf(matHeader, sizeof(matHeader), "Material (1 cube)");
        else if (csel.size() > 1)
            snprintf(matHeader, sizeof(matHeader), "Material (%d cubes)", (int)csel.size());
        else
            snprintf(matHeader, sizeof(matHeader), "Material (Default)");

        if (ImGui::CollapsingHeader(matHeader, ImGuiTreeNodeFlags_DefaultOpen)) {
            if (meshSel) {
                // Edit loaded model's material
                if (materialEditor("mat",
                        gltfMaterial.color, gltfMaterial.alpha,
                        gltfMaterial.ambient, gltfMaterial.diffuse,
                        gltfMaterial.specular, gltfMaterial.shininess,
                        gltfMaterial.materialType,
                        gltfMaterial.p0, gltfMaterial.p1,
                        gltfMaterial.p2, gltfMaterial.p3)
                    && gltfInstanceMapped)
                {
                    InstanceData* inst = static_cast<InstanceData*>(gltfInstanceMapped);
                    inst->color[0]     = gltfMaterial.color[0];
                    inst->color[1]     = gltfMaterial.color[1];
                    inst->color[2]     = gltfMaterial.color[2];
                    inst->color[3]     = gltfMaterial.alpha;
                    inst->ambient      = gltfMaterial.ambient;
                    inst->diffuse      = gltfMaterial.diffuse;
                    inst->specular     = gltfMaterial.specular;
                    inst->shininess    = gltfMaterial.shininess;
                    inst->materialType = gltfMaterial.materialType;
                    inst->p0 = gltfMaterial.p0; inst->p1 = gltfMaterial.p1;
                    inst->p2 = gltfMaterial.p2; inst->p3 = gltfMaterial.p3;
                }
            } else if (!csel.empty()) {
                // Edit selected cubes' material (read from first, write to all)
                int first = *csel.begin();
                InstanceData& ref = instanceData[first];
                float col[3] = { ref.color[0], ref.color[1], ref.color[2] };
                float alpha  = ref.color[3];
                if (materialEditor("mat",
                        col, alpha,
                        ref.ambient, ref.diffuse, ref.specular, ref.shininess,
                        ref.materialType,
                        ref.p0, ref.p1, ref.p2, ref.p3)) {
                    for (int idx : csel) {
                        instanceData[idx].color[0]     = col[0];
                        instanceData[idx].color[1]     = col[1];
                        instanceData[idx].color[2]     = col[2];
                        instanceData[idx].color[3]     = alpha;
                        instanceData[idx].ambient      = ref.ambient;
                        instanceData[idx].diffuse      = ref.diffuse;
                        instanceData[idx].specular     = ref.specular;
                        instanceData[idx].shininess    = ref.shininess;
                        instanceData[idx].materialType = ref.materialType;
                        instanceData[idx].p0           = ref.p0;
                        instanceData[idx].p1           = ref.p1;
                        instanceData[idx].p2           = ref.p2;
                        instanceData[idx].p3           = ref.p3;
                    }
                    memcpy(instanceMapped, instanceData.data(), sizeof(instanceData));
                }
            } else {
                // No selection — changes apply to all cubes immediately
                Material& dm = _input->state.defaultMaterial;
                if (materialEditor("mat",
                        dm.color, dm.alpha,
                        dm.ambient, dm.diffuse,
                        dm.specular, dm.shininess,
                        dm.materialType,
                        dm.p0, dm.p1,
                        dm.p2, dm.p3)) {
                    for (auto& d : instanceData) {
                        d.color[0]     = dm.color[0];
                        d.color[1]     = dm.color[1];
                        d.color[2]     = dm.color[2];
                        d.color[3]     = dm.alpha;
                        d.ambient      = dm.ambient;
                        d.diffuse      = dm.diffuse;
                        d.specular     = dm.specular;
                        d.shininess    = dm.shininess;
                        d.materialType = dm.materialType;
                        d.p0           = dm.p0;
                        d.p1           = dm.p1;
                        d.p2           = dm.p2;
                        d.p3           = dm.p3;
                    }
                    memcpy(instanceMapped, instanceData.data(), sizeof(instanceData));
                }
            }
        }
    }

    // ── Texture & Environment ─────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Texture & Environment", ImGuiTreeNodeFlags_DefaultOpen)) {
        // Albedo texture
        if (ImGui::Button("Load Albedo Texture...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFilter = "Images\0*.png;*.jpg;*.jpeg;*.bmp\0All Files\0*.*\0";
            ofn.lpstrFile   = buf; ofn.nMaxFile = sizeof(buf);
            ofn.Flags       = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle  = "Load Albedo Texture";
            if (GetOpenFileNameA(&ofn)) loadAlbedoTexture(std::string(buf));
        }
        if (albedoLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Clear##atex")) {
                albedoLoaded = false;
                _input->state.albedoTexPath.clear();
            }
            ImGui::TextDisabled("%s", _input->state.albedoTexPath.c_str());
        }

        ImGui::Spacing();

        // HDR environment map
        if (ImGui::Button("Load HDR Environment...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFilter = "HDR Images\0*.hdr;*.exr\0All Files\0*.*\0";
            ofn.lpstrFile   = buf; ofn.nMaxFile = sizeof(buf);
            ofn.Flags       = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle  = "Load HDR Environment";
            if (GetOpenFileNameA(&ofn)) loadEnvMap(std::string(buf));
        }
        if (envLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Clear##env")) {
                envLoaded = false;
                _input->state.envMapPath.clear();
            }
            ImGui::SliderFloat("IBL Intensity", &_input->state.iblIntensity, 0.0f, 5.0f, "%.2f");
            ImGui::TextDisabled("%s", _input->state.envMapPath.c_str());
        }
    }

    // ── 3D Model loader ───────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("3D Model", ImGuiTreeNodeFlags_DefaultOpen)) {
        static char gltfPath[512] = "";
        auto dispatchLoad = [&](const char* p) {
            std::string s(p);
            auto ext = s.size() >= 4 ? s.substr(s.size() - 4) : "";
            // lowercase the extension
            for (auto& c : ext) c = (char)tolower((unsigned char)c);
            if (ext == ".obj") loadObj(s);
            else               loadGltf(s);
        };

        if (ImGui::Button("Open File...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner   = nullptr;
            ofn.lpstrFilter = "3D Models\0*.gltf;*.glb;*.obj\0"
                              "GLTF\0*.gltf;*.glb\0"
                              "Wavefront OBJ\0*.obj\0"
                              "All Files\0*.*\0";
            ofn.lpstrFile   = buf;
            ofn.nMaxFile    = sizeof(buf);
            ofn.Flags       = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle  = "Open 3D Model";
            if (GetOpenFileNameA(&ofn)) {
                memcpy(gltfPath, buf, sizeof(gltfPath));
                dispatchLoad(gltfPath);
            }
        }
        // Also allow manual path entry + load
        ImGui::SetNextItemWidth(-1);
        if (ImGui::InputText("##gltfpath", gltfPath, sizeof(gltfPath),
                             ImGuiInputTextFlags_EnterReturnsTrue))
            dispatchLoad(gltfPath);
        if (gltfLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Unload")) {
                vkDeviceWaitIdle(device);
                if (gltfInstanceMapped) { vkUnmapMemory(device, gltfInstanceMemory); gltfInstanceMapped = nullptr; }
                vkDestroyBuffer(device, gltfVertexBuffer,   nullptr); vkFreeMemory(device, gltfVertexMemory,   nullptr);
                vkDestroyBuffer(device, gltfIndexBuffer,    nullptr); vkFreeMemory(device, gltfIndexMemory,    nullptr);
                vkDestroyBuffer(device, gltfInstanceBuffer, nullptr); vkFreeMemory(device, gltfInstanceMemory, nullptr);
                gltfVertexBuffer = gltfIndexBuffer = gltfInstanceBuffer = VK_NULL_HANDLE;
                gltfLoaded = false; gltfError.clear();
                if (_input) _input->setMeshPickContext({}, 0.0f, false);
            }
            ImGui::TextDisabled("%u tris — click to select", gltfIndexCount / 3);
        }
        if (!gltfError.empty())
            ImGui::TextColored(ImVec4(1,0.3f,0.3f,1), "%s", gltfError.c_str());
    }

    ImGui::End();
    ImGui::Render();
}

// ─── Texture helpers ──────────────────────────────────────────────────────────
VkCommandBuffer Renderer::beginSingleTimeCommands() {
    VkCommandBufferAllocateInfo ai{};
    ai.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    ai.commandPool        = commandPool;
    ai.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    ai.commandBufferCount = 1;
    VkCommandBuffer cb;
    vkAllocateCommandBuffers(device, &ai, &cb);
    VkCommandBufferBeginInfo bi{};
    bi.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bi.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    vkBeginCommandBuffer(cb, &bi);
    return cb;
}

void Renderer::endSingleTimeCommands(VkCommandBuffer cb) {
    vkEndCommandBuffer(cb);
    VkSubmitInfo si{};
    si.sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    si.commandBufferCount = 1;
    si.pCommandBuffers    = &cb;
    vkQueueSubmit(graphicsQueue, 1, &si, VK_NULL_HANDLE);
    vkQueueWaitIdle(graphicsQueue);
    vkFreeCommandBuffers(device, commandPool, 1, &cb);
}

void Renderer::createVkImage(uint32_t w, uint32_t h, uint32_t layers, uint32_t mipLevels,
                              VkFormat fmt, VkImageCreateFlags flags,
                              VkImage& img, VkDeviceMemory& mem) {
    VkImageCreateInfo ici{};
    ici.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ici.flags         = flags;
    ici.imageType     = VK_IMAGE_TYPE_2D;
    ici.format        = fmt;
    ici.extent        = { w, h, 1 };
    ici.mipLevels     = mipLevels;
    ici.arrayLayers   = layers;
    ici.samples       = VK_SAMPLE_COUNT_1_BIT;
    ici.tiling        = VK_IMAGE_TILING_OPTIMAL;
    ici.usage         = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
                        VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    ici.sharingMode   = VK_SHARING_MODE_EXCLUSIVE;
    ici.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    if (vkCreateImage(device, &ici, nullptr, &img) != VK_SUCCESS)
        throw std::runtime_error("vkCreateImage (texture) failed");
    VkMemoryRequirements req; vkGetImageMemoryRequirements(device, img, &req);
    VkMemoryAllocateInfo mai{};
    mai.sType            = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    mai.allocationSize   = req.size;
    mai.memoryTypeIndex  = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    if (vkAllocateMemory(device, &mai, nullptr, &mem) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateMemory (texture) failed");
    vkBindImageMemory(device, img, mem, 0);
}

void Renderer::uploadTexture2D(VkTex& tex, const float* rgba32f, uint32_t w, uint32_t h,
                                bool genMips, bool /*srgb*/) {
    uint32_t mipLevels = genMips
        ? (uint32_t)std::floor(std::log2(std::max(w, h))) + 1
        : 1;
    createVkImage(w, h, 1, mipLevels, VK_FORMAT_R8G8B8A8_UNORM, 0, tex.image, tex.memory);

    // Staging
    VkDeviceSize sz = (VkDeviceSize)w * h * 4;
    VkBuffer staging; VkDeviceMemory stagingMem;
    createBuffer(sz, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 staging, stagingMem);
    void* mapped; vkMapMemory(device, stagingMem, 0, sz, 0, &mapped);
    uint8_t* dst = static_cast<uint8_t*>(mapped);
    for (uint32_t i = 0; i < w * h; ++i) {
        dst[i*4+0] = (uint8_t)std::min(rgba32f[i*4+0] * 255.0f, 255.0f);
        dst[i*4+1] = (uint8_t)std::min(rgba32f[i*4+1] * 255.0f, 255.0f);
        dst[i*4+2] = (uint8_t)std::min(rgba32f[i*4+2] * 255.0f, 255.0f);
        dst[i*4+3] = (uint8_t)std::min(rgba32f[i*4+3] * 255.0f, 255.0f);
    }
    vkUnmapMemory(device, stagingMem);

    auto cb = beginSingleTimeCommands();
    // Transition all mips+layers to TRANSFER_DST
    VkImageMemoryBarrier barrier{};
    barrier.sType            = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout        = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout        = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image            = tex.image;
    barrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, mipLevels, 0, 1 };
    barrier.srcAccessMask    = 0;
    barrier.dstAccessMask    = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);

    VkBufferImageCopy region{};
    region.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    region.imageExtent      = { w, h, 1 };
    vkCmdCopyBufferToImage(cb, staging, tex.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

    if (genMips && mipLevels > 1) {
        // Blit mip chain
        int32_t mw = (int32_t)w, mh = (int32_t)h;
        for (uint32_t m = 1; m < mipLevels; ++m) {
            VkImageMemoryBarrier blit_barrier = barrier;
            blit_barrier.subresourceRange.baseMipLevel = m - 1;
            blit_barrier.subresourceRange.levelCount   = 1;
            blit_barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            blit_barrier.newLayout     = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            blit_barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            blit_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                                 0, 0, nullptr, 0, nullptr, 1, &blit_barrier);
            int32_t nw = std::max(mw / 2, 1), nh = std::max(mh / 2, 1);
            VkImageBlit blit{};
            blit.srcSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, m-1, 0, 1 };
            blit.srcOffsets[1]  = { mw, mh, 1 };
            blit.dstSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, m,   0, 1 };
            blit.dstOffsets[1]  = { nw, nh, 1 };
            vkCmdBlitImage(cb, tex.image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
                               tex.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                               1, &blit, VK_FILTER_LINEAR);
            // Transition previous mip to SHADER_READ
            blit_barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            blit_barrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            blit_barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
            blit_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
            vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                                 0, 0, nullptr, 0, nullptr, 1, &blit_barrier);
            mw = nw; mh = nh;
        }
        // Transition last mip
        barrier.subresourceRange.baseMipLevel = mipLevels - 1;
        barrier.subresourceRange.levelCount   = 1;
        barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                             0, 0, nullptr, 0, nullptr, 1, &barrier);
    } else {
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount   = mipLevels;
        barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
        vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                             0, 0, nullptr, 0, nullptr, 1, &barrier);
    }
    endSingleTimeCommands(cb);
    vkDestroyBuffer(device, staging, nullptr);
    vkFreeMemory(device, stagingMem, nullptr);

    // Image view
    VkImageViewCreateInfo vci{};
    vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image    = tex.image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format   = VK_FORMAT_R8G8B8A8_UNORM;
    vci.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, mipLevels, 0, 1 };
    vkCreateImageView(device, &vci, nullptr, &tex.view);

    // Sampler
    VkSamplerCreateInfo sci{};
    sci.sType        = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sci.magFilter    = VK_FILTER_LINEAR;
    sci.minFilter    = VK_FILTER_LINEAR;
    sci.mipmapMode   = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    sci.mipLodBias   = 0.0f;
    sci.minLod       = 0.0f;
    sci.maxLod       = (float)mipLevels;
    sci.anisotropyEnable = anisotropySupported ? VK_TRUE : VK_FALSE;
    sci.maxAnisotropy    = anisotropySupported ? maxAnisotropy : 1.0f;
    vkCreateSampler(device, &sci, nullptr, &tex.sampler);
}

// facesMips[face][mip] = float RGBA data (baseW>>mip × baseH>>mip × 4 floats)
void Renderer::uploadCubemapMipped(VkTex& tex,
                                    const std::vector<std::vector<std::vector<float>>>& facesMips,
                                    uint32_t baseW, uint32_t baseH, uint32_t mipLevels) {
    createVkImage(baseW, baseH, 6, mipLevels, VK_FORMAT_R16G16B16A16_SFLOAT,
                  VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, tex.image, tex.memory);

    // Compute total staging size
    VkDeviceSize totalSz = 0;
    for (uint32_t f = 0; f < 6; ++f)
        for (uint32_t m = 0; m < mipLevels; ++m)
            totalSz += facesMips[f][m].size() * sizeof(uint16_t);

    VkBuffer staging; VkDeviceMemory stagingMem;
    createBuffer(totalSz, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 staging, stagingMem);
    uint8_t* mapped; vkMapMemory(device, stagingMem, 0, totalSz, 0, (void**)&mapped);

    // Convert float32 → float16 and pack into staging
    std::vector<VkBufferImageCopy> copies;
    VkDeviceSize offset = 0;
    for (uint32_t f = 0; f < 6; ++f) {
        for (uint32_t m = 0; m < mipLevels; ++m) {
            const auto& src = facesMips[f][m];
            uint16_t* dst16 = reinterpret_cast<uint16_t*>(mapped + offset);
            uint32_t mw = std::max(baseW >> m, 1u), mh = std::max(baseH >> m, 1u);
            for (uint32_t i = 0; i < mw * mh * 4; ++i) {
                // Simple float→half conversion
                float v  = src[i];
                uint32_t bits; memcpy(&bits, &v, 4);
                uint32_t s = (bits >> 31) & 1;
                int32_t  e = (int32_t)((bits >> 23) & 0xFF) - 127;
                uint32_t m_ = bits & 0x7FFFFF;
                uint16_t h;
                if (e >= 16)        h = (uint16_t)((s << 15) | 0x7C00);
                else if (e >= -14)  h = (uint16_t)((s << 15) | ((e + 15) << 10) | (m_ >> 13));
                else                h = 0;
                dst16[i] = h;
            }
            VkBufferImageCopy copy{};
            copy.bufferOffset      = offset;
            copy.imageSubresource  = { VK_IMAGE_ASPECT_COLOR_BIT, m, f, 1 };
            copy.imageExtent       = { mw, mh, 1 };
            copies.push_back(copy);
            offset += (VkDeviceSize)mw * mh * 4 * sizeof(uint16_t);
        }
    }
    vkUnmapMemory(device, stagingMem);

    auto cb = beginSingleTimeCommands();
    VkImageMemoryBarrier barrier{};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image               = tex.image;
    barrier.subresourceRange    = { VK_IMAGE_ASPECT_COLOR_BIT, 0, mipLevels, 0, 6 };
    barrier.srcAccessMask       = 0;
    barrier.dstAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);
    vkCmdCopyBufferToImage(cb, staging, tex.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           (uint32_t)copies.size(), copies.data());
    barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);
    endSingleTimeCommands(cb);
    vkDestroyBuffer(device, staging, nullptr);
    vkFreeMemory(device, stagingMem, nullptr);

    // Image view (cube)
    VkImageViewCreateInfo vci{};
    vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image    = tex.image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_CUBE;
    vci.format   = VK_FORMAT_R16G16B16A16_SFLOAT;
    vci.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, mipLevels, 0, 6 };
    vkCreateImageView(device, &vci, nullptr, &tex.view);

    // Sampler
    VkSamplerCreateInfo sci{};
    sci.sType        = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sci.magFilter    = VK_FILTER_LINEAR;
    sci.minFilter    = VK_FILTER_LINEAR;
    sci.mipmapMode   = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    sci.maxLod       = (float)(mipLevels - 1);
    vkCreateSampler(device, &sci, nullptr, &tex.sampler);
}

// Uploads a float32 RGBA equirectangular image as R16G16B16A16_SFLOAT (no mips).
// U wraps (longitude), V clamps (latitude poles).
void Renderer::uploadEquirectTexture(VkTex& tex, const float* rgba32f, uint32_t w, uint32_t h) {
    createVkImage(w, h, 1, 1, VK_FORMAT_R16G16B16A16_SFLOAT, 0, tex.image, tex.memory);

    VkDeviceSize sz = (VkDeviceSize)w * h * 4 * sizeof(uint16_t);
    VkBuffer staging; VkDeviceMemory stagingMem;
    createBuffer(sz, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                 VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                 staging, stagingMem);
    uint16_t* dst; vkMapMemory(device, stagingMem, 0, sz, 0, (void**)&dst);
    uint64_t N = (uint64_t)w * h * 4;
    for (uint64_t i = 0; i < N; ++i) {
        float v = rgba32f[i];
        uint32_t bits; memcpy(&bits, &v, 4);
        uint32_t s = (bits >> 31) & 1;
        int32_t  e = (int32_t)((bits >> 23) & 0xFF) - 127;
        uint32_t m = bits & 0x7FFFFF;
        uint16_t h16;
        if      (e >= 16)  h16 = (uint16_t)((s << 15) | 0x7C00);
        else if (e >= -14) h16 = (uint16_t)((s << 15) | ((e + 15) << 10) | (m >> 13));
        else               h16 = 0;
        dst[i] = h16;
    }
    vkUnmapMemory(device, stagingMem);

    auto cb = beginSingleTimeCommands();
    VkImageMemoryBarrier barrier{};
    barrier.sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    barrier.oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
    barrier.newLayout           = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image               = tex.image;
    barrier.subresourceRange    = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    barrier.srcAccessMask       = 0;
    barrier.dstAccessMask       = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);
    VkBufferImageCopy region{};
    region.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
    region.imageExtent      = { w, h, 1 };
    vkCmdCopyBufferToImage(cb, staging, tex.image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    barrier.oldLayout     = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    barrier.newLayout     = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(cb, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                         0, 0, nullptr, 0, nullptr, 1, &barrier);
    endSingleTimeCommands(cb);
    vkDestroyBuffer(device, staging, nullptr);
    vkFreeMemory(device, stagingMem, nullptr);

    VkImageViewCreateInfo vci{};
    vci.sType    = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    vci.image    = tex.image;
    vci.viewType = VK_IMAGE_VIEW_TYPE_2D;
    vci.format   = VK_FORMAT_R16G16B16A16_SFLOAT;
    vci.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
    vkCreateImageView(device, &vci, nullptr, &tex.view);

    VkSamplerCreateInfo sci{};
    sci.sType        = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sci.magFilter    = VK_FILTER_LINEAR;
    sci.minFilter    = VK_FILTER_LINEAR;
    sci.mipmapMode   = VK_SAMPLER_MIPMAP_MODE_LINEAR;
    sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;       // longitude wraps
    sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;// latitude clamps at poles
    sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
    vkCreateSampler(device, &sci, nullptr, &tex.sampler);
}

void Renderer::destroyVkTex(VkTex& tex) {
    if (tex.sampler) { vkDestroySampler(device, tex.sampler, nullptr); tex.sampler = VK_NULL_HANDLE; }
    if (tex.view)    { vkDestroyImageView(device, tex.view, nullptr);  tex.view    = VK_NULL_HANDLE; }
    if (tex.image)   { vkDestroyImage(device, tex.image, nullptr);     tex.image   = VK_NULL_HANDLE; }
    if (tex.memory)  { vkFreeMemory(device, tex.memory, nullptr);      tex.memory  = VK_NULL_HANDLE; }
}

void Renderer::createTextureDescriptorLayout() {
    VkDescriptorSetLayoutBinding bindings[5] = {};
    bindings[0].binding         = 0;
    bindings[0].descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    bindings[0].descriptorCount = 1;
    bindings[0].stageFlags      = VK_SHADER_STAGE_FRAGMENT_BIT;
    bindings[1] = bindings[0]; bindings[1].binding = 1;
    bindings[2] = bindings[0]; bindings[2].binding = 2;
    bindings[3] = bindings[0]; bindings[3].binding = 3;
    bindings[4] = bindings[0]; bindings[4].binding = 4;  // equirectTex (skybox)
    VkDescriptorSetLayoutCreateInfo ci{};
    ci.sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    ci.bindingCount = 5; ci.pBindings = bindings;
    if (vkCreateDescriptorSetLayout(device, &ci, nullptr, &texDescLayout) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDescriptorSetLayout (textures) failed");
}

void Renderer::createDefaultTextures() {
    static const float white1x1[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const float black1x1[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    uploadTexture2D(albedoTex,  white1x1, 1, 1, false, false);
    uploadTexture2D(brdfLutTex, white1x1, 1, 1, false, false);
    uploadEquirectTexture(equirectTex, black1x1, 1, 1);
    // 1x1 cubemaps (irradiance + prefilteredEnv) — 6 identical faces, 1 mip
    std::vector<std::vector<std::vector<float>>> cubeFacesMips(6,
        std::vector<std::vector<float>>(1, std::vector<float>(4, 0.0f)));
    uploadCubemapMipped(irradianceTex,     cubeFacesMips, 1, 1, 1);
    uploadCubemapMipped(prefilteredEnvTex, cubeFacesMips, 1, 1, 1);
}

void Renderer::createTextureDescriptorSet() {
    VkDescriptorPoolSize poolSize{};
    poolSize.type            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    poolSize.descriptorCount = 5;
    VkDescriptorPoolCreateInfo pci{};
    pci.sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pci.maxSets       = 1;
    pci.poolSizeCount = 1; pci.pPoolSizes = &poolSize;
    if (vkCreateDescriptorPool(device, &pci, nullptr, &texDescPool) != VK_SUCCESS)
        throw std::runtime_error("vkCreateDescriptorPool (textures) failed");

    VkDescriptorSetAllocateInfo ai{};
    ai.sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    ai.descriptorPool     = texDescPool;
    ai.descriptorSetCount = 1;
    ai.pSetLayouts        = &texDescLayout;
    if (vkAllocateDescriptorSets(device, &ai, &texDescSet) != VK_SUCCESS)
        throw std::runtime_error("vkAllocateDescriptorSets (textures) failed");

    auto writeBinding = [&](uint32_t binding, VkTex& t, VkImageViewType viewType) {
        (void)viewType;
        VkDescriptorImageInfo info{};
        info.sampler     = t.sampler;
        info.imageView   = t.view;
        info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        VkWriteDescriptorSet w{};
        w.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        w.dstSet          = texDescSet;
        w.dstBinding      = binding;
        w.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        w.descriptorCount = 1;
        w.pImageInfo      = &info;
        vkUpdateDescriptorSets(device, 1, &w, 0, nullptr);
    };
    writeBinding(0, albedoTex,         VK_IMAGE_VIEW_TYPE_2D);
    writeBinding(1, irradianceTex,     VK_IMAGE_VIEW_TYPE_CUBE);
    writeBinding(2, prefilteredEnvTex, VK_IMAGE_VIEW_TYPE_CUBE);
    writeBinding(3, brdfLutTex,        VK_IMAGE_VIEW_TYPE_2D);
    writeBinding(4, equirectTex,       VK_IMAGE_VIEW_TYPE_2D);
}

void Renderer::loadAlbedoTexture(const std::string& path) {
    TexImage img = loadImageLDR(path.c_str());
    if (img.data.empty()) return;
    vkDeviceWaitIdle(device);
    destroyVkTex(albedoTex);
    uploadTexture2D(albedoTex, img.data.data(), img.w, img.h, true, true);
    // Update descriptor set binding 0
    VkDescriptorImageInfo info{};
    info.sampler     = albedoTex.sampler;
    info.imageView   = albedoTex.view;
    info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    VkWriteDescriptorSet w{};
    w.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    w.dstSet          = texDescSet;
    w.dstBinding      = 0;
    w.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    w.descriptorCount = 1;
    w.pImageInfo      = &info;
    vkUpdateDescriptorSets(device, 1, &w, 0, nullptr);
    albedoLoaded = true;
    if (_input) _input->state.albedoTexPath = path;
}

void Renderer::loadEnvMap(const std::string& path) {
    TexImage hdr = loadImageHDR(path.c_str());
    if (hdr.data.empty()) return;
    vkDeviceWaitIdle(device);
    destroyVkTex(irradianceTex);
    destroyVkTex(prefilteredEnvTex);
    destroyVkTex(brdfLutTex);
    destroyVkTex(equirectTex);

    CubeImage env      = equirectToCubemap(hdr, 512);
    CubeImage irr      = computeIrradiance(env);
    auto      prefMips = computePrefilteredEnv(env);
    TexImage  brdf     = computeBRDFLUT();

    // Irradiance: 1 mip, 6 faces
    std::vector<std::vector<std::vector<float>>> irrFacesMips(6,
        std::vector<std::vector<float>>(1));
    for (int f = 0; f < 6; ++f) {
        irrFacesMips[f][0].resize(irr.faces[f].size());
        std::copy(irr.faces[f].begin(), irr.faces[f].end(), irrFacesMips[f][0].begin());
    }
    uploadCubemapMipped(irradianceTex, irrFacesMips, irr.size, irr.size, 1);

    // Prefiltered env: NUM_ENV_MIPS mips, 6 faces
    uint32_t pfBase = (uint32_t)prefMips[0].size;
    uint32_t numMips = (uint32_t)prefMips.size();
    std::vector<std::vector<std::vector<float>>> pfFacesMips(6,
        std::vector<std::vector<float>>(numMips));
    for (uint32_t m = 0; m < numMips; ++m)
        for (int f = 0; f < 6; ++f) {
            pfFacesMips[f][m].resize(prefMips[m].faces[f].size());
            std::copy(prefMips[m].faces[f].begin(), prefMips[m].faces[f].end(),
                      pfFacesMips[f][m].begin());
        }
    uploadCubemapMipped(prefilteredEnvTex, pfFacesMips, pfBase, pfBase, numMips);

    // BRDF LUT: 2D, no mips
    uploadTexture2D(brdfLutTex, brdf.data.data(), brdf.w, brdf.h, false, false);

    // Original equirect HDR: upload as float16 2D for skybox background
    uploadEquirectTexture(equirectTex, hdr.data.data(), (uint32_t)hdr.w, (uint32_t)hdr.h);

    // Update descriptor set bindings 1-4
    auto updateBinding = [&](uint32_t binding, VkTex& t) {
        VkDescriptorImageInfo info{};
        info.sampler     = t.sampler;
        info.imageView   = t.view;
        info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        VkWriteDescriptorSet w{};
        w.sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        w.dstSet          = texDescSet;
        w.dstBinding      = binding;
        w.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        w.descriptorCount = 1;
        w.pImageInfo      = &info;
        vkUpdateDescriptorSets(device, 1, &w, 0, nullptr);
    };
    updateBinding(1, irradianceTex);
    updateBinding(2, prefilteredEnvTex);
    updateBinding(3, brdfLutTex);
    updateBinding(4, equirectTex);
    envLoaded = true;
    if (_input) _input->state.envMapPath = path;
}

// ─── Selection highlight render passes ───────────────────────────────────────
void Renderer::createHighlightRenderPass() {
    VkAttachmentDescription atts[2] = {};
    // Color: RGBA8 selection mask — cleared each frame, kept for masking pass
    atts[0].format         = VK_FORMAT_R8G8B8A8_UNORM;
    atts[0].samples        = VK_SAMPLE_COUNT_1_BIT;
    atts[0].loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    atts[0].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    atts[0].initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[0].finalLayout    = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    // Depth: dedicated per-image depth, cleared each frame, sampled by masking pass
    atts[1].format         = VK_FORMAT_D32_SFLOAT;
    atts[1].samples        = VK_SAMPLE_COUNT_1_BIT;
    atts[1].loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
    atts[1].storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
    atts[1].stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    atts[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    atts[1].initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
    atts[1].finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;

    VkAttachmentReference colorRef{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkAttachmentReference depthRef{1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL};

    VkSubpassDescription sp{};
    sp.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount    = 1;
    sp.pColorAttachments       = &colorRef;
    sp.pDepthStencilAttachment = &depthRef;

    // Depth+color writes in this pass must be visible to masking pass fragment shader
    VkSubpassDependency dep{};
    dep.srcSubpass    = 0;
    dep.dstSubpass    = VK_SUBPASS_EXTERNAL;
    dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    dep.dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    dep.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    VkRenderPassCreateInfo ci{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    ci.attachmentCount = 2; ci.pAttachments = atts;
    ci.subpassCount    = 1; ci.pSubpasses   = &sp;
    ci.dependencyCount = 1; ci.pDependencies = &dep;
    if (vkCreateRenderPass(device, &ci, nullptr, &highlightRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (highlight) failed");
}

void Renderer::createOutlineRenderPass() {
    VkAttachmentDescription att{};
    att.format        = VK_FORMAT_R8G8B8A8_UNORM;
    att.samples       = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout   = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference colorRef{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp{};
    sp.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments    = &colorRef;

    // Color write must be visible to blend pass fragment shader
    VkSubpassDependency dep{};
    dep.srcSubpass    = 0;
    dep.dstSubpass    = VK_SUBPASS_EXTERNAL;
    dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dep.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    VkRenderPassCreateInfo ci{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    ci.attachmentCount = 1; ci.pAttachments  = &att;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 1; ci.pDependencies = &dep;
    if (vkCreateRenderPass(device, &ci, nullptr, &outlineRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (outline) failed");
}

void Renderer::createBlendRenderPass() {
    VkAttachmentDescription att{};
    att.format        = swapFormat;
    att.samples       = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp        = VK_ATTACHMENT_LOAD_OP_LOAD;
    att.storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    att.initialLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    att.finalLayout   = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorRef{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp{};
    sp.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments    = &colorRef;

    VkSubpassDependency deps[2] = {};
    // Wait for outline texture writes before sampling
    deps[0].srcSubpass    = VK_SUBPASS_EXTERNAL;
    deps[0].dstSubpass    = 0;
    deps[0].srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    deps[0].dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT | VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    deps[0].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    deps[0].dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    deps[1].srcSubpass    = 0;
    deps[1].dstSubpass    = VK_SUBPASS_EXTERNAL;
    deps[1].srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    deps[1].dstStageMask  = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
    deps[1].srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    deps[1].dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;

    VkRenderPassCreateInfo ci{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    ci.attachmentCount = 1; ci.pAttachments  = &att;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 2; ci.pDependencies = deps;
    if (vkCreateRenderPass(device, &ci, nullptr, &blendRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (blend) failed");
}

void Renderer::createHighlightPipeline() {
    auto vertMod = createShaderModule(readFile("shaders/highlight_vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/highlight_frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2]{};
    stages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    // Same vertex layout as geometry pipeline (binding 0 = vertex, binding 1 = instance)
    VkVertexInputBindingDescription bindings[2]{};
    bindings[0].binding = 0; bindings[0].stride = sizeof(Vertex);       bindings[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    bindings[1].binding = 1; bindings[1].stride = sizeof(InstanceData); bindings[1].inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
    VkVertexInputAttributeDescription attrs[11]{};
    attrs[0].binding = 0; attrs[0].location = 0; attrs[0].format = VK_FORMAT_R32G32B32_SFLOAT; attrs[0].offset = offsetof(Vertex, pos);
    attrs[9].binding = 0; attrs[9].location = 9; attrs[9].format = VK_FORMAT_R32G32B32_SFLOAT; attrs[9].offset = offsetof(Vertex, nrm);
    attrs[10].binding = 0; attrs[10].location = 10; attrs[10].format = VK_FORMAT_R32G32_SFLOAT; attrs[10].offset = offsetof(Vertex, uv);
    for (int i = 0; i < 4; ++i) {
        attrs[1+i].binding = 1; attrs[1+i].location = 1+i;
        attrs[1+i].format  = VK_FORMAT_R32G32B32A32_SFLOAT;
        attrs[1+i].offset  = (uint32_t)(offsetof(InstanceData, transform) + i * sizeof(float) * 4);
    }
    attrs[5].binding = 1; attrs[5].location = 5; attrs[5].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[5].offset = (uint32_t)offsetof(InstanceData, color);
    attrs[6].binding = 1; attrs[6].location = 6; attrs[6].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[6].offset = (uint32_t)offsetof(InstanceData, ambient);
    attrs[7].binding = 1; attrs[7].location = 7; attrs[7].format = VK_FORMAT_R32_SINT;            attrs[7].offset = (uint32_t)offsetof(InstanceData, materialType);
    attrs[8].binding = 1; attrs[8].location = 8; attrs[8].format = VK_FORMAT_R32G32B32A32_SFLOAT; attrs[8].offset = (uint32_t)offsetof(InstanceData, p0);

    VkPipelineVertexInputStateCreateInfo vi{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
    vi.vertexBindingDescriptionCount   = 2; vi.pVertexBindingDescriptions   = bindings;
    vi.vertexAttributeDescriptionCount = 11; vi.pVertexAttributeDescriptions = attrs;

    VkPipelineInputAssemblyStateCreateInfo ia{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineViewportStateCreateInfo vs{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
    vs.viewportCount = 1; vs.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo rs{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
    rs.polygonMode = VK_POLYGON_MODE_FILL;
    rs.cullMode    = VK_CULL_MODE_BACK_BIT;
    rs.frontFace   = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rs.lineWidth   = 1.0f;

    VkPipelineMultisampleStateCreateInfo ms{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // Depth test+write into highlight's own depth buffer (records selected object depths for masking)
    VkPipelineDepthStencilStateCreateInfo ds{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
    ds.depthTestEnable  = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    ds.depthCompareOp   = VK_COMPARE_OP_LESS;

    VkPipelineColorBlendAttachmentState cba{};
    cba.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

    VkPipelineColorBlendStateCreateInfo cb{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    cb.attachmentCount = 1; cb.pAttachments = &cba;

    VkDynamicState dynStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dyn{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkGraphicsPipelineCreateInfo pci{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
    pci.stageCount          = 2;       pci.pStages             = stages;
    pci.pVertexInputState   = &vi;     pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vs;     pci.pRasterizationState = &rs;
    pci.pMultisampleState   = &ms;     pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &cb;     pci.pDynamicState       = &dyn;
    pci.layout              = pipelineLayout;
    pci.renderPass          = highlightRenderPass;
    pci.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &highlightPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (highlight) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

void Renderer::createOutlinePipeline() {
    auto vertMod = createShaderModule(readFile("shaders/outline_vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/outline_frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2]{};
    stages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    // Descriptor set layout: binding 0 = highlightMask sampler
    VkDescriptorSetLayoutBinding b{};
    b.binding         = 0;
    b.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    b.descriptorCount = 1;
    b.stageFlags      = VK_SHADER_STAGE_FRAGMENT_BIT;
    VkDescriptorSetLayoutCreateInfo dlci{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    dlci.bindingCount = 1; dlci.pBindings = &b;
    vkCreateDescriptorSetLayout(device, &dlci, nullptr, &outlineDescLayout);

    // Push constants: vec2 texelSize + float thickness + float pad + vec4 color = 32 bytes
    VkPushConstantRange pcRange{};
    pcRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    pcRange.offset     = 0;
    pcRange.size       = 32;

    VkPipelineLayoutCreateInfo plci{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    plci.setLayoutCount         = 1; plci.pSetLayouts         = &outlineDescLayout;
    plci.pushConstantRangeCount = 1; plci.pPushConstantRanges = &pcRange;
    vkCreatePipelineLayout(device, &plci, nullptr, &outlinePipelineLayout);

    VkPipelineVertexInputStateCreateInfo vi{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
    VkPipelineInputAssemblyStateCreateInfo ia{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    VkPipelineViewportStateCreateInfo vs{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
    vs.viewportCount = 1; vs.scissorCount = 1;
    VkPipelineRasterizationStateCreateInfo rs{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
    rs.polygonMode = VK_POLYGON_MODE_FILL; rs.cullMode = VK_CULL_MODE_NONE; rs.lineWidth = 1.0f;
    VkPipelineMultisampleStateCreateInfo ms{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    VkPipelineDepthStencilStateCreateInfo ds{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};

    VkPipelineColorBlendAttachmentState cba{};
    cba.blendEnable    = VK_FALSE;
    cba.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo cb{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    cb.attachmentCount = 1; cb.pAttachments = &cba;

    VkDynamicState dynStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dyn{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkGraphicsPipelineCreateInfo pci{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
    pci.stageCount          = 2;       pci.pStages             = stages;
    pci.pVertexInputState   = &vi;     pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vs;     pci.pRasterizationState = &rs;
    pci.pMultisampleState   = &ms;     pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &cb;     pci.pDynamicState       = &dyn;
    pci.layout              = outlinePipelineLayout;
    pci.renderPass          = outlineRenderPass;
    pci.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &outlinePipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (outline) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

void Renderer::createBlendPipeline() {
    auto vertMod = createShaderModule(readFile("shaders/outline_vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/blend_frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2]{};
    stages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    VkDescriptorSetLayoutBinding b{};
    b.binding         = 0;
    b.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    b.descriptorCount = 1;
    b.stageFlags      = VK_SHADER_STAGE_FRAGMENT_BIT;
    VkDescriptorSetLayoutCreateInfo dlci{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    dlci.bindingCount = 1; dlci.pBindings = &b;
    vkCreateDescriptorSetLayout(device, &dlci, nullptr, &blendDescLayout);

    VkPushConstantRange pcRange{};
    pcRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    pcRange.offset     = 0;
    pcRange.size       = 8; // vec2 texelSize

    VkPipelineLayoutCreateInfo plci{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    plci.setLayoutCount         = 1; plci.pSetLayouts         = &blendDescLayout;
    plci.pushConstantRangeCount = 1; plci.pPushConstantRanges = &pcRange;
    vkCreatePipelineLayout(device, &plci, nullptr, &blendPipelineLayout);

    VkPipelineVertexInputStateCreateInfo vi{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
    VkPipelineInputAssemblyStateCreateInfo ia{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    VkPipelineViewportStateCreateInfo vs{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
    vs.viewportCount = 1; vs.scissorCount = 1;
    VkPipelineRasterizationStateCreateInfo rs{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
    rs.polygonMode = VK_POLYGON_MODE_FILL; rs.cullMode = VK_CULL_MODE_NONE; rs.lineWidth = 1.0f;
    VkPipelineMultisampleStateCreateInfo ms{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    VkPipelineDepthStencilStateCreateInfo ds{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};

    VkPipelineColorBlendAttachmentState cba{};
    cba.blendEnable         = VK_TRUE;
    cba.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    cba.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    cba.colorBlendOp        = VK_BLEND_OP_ADD;
    cba.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    cba.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    cba.alphaBlendOp        = VK_BLEND_OP_ADD;
    cba.colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                              VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo cb{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    cb.attachmentCount = 1; cb.pAttachments = &cba;

    VkDynamicState dynStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dyn{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkGraphicsPipelineCreateInfo pci{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
    pci.stageCount          = 2;       pci.pStages             = stages;
    pci.pVertexInputState   = &vi;     pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vs;     pci.pRasterizationState = &rs;
    pci.pMultisampleState   = &ms;     pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &cb;     pci.pDynamicState       = &dyn;
    pci.layout              = blendPipelineLayout;
    pci.renderPass          = blendRenderPass;
    pci.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &blendPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (blend) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

void Renderer::createHighlightImages() {
    size_t n = swapImages.size();
    highlightImages.resize(n);        highlightMemories.resize(n);      highlightImageViews.resize(n);
    maskDepthImages.resize(n);        maskDepthMemories.resize(n);      maskDepthImageViews.resize(n);
    maskedHighlightImages.resize(n);  maskedHighlightMemories.resize(n); maskedHighlightImageViews.resize(n);
    outlineImages.resize(n);          outlineMemories.resize(n);         outlineImageViews.resize(n);

    auto makeImage = [&](VkFormat fmt, VkImageUsageFlags usage, VkImageAspectFlags aspect,
                         VkImage& img, VkDeviceMemory& mem, VkImageView& view) {
        VkImageCreateInfo ici{VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO};
        ici.imageType = VK_IMAGE_TYPE_2D;
        ici.format    = fmt;
        ici.extent    = {swapExtent.width, swapExtent.height, 1};
        ici.mipLevels = 1; ici.arrayLayers = 1;
        ici.samples   = VK_SAMPLE_COUNT_1_BIT;
        ici.tiling    = VK_IMAGE_TILING_OPTIMAL;
        ici.usage     = usage;
        vkCreateImage(device, &ici, nullptr, &img);
        VkMemoryRequirements mr;
        vkGetImageMemoryRequirements(device, img, &mr);
        VkMemoryAllocateInfo mai{VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO};
        mai.allocationSize  = mr.size;
        mai.memoryTypeIndex = findMemoryType(mr.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        vkAllocateMemory(device, &mai, nullptr, &mem);
        vkBindImageMemory(device, img, mem, 0);
        VkImageViewCreateInfo vci{VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO};
        vci.image            = img;
        vci.viewType         = VK_IMAGE_VIEW_TYPE_2D;
        vci.format           = fmt;
        vci.subresourceRange = {aspect, 0, 1, 0, 1};
        vkCreateImageView(device, &vci, nullptr, &view);
    };

    for (size_t i = 0; i < n; i++) {
        makeImage(VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                  VK_IMAGE_ASPECT_COLOR_BIT, highlightImages[i], highlightMemories[i], highlightImageViews[i]);
        makeImage(VK_FORMAT_D32_SFLOAT, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                  VK_IMAGE_ASPECT_DEPTH_BIT, maskDepthImages[i], maskDepthMemories[i], maskDepthImageViews[i]);
        makeImage(VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                  VK_IMAGE_ASPECT_COLOR_BIT, maskedHighlightImages[i], maskedHighlightMemories[i], maskedHighlightImageViews[i]);
        makeImage(VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
                  VK_IMAGE_ASPECT_COLOR_BIT, outlineImages[i], outlineMemories[i], outlineImageViews[i]);
    }

    if (!highlightSampler) {
        VkSamplerCreateInfo sci{VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO};
        sci.magFilter    = VK_FILTER_NEAREST;
        sci.minFilter    = VK_FILTER_NEAREST;
        sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        vkCreateSampler(device, &sci, nullptr, &highlightSampler);
    }
    if (!maskingSampler) {
        VkSamplerCreateInfo sci{VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO};
        sci.magFilter    = VK_FILTER_NEAREST;
        sci.minFilter    = VK_FILTER_NEAREST;
        sci.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sci.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sci.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        vkCreateSampler(device, &sci, nullptr, &maskingSampler);
    }
}

void Renderer::createHighlightFramebuffers() {
    highlightFramebuffers.resize(highlightImages.size());
    for (size_t i = 0; i < highlightImages.size(); i++) {
        VkImageView atts[] = { highlightImageViews[i], maskDepthImageViews[i] };
        VkFramebufferCreateInfo fi{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
        fi.renderPass      = highlightRenderPass;
        fi.attachmentCount = 2; fi.pAttachments = atts;
        fi.width           = swapExtent.width;
        fi.height          = swapExtent.height;
        fi.layers          = 1;
        if (vkCreateFramebuffer(device, &fi, nullptr, &highlightFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (highlight) failed");
    }
}

void Renderer::createOutlineFramebuffers() {
    outlineFramebuffers.resize(swapImageViews.size());
    for (size_t i = 0; i < swapImageViews.size(); i++) {
        VkFramebufferCreateInfo fi{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
        fi.renderPass      = outlineRenderPass;
        fi.attachmentCount = 1; fi.pAttachments = &outlineImageViews[i];
        fi.width           = swapExtent.width;
        fi.height          = swapExtent.height;
        fi.layers          = 1;
        if (vkCreateFramebuffer(device, &fi, nullptr, &outlineFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (outline) failed");
    }
}

void Renderer::createBlendFramebuffers() {
    blendFramebuffers.resize(swapImageViews.size());
    for (size_t i = 0; i < swapImageViews.size(); i++) {
        VkFramebufferCreateInfo fi{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
        fi.renderPass      = blendRenderPass;
        fi.attachmentCount = 1; fi.pAttachments = &swapImageViews[i];
        fi.width           = swapExtent.width;
        fi.height          = swapExtent.height;
        fi.layers          = 1;
        if (vkCreateFramebuffer(device, &fi, nullptr, &blendFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (blend) failed");
    }
}

void Renderer::createOutlineDescriptorSets() {
    size_t n = highlightImages.size();
    VkDescriptorPoolSize ps{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, (uint32_t)n};
    VkDescriptorPoolCreateInfo dpi{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    dpi.maxSets = (uint32_t)n; dpi.poolSizeCount = 1; dpi.pPoolSizes = &ps;
    vkCreateDescriptorPool(device, &dpi, nullptr, &outlineDescPool);

    std::vector<VkDescriptorSetLayout> layouts(n, outlineDescLayout);
    VkDescriptorSetAllocateInfo dai{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    dai.descriptorPool     = outlineDescPool;
    dai.descriptorSetCount = (uint32_t)n;
    dai.pSetLayouts        = layouts.data();
    outlineDescSets.resize(n);
    vkAllocateDescriptorSets(device, &dai, outlineDescSets.data());

    for (size_t i = 0; i < n; i++) {
        VkDescriptorImageInfo ii{};
        ii.sampler     = highlightSampler;
        ii.imageView   = maskedHighlightImageViews[i];
        ii.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        VkWriteDescriptorSet w{VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET};
        w.dstSet          = outlineDescSets[i];
        w.dstBinding      = 0;
        w.descriptorCount = 1;
        w.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        w.pImageInfo      = &ii;
        vkUpdateDescriptorSets(device, 1, &w, 0, nullptr);
    }
}

void Renderer::createBlendDescriptorSets() {
    size_t n = outlineImages.size();
    VkDescriptorPoolSize ps{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, (uint32_t)n};
    VkDescriptorPoolCreateInfo dpi{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    dpi.maxSets = (uint32_t)n; dpi.poolSizeCount = 1; dpi.pPoolSizes = &ps;
    vkCreateDescriptorPool(device, &dpi, nullptr, &blendDescPool);

    std::vector<VkDescriptorSetLayout> layouts(n, blendDescLayout);
    VkDescriptorSetAllocateInfo dai{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    dai.descriptorPool     = blendDescPool;
    dai.descriptorSetCount = (uint32_t)n;
    dai.pSetLayouts        = layouts.data();
    blendDescSets.resize(n);
    vkAllocateDescriptorSets(device, &dai, blendDescSets.data());

    for (size_t i = 0; i < n; i++) {
        VkDescriptorImageInfo ii{};
        ii.sampler     = highlightSampler;
        ii.imageView   = outlineImageViews[i];
        ii.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        VkWriteDescriptorSet w{VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET};
        w.dstSet          = blendDescSets[i];
        w.dstBinding      = 0;
        w.descriptorCount = 1;
        w.descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        w.pImageInfo      = &ii;
        vkUpdateDescriptorSets(device, 1, &w, 0, nullptr);
    }
}

void Renderer::createMaskingRenderPass() {
    VkAttachmentDescription att{};
    att.format        = VK_FORMAT_R8G8B8A8_UNORM;
    att.samples       = VK_SAMPLE_COUNT_1_BIT;
    att.loadOp        = VK_ATTACHMENT_LOAD_OP_CLEAR;
    att.storeOp       = VK_ATTACHMENT_STORE_OP_STORE;
    att.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    att.finalLayout   = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

    VkAttachmentReference colorRef{0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkSubpassDescription sp{};
    sp.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
    sp.colorAttachmentCount = 1;
    sp.pColorAttachments    = &colorRef;

    // Color write must be visible to outline pass fragment shader
    VkSubpassDependency dep{};
    dep.srcSubpass    = 0;
    dep.dstSubpass    = VK_SUBPASS_EXTERNAL;
    dep.srcStageMask  = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dep.dstStageMask  = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
    dep.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    dep.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

    VkRenderPassCreateInfo ci{VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    ci.attachmentCount = 1; ci.pAttachments  = &att;
    ci.subpassCount    = 1; ci.pSubpasses    = &sp;
    ci.dependencyCount = 1; ci.pDependencies = &dep;
    if (vkCreateRenderPass(device, &ci, nullptr, &maskingRenderPass) != VK_SUCCESS)
        throw std::runtime_error("vkCreateRenderPass (masking) failed");
}

void Renderer::createMaskingPipeline() {
    // Descriptor layout: mainDepth, highlightDepth, highlightMask
    VkDescriptorSetLayoutBinding bindings[3]{};
    for (int b = 0; b < 3; b++) {
        bindings[b].binding        = (uint32_t)b;
        bindings[b].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        bindings[b].descriptorCount = 1;
        bindings[b].stageFlags     = VK_SHADER_STAGE_FRAGMENT_BIT;
    }
    VkDescriptorSetLayoutCreateInfo dlci{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO};
    dlci.bindingCount = 3; dlci.pBindings = bindings;
    vkCreateDescriptorSetLayout(device, &dlci, nullptr, &maskingDescLayout);

    VkPushConstantRange pcRange{};
    pcRange.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    pcRange.offset     = 0;
    pcRange.size       = sizeof(float);

    VkPipelineLayoutCreateInfo plci{VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO};
    plci.setLayoutCount         = 1; plci.pSetLayouts         = &maskingDescLayout;
    plci.pushConstantRangeCount = 1; plci.pPushConstantRanges = &pcRange;
    vkCreatePipelineLayout(device, &plci, nullptr, &maskingPipelineLayout);

    auto vertMod = createShaderModule(readFile("shaders/masking_vert.spv"));
    auto fragMod = createShaderModule(readFile("shaders/masking_frag.spv"));

    VkPipelineShaderStageCreateInfo stages[2]{};
    stages[0].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[0].stage  = VK_SHADER_STAGE_VERTEX_BIT;   stages[0].module = vertMod; stages[0].pName = "main";
    stages[1].sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    stages[1].stage  = VK_SHADER_STAGE_FRAGMENT_BIT; stages[1].module = fragMod; stages[1].pName = "main";

    VkPipelineVertexInputStateCreateInfo vi{VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO};
    VkPipelineInputAssemblyStateCreateInfo ia{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    VkPipelineViewportStateCreateInfo vs{VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO};
    vs.viewportCount = 1; vs.scissorCount = 1;
    VkPipelineRasterizationStateCreateInfo rs{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};
    rs.polygonMode = VK_POLYGON_MODE_FILL; rs.cullMode = VK_CULL_MODE_NONE; rs.lineWidth = 1.0f;
    VkPipelineMultisampleStateCreateInfo ms{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    VkPipelineDepthStencilStateCreateInfo ds{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};

    VkPipelineColorBlendAttachmentState cba{};
    cba.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                         VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    VkPipelineColorBlendStateCreateInfo cb{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    cb.attachmentCount = 1; cb.pAttachments = &cba;

    VkDynamicState dynStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
    VkPipelineDynamicStateCreateInfo dyn{VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO};
    dyn.dynamicStateCount = 2; dyn.pDynamicStates = dynStates;

    VkGraphicsPipelineCreateInfo pci{VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO};
    pci.stageCount          = 2;       pci.pStages             = stages;
    pci.pVertexInputState   = &vi;     pci.pInputAssemblyState = &ia;
    pci.pViewportState      = &vs;     pci.pRasterizationState = &rs;
    pci.pMultisampleState   = &ms;     pci.pDepthStencilState  = &ds;
    pci.pColorBlendState    = &cb;     pci.pDynamicState       = &dyn;
    pci.layout              = maskingPipelineLayout;
    pci.renderPass          = maskingRenderPass;
    pci.subpass             = 0;
    if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pci, nullptr, &maskingPipeline) != VK_SUCCESS)
        throw std::runtime_error("vkCreateGraphicsPipelines (masking) failed");

    vkDestroyShaderModule(device, vertMod, nullptr);
    vkDestroyShaderModule(device, fragMod, nullptr);
}

void Renderer::createMaskingFramebuffers() {
    maskingFramebuffers.resize(maskedHighlightImages.size());
    for (size_t i = 0; i < maskedHighlightImages.size(); i++) {
        VkFramebufferCreateInfo fi{VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
        fi.renderPass      = maskingRenderPass;
        fi.attachmentCount = 1; fi.pAttachments = &maskedHighlightImageViews[i];
        fi.width           = swapExtent.width;
        fi.height          = swapExtent.height;
        fi.layers          = 1;
        if (vkCreateFramebuffer(device, &fi, nullptr, &maskingFramebuffers[i]) != VK_SUCCESS)
            throw std::runtime_error("vkCreateFramebuffer (masking) failed");
    }
}

void Renderer::createMaskingDescriptorSets() {
    size_t n = swapImages.size();
    VkDescriptorPoolSize ps{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, (uint32_t)(n * 3)};
    VkDescriptorPoolCreateInfo dpi{VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO};
    dpi.maxSets = (uint32_t)n; dpi.poolSizeCount = 1; dpi.pPoolSizes = &ps;
    vkCreateDescriptorPool(device, &dpi, nullptr, &maskingDescPool);

    std::vector<VkDescriptorSetLayout> layouts(n, maskingDescLayout);
    VkDescriptorSetAllocateInfo dai{VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO};
    dai.descriptorPool     = maskingDescPool;
    dai.descriptorSetCount = (uint32_t)n;
    dai.pSetLayouts        = layouts.data();
    maskingDescSets.resize(n);
    vkAllocateDescriptorSets(device, &dai, maskingDescSets.data());

    for (size_t i = 0; i < n; i++) {
        VkDescriptorImageInfo infos[3]{};
        // binding 0: main scene depth
        infos[0].sampler     = maskingSampler;
        infos[0].imageView   = depthImageView;
        infos[0].imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        // binding 1: highlight pass depth (records selected objects' depths)
        infos[1].sampler     = maskingSampler;
        infos[1].imageView   = maskDepthImageViews[i];
        infos[1].imageLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
        // binding 2: highlight mask (R8 selection mask)
        infos[2].sampler     = maskingSampler;
        infos[2].imageView   = highlightImageViews[i];
        infos[2].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

        VkWriteDescriptorSet writes[3]{};
        for (int b = 0; b < 3; b++) {
            writes[b].sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            writes[b].dstSet          = maskingDescSets[i];
            writes[b].dstBinding      = (uint32_t)b;
            writes[b].descriptorCount = 1;
            writes[b].descriptorType  = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            writes[b].pImageInfo      = &infos[b];
        }
        vkUpdateDescriptorSets(device, 3, writes, 0, nullptr);
    }
}

// ─── Init / loop / cleanup ────────────────────────────────────────────────────
void Renderer::initVulkan() {
    createInstance(); setupDebugMessenger(); createSurface();
    pickPhysicalDevice(); createLogicalDevice();
    pfnCmdInsertLabel = (PFN_vkCmdInsertDebugUtilsLabelEXT)
        vkGetDeviceProcAddr(device, "vkCmdInsertDebugUtilsLabelEXT");
    createSwapchain(); createImageViews();
    createCommandPool();   // moved up: needed for single-time commands during texture upload
    createTextureDescriptorLayout();
    createDefaultTextures();
    createTextureDescriptorSet();
    // Persistent render passes (never recreated on resize/MSAA toggle)
    createOITAccumRenderPass(); createCompositeRenderPass();
    createHighlightRenderPass(); createOutlineRenderPass(); createMaskingRenderPass(); createBlendRenderPass();
    // Per-swapchain resources (must come before pipelines that need pipelineLayout)
    createDepthResources();
    createOpaqueRenderPass(); createGraphicsPipeline(); createSkyboxPipeline();
    // Pipelines that need pipelineLayout (created above in createGraphicsPipeline)
    createOITPipelines();
    createHighlightPipeline(); createOutlinePipeline(); createMaskingPipeline(); createBlendPipeline();
    createOITImages(); createOITDescriptorSets();
    createOpaqueFramebuffers(); createOITFramebuffers(); createCompositeFramebuffers();
    createHighlightImages(); createHighlightFramebuffers(); createOutlineFramebuffers();
    createMaskingFramebuffers(); createMaskingDescriptorSets();
    createOutlineDescriptorSets();
    createBlendFramebuffers(); createBlendDescriptorSets();
    createVertexBuffer(); createIndexBuffer(); createInstanceBuffer();
    createCommandBuffers(); createSyncObjects();
    initImGui();
}

void Renderer::mainLoop() {
    while (!glfwWindowShouldClose(window) && !_input->state.switchRenderer) {
        glfwPollEvents();
        if (msaaChanged) {
            msaaChanged = false;
            vkDeviceWaitIdle(device);
            cleanupImGui();
            // Destroy MSAA-dependent pipelines
            if (depthPrepassPipeline) { vkDestroyPipeline(device, depthPrepassPipeline, nullptr); depthPrepassPipeline = VK_NULL_HANDLE; }
            if (depthPrepassRenderPass) { vkDestroyRenderPass(device, depthPrepassRenderPass, nullptr); depthPrepassRenderPass = VK_NULL_HANDLE; }
            vkDestroyPipeline(device, skyboxPipeline, nullptr);    skyboxPipeline    = VK_NULL_HANDLE;
            vkDestroyPipeline(device, wireframePipeline, nullptr); wireframePipeline = VK_NULL_HANDLE;
            vkDestroyPipeline(device, graphicsPipeline, nullptr);  graphicsPipeline  = VK_NULL_HANDLE;
            vkDestroyPipelineLayout(device, pipelineLayout, nullptr); pipelineLayout = VK_NULL_HANDLE;
            // recreateSwapchain destroys/recreates opaqueRenderPass, MSAA images, framebuffers
            recreateSwapchain();
            createGraphicsPipeline(); createSkyboxPipeline();
            if (msaa8) { createDepthPrepassRenderPass(); createDepthPrepassPipeline(); }
            initImGui();
        }
        drawFrame();
    }
    vkDeviceWaitIdle(device);
}

void Renderer::cleanup() {
    cleanupImGui();
    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
        vkDestroySemaphore(device, imageAvailable[i], nullptr);
        vkDestroySemaphore(device, renderFinished[i], nullptr);
        vkDestroyFence(device, inFlight[i], nullptr);
    }
    vkDestroyCommandPool(device, commandPool, nullptr);
    cleanupSwapchain();
    vkDestroyBuffer(device, vertexBuffer,   nullptr); vkFreeMemory(device, vertexMemory,   nullptr);
    vkDestroyBuffer(device, indexBuffer,    nullptr); vkFreeMemory(device, indexMemory,    nullptr);
    vkUnmapMemory(device, instanceMemory);
    vkDestroyBuffer(device, instanceBuffer, nullptr); vkFreeMemory(device, instanceMemory, nullptr);

    // Texture resources
    destroyVkTex(albedoTex);
    destroyVkTex(irradianceTex);
    destroyVkTex(prefilteredEnvTex);
    destroyVkTex(brdfLutTex);
    if (texDescPool != VK_NULL_HANDLE) {
        vkDestroyDescriptorPool(device, texDescPool, nullptr);
        texDescPool = VK_NULL_HANDLE;
    }
    if (texDescLayout != VK_NULL_HANDLE) {
        vkDestroyDescriptorSetLayout(device, texDescLayout, nullptr);
        texDescLayout = VK_NULL_HANDLE;
    }

    if (blendPipeline)       { vkDestroyPipeline(device, blendPipeline, nullptr); }
    if (blendPipelineLayout) { vkDestroyPipelineLayout(device, blendPipelineLayout, nullptr); }
    if (blendDescLayout)     { vkDestroyDescriptorSetLayout(device, blendDescLayout, nullptr); }
    if (blendRenderPass)     { vkDestroyRenderPass(device, blendRenderPass, nullptr); }
    vkDestroyPipeline(device, outlinePipeline, nullptr);
    vkDestroyPipelineLayout(device, outlinePipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, outlineDescLayout, nullptr);
    if (maskingPipeline)       { vkDestroyPipeline(device, maskingPipeline, nullptr); }
    if (maskingPipelineLayout) { vkDestroyPipelineLayout(device, maskingPipelineLayout, nullptr); }
    if (maskingDescLayout)     { vkDestroyDescriptorSetLayout(device, maskingDescLayout, nullptr); }
    if (maskingRenderPass)     { vkDestroyRenderPass(device, maskingRenderPass, nullptr); }
    if (maskingSampler)        { vkDestroySampler(device, maskingSampler, nullptr); }
    vkDestroyPipeline(device, highlightPipeline, nullptr);
    if (highlightSampler) vkDestroySampler(device, highlightSampler, nullptr);
    vkDestroyRenderPass(device, outlineRenderPass, nullptr);
    vkDestroyRenderPass(device, highlightRenderPass, nullptr);
    if (depthPrepassPipeline)   { vkDestroyPipeline(device, depthPrepassPipeline, nullptr); }
    if (depthPrepassRenderPass) { vkDestroyRenderPass(device, depthPrepassRenderPass, nullptr); }
    vkDestroyPipeline(device, compositePipeline, nullptr);
    vkDestroyPipeline(device, oitPipeline, nullptr);
    if (oitCompositeSampler)    { vkDestroySampler(device, oitCompositeSampler, nullptr); }
    vkDestroyPipelineLayout(device, compositePipelineLayout, nullptr);
    vkDestroyDescriptorSetLayout(device, compositeDescLayout, nullptr);
    if (oitRenderPass)          { vkDestroyRenderPass(device, oitRenderPass, nullptr); }
    if (compositeRenderPass)    { vkDestroyRenderPass(device, compositeRenderPass, nullptr); }
    destroyVkTex(equirectTex);
    if (skyboxPipeline)         { vkDestroyPipeline(device, skyboxPipeline, nullptr); }
    if (wireframePipeline)      { vkDestroyPipeline(device, wireframePipeline, nullptr); }
    if (graphicsPipeline)       { vkDestroyPipeline(device, graphicsPipeline, nullptr); }
    if (pipelineLayout)         { vkDestroyPipelineLayout(device, pipelineLayout, nullptr); }
    // opaqueRenderPass is destroyed in cleanupSwapchain (called above)
    vkDestroyDevice(device, nullptr);
    if (ENABLE_VALIDATION) {
        auto fn = (PFN_vkDestroyDebugUtilsMessengerEXT)
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (fn) fn(instance, debugMessenger, nullptr);
    }
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window); glfwTerminate();
}

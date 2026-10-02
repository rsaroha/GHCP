cmake_minimum_required(VERSION 3.20)
project(VulkanTriangle CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui CONFIG REQUIRED)
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
find_path(TINYGLTF_INCLUDE_DIRS "tiny_gltf.h" HINTS "${THIRD_PARTY_DIR}")
find_path(STB_INCLUDE_DIRS "stb_image.h" HINTS "${THIRD_PARTY_DIR}")
find_package(tinyexr CONFIG REQUIRED)

# GLAD — pre-built from vcpkg
find_package(glad CONFIG QUIET)
if (NOT glad_FOUND)
    # Fallback: point directly at the vcpkg installed tree
    set(GLAD_INCLUDE_DIR "C:/vcpkg/installed/x64-windows/include")
    set(GLAD_LIB        "C:/vcpkg/installed/x64-windows/lib/glad.lib")
endif()

add_executable(triangle
    main.cpp
    renderer.cpp
    renderer_gl.cpp
    mesh_loader.cpp
    stb_image_impl.cpp
    tinyexr_impl.cpp
    input.cpp
    imgui_impl_opengl3.cpp
    imgui_impl_glfw.cpp
    imgui_impl_vulkan.cpp
)

target_link_libraries(triangle
    PRIVATE
    Vulkan::Vulkan
    glfw
    imgui::imgui
    opengl32
    comdlg32
    unofficial::tinyexr::tinyexr
)

if (glad_FOUND)
    target_link_libraries(triangle PRIVATE glad::glad)
else()
    target_include_directories(triangle PRIVATE ${GLAD_INCLUDE_DIR})
    target_link_libraries(triangle PRIVATE ${GLAD_LIB})
endif()

target_include_directories(triangle PRIVATE ${TINYGLTF_INCLUDE_DIRS})
target_include_directories(triangle PRIVATE ${STB_INCLUDE_DIRS})
target_include_directories(triangle PRIVATE ${THIRD_PARTY_DIR})
target_include_directories(triangle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# tinyexr include dirs come via the imported target (no separate find_path needed)

# ── Compile shaders ──────────────────────────────────────────────────────────
find_program(GLSLC glslc REQUIRED HINTS "$ENV{VULKAN_SDK}/Bin")


set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SHADER_OUT ${CMAKE_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADER_OUT})

add_custom_command(
    OUTPUT  ${SHADER_OUT}/vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/triangle.vert -o ${SHADER_OUT}/vert.spv
    DEPENDS ${SHADER_DIR}/triangle.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/triangle.frag -o ${SHADER_OUT}/frag.spv
    DEPENDS ${SHADER_DIR}/triangle.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/oitaccum.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/oitaccum.frag -o ${SHADER_OUT}/oitaccum.spv
    DEPENDS ${SHADER_DIR}/oitaccum.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/composite_vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/composite.vert -o ${SHADER_OUT}/composite_vert.spv
    DEPENDS ${SHADER_DIR}/composite.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/composite_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/composite.frag -o ${SHADER_OUT}/composite_frag.spv
    DEPENDS ${SHADER_DIR}/composite.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/skybox_vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/skybox.vert -o ${SHADER_OUT}/skybox_vert.spv
    DEPENDS ${SHADER_DIR}/skybox.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/skybox_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/skybox.frag -o ${SHADER_OUT}/skybox_frag.spv
    DEPENDS ${SHADER_DIR}/skybox.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/highlight_vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/highlight.vert -o ${SHADER_OUT}/highlight_vert.spv
    DEPENDS ${SHADER_DIR}/highlight.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/highlight_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/highlight.frag -o ${SHADER_OUT}/highlight_frag.spv
    DEPENDS ${SHADER_DIR}/highlight.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/outline_vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/outline.vert -o ${SHADER_OUT}/outline_vert.spv
    DEPENDS ${SHADER_DIR}/outline.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/outline_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/outline.frag -o ${SHADER_OUT}/outline_frag.spv
    DEPENDS ${SHADER_DIR}/outline.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/masking_vert.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/masking.vert -o ${SHADER_OUT}/masking_vert.spv
    DEPENDS ${SHADER_DIR}/masking.vert
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/masking_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/masking.frag -o ${SHADER_OUT}/masking_frag.spv
    DEPENDS ${SHADER_DIR}/masking.frag
)
add_custom_command(
    OUTPUT  ${SHADER_OUT}/blend_frag.spv
    COMMAND ${GLSLC} ${SHADER_DIR}/blend.frag -o ${SHADER_OUT}/blend_frag.spv
    DEPENDS ${SHADER_DIR}/blend.frag
)
add_custom_target(shaders ALL
    DEPENDS
        ${SHADER_OUT}/vert.spv
        ${SHADER_OUT}/frag.spv
        ${SHADER_OUT}/oitaccum.spv
        ${SHADER_OUT}/composite_vert.spv
        ${SHADER_OUT}/composite_frag.spv
        ${SHADER_OUT}/skybox_vert.spv
        ${SHADER_OUT}/skybox_frag.spv
        ${SHADER_OUT}/highlight_vert.spv
        ${SHADER_OUT}/highlight_frag.spv
        ${SHADER_OUT}/outline_vert.spv
        ${SHADER_OUT}/outline_frag.spv
        ${SHADER_OUT}/masking_vert.spv
        ${SHADER_OUT}/masking_frag.spv
        ${SHADER_OUT}/blend_frag.spv
)
add_dependencies(triangle shaders)

# Copy compiled SPV files next to the executable so the app can find them
add_custom_command(TARGET triangle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:triangle>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/vert.spv $<TARGET_FILE_DIR:triangle>/shaders/vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/frag.spv $<TARGET_FILE_DIR:triangle>/shaders/frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/oitaccum.spv $<TARGET_FILE_DIR:triangle>/shaders/oitaccum.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/composite_vert.spv $<TARGET_FILE_DIR:triangle>/shaders/composite_vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/composite_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/composite_frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/skybox_vert.spv $<TARGET_FILE_DIR:triangle>/shaders/skybox_vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/skybox_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/skybox_frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/highlight_vert.spv $<TARGET_FILE_DIR:triangle>/shaders/highlight_vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/highlight_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/highlight_frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/outline_vert.spv $<TARGET_FILE_DIR:triangle>/shaders/outline_vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/outline_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/outline_frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/masking_vert.spv $<TARGET_FILE_DIR:triangle>/shaders/masking_vert.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/masking_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/masking_frag.spv
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SHADER_OUT}/blend_frag.spv $<TARGET_FILE_DIR:triangle>/shaders/blend_frag.spv
)

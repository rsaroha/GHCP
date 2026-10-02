cmake_minimum_required(VERSION 3.20)
project(gl_capture LANGUAGES CXX)

if (NOT WIN32)
    message(FATAL_ERROR "gl_capture currently targets Windows desktop GL (wglGetProcAddress interception).")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Matches the prebuilt wxWidgets libs (built with RUNTIME_LIBS=dynamic, i.e.
# /MDd in Debug) -- mixing CRTs between this project and a statically-linked
# wx would fail to link/run correctly.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
if (MSVC)
    add_compile_options(/EHsc)
endif()

set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)
set(COMMON_DIR ${CMAKE_SOURCE_DIR}/common)

# --- wxWidgets (static, prebuilt) -----------------------------------------
# gl_capture_ui and gl_replay use wxWidgets for their UI; gl_capture_hook
# (injected into the traced process) and gl_capture_test_app do not link
# it at all. Prebuilt as static (non-DLL) Debug/Unicode libs only, so this
# project only supports a Debug build for those two targets.
set(WX_ROOT "${CMAKE_SOURCE_DIR}/../third_party/wxWidgets")
set(WX_LIB_DIR "${WX_ROOT}/lib/vc_x64_lib")
set(WX_INCLUDE_DIRS "${WX_ROOT}/include" "${WX_ROOT}/include/msvc" "${WX_LIB_DIR}/mswud")
set(WX_LIBS
    "${WX_LIB_DIR}/wxmsw33ud_core.lib"
    "${WX_LIB_DIR}/wxbase33ud.lib"
    "${WX_LIB_DIR}/wxpngd.lib"
    "${WX_LIB_DIR}/wxjpegd.lib"
    "${WX_LIB_DIR}/wxtiffd.lib"
    "${WX_LIB_DIR}/wxwebpd.lib"
    "${WX_LIB_DIR}/wxwebpdemuxd.lib"
    "${WX_LIB_DIR}/wxsharpyuvd.lib"
    "${WX_LIB_DIR}/wxzlibd.lib"
    "${WX_LIB_DIR}/wxregexud.lib"
    comctl32 rpcrt4 oleacc uxtheme winmm version shlwapi ws2_32
)

function(target_use_wxwidgets target)
    target_include_directories(${target} PRIVATE ${WX_INCLUDE_DIRS})
    target_compile_definitions(${target} PRIVATE __WXMSW__ _UNICODE UNICODE
        # This prebuilt wx was configured with several optional components
        # (net/xml/html/aui/xrc/...) enabled, which makes wx/setup.h try to
        # auto-link their libraries via #pragma comment(lib, ...) even
        # though we only use core+base -- and this distribution only
        # actually ships the core/base/image-codec libs. Suppress all of
        # those pragmas; target_link_libraries above lists everything we
        # actually link.
        wxNO_NET_LIB wxNO_XML_LIB wxNO_EXPAT_LIB wxNO_HTML_LIB wxNO_QA_LIB
        wxNO_XRC_LIB wxNO_AUI_LIB wxNO_PROPGRID_LIB wxNO_RIBBON_LIB
        wxNO_RICHTEXT_LIB wxNO_MEDIA_LIB wxNO_STC_LIB wxNO_WEBVIEW_LIB wxNO_GL_LIB
    )
    target_link_libraries(${target} PRIVATE ${WX_LIBS})
endfunction()

# --- interceptor: hook DLL, injected into the target process (not loaded
# via the opengl32.dll search-order trick -- see interceptor/dllmain.cpp
# for why) ------------------------------------------------------------
add_library(gl_capture_hook SHARED
    interceptor/dllmain.cpp
    interceptor/custom_wrappers.cpp
    interceptor/iat_patch.cpp
    ${GEN_DIR}/gl_ids.cpp
    ${GEN_DIR}/gl_real_table.cpp
    ${GEN_DIR}/gl_wrappers_generated.cpp
    ${GEN_DIR}/gl_passthrough_wrappers.cpp
    ${GEN_DIR}/gl_lookup_table.cpp
)
target_include_directories(gl_capture_hook PRIVATE ${GEN_DIR} ${COMMON_DIR} interceptor)
set_target_properties(gl_capture_hook PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# --- replay tool ----------------------------------------------------------
add_executable(gl_replay
    replay/main.cpp
    replay/custom_replay.cpp
    replay/custom_format.cpp
    replay/gl_inspect.cpp
    replay/gl_state_view.cpp
    replay/texture_view.cpp
    replay/shader_registry.cpp
    replay/shader_view.cpp
    ${GEN_DIR}/gl_ids.cpp
    ${GEN_DIR}/gl_real_table.cpp
    ${GEN_DIR}/gl_replay_decode.cpp
    ${GEN_DIR}/gl_format_calls.cpp
    ${GEN_DIR}/gl_enum_names.cpp
)
target_include_directories(gl_replay PRIVATE ${GEN_DIR} ${COMMON_DIR})
target_link_libraries(gl_replay PRIVATE opengl32 gdi32 user32)
target_use_wxwidgets(gl_replay)
set_target_properties(gl_replay PROPERTIES WIN32_EXECUTABLE TRUE)

# --- test app: exercises legacy + modern GL paths for smoke-testing ------
add_executable(gl_capture_test_app test_app/main.cpp)
target_link_libraries(gl_capture_test_app PRIVATE opengl32 gdi32 user32)

# --- launcher UI: pick a target exe + trace path, start/stop capture, replay ---
add_executable(gl_capture_ui WIN32 ui/main.cpp)
target_link_libraries(gl_capture_ui PRIVATE comdlg32 shlwapi user32 gdi32)
target_use_wxwidgets(gl_capture_ui)
add_dependencies(gl_capture_ui gl_capture_hook gl_replay)

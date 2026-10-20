cmake_minimum_required(VERSION 3.20)
project(GLFromWebGL LANGUAGES CXX)

if(NOT WIN32)
    message(FATAL_ERROR "GL_from_WEBGL is a Win32 application.")
endif()

add_executable(GLFromWebGL WIN32 main.cpp stb_image_impl.cpp)
target_compile_features(GLFromWebGL PRIVATE cxx_std_17)
target_compile_definitions(GLFromWebGL PRIVATE UNICODE _UNICODE)
set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui")
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../third_party")
target_sources(GLFromWebGL PRIVATE
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_win32.cpp"
    "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
)
target_include_directories(GLFromWebGL PRIVATE
    "${IMGUI_DIR}"
    "${IMGUI_DIR}/backends"
    "${THIRD_PARTY_DIR}"
)
target_link_libraries(GLFromWebGL PRIVATE opengl32 user32 gdi32 comdlg32)

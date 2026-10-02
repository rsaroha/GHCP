cmake_minimum_required(VERSION 3.20)

project(OpenGLOutline LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(IMGUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/imgui"
    CACHE PATH "Path to the Dear ImGui source directory")

set(IMGUI_BACKEND_DIR "${IMGUI_DIR}/backends")

set(APP_SOURCES
    main.cpp
    renderer.cpp
    renderer.h
    ui.cpp
    ui.h
)

set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_BACKEND_DIR}/imgui_impl_win32.cpp"
    "${IMGUI_BACKEND_DIR}/imgui_impl_opengl3.cpp"
)

set(SHADER_FILES
    shaders/cube.vert
    shaders/cube.frag
    shaders/fullscreen.vert
    shaders/outline.frag
    shaders/present.frag
)

add_executable(OpenGLOutline WIN32
    ${APP_SOURCES}
    ${IMGUI_SOURCES}
    ${SHADER_FILES}
)

target_include_directories(OpenGLOutline PRIVATE
    "${IMGUI_DIR}"
    "${IMGUI_BACKEND_DIR}"
)

if(WIN32)
    target_link_libraries(OpenGLOutline PRIVATE opengl32)
endif()

source_group("Application" FILES ${APP_SOURCES})
source_group("Dear ImGui" FILES ${IMGUI_SOURCES})
source_group("Shaders" FILES ${SHADER_FILES})

foreach(SHADER_FILE IN LISTS SHADER_FILES)
    add_custom_command(TARGET OpenGLOutline POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:OpenGLOutline>/shaders"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_CURRENT_SOURCE_DIR}/${SHADER_FILE}"
            "$<TARGET_FILE_DIR:OpenGLOutline>/${SHADER_FILE}"
        VERBATIM
    )
endforeach()

if(MSVC)
    target_compile_options(OpenGLOutline PRIVATE /W3 /permissive-)
endif()

# OpenGL Outline Project Context

This document is the handoff reference for another Copilot session working on this project. Read it before changing the renderer.

## Project location and purpose

- Project root: `E:\copilot\opengl-outline\`
- Third-party root: `E:\copilot\third_party\`
- Application: Win32 C++ OpenGL compatibility-profile demo.
- Current visual result: a gray, lit, quaternion-rotated cube rendered through offscreen framebuffers, with a red four-pixel stencil-based outline and an ImGui background-color picker.
- Build target: Debug x86.
- Installed compiler/toolset: Visual Studio 18, MSVC platform toolset `v145`.
- Expected executable: `E:\copilot\opengl-outline\bin\Debug\OpenGLOutline.exe`

## Source layout

### Application code

- `main.cpp`
  - Creates the Win32 window and OpenGL context.
  - Creates a temporary legacy WGL context to load `wglCreateContextAttribsARB`.
  - Replaces it with an OpenGL 3.3 compatibility-profile context.
  - Runs the main loop:
    1. Poll Win32 messages.
    2. `Ui_NewFrame()`.
    3. `Renderer_Render()`.
    4. `Ui_Render()`.
    5. `Renderer_Present()`.
  - Routes mouse messages to ImGui first.
  - Blocks model interaction while ImGui reports `WantCaptureMouse`.
  - Escape and window close terminate the application.

- `renderer.h`
  - Public renderer API and global window/context declarations.
  - Main APIs:
    - `Renderer_Initialize`
    - `Renderer_Resize`
    - `Renderer_Render`
    - `Renderer_Present`
    - `Renderer_Shutdown`
    - `Renderer_SetBackgroundColor`
    - `Renderer_MouseButton`
    - `Renderer_MouseMove`
    - `Renderer_MouseWheel`

- `renderer.cpp`
  - Loads OpenGL 3.3 functions dynamically.
  - Compiles and links shader files.
  - Owns cube geometry, quaternion navigation, projection, framebuffer creation, stencil outline compositing, and cleanup.

- `ui.cpp` / `ui.h`
  - Initializes Dear ImGui Win32 and OpenGL3 backends.
  - Displays only the `Background color` label and color button.
  - Opens an RGB/HSV/hex color picker popup.
  - Calls `Renderer_SetBackgroundColor`.
  - Exposes `Ui_HandleMessage`, `Ui_CapturesMouse`, `Ui_NewFrame`, `Ui_Render`, and `Ui_Shutdown`.

### Shader files

All shader source is external and loaded at runtime:

- `shaders/cube.vert`
  - Transforms cube positions by `mvp`.
  - Computes camera/view-space position using `modelView`.
  - Transforms normals using `mat3(modelView)`.

- `shaders/cube.frag`
  - Gray material (`vec3(0.58)`).
  - Camera-space directional diffuse lighting.
  - Camera-space specular highlight.
  - Outputs opaque lit color.

- `shaders/fullscreen.vert`
  - Generates a fullscreen triangle from `gl_VertexID`.
  - Outputs `uv`.
  - No fullscreen VAO-specific vertex data is required.

- `shaders/outline.frag`
  - Contains selectable non-JFA outline implementations.
  - `Brute-force`: 9x9 stencil neighborhood search.
  - `Cross kernel`: horizontal + vertical stencil neighborhood search.
- `shaders/jfa_seed.frag`
  - Initializes jump-flood seeds from stencil-marked pixels.
- `shaders/jfa_step.frag`
  - Executes one jump-flood propagation step over the seed buffer.
- `shaders/jfa_compose.frag`
  - Composites scene color with an outline using the final jump-flood result.

- `shaders/present.frag`
  - Copies the outline FBO texture to the default framebuffer.

Shader loading searches these paths in order:

1. Working-directory `shaders\filename`.
2. Directory beside the executable: `bin\Debug\shaders\filename`.
3. Two levels above the executable, followed by `shaders\filename`.

The Visual Studio project marks shader files as `None` items with `CopyToOutputDirectory=PreserveNewest`.

## OpenGL context and compatibility requirements

The renderer requests:

- OpenGL major version `3`
- OpenGL minor version `3`
- `WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB`

The compatibility profile is intentional. The application uses modern shader/FBO functionality while retaining compatibility-profile behavior and `GL_QUADS` for cube faces.

Do not assume GLEW, GLAD, GLFW, or another loader is available. OpenGL entry points are loaded manually with `wglGetProcAddress`, with fallback to `opengl32.dll`.

Important loaded functions include:

- VAO/VBO functions.
- Shader/program functions.
- Uniform functions.
- Framebuffer and texture functions.
- `glActiveTexture`.

## Rendering architecture

### Main framebuffer

The main FBO contains:

- `g_colorTexture`: `GL_RGBA8` color texture.
- `g_depthTexture`: `GL_DEPTH24_STENCIL8` texture attached as `GL_DEPTH_STENCIL_ATTACHMENT`.

The packed depth-stencil texture uses `GL_NEAREST` filtering and
`GL_DEPTH_STENCIL_TEXTURE_MODE = GL_STENCIL_INDEX`, so sampling it in
`outline.frag` returns stencil data.

### Outline framebuffer

The outline FBO contains:

- `g_outlineTexture`: `GL_RGBA8` color texture.

It has no depth/stencil attachment because it only receives the fullscreen composite.

### Per-frame pass sequence

`Renderer_Render()` performs these passes:

1. Bind `g_framebuffer`.
2. Set the viewport to the window size.
3. Clear color, depth, and stencil.
4. Enable depth testing.
5. Enable stencil testing.
6. Configure stencil:
   - `glStencilMask(0xFF)`
   - `glStencilFunc(GL_ALWAYS, 1, 0xFF)`
   - `glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE)`
7. Build perspective, model-view, and MVP matrices.
8. Draw six cube faces with `GL_QUADS`.
9. Disable stencil testing.
10. Bind `g_outlineFramebuffer`.
11. Render a fullscreen triangle using `outline.frag`.
12. Bind:
    - Texture unit 0: `g_colorTexture`
    - Texture unit 1: `g_depthTexture` (stencil component)
13. Set:
    - `sceneColor = 0`
    - `stencilMask = 1`
    - `texelSize = (1 / width, 1 / height)`
14. Bind the default framebuffer.
15. Render a fullscreen triangle using `present.frag`, sampling `g_outlineTexture`.
16. ImGui is rendered afterward by `Ui_Render()`, so the UI is not included in the outline.
17. `Renderer_Present()` calls `SwapBuffers`.

The stencil pass marks visible cube fragments because the depth test is enabled while the cube is drawn. The outline shader then expands outward from the stencil mask.

## Camera and model interaction decisions

### Rotation

- Rotation state is a normalized quaternion:
  - `g_rotation = {1, 0, 0, 0}` initially.
- Left mouse drag composes incremental yaw and pitch quaternions.
- Quaternion multiplication and normalization are implemented in `renderer.cpp`.
- Horizontal drag signs were chosen so moving the mouse left rotates the model toward its left side.

### Zoom

- Zoom changes field of view, not camera distance.
- Camera distance is fixed at `6.0`.
- FOV starts at `60` degrees.
- FOV is clamped between `20` and `90` degrees.
- This avoids the extreme perspective distortion caused by dollying the camera.

### Pan

- Middle mouse drag changes projection matrix offsets `m[8]` and `m[9]`.
- Pan is screen-space and does not translate the model in depth.
- Current accumulators:
  - `g_panX -= 2.0f * deltaX / width`
  - `g_panY -= 2.0f * deltaY / height`
- The signs intentionally make the model follow the mouse direction:
  - Moving left moves the model left.
  - Moving up moves the model up.

### ImGui mouse capture

Win32 mouse messages are first sent to ImGui. If ImGui captures the mouse, model rotation, pan, and zoom input are suppressed. This prevents dragging inside the color picker from rotating the cube.

## UI decisions

- Dear ImGui files live under:
  - `E:\copilot\third_party\imgui\`
  - `E:\copilot\third_party\imgui\backends\`
- The project includes ImGui core and Win32/OpenGL3 backend source files directly.
- The UI includes a background color picker and controls for outline rendering.
- The `Load OBJ...` button opens a native file picker and loads triangle geometry
  with `third_party/tiny_obj_loader.h`. Loaded models are centered and uniformly
  scaled to fit the existing camera; the default cube is used at startup.
- The UI includes buttons to switch outline implementation:
  - `Brute-force` (9x9 neighborhood)
  - `Cross kernel` (horizontal + vertical neighborhood)
  - `Jump flood` (multi-pass jump-flood distance propagation)
  - `Gaussian blur` (Gaussian-weighted stencil-mask blur)
- The UI includes an `Outline thickness (px)` slider (1..32) that is sent to
  outline shaders.
- The UI includes an `Antialiased outline` checkbox that toggles smooth
  `fwidth`/`smoothstep` coverage versus hard-edged outline coverage in all
  outline composition shaders.
- The UI includes an `MSAA x8` checkbox. When enabled, the main scene renders
  into multisampled color + depth-stencil textures and is resolved into the
  single-sample main FBO before outline passes.
- The UI shows live performance text: `FPS` and `ms/frame`.
- The default background is white: `(1.0, 1.0, 1.0)`.

## Build and verification

Build from PowerShell:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Professional\MSBuild\Current\Bin\MSBuild.exe' `
  'D:\programming\git_rsaroha\GHCP\opengl-outline\OpenGLOutline.sln' `
  /m /p:Configuration=Debug /p:Platform=x64 /v:minimal
```

Run:

```powershell
Start-Process 'D:\programming\git_rsaroha\GHCP\opengl-outline\build\Debug\OpenGLOutline.exe'
```

The project has been repeatedly verified with successful Debug x64 builds and launch tests. When launch testing from automation, check that the process remains alive for several seconds and stop it with its specific PID.

## Project file details

`OpenGLOutline.vcxproj`:

- Uses `v145`.
- Uses x64 project configurations.
- Uses Debug/Release x64-compatible settings.
- Includes:
  - `main.cpp`
  - `renderer.cpp`
  - `ui.cpp`
  - ImGui core/backend `.cpp` files
  - `renderer.h`
  - `ui.h`
- Includes ImGui directories:
  - `E:\copilot\third_party\imgui`
  - `E:\copilot\third_party\imgui\backends`
- Copies all shader files to the output directory.

`OpenGLOutline.sln` currently uses the `Debug|x64` and `Release|x64` solution configurations.

## Resource ownership and cleanup

`Renderer_Shutdown()` deletes:

- Cube VAO and VBO.
- Cube, outline, and presentation shader programs.
- Main and outline framebuffer objects.
- Main color, packed depth-stencil, and outline textures.

`Renderer_Resize()` recreates both framebuffer targets through `CreateRenderTarget()`.

If framebuffer resources are changed, update all of:

1. Creation and attachment code.
2. Resize recreation.
3. Shutdown deletion.
4. Texture bindings in the outline/presentation passes.
5. Framebuffer completeness checks.

## Known caveats and future work

Current renderer behavior:

- The supported build target is x64, with Visual Studio and CMake outputs under
  `build`.
- Outline implementation, thickness, antialiasing, and MSAA x8 are controlled
  from the ImGui panel.
- The outline implementation choices are brute-force, cross-kernel, jump flood,
  and Gaussian blur.

- The outline width is controlled by the UI and passed to all outline shaders.
- The neighborhood is square (`9 x 9` samples), so the visual shape is a square-radius expansion rather than an exact Euclidean-radius outline.
- The outline color is hard-coded red.
- The outline is generated from the visible stencil mask and therefore outlines the visible silhouette, not hidden/back-facing geometry.
- The stencil texture sampling path depends on the OpenGL driver supporting packed depth-stencil texture sampling with `GL_DEPTH_STENCIL_TEXTURE_MODE = GL_STENCIL_INDEX`.
- The color picker changes the scene background but the current outline color is independent of the background color.
- Shader loading errors are shown with a Win32 message box.
- Shader compilation and program-link errors are also shown with a Win32 message box.
- Avoid adding shader source back into C++ string literals; external files are now the intended design.

## Safe change guidelines

- Keep project-owned C++ functions non-inline and format braces in Allman/BSD style,
  with opening braces on the following line.
- Preserve the OpenGL 3.3 compatibility profile unless there is an explicit design change.
- Keep shader interfaces synchronized with uniform lookups in `renderer.cpp`.
- If changing `outline.frag`, remember that the stencil texture is read with integer coordinates and `texelFetch`.
- Keep the rendering order as scene FBO -> outline FBO -> default framebuffer -> ImGui -> swap.
- Do not let ImGui input reach model controls while `WantCaptureMouse` is true.
- Build Debug x64 after renderer, shader, project, or UI changes.
- Do not move third-party ImGui files out of `E:\copilot\third_party\imgui`.

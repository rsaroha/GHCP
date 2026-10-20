# GL_from_WEBGL

Native Win32/OpenGL 3.3 port of the Jump Flood Algorithm distance-field effects in `webgl_2_ogl`,
with a Dear ImGui control panel.
The render pipeline keeps the source demo's low-resolution silhouette mask, mask expansion,
signed seed field, ping-pong JFA passes, and eight display modes. A procedural torus-knot mesh
is the startup fallback. The ImGui load action supports triangulated OBJ, glTF, and GLB meshes,
using the repository's tinyobjloader and tinygltf headers. glTF scene-node transforms are applied
and imported geometry is normalized to fit the view. Materials and textures are not applied to
the renderer; animation, sparse accessors, and non-triangle primitives are not supported. The source demo's HDR
environment is also not supported: this port uses basic directional lighting and has no HDR
environment or image-based-lighting pipeline.

## Build

Close the solution in Visual Studio first, then run `build.bat` from this directory to delete the
existing generated `build` directory, regenerate the x64 Visual Studio solution with CMake, and
build the Debug configuration.
Alternatively, from a Visual Studio Developer PowerShell:

```powershell
cmake -S . -B build -A x64
cmake --build build --config Debug
```

The build uses the repository's `third_party/imgui` sources for Dear ImGui and its Win32/OpenGL3
backends. GLSL programs are stored in `shaders/` and copied beside the executable during the build.
The application creates its own OpenGL 3.3 core context and uses a multisample framebuffer backed
by color and depth textures by default. The ImGui panel can disable FSAA; all framebuffer
attachments use textures. Scene, mask, seed, jump-flood, effect, UI, resolve, and presentation
rendering are split into explicit passes; each pass checks for OpenGL errors at entry and exit.

## Controls

- Drag with the left mouse button to orbit, right-drag to pan, and use the wheel to zoom. Pan and
  zoom are screen-space transforms that preserve the camera perspective.
- `M` / `Shift+M`: next / previous effect (Mask, Coordinate, SDF, Outline, Glow, Pulse, Halftone, Rings).
- `I`: toggle inside/outside effect.
- Up/Down: change thickness; hold Shift for larger steps.
- `C`: cycle effect color.
- Space: toggle auto-rotation; Esc: exit.

Use the ImGui panel to load an OBJ/glTF/GLB, choose the effect mode, change inside/outside,
thickness, color, and auto-rotation, or disable FSAA completely (when supported by the graphics
driver).

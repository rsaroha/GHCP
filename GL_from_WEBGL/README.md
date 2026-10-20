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

From a Visual Studio Developer PowerShell:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

The build uses the repository's `third_party/imgui` sources for Dear ImGui and its Win32/OpenGL3
backends. The application creates its own OpenGL 3.3 core context.

## Controls

- Drag with the left mouse button to orbit; use the wheel to zoom.
- `M` / `Shift+M`: next / previous effect (Mask, Coordinate, SDF, Outline, Glow, Pulse, Halftone, Rings).
- `I`: toggle inside/outside effect.
- Up/Down: change thickness; hold Shift for larger steps.
- `C`: cycle effect color.
- Space: toggle auto-rotation; Esc: exit.

Use the ImGui panel to load an OBJ/glTF/GLB, choose the effect mode, change inside/outside,
thickness, color, and auto-rotation.

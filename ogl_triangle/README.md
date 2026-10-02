# ogl_triangle

A minimal native Win32/WGL OpenGL Visual Studio project that renders a
lit Utah teapot using the OpenGL fixed-function API and standard Bézier patch
control data.

## Build

Open `ogl_triangle.sln` in Visual Studio 2022 with the **Desktop development
with C++** workload installed. Select `Debug | x64` or `Release | x64`, then
build and run.

The only external library is the Windows SDK's `opengl32.lib`; no third-party
dependencies are required. Hold the **left mouse button** and drag to rotate
the teapot with the virtual trackball. Press **Esc** to close the window.

# gl_capture

A custom OpenGL call capture/replay tool for Windows desktop GL, for
debugging rendering issues: intercept every GL call an app makes, log it
(with enough data to reproduce it later), and replay the trace against a
fresh context for inspection.

## Architecture

- **`codegen/functions.json` + `codegen/generate.py`** -- the source of
  truth for which GL functions are known. Running `generate.py` emits
  `generated/`: a `GLFuncId` enum, a table of real-function pointers
  (`RealGLFunctions`), mechanically-generated trace/replay code for
  value-only functions, and stub declarations for functions with
  pointer/array arguments that need hand-written logic.
- **`codegen/gl.xml` + `codegen/import_gl_registry.py`** -- the vendored
  Khronos desktop OpenGL registry and importer for the 1.0-4.6 core and
  compatibility command set. The importer emits typed signature metadata in
  `codegen/registry_commands.json`; commands are migrated into the active
  trace table only after their pointer sizes, return values, and object
  remapping rules have verified replay implementations.
- **`interceptor/`** -- builds `gl_capture_hook.dll`. Unlike a typical
  "proxy DLL" GL wrapper, this is *injected* into an already-running
  target process (see `ui/main.cpp`'s `InjectHookDll`) rather than dropped
  into its directory under the name `opengl32.dll`. On load, it patches
  the target's own import table (`interceptor/iat_patch.*`): every
  statically-imported GL/WGL function gets redirected to our wrapper, and
  `wglGetProcAddress` itself gets redirected so calls fetched dynamically
  (buffers, shaders, FBOs, ...) are traced too, by handing back our
  wrapper instead of the real address. `SwapBuffers`/`wglSwapBuffers` mark
  frame boundaries. Because the target's real `opengl32.dll` is never
  touched -- it loads exactly once, exactly as it would unmodified -- this
  avoids ever needing a second copy of the driver in the process (see
  "Known issues" below for why that mattered).
- **`replay/`** -- builds `gl_replay.exe`. Creates its own window+context
  and re-issues every recorded call against the real driver, remapping
  object ids (buffers/textures/programs/...) since the replay driver hands
  out different ids than the traced process saw. Its UI (and
  `gl_capture_ui`'s) is built on wxWidgets, statically linked from
  `third_party/wxWidgets` -- but the actual GL/WGL setup (pixel format,
  context creation, the hidden render surface) stays plain Win32, since
  that's independent of whatever toolkit draws the window around it.
  `gl_capture_test_app` intentionally stays pure Win32/GDI with no
  wxWidgets dependency, so there's always a minimal-dependency target to
  test the capture side against.
- **`common/`** -- the trace file format, the byte-cursor reader, the
  object-id remapper, and the minimal GL type definitions shared by both
  sides (deliberately not `<GL/gl.h>`, to avoid dllimport/dllexport
  collisions with our own exports).
- **`test_app/`** -- an app that renders a lit, textured cube into an FBO
  (color texture + a combined depth-stencil *texture* attachment, rather
  than a renderbuffer, via VBO/index-buffer/VAO geometry), then displays
  that FBO's color texture on a full-window quad. Exercises most of the
  traced surface in one run: buffers, index buffers, a VAO, 2D textures
  with mipmaps, FBOs, shader/program uniforms (including matrices), for
  smoke-testing the whole pipeline.

## Function coverage

Function coverage is a curated subset in `functions.json`: legacy
immediate-mode (`glBegin`/`glVertex3f`/matrix stack/...) plus a modern core
subset (buffers, VAOs, shaders/programs, textures, framebuffers, draw
calls). Adding a function means adding an entry to `functions.json` and
rerunning `generate.py`; functions with only value/enum arguments need
nothing else, functions with pointers/arrays need a hand-written pair in
`interceptor/custom_wrappers.cpp` / `replay/custom_replay.cpp`.

Client-memory (non-VBO) vertex arrays are snapshotted at draw-call time
(not when `glVertexPointer`/`glVertexAttribPointer` is called), since GL
fixes address-vs-offset interpretation at the time the pointer is set, and
replay has no access to the traced process's memory. One known gap: if the
element (index) buffer is a real VBO but a vertex attribute still points
at client memory, that attribute isn't captured (would need to shadow the
index VBO's contents to compute which vertices are reachable).

## Building

Requires a Windows C++ toolchain (MSVC) and CMake, plus a prebuilt static
wxWidgets at `../third_party/wxWidgets` (relative to this directory) --
the NuGet-style layout with `include/`, `include/msvc/`, and
`lib/vc_x64_lib/` containing the static (non-DLL) Debug/Unicode
(`*33ud*`) libs. Only that Debug/Unicode configuration is available, so
only `--config Debug` is supported.

```bash
cd gl_capture
mkdir build && cd build
cmake -A x64 ..
cmake --build . --config Debug
```

(Omit `-G`/let CMake pick the installed Visual Studio version -- pinning
a specific generator string like `"Visual Studio 17 2022"` breaks as
soon as VS auto-updates to a new major version.)

Produces `build/Debug/gl_capture_hook.dll`, `build/Debug/
gl_capture_ui.exe`, `gl_replay.exe`, and `gl_capture_test_app.exe`.

## Usage

The easiest way is `gl_capture_ui.exe`: pick a target `.exe` and a trace
path, choose a capture mode, then click **Start Capture**. It launches the
target suspended, injects `gl_capture_hook.dll` (which patches the target's
import table before its first instruction ever runs), resumes it, and waits
for it to exit.

The launcher can also prefill all capture fields from the command line:

```powershell
gl_capture_ui.exe -e <executable_path> -i "<arguments>" -d <run_directory> -o <output_trace_file_path>
```

For example:

```powershell
gl_capture_ui.exe `
  -e "D:\projects\Q2830_HOutline_loc\x86e_win64\obj\pglview.exe" `
  -i "-1 -t pgl_test21" `
  -d "D:\projects\Q2830_HOutline_loc\testrun" `
  -o "D:\projects\Q2830_HOutline_loc\testrun\gl_capture.trace"
```

The existing positional form, `gl_capture_ui.exe <executable> [trace-file]`,
is still supported. Command-line options prefill the UI; capture begins when
**Start Capture** is clicked.

Capture modes:
- **Trace all calls**: capture starts immediately and records every traced
  call/frame marker until the target exits or is stopped.
- **Capture one frame on demand**: the target starts with tracing disabled.
  Each **Capture Frame** click arms the next presented frame, recording calls
  from that frame only.

To do the same thing by hand: launch the target suspended (e.g.
`CreateProcess` with `CREATE_SUSPENDED`), inject `gl_capture_hook.dll`
into it (a `LoadLibraryA` call via a remote thread is the standard
technique), set `GLCAP_TRACE_PATH` in the environment beforehand, then
resume the main thread. If `GLCAP_TRACE_PATH` isn't set, the trace is
written to `gl_capture.trace` in the current directory.

Replay:

```bash
gl_replay.exe my_capture.trace
```

Replays the whole trace, swapping buffers at each captured frame boundary,
then leaves the final frame on screen until the window is closed. Set
`GLCAP_REPLAY_AUTOEXIT=1` to have it exit immediately after replaying
instead (useful for scripted/automated runs).

`gl_replay` opens a single maximized window divided into three vertical
columns, each able to hold up to two sub-windows (call list, render
surface, resources & state, and the two attachment viewers described
below), stacked top/bottom or filling the whole column. They're laid
out as child panels of one container rather than separate top-level
windows, so they stay together and can't get lost behind other
windows. Drag the thin gap between two columns (or, once a column is
split top/bottom, the gap between its two halves) to resize them --
each has a minimum size so none can be squeezed away entirely.

Drag a panel's label strip onto another panel to rearrange them:
- Dropping on the *middle* of a panel that's filling its whole column
  swaps the two panels' contents.
- Dropping near the *top or bottom edge* of a panel that's filling its
  whole column splits that column, giving the dragged panel the near
  half and pushing what was already there into the other half.
- Dropping onto an empty half (left behind after moving something out
  of it) just moves the dragged panel there.

A light-blue highlight on the label under the cursor shows where it'll
land, and a translucent blue overlay previews exactly what a drop right
now would do -- the whole panel's rect for a swap, or just its top/bottom
half when it would split instead, updating live as the cursor moves
between zones. Moving a panel out of a shared column automatically
collapses that column back down so the remaining panel fills it
completely again -- a panel is always either the sole occupant of its
column or sharing it with exactly one other.

The render panel displays the captured content at whatever size fits the
panel, preserving aspect ratio -- resizing the panel refits the image
rather than stretching or distorting it, since the underlying GL surface
that actually renders the frame is never itself resized to the panel
(its pixel size stays fixed at the size the trace was captured at, read
back and redrawn into the panel as a plain image instead). The mouse
wheel zooms in and out on that image (centered on the cursor), and
dragging with the left mouse button pans it; resizing the panel resets
back to the fit-and-centered view. Right-click to jump straight to the
image's actual (1:1) pixel size, keeping whatever point is under the
cursor fixed in place.

The default layout is call list (left column, full height), color
attachment over depth/stencil attachment (middle column), and render
over resources & state (right column) -- drag a panel's label onto
another's to rearrange, as described above.

The middle column's two panels are always-live views of the current
framebuffer's color and depth/stencil attachments: whichever FBO the
trace has most recently created (by captured id), or, if the trace
never creates one, the default framebuffer's back buffer and depth
buffer. Each attachment's dimensions and backing (texture or
renderbuffer) are queried directly from the live GL context
(`glGetFramebufferAttachmentParameteriv`), then read back with
`glReadPixels` -- which works the same way regardless of whether the
attachment is a texture or a renderbuffer, so no special-casing is
needed there. They refresh automatically after every run, right
alongside the resources & state panel, using the same depth/
depth-stencil classification and grayscale visualization as the
texture viewer described below. Like the render panel, each supports
mouse-wheel zoom (centered on the cursor), left-drag panning, and a
status line showing the exact value(s) under the cursor; an attachment
that isn't present (e.g. no depth buffer) shows as blank instead.

The call-list panel lists every captured call in order (frame boundaries
marked with `---- frame N ----`), each with its decoded arguments -- e.g.
`42: glBufferData(target=GL_ARRAY_BUFFER, size=36, data=36 bytes, usage=GL_STATIC_DRAW)`.
`GLenum` values are shown by symbolic name where known (falling back to
hex for anything not in the table); `GLbitfield` values are decomposed
into their flags, e.g. `glClear(mask=GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)`.
The name table (`codegen/gl_enums.json`, ~4000 entries) comes from the
Khronos `gl.xml` registry; since many GL enums share a numeric value
across unrelated purposes (0 is both `GL_POINTS` and `GL_ZERO`, for
instance), an occasional value may show a plausible-but-wrong name --
full disambiguation would need tracking each parameter's specific enum
group, which isn't done here. The list is a plain listbox with both
scrollbars, so it handles long traces and long lines. Large data (buffer/
texture contents, vertex array snapshots) is summarized by byte count
rather than dumped in full; shader source is shown truncated to ~60
characters.

A search box sits above the call list: type text and press Enter or
click **Search** to jump to the next line containing it (case-
insensitive), wrapping around to the top once it reaches the end.
Repeated searches continue from the current selection.

A green arrow appears to the left of whichever line execution was most
recently run to (the initial load runs to the last line; double-clicking
any line moves the arrow there once that run finishes).

The third panel, "resources & state", shows every buffer/texture/
framebuffer/renderbuffer/VAO/program/shader created so far (by id, with
its live-queried properties -- size and usage for buffers, dimensions and
format for textures, attachments for framebuffers, link/compile status for
programs/shaders) plus the current binding and pipeline state (bound
buffer/texture/framebuffer/program/VAO, viewport, clear color, blend/
depth/cull enable state). It's queried directly from the live GL context
right after a run stops, so it always reflects exactly where the replay
is -- refreshing automatically on the initial full run and after every
double-click "run to here". `GLenum` values here go through the same
symbolic-name lookup as the call list (e.g. `internalformat=GL_RGBA`
rather than `0x1908`).

Resource tracking relies on the same id-remap table used for object-id
translation, so it only knows about objects created via a captured
glGen*/glCreate* call (the modern-GL path); it won't list anything from
legacy immediate-mode state that has no object id (e.g. the matrix stack).

Double-clicking a texture line in that panel reads its pixels back
(`glGetTexImage`, from the same live context) and shows them in a
separate viewer window (not another panel of the container -- one such
window is created lazily and reused for whichever texture was double-
clicked most recently), initially scaled to fit (tiny textures are
scaled up, huge ones scaled down) while preserving aspect ratio. Depth and depth-stencil
internal formats are recognized and read back as depth (float, via
`GL_DEPTH_COMPONENT`) and, for combined formats, stencil too (via
`GL_DEPTH_STENCIL`/`GL_UNSIGNED_INT_24_8`, unpacked into the two values),
visualized as grayscale by depth; anything else is treated as an ordinary
color texture (`GL_BGRA`). Moving the mouse over the image shows the
exact value(s) at that pixel -- `R/G/B/A` for color, `depth`
(and `stencil`) otherwise -- in a status line at the bottom. It doesn't
attempt anything special for compressed formats.

The viewer supports freely zooming and panning: the mouse wheel zooms in
and out (centered on the cursor, so the texel under the pointer stays put
as the zoom changes), and dragging with the left mouse button pans.
Zoom/pan reset to the fit-and-centered view only when a texture is (re-)
opened, not on plain window resizes, so resizing the window to see more
detail doesn't fight with a zoom level you've already picked. Press
**Esc** to close the viewer window.

Double-clicking a shader line opens its captured source (from
`glShaderSource`, remembered per real shader id -- see
`replay/shader_registry.*`) in a small read-only text window, titled with
its type (`VERTEX`/`FRAGMENT`/`OTHER`, queried live via `glGetShaderiv`).

## Known issues

- **(Resolved) Loading the real driver a second time used to be flaky.**
  The original design was a same-named `opengl32.dll` proxy that had to
  load a *second copy* of the real driver internally to forward calls. On
  one heavily locked-down/virtualized machine this reliably produced a
  "zombie" context -- `wglCreateContext`/`wglMakeCurrent` reported success
  and returned real-looking function pointers, but `glGetString` returned
  null, shaders/FBOs failed, and real draw calls (`glDrawElements`) could
  crash *inside the driver itself*. Switching to import-table patching on
  an injected DLL (see Architecture above) means the real driver is now
  loaded exactly once, normally, by the target process itself -- this
  class of failure hasn't reproduced since, including on the same machine
  that reliably hit it before.
- `GL_TEXTURE_*` formats handled in `TexelSize` (interceptor/custom_wrappers.cpp)
  cover the common cases (RGB/RGBA/ALPHA/LUMINANCE/DEPTH); an uncommon
  format will still be captured but with a possibly-wrong computed byte
  length -- extend `TexelSize` if you hit one.

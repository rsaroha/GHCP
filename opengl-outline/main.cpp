#include <windows.h>
#include <gl/GL.h>
#include <stdio.h>
#include "renderer.h"
#include "ui.h"

#pragma comment(lib, "opengl32.lib")

#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);

extern "C" __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;

HGLRC g_renderContext = 0;
bool g_running = true;

static void* GetWglProc(const char* name)
{
    void* address = (void*)wglGetProcAddress(name);
    if (address == 0 || address == (void*)0x1 || address == (void*)0x2 || address == (void*)0x3 || address == (void*)-1)
    {
        address = (void*)GetProcAddress(GetModuleHandleA("opengl32.dll"), name);
    }
    return address;
}

LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (Ui_HandleMessage(window, message, wParam, lParam))
    {
        return 0;
    }

    const bool isMouseMessage = message == WM_LBUTTONDOWN || message == WM_LBUTTONUP || message == WM_MBUTTONDOWN || message == WM_MBUTTONUP || message == WM_MOUSEMOVE || message == WM_MOUSEWHEEL;
    if (isMouseMessage && Ui_CapturesMouse())
    {
        return 0;
    }

    if (message == WM_SIZE)
    {
        g_width = LOWORD(lParam);
        g_height = HIWORD(lParam);
        if (g_renderContext)
        {
            Renderer_Resize(g_width, g_height);
        }
        return 0;
    }

    if (message == WM_LBUTTONDOWN)
    {
        SetCapture(window);
        Renderer_MouseButton(0, true, (short)LOWORD(lParam), (short)HIWORD(lParam));
        return 0;
    }

    if (message == WM_LBUTTONUP)
    {
        Renderer_MouseButton(0, false, (short)LOWORD(lParam), (short)HIWORD(lParam));
        if (!(wParam & MK_MBUTTON))
        {
            ReleaseCapture();
        }
        return 0;
    }

    if (message == WM_MBUTTONDOWN)
    {
        SetCapture(window);
        Renderer_MouseButton(1, true, (short)LOWORD(lParam), (short)HIWORD(lParam));
        return 0;
    }

    if (message == WM_MBUTTONUP)
    {
        Renderer_MouseButton(1, false, (short)LOWORD(lParam), (short)HIWORD(lParam));
        if (!(wParam & MK_LBUTTON))
        {
            ReleaseCapture();
        }
        return 0;
    }

    if (message == WM_MOUSEMOVE)
    {
        Renderer_MouseMove((short)LOWORD(lParam), (short)HIWORD(lParam));
        return 0;
    }

    if (message == WM_MOUSEWHEEL)
    {
        Renderer_MouseWheel((short)HIWORD(wParam));
        return 0;
    }

    if (message == WM_CLOSE)
    {
        g_running = false;
        PostQuitMessage(0);
        return 0;
    }

    if (message == WM_KEYDOWN && wParam == VK_ESCAPE)
    {
        g_running = false;
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcA(window, message, wParam, lParam);
}

bool CreateOpenGLWindow(HINSTANCE instance)
{
    WNDCLASSA windowClass = {};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = instance;
    windowClass.hCursor = LoadCursorA(0, IDC_ARROW);
    windowClass.lpszClassName = "OpenGLOutlineWindow";
    if (!RegisterClassA(&windowClass))
    {
        return false;
    }

    g_window = CreateWindowExA(0, windowClass.lpszClassName, "OpenGL Compatibility - Texture FBO Cube", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, g_width, g_height, 0, 0, instance, 0);
    if (!g_window)
    {
        return false;
    }

    g_deviceContext = GetDC(g_window);
    PIXELFORMATDESCRIPTOR descriptor = {};
    descriptor.nSize = sizeof(descriptor);
    descriptor.nVersion = 1;
    descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descriptor.iPixelType = PFD_TYPE_RGBA;
    descriptor.cColorBits = 32;
    descriptor.cDepthBits = 24;
    descriptor.iLayerType = PFD_MAIN_PLANE;

    int format = ChoosePixelFormat(g_deviceContext, &descriptor);
    if (!format || !SetPixelFormat(g_deviceContext, format, &descriptor))
    {
        return false;
    }

    HGLRC temporary = wglCreateContext(g_deviceContext);
    if (!temporary || !wglMakeCurrent(g_deviceContext, temporary))
    {
        return false;
    }

    PFNWGLCREATECONTEXTATTRIBSARBPROC createContext = (PFNWGLCREATECONTEXTATTRIBSARBPROC)GetWglProc("wglCreateContextAttribsARB");
    if (!createContext)
    {
        return false;
    }

    const int attributes[] = { WGL_CONTEXT_MAJOR_VERSION_ARB, 3, WGL_CONTEXT_MINOR_VERSION_ARB, 3, WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, 0 };
    g_renderContext = createContext(g_deviceContext, 0, attributes);
    wglMakeCurrent(0, 0);
    wglDeleteContext(temporary);
    if (!g_renderContext || !wglMakeCurrent(g_deviceContext, g_renderContext))
    {
        return false;
    }

    const GLubyte* rendererName = glGetString(GL_RENDERER);
    if (rendererName != 0)
    {
        char title[256] = {};
        sprintf_s(title, "OpenGL Compatibility - Texture FBO Cube - %s", reinterpret_cast<const char*>(rendererName));
        SetWindowTextA(g_window, title);
    }

    return true;
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    if (!CreateOpenGLWindow(instance) || !Renderer_Initialize() || !Ui_Initialize(g_window))
    {
        return 1;
    }

    MSG message = {};
    while (g_running)
    {
        while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }

        Ui_NewFrame();
        Renderer_Render();
        Ui_Render();
        Renderer_Present();
    }

    Ui_Shutdown();
    Renderer_Shutdown();
    wglMakeCurrent(0, 0);
    wglDeleteContext(g_renderContext);
    ReleaseDC(g_window, g_deviceContext);
    DestroyWindow(g_window);
    return 0;
}







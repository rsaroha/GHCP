#pragma once

#include <windows.h>
#include <gl/GL.h>

extern HDC g_deviceContext;
extern HWND g_window;
extern int g_width;
extern int g_height;

enum OutlineImplementation
{
    OutlineNone = 0,
    OutlineBruteForce = 1,
    OutlineCrossKernel = 2,
    OutlineJumpFlood = 3,
    OutlineBetterJfa = 4,
    OutlineGaussianBlur = 5,
    OutlineBoxBlur = 6,
    OutlineSobel = 7
};
void Renderer_MouseButton(int button, bool down, int x, int y);
void Renderer_MouseMove(int x, int y);
void Renderer_MouseWheel(int delta);

bool Renderer_Initialize(void);
void Renderer_Resize(int width, int height);
void Renderer_Render(void);
void Renderer_UpdateGpuTimers(void);
void Renderer_Shutdown(void);
void Renderer_Present(void);
void Renderer_SwapBuffers(void);
void Renderer_SetBackgroundColor(float red, float green, float blue);
bool Renderer_LoadObj(const char* filename);
void Renderer_SetOutlineImplementation(OutlineImplementation implementation);
void Renderer_SetOutlineThickness(float pixels);
void Renderer_SetOutlineAntialiasing(bool enabled);
void Renderer_SetInteriorOutline(bool enabled);
void Renderer_SetExteriorOutline(bool enabled);
void Renderer_SetPostFxaa(bool enabled);
void Renderer_SetMsaaEnabled(bool enabled);
double Renderer_GetSceneTimeMicroseconds(void);
double Renderer_GetOutlineTimeMicroseconds(void);
double Renderer_GetFxaaTimeMicroseconds(void);
double Renderer_GetRenderTimeMicroseconds(void);
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
bool CreateOpenGLWindow(HINSTANCE instance);

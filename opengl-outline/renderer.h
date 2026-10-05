#pragma once

#include <windows.h>
#include <gl/GL.h>

extern HDC g_deviceContext;
extern HWND g_window;
extern int g_width;
extern int g_height;
void Renderer_MouseButton(int button, bool down, int x, int y);
void Renderer_MouseMove(int x, int y);
void Renderer_MouseWheel(int delta);

bool Renderer_Initialize(void);
void Renderer_Resize(int width, int height);
void Renderer_Render(void);
void Renderer_Shutdown(void);
void Renderer_Present(void);
void Renderer_SetBackgroundColor(float red, float green, float blue);
void Renderer_SetOutlineImplementation(int implementation);
void Renderer_SetOutlineThickness(float pixels);
void Renderer_SetOutlineAntialiasing(bool enabled);
void Renderer_SetMsaaEnabled(bool enabled);
LRESULT CALLBACK WindowProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
bool CreateOpenGLWindow(HINSTANCE instance);



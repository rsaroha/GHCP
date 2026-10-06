#pragma once

#include <windows.h>

bool Ui_Initialize(HWND window);
bool Ui_NewFrame(void);
void Ui_SetFrameTiming(double microseconds);
void Ui_SetTiming(double newFrameMicroseconds, double renderMicroseconds);
void Ui_Render(void);
void Ui_Shutdown(void);
bool Ui_HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
bool Ui_CapturesMouse(void);

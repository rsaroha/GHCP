#pragma once

#include <windows.h>

bool Ui_Initialize(HWND window);
void Ui_NewFrame(void);
void Ui_Render(void);
void Ui_Shutdown(void);
bool Ui_HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
bool Ui_CapturesMouse(void);


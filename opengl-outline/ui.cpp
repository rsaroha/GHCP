#include "ui.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include "renderer.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Ui_Initialize(HWND window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    if (!ImGui_ImplWin32_Init(window)) return false;
    if (!ImGui_ImplOpenGL3_Init("#version 330")) return false;
    return true;
}

void Ui_NewFrame(void)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static float backgroundColor[3] = { 1.0f, 1.0f, 1.0f };
    Renderer_SetBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);

    ImGui::Begin("OpenGL Outline Demo");
    ImGui::Text("Background color");
    ImGui::SameLine();
    if (ImGui::ColorButton("##BackgroundColor", ImVec4(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f), ImGuiColorEditFlags_NoTooltip, ImVec2(32.0f, 20.0f))) ImGui::OpenPopup("BackgroundColorPopup");
    if (ImGui::BeginPopup("BackgroundColorPopup")) {
        ImGui::ColorPicker3("##BackgroundColorPicker", backgroundColor, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex);
        ImGui::EndPopup();
    }    ImGui::End();
}

void Ui_Render(void)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Ui_Shutdown(void)
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

bool Ui_HandleMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    return ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam) != 0;
}




bool Ui_CapturesMouse(void)
{
    return ImGui::GetCurrentContext() != 0 && ImGui::GetIO().WantCaptureMouse;
}

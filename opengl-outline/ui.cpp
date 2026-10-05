#include "ui.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#include <commdlg.h>
#include <string>
#include "renderer.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#pragma comment(lib, "comdlg32.lib")

static bool OpenObjFileDialog(HWND window, std::string& filename)
{
    char path[MAX_PATH] = {};
    OPENFILENAMEA dialog = {};
    dialog.lStructSize = sizeof(dialog);
    dialog.hwndOwner = window;
    dialog.lpstrFilter = "Wavefront OBJ files (*.obj)\0*.obj\0All files (*.*)\0*.*\0";
    dialog.lpstrFile = path;
    dialog.nMaxFile = sizeof(path);
    dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
    dialog.lpstrDefExt = "obj";
    if (!GetOpenFileNameA(&dialog))
    {
        return false;
    }

    filename = path;
    return true;
}

static bool DrawOutlineModeButton(const char* label, int mode, int* selectedMode)
{
    bool isSelected = *selectedMode == mode;
    if (isSelected)
    {
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.16f, 0.50f, 0.30f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.20f, 0.62f, 0.37f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.12f, 0.42f, 0.25f, 1.0f));
    }

    bool clicked = ImGui::Button(label);
    if (clicked)
    {
        *selectedMode = mode;
    }

    if (isSelected)
    {
        ImGui::PopStyleColor(3);
    }

    return clicked;
}

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
    static int outlineImplementation = 0;
    static float outlineThickness = 4.0f;
    static bool outlineAntialiasing = true;
    static bool msaa8Enabled = false;
    static std::string loadedObjFilename = "Default cube";
    Renderer_SetBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    Renderer_SetOutlineImplementation(outlineImplementation);
    Renderer_SetOutlineThickness(outlineThickness);
    Renderer_SetOutlineAntialiasing(outlineAntialiasing);
    Renderer_SetMsaaEnabled(msaa8Enabled);

    ImGui::Begin("OpenGL Outline Demo");
    ImGui::Text("Background color");
    ImGui::SameLine();
    if (ImGui::ColorButton("##BackgroundColor", ImVec4(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f), ImGuiColorEditFlags_NoTooltip, ImVec2(32.0f, 20.0f)))
    {
        ImGui::OpenPopup("BackgroundColorPopup");
    }

    if (ImGui::BeginPopup("BackgroundColorPopup"))
    {
        ImGui::ColorPicker3("##BackgroundColorPicker", backgroundColor, ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHSV | ImGuiColorEditFlags_DisplayHex);
        ImGui::EndPopup();
    }

    if (ImGui::Button("Load OBJ..."))
    {
        std::string filename;
        if (OpenObjFileDialog(g_window, filename) && Renderer_LoadObj(filename.c_str()))
        {
            loadedObjFilename = filename;
        }
    }
    ImGui::SameLine();
    ImGui::TextWrapped("%s", loadedObjFilename.c_str());

    ImGui::Separator();
    ImGui::Text("Outline implementation");
    DrawOutlineModeButton("Brute-force", 0, &outlineImplementation);
    ImGui::SameLine();
    DrawOutlineModeButton("Cross kernel", 1, &outlineImplementation);
    ImGui::SameLine();
    DrawOutlineModeButton("Jump flood", 2, &outlineImplementation);
    ImGui::SameLine();
    DrawOutlineModeButton("Gaussian blur", 3, &outlineImplementation);

    ImGui::Checkbox("MSAA x8", &msaa8Enabled);
    ImGui::Checkbox("Antialiased outline", &outlineAntialiasing);
    ImGui::SliderFloat("Outline thickness (px)", &outlineThickness, 1.0f, 32.0f, "%.1f");
    ImGuiIO& io = ImGui::GetIO();
    float framesPerSecond = io.Framerate;
    float millisecondsPerFrame = framesPerSecond > 0.0f ? 1000.0f / framesPerSecond : 0.0f;
    ImGui::Text("FPS: %.1f (%.2f ms/frame)", framesPerSecond, millisecondsPerFrame);

    ImGui::End();
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

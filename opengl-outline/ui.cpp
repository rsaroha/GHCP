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

bool Ui_Initialize(HWND window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    

    ImFontConfig fontConfig;
    fontConfig.SizePixels = 13.0f;
    io.Fonts->AddFontDefaultVector(&fontConfig);

    ImGui::StyleColorsDark();
    ImGui::GetStyle().Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
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
    static OutlineImplementation outlineImplementation = OutlineBruteForce;
    static int outlineThickness = 4;
    static bool outlineAntialiasing = true;
    static bool interiorOutline = true;
    static bool exteriorOutline = true;
    static bool msaa8Enabled = false;
    static std::string loadedObjFilename = "Default cube";
    Renderer_SetBackgroundColor(backgroundColor[0], backgroundColor[1], backgroundColor[2]);
    Renderer_SetOutlineImplementation(outlineImplementation);
    if (outlineThickness < 1) outlineThickness = 1;
    if (outlineThickness > 100) outlineThickness = 100;
    Renderer_SetOutlineThickness((float)outlineThickness);
    Renderer_SetOutlineAntialiasing(outlineAntialiasing);
    Renderer_SetInteriorOutline(interiorOutline);
    Renderer_SetExteriorOutline(exteriorOutline);
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
    const char* outlineImplementationNames[] = {
        "Brute-force",
        "Cross kernel",
        "Jump flood (JFA)",
        "Better-JFA",
        "Gaussian blur",
        "Box blur"
    };
    int outlineImplementationIndex = (int)outlineImplementation;
    if (outlineImplementationIndex < (int)OutlineBruteForce ||
        outlineImplementationIndex > (int)OutlineBoxBlur)
    {
        outlineImplementation = OutlineBruteForce;
        outlineImplementationIndex = (int)outlineImplementation;
    }
    ImGui::SetNextItemWidth(180.0f);
    if (ImGui::Combo("##OutlineImplementation", &outlineImplementationIndex, outlineImplementationNames,
        (int)(sizeof(outlineImplementationNames) / sizeof(outlineImplementationNames[0]))))
    {
        outlineImplementation = (OutlineImplementation)outlineImplementationIndex;
    }

    ImGui::Separator();

    ImGui::Checkbox("MSAA x8", &msaa8Enabled);
    ImGui::Checkbox("Antialiased outline", &outlineAntialiasing);
    ImGui::Checkbox("Interior outline", &interiorOutline);
    ImGui::Checkbox("Exterior outline", &exteriorOutline);
    ImGui::Text("Outline thickness (px)");
    //ImGui::SameLine();
    ImGui::SetNextItemWidth(160.0f);
    ImGui::SliderInt("##OutlineThicknessSlider", &outlineThickness, 1, 100);
    /*ImGui::SameLine();
    if (ImGui::Button("-"))
    {
        if (outlineThickness > 1) --outlineThickness;
    } */
    ImGui::SameLine(); 
    ImGui::SetNextItemWidth(100.0f);
    if (ImGui::InputInt("##OutlineThickness", &outlineThickness, 1, 1))
    {
        if (outlineThickness < 1) outlineThickness = 1;
        if (outlineThickness > 100) outlineThickness = 100;
    }
    /*
    ImGui::SameLine();
    if (ImGui::Button("+"))
    {
        if (outlineThickness < 100) ++outlineThickness;
    }*/
    ImGuiIO& io = ImGui::GetIO();
    float framesPerSecond = io.Framerate;
    float millisecondsPerFrame = framesPerSecond > 0.0f ? 1000.0f / framesPerSecond : 0.0f;

    ImGui::Separator();
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

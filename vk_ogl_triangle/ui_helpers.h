#pragma once
#include <imgui.h>
#include "config.h"

// Returns true if any value changed.
inline bool materialEditor(const char* idSuffix,
                            float color[3], float& alpha,
                            float& ambient, float& diffuse,
                            float& specular, float& shininess,
                            int& matType,
                            float& p0, float& p1, float& p2, float& p3)
{
    bool changed = false;
    char id[64];

    static const char* matNames[] = {
        "Phong", "Toon", "Gooch", "Rim/Fresnel",
        "Oren-Nayar", "Minnaert", "PBR", "Anisotropic", "SSS"
    };
    ImGui::Text("Shader");    ImGui::SameLine();
    snprintf(id, sizeof(id), "##mat%s", idSuffix);
    int prevType = matType;
    if (ImGui::Combo(id, &matType, matNames, IM_ARRAYSIZE(matNames))) {
        changed = true;
        if (matType != prevType) {
            p0 = p1 = p2 = p3 = 0.0f;
            switch (matType) {
            case 1: p0=4.0f; p1=0.8f; p2=3.0f; p3=0.5f; break;
            case 2: p0=0.5f; p1=1.0f;           break;
            case 3: p0=3.0f; p1=1.0f; p2=0.5f; p3=0.0f; break;
            case 4: p0=0.5f;                     break;
            case 5: p0=1.0f;                     break;
            case 6: p0=0.0f; p1=0.4f;           break;
            case 7: p0=0.3f; p1=0.1f; p2=0.0f; p3=1.0f; break;
            case 8: p0=0.5f; p1=0.3f; p2=0.5f; break;
            }
        }
    }

    ImGui::Text("Color");     ImGui::SameLine();
    snprintf(id, sizeof(id), "##col%s", idSuffix);
    changed |= ImGui::ColorEdit3(id, color,
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_NoLabel);

    ImGui::Text("Opacity");   ImGui::SameLine();
    snprintf(id, sizeof(id), "##opa%s", idSuffix);
    changed |= ImGui::SliderFloat(id, &alpha,     0.0f,   1.0f);

    ImGui::Text("Ambient");   ImGui::SameLine();
    snprintf(id, sizeof(id), "##amb%s", idSuffix);
    changed |= ImGui::SliderFloat(id, &ambient,   0.0f,   1.0f);

    ImGui::Text("Diffuse");   ImGui::SameLine();
    snprintf(id, sizeof(id), "##dif%s", idSuffix);
    changed |= ImGui::SliderFloat(id, &diffuse,   0.0f,   1.0f);

    ImGui::Text("Specular");  ImGui::SameLine();
    snprintf(id, sizeof(id), "##spc%s", idSuffix);
    changed |= ImGui::SliderFloat(id, &specular,  0.0f,   1.0f);

    ImGui::Text("Shininess"); ImGui::SameLine();
    snprintf(id, sizeof(id), "##shi%s", idSuffix);
    changed |= ImGui::SliderFloat(id, &shininess, 1.0f, 256.0f);

    switch (matType) {
    case 1: {
        ImGui::Text("Bands");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##tn_b%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 1.0f, 8.0f, "%.0f");
        ImGui::Text("SpcThr");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##tn_s%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p1, 0.0f, 1.0f);
        ImGui::Text("RimPow");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##tn_r%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p2, 0.1f, 10.0f);
        ImGui::Text("RimInt");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##tn_i%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p3, 0.0f, 2.0f);
        break;
    }
    case 2: {
        ImGui::Text("Blend");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##gc_b%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.0f, 1.0f);
        ImGui::Text("Specular");ImGui::SameLine();
        snprintf(id, sizeof(id), "##gc_s%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p1, 0.0f, 2.0f);
        break;
    }
    case 3: {
        ImGui::Text("RimPow");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##rm_p%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.1f, 10.0f);
        ImGui::Text("RimClr");  ImGui::SameLine();
        float rimCol[3] = { p1, p2, p3 };
        snprintf(id, sizeof(id), "##rm_c%s", idSuffix);
        if (ImGui::ColorEdit3(id, rimCol,
                ImGuiColorEditFlags_NoInputs |
                ImGuiColorEditFlags_PickerHueWheel |
                ImGuiColorEditFlags_NoLabel))
        { p1 = rimCol[0]; p2 = rimCol[1]; p3 = rimCol[2]; changed = true; }
        break;
    }
    case 4: {
        ImGui::Text("Rough");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##on_r%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.0f, 1.0f);
        break;
    }
    case 5: {
        ImGui::Text("k");       ImGui::SameLine();
        snprintf(id, sizeof(id), "##mn_k%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.1f, 2.0f);
        break;
    }
    case 6: {
        ImGui::Text("Metal");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##pb_m%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.0f, 1.0f);
        ImGui::Text("Rough");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##pb_r%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p1, 0.04f, 1.0f);
        break;
    }
    case 7: {
        ImGui::Text("RoughX");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##an_x%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.01f, 1.0f);
        ImGui::Text("RoughY");  ImGui::SameLine();
        snprintf(id, sizeof(id), "##an_y%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p1, 0.01f, 1.0f);
        ImGui::Text("Angle");   ImGui::SameLine();
        snprintf(id, sizeof(id), "##an_a%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p2, 0.0f, 360.0f, "%.0f");
        ImGui::Text("SpecStr"); ImGui::SameLine();
        snprintf(id, sizeof(id), "##an_s%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p3, 0.0f, 2.0f);
        break;
    }
    case 8: {
        ImGui::Text("Wrap");    ImGui::SameLine();
        snprintf(id, sizeof(id), "##ss_w%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p0, 0.0f, 1.0f);
        ImGui::Text("BackLit"); ImGui::SameLine();
        snprintf(id, sizeof(id), "##ss_b%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p1, 0.0f, 2.0f);
        ImGui::Text("Scatter"); ImGui::SameLine();
        snprintf(id, sizeof(id), "##ss_s%s", idSuffix);
        changed |= ImGui::SliderFloat(id, &p2, 0.0f, 1.0f);
        break;
    }
    default: break;
    }

    return changed;
}

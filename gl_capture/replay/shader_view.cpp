#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "shader_view.h"

#include <wx/wx.h>

#include <cstdio>
#include <string>

#include "gl_inspect.h"
#include "shader_registry.h"

namespace {

constexpr GLenum GL_SHADER_TYPE = 0x8B4F;
constexpr GLenum GL_VERTEX_SHADER = 0x8B31;
constexpr GLenum GL_FRAGMENT_SHADER = 0x8B30;

class ShaderViewFrame : public wxFrame {
public:
    ShaderViewFrame() : wxFrame(nullptr, wxID_ANY, "shader", wxDefaultPosition, wxSize(600, 500)) {
        m_text = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                                 wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP | wxHSCROLL);
        wxFont font(11, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, "Consolas");
        m_text->SetFont(font);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(m_text, 1, wxEXPAND);
        SetSizer(sizer);

        Bind(wxEVT_CLOSE_WINDOW, &ShaderViewFrame::OnClose, this);
    }

    void SetSource(const wxString& text) { m_text->SetValue(text); }

private:
    void OnClose(wxCloseEvent&);

    wxTextCtrl* m_text;
};

ShaderViewFrame* g_shaderFrame = nullptr;

void ShaderViewFrame::OnClose(wxCloseEvent&) {
    g_shaderFrame = nullptr;
    Destroy();
}

} // namespace

void ShowShaderSource(GLuint realId) {
    const std::string* source = GetShaderSource(realId);

    GLint type = 0;
    if (g_inspect.glGetShaderiv) g_inspect.glGetShaderiv(realId, GL_SHADER_TYPE, &type);
    const char* kind = type == GL_VERTEX_SHADER ? "VERTEX" : type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "OTHER";

    if (!g_shaderFrame) g_shaderFrame = new ShaderViewFrame();

    g_shaderFrame->SetTitle(wxString::Format("shader %u (%s)", realId, kind));
    // wxTextCtrl handles "\n"-only line breaks fine on wxMSW, no CRLF conversion needed.
    g_shaderFrame->SetSource(source ? wxString(*source) : wxString("(no source captured for this shader)"));

    g_shaderFrame->Show();
    g_shaderFrame->Raise();
}

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include "texture_view.h"

#include <wx/wx.h>

#include <cstdint>
#include <cstdio>
#include <utility>
#include <vector>

#include "gl_inspect.h"
#include "gl_real_table.h"

namespace {

constexpr GLenum GL_TEXTURE_2D = 0x0DE1;
constexpr GLenum GL_TEXTURE_BINDING_2D = 0x8069;
constexpr GLenum GL_BGRA = 0x80E1;
constexpr GLenum GL_UNSIGNED_BYTE = 0x1401;
constexpr GLenum GL_FLOAT = 0x1406;
constexpr GLenum GL_UNSIGNED_INT_24_8 = 0x84FA;
constexpr GLenum GL_DEPTH_COMPONENT = 0x1902;
constexpr GLenum GL_DEPTH_STENCIL = 0x84F9;
constexpr int kMaxDisplaySize = 800;
constexpr int kStatusBarHeight = 22;
constexpr int kMinWindowWidth = 380; // enough for the longest hover status line

enum class TexKind { Color, Depth, DepthStencil };

TexKind ClassifyFormat(GLenum internalFormat) {
    switch (internalFormat) {
        case 0x88F0: // GL_DEPTH24_STENCIL8
        case 0x8CAD: // GL_DEPTH32F_STENCIL8
        case 0x84F9: // GL_DEPTH_STENCIL
            return TexKind::DepthStencil;
        case 0x1902: // GL_DEPTH_COMPONENT
        case 0x81A5: // GL_DEPTH_COMPONENT16
        case 0x81A6: // GL_DEPTH_COMPONENT24
        case 0x81A7: // GL_DEPTH_COMPONENT32
        case 0x8CAC: // GL_DEPTH_COMPONENT32F
            return TexKind::Depth;
        default:
            return TexKind::Color;
    }
}

// Displays the texture image, letting the mouse wheel zoom (centered on
// the cursor) and left-drag pan; reports the exact per-pixel value(s)
// under the cursor via a status label owned by the enclosing frame.
// Zoom/pan reset only when a new texture is loaded (SetTexture), not on
// plain window resizes.
class TextureCanvas : public wxPanel {
public:
    TextureCanvas(wxWindow* parent, wxStaticText* status)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE), m_status(status) {
        Bind(wxEVT_PAINT, &TextureCanvas::OnPaint, this);
        Bind(wxEVT_SIZE, &TextureCanvas::OnSize, this);
        Bind(wxEVT_MOUSEWHEEL, &TextureCanvas::OnMouseWheel, this);
        Bind(wxEVT_LEFT_DOWN, &TextureCanvas::OnLeftDown, this);
        Bind(wxEVT_LEFT_UP, &TextureCanvas::OnLeftUp, this);
        Bind(wxEVT_MOTION, &TextureCanvas::OnMouseMove, this);
        Bind(wxEVT_RIGHT_DOWN, &TextureCanvas::OnRightDown, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    }

    void SetTexture(TexKind kind, int w, int h, std::vector<unsigned char> displayPixels,
                     std::vector<unsigned char> colorRaw, std::vector<float> depthRaw,
                     std::vector<unsigned char> stencilRaw) {
        m_kind = kind;
        m_texW = w;
        m_texH = h;
        m_displayPixels = std::move(displayPixels);
        m_colorRaw = std::move(colorRaw);
        m_depthRaw = std::move(depthRaw);
        m_stencilRaw = std::move(stencilRaw);
        m_dragging = false;
        ResetView();
        Refresh();
    }

    void ResetView() {
        wxSize sz = GetClientSize();
        int availW = sz.GetWidth(), availH = sz.GetHeight();
        if (m_texW <= 0 || m_texH <= 0 || availW <= 0 || availH <= 0) {
            m_zoom = 1.0;
            m_panX = m_panY = 0;
            return;
        }
        m_zoom = (availW / static_cast<double>(m_texW) < availH / static_cast<double>(m_texH))
                     ? availW / static_cast<double>(m_texW)
                     : availH / static_cast<double>(m_texH);
        int dispW = static_cast<int>(m_texW * m_zoom);
        int dispH = static_cast<int>(m_texH * m_zoom);
        m_panX = (availW - dispW) / 2;
        m_panY = (availH - dispH) / 2;
    }

private:
    void UpdateStatusForPoint(int clientX, int clientY) {
        if (m_texW <= 0 || m_texH <= 0 || m_zoom <= 0) {
            m_status->SetLabel("");
            return;
        }
        double texXf = (clientX - m_panX) / m_zoom;
        double texYFromTopF = (clientY - m_panY) / m_zoom; // 0 at the top of the displayed image
        if (texXf < 0 || texYFromTopF < 0 || texXf >= m_texW || texYFromTopF >= m_texH) {
            m_status->SetLabel("");
            return;
        }
        int texX = static_cast<int>(texXf);
        int texYFromTop = static_cast<int>(texYFromTopF);
        int bufRow = m_texH - 1 - texYFromTop; // our buffers are bottom-up (row 0 = bottom), like GL itself
        size_t idx = static_cast<size_t>(bufRow) * m_texW + texX;

        char buf[160];
        if (m_kind == TexKind::Color && idx * 4 + 3 < m_colorRaw.size()) {
            const unsigned char* p = &m_colorRaw[idx * 4];
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  R=%d  G=%d  B=%d  A=%d   [zoom %.0f%%, drag to pan, wheel to zoom, Esc to close]",
                     texX, texYFromTop, p[2], p[1], p[0], p[3], m_zoom * 100.0);
        } else if (m_kind == TexKind::DepthStencil && idx < m_depthRaw.size() && idx < m_stencilRaw.size()) {
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  depth=%.6f  stencil=%u   [zoom %.0f%%]",
                     texX, texYFromTop, m_depthRaw[idx], m_stencilRaw[idx], m_zoom * 100.0);
        } else if (m_kind == TexKind::Depth && idx < m_depthRaw.size()) {
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  depth=%.6f   [zoom %.0f%%]", texX, texYFromTop, m_depthRaw[idx], m_zoom * 100.0);
        } else {
            m_status->SetLabel("");
            return;
        }
        m_status->SetLabel(wxString(buf));
    }

    void ZoomAt(int clientX, int clientY, double factor) {
        double oldZoom = m_zoom;
        double newZoom = oldZoom * factor;
        if (newZoom < 0.05) newZoom = 0.05;
        if (newZoom > 40.0) newZoom = 40.0;
        double texelX = (clientX - m_panX) / oldZoom;
        double texelY = (clientY - m_panY) / oldZoom;
        m_panX = static_cast<int>(clientX - texelX * newZoom);
        m_panY = static_cast<int>(clientY - texelY * newZoom);
        m_zoom = newZoom;
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();
        if (m_displayPixels.empty()) return;
        HDC hdc = static_cast<HDC>(dc.GetHDC());
        if (!hdc) return;
        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = m_texW;
        bmi.bmiHeader.biHeight = m_texH; // positive: bottom-up, matches how we filled it
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        int dispW = static_cast<int>(m_texW * m_zoom);
        int dispH = static_cast<int>(m_texH * m_zoom);
        StretchDIBits(hdc, m_panX, m_panY, dispW, dispH, 0, 0, m_texW, m_texH,
                       m_displayPixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);
    }

    void OnSize(wxSizeEvent& event) {
        Refresh();
        event.Skip();
    }

    void OnMouseWheel(wxMouseEvent& event) {
        double factor = (event.GetWheelRotation() > 0) ? 1.1 : (1.0 / 1.1);
        ZoomAt(event.GetX(), event.GetY(), factor);
        UpdateStatusForPoint(event.GetX(), event.GetY());
        Refresh();
    }

    void OnLeftDown(wxMouseEvent& event) {
        m_dragging = true;
        m_dragStart = event.GetPosition();
        m_dragPanStartX = m_panX;
        m_dragPanStartY = m_panY;
        CaptureMouse();
    }

    void OnLeftUp(wxMouseEvent&) {
        m_dragging = false;
        if (HasCapture()) ReleaseMouse();
    }

    // Right-click resets zoom/pan back to the fit-and-centered default
    // view, the same one shown when the texture is first opened.
    void OnRightDown(wxMouseEvent& event) {
        ResetView();
        UpdateStatusForPoint(event.GetX(), event.GetY());
        Refresh();
    }

    void OnMouseMove(wxMouseEvent& event) {
        if (m_dragging && event.LeftIsDown()) {
            m_panX = m_dragPanStartX + (event.GetX() - m_dragStart.x);
            m_panY = m_dragPanStartY + (event.GetY() - m_dragStart.y);
            Refresh(false);
        }
        UpdateStatusForPoint(event.GetX(), event.GetY());
    }

    TexKind m_kind = TexKind::Color;
    int m_texW = 0, m_texH = 0;
    std::vector<unsigned char> m_displayPixels; // BGRA8, bottom-up -- what StretchDIBits shows
    std::vector<unsigned char> m_colorRaw;      // valid when m_kind == Color (same data as m_displayPixels)
    std::vector<float> m_depthRaw;              // depth in [0,1] per pixel, valid when Depth or DepthStencil
    std::vector<unsigned char> m_stencilRaw;    // valid when DepthStencil

    double m_zoom = 1.0;
    int m_panX = 0, m_panY = 0;
    bool m_dragging = false;
    wxPoint m_dragStart;
    int m_dragPanStartX = 0, m_dragPanStartY = 0;

    wxStaticText* m_status;
};

class TextureViewFrame : public wxFrame {
public:
    TextureViewFrame() : wxFrame(nullptr, wxID_ANY, "texture") {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_status = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, kStatusBarHeight));
        m_canvas = new TextureCanvas(this, m_status);
        sizer->Add(m_canvas, 1, wxEXPAND);
        sizer->Add(m_status, 0, wxEXPAND | wxALL, 3);
        SetSizer(sizer);

        Bind(wxEVT_CHAR_HOOK, &TextureViewFrame::OnCharHook, this);
        Bind(wxEVT_CLOSE_WINDOW, &TextureViewFrame::OnClose, this);
    }

    TextureCanvas* GetCanvas() const { return m_canvas; }

private:
    void OnCharHook(wxKeyEvent& event) {
        if (event.GetKeyCode() == WXK_ESCAPE) {
            Close();
            return;
        }
        event.Skip();
    }

    void OnClose(wxCloseEvent&);

    TextureCanvas* m_canvas = nullptr;
    wxStaticText* m_status = nullptr;
};

TextureViewFrame* g_texFrame = nullptr;

void TextureViewFrame::OnClose(wxCloseEvent&) {
    g_texFrame = nullptr;
    Destroy();
}

} // namespace

void ShowTextureImage(GLuint realId, GLint width, GLint height, GLenum internalFormat) {
    if (!g_real.glBindTexture || width <= 0 || height <= 0) return;

    GLint prevTex = 0;
    if (g_inspect.glGetIntegerv) g_inspect.glGetIntegerv(GL_TEXTURE_BINDING_2D, &prevTex);
    g_real.glBindTexture(GL_TEXTURE_2D, realId);

    TexKind kind = ClassifyFormat(internalFormat);
    size_t pixelCount = static_cast<size_t>(width) * height;
    std::vector<unsigned char> displayPixels(pixelCount * 4, 0);
    std::vector<unsigned char> colorRaw;
    std::vector<float> depthRaw;
    std::vector<unsigned char> stencilRaw;

    if (kind == TexKind::Color) {
        if (g_inspect.glGetTexImage) g_inspect.glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, displayPixels.data());
        colorRaw = displayPixels;
    } else if (kind == TexKind::DepthStencil) {
        std::vector<uint32_t> packed(pixelCount, 0);
        if (g_inspect.glGetTexImage) g_inspect.glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, packed.data());
        depthRaw.assign(pixelCount, 0.0f);
        stencilRaw.assign(pixelCount, 0);
        for (size_t i = 0; i < pixelCount; ++i) {
            depthRaw[i] = (packed[i] >> 8) / 16777215.0f; // top 24 bits
            stencilRaw[i] = static_cast<unsigned char>(packed[i] & 0xFF);
            unsigned char gray = static_cast<unsigned char>(depthRaw[i] * 255.0f);
            displayPixels[i * 4 + 0] = gray;
            displayPixels[i * 4 + 1] = gray;
            displayPixels[i * 4 + 2] = gray;
            displayPixels[i * 4 + 3] = 255;
        }
    } else { // Depth-only
        depthRaw.assign(pixelCount, 0.0f);
        if (g_inspect.glGetTexImage) g_inspect.glGetTexImage(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, GL_FLOAT, depthRaw.data());
        for (size_t i = 0; i < pixelCount; ++i) {
            unsigned char gray = static_cast<unsigned char>(depthRaw[i] * 255.0f);
            displayPixels[i * 4 + 0] = gray;
            displayPixels[i * 4 + 1] = gray;
            displayPixels[i * 4 + 2] = gray;
            displayPixels[i * 4 + 3] = 255;
        }
    }

    g_real.glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(prevTex));

    if (!g_texFrame) g_texFrame = new TextureViewFrame();

    const char* kindStr = kind == TexKind::Color ? "" : kind == TexKind::DepthStencil ? " depth-stencil" : " depth";
    g_texFrame->SetTitle(wxString::Format("texture %u (%dx%d%s)", realId, width, height, kindStr));
    g_texFrame->GetCanvas()->SetTexture(kind, width, height, std::move(displayPixels), std::move(colorRaw),
                                         std::move(depthRaw), std::move(stencilRaw));

    // Pick an initial window size that shows the texture at a sane scale
    // (tiny textures enlarged, huge ones shrunk) while preserving aspect
    // ratio, but never narrower than kMinWindowWidth -- otherwise the
    // hover status text (which can be longer than a small texture is
    // wide) would get clipped.
    int showW = width, showH = height;
    int longest = showW > showH ? showW : showH;
    if (longest > kMaxDisplaySize) {
        double scale = static_cast<double>(kMaxDisplaySize) / longest;
        showW = static_cast<int>(showW * scale);
        showH = static_cast<int>(showH * scale);
    } else if (longest < 128) {
        double scale = 128.0 / longest;
        showW = static_cast<int>(showW * scale);
        showH = static_cast<int>(showH * scale);
    }
    if (showW < kMinWindowWidth) showW = kMinWindowWidth;

    g_texFrame->SetClientSize(showW, showH + kStatusBarHeight);
    g_texFrame->GetCanvas()->ResetView();
    g_texFrame->Show();
    g_texFrame->Raise();
    g_texFrame->SetFocus();
    g_texFrame->GetCanvas()->Refresh();
}

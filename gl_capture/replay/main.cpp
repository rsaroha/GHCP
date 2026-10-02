// Replay tool: shows the render surface, the call list, and the
// resources/state view as three resizable panels in one window (built on
// wxWidgets -- wxSplitterWindow gives panel resizing for free; dragging a
// panel's title onto another's swaps their contents, "snapping" them to
// a different slot), then loads a trace file fully into memory and
// replays it against the real driver. Swaps buffers at each captured
// frame boundary. Double-clicking a call-list entry re-runs the trace
// from the start up to (and including) that call, then stops there --
// since GL state can't be rewound, "running to a point" means restarting
// and fast-forwarding rather than seeking.
//
// The actual GL rendering happens on a hidden native window (never shown
// -- see RenderPanel) sized to match the captured content; each frame is
// read back into a plain pixel buffer and displayed, fit/zoomed/panned,
// by the (wx) render panel. This keeps the GL surface's size decoupled
// from the panel's size/zoom/pan entirely, and keeps wxWidgets out of
// the GL/WGL setup, which stays plain Win32.
//
// Usage: gl_replay.exe <trace-file>
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <windowsx.h>

#include <wx/wx.h>
#include <wx/splitter.h>

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <utility>
#include <vector>

#include "gl_format_calls.h"
#include "gl_ids.h"
#include "gl_inspect.h"
#include "gl_real_table.h"
#include "gl_replay_decode.h"
#include "gl_state_view.h"
#include "id_remapper.h"
#include "shader_registry.h"
#include "shader_view.h"
#include "texture_view.h"
#include "trace_format.h"

namespace {

constexpr GLenum GL_VIEWPORT = 0x0BA2;
constexpr GLenum GL_BGRA = 0x80E1;
constexpr GLenum GL_UNSIGNED_BYTE = 0x1401;
constexpr GLenum GL_FLOAT = 0x1406;
constexpr GLenum GL_UNSIGNED_INT_24_8 = 0x84FA;
constexpr GLenum GL_DEPTH_COMPONENT = 0x1902;
constexpr GLenum GL_DEPTH_STENCIL = 0x84F9;
constexpr GLenum GL_TEXTURE_2D = 0x0DE1;
constexpr GLenum GL_TEXTURE_2D_MULTISAMPLE = 0x9100;
constexpr GLenum GL_TEXTURE_BINDING_2D = 0x8069;
constexpr GLenum GL_TEXTURE_BINDING_2D_MULTISAMPLE = 0x9104;
constexpr GLenum GL_TEXTURE_WIDTH = 0x1000;
constexpr GLenum GL_TEXTURE_HEIGHT = 0x1001;
constexpr GLenum GL_RENDERBUFFER = 0x8D41;
constexpr GLenum GL_RENDERBUFFER_BINDING = 0x8CA7;
constexpr GLenum GL_RENDERBUFFER_WIDTH = 0x8D42;
constexpr GLenum GL_RENDERBUFFER_HEIGHT = 0x8D43;
constexpr GLenum GL_FRAMEBUFFER = 0x8D40;
constexpr GLenum GL_FRAMEBUFFER_BINDING = 0x8CA6;
constexpr GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
constexpr GLenum GL_DEPTH_ATTACHMENT = 0x8D00;
constexpr GLenum GL_STENCIL_ATTACHMENT = 0x8D20;
constexpr GLenum GL_DEPTH_STENCIL_ATTACHMENT = 0x821A;
constexpr GLenum GL_READ_BUFFER = 0x0C02;
constexpr GLenum GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE = 0x8CD0;
constexpr GLenum GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME = 0x8CD1;
constexpr GLenum GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_TARGET = 0x8CD6;
constexpr GLenum GL_ATTACHMENT_TYPE_TEXTURE = 0x1702; // GL_TEXTURE
constexpr GLenum GL_NONE_ATTACHMENT = 0;
constexpr int kDefaultGLContentW = 640;
constexpr int kDefaultGLContentH = 480;

constexpr int PANEL_RENDER = 0;
constexpr int PANEL_CALLLIST = 1;
constexpr int PANEL_STATE = 2;
constexpr int PANEL_COLOR_ATTACHMENT = 3;
constexpr int PANEL_DEPTH_ATTACHMENT = 4;
constexpr int PANEL_EMPTY = -1;

struct Record {
    bool isFrameMarker;
    GLFuncId id;
    std::vector<uint8_t> data;
};

wxString LabelForIdentity(int identity) {
    switch (identity) {
        case PANEL_RENDER: return "Render";
        case PANEL_CALLLIST: return "Call list (double-click: run to here)";
        case PANEL_STATE: return "Resources & state (double-click a texture/shader to view it)";
        case PANEL_COLOR_ATTACHMENT: return "Color attachment";
        case PANEL_DEPTH_ATTACHMENT: return "Depth/stencil attachment";
        default: return "(empty -- drag a panel here)";
    }
}

// Same classification used by the (separate, floating) texture viewer --
// duplicated rather than shared since it's a couple of lines and pulling
// texture_view.h in here would be for one enum.
enum class AttachmentKind { Color, Depth, DepthStencil };

// ---------------------------------------------------------------------------
// RenderPanel: displays the last-rendered frame (a plain BGRA8 pixel
// buffer read back from the hidden GL surface), fit to the panel by
// default, adjustable with the mouse wheel (zoom, centered on the
// cursor) and left-drag (pan). Resizing the panel refits the image.
// ---------------------------------------------------------------------------
class RenderPanel : public wxPanel {
public:
    explicit RenderPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) {
        static bool classRegistered = false;
        if (!classRegistered) {
            WNDCLASSA wc{};
            wc.style = CS_OWNDC; // private DC keeps the pixel format across resizes
            wc.lpfnWndProc = DefWindowProc;
            wc.hInstance = GetModuleHandle(nullptr);
            wc.lpszClassName = "GLReplaySurface";
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            RegisterClassA(&wc);
            classRegistered = true;
        }
        // Hidden (no WS_VISIBLE): only used off-screen for GL rendering; its
        // frames are read back into m_pixels and drawn by OnPaint instead,
        // so nothing about displaying/zooming/panning ever touches it.
        m_glSurfaceHwnd = CreateWindowA("GLReplaySurface", "", WS_CHILD,
                                         0, 0, kDefaultGLContentW, kDefaultGLContentH,
                                         static_cast<HWND>(GetHandle()), nullptr, GetModuleHandle(nullptr), nullptr);
        m_contentW = kDefaultGLContentW;
        m_contentH = kDefaultGLContentH;

        Bind(wxEVT_PAINT, &RenderPanel::OnPaint, this);
        Bind(wxEVT_SIZE, &RenderPanel::OnSize, this);
        Bind(wxEVT_MOUSEWHEEL, &RenderPanel::OnMouseWheel, this);
        Bind(wxEVT_LEFT_DOWN, &RenderPanel::OnLeftDown, this);
        Bind(wxEVT_LEFT_UP, &RenderPanel::OnLeftUp, this);
        Bind(wxEVT_MOTION, &RenderPanel::OnMouseMove, this);
        Bind(wxEVT_RIGHT_DOWN, &RenderPanel::OnRightDown, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {}); // OnPaint always fully repaints
    }

    HWND GetGLSurfaceHwnd() const { return m_glSurfaceHwnd; }

    // Resizes the hidden GL surface to match the captured content's real
    // size (from GL_VIEWPORT) and refits the display.
    void SetContentSize(int w, int h) {
        if (w == m_contentW && h == m_contentH) return;
        m_contentW = w;
        m_contentH = h;
        MoveWindow(m_glSurfaceHwnd, 0, 0, w, h, TRUE);
        ResetView();
        Refresh();
    }

    void SetPixels(std::vector<uint8_t> pixels) {
        m_pixels = std::move(pixels);
        Refresh(false);
    }

private:
    void ResetView() {
        wxSize sz = GetClientSize();
        int availW = sz.GetWidth(), availH = sz.GetHeight();
        if (m_contentW <= 0 || m_contentH <= 0 || availW <= 0 || availH <= 0) {
            m_zoom = 1.0;
            m_panX = m_panY = 0;
            return;
        }
        m_zoom = (availW / static_cast<double>(m_contentW) < availH / static_cast<double>(m_contentH))
                     ? availW / static_cast<double>(m_contentW)
                     : availH / static_cast<double>(m_contentH);
        int dispW = static_cast<int>(m_contentW * m_zoom);
        int dispH = static_cast<int>(m_contentH * m_zoom);
        m_panX = (availW - dispW) / 2;
        m_panY = (availH - dispH) / 2;
    }

    void ZoomAt(int x, int y, double factor) {
        double oldZoom = m_zoom;
        double newZoom = oldZoom * factor;
        if (newZoom < 0.05) newZoom = 0.05;
        if (newZoom > 40.0) newZoom = 40.0;
        double texelX = (x - m_panX) / oldZoom;
        double texelY = (y - m_panY) / oldZoom;
        m_panX = static_cast<int>(x - texelX * newZoom);
        m_panY = static_cast<int>(y - texelY * newZoom);
        m_zoom = newZoom;
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        wxSize sz = GetClientSize();
        dc.SetBackground(wxBrush(wxColour(160, 160, 164)));
        dc.Clear();
        if (m_pixels.empty()) return;
        HDC hdc = static_cast<HDC>(dc.GetHDC());
        if (!hdc) return;
        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = m_contentW;
        bmi.bmiHeader.biHeight = m_contentH; // positive: bottom-up, matches how we read it back
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        int dispW = static_cast<int>(m_contentW * m_zoom);
        int dispH = static_cast<int>(m_contentH * m_zoom);
        StretchDIBits(hdc, m_panX, m_panY, dispW, dispH, 0, 0, m_contentW, m_contentH,
                       m_pixels.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);
    }

    void OnSize(wxSizeEvent& event) {
        ResetView();
        Refresh();
        event.Skip();
    }

    void OnMouseWheel(wxMouseEvent& event) {
        double factor = (event.GetWheelRotation() > 0) ? 1.1 : (1.0 / 1.1);
        ZoomAt(event.GetX(), event.GetY(), factor);
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

    void OnMouseMove(wxMouseEvent& event) {
        if (m_dragging && event.Dragging() && event.LeftIsDown()) {
            m_panX = m_dragPanStartX + (event.GetX() - m_dragStart.x);
            m_panY = m_dragPanStartY + (event.GetY() - m_dragStart.y);
            Refresh(false);
        }
    }

    // Right-click: show the image at its native (1:1) pixel size, keeping
    // whatever texel is currently under the cursor fixed in place -- the
    // same "zoom around a point" math the wheel uses, just jumping
    // straight to a 1.0 target instead of stepping by a factor.
    void OnRightDown(wxMouseEvent& event) {
        if (m_zoom > 0) ZoomAt(event.GetX(), event.GetY(), 1.0 / m_zoom);
        Refresh();
    }

    HWND m_glSurfaceHwnd = nullptr;
    int m_contentW = 0, m_contentH = 0;
    std::vector<uint8_t> m_pixels; // BGRA8, bottom-up

    double m_zoom = 1.0;
    int m_panX = 0, m_panY = 0;
    bool m_dragging = false;
    wxPoint m_dragStart;
    int m_dragPanStartX = 0, m_dragPanStartY = 0;
};

// ---------------------------------------------------------------------------
// AttachmentPanel: docked, always-live view of one framebuffer
// attachment (color, or depth/stencil) -- the embedded counterpart to
// the floating texture viewer (texture_view.*), showing whatever's
// currently read back into it via SetImage() with the same zoom (mouse
// wheel, centered on the cursor)/pan (left-drag) support and a
// per-pixel hover readout in a status line at the bottom. Resizing
// refits; a new SetImage() with different dimensions refits too (same
// "resize refits, new content doesn't fight your zoom" rule as the
// floating viewer, just triggered by dimension changes since this one
// updates continuously rather than on open).
// ---------------------------------------------------------------------------
class AttachmentPanel : public wxPanel {
public:
    explicit AttachmentPanel(wxWindow* parent) : wxPanel(parent) {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_canvas = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
        m_status = new wxStaticText(this, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 22));
        sizer->Add(m_canvas, 1, wxEXPAND);
        sizer->Add(m_status, 0, wxEXPAND | wxALL, 3);
        SetSizer(sizer);

        m_canvas->Bind(wxEVT_PAINT, &AttachmentPanel::OnPaint, this);
        m_canvas->Bind(wxEVT_SIZE, &AttachmentPanel::OnSize, this);
        m_canvas->Bind(wxEVT_MOUSEWHEEL, &AttachmentPanel::OnMouseWheel, this);
        m_canvas->Bind(wxEVT_LEFT_DOWN, &AttachmentPanel::OnLeftDown, this);
        m_canvas->Bind(wxEVT_LEFT_UP, &AttachmentPanel::OnLeftUp, this);
        m_canvas->Bind(wxEVT_MOTION, &AttachmentPanel::OnMouseMove, this);
        m_canvas->Bind(wxEVT_RIGHT_DOWN, &AttachmentPanel::OnRightDown, this);
        m_canvas->Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    }

    void SetImage(AttachmentKind kind, int w, int h, std::vector<unsigned char> displayPixels,
                  std::vector<unsigned char> colorRaw, std::vector<float> depthRaw, std::vector<unsigned char> stencilRaw) {
        bool sizeChanged = (w != m_texW || h != m_texH);
        m_kind = kind;
        m_texW = w;
        m_texH = h;
        m_displayPixels = std::move(displayPixels);
        m_colorRaw = std::move(colorRaw);
        m_depthRaw = std::move(depthRaw);
        m_stencilRaw = std::move(stencilRaw);
        m_hasImage = true;
        if (sizeChanged) ResetView();
        m_canvas->Refresh();
    }

    // No source for this attachment right now (e.g. an FBO with no
    // depth attachment) -- show the panel empty rather than stale.
    void Clear() {
        m_hasImage = false;
        m_displayPixels.clear();
        m_canvas->Refresh();
        m_status->SetLabel("");
    }

private:
    void ResetView() {
        wxSize sz = m_canvas->GetClientSize();
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

    void ZoomAt(int x, int y, double factor) {
        double oldZoom = m_zoom;
        double newZoom = oldZoom * factor;
        if (newZoom < 0.05) newZoom = 0.05;
        if (newZoom > 40.0) newZoom = 40.0;
        double texelX = (x - m_panX) / oldZoom;
        double texelY = (y - m_panY) / oldZoom;
        m_panX = static_cast<int>(x - texelX * newZoom);
        m_panY = static_cast<int>(y - texelY * newZoom);
        m_zoom = newZoom;
    }

    void UpdateStatusForPoint(int clientX, int clientY) {
        if (!m_hasImage || m_texW <= 0 || m_texH <= 0 || m_zoom <= 0) {
            m_status->SetLabel("");
            return;
        }
        double texXf = (clientX - m_panX) / m_zoom;
        double texYFromTopF = (clientY - m_panY) / m_zoom;
        if (texXf < 0 || texYFromTopF < 0 || texXf >= m_texW || texYFromTopF >= m_texH) {
            m_status->SetLabel("");
            return;
        }
        int texX = static_cast<int>(texXf);
        int texYFromTop = static_cast<int>(texYFromTopF);
        int bufRow = m_texH - 1 - texYFromTop; // bottom-up, like GL itself
        size_t idx = static_cast<size_t>(bufRow) * m_texW + texX;

        char buf[128];
        if (m_kind == AttachmentKind::Color && idx * 4 + 3 < m_colorRaw.size()) {
            const unsigned char* p = &m_colorRaw[idx * 4];
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  R=%d  G=%d  B=%d  A=%d   [zoom %.0f%%]",
                     texX, texYFromTop, p[2], p[1], p[0], p[3], m_zoom * 100.0);
        } else if (m_kind == AttachmentKind::DepthStencil && idx < m_depthRaw.size() && idx < m_stencilRaw.size()) {
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  depth=%.6f  stencil=%u   [zoom %.0f%%]",
                     texX, texYFromTop, m_depthRaw[idx], m_stencilRaw[idx], m_zoom * 100.0);
        } else if (m_kind == AttachmentKind::Depth && idx < m_depthRaw.size()) {
            snprintf(buf, sizeof(buf), "pixel (%d, %d):  depth=%.6f   [zoom %.0f%%]", texX, texYFromTop, m_depthRaw[idx], m_zoom * 100.0);
        } else {
            m_status->SetLabel("");
            return;
        }
        m_status->SetLabel(wxString(buf));
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(m_canvas);
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
        ResetView();
        m_canvas->Refresh();
        event.Skip();
    }

    void OnMouseWheel(wxMouseEvent& event) {
        double factor = (event.GetWheelRotation() > 0) ? 1.1 : (1.0 / 1.1);
        ZoomAt(event.GetX(), event.GetY(), factor);
        UpdateStatusForPoint(event.GetX(), event.GetY());
        m_canvas->Refresh();
    }

    void OnLeftDown(wxMouseEvent& event) {
        m_dragging = true;
        m_dragStart = event.GetPosition();
        m_dragPanStartX = m_panX;
        m_dragPanStartY = m_panY;
        m_canvas->CaptureMouse();
    }

    void OnLeftUp(wxMouseEvent&) {
        m_dragging = false;
        if (m_canvas->HasCapture()) m_canvas->ReleaseMouse();
    }

    void OnMouseMove(wxMouseEvent& event) {
        if (m_dragging && event.LeftIsDown()) {
            m_panX = m_dragPanStartX + (event.GetX() - m_dragStart.x);
            m_panY = m_dragPanStartY + (event.GetY() - m_dragStart.y);
            m_canvas->Refresh(false);
        }
        UpdateStatusForPoint(event.GetX(), event.GetY());
    }

    // Right-click resets zoom/pan back to the fit-and-centered default
    // view, the same one shown when this attachment's size last changed.
    void OnRightDown(wxMouseEvent& event) {
        ResetView();
        UpdateStatusForPoint(event.GetX(), event.GetY());
        m_canvas->Refresh();
    }

    wxPanel* m_canvas = nullptr;
    wxStaticText* m_status = nullptr;

    bool m_hasImage = false;
    AttachmentKind m_kind = AttachmentKind::Color;
    int m_texW = 0, m_texH = 0;
    std::vector<unsigned char> m_displayPixels;
    std::vector<unsigned char> m_colorRaw;
    std::vector<float> m_depthRaw;
    std::vector<unsigned char> m_stencilRaw;

    double m_zoom = 1.0;
    int m_panX = 0, m_panY = 0;
    bool m_dragging = false;
    wxPoint m_dragStart;
    int m_dragPanStartX = 0, m_dragPanStartY = 0;
};

// ---------------------------------------------------------------------------
// CallListGutter: a thin strip to the left of the call-list box that
// draws a green arrow next to whichever line was most recently run to
// (see CallListPanel::SetMarkerLine). Kept in sync with the listbox's
// scroll position via a periodic timer (see CallListPanel) rather than
// a scroll notification, since a native listbox's internal scrolling
// doesn't raise one wx can hook.
// ---------------------------------------------------------------------------
class CallListGutter : public wxPanel {
public:
    explicit CallListGutter(wxWindow* parent)
        : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(16, -1)) {
        Bind(wxEVT_PAINT, &CallListGutter::OnPaint, this);
        Bind(wxEVT_ERASE_BACKGROUND, [](wxEraseEvent&) {});
    }

    void SetListBox(wxListBox* listBox) { m_listBox = listBox; }

    void SetMarkerLine(int line) {
        if (line == m_markerLine) return;
        m_markerLine = line;
        Refresh();
    }

    void SetFrameStartLines(std::vector<int> lines) {
        m_frameStartLines = std::move(lines);
        Refresh();
    }

    void SetFrameEndLines(std::vector<int> lines) {
        m_frameEndLines = std::move(lines);
        Refresh();
    }

    void SetSearchMatches(std::vector<int> lines, int selectedLine) {
        m_searchMatchLines = std::move(lines);
        m_selectedSearchLine = selectedLine;
        Refresh();
    }

private:
    template <typename DrawFn>
    void DrawVisibleLines(int topIndex, int bottomIndexInclusive, const std::vector<int>& lines, DrawFn&& drawFn) {
        auto it = std::lower_bound(lines.begin(), lines.end(), topIndex);
        for (; it != lines.end() && *it <= bottomIndexInclusive; ++it) drawFn(*it);
    }

    void DrawFrameBand(wxPaintDC& dc, int topIndex, int itemHeight, int line, const wxColour& color) {
        const int y = (line - topIndex) * itemHeight;
        wxSize sz = GetClientSize();
        if (y + itemHeight < 0 || y > sz.GetHeight()) return;
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.SetBrush(wxBrush(color));
        dc.DrawRectangle(0, y, sz.GetWidth(), itemHeight);
    }

    void DrawArrow(wxPaintDC& dc, int topIndex, int itemHeight, int line, const wxColour& fill, const wxColour& edge) {
        const int y = (line - topIndex) * itemHeight;
        wxSize sz = GetClientSize();
        if (y + itemHeight < 0 || y > sz.GetHeight()) return;
        dc.SetBrush(wxBrush(fill));
        dc.SetPen(wxPen(edge));
        wxPoint pts[3] = {
            wxPoint(2, y + 2),
            wxPoint(2, y + itemHeight - 2),
            wxPoint(sz.GetWidth() - 2, y + itemHeight / 2),
        };
        dc.DrawPolygon(3, pts);
    }

    void OnPaint(wxPaintEvent&) {
        wxPaintDC dc(this);
        dc.SetBackground(*wxWHITE_BRUSH);
        dc.Clear();
        if (!m_listBox) return;

        HWND hwnd = static_cast<HWND>(m_listBox->GetHandle());
        int itemHeight = static_cast<int>(::SendMessageA(hwnd, LB_GETITEMHEIGHT, 0, 0));
        int topIndex = static_cast<int>(::SendMessageA(hwnd, LB_GETTOPINDEX, 0, 0));
        if (itemHeight <= 0) return;
        wxSize sz = GetClientSize();
        int bottomIndexInclusive = topIndex + (sz.GetHeight() / itemHeight) + 1;

        DrawVisibleLines(topIndex, bottomIndexInclusive, m_frameStartLines, [&](int line) {
            DrawFrameBand(dc, topIndex, itemHeight, line, wxColour(180, 225, 255));
        });
        DrawVisibleLines(topIndex, bottomIndexInclusive, m_frameEndLines, [&](int line) {
            DrawFrameBand(dc, topIndex, itemHeight, line, wxColour(255, 214, 170));
        });
        DrawVisibleLines(topIndex, bottomIndexInclusive, m_searchMatchLines, [&](int line) {
            if (line == m_selectedSearchLine) return;
            DrawArrow(dc, topIndex, itemHeight, line, wxColour(214, 170, 0), wxColour(156, 118, 0)); // dark yellow arrow
        });
        if (m_selectedSearchLine >= 0) {
            DrawArrow(dc, topIndex, itemHeight, m_selectedSearchLine, wxColour(76, 154, 255), wxColour(35, 102, 190)); // blue arrow
        }

        if (m_markerLine < 0) return;

        DrawArrow(dc, topIndex, itemHeight, m_markerLine, wxColour(0, 170, 0), wxColour(0, 120, 0)); // run-to marker
    }

    wxListBox* m_listBox = nullptr;
    int m_markerLine = -1;
    std::vector<int> m_frameStartLines;
    std::vector<int> m_frameEndLines;
    std::vector<int> m_searchMatchLines;
    int m_selectedSearchLine = -1;
};

// ---------------------------------------------------------------------------
// CallListPanel: the call-list box plus a search bar above it (Enter, the
// Search button, or the Next/Previous buttons on the row below it jump to
// the next/previous line containing the search text, wrapping around) and
// the green "last run to here" marker gutter to its left.
// ---------------------------------------------------------------------------
class CallListPanel : public wxPanel {
public:
    explicit CallListPanel(wxWindow* parent) : wxPanel(parent) {
        wxBoxSizer* outer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* searchRow = new wxBoxSizer(wxHORIZONTAL);
        m_searchCtrl = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
        m_searchCtrl->SetHint("Search call list...");
        wxButton* searchBtn = new wxButton(this, wxID_ANY, "Search", wxDefaultPosition, wxSize(70, -1));
        searchRow->Add(m_searchCtrl, 1, wxALIGN_CENTER_VERTICAL | wxRIGHT, 4);
        searchRow->Add(searchBtn, 0, wxALIGN_CENTER_VERTICAL);
        outer->Add(searchRow, 0, wxEXPAND | wxBOTTOM, 3);

        wxBoxSizer* navRow = new wxBoxSizer(wxHORIZONTAL);
        wxButton* prevBtn = new wxButton(this, wxID_ANY, "Previous", wxDefaultPosition, wxSize(70, -1));
        wxButton* nextBtn = new wxButton(this, wxID_ANY, "Next", wxDefaultPosition, wxSize(70, -1));
        navRow->Add(prevBtn, 0, wxRIGHT, 4);
        navRow->Add(nextBtn, 0);
        outer->Add(navRow, 0, wxEXPAND | wxBOTTOM, 3);

        wxBoxSizer* listRow = new wxBoxSizer(wxHORIZONTAL);
        m_gutter = new CallListGutter(this);
        m_listBox = new wxListBox(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, nullptr, wxLB_HSCROLL);
        listRow->Add(m_gutter, 0, wxEXPAND);
        listRow->Add(m_listBox, 1, wxEXPAND);
        outer->Add(listRow, 1, wxEXPAND);

        SetSizer(outer);
        m_gutter->SetListBox(m_listBox);

        searchBtn->Bind(wxEVT_BUTTON, &CallListPanel::OnSearchNext, this);
        m_searchCtrl->Bind(wxEVT_TEXT_ENTER, &CallListPanel::OnSearchNext, this);
        m_searchCtrl->Bind(wxEVT_TEXT, &CallListPanel::OnSearchText, this);
        nextBtn->Bind(wxEVT_BUTTON, &CallListPanel::OnSearchNext, this);
        prevBtn->Bind(wxEVT_BUTTON, &CallListPanel::OnSearchPrev, this);
        m_listBox->Bind(wxEVT_LISTBOX, &CallListPanel::OnSelectionChanged, this);

        // The gutter's arrow position depends on the listbox's current
        // scroll offset, which changes with no wx-level notification --
        // just repaint it regularly rather than trying to hook the
        // native control's internal scroll handling.
        m_syncTimer.Bind(wxEVT_TIMER, &CallListPanel::OnSyncTimer, this);
        m_syncTimer.Start(150);
    }

    wxListBox* GetListBox() const { return m_listBox; }
    void SetMarkerLine(int line) { m_gutter->SetMarkerLine(line); }
    void SetFrameLines(const std::vector<int>& frameStarts, const std::vector<int>& frameEnds) {
        m_gutter->SetFrameStartLines(frameStarts);
        m_gutter->SetFrameEndLines(frameEnds);
    }
    void RebuildSearchIndex() {
        m_searchCorpusLower.clear();
        int count = static_cast<int>(m_listBox->GetCount());
        m_searchCorpusLower.reserve(static_cast<size_t>(count));
        for (int i = 0; i < count; ++i) m_searchCorpusLower.push_back(m_listBox->GetString(i).Lower());
    }

private:
    void EnsureSearchIndex() {
        if (m_searchCorpusLower.size() != static_cast<size_t>(m_listBox->GetCount())) RebuildSearchIndex();
    }

    void RebuildSearchMatches() {
        m_searchMatches.clear();
        wxString needle = m_searchCtrl->GetValue().Lower();
        if (needle.IsEmpty()) return;
        EnsureSearchIndex();
        int count = static_cast<int>(m_searchCorpusLower.size());
        for (int i = 0; i < count; ++i) {
            if (m_searchCorpusLower[static_cast<size_t>(i)].Contains(needle)) m_searchMatches.push_back(i);
        }
    }

    void SyncSearchHighlights() {
        int sel = m_listBox->GetSelection();
        m_gutter->SetSearchMatches(m_searchMatches, sel);
    }

    // direction: +1 for the next match, -1 for the previous one, wrapping
    // around the list either way.
    void Find(int direction) {
        wxString needle = m_searchCtrl->GetValue();
        if (needle.IsEmpty()) return;
        int count = static_cast<int>(m_listBox->GetCount());
        if (count == 0) return;
        RebuildSearchMatches();
        if (m_searchMatches.empty()) {
            wxBell(); // no match anywhere in the list
            SyncSearchHighlights();
            return;
        }

        int start = m_listBox->GetSelection();
        if (start == wxNOT_FOUND) start = (direction > 0) ? -1 : count;

        int idx = -1;
        if (direction > 0) {
            auto it = std::upper_bound(m_searchMatches.begin(), m_searchMatches.end(), start);
            if (it == m_searchMatches.end()) it = m_searchMatches.begin();
            idx = *it;
        } else {
            auto it = std::lower_bound(m_searchMatches.begin(), m_searchMatches.end(), start);
            if (it == m_searchMatches.begin()) {
                idx = m_searchMatches.back();
            } else {
                --it;
                idx = *it;
            }
        }

        m_listBox->SetSelection(idx);
        m_listBox->EnsureVisible(idx);
        SyncSearchHighlights();
    }

    void OnSearchNext(wxCommandEvent&) { Find(1); }
    void OnSearchPrev(wxCommandEvent&) { Find(-1); }
    void OnSearchText(wxCommandEvent&) {
        RebuildSearchMatches();
        SyncSearchHighlights();
    }
    void OnSelectionChanged(wxCommandEvent& event) {
        SyncSearchHighlights();
        event.Skip();
    }

    void OnSyncTimer(wxTimerEvent&) { m_gutter->Refresh(); }

    wxTextCtrl* m_searchCtrl = nullptr;
    wxListBox* m_listBox = nullptr;
    CallListGutter* m_gutter = nullptr;
    std::vector<int> m_searchMatches;
    std::vector<wxString> m_searchCorpusLower;
    wxTimer m_syncTimer;
};

// ---------------------------------------------------------------------------
// DropIndicator: a translucent blue overlay shown during a panel drag,
// positioned/sized to preview exactly what dropping right now would do
// -- the whole target panel's rect for a swap, or just its top/bottom
// half when the drop would split it. A single instance is reused for
// the whole app's lifetime (see PanelContainer::GetIndicator).
// ---------------------------------------------------------------------------
class DropIndicator : public wxFrame {
public:
    DropIndicator()
        : wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
                   wxFRAME_TOOL_WINDOW | wxFRAME_NO_TASKBAR | wxSTAY_ON_TOP | wxBORDER_NONE) {
        SetBackgroundColour(wxColour(40, 120, 220));
        SetTransparent(110);
    }

    void ShowAt(const wxRect& screenRect) {
        SetSize(screenRect);
        if (!IsShown()) Show();
        Raise();
    }

    void HideIt() {
        if (IsShown()) Hide();
    }
};

class PanelContainer; // fwd decl -- ColumnSplitter only ever holds pointers to it

// ---------------------------------------------------------------------------
// ColumnSplitter: one of the three top-level vertical panels. Splits
// horizontally into an (always-present, possibly hidden) top and bottom
// slot, so a panel can hold either one sub-window spanning the whole
// column or two sub-windows sharing its upper/lower halves. Starts
// unsplit (Initialize()'d with just topSlot); PanelContainer's drop
// logic calls SplitHorizontally()/Unsplit() on it as panels move in and
// out of the bottom half.
// ---------------------------------------------------------------------------
class ColumnSplitter : public wxSplitterWindow {
public:
    explicit ColumnSplitter(wxWindow* parent)
        : wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE | wxSP_3D) {
        SetSashGravity(0.5);
        SetMinimumPaneSize(40);
    }

    PanelContainer* topSlot = nullptr;
    PanelContainer* bottomSlot = nullptr;
};

// ---------------------------------------------------------------------------
// PanelContainer: a label strip above a content window -- one slot (top,
// bottom, or a whole unsplit column) of a ColumnSplitter. Dragging a
// label and dropping it:
//   - in the middle of another (occupied) slot swaps their contents;
//   - onto the empty half of a column simply moves the dragged content
//     there;
//   - near the top/bottom edge of a slot that's currently a *whole*,
//     unsplit column splits that column, giving the dragged content the
//     near half and pushing what was there into the other half.
// Whenever a slot's content is removed and its column is split, that
// column auto-unsplits so the remaining sub-window fills the whole
// panel again -- "full panel or upper/lower part" is a direct
// consequence of the column's split state, not something tracked
// separately.
// ---------------------------------------------------------------------------
class PanelContainer : public wxPanel {
public:
    explicit PanelContainer(wxWindow* parent) : wxPanel(parent), m_identity(PANEL_EMPTY) {
        s_all.push_back(this);
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        m_label = new wxStaticText(this, wxID_ANY, LabelForIdentity(PANEL_EMPTY), wxDefaultPosition, wxDefaultSize,
                                    wxST_NO_AUTORESIZE | wxALIGN_LEFT);
        m_label->SetBackgroundColour(wxColour(240, 240, 240));
        wxFont f = m_label->GetFont();
        f.SetWeight(wxFONTWEIGHT_BOLD);
        m_label->SetFont(f);
        sizer->Add(m_label, 0, wxEXPAND | wxALL, 3);
        SetSizer(sizer);

        m_label->SetCursor(wxCursor(wxCURSOR_HAND));
        m_label->Bind(wxEVT_LEFT_DOWN, &PanelContainer::OnLabelLeftDown, this);
        m_label->Bind(wxEVT_LEFT_UP, &PanelContainer::OnLabelLeftUp, this);
        m_label->Bind(wxEVT_MOTION, &PanelContainer::OnLabelMotion, this);
        // Defensive cleanup if capture is yanked away mid-drag (e.g.
        // Alt+Tab) instead of a normal mouse-up -- otherwise the drop
        // indicator/highlight would stay stuck on screen forever.
        m_label->Bind(wxEVT_MOUSE_CAPTURE_LOST, &PanelContainer::OnLabelCaptureLost, this);
    }

    ~PanelContainer() {
        s_all.erase(std::remove(s_all.begin(), s_all.end(), this), s_all.end());
    }

    // Assigns this slot's content/identity directly, detaching/reparenting
    // as needed. Used both for the initial one-time content assignment and
    // as the low-level primitive the drag-and-drop logic below builds on;
    // it never touches any ColumnSplitter's split state itself.
    //
    // `content` may currently belong to a *different* container's sizer
    // (moves/swaps between containers are just two Assign() calls) -- wx
    // asserts if Add() sees a window still registered with another sizer,
    // so this detaches it from wherever it actually is, not just from
    // this container's own sizer.
    void Assign(wxWindow* content, int identity) {
        if (m_content) GetSizer()->Detach(m_content);
        m_content = content;
        m_identity = identity;
        m_label->SetLabel(LabelForIdentity(identity));
        if (content) {
            wxSizer* oldSizer = content->GetContainingSizer();
            if (oldSizer && oldSizer != GetSizer()) oldSizer->Detach(content);
            content->Reparent(this);
            content->Show(true);
            GetSizer()->Add(content, 1, wxEXPAND | wxALL, 2);
        }
        Layout();
    }

    wxWindow* GetContent() const { return m_content; }
    int GetIdentity() const { return m_identity; }

    void SetHighlighted(bool on) {
        m_label->SetBackgroundColour(on ? wxColour(173, 216, 230) : wxColour(240, 240, 240));
        m_label->Refresh();
    }

private:
    enum class DropZone { Swap, InsertTop, InsertBottom };

    static PanelContainer* HitTest(const wxPoint& screenPt) {
        for (PanelContainer* c : s_all) {
            if (c->IsShown() && c->GetScreenRect().Contains(screenPt)) return c;
        }
        return nullptr;
    }

    // Same zone logic PerformDrop acts on, factored out so the drag
    // preview (UpdateDropIndicator) shows exactly what a drop right now
    // would actually do.
    static DropZone ComputeZone(PanelContainer* dst, const wxPoint& screenPt) {
        auto* dstCol = dynamic_cast<ColumnSplitter*>(dst->GetParent());
        if (!dstCol || dstCol->IsSplit()) return DropZone::Swap;
        wxRect r = dst->GetScreenRect();
        double frac = (r.GetHeight() > 0) ? static_cast<double>(screenPt.y - r.GetTop()) / r.GetHeight() : 0.5;
        if (frac < 0.3) return DropZone::InsertTop;
        if (frac > 0.7) return DropZone::InsertBottom;
        return DropZone::Swap;
    }

    static DropIndicator* GetIndicator() {
        static DropIndicator* indicator = new DropIndicator();
        return indicator;
    }

    static void UpdateDropIndicator(PanelContainer* target, DropZone zone) {
        wxRect r = target->GetScreenRect();
        if (zone == DropZone::InsertTop) {
            r.SetHeight(r.GetHeight() / 2);
        } else if (zone == DropZone::InsertBottom) {
            int h = r.GetHeight() - r.GetHeight() / 2;
            r.SetTop(r.GetTop() + r.GetHeight() / 2);
            r.SetHeight(h);
        }
        GetIndicator()->ShowAt(r);
    }

    static void HideDropIndicator() { GetIndicator()->HideIt(); }

    // If `container` just lost its content and its column is split,
    // collapse that column so the remaining sibling fills the whole
    // panel -- the "give it back the full panel" half of the rule.
    static void AutoUnsplitIfNeeded(PanelContainer* container) {
        auto* col = dynamic_cast<ColumnSplitter*>(container->GetParent());
        if (!col || !col->IsSplit() || container->m_content) return;
        col->Unsplit(container);
    }

    static void PerformDrop(PanelContainer* src, PanelContainer* dst, const wxPoint& screenPt) {
        wxWindow* srcContent = src->m_content;
        int srcIdentity = src->m_identity;
        if (!srcContent) return; // dragging an empty slot's label does nothing

        if (!dst->m_content) {
            // Empty destination: just move it there, no split involved.
            dst->Assign(srcContent, srcIdentity);
            src->Assign(nullptr, PANEL_EMPTY);
            AutoUnsplitIfNeeded(src);
            return;
        }

        auto* dstCol = dynamic_cast<ColumnSplitter*>(dst->GetParent());
        DropZone zone = ComputeZone(dst, screenPt);

        if (zone == DropZone::Swap) {
            wxWindow* dstContent = dst->m_content;
            int dstIdentity = dst->m_identity;
            dst->Assign(srcContent, srcIdentity);
            src->Assign(dstContent, dstIdentity);
            return; // occupancy is unchanged on both sides -- no split/unsplit to do
        }

        // Insert near an edge of a whole (unsplit) column: split it,
        // keeping its current content and giving the dragged content the
        // near half.
        PanelContainer* top = dstCol->topSlot;
        PanelContainer* bottom = dstCol->bottomSlot;
        wxWindow* existingContent = dst->m_content;
        int existingIdentity = dst->m_identity;
        if (zone == DropZone::InsertTop) {
            top->Assign(srcContent, srcIdentity);
            bottom->Assign(existingContent, existingIdentity);
        } else {
            bottom->Assign(srcContent, srcIdentity);
            top->Assign(existingContent, existingIdentity);
        }
        top->Show(true);
        bottom->Show(true);
        dstCol->SplitHorizontally(top, bottom);
        dstCol->SetSashGravity(0.5);

        src->Assign(nullptr, PANEL_EMPTY);
        AutoUnsplitIfNeeded(src);
    }

    void OnLabelLeftDown(wxMouseEvent&) {
        if (!m_content) return; // nothing to drag
        s_dragSource = this;
        s_dropTarget = nullptr;
        m_label->CaptureMouse();
    }

    void OnLabelMotion(wxMouseEvent& event) {
        if (s_dragSource != this || !m_label->HasCapture()) return;
        wxPoint screenPt = m_label->ClientToScreen(event.GetPosition());
        PanelContainer* hover = HitTest(screenPt);
        if (hover == this) hover = nullptr;
        DropZone zone = hover ? ComputeZone(hover, screenPt) : DropZone::Swap;
        if (hover != s_dropTarget || zone != s_dropZone) {
            if (s_dropTarget) s_dropTarget->SetHighlighted(false);
            s_dropTarget = hover;
            s_dropZone = zone;
            if (s_dropTarget) {
                s_dropTarget->SetHighlighted(true);
                // Empty targets have no meaningful "insert" sub-zone --
                // dropping anywhere on one just moves the panel there, so
                // preview the whole slot regardless of cursor position.
                UpdateDropIndicator(s_dropTarget, s_dropTarget->m_content ? zone : DropZone::Swap);
            } else {
                HideDropIndicator();
            }
        }
    }

    void OnLabelLeftUp(wxMouseEvent& event) {
        if (s_dragSource != this) return;
        if (m_label->HasCapture()) m_label->ReleaseMouse();
        wxPoint screenPt = m_label->ClientToScreen(event.GetPosition());
        PanelContainer* drop = HitTest(screenPt);
        if (s_dropTarget) s_dropTarget->SetHighlighted(false);
        HideDropIndicator();
        if (drop && drop != this) PerformDrop(this, drop, screenPt);
        s_dragSource = nullptr;
        s_dropTarget = nullptr;
    }

    void OnLabelCaptureLost(wxMouseCaptureLostEvent&) {
        if (s_dragSource != this) return;
        if (s_dropTarget) s_dropTarget->SetHighlighted(false);
        HideDropIndicator();
        s_dragSource = nullptr;
        s_dropTarget = nullptr;
    }

    wxStaticText* m_label = nullptr;
    wxWindow* m_content = nullptr;
    int m_identity;

    static std::vector<PanelContainer*> s_all;
    static PanelContainer* s_dragSource;
    static PanelContainer* s_dropTarget;
    static DropZone s_dropZone;
};

std::vector<PanelContainer*> PanelContainer::s_all;
PanelContainer* PanelContainer::s_dragSource = nullptr;
PanelContainer* PanelContainer::s_dropTarget = nullptr;
PanelContainer::DropZone PanelContainer::s_dropZone = PanelContainer::DropZone::Swap;

// ---------------------------------------------------------------------------
// ReplayFrame: the whole tool's one window.
// ---------------------------------------------------------------------------
class ReplayFrame : public wxFrame {
public:
    ReplayFrame() : wxFrame(nullptr, wxID_ANY, "gl_capture replay", wxDefaultPosition, wxSize(1600, 900)) {
        wxSplitterWindow* outer = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                                         wxSP_LIVE_UPDATE | wxSP_3D);
        wxSplitterWindow* inner = new wxSplitterWindow(outer, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                                         wxSP_LIVE_UPDATE | wxSP_3D);

        // Default left-to-right order: call list (whole column); color and
        // depth/stencil attachment views sharing the middle column;
        // render and resources & state sharing the right column. Every
        // column gets both slots created up front (even the ones that
        // start out unsplit) so dragging a panel to the upper/lower half
        // of any column later just means splitting it and showing its
        // (already-existing) other slot -- see PanelContainer's drag.
        ColumnSplitter* col0 = new ColumnSplitter(outer);
        ColumnSplitter* col1 = new ColumnSplitter(inner);
        ColumnSplitter* col2 = new ColumnSplitter(inner);
        for (ColumnSplitter* col : {col0, col1, col2}) {
            col->topSlot = new PanelContainer(col);
            col->bottomSlot = new PanelContainer(col);
            col->bottomSlot->Show(false);
            col->Initialize(col->topSlot); // top/bottom splits happen below, once sizes are real
        }

        m_callListPanel = new CallListPanel(col0->topSlot);
        m_colorAttachmentPanel = new AttachmentPanel(col1->topSlot);
        m_depthAttachmentPanel = new AttachmentPanel(col1->bottomSlot);
        m_renderPanel = new RenderPanel(col2->topSlot);
        m_stateList = new wxListBox(col2->bottomSlot, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                     0, nullptr, wxLB_HSCROLL);
        m_callList = m_callListPanel->GetListBox();

        col0->topSlot->Assign(m_callListPanel, PANEL_CALLLIST);
        col1->topSlot->Assign(m_colorAttachmentPanel, PANEL_COLOR_ATTACHMENT);
        col1->bottomSlot->Assign(m_depthAttachmentPanel, PANEL_DEPTH_ATTACHMENT);
        col2->topSlot->Assign(m_renderPanel, PANEL_RENDER);
        col2->bottomSlot->Assign(m_stateList, PANEL_STATE);

        // wxSplitterWindow's default (sashPosition == 0) placement is half
        // of its OWN current size at Split() time, which -- this early,
        // before the top-level sizer has laid anything out -- can still
        // be the tiny default size rather than the frame's real size.
        // Pass an explicit position (thirds, matching the intended
        // default layout) computed from the size given to the frame's
        // own constructor instead.
        int totalW = GetClientSize().GetWidth();
        if (totalW <= 0) totalW = 1600;
        inner->SplitVertically(col1, col2, (totalW - totalW / 3) / 2);
        outer->SplitVertically(col0, inner, totalW / 3);
        // Gravity controls how the *next* resize (Maximize(), right below)
        // divides new space, not the initial split above. 0.0/0.0 would
        // dump 100% of that growth into inner and then all of that into
        // col2, leaving col0/col1 at their pre-maximize width and col2
        // much wider -- not the equal thirds this is meant to start at.
        // outer's gravity of 1/3 keeps col0 at a third of the total width;
        // inner's gravity of 0.5 splits its own two-thirds evenly between
        // col1 and col2, so growth keeps landing as another equal third
        // in each column.
        outer->SetSashGravity(1.0 / 3.0);
        inner->SetSashGravity(0.5);
        outer->SetMinimumPaneSize(80);
        inner->SetMinimumPaneSize(80);

        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        sizer->Add(outer, 1, wxEXPAND);
        SetSizer(sizer);

        m_callList->Bind(wxEVT_LISTBOX_DCLICK, &ReplayFrame::OnCallListDClick, this);
        m_stateList->Bind(wxEVT_LISTBOX_DCLICK, &ReplayFrame::OnStateListDClick, this);
        Bind(wxEVT_CLOSE_WINDOW, &ReplayFrame::OnClose, this);
        Bind(wxEVT_CHAR_HOOK, &ReplayFrame::OnCharHook, this);

        Maximize(true);
        // col1/col2 (each nested two levels deep, inside "inner" inside
        // "outer") don't have their real on-screen height until the
        // whole splitter tree above them has actually been laid out --
        // Maximize() resizes the frame, but Layout() is what propagates
        // that down through the nested splitters synchronously. Only
        // *then* is GetSize() on col1/col2 themselves meaningful, which
        // is why the top/bottom split within each happens here and not
        // above with the others.
        Layout();
        // Same reasoning as the comment above: Maximize() can land on a
        // real width quite different from whatever GetClientSize() read
        // before layout (window-manager/DPI adjustments, or just that the
        // frame wasn't its final size yet), so the thirds computed further
        // up may no longer be exact. Recompute outer's and inner's sash
        // positions from the real post-maximize/post-layout sizes so the
        // three columns actually start out equal, rather than trusting
        // gravity to have landed on the same answer.
        outer->SetSashPosition(GetClientSize().GetWidth() / 3);
        Layout();
        inner->SetSashPosition(inner->GetClientSize().GetWidth() / 2);
        Layout();
        col1->SetSashGravity(0.5);
        col2->SetSashGravity(0.5);
        col1->SetMinimumPaneSize(40);
        col2->SetMinimumPaneSize(40);
        col1->SplitHorizontally(col1->topSlot, col1->bottomSlot, col1->GetSize().GetHeight() / 2);
        col2->SplitHorizontally(col2->topSlot, col2->bottomSlot, col2->GetSize().GetHeight() / 2);
    }

    ~ReplayFrame() {
        if (m_hglrc) {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(m_hglrc);
        }
    }

    bool SetupGLContext() {
        m_hdc = GetDC(m_renderPanel->GetGLSurfaceHwnd());

        PIXELFORMATDESCRIPTOR pfd{};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;

        int fmt = ChoosePixelFormat(m_hdc, &pfd);
        if (!fmt || !SetPixelFormat(m_hdc, fmt, &pfd)) return false;
        return CreateFreshGLContext();
    }

    bool LoadTrace(const char* path) {
        FILE* f = fopen(path, "rb");
        if (!f) {
            fprintf(stderr, "could not open trace file: %s\n", path);
            return false;
        }
        char magic[8];
        if (fread(magic, 1, sizeof(magic), f) != sizeof(magic) ||
            memcmp(magic, tracefmt::kMagic, sizeof(magic)) != 0) {
            fprintf(stderr, "not a gl_capture trace file\n");
            fclose(f);
            return false;
        }

        // A large trace can contain hundreds of thousands of rows. Reserve
        // the record storage up front and suppress list-box repaints while
        // the rows are being populated; otherwise each append can trigger a
        // native control relayout and repaint.
        if (fseek(f, 0, SEEK_END) == 0) {
            long end = ftell(f);
            if (end > static_cast<long>(sizeof(magic))) {
                constexpr size_t kMinimumRecordBytes = sizeof(tracefmt::RecordHeader);
                m_records.reserve(static_cast<size_t>(end - sizeof(magic)) / kMinimumRecordBytes);
            }
            fseek(f, static_cast<long>(sizeof(magic)), SEEK_SET);
        }
        m_callList->Freeze();
        LRESULT estimatedRows = 0;
        if (fseek(f, 0, SEEK_END) == 0) {
            long end = ftell(f);
            if (end > static_cast<long>(sizeof(magic))) {
                estimatedRows = static_cast<LRESULT>(
                    (static_cast<size_t>(end - sizeof(magic)) / sizeof(tracefmt::RecordHeader)) + 1);
            }
            fseek(f, static_cast<long>(sizeof(magic)), SEEK_SET);
        }
        if (estimatedRows > 0) {
            ::SendMessageA(static_cast<HWND>(m_callList->GetHandle()), LB_INITSTORAGE,
                           static_cast<WPARAM>(estimatedRows), 128);
        }

        size_t frameCount = 0;
        std::vector<int> frameStartLines;
        std::vector<int> frameEndLines;
        int nextFrameStartLine = 0;
        for (;;) {
            tracefmt::RecordHeader hdr;
            if (fread(&hdr, sizeof(hdr), 1, f) != 1) break; // end of trace

            if (hdr.func_id == tracefmt::kFrameEndMarker) {
                m_records.push_back({true, GLFuncId::Count, {}});
                m_callList->Append(wxString::Format("---- frame %zu ----", frameCount++));
                int frameEndLine = static_cast<int>(m_records.size()) - 1;
                frameStartLines.push_back(nextFrameStartLine);
                frameEndLines.push_back(frameEndLine);
                nextFrameStartLine = frameEndLine + 1;
                continue;
            }

            std::vector<uint8_t> data(hdr.data_len);
            if (hdr.data_len && fread(data.data(), 1, hdr.data_len, f) != hdr.data_len) break;

            GLFuncId id = static_cast<GLFuncId>(hdr.func_id);
            std::string line = std::to_string(m_records.size()) + ": " + FormatCall(id, data.data(), data.size());
            m_callList->Append(wxString(line));

            m_records.push_back({false, id, std::move(data)});
        }
        m_callListPanel->SetFrameLines(frameStartLines, frameEndLines);
        m_callListPanel->RebuildSearchIndex();
        m_callList->Thaw();
        fclose(f);
        // Size the hidden surface from the final captured viewport before
        // the first replay. This avoids replaying the entire trace twice
        // just to discover the surface dimensions.
        for (auto it = m_records.rbegin(); it != m_records.rend(); ++it) {
            if (it->isFrameMarker || it->id != GLFuncId::glViewport ||
                it->data.size() < sizeof(GLint) * 4) {
                continue;
            }
            GLint viewport[4]{};
            memcpy(viewport, it->data.data(), sizeof(viewport));
            if (viewport[2] > 0 && viewport[3] > 0) {
                m_contentW = viewport[2];
                m_contentH = viewport[3];
                m_renderPanel->SetContentSize(m_contentW, m_contentH);
            }
            break;
        }
        printf("loaded %zu records across %zu frames\n", m_records.size(), frameCount);
        fflush(stdout);
        return true;
    }

    // GL state can't be rewound, so "running to call N" means starting
    // over with a brand new context (fresh objects, fresh id-remap
    // namespace) and fast-forwarding through every call up to and
    // including N. The hidden GL surface's client-area size doubles as
    // the framebuffer's actual size, so it has to match whatever size
    // the captured calls set via glViewport for the image to render (and
    // read back) correctly; since that's only known once glViewport has
    // actually been replayed, the first run after a (re-)size discovery
    // re-runs once more at the corrected size.
    void RunToIndex(size_t targetIdx) {
        if (m_records.empty()) return;
        if (targetIdx >= m_records.size()) targetIdx = m_records.size() - 1;
        RunOnce(targetIdx);

        GLint vp[4] = {0, 0, 0, 0};
        if (g_inspect.glGetIntegerv) g_inspect.glGetIntegerv(GL_VIEWPORT, vp);
        int w = vp[2] > 0 ? vp[2] : kDefaultGLContentW;
        int h = vp[3] > 0 ? vp[3] : kDefaultGLContentH;
        if (w != m_contentW || h != m_contentH) {
            m_contentW = w;
            m_contentH = h;
            m_renderPanel->SetContentSize(w, h);
            RunOnce(targetIdx); // re-render now that the surface is sized to match
        }

        // Mark where execution actually stopped, once it's done.
        m_callListPanel->SetMarkerLine(static_cast<int>(targetIdx));
    }

private:
    bool CreateFreshGLContext() {
        if (m_hglrc) {
            wglMakeCurrent(nullptr, nullptr);
            wglDeleteContext(m_hglrc);
            m_hglrc = nullptr;
        }
        m_hglrc = wglCreateContext(m_hdc);
        if (!m_hglrc || !wglMakeCurrent(m_hdc, m_hglrc)) return false;
        LoadRealGLFunctions(GetModuleHandleA("opengl32.dll"),
                             [](const char* name) { return (void*)wglGetProcAddress(name); });
        LoadInspectFunctions(GetModuleHandleA("opengl32.dll"),
                              [](const char* name) { return (void*)wglGetProcAddress(name); });
        return true;
    }

    // Reads the just-rendered frame back from the (hidden) GL surface and
    // hands it to the render panel for display.
    void ReadbackRenderFrame() {
        if (!g_real.glReadPixels || m_contentW <= 0 || m_contentH <= 0) return;
        std::vector<uint8_t> pixels(static_cast<size_t>(m_contentW) * m_contentH * 4, 0);
        g_real.glReadPixels(0, 0, m_contentW, m_contentH, GL_BGRA, GL_UNSIGNED_BYTE, pixels.data());
        m_renderPanel->SetPixels(std::move(pixels));
    }

    // Runs the trace up to (and including) targetIdx against whatever GL
    // context/surface size is currently set up. Split out from
    // RunToIndex so it can be re-run once after the surface is resized
    // to match the captured content.
    void RunOnce(size_t targetIdx) {
        if (!CreateFreshGLContext()) return;
        ClearShaderSources();

        IdRemapper remap;
        bool readBackAtFrameBoundary = false;
        for (size_t i = 0; i <= targetIdx; ++i) {
            const Record& rec = m_records[i];
            if (rec.isFrameMarker) {
                // The rendered image is in the back buffer immediately
                // before the swap. Reading after the swap can inspect the
                // newly available back buffer, which is not the frame just
                // rendered and may already be cleared by the application.
                ReadbackRenderFrame();
                readBackAtFrameBoundary = true;
                SwapBuffers(m_hdc);
            } else {
                ReplayDispatch(rec.id, rec.data.data(), rec.data.size(), remap);
            }
        }
        // If execution stopped mid-frame, read back the pending back buffer.
        // Otherwise the last completed frame was captured at its boundary;
        // do not overwrite it with the post-swap back buffer.
        if (!readBackAtFrameBoundary) ReadbackRenderFrame();
        SwapBuffers(m_hdc);
        RefreshStateWindow(remap);
        RefreshAttachmentViews(remap);
    }

    void RefreshStateWindow(const IdRemapper& remap) {
        ResourceStateReport report = RenderResourcesAndState(remap);
        m_stateList->Clear();
        for (const auto& line : report.lines) m_stateList->Append(wxString(line));
        m_stateTextureByLine = std::move(report.textureByLine);
        m_stateShaderByLine = std::move(report.shaderByLine);
        m_stateFramebufferByLine = std::move(report.framebufferByLine);
    }

    void EnsureFramebufferViewWindow() {
        if (m_framebufferViewFrame) return;
        m_framebufferViewFrame = new wxFrame(this, wxID_ANY, "Frame Buffer", wxDefaultPosition, wxSize(900, 760));
        wxBoxSizer* root = new wxBoxSizer(wxVERTICAL);
        root->Add(new wxStaticText(m_framebufferViewFrame, wxID_ANY, "Color attachment"), 0, wxEXPAND | wxALL, 4);
        m_framebufferViewColorPanel = new AttachmentPanel(m_framebufferViewFrame);
        root->Add(m_framebufferViewColorPanel, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);
        root->Add(new wxStaticText(m_framebufferViewFrame, wxID_ANY, "Depth / stencil attachment"), 0, wxEXPAND | wxALL, 4);
        m_framebufferViewDepthPanel = new AttachmentPanel(m_framebufferViewFrame);
        root->Add(m_framebufferViewDepthPanel, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 4);
        m_framebufferViewFrame->SetSizer(root);
        m_framebufferViewFrame->Bind(wxEVT_CHAR_HOOK, [this](wxKeyEvent& e) {
            if (e.GetKeyCode() == WXK_ESCAPE) {
                m_framebufferViewFrame->Close();
                return;
            }
            e.Skip();
        });
        m_framebufferViewFrame->Bind(wxEVT_CLOSE_WINDOW, [this](wxCloseEvent& e) {
            m_framebufferViewColorPanel = nullptr;
            m_framebufferViewDepthPanel = nullptr;
            m_framebufferViewFrame = nullptr;
            e.Skip();
        });
    }

    void ShowFramebufferAttachments(GLuint realFbo) {
        EnsureFramebufferViewWindow();
        if (!m_framebufferViewFrame || !m_framebufferViewColorPanel || !m_framebufferViewDepthPanel) return;
        if (!g_inspect.glGetIntegerv || !g_real.glBindFramebuffer) return;

        GLint prevFbo = 0;
        g_inspect.glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);
        g_real.glBindFramebuffer(GL_FRAMEBUFFER, realFbo);

        AttachmentInfo colorInfo = QueryAttachment(GL_COLOR_ATTACHMENT0);
        AttachmentInfo depthInfo = QueryAttachment(GL_DEPTH_ATTACHMENT);
        AttachmentInfo depthStencilInfo = QueryAttachment(GL_DEPTH_STENCIL_ATTACHMENT);
        AttachmentInfo stencilInfo = QueryAttachment(GL_STENCIL_ATTACHMENT);
        if (depthStencilInfo.objType != GL_NONE_ATTACHMENT) {
            depthInfo = depthStencilInfo;
        }

        if (colorInfo.objType != GL_NONE_ATTACHMENT && colorInfo.width > 0) {
            GLint prevReadBuffer = 0;
            g_inspect.glGetIntegerv(GL_READ_BUFFER, &prevReadBuffer);
            ReadbackAndShow(colorInfo.width, colorInfo.height, GL_BGRA, GL_UNSIGNED_BYTE,
                            AttachmentKind::Color, m_framebufferViewColorPanel);
            if (g_real.glReadBuffer) g_real.glReadBuffer(static_cast<GLenum>(prevReadBuffer));
        } else {
            m_framebufferViewColorPanel->Clear();
        }

        if (depthInfo.objType != GL_NONE_ATTACHMENT && depthInfo.width > 0) {
            if (depthStencilInfo.objType != GL_NONE_ATTACHMENT ||
                stencilInfo.objType != GL_NONE_ATTACHMENT) {
                ReadbackAndShow(depthInfo.width, depthInfo.height, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,
                                AttachmentKind::DepthStencil, m_framebufferViewDepthPanel);
            } else {
                ReadbackAndShow(depthInfo.width, depthInfo.height, GL_DEPTH_COMPONENT, GL_FLOAT,
                                AttachmentKind::Depth, m_framebufferViewDepthPanel);
            }
        } else {
            m_framebufferViewDepthPanel->Clear();
        }

        g_real.glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevFbo));
        m_framebufferViewFrame->SetTitle(wxString::Format("Frame Buffer = %u", realFbo));
        m_framebufferViewFrame->Show();
        m_framebufferViewFrame->Raise();
     }

    // What a framebuffer attachment point currently holds and (if it's a
    // texture or renderbuffer -- i.e. anything actually there) its size,
    // queried by temporarily binding it. Used to know how big a buffer to
    // glReadPixels back for each attachment.
    struct AttachmentInfo {
        GLint objType = 0; // GL_NONE / GL_TEXTURE / GL_RENDERBUFFER
        GLint width = 0;
        GLint height = 0;
        GLenum textureTarget = GL_TEXTURE_2D;
    };

    AttachmentInfo QueryAttachment(GLenum point) {
        AttachmentInfo info;
        if (!g_inspect.glGetFramebufferAttachmentParameteriv) return info;
        GLint objName = 0;
        g_inspect.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, point, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, &info.objType);
        g_inspect.glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, point, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &objName);
        if (info.objType == GL_ATTACHMENT_TYPE_TEXTURE && g_real.glBindTexture && g_inspect.glGetTexLevelParameteriv) {
            GLint target = GL_TEXTURE_2D;
            g_inspect.glGetFramebufferAttachmentParameteriv(
                GL_FRAMEBUFFER, point, GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_TARGET, &target);
            info.textureTarget = static_cast<GLenum>(target);

            GLenum bindingPname = 0;
            switch (info.textureTarget) {
                case GL_TEXTURE_2D:
                    bindingPname = GL_TEXTURE_BINDING_2D;
                    break;
                case GL_TEXTURE_2D_MULTISAMPLE:
                    bindingPname = GL_TEXTURE_BINDING_2D_MULTISAMPLE;
                    break;
                default:
                    bindingPname = 0;
                    break;
            }

            if (bindingPname != 0) {
                GLint prevTex = 0;
                g_inspect.glGetIntegerv(bindingPname, &prevTex);
                g_real.glBindTexture(info.textureTarget, static_cast<GLuint>(objName));
                g_inspect.glGetTexLevelParameteriv(info.textureTarget, 0, GL_TEXTURE_WIDTH, &info.width);
                g_inspect.glGetTexLevelParameteriv(info.textureTarget, 0, GL_TEXTURE_HEIGHT, &info.height);
                g_real.glBindTexture(info.textureTarget, static_cast<GLuint>(prevTex));
            }
        } else if (info.objType == GL_RENDERBUFFER && g_real.glBindRenderbuffer && g_inspect.glGetRenderbufferParameteriv) {
            GLint prevRb = 0;
            g_inspect.glGetIntegerv(GL_RENDERBUFFER_BINDING, &prevRb);
            g_real.glBindRenderbuffer(GL_RENDERBUFFER, static_cast<GLuint>(objName));
            g_inspect.glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &info.width);
            g_inspect.glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &info.height);
            g_real.glBindRenderbuffer(GL_RENDERBUFFER, static_cast<GLuint>(prevRb));
        }
        return info;
    }

    // Reads back whatever's currently bound as the read framebuffer --
    // works the same whether the attachment is a texture or a
    // renderbuffer, since glReadPixels doesn't care which -- and hands
    // it to `panel`.
    void ReadbackAndShow(int w, int h, GLenum format, GLenum type, AttachmentKind kind, AttachmentPanel* panel) {
        if (!g_real.glReadPixels || w <= 0 || h <= 0) {
            panel->Clear();
            return;
        }
        size_t pixelCount = static_cast<size_t>(w) * h;
        std::vector<unsigned char> displayPixels(pixelCount * 4, 0);
        std::vector<unsigned char> colorRaw;
        std::vector<float> depthRaw;
        std::vector<unsigned char> stencilRaw;

        if (kind == AttachmentKind::Color) {
            // User FBOs have their own read-buffer state. Explicitly select
            // the attachment we queried instead of relying on the trace's
            // current GL_READ_BUFFER value (which may be GL_NONE).
            if (g_real.glReadBuffer) g_real.glReadBuffer(GL_COLOR_ATTACHMENT0);
            g_real.glReadPixels(0, 0, w, h, format, type, displayPixels.data());
            colorRaw = displayPixels;
        } else if (kind == AttachmentKind::DepthStencil) {
            std::vector<uint32_t> packed(pixelCount, 0);
            g_real.glReadPixels(0, 0, w, h, format, type, packed.data());
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
            g_real.glReadPixels(0, 0, w, h, format, type, depthRaw.data());
            for (size_t i = 0; i < pixelCount; ++i) {
                unsigned char gray = static_cast<unsigned char>(depthRaw[i] * 255.0f);
                displayPixels[i * 4 + 0] = gray;
                displayPixels[i * 4 + 1] = gray;
                displayPixels[i * 4 + 2] = gray;
                displayPixels[i * 4 + 3] = 255;
            }
        }
        panel->SetImage(kind, w, h, std::move(displayPixels), std::move(colorRaw), std::move(depthRaw), std::move(stencilRaw));
    }

    // Refreshes the two docked attachment panels from the framebuffer
    // currently bound at the end of replay. If that's the default
    // framebuffer (0), optionally falls back to the most recently-created
    // user FBO when one exists, then finally to the default buffers.
    //
    // Using "highest created id" unconditionally can easily pick an FBO
    // that's unrelated to the draw currently being inspected (or already
    // detached/deleted), which makes the panels appear blank even when the
    // replay itself rendered valid content.
    void RefreshAttachmentViews(const IdRemapper& remap) {
        if (!g_inspect.glGetIntegerv || !g_real.glBindFramebuffer) return;

        GLint prevFbo = 0;
        g_inspect.glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevFbo);

        bool haveFbo = prevFbo != 0;
        GLuint realFbo = static_cast<GLuint>(prevFbo);
        if (!haveFbo) {
            uint32_t bestCapturedId = 0;
            for (auto& [capturedId, mappedRealId] : remap.All("framebuffer")) {
                if (!haveFbo || capturedId > bestCapturedId) {
                    haveFbo = true;
                    bestCapturedId = capturedId;
                    realFbo = mappedRealId;
                }
            }
        }

        if (haveFbo) {
            g_real.glBindFramebuffer(GL_FRAMEBUFFER, realFbo);
            AttachmentInfo colorInfo = QueryAttachment(GL_COLOR_ATTACHMENT0);
            AttachmentInfo depthInfo = QueryAttachment(GL_DEPTH_ATTACHMENT);
            AttachmentInfo depthStencilInfo = QueryAttachment(GL_DEPTH_STENCIL_ATTACHMENT);
            AttachmentInfo stencilInfo = QueryAttachment(GL_STENCIL_ATTACHMENT);
            if (depthStencilInfo.objType != GL_NONE_ATTACHMENT) {
                depthInfo = depthStencilInfo;
            }

            if (colorInfo.objType != GL_NONE_ATTACHMENT && colorInfo.width > 0) {
                GLint prevReadBuffer = 0;
                g_inspect.glGetIntegerv(GL_READ_BUFFER, &prevReadBuffer);
                ReadbackAndShow(colorInfo.width, colorInfo.height, GL_BGRA, GL_UNSIGNED_BYTE,
                                 AttachmentKind::Color, m_colorAttachmentPanel);
                if (g_real.glReadBuffer) {
                    g_real.glReadBuffer(static_cast<GLenum>(prevReadBuffer));
                }
            } else {
                m_colorAttachmentPanel->Clear();
            }

            if (depthInfo.objType != GL_NONE_ATTACHMENT && depthInfo.width > 0) {
                if (depthStencilInfo.objType != GL_NONE_ATTACHMENT ||
                    stencilInfo.objType != GL_NONE_ATTACHMENT) {
                    ReadbackAndShow(depthInfo.width, depthInfo.height, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8,
                                     AttachmentKind::DepthStencil, m_depthAttachmentPanel);
                } else {
                    ReadbackAndShow(depthInfo.width, depthInfo.height, GL_DEPTH_COMPONENT, GL_FLOAT,
                                     AttachmentKind::Depth, m_depthAttachmentPanel);
                }
            } else {
                m_depthAttachmentPanel->Clear();
            }
        } else {
            g_real.glBindFramebuffer(GL_FRAMEBUFFER, 0);
            ReadbackAndShow(m_contentW, m_contentH, GL_BGRA, GL_UNSIGNED_BYTE, AttachmentKind::Color, m_colorAttachmentPanel);
            ReadbackAndShow(m_contentW, m_contentH, GL_DEPTH_COMPONENT, GL_FLOAT, AttachmentKind::Depth, m_depthAttachmentPanel);
        }

        g_real.glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(prevFbo));
    }

    void OnCallListDClick(wxCommandEvent& event) {
        int sel = event.GetSelection();
        if (sel != wxNOT_FOUND) RunToIndex(static_cast<size_t>(sel));
    }

    void OnStateListDClick(wxCommandEvent& event) {
        int sel = event.GetSelection();
        if (sel == wxNOT_FOUND) return;
        if (static_cast<size_t>(sel) < m_stateTextureByLine.size()) {
            const TextureLineInfo& t = m_stateTextureByLine[sel];
            if (t.realId != 0) ShowTextureImage(t.realId, t.width, t.height, t.internalFormat);
        }
        if (static_cast<size_t>(sel) < m_stateShaderByLine.size()) {
            const ShaderLineInfo& sh = m_stateShaderByLine[sel];
            if (sh.realId != 0) ShowShaderSource(sh.realId);
        }
        if (static_cast<size_t>(sel) < m_stateFramebufferByLine.size()) {
            const FramebufferLineInfo& fb = m_stateFramebufferByLine[sel];
            if (fb.realId != 0) ShowFramebufferAttachments(fb.realId);
        }
    }

    void OnClose(wxCloseEvent&) { Destroy(); }

    // Esc is otherwise unused at the frame level (the floating texture/
    // shader viewers each close themselves on a single Esc, independent
    // of this) -- two Escapes within kDoubleEscMs of each other exit the
    // whole application, closing every top-level window (this frame plus
    // any floating viewers) rather than just this one, so nothing is left
    // running behind it.
    void OnCharHook(wxKeyEvent& event) {
        if (event.GetKeyCode() == WXK_ESCAPE) {
            constexpr ULONGLONG kDoubleEscMs = 600;
            ULONGLONG now = GetTickCount64();
            if (m_lastEscTick != 0 && now - m_lastEscTick <= kDoubleEscMs) {
                std::vector<wxWindow*> tops(wxTopLevelWindows.begin(), wxTopLevelWindows.end());
                for (wxWindow* w : tops) {
                    if (auto* top = dynamic_cast<wxTopLevelWindow*>(w)) top->Close(true);
                }
                return;
            }
            m_lastEscTick = now;
        }
        event.Skip();
    }

    RenderPanel* m_renderPanel = nullptr;
    CallListPanel* m_callListPanel = nullptr;
    AttachmentPanel* m_colorAttachmentPanel = nullptr;
    AttachmentPanel* m_depthAttachmentPanel = nullptr;
    wxListBox* m_callList = nullptr;
    wxListBox* m_stateList = nullptr;

    HGLRC m_hglrc = nullptr;
    HDC m_hdc = nullptr;
    int m_contentW = kDefaultGLContentW;
    int m_contentH = kDefaultGLContentH;
    ULONGLONG m_lastEscTick = 0;

    std::vector<Record> m_records;
    std::vector<TextureLineInfo> m_stateTextureByLine;
    std::vector<ShaderLineInfo> m_stateShaderByLine;
    std::vector<FramebufferLineInfo> m_stateFramebufferByLine;
    wxFrame* m_framebufferViewFrame = nullptr;
    AttachmentPanel* m_framebufferViewColorPanel = nullptr;
    AttachmentPanel* m_framebufferViewDepthPanel = nullptr;
};

class ReplayApp : public wxApp {
public:
    bool OnInit() override {
        if (argc < 2) {
            fprintf(stderr, "usage: gl_replay.exe <trace-file>\n");
            return false;
        }
        std::string tracePath = wxString(argv[1]).ToStdString();

        ReplayFrame* frame = new ReplayFrame();
        frame->Show();

        if (!frame->SetupGLContext()) {
            fprintf(stderr, "failed to create GL context\n");
            return false;
        }
        if (!frame->LoadTrace(tracePath.c_str())) return false;
        frame->RunToIndex(SIZE_MAX); // replay everything once, up front (RunToIndex handles an empty trace fine)

        // Driven non-interactively (e.g. from an automated test): do the
        // work above, then exit immediately instead of entering the
        // normal event loop.
        if (GetEnvironmentVariableA("GLCAP_REPLAY_AUTOEXIT", nullptr, 0)) {
            frame->Close(true);
            return false;
        }
        return true;
    }
};

} // namespace

wxIMPLEMENT_APP(ReplayApp);

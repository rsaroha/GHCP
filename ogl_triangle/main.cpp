#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <GL/gl.h>
#include "teapot_data.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>

namespace
{
constexpr wchar_t kWindowClassName[] = L"OglTriangleWindow";
constexpr wchar_t kWindowTitle[] = L"Lit Teapot - Trackball";
constexpr float kPi = 3.14159265358979323846f;

struct Vec3
{
    float x;
    float y;
    float z;
};

HDC g_deviceContext = nullptr;
HGLRC g_renderContext = nullptr;
int g_viewWidth = 1;
int g_viewHeight = 1;
bool g_dragging = false;
Vec3 g_previousTrackballPoint{};
float g_rotation[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

Vec3 Cross(Vec3 a, Vec3 b)
{
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

float Dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Normalize(Vec3 value)
{
    const float length = std::sqrt(Dot(value, value));
    return length > 0.0001f ? Vec3{value.x / length, value.y / length, value.z / length} : Vec3{};
}

Vec3 TrackballPoint(int x, int y)
{
    const float nx = (2.0f * x - g_viewWidth) / static_cast<float>(std::max(1, g_viewWidth));
    const float ny = (g_viewHeight - 2.0f * y) / static_cast<float>(std::max(1, g_viewHeight));
    const float distanceSquared = nx * nx + ny * ny;
    if (distanceSquared <= 1.0f)
    {
        return {nx, ny, std::sqrt(1.0f - distanceSquared)};
    }
    return Normalize({nx, ny, 0.0f});
}

void ApplyTrackballRotation(Vec3 from, Vec3 to)
{
    const Vec3 axis = Cross(from, to);
    const float axisLength = std::sqrt(Dot(axis, axis));
    if (axisLength < 0.0001f)
    {
        return;
    }

    const float angle = std::acos(std::clamp(Dot(from, to), -1.0f, 1.0f)) * 180.0f / kPi;
    glPushMatrix();
    glLoadIdentity();
    glRotatef(angle, axis.x, axis.y, axis.z);
    glMultMatrixf(&g_rotation[0][0]);
    glGetFloatv(GL_MODELVIEW_MATRIX, &g_rotation[0][0]);
    glPopMatrix();
}

void DrawLathe(const float (*profile)[2], int profileCount, int slices)
{
    for (int ring = 0; ring < profileCount - 1; ++ring)
    {
        const float z0 = profile[ring][0];
        const float r0 = profile[ring][1];
        const float z1 = profile[ring + 1][0];
        const float r1 = profile[ring + 1][1];
        const float slope = (r1 - r0) / std::max(0.0001f, z1 - z0);

        glBegin(GL_QUAD_STRIP);
        for (int slice = 0; slice <= slices; ++slice)
        {
            const float angle = 2.0f * kPi * slice / slices;
            const float c = std::cos(angle);
            const float s = std::sin(angle);
            const Vec3 normal0 = Normalize({c, s, -slope});
            const Vec3 normal1 = normal0;
            glNormal3f(normal0.x, normal0.y, normal0.z);
            glVertex3f(r0 * c, r0 * s, z0);
            glNormal3f(normal1.x, normal1.y, normal1.z);
            glVertex3f(r1 * c, r1 * s, z1);
        }
        glEnd();
    }
}

void DrawFrustum(float radius0, float radius1, float length, int slices)
{
    glBegin(GL_QUAD_STRIP);
    for (int slice = 0; slice <= slices; ++slice)
    {
        const float angle = 2.0f * kPi * slice / slices;
        const float c = std::cos(angle);
        const float s = std::sin(angle);
        glNormal3f(c, s, 0.0f);
        glVertex3f(radius0 * c, radius0 * s, 0.0f);
        glVertex3f(radius1 * c, radius1 * s, length);
    }
    glEnd();
}

void DrawTorus(float majorRadius, float tubeRadius, int majorSegments, int tubeSegments)
{
    for (int major = 0; major < majorSegments; ++major)
    {
        const float a0 = 2.0f * kPi * major / majorSegments;
        const float a1 = 2.0f * kPi * (major + 1) / majorSegments;
        glBegin(GL_QUAD_STRIP);
        for (int tube = 0; tube <= tubeSegments; ++tube)
        {
            const float b = 2.0f * kPi * tube / tubeSegments;
            for (float a : {a0, a1})
            {
                const float c = std::cos(a);
                const float s = std::sin(a);
                const float cb = std::cos(b);
                const float sb = std::sin(b);
                glNormal3f(c * cb, sb, s * cb);
                glVertex3f((majorRadius + tubeRadius * cb) * c, tubeRadius * sb,
                    (majorRadius + tubeRadius * cb) * s);
            }
        }
        glEnd();
    }
}

void DrawTeapot()
{
    glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_MAP2_VERTEX_3);
    glColor3f(0.72f, 0.18f, 0.08f);
    glPushMatrix();
    glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);
    glTranslatef(0.0f, 0.0f, -1.5f);

    for (int patch = 0; patch < 10; ++patch)
    {
        float p[4][4][3]{};
        float q[4][4][3]{};
        float r[4][4][3]{};
        float s[4][4][3]{};
        for (int row = 0; row < 4; ++row)
        {
            for (int column = 0; column < 4; ++column)
            {
                const int index = kTeapotPatches[patch][row * 4 + column];
                const int reverseIndex = kTeapotPatches[patch][row * 4 + (3 - column)];
                for (int axis = 0; axis < 3; ++axis)
                {
                    p[row][column][axis] = kTeapotControlPoints[index][axis];
                    q[row][column][axis] = kTeapotControlPoints[reverseIndex][axis];
                    if (axis == 1)
                    {
                        q[row][column][axis] *= -1.0f;
                    }
                    if (patch < 6)
                    {
                        r[row][column][axis] = kTeapotControlPoints[reverseIndex][axis];
                        s[row][column][axis] = kTeapotControlPoints[index][axis];
                        if (axis == 0)
                        {
                            r[row][column][axis] *= -1.0f;
                            s[row][column][axis] *= -1.0f;
                        }
                        if (axis == 1)
                        {
                            s[row][column][axis] *= -1.0f;
                        }
                    }
                }
            }
        }

        glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3, 4, 0.0f, 1.0f, 12, 4, &p[0][0][0]);
        glMapGrid2f(10, 0.0f, 1.0f, 10, 0.0f, 1.0f);
        glEvalMesh2(GL_FILL, 0, 10, 0, 10);
        glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3, 4, 0.0f, 1.0f, 12, 4, &q[0][0][0]);
        glEvalMesh2(GL_FILL, 0, 10, 0, 10);
        if (patch < 6)
        {
            glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3, 4, 0.0f, 1.0f, 12, 4, &r[0][0][0]);
            glEvalMesh2(GL_FILL, 0, 10, 0, 10);
            glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3, 4, 0.0f, 1.0f, 12, 4, &s[0][0][0]);
            glEvalMesh2(GL_FILL, 0, 10, 0, 10);
        }
    }
    glPopMatrix();
    glPopAttrib();
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.6f);
    glRotatef(-12.0f, 1.0f, 0.0f, 0.0f);
    glMultMatrixf(&g_rotation[0][0]);
    DrawTeapot();
    SwapBuffers(g_deviceContext);
}

void Resize(int width, int height)
{
    g_viewWidth = std::max(1, width);
    g_viewHeight = std::max(1, height);
    glViewport(0, 0, g_viewWidth, g_viewHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float aspect = g_viewWidth / static_cast<float>(g_viewHeight);
    if (aspect >= 1.0f)
    {
        glOrtho(-1.8f * aspect, 1.8f * aspect, -1.8f, 1.8f, -10.0f, 10.0f);
    }
    else
    {
        glOrtho(-1.8f, 1.8f, -1.8f / aspect, 1.8f / aspect, -10.0f, 10.0f);
    }
    glMatrixMode(GL_MODELVIEW);
}

bool InitializeOpenGL(HWND window)
{
    g_deviceContext = GetDC(window);
    if (!g_deviceContext)
    {
        return false;
    }

    PIXELFORMATDESCRIPTOR descriptor{};
    descriptor.nSize = sizeof(descriptor);
    descriptor.nVersion = 1;
    descriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    descriptor.iPixelType = PFD_TYPE_RGBA;
    descriptor.cColorBits = 32;
    descriptor.cDepthBits = 24;
    descriptor.cStencilBits = 8;
    descriptor.iLayerType = PFD_MAIN_PLANE;

    const int pixelFormat = ChoosePixelFormat(g_deviceContext, &descriptor);
    if (pixelFormat == 0 || !SetPixelFormat(g_deviceContext, pixelFormat, &descriptor))
    {
        return false;
    }

    g_renderContext = wglCreateContext(g_deviceContext);
    if (!g_renderContext || !wglMakeCurrent(g_deviceContext, g_renderContext))
    {
        return false;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);
    const GLfloat lightPosition[] = {2.0f, 3.0f, 4.0f, 1.0f};
    const GLfloat lightColor[] = {1.0f, 0.92f, 0.78f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glClearColor(0.06f, 0.07f, 0.10f, 1.0f);

    RECT clientRect{};
    GetClientRect(window, &clientRect);
    Resize(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
    return true;
}

void ShutdownOpenGL(HWND window)
{
    if (g_renderContext)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(g_renderContext);
        g_renderContext = nullptr;
    }
    if (g_deviceContext)
    {
        ReleaseDC(window, g_deviceContext);
        g_deviceContext = nullptr;
    }
}

LRESULT CALLBACK WindowProcedure(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
        if (g_renderContext)
        {
            Resize(LOWORD(lParam), HIWORD(lParam));
        }
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT paint{};
        BeginPaint(window, &paint);
        if (g_renderContext)
        {
            Render();
        }
        EndPaint(window, &paint);
        return 0;
    }
    case WM_TIMER:
        InvalidateRect(window, nullptr, FALSE);
        return 0;
    case WM_LBUTTONDOWN:
        g_dragging = true;
        SetCapture(window);
        g_previousTrackballPoint = TrackballPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
        return 0;
    case WM_MOUSEMOVE:
        if (g_dragging)
        {
            const Vec3 currentPoint = TrackballPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
            ApplyTrackballRotation(g_previousTrackballPoint, currentPoint);
            g_previousTrackballPoint = currentPoint;
            InvalidateRect(window, nullptr, FALSE);
        }
        return 0;
    case WM_LBUTTONUP:
        g_dragging = false;
        ReleaseCapture();
        return 0;
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
        {
            DestroyWindow(window);
        }
        return 0;
    case WM_CLOSE:
        DestroyWindow(window);
        return 0;
    case WM_DESTROY:
        KillTimer(window, 1);
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProcW(window, message, wParam, lParam);
    }
}
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int showCommand)
{
    WNDCLASSEXW windowClass{};
    windowClass.cbSize = sizeof(windowClass);
    windowClass.hInstance = instance;
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    windowClass.lpszClassName = kWindowClassName;
    windowClass.style = CS_OWNDC;

    if (!RegisterClassExW(&windowClass))
    {
        return EXIT_FAILURE;
    }

    RECT windowRect{0, 0, 900, 700};
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
    HWND window = CreateWindowExW(
        0, kWindowClassName, kWindowTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
        nullptr, nullptr, instance, nullptr);

    if (!window || !InitializeOpenGL(window))
    {
        if (window)
        {
            ShutdownOpenGL(window);
            DestroyWindow(window);
        }
        return EXIT_FAILURE;
    }

    SetTimer(window, 1, 16, nullptr);
    ShowWindow(window, showCommand);
    UpdateWindow(window);

    MSG message{};
    while (GetMessageW(&message, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&message);
        DispatchMessageW(&message);
    }

    ShutdownOpenGL(window);
    UnregisterClassW(kWindowClassName, instance);
    return static_cast<int>(message.wParam);
}

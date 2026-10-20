#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <GL/gl.h>
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_win32.h"
#define TINYGLTF_NO_STB_IMAGE_WRITE
#define TINYGLTF_USE_CUSTOM_JSON
#define TINYGLTF_IMPLEMENTATION
#include <tiny_gltf.h>
#define TINYOBJLOADER_IMPLEMENTATION
#include <algorithm>
#include <cctype>
#include <cmath>
#include <commdlg.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iterator>
#include <limits>
#include <string>
#include <tiny_obj_loader.h>
#include <vector>

#pragma comment(lib, "opengl32.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_STATIC_DRAW 0x88E4
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_FRAMEBUFFER 0x8D40
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_MAX_SAMPLES 0x8D57
#define GL_RGBA8 0x8058
#define GL_RGBA32F 0x8814
#define GL_R8 0x8229
#define GL_RED 0x1903
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_TEXTURE0 0x84C0
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001

typedef ptrdiff_t GLsizeiptr;
typedef char GLchar;

#define GL_FUNCTIONS(X)                                                                            \
    X(GLuint, glCreateShader, (GLenum))                                                            \
    X(void, glShaderSource, (GLuint, GLsizei, const GLchar *const *, const GLint *))               \
    X(void, glCompileShader, (GLuint))                                                             \
    X(void, glGetShaderiv, (GLuint, GLenum, GLint *))                                              \
    X(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *))                            \
    X(GLuint, glCreateProgram, (void))                                                             \
    X(void, glAttachShader, (GLuint, GLuint))                                                      \
    X(void, glLinkProgram, (GLuint))                                                               \
    X(void, glGetProgramiv, (GLuint, GLenum, GLint *))                                             \
    X(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei *, GLchar *))                           \
    X(void, glDeleteShader, (GLuint))                                                              \
    X(void, glUseProgram, (GLuint))                                                                \
    X(GLint, glGetUniformLocation, (GLuint, const GLchar *))                                       \
    X(void, glUniform1i, (GLint, GLint))                                                           \
    X(void, glUniform1f, (GLint, GLfloat))                                                         \
    X(void, glUniform2f, (GLint, GLfloat, GLfloat))                                                \
    X(void, glUniform3f, (GLint, GLfloat, GLfloat, GLfloat))                                       \
    X(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat *))                      \
    X(void, glGenVertexArrays, (GLsizei, GLuint *))                                                \
    X(void, glBindVertexArray, (GLuint))                                                           \
    X(void, glDeleteVertexArrays, (GLsizei, const GLuint *))                                       \
    X(void, glGenBuffers, (GLsizei, GLuint *))                                                     \
    X(void, glDeleteBuffers, (GLsizei, const GLuint *))                                            \
    X(void, glBindBuffer, (GLenum, GLuint))                                                        \
    X(void, glBufferData, (GLenum, GLsizeiptr, const void *, GLenum))                              \
    X(void, glEnableVertexAttribArray, (GLuint))                                                   \
    X(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))      \
    X(void, glGenFramebuffers, (GLsizei, GLuint *))                                                \
    X(void, glDeleteFramebuffers, (GLsizei, const GLuint *))                                       \
    X(void, glBindFramebuffer, (GLenum, GLuint))                                                   \
    X(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))                       \
    X(GLenum, glCheckFramebufferStatus, (GLenum))                                                  \
    X(void, glTexImage2DMultisample, (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean))       \
    X(void, glBlitFramebuffer,                                                                     \
      (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum))                \
    X(void, glActiveTexture, (GLenum))

#define DECLARE_GL(ret, name, args)                                                                \
    typedef ret(APIENTRY *name##_t) args;                                                          \
    static name##_t name;
GL_FUNCTIONS(DECLARE_GL)
#undef DECLARE_GL

typedef HGLRC(WINAPI *CreateContextAttribs)(HDC, HGLRC, const int *);
typedef BOOL(WINAPI *SwapInterval)(int);

/**********************************************************************************
 *   Function Name  : loadGL
 *   Purpose : Resolve the OpenGL entry points required by the renderer.
 *
 **********************************************************************************/
static bool loadGL()
{
    bool ok = true;
#define LOAD_GL(ret, name, args)                                                                   \
    name = reinterpret_cast<name##_t>(wglGetProcAddress(#name));                                   \
    if (!name)                                                                                     \
        ok = false;
    GL_FUNCTIONS(LOAD_GL)
#undef LOAD_GL
    return ok;
}

struct V3
{
    float x, y, z;
};

/**********************************************************************************
 *   Function Name  : operator+
 *   Purpose : Add two three-dimensional vectors component-wise.
 *
 **********************************************************************************/
static V3 operator+(V3 a, V3 b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

/**********************************************************************************
 *   Function Name  : operator-
 *   Purpose : Subtract one three-dimensional vector from another.
 *
 **********************************************************************************/
static V3 operator-(V3 a, V3 b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

/**********************************************************************************
 *   Function Name  : operator*
 *   Purpose : Scale a three-dimensional vector by a scalar.
 *
 **********************************************************************************/
static V3 operator*(V3 a, float s)
{
    return {a.x * s, a.y * s, a.z * s};
}

/**********************************************************************************
 *   Function Name  : dot
 *   Purpose : Compute the dot product of two three-dimensional vectors.
 *
 **********************************************************************************/
static float dot(V3 a, V3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**********************************************************************************
 *   Function Name  : cross
 *   Purpose : Compute the cross product of two three-dimensional vectors.
 *
 **********************************************************************************/
static V3 cross(V3 a, V3 b)
{
    return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

/**********************************************************************************
 *   Function Name  : norm
 *   Purpose : Return the normalized vector, or the zero vector for zero length.
 *
 **********************************************************************************/
static V3 norm(V3 a)
{
    float d = std::sqrt(dot(a, a));
    return d > 0 ? a * (1.0f / d) : a;
}

struct M4
{
    float m[16]{};
};

/**********************************************************************************
 *   Function Name  : multiply
 *   Purpose : Multiply two column-major 4x4 matrices.
 *
 **********************************************************************************/
static M4 multiply(const M4 &a, const M4 &b)
{
    M4 r{};
    for (int c = 0; c < 4; c++)
        for (int row = 0; row < 4; row++)
            for (int k = 0; k < 4; k++)
                r.m[c * 4 + row] += a.m[k * 4 + row] * b.m[c * 4 + k];
    return r;
}

/**********************************************************************************
 *   Function Name  : perspective
 *   Purpose : Build a perspective projection matrix from the camera parameters.
 *
 **********************************************************************************/
static M4 perspective(float fovy, float aspect, float nearZ, float farZ)
{
    float f = 1.0f / std::tan(fovy * 0.00872664626f);
    M4 r{};
    r.m[0] = f / aspect;
    r.m[5] = f;
    r.m[10] = (farZ + nearZ) / (nearZ - farZ);
    r.m[11] = -1;
    r.m[14] = 2 * farZ * nearZ / (nearZ - farZ);
    return r;
}

/**********************************************************************************
 *   Function Name  : lookAt
 *   Purpose : Build a view matrix looking from the eye toward the target.
 *
 **********************************************************************************/
static M4 lookAt(V3 eye, V3 target, V3 up)
{
    V3 f = norm(target - eye), s = norm(cross(f, up)), u = cross(s, f);
    M4 r{};
    r.m[0] = s.x;
    r.m[4] = s.y;
    r.m[8] = s.z;
    r.m[1] = u.x;
    r.m[5] = u.y;
    r.m[9] = u.z;
    r.m[2] = -f.x;
    r.m[6] = -f.y;
    r.m[10] = -f.z;
    r.m[12] = -dot(s, eye);
    r.m[13] = -dot(u, eye);
    r.m[14] = dot(f, eye);
    r.m[15] = 1;
    return r;
}

/**********************************************************************************
 *   Function Name  : loadShaderSource
 *   Purpose : Read a shader file from the shaders directory beside the executable.
 *
 **********************************************************************************/
static std::string loadShaderSource(const wchar_t *filename)
{
    wchar_t executablePath[32768];
    const DWORD pathLength =
        GetModuleFileNameW(nullptr, executablePath,
                           static_cast<DWORD>(sizeof(executablePath) / sizeof(executablePath[0])));
    if (pathLength == 0 || pathLength >= sizeof(executablePath) / sizeof(executablePath[0]))
    {
        MessageBoxW(nullptr, L"Could not locate the application directory.",
                    L"Shader loading failed", MB_ICONERROR);
        ExitProcess(1);
    }

    const std::filesystem::path path =
        std::filesystem::path(executablePath).parent_path() / L"shaders" / filename;
    std::ifstream file(path, std::ios::binary);
    if (!file)
    {
        const std::wstring message = L"Could not open shader file:\n" + path.wstring();
        MessageBoxW(nullptr, message.c_str(), L"Shader loading failed", MB_ICONERROR);
        ExitProcess(1);
    }
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

/**********************************************************************************
 *   Function Name  : shader
 *   Purpose : Compile a GLSL shader and report compilation failures.
 *
 **********************************************************************************/
static GLuint shader(GLenum type, const std::string &source)
{
    const char *sourceData = source.c_str();
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &sourceData, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok)
    {
        GLint n = 0;
        glGetShaderiv(s, GL_INFO_LOG_LENGTH, &n);
        std::string log(n > 0 ? n : 1, '\0');
        glGetShaderInfoLog(s, n, nullptr, &log[0]);
        MessageBoxA(nullptr, log.c_str(), "GLSL compile failed", MB_ICONERROR);
        ExitProcess(1);
    }
    return s;
}

/**********************************************************************************
 *   Function Name  : program
 *   Purpose : Link a vertex and fragment shader into an OpenGL program.
 *
 **********************************************************************************/
static GLuint program(const std::string &vs, const std::string &fs)
{
    GLuint v = shader(GL_VERTEX_SHADER, vs), f = shader(GL_FRAGMENT_SHADER, fs),
           p = glCreateProgram();
    glAttachShader(p, v);
    glAttachShader(p, f);
    glLinkProgram(p);
    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok)
    {
        GLint n = 0;
        glGetProgramiv(p, GL_INFO_LOG_LENGTH, &n);
        std::string log(n > 0 ? n : 1, '\0');
        glGetProgramInfoLog(p, n, nullptr, &log[0]);
        MessageBoxA(nullptr, log.c_str(), "GLSL link failed", MB_ICONERROR);
        ExitProcess(1);
    }
    glDeleteShader(v);
    glDeleteShader(f);
    return p;
}

/**********************************************************************************
 *   Function Name  : loc
 *   Purpose : Look up a uniform location in an OpenGL program.
 *
 **********************************************************************************/
static GLint loc(GLuint p, const char *n)
{
    return glGetUniformLocation(p, n);
}

/**********************************************************************************
 *   Function Name  : u1i
 *   Purpose : Set an integer uniform by name on an OpenGL program.
 *
 **********************************************************************************/
static void u1i(GLuint p, const char *n, int v)
{
    glUniform1i(loc(p, n), v);
}

/**********************************************************************************
 *   Function Name  : u1f
 *   Purpose : Set a floating-point uniform by name on an OpenGL program.
 *
 **********************************************************************************/
static void u1f(GLuint p, const char *n, float v)
{
    glUniform1f(loc(p, n), v);
}

struct Target
{
    GLuint fbo = 0, tex = 0, depthTex = 0;
    int w = 0, h = 0;
    GLint format = 0;
    GLenum channels = 0, type = 0;
    bool withDepth = false;

    /**********************************************************************************
     *   Function Name  : Target::init
     *   Purpose : Configure the framebuffer target's pixel format and depth buffer.
     *
     **********************************************************************************/
    void init(GLint f, GLenum c, GLenum t, bool depthBuffer = false)
    {
        format = f;
        channels = c;
        type = t;
        withDepth = depthBuffer;
        if (withDepth)
            glGenTextures(1, &depthTex);
    }

    /**********************************************************************************
     *   Function Name  : Target::resize
     *   Purpose : Allocate or resize the framebuffer attachments.
     *
     **********************************************************************************/
    void resize(int nw, int nh)
    {
        if (w == nw && h == nh && tex)
            return;
        w = nw;
        h = nh;
        if (!tex)
        {
            glGenTextures(1, &tex);
            glGenFramebuffers(1, &fbo);
        }
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, channels, type, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        if (withDepth)
        {
            glBindTexture(GL_TEXTURE_2D, depthTex);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT,
                         GL_UNSIGNED_INT, nullptr);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTex, 0);
        }
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            MessageBoxA(nullptr, "Incomplete framebuffer", "OpenGL error", MB_ICONERROR);
            ExitProcess(1);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /**********************************************************************************
     *   Function Name  : Target::bind
     *   Purpose : Bind this framebuffer and set its viewport dimensions.
     *
     **********************************************************************************/
    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, w, h);
    }
};

struct MultisampleTarget
{
    GLuint fbo = 0, colorTex = 0, depthTex = 0;
    int w = 0, h = 0, samples = 0;

    /**********************************************************************************
     *   Function Name  : MultisampleTarget::init
     *   Purpose : Configure the number of samples used by multisample texture attachments.
     *
     **********************************************************************************/
    void init(int sampleCount)
    {
        samples = sampleCount;
        if (samples > 1)
        {
            glGenFramebuffers(1, &fbo);
            glGenTextures(1, &colorTex);
            glGenTextures(1, &depthTex);
        }
    }

    /**********************************************************************************
     *   Function Name  : MultisampleTarget::available
     *   Purpose : Report whether multisample texture attachments were initialized.
     *
     **********************************************************************************/
    bool available() const
    {
        return samples > 1 && fbo && colorTex && depthTex;
    }

    /**********************************************************************************
     *   Function Name  : MultisampleTarget::resize
     *   Purpose : Allocate multisample color and depth textures for the requested size.
     *
     **********************************************************************************/
    void resize(int nw, int nh)
    {
        if (!available() || (w == nw && h == nh))
            return;
        w = nw;
        h = nh;
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, colorTex);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, w, h, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, depthTex);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_DEPTH_COMPONENT24, w, h,
                                GL_TRUE);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE,
                               colorTex, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE,
                               depthTex, 0);
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            MessageBoxA(nullptr, "Incomplete multisample texture framebuffer.", "OpenGL error",
                        MB_ICONERROR);
            ExitProcess(1);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    /**********************************************************************************
     *   Function Name  : MultisampleTarget::bind
     *   Purpose : Bind the multisample framebuffer and set its viewport dimensions.
     *
     **********************************************************************************/
    void bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glViewport(0, 0, w, h);
    }
};
struct Mesh
{
    GLuint vao = 0, vbo = 0, ibo = 0;
    GLsizei count = 0;
};

/**********************************************************************************
 *   Function Name  : uploadMesh
 *   Purpose : Create OpenGL buffers and vertex attributes for indexed mesh data.
 *
 **********************************************************************************/
static Mesh uploadMesh(const std::vector<float> &vertices, const std::vector<uint32_t> &indices)
{
    Mesh m;
    if (vertices.empty() || indices.empty() ||
        indices.size() > (size_t)std::numeric_limits<GLsizei>::max())
        return m;
    m.count = (GLsizei)indices.size();
    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);
    glGenBuffers(1, &m.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &m.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(),
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glBindVertexArray(0);
    return m;
}

/**********************************************************************************
 *   Function Name  : destroyMesh
 *   Purpose : Release the OpenGL objects owned by a mesh and clear its handles.
 *
 **********************************************************************************/
static void destroyMesh(Mesh &m)
{
    if (m.ibo)
        glDeleteBuffers(1, &m.ibo);
    if (m.vbo)
        glDeleteBuffers(1, &m.vbo);
    if (m.vao)
        glDeleteVertexArrays(1, &m.vao);
    m = {};
}

/**********************************************************************************
 *   Function Name  : knot
 *   Purpose : Evaluate a point on the procedural torus-knot centerline.
 *
 **********************************************************************************/
static V3 knot(float u, float radius)
{
    float a = 1.5f * u, cs = std::cos(a);
    return {radius * (2 + cs) * .5f * std::cos(u), radius * (2 + cs) * .5f * std::sin(u),
            radius * std::sin(a) * .5f};
}

/**********************************************************************************
 *   Function Name  : makeMesh
 *   Purpose : Generate and upload the procedural torus-knot fallback mesh.
 *
 **********************************************************************************/
static Mesh makeMesh()
{
    constexpr int rings = 256, sides = 32;
    constexpr float pi = 3.14159265f, r = .6f, t = .2f;
    std::vector<float> v;
    std::vector<unsigned> ix;
    for (int i = 0; i <= rings; i++)
    {
        float u = (float)i / rings * 4 * pi;
        V3 p = knot(u, r), p2 = knot(u + .01f, r);
        V3 tangent = p2 - p, norm0 = p2 + p, b = norm(cross(tangent, norm0));
        norm0 = norm(cross(b, tangent));
        for (int j = 0; j <= sides; j++)
        {
            float a = (float)j / sides * 2 * pi;
            V3 pos = p + norm0 * (-t * std::cos(a)) + b * (t * std::sin(a));
            V3 n = norm(pos - p);
            v.insert(v.end(), {pos.x, pos.z, -pos.y, n.x, n.z, -n.y});
        }
    }
    for (int i = 1; i <= rings; i++)
        for (int j = 1; j <= sides; j++)
        {
            unsigned a = (sides + 1) * (i - 1) + j - 1, b = (sides + 1) * i + j - 1,
                     c = (sides + 1) * i + j, d = (sides + 1) * (i - 1) + j;
            ix.insert(ix.end(), {a, b, d, b, c, d});
        }
    return uploadMesh(v, ix);
}

/**********************************************************************************
 *   Function Name  : identity
 *   Purpose : Return a 4x4 identity matrix.
 *
 **********************************************************************************/
static M4 identity()
{
    M4 m{};
    m.m[0] = m.m[5] = m.m[10] = m.m[15] = 1.0f;
    return m;
}

/**********************************************************************************
 *   Function Name  : transformPoint
 *   Purpose : Transform a point by a 4x4 matrix.
 *
 **********************************************************************************/
static V3 transformPoint(const M4 &m, V3 p)
{
    return {m.m[0] * p.x + m.m[4] * p.y + m.m[8] * p.z + m.m[12],
            m.m[1] * p.x + m.m[5] * p.y + m.m[9] * p.z + m.m[13],
            m.m[2] * p.x + m.m[6] * p.y + m.m[10] * p.z + m.m[14]};
}

/**********************************************************************************
 *   Function Name  : transformNormal
 *   Purpose : Transform a normal using the inverse-transpose of a matrix's linear part.
 *
 **********************************************************************************/
static V3 transformNormal(const M4 &m, V3 n)
{
    V3 a = {m.m[0], m.m[1], m.m[2]}, b = {m.m[4], m.m[5], m.m[6]}, c = {m.m[8], m.m[9], m.m[10]};
    V3 bc = cross(b, c), ca = cross(c, a), ab = cross(a, b);
    float det = dot(a, bc);
    if (std::abs(det) < 1e-10f)
        return {};
    return norm((bc * n.x + ca * n.y + ab * n.z) * (1.0f / det));
}

/**********************************************************************************
 *   Function Name  : nodeTransform
 *   Purpose : Convert a glTF node's matrix or TRS properties into a 4x4 matrix.
 *
 **********************************************************************************/
static M4 nodeTransform(const tinygltf::Node &node)
{
    if (node.matrix.size() == 16)
    {
        M4 m{};
        for (int i = 0; i < 16; i++)
            m.m[i] = (float)node.matrix[i];
        return m;
    }
    M4 m = identity();
    V3 t = {0, 0, 0}, s = {1, 1, 1};
    double x = 0, y = 0, z = 0, w = 1;
    if (node.translation.size() == 3)
        t = {(float)node.translation[0], (float)node.translation[1], (float)node.translation[2]};
    if (node.scale.size() == 3)
        s = {(float)node.scale[0], (float)node.scale[1], (float)node.scale[2]};
    if (node.rotation.size() == 4)
    {
        x = node.rotation[0];
        y = node.rotation[1];
        z = node.rotation[2];
        w = node.rotation[3];
    }
    m.m[0] = (float)(1 - 2 * (y * y + z * z)) * s.x;
    m.m[1] = (float)(2 * (x * y + z * w)) * s.x;
    m.m[2] = (float)(2 * (x * z - y * w)) * s.x;
    m.m[4] = (float)(2 * (x * y - z * w)) * s.y;
    m.m[5] = (float)(1 - 2 * (x * x + z * z)) * s.y;
    m.m[6] = (float)(2 * (y * z + x * w)) * s.y;
    m.m[8] = (float)(2 * (x * z + y * w)) * s.z;
    m.m[9] = (float)(2 * (y * z - x * w)) * s.z;
    m.m[10] = (float)(1 - 2 * (x * x + y * y)) * s.z;
    m.m[12] = t.x;
    m.m[13] = t.y;
    m.m[14] = t.z;
    return m;
}

/**********************************************************************************
 *   Function Name  : componentSize
 *   Purpose : Return the byte width of a supported glTF accessor component type.
 *
 **********************************************************************************/
static int componentSize(int type)
{
    switch (type)
    {
    case TINYGLTF_COMPONENT_TYPE_BYTE:
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE:
        return 1;
    case TINYGLTF_COMPONENT_TYPE_SHORT:
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT:
        return 2;
    case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT:
    case TINYGLTF_COMPONENT_TYPE_FLOAT:
        return 4;
    default:
        return 0;
    }
}

/**********************************************************************************
 *   Function Name  : accessorBytes
 *   Purpose : Validate a glTF accessor and expose its data pointer and byte stride.
 *
 **********************************************************************************/
static bool accessorBytes(const tinygltf::Model &model, const tinygltf::Accessor &accessor,
                          const unsigned char *&data, size_t &stride, std::string &error)
{
    if (accessor.sparse.isSparse)
    {
        error = "Sparse glTF accessors are not supported.";
        return false;
    }
    if (accessor.bufferView < 0 || accessor.bufferView >= (int)model.bufferViews.size())
    {
        error = "glTF accessor has no valid buffer view.";
        return false;
    }
    const auto &view = model.bufferViews[accessor.bufferView];
    if (view.buffer < 0 || view.buffer >= (int)model.buffers.size())
    {
        error = "glTF buffer view references an invalid buffer.";
        return false;
    }
    int size = componentSize(accessor.componentType),
        components = accessor.type == TINYGLTF_TYPE_VEC3     ? 3
                     : accessor.type == TINYGLTF_TYPE_SCALAR ? 1
                                                             : 0;
    if (!size || !components)
    {
        error = "Unsupported glTF accessor type.";
        return false;
    }
    size_t element = (size_t)size * components;
    stride = view.byteStride ? (size_t)view.byteStride : element;
    if (stride < element)
    {
        error = "Invalid glTF accessor stride.";
        return false;
    }
    const auto &bytes = model.buffers[view.buffer].data;
    if (view.byteOffset > bytes.size() || view.byteLength > bytes.size() - view.byteOffset ||
        accessor.byteOffset > view.byteLength)
    {
        error = "glTF accessor exceeds its buffer.";
        return false;
    }
    size_t available = view.byteLength - accessor.byteOffset;
    if (element > available ||
        (accessor.count && accessor.count - 1 > (available - element) / stride))
    {
        error = "glTF accessor exceeds its buffer view.";
        return false;
    }
    size_t offset = view.byteOffset + accessor.byteOffset;
    data = bytes.empty() ? nullptr : bytes.data() + offset;
    return true;
}

/**********************************************************************************
 *   Function Name  : appendTriangle
 *   Purpose : Append triangle vertices, selecting supplied or generated face normals.
 *
 **********************************************************************************/
static void appendTriangle(const V3 p[3], const V3 n[3], const bool hasNormal[3],
                           std::vector<float> &vertices, std::vector<uint32_t> &indices)
{
    V3 face = norm(cross(p[1] - p[0], p[2] - p[0]));
    for (int i = 0; i < 3; i++)
    {
        V3 normal = hasNormal[i] ? norm(n[i]) : face;
        if (dot(normal, normal) < 1e-10f)
            normal = face;
        uint32_t idx = (uint32_t)(vertices.size() / 6);
        vertices.insert(vertices.end(), {p[i].x, p[i].y, p[i].z, normal.x, normal.y, normal.z});
        indices.push_back(idx);
    }
}

/**********************************************************************************
 *   Function Name  : normalizeModel
 *   Purpose : Validate model coordinates and center and scale the geometry for viewing.
 *
 **********************************************************************************/
static bool normalizeModel(std::vector<float> &vertices, std::string &error)
{
    if (vertices.size() < 18)
    {
        error = "The model contains no triangle geometry.";
        return false;
    }
    V3 lo = {vertices[0], vertices[1], vertices[2]}, hi = lo;
    for (size_t i = 0; i < vertices.size(); i += 6)
        for (int c = 0; c < 3; c++)
        {
            float value = vertices[i + c];
            if (!std::isfinite(value))
            {
                error = "The model contains non-finite vertex coordinates.";
                return false;
            }
            if (c == 0)
            {
                lo.x = std::min(lo.x, value);
                hi.x = std::max(hi.x, value);
            }
            else if (c == 1)
            {
                lo.y = std::min(lo.y, value);
                hi.y = std::max(hi.y, value);
            }
            else
            {
                lo.z = std::min(lo.z, value);
                hi.z = std::max(hi.z, value);
            }
        }
    V3 center = (lo + hi) * .5f;
    float radius = 0;
    for (size_t i = 0; i < vertices.size(); i += 6)
    {
        V3 p = {vertices[i], vertices[i + 1], vertices[i + 2]};
        radius = std::max(radius, std::sqrt(dot(p - center, p - center)));
    }
    if (!std::isfinite(radius) || radius < 1e-8f)
    {
        error = "The model has zero or invalid bounds.";
        return false;
    }
    float scale = .9f / radius;
    for (size_t i = 0; i < vertices.size(); i += 6)
    {
        vertices[i] = (vertices[i] - center.x) * scale;
        vertices[i + 1] = (vertices[i + 1] - center.y) * scale;
        vertices[i + 2] = (vertices[i + 2] - center.z) * scale;
    }
    return true;
}

/**********************************************************************************
 *   Function Name  : loadObj
 *   Purpose : Parse OBJ geometry, triangulate faces, and normalize the resulting mesh.
 *
 **********************************************************************************/
static bool loadObj(const std::string &path, std::vector<float> &vertices,
                    std::vector<uint32_t> &indices, std::string &warning, std::string &error)
{
    tinyobj::ObjReaderConfig config;
    config.triangulate = true;
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(path, config))
    {
        error = reader.Error().empty() ? "Failed to parse OBJ file." : reader.Error();
        return false;
    }
    warning = reader.Warning();
    const auto &attrib = reader.GetAttrib();
    for (const auto &shape : reader.GetShapes())
    {
        size_t offset = 0;
        for (unsigned char faceSize : shape.mesh.num_face_vertices)
        {
            if (faceSize < 3 || offset + faceSize > shape.mesh.indices.size())
            {
                error = "OBJ contains an invalid face.";
                return false;
            }

            /**********************************************************************************
             *   Function Name  : position
             *   Purpose : Read and validate a vertex position from an OBJ index.
             *
             **********************************************************************************/
            auto position = [&](const tinyobj::index_t &idx, V3 &out) -> bool
            {
                if (idx.vertex_index < 0 ||
                    (size_t)(idx.vertex_index * 3 + 2) >= attrib.vertices.size())
                    return false;
                out = {attrib.vertices[3 * idx.vertex_index],
                       attrib.vertices[3 * idx.vertex_index + 1],
                       attrib.vertices[3 * idx.vertex_index + 2]};
                return true;
            };
            for (size_t tri = 1; tri + 1 < faceSize; tri++)
            {
                tinyobj::index_t face[3] = {shape.mesh.indices[offset],
                                            shape.mesh.indices[offset + tri],
                                            shape.mesh.indices[offset + tri + 1]};
                V3 p[3], n[3]{};
                bool hasN[3]{};
                for (int k = 0; k < 3; k++)
                {
                    if (!position(face[k], p[k]))
                    {
                        error = "OBJ contains an invalid vertex index.";
                        return false;
                    }
                    int ni = face[k].normal_index;
                    if (ni >= 0 && (size_t)(ni * 3 + 2) < attrib.normals.size())
                    {
                        n[k] = {attrib.normals[3 * ni], attrib.normals[3 * ni + 1],
                                attrib.normals[3 * ni + 2]};
                        hasN[k] = true;
                    }
                }
                appendTriangle(p, n, hasN, vertices, indices);
            }
            offset += faceSize;
        }
    }
    return normalizeModel(vertices, error);
}

/**********************************************************************************
 *   Function Name  : appendGltfPrimitive
 *   Purpose : Convert a supported glTF triangle primitive into transformed mesh data.
 *
 **********************************************************************************/
static bool appendGltfPrimitive(const tinygltf::Model &model, const tinygltf::Primitive &primitive,
                                const M4 &world, std::vector<float> &vertices,
                                std::vector<uint32_t> &indices, std::string &error)
{
    if (primitive.mode != -1 && primitive.mode != TINYGLTF_MODE_TRIANGLES)
    {
        error = "Only triangle glTF primitives are supported.";
        return false;
    }
    auto posIt = primitive.attributes.find("POSITION");
    if (posIt == primitive.attributes.end() || posIt->second < 0 ||
        posIt->second >= (int)model.accessors.size())
    {
        error = "glTF primitive has no valid POSITION accessor.";
        return false;
    }
    const auto &pa = model.accessors[posIt->second];
    if (pa.type != TINYGLTF_TYPE_VEC3 || pa.componentType != TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        error = "glTF POSITION must use FLOAT VEC3.";
        return false;
    }
    const unsigned char *posData = nullptr;
    size_t posStride = 0;
    if (!accessorBytes(model, pa, posData, posStride, error))
        return false;
    const tinygltf::Accessor *na = nullptr;
    const unsigned char *normalData = nullptr;
    size_t normalStride = 0;
    auto normalIt = primitive.attributes.find("NORMAL");
    if (normalIt != primitive.attributes.end())
    {
        if (normalIt->second < 0 || normalIt->second >= (int)model.accessors.size())
        {
            error = "glTF primitive has an invalid NORMAL accessor.";
            return false;
        }
        na = &model.accessors[normalIt->second];
        if (na->type != TINYGLTF_TYPE_VEC3 || na->componentType != TINYGLTF_COMPONENT_TYPE_FLOAT)
        {
            error = "glTF NORMAL must use FLOAT VEC3.";
            return false;
        }
        if (!accessorBytes(model, *na, normalData, normalStride, error))
            return false;
    }
    std::vector<uint32_t> primitiveIndices;
    if (primitive.indices >= 0)
    {
        if (primitive.indices >= (int)model.accessors.size())
        {
            error = "glTF primitive has an invalid index accessor.";
            return false;
        }
        const auto &ia = model.accessors[primitive.indices];
        if (ia.type != TINYGLTF_TYPE_SCALAR)
        {
            error = "glTF indices must use SCALAR.";
            return false;
        }
        const unsigned char *indexData = nullptr;
        size_t indexStride = 0;
        if (!accessorBytes(model, ia, indexData, indexStride, error))
            return false;
        if (ia.componentType != TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE &&
            ia.componentType != TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT &&
            ia.componentType != TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
        {
            error = "Unsupported glTF index component type.";
            return false;
        }
        primitiveIndices.resize(ia.count);
        for (size_t i = 0; i < ia.count; i++)
        {
            const unsigned char *q = indexData + i * indexStride;
            if (ia.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE)
                primitiveIndices[i] = *q;
            else if (ia.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT)
            {
                uint16_t v;
                std::memcpy(&v, q, sizeof(v));
                primitiveIndices[i] = v;
            }
            else
                std::memcpy(&primitiveIndices[i], q, sizeof(uint32_t));
        }
    }
    else
    {
        if (pa.count > UINT32_MAX)
        {
            error = "glTF primitive has too many vertices.";
            return false;
        }
        primitiveIndices.resize(pa.count);
        for (size_t i = 0; i < pa.count; i++)
            primitiveIndices[i] = (uint32_t)i;
    }
    if (primitiveIndices.empty() || primitiveIndices.size() % 3 != 0)
    {
        error = "glTF triangle index count is invalid.";
        return false;
    }
    for (size_t i = 0; i < primitiveIndices.size(); i += 3)
    {
        V3 p[3], n[3]{};
        bool hasN[3]{};
        for (int k = 0; k < 3; k++)
        {
            uint32_t vi = primitiveIndices[i + k];
            if (vi >= pa.count)
            {
                error = "glTF index exceeds POSITION accessor.";
                return false;
            }
            float values[3];
            std::memcpy(values, posData + (size_t)vi * posStride, sizeof(values));
            p[k] = transformPoint(world, {values[0], values[1], values[2]});
            if (na && vi < na->count)
            {
                float normal[3];
                std::memcpy(normal, normalData + (size_t)vi * normalStride, sizeof(normal));
                n[k] = transformNormal(world, {normal[0], normal[1], normal[2]});
                hasN[k] = dot(n[k], n[k]) > 1e-10f;
            }
        }
        appendTriangle(p, n, hasN, vertices, indices);
    }
    return true;
}

/**********************************************************************************
 *   Function Name  : loadGltf
 *   Purpose : Load glTF/GLB scenes, traverse node transforms, and normalize their meshes.
 *
 **********************************************************************************/
static bool loadGltf(const std::string &path, std::vector<float> &vertices,
                     std::vector<uint32_t> &indices, std::string &warning, std::string &error)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err, warn;
    std::string ext = path.substr(
        path.find_last_of('.') == std::string::npos ? path.size() : path.find_last_of('.'));

    /**********************************************************************************
     *   Function Name  : lowercase extension transform
     *   Purpose : Normalize the glTF file extension for format selection.
     *
     **********************************************************************************/
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c)
                   {
                       return (char)std::tolower(c);
                   });
    bool ok = ext == ".glb" ? loader.LoadBinaryFromFile(&model, &err, &warn, path)
                            : loader.LoadASCIIFromFile(&model, &err, &warn, path);
    if (!ok)
    {
        error = err.empty() ? "Failed to parse glTF file." : err;
        return false;
    }
    warning = warn;
    if (model.meshes.empty())
    {
        error = "glTF file contains no meshes.";
        return false;
    }

    /**********************************************************************************
     *   Function Name  : loadMesh
     *   Purpose : Append all validated primitives from a glTF mesh to the output geometry.
     *
     **********************************************************************************/
    auto loadMesh = [&](int meshIndex, const M4 &world) -> bool
    {
        if (meshIndex < 0 || meshIndex >= (int)model.meshes.size())
        {
            error = "glTF node references an invalid mesh.";
            return false;
        }
        for (const auto &primitive : model.meshes[meshIndex].primitives)
            if (!appendGltfPrimitive(model, primitive, world, vertices, indices, error))
                return false;
        return true;
    };
    std::vector<bool> active(model.nodes.size(), false);

    /**********************************************************************************
     *   Function Name  : visit
     *   Purpose : Recursively traverse glTF nodes and append meshes using world transforms.
     *
     **********************************************************************************/
    std::function<bool(int, const M4 &)> visit = [&](int nodeIndex, const M4 &parent) -> bool
    {
        if (nodeIndex < 0 || nodeIndex >= (int)model.nodes.size())
        {
            error = "glTF scene references an invalid node.";
            return false;
        }
        if (active[nodeIndex])
        {
            error = "glTF node hierarchy contains a cycle.";
            return false;
        }
        active[nodeIndex] = true;
        const auto &node = model.nodes[nodeIndex];
        M4 world = multiply(parent, nodeTransform(node));
        if (node.mesh >= 0 && !loadMesh(node.mesh, world))
        {
            active[nodeIndex] = false;
            return false;
        }
        for (int child : node.children)
            if (!visit(child, world))
            {
                active[nodeIndex] = false;
                return false;
            }
        active[nodeIndex] = false;
        return true;
    };
    if (!model.scenes.empty())
    {
        int sceneIndex = model.defaultScene >= 0 ? model.defaultScene : 0;
        if (sceneIndex >= (int)model.scenes.size())
        {
            error = "glTF default scene index is invalid.";
            return false;
        }
        for (int node : model.scenes[sceneIndex].nodes)
            if (!visit(node, identity()))
                return false;
    }
    else if (!model.nodes.empty())
    {
        std::vector<bool> child(model.nodes.size(), false);
        for (const auto &node : model.nodes)
            for (int i : node.children)
                if (i >= 0 && i < (int)child.size())
                    child[i] = true;
        for (size_t i = 0; i < child.size(); i++)
            if (!child[i] && !visit((int)i, identity()))
                return false;
    }
    else
    {
        for (size_t i = 0; i < model.meshes.size(); i++)
            if (!loadMesh((int)i, identity()))
                return false;
    }
    return normalizeModel(vertices, error);
}

/**********************************************************************************
 *   Function Name  : loadModel
 *   Purpose : Dispatch a model file to its format loader and upload the resulting mesh.
 *
 **********************************************************************************/
static bool loadModel(const std::string &path, Mesh &result, std::string &warning,
                      std::string &error)
{
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    size_t dotPos = path.find_last_of('.');
    if (dotPos == std::string::npos)
    {
        error = "Choose an OBJ, glTF, or GLB file.";
        return false;
    }
    std::string ext = path.substr(dotPos);

    /**********************************************************************************
     *   Function Name  : lowercase extension transform
     *   Purpose : Normalize the model file extension before choosing a loader.
     *
     **********************************************************************************/
    std::transform(ext.begin(), ext.end(), ext.begin(),
                   [](unsigned char c)
                   {
                       return (char)std::tolower(c);
                   });
    bool ok = ext == ".obj" ? loadObj(path, vertices, indices, warning, error)
              : (ext == ".gltf" || ext == ".glb")
                  ? loadGltf(path, vertices, indices, warning, error)
                  : false;
    if (!ok)
    {
        if (ext != ".obj" && ext != ".gltf" && ext != ".glb")
            error = "Unsupported model format. Select .obj, .gltf, or .glb.";
        return false;
    }
    result = uploadMesh(vertices, indices);
    if (!result.vao)
    {
        destroyMesh(result);
        error = "Could not upload model geometry to OpenGL.";
        return false;
    }
    return true;
}

static HWND hwnd;
static HDC dc;
static HGLRC context;
static int width = 1280, height = 720, mode = 2, colorIndex = 0, drawCalls = 0;
static float thickness = 6, yaw = .7853982f, pitch = .3217506f;
static constexpr float cameraDistance = 2.25f;
static float imagePanX = 0, imagePanY = 0, imageZoom = 1;
static bool alive = true, drag = false, panDrag = false, inside = false, rotate = true,
            imguiInitialized = false;
static POINT mouse;
static bool disableFsaa = false;
static GLuint litProgram, maskProgram, seedProgram, seedQuadProgram, expandProgram, jfaProgram,
    effectProgram, quadVao;
static Mesh mesh;
static Target field[2], mask[2];
static Target presentationTarget;
static MultisampleTarget multisampleOutput;
static std::string modelName = "Procedural torus knot (demo fallback)";
static std::string modelStatus = "Ready.";
static bool modelLoadFailed = false;
static const char *names[] = {"Mask", "Coordinate", "SDF",      "Outline",
                              "Glow", "Pulse",      "Halftone", "Rings"};
static float colors[][3] = {
    {.914f, .118f, .388f}, {0, .737f, .831f}, {1, .757f, .027f}, {.545f, .765f, .290f}, {1, 1, 1}};

/**********************************************************************************
 *   Function Name  : setViewUniforms
 *   Purpose : Set the fixed camera projection and screen-space pan/zoom parameters.
 *
 **********************************************************************************/
static void setViewUniforms(GLuint p, const M4 &viewProj)
{
    glUniformMatrix4fv(loc(p, "viewProj"), 1, GL_FALSE, viewProj.m);
    glUniform2f(loc(p, "viewportSize"), (GLfloat)width, (GLfloat)height);
    glUniform2f(loc(p, "imagePan"), imagePanX, imagePanY);
    u1f(p, "imageZoom", imageZoom);
}

/**********************************************************************************
 *   Function Name  : glDebug
 *   Purpose : Report OpenGL errors found at the beginning or end of a render pass.
 *
 **********************************************************************************/
static void glDebug(const char *pass, const char *phase)
{
    GLenum error = GL_NO_ERROR;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        char message[256];
        snprintf(message, sizeof(message), "OpenGL error 0x%04X at %s of %s pass.\n", error, phase,
                 pass);
        OutputDebugStringA(message);
    }
}

/**********************************************************************************
 *   Function Name  : drawMesh
 *   Purpose : Draw the active indexed mesh and update the draw-call counter.
 *
 **********************************************************************************/
static void drawMesh()
{
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.count, GL_UNSIGNED_INT, nullptr);
    drawCalls++;
}

/**********************************************************************************
 *   Function Name  : drawQuad
 *   Purpose : Draw the full-screen triangle and update the draw-call counter.
 *
 **********************************************************************************/
static void drawQuad()
{
    glBindVertexArray(quadVao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    drawCalls++;
}

/**********************************************************************************
 *   Function Name  : texture
 *   Purpose : Bind a 2D texture to the selected OpenGL texture unit.
 *
 **********************************************************************************/
static void texture(int unit, GLuint t)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, t);
}

/**********************************************************************************
 *   Function Name  : resize
 *   Purpose : Update the viewport dimensions and resize the full-resolution render targets.
 *
 **********************************************************************************/
static void resize(int w, int h)
{
    width = std::max(w, 1);
    height = std::max(h, 1);
    presentationTarget.resize(width, height);
    field[0].resize(width, height);
    field[1].resize(width, height);
    multisampleOutput.resize(width, height);
}

/**********************************************************************************
 *   Function Name  : renderScenePass
 *   Purpose : Draw the lit model into the selected scene framebuffer.
 *
 **********************************************************************************/
static void renderScenePass(const M4 &viewProj, V3 light, bool useFbo)
{
    glDebug("scene", "beginning");
    if (useFbo)
        multisampleOutput.bind();
    else
        presentationTarget.bind();
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(.529f, .529f, .529f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(litProgram);
    setViewUniforms(litProgram, viewProj);
    glUniform3f(loc(litProgram, "lightDir"), light.x, light.y, light.z);
    drawMesh();
    glDebug("scene", "end");
}

/**********************************************************************************
 *   Function Name  : renderMaskPass
 *   Purpose : Render the mesh silhouette into the low-resolution mask framebuffer.
 *
 **********************************************************************************/
static void renderMaskPass(const M4 &viewProj)
{
    glDebug("mask", "beginning");
    int maskWidth = std::max((int)std::floor(width / thickness), 3);
    int maskHeight = std::max((int)std::floor(height / thickness), 3);
    mask[0].resize(maskWidth, maskHeight);
    mask[1].resize(maskWidth, maskHeight);
    mask[0].bind();
    glDisable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(maskProgram);
    setViewUniforms(maskProgram, viewProj);
    drawMesh();
    glDebug("mask", "end");
}

/**********************************************************************************
 *   Function Name  : expandMaskPass
 *   Purpose : Expand the silhouette mask by four neighboring-texel passes.
 *
 **********************************************************************************/
static int expandMaskPass(int maskSource)
{
    glDebug("mask expansion", "beginning");
    glUseProgram(expandProgram);
    u1i(expandProgram, "source", 0);
    texture(0, mask[maskSource].tex);
    mask[1 - maskSource].bind();
    drawQuad();
    const int expandedMaskSource = 1 - maskSource;
    glDebug("mask expansion", "end");
    return expandedMaskSource;
}

/**********************************************************************************
 *   Function Name  : renderSeedPass
 *   Purpose : Initialize the signed distance field and draw the mesh seed.
 *
 **********************************************************************************/
static void renderSeedPass(const M4 &viewProj)
{
    glDebug("seed", "beginning");
    field[0].bind();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClearDepth(1);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(seedQuadProgram);
    glDisable(GL_DEPTH_TEST);
    drawQuad();
    glEnable(GL_DEPTH_TEST);
    glUseProgram(seedProgram);
    setViewUniforms(seedProgram, viewProj);
    u1i(seedProgram, "negative", -1);
    drawMesh();
    glDebug("seed", "end");
}

/**********************************************************************************
 *   Function Name  : jumpFloodPass
 *   Purpose : Propagate nearest signed-distance seeds across ping-pong FBOs.
 *
 **********************************************************************************/
static int jumpFloodPass(GLuint maskTexture)
{
    glDebug("jump flood", "beginning");
    int source = 0;
    int step = std::min(std::max(width, height), (int)thickness);
    glDisable(GL_DEPTH_TEST);
    glUseProgram(jfaProgram);
    u1i(jfaProgram, "source", 0);
    u1i(jfaProgram, "mask", 1);
    for (;;)
    {
        glDebug("jump flood iteration", "beginning");
        u1i(jfaProgram, "step", step);
        texture(0, field[source].tex);
        texture(1, maskTexture);
        field[1 - source].bind();
        drawQuad();
        glDebug("jump flood iteration", "end");
        source = 1 - source;
        if (step <= 1)
            break;
        step = (int)std::ceil(step * .5f);
    }
    glDebug("jump flood", "end");
    return source;
}

/**********************************************************************************
 *   Function Name  : renderEffectPass
 *   Purpose : Composite the selected distance-field effect over the scene FBO.
 *
 **********************************************************************************/
static void renderEffectPass(float time, GLuint maskTexture, int fieldSource, bool useFbo)
{
    glDebug("effect", "beginning");
    if (useFbo)
        multisampleOutput.bind();
    else
        presentationTarget.bind();
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(effectProgram);
    texture(0, field[fieldSource].tex);
    texture(1, maskTexture);
    u1i(effectProgram, "map", 0);
    u1i(effectProgram, "mask", 1);
    u1f(effectProgram, "time", time);
    u1f(effectProgram, "thickness", thickness);
    u1i(effectProgram, "mode", mode);
    u1i(effectProgram, "inside", inside ? -1 : 1);
    const float *color = colors[colorIndex];
    glUniform3f(loc(effectProgram, "color"), color[0], color[1], color[2]);
    drawQuad();
    glDisable(GL_BLEND);
    glActiveTexture(GL_TEXTURE0);
    glDebug("effect", "end");
}

/**********************************************************************************
 *   Function Name  : resolvePass
 *   Purpose : Resolve multisample color into the single-sample presentation FBO.
 *
 **********************************************************************************/
static void resolvePass()
{
    if (!multisampleOutput.available() || disableFsaa)
        return;
    glDebug("resolve", "beginning");
    glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampleOutput.fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, presentationTarget.fbo);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, presentationTarget.fbo);
    glDebug("resolve", "end");
}

/**********************************************************************************
 *   Function Name  : render
 *   Purpose : Execute the scene, mask, seed, jump-flood, effect, and resolve passes.
 *
 **********************************************************************************/
static void render(float time)
{
    drawCalls = 0;
    V3 eye = {cameraDistance * std::cos(pitch) * std::sin(yaw), cameraDistance * std::sin(pitch),
              cameraDistance * std::cos(pitch) * std::cos(yaw)};
    M4 viewProj = multiply(perspective(45, (float)width / height, .25f, 20),
                           lookAt(eye, {0, 0, 0}, {0, 1, 0}));
    V3 light = norm(eye + V3{.3f, .8f, 0});
    const bool useFbo = !disableFsaa && multisampleOutput.available();
    renderScenePass(viewProj, light, useFbo);
    renderMaskPass(viewProj);
    int maskSource = 0;
    for (int i = 0; i < 4; i++)
        maskSource = expandMaskPass(maskSource);
    const GLuint maskTexture = mask[maskSource].tex;
    renderSeedPass(viewProj);
    const int fieldSource = jumpFloodPass(maskTexture);
    renderEffectPass(time, maskTexture, fieldSource, useFbo);
    resolvePass();
}

/**********************************************************************************
 *   Function Name  : renderUi
 *   Purpose : Draw the ImGui controls and current render statistics.
 *
 **********************************************************************************/
static void renderUi(float frameMs)
{
    glDebug("UI", "beginning");
    presentationTarget.bind();
    glDisable(GL_DEPTH_TEST);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::SetNextWindowPos(ImVec2(12, 12), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(340, 0), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Jump Flood Effects"))
    {
        if (ImGui::Button("Load OBJ / glTF / GLB..."))
        {
            char path[32768] = {};
            OPENFILENAMEA dialog{};
            dialog.lStructSize = sizeof(dialog);
            dialog.hwndOwner = hwnd;
            dialog.lpstrFilter =
                "3D models (*.obj;*.gltf;*.glb)\0*.obj;*.gltf;*.glb\0All files (*.*)\0*.*\0";
            dialog.lpstrFile = path;
            dialog.nMaxFile = (DWORD)sizeof(path);
            dialog.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
            if (GetOpenFileNameA(&dialog))
            {
                Mesh candidate{};
                std::string warning, error;
                if (loadModel(path, candidate, warning, error))
                {
                    destroyMesh(mesh);
                    mesh = candidate;
                    modelName = path;
                    modelStatus =
                        warning.empty() ? "Model loaded." : "Model loaded with warning: " + warning;
                    modelLoadFailed = false;
                }
                else
                {
                    modelStatus = "Model load failed: " +
                                  (error.empty() ? std::string("Unknown loader error.") : error);
                    modelLoadFailed = true;
                }
            }
        }
        ImGui::TextWrapped("Model: %s", modelName.c_str());
        ImGui::PushStyleColor(ImGuiCol_Text, modelLoadFailed ? ImVec4(1.0f, .35f, .35f, 1.0f)
                                                             : ImVec4(.55f, .85f, .55f, 1.0f));
        ImGui::TextWrapped("%s", modelStatus.c_str());
        ImGui::PopStyleColor();
        ImGui::TextDisabled(
            "Geometry only: materials, textures, and HDR environment lighting are not rendered.");
        ImGui::Separator();
        int modeIndex = mode + 1;
        if (ImGui::Combo("Effect", &modeIndex, names, IM_ARRAYSIZE(names)))
            mode = modeIndex - 1;
        ImGui::Checkbox("Inside", &inside);
        ImGui::SliderFloat("Thickness", &thickness, 1.0f, 250.0f, "%.2f");
        ImGui::ColorEdit3("Effect color", colors[colorIndex]);
        ImGui::Checkbox("Auto-rotate", &rotate);
        if (multisampleOutput.available())
        {
            ImGui::Checkbox("Disable FSAA", &disableFsaa);
        }
        else
        {
            ImGui::TextDisabled("FSAA unavailable (multisampling is unsupported)");
        }
        ImGui::Separator();
        ImGui::Text("Frame: %.2f ms (%.1f FPS)", frameMs, frameMs > 0 ? 1000.0f / frameMs : 0.0f);
        ImGui::Text("Draw calls: %d", drawCalls);
        ImGui::TextDisabled("Drag to orbit | Wheel to zoom | C cycles color | Esc exits");
    }
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glDebug("UI", "end");
}

/**********************************************************************************
 *   Function Name  : presentPass
 *   Purpose : Blit the completed presentation FBO to the window back buffer.
 *
 **********************************************************************************/
static void presentPass()
{
    glDebug("presentation", "beginning");
    glBindFramebuffer(GL_READ_FRAMEBUFFER, presentationTarget.fbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDebug("presentation", "end");
}

/**********************************************************************************
 *   Function Name  : windowResize
 *   Purpose : Resize render targets after the window's client area changes.
 *
 **********************************************************************************/
static void windowResize(int w, int h)
{
    if (context && w > 0 && h > 0)
        resize(w, h);
}

/**********************************************************************************
 *   Function Name  : wndProc
 *   Purpose : Handle ImGui input, window events, and application controls.
 *
 **********************************************************************************/
static LRESULT CALLBACK wndProc(HWND w, UINT msg, WPARAM wp, LPARAM lp)
{
    if (imguiInitialized && ImGui_ImplWin32_WndProcHandler(w, msg, wp, lp))
        return 1;
    if (imguiInitialized && ImGui::GetCurrentContext())
    {
        ImGuiIO &io = ImGui::GetIO();
        const bool mouseMessage = msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP ||
                                  msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP ||
                                  msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP ||
                                  msg == WM_MOUSEMOVE || msg == WM_MOUSEWHEEL;
        const bool keyboardMessage = msg == WM_KEYDOWN || msg == WM_KEYUP || msg == WM_CHAR;
        if ((mouseMessage && io.WantCaptureMouse) || (keyboardMessage && io.WantCaptureKeyboard))
            return 0;
    }
    switch (msg)
    {
    case WM_SIZE:
        if (wp != SIZE_MINIMIZED)
            windowResize(LOWORD(lp), HIWORD(lp));
        return 0;
    case WM_LBUTTONDOWN:
        drag = true;
        GetCursorPos(&mouse);
        SetCapture(w);
        return 0;
    case WM_LBUTTONUP:
        drag = false;
        ReleaseCapture();
        return 0;
    case WM_RBUTTONDOWN:
        panDrag = true;
        GetCursorPos(&mouse);
        SetCapture(w);
        return 0;
    case WM_RBUTTONUP:
        panDrag = false;
        ReleaseCapture();
        return 0;
    case WM_MOUSEMOVE:
        if (drag)
        {
            POINT p;
            GetCursorPos(&p);
            yaw -= (p.x - mouse.x) * .01f;
            pitch = std::clamp(pitch + (p.y - mouse.y) * .01f, -1.5f, 1.5f);
            mouse = p;
        }
        else if (panDrag)
        {
            POINT p;
            GetCursorPos(&p);
            imagePanX += (float)(p.x - mouse.x);
            imagePanY += (float)(p.y - mouse.y);
            mouse = p;
        }
        return 0;
    case WM_MOUSEWHEEL:
        imageZoom = std::clamp(
            imageZoom * std::pow(1.0f / .9f, GET_WHEEL_DELTA_WPARAM(wp) / (float)WHEEL_DELTA), .25f,
            4.0f);
        return 0;
    case WM_KEYDOWN:
        if (wp == VK_ESCAPE)
            alive = false;
        else if (wp == 'M')
        {
            int index = mode + 1;
            index = (index + ((GetKeyState(VK_SHIFT) & 0x8000) ? 7 : 1)) % 8;
            mode = index - 1;
        }
        else if (wp == 'I')
            inside = !inside;
        else if (wp == 'C')
            colorIndex = (colorIndex + 1) % 5;
        else if (wp == VK_SPACE)
            rotate = !rotate;
        else if (wp == VK_UP)
            thickness =
                std::min(thickness + ((GetKeyState(VK_SHIFT) & 0x8000) ? 2.0f : .25f), 250.0f);
        else if (wp == VK_DOWN)
            thickness =
                std::max(thickness - ((GetKeyState(VK_SHIFT) & 0x8000) ? 2.0f : .25f), 1.0f);
        return 0;
    case WM_CLOSE:
        alive = false;
        return 0;
    case WM_DESTROY:
        if (w == hwnd)
            PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcW(w, msg, wp, lp);
}

/**********************************************************************************
 *   Function Name  : createWindow
 *   Purpose : Create the Win32 window and initialize an OpenGL 3.3 core context.
 *
 **********************************************************************************/
static bool createWindow(HINSTANCE instance)
{
    WNDCLASSW wc{};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = L"GLFromWebGL";
    if (!RegisterClassW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        return false;
    RECT r{0, 0, width, height};
    AdjustWindowRect(&r, WS_OVERLAPPEDWINDOW, FALSE);
    hwnd = CreateWindowW(wc.lpszClassName, L"Jump Flood Algorithm Effects",
                         WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
                         r.right - r.left, r.bottom - r.top, nullptr, nullptr, instance, nullptr);
    if (!hwnd)
        return false;
    dc = GetDC(hwnd);
    if (!dc)
        return false;
    PIXELFORMATDESCRIPTOR pfd{};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pf = ChoosePixelFormat(dc, &pfd);
    if (!pf || !SetPixelFormat(dc, pf, &pfd))
        return false;

    HWND bootstrap =
        CreateWindowW(wc.lpszClassName, L"", 0, 0, 0, 1, 1, nullptr, nullptr, instance, nullptr);
    if (!bootstrap)
        return false;
    HDC bootstrapDc = GetDC(bootstrap);
    if (!bootstrapDc)
    {
        DestroyWindow(bootstrap);
        return false;
    }
    int bootstrapPf = ChoosePixelFormat(bootstrapDc, &pfd);
    if (!bootstrapPf || !SetPixelFormat(bootstrapDc, bootstrapPf, &pfd))
    {
        ReleaseDC(bootstrap, bootstrapDc);
        DestroyWindow(bootstrap);
        return false;
    }
    HGLRC bootstrapContext = wglCreateContext(bootstrapDc);
    if (!bootstrapContext || !wglMakeCurrent(bootstrapDc, bootstrapContext))
    {
        if (bootstrapContext)
            wglDeleteContext(bootstrapContext);
        ReleaseDC(bootstrap, bootstrapDc);
        DestroyWindow(bootstrap);
        return false;
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(bootstrapContext);
    ReleaseDC(bootstrap, bootstrapDc);
    DestroyWindow(bootstrap);

    HGLRC legacy = wglCreateContext(dc);
    if (!legacy || !wglMakeCurrent(dc, legacy))
        return false;
    auto create =
        reinterpret_cast<CreateContextAttribs>(wglGetProcAddress("wglCreateContextAttribsARB"));
    if (!create)
        return false;
    const int attrs[] = {WGL_CONTEXT_MAJOR_VERSION_ARB,
                         3,
                         WGL_CONTEXT_MINOR_VERSION_ARB,
                         3,
                         WGL_CONTEXT_PROFILE_MASK_ARB,
                         WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                         0};
    context = create(dc, nullptr, attrs);
    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(legacy);
    if (!context || !wglMakeCurrent(dc, context) || !loadGL())
        return false;
    auto swap = reinterpret_cast<SwapInterval>(wglGetProcAddress("wglSwapIntervalEXT"));
    if (swap)
        swap(1);
    return true;
}

/**********************************************************************************
 *   Function Name  : wWinMain
 *   Purpose : Initialize the renderer and run the application message/render loop.
 *
 **********************************************************************************/
int WINAPI wWinMain(HINSTANCE instance, HINSTANCE, PWSTR, int)
{
    SetProcessDPIAware();
    if (!createWindow(instance))
    {
        MessageBoxA(nullptr, "Could not create an OpenGL 3.3 core context.", "Startup error",
                    MB_ICONERROR);
        return 1;
    }
    GLint maxSamples = 0;
    glGetIntegerv(GL_MAX_SAMPLES, &maxSamples);
    multisampleOutput.init(maxSamples > 1 ? std::min(4, (int)maxSamples) : 0);
    presentationTarget.init(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, true);
    const std::string modelVS = loadShaderSource(L"model.vert");
    const std::string litFS = loadShaderSource(L"lit.frag");
    const std::string maskFS = loadShaderSource(L"mask.frag");
    const std::string seedFS = loadShaderSource(L"seed.frag");
    const std::string quadVS = loadShaderSource(L"quad.vert");
    const std::string seedQuadFS = loadShaderSource(L"seed_quad.frag");
    const std::string expandFS = loadShaderSource(L"expand.frag");
    const std::string jfaFS = loadShaderSource(L"jfa.frag");
    const std::string effectFS = loadShaderSource(L"effect.frag");
    litProgram = program(modelVS, litFS);
    maskProgram = program(modelVS, maskFS);
    seedProgram = program(modelVS, seedFS);
    seedQuadProgram = program(quadVS, seedQuadFS);
    expandProgram = program(quadVS, expandFS);
    jfaProgram = program(quadVS, jfaFS);
    effectProgram = program(quadVS, effectFS);
    glGenVertexArrays(1, &quadVao);
    mesh = makeMesh();
    field[0].init(GL_RGBA32F, GL_RGBA, GL_FLOAT, true);
    field[1].init(GL_RGBA32F, GL_RGBA, GL_FLOAT);
    mask[0].init(GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    mask[1].init(GL_R8, GL_RED, GL_UNSIGNED_BYTE);
    RECT client{};
    GetClientRect(hwnd, &client);
    resize(client.right, client.bottom);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    if (!ImGui_ImplWin32_InitForOpenGL(hwnd) || !ImGui_ImplOpenGL3_Init("#version 330"))
    {
        MessageBoxA(hwnd, "Dear ImGui initialization failed.", "Startup error", MB_ICONERROR);
        return 1;
    }
    imguiInitialized = true;
    LARGE_INTEGER freq, last, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&last);
    double avgMs = 0, titleTime = 0;
    int sampleCount = 0;
    while (alive)
    {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                alive = false;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (!alive)
            break;
        QueryPerformanceCounter(&now);
        double dt = (now.QuadPart - last.QuadPart) * 1000.0 / freq.QuadPart;
        last = now;
        if (sampleCount)
            avgMs += (dt - avgMs) / (sampleCount + 1);
        if (sampleCount < 60)
            sampleCount++;
        if (rotate && !drag)
            yaw += (float)(dt * .001 * 2 * 3.14159265 / 60);
        render((float)(now.QuadPart * 1000.0 / freq.QuadPart));
        renderUi((float)avgMs);
        presentPass();
        SwapBuffers(dc);
        titleTime += dt;
        if (titleTime > 250 && avgMs > 0)
        {
            titleTime = 0;
            char title[256];
            snprintf(
                title, sizeof(title),
                "JFA Effects | %s%s | thickness %.2f | Draw Calls: %d | Frame: %.2fms | FPS: %.1f",
                names[mode + 1], inside ? " (inside)" : "", thickness, drawCalls, avgMs,
                1000.0 / avgMs);
            SetWindowTextA(hwnd, title);
        }
    }
    if (imguiInitialized)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    if (context)
    {
        wglMakeCurrent(nullptr, nullptr);
        wglDeleteContext(context);
    }
    if (dc)
        ReleaseDC(hwnd, dc);
    return 0;
}

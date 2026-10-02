#include <windows.h>
#include <gl/GL.h>
#include <stddef.h>
#include <math.h>
#include <fstream>
#include <iterator>
#include <string>

#pragma comment(lib, "opengl32.lib")

#define GL_ARRAY_BUFFER 0x8892
#define GL_STATIC_DRAW 0x88E4
#define GL_FLOAT 0x1406
#define GL_FALSE 0
#define GL_TRUE 1
#define GL_VERTEX_SHADER 0x8B31
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_FRAMEBUFFER 0x8D40
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_DEPTH_STENCIL 0x84F9
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_STENCIL_INDEX 0x1901
#define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90EA
#define GL_STENCIL_BUFFER_BIT 0x00000400
#define GL_STENCIL_TEST 0x0B90
#define GL_ALWAYS 0x0207
#define GL_KEEP 0x1E00
#define GL_REPLACE 0x1E01
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RGBA8 0x8058
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT 0x1902
#define GL_UNSIGNED_INT 0x1405
#define GL_TEXTURE_2D 0x0DE1
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB 0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002

typedef char GLchar;
typedef ptrdiff_t GLsizeiptr;
typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
typedef void (APIENTRY* PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY* PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (APIENTRY* PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (APIENTRY* PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY* PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRY* PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const void*, GLenum);
typedef void (APIENTRY* PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef GLuint (APIENTRY* PFNGLCREATESHADERPROC)(GLenum);
typedef void (APIENTRY* PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar* const*, const GLint*);
typedef void (APIENTRY* PFNGLCOMPILESHADERPROC)(GLuint);
typedef void (APIENTRY* PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRY* PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRY* PFNGLDELETESHADERPROC)(GLuint);
typedef GLuint (APIENTRY* PFNGLCREATEPROGRAMPROC)(void);
typedef void (APIENTRY* PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (APIENTRY* PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (APIENTRY* PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (APIENTRY* PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (APIENTRY* PFNGLUSEPROGRAMPROC)(GLuint);
typedef void (APIENTRY* PFNGLDELETEPROGRAMPROC)(GLuint);
typedef GLint (APIENTRY* PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (APIENTRY* PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (APIENTRY* PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (APIENTRY* PFNGLUNIFORM2FPROC)(GLint, GLfloat, GLfloat);
typedef void (APIENTRY* PFNGLUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (APIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (APIENTRY* PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
typedef void (APIENTRY* PFNGLGENFRAMEBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY* PFNGLBINDFRAMEBUFFERPROC)(GLenum, GLuint);
typedef void (APIENTRY* PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei, const GLuint*);
typedef GLenum (APIENTRY* PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
typedef void (APIENTRY* PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRY* PFNGLGENRENDERBUFFERSPROC)(GLsizei, GLuint*);
typedef void (APIENTRY* PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);

typedef void (APIENTRY* PFNGLACTIVETEXTUREPROC)(GLenum);
typedef void (APIENTRY* PFNGLGENERATEMIPMAPPROC)(GLenum);

#define LOAD_GL(name) name = (decltype(name))wglGetProcAddress(#name)

static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
static PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
static PFNGLGENBUFFERSPROC glGenBuffers;
static PFNGLBINDBUFFERPROC glBindBuffer;
static PFNGLBUFFERDATAPROC glBufferData;
static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
static PFNGLCREATESHADERPROC glCreateShader;
static PFNGLSHADERSOURCEPROC glShaderSource;
static PFNGLCOMPILESHADERPROC glCompileShader;
static PFNGLGETSHADERIVPROC glGetShaderiv;
static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
static PFNGLDELETESHADERPROC glDeleteShader;
static PFNGLCREATEPROGRAMPROC glCreateProgram;
static PFNGLATTACHSHADERPROC glAttachShader;
static PFNGLLINKPROGRAMPROC glLinkProgram;
static PFNGLGETPROGRAMIVPROC glGetProgramiv;
static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
static PFNGLUSEPROGRAMPROC glUseProgram;
static PFNGLDELETEPROGRAMPROC glDeleteProgram;
static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
static PFNGLUNIFORM1IPROC glUniform1i;
static PFNGLUNIFORM2FPROC glUniform2f;
static PFNGLUNIFORM4FPROC glUniform4f;
static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
static PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
static PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
static PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;
static PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus;
static PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
static PFNGLACTIVETEXTUREPROC glActiveTexture;

HDC g_deviceContext = 0;
HWND g_window = 0;
static GLuint g_cubeVao = 0;
static GLuint g_cubeVbo = 0;
static GLuint g_cubeProgram = 0;
static GLuint g_screenProgram = 0;
static GLuint g_presentProgram = 0;
static GLuint g_framebuffer = 0;
static GLuint g_colorTexture = 0;
static GLuint g_depthTexture = 0;
static GLuint g_outlineFramebuffer = 0;
static GLuint g_outlineTexture = 0;
static GLint g_cubeMatrix = -1;
static GLint g_cubeModelView = -1;
static GLint g_screenTexture = -1;
static GLint g_screenStencil = -1;
static GLint g_screenTexelSize = -1;
static GLint g_presentTexture = -1;
int g_width = 960;
int g_height = 640;
struct Quaternion { float w, x, y, z; };
static Quaternion g_rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

static const float g_distance = 6.0f;
static float g_fieldOfView = 60.0f;
static float g_backgroundColor[3] = { 1.0f, 1.0f, 1.0f };
static float g_panX = 0.0f;
static float g_panY = 0.0f;
static bool g_rotating = false;
static bool g_panning = false;
static int g_lastMouseX = 0;
static int g_lastMouseY = 0;

static void Fail(const char* message)
{
    MessageBoxA(g_window, message, "OpenGL initialization error", MB_ICONERROR | MB_OK);
}

static void* GetGLProc(const char* name)
{
    void* address = (void*)wglGetProcAddress(name);
    if (address == 0 || address == (void*)0x1 || address == (void*)0x2 || address == (void*)0x3 || address == (void*)-1) {
        HMODULE module = GetModuleHandleA("opengl32.dll");
        address = (void*)GetProcAddress(module, name);
    }
    return address;
}

static bool LoadFunctions(void)
{
#define LOAD_REQUIRED(name) name = (decltype(name))GetGLProc(#name); if (!name) return false
    LOAD_REQUIRED(glGenVertexArrays); LOAD_REQUIRED(glBindVertexArray); LOAD_REQUIRED(glDeleteVertexArrays);
    LOAD_REQUIRED(glGenBuffers); LOAD_REQUIRED(glBindBuffer); LOAD_REQUIRED(glBufferData); LOAD_REQUIRED(glDeleteBuffers);
    LOAD_REQUIRED(glCreateShader); LOAD_REQUIRED(glShaderSource); LOAD_REQUIRED(glCompileShader); LOAD_REQUIRED(glGetShaderiv);
    LOAD_REQUIRED(glGetShaderInfoLog); LOAD_REQUIRED(glDeleteShader); LOAD_REQUIRED(glCreateProgram); LOAD_REQUIRED(glAttachShader);
    LOAD_REQUIRED(glLinkProgram); LOAD_REQUIRED(glGetProgramiv); LOAD_REQUIRED(glGetProgramInfoLog); LOAD_REQUIRED(glUseProgram);
    LOAD_REQUIRED(glDeleteProgram); LOAD_REQUIRED(glGetUniformLocation); LOAD_REQUIRED(glUniformMatrix4fv); LOAD_REQUIRED(glUniform1i); LOAD_REQUIRED(glUniform2f); LOAD_REQUIRED(glUniform4f);
    LOAD_REQUIRED(glEnableVertexAttribArray); LOAD_REQUIRED(glDisableVertexAttribArray); LOAD_REQUIRED(glVertexAttribPointer);
    LOAD_REQUIRED(glGenFramebuffers); LOAD_REQUIRED(glBindFramebuffer); LOAD_REQUIRED(glDeleteFramebuffers);
    LOAD_REQUIRED(glCheckFramebufferStatus); LOAD_REQUIRED(glFramebufferTexture2D); LOAD_REQUIRED(glActiveTexture);
#undef LOAD_REQUIRED
    return true;
}

static GLuint CompileShader(GLenum type, const char* source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    GLint status = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (!status) {
        char log[2048] = {};
        glGetShaderInfoLog(shader, sizeof(log), 0, log);
        MessageBoxA(g_window, log, "Shader compilation failed", MB_ICONERROR | MB_OK);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static GLuint CreateProgram(const char* vertexSource, const char* fragmentSource)
{
    GLuint vertex = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!vertex || !fragment) return 0;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (!status) {
        char log[2048] = {};
        glGetProgramInfoLog(program, sizeof(log), 0, log);
        MessageBoxA(g_window, log, "Program link failed", MB_ICONERROR | MB_OK);
        glDeleteProgram(program);
        return 0;
    }

    return program;
}

static bool LoadShaderSource(const char* filename, std::string& source)
{
    char executablePath[MAX_PATH] = {};
    GetModuleFileNameA(0, executablePath, MAX_PATH);
    std::string executableDirectory(executablePath);
    const size_t separator = executableDirectory.find_last_of("\\/");
    executableDirectory.resize(separator == std::string::npos ? 0 : separator);

    const std::string paths[] = {
        std::string("shaders\\") + filename,
        executableDirectory + "\\shaders\\" + filename,
        executableDirectory + "\\..\\..\\shaders\\" + filename
    };
    for (const std::string& path : paths)
    {
        std::ifstream file(path, std::ios::binary);
        if (file)
        {
            source.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            return true;
        }
    }
    return false;
}

static void Multiply(const float* a, const float* b, float* out);

static void Identity(float* m)
{
    for (int i = 0; i < 16; ++i) m[i] = 0.0f;
    m[0] = m[5] = m[10] = m[15] = 1.0f;
}

static void BuildPerspective(float aspect, float* m)
{
    const float fovRadians = g_fieldOfView * 0.01745329252f;
    const float nearPlane = 0.1f;
    const float farPlane = 100.0f;
    const float focalLength = 1.0f / (float)tan(fovRadians * 0.5f);

    Identity(m);
    m[0] = focalLength / aspect;
    m[5] = focalLength;
    m[8] = g_panX;
    m[9] = g_panY;
    m[10] = (farPlane + nearPlane) / (nearPlane - farPlane);
    m[11] = -1.0f;
    m[14] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);
    m[15] = 0.0f;
}
static Quaternion NormalizeQuaternion(Quaternion q)
{
    const float length = (float)sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    if (length <= 0.000001f) return { 1.0f, 0.0f, 0.0f, 0.0f };
    return { q.w / length, q.x / length, q.y / length, q.z / length };
}

static Quaternion MultiplyQuaternion(Quaternion a, Quaternion b)
{
    return { a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z, a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x, a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w };
}

static Quaternion QuaternionFromAxisAngle(float axisX, float axisY, float axisZ, float radians)
{
    const float halfAngle = radians * 0.5f;
    const float sine = (float)sin(halfAngle);
    return NormalizeQuaternion({ (float)cos(halfAngle), axisX * sine, axisY * sine, axisZ * sine });
}

static void QuaternionToMatrix(Quaternion q, float* m)
{
    q = NormalizeQuaternion(q);
    const float xx = q.x * q.x, yy = q.y * q.y, zz = q.z * q.z;
    const float xy = q.x * q.y, xz = q.x * q.z, yz = q.y * q.z;
    const float wx = q.w * q.x, wy = q.w * q.y, wz = q.w * q.z;
    Identity(m);
    m[0] = 1.0f - 2.0f * (yy + zz); m[1] = 2.0f * (xy + wz); m[2] = 2.0f * (xz - wy);
    m[4] = 2.0f * (xy - wz); m[5] = 1.0f - 2.0f * (xx + zz); m[6] = 2.0f * (yz + wx);
    m[8] = 2.0f * (xz + wy); m[9] = 2.0f * (yz - wx); m[10] = 1.0f - 2.0f * (xx + yy);
}

static void BuildModelView(float* m)
{
    QuaternionToMatrix(g_rotation, m);
    m[12] = 0.0f; m[13] = 0.0f; m[14] = -g_distance; m[15] = 1.0f;
}
static void Multiply(const float* a, const float* b, float* out)
{
    float result[16] = {};
    for (int column = 0; column < 4; ++column) for (int row = 0; row < 4; ++row)
        for (int k = 0; k < 4; ++k) result[column * 4 + row] += a[k * 4 + row] * b[column * 4 + k];
    for (int i = 0; i < 16; ++i) out[i] = result[i];
}

static bool CreateRenderTarget(int width, int height)
{
    if (g_framebuffer) glDeleteFramebuffers(1, &g_framebuffer);
    if (g_outlineFramebuffer) glDeleteFramebuffers(1, &g_outlineFramebuffer);
    if (g_colorTexture) glDeleteTextures(1, &g_colorTexture);
    if (g_depthTexture) glDeleteTextures(1, &g_depthTexture);
    if (g_outlineTexture) glDeleteTextures(1, &g_outlineTexture);

    glGenFramebuffers(1, &g_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
    glGenTextures(1, &g_colorTexture);
    glBindTexture(GL_TEXTURE_2D, g_colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_colorTexture, 0);

    glGenTextures(1, &g_depthTexture);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, g_depthTexture, 0);
    const bool mainComplete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;

    glGenFramebuffers(1, &g_outlineFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
    glGenTextures(1, &g_outlineTexture);
    glBindTexture(GL_TEXTURE_2D, g_outlineTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_outlineTexture, 0);
    const bool outlineComplete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return mainComplete && outlineComplete;
}
bool Renderer_Initialize(void)
{
    if (!LoadFunctions()) { Fail("Required OpenGL 3.3 compatibility functions are unavailable."); return false; }

    std::string cubeVertex, cubeFragment, screenVertex, screenFragment, presentFragment;
    if (!LoadShaderSource("cube.vert", cubeVertex) ||
        !LoadShaderSource("cube.frag", cubeFragment) ||
        !LoadShaderSource("fullscreen.vert", screenVertex) ||
        !LoadShaderSource("outline.frag", screenFragment) ||
        !LoadShaderSource("present.frag", presentFragment))
    {
        Fail("Unable to load shader files from the shaders directory.");
        return false;
    }
    g_cubeProgram = CreateProgram(cubeVertex.c_str(), cubeFragment.c_str());
    g_screenProgram = CreateProgram(screenVertex.c_str(), screenFragment.c_str());
    g_presentProgram = CreateProgram(screenVertex.c_str(), presentFragment.c_str());
    if (!g_cubeProgram || !g_screenProgram || !g_presentProgram) return false;
    g_cubeMatrix = glGetUniformLocation(g_cubeProgram, "mvp");
    g_cubeModelView = glGetUniformLocation(g_cubeProgram, "modelView");
    g_screenTexture = glGetUniformLocation(g_screenProgram, "sceneColor");
    g_screenStencil = glGetUniformLocation(g_screenProgram, "stencilMask");
    g_screenTexelSize = glGetUniformLocation(g_screenProgram, "texelSize");
    g_presentTexture = glGetUniformLocation(g_presentProgram, "screenTexture");

    const float vertices[] = {
        -1,-1,1, 0,0,1,  1,-1,1, 0,0,1,  1,1,1, 0,0,1,  -1,1,1, 0,0,1,
         1,-1,-1, 0,0,-1, -1,-1,-1, 0,0,-1, -1,1,-1, 0,0,-1,  1,1,-1, 0,0,-1,
        -1,-1,-1, -1,0,0, -1,-1,1, -1,0,0, -1,1,1, -1,0,0, -1,1,-1, -1,0,0,
         1,-1,1, 1,0,0,  1,-1,-1, 1,0,0,  1,1,-1, 1,0,0,  1,1,1, 1,0,0,
        -1,1,1, 0,1,0,  1,1,1, 0,1,0,  1,1,-1, 0,1,0, -1,1,-1, 0,1,0,
        -1,-1,-1, 0,-1,0,  1,-1,-1, 0,-1,0,  1,-1,1, 0,-1,0, -1,-1,1, 0,-1,0
    };
    glGenVertexArrays(1, &g_cubeVao); glBindVertexArray(g_cubeVao);
    glGenBuffers(1, &g_cubeVbo); glBindBuffer(GL_ARRAY_BUFFER, g_cubeVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0); glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1); glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    if (!CreateRenderTarget(g_width, g_height)) { Fail("The texture-backed framebuffer is incomplete."); return false; }
    return true;
}

void Renderer_Render(void)
{
    if (g_width <= 0 || g_height <= 0) return;
    glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
    glViewport(0, 0, g_width, g_height);
    glClearColor(g_backgroundColor[0], g_backgroundColor[1], g_backgroundColor[2], 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    float projection[16], modelView[16], mvp[16];
    BuildPerspective((float)g_width / (float)g_height, projection);
    BuildModelView(modelView);
    Multiply(projection, modelView, mvp);
    glUseProgram(g_cubeProgram); glUniformMatrix4fv(g_cubeMatrix, 1, GL_FALSE, mvp); glUniformMatrix4fv(g_cubeModelView, 1, GL_FALSE, modelView);
    glBindVertexArray(g_cubeVao);
    for (int face = 0; face < 6; ++face) glDrawArrays(GL_QUADS, face * 4, 4);

    glDisable(GL_STENCIL_TEST);
    glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
    glViewport(0, 0, g_width, g_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glUseProgram(g_screenProgram);
    glUniform1i(g_screenTexture, 0);
    glUniform1i(g_screenStencil, 1);
    glUniform2f(g_screenTexelSize, 1.0f / (float)g_width, 1.0f / (float)g_height);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_colorTexture);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, g_width, g_height);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(g_presentProgram);
    glUniform1i(g_presentTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_outlineTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}


void Renderer_MouseButton(int button, bool down, int x, int y)
{
    if (button == 0) g_rotating = down;
    if (button == 1) g_panning = down;
    if (down) { g_lastMouseX = x; g_lastMouseY = y; }
}

void Renderer_MouseMove(int x, int y)
{
    const int deltaX = x - g_lastMouseX;
    const int deltaY = y - g_lastMouseY;
    g_lastMouseX = x;
    g_lastMouseY = y;
    if (g_rotating) {
        const float radiansPerPixel = 0.5f * 0.01745329252f;
        const Quaternion yaw = QuaternionFromAxisAngle(0.0f, 1.0f, 0.0f, deltaX * radiansPerPixel);
        const Quaternion pitch = QuaternionFromAxisAngle(1.0f, 0.0f, 0.0f, -deltaY * radiansPerPixel);
        g_rotation = NormalizeQuaternion(MultiplyQuaternion(yaw, MultiplyQuaternion(pitch, g_rotation)));
    }
    if (g_panning) {
        const float width = (float)(g_width > 0 ? g_width : 1);
        const float height = (float)(g_height > 0 ? g_height : 1);
        g_panX -= 2.0f * deltaX / width;
        g_panY -= 2.0f * deltaY / height;    }
}

void Renderer_MouseWheel(int delta)
{
    g_fieldOfView *= (float)pow(0.85, (double)delta / 120.0);
    if (g_fieldOfView < 20.0f) g_fieldOfView = 20.0f;
    if (g_fieldOfView > 90.0f) g_fieldOfView = 90.0f;
}
void Renderer_Resize(int width, int height)
{
    g_width = width > 0 ? width : 1;
    g_height = height > 0 ? height : 1;
    if (g_framebuffer) CreateRenderTarget(g_width, g_height);
}

void Renderer_Shutdown(void)
{
    if (g_cubeVao) glDeleteVertexArrays(1, &g_cubeVao);
    if (g_cubeVbo) glDeleteBuffers(1, &g_cubeVbo);
    if (g_cubeProgram) glDeleteProgram(g_cubeProgram);
    if (g_screenProgram) glDeleteProgram(g_screenProgram);
    if (g_presentProgram) glDeleteProgram(g_presentProgram);
    if (g_framebuffer) glDeleteFramebuffers(1, &g_framebuffer);
    if (g_outlineFramebuffer) glDeleteFramebuffers(1, &g_outlineFramebuffer);
    if (g_colorTexture) glDeleteTextures(1, &g_colorTexture);
    if (g_depthTexture) glDeleteTextures(1, &g_depthTexture);
    if (g_outlineTexture) glDeleteTextures(1, &g_outlineTexture);
}














void Renderer_Present(void)
{
    SwapBuffers(g_deviceContext);
}

void Renderer_SetBackgroundColor(float red, float green, float blue)
{
    g_backgroundColor[0] = red;
    g_backgroundColor[1] = green;
    g_backgroundColor[2] = blue;
}

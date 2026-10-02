// Smoke-test app: renders a lit, textured cube into an FBO (color texture
// + combined depth-stencil texture attachment), then displays that FBO's
// color texture on a full-window quad. Exercises VBOs, index buffers, a
// VAO, 2D textures (with mipmaps), FBOs, and a basic diffuse-lit shader --
// run it with the proxy opengl32.dll copied next to the exe to produce a
// trace, or against the real system DLL to sanity-check it renders.
#include <windows.h>
#include <GL/gl.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

typedef char GLchar;
#if defined(_WIN64)
typedef long long GLsizeiptr;
#else
typedef long GLsizeiptr;
#endif

using PFN_glGenBuffers = void(__stdcall*)(GLsizei, GLuint*);
using PFN_glBindBuffer = void(__stdcall*)(GLenum, GLuint);
using PFN_glBufferData = void(__stdcall*)(GLenum, GLsizeiptr, const void*, GLenum);
using PFN_glCreateShader = GLuint(__stdcall*)(GLenum);
using PFN_glShaderSource = void(__stdcall*)(GLuint, GLsizei, const GLchar* const*, const GLint*);
using PFN_glCompileShader = void(__stdcall*)(GLuint);
using PFN_glGetShaderiv = void(__stdcall*)(GLuint, GLenum, GLint*);
using PFN_glCreateProgram = GLuint(__stdcall*)();
using PFN_glAttachShader = void(__stdcall*)(GLuint, GLuint);
using PFN_glLinkProgram = void(__stdcall*)(GLuint);
using PFN_glGetProgramiv = void(__stdcall*)(GLuint, GLenum, GLint*);
using PFN_glUseProgram = void(__stdcall*)(GLuint);
using PFN_glEnableVertexAttribArray = void(__stdcall*)(GLuint);
using PFN_glVertexAttribPointer = void(__stdcall*)(GLuint, GLint, GLenum, GLboolean, GLsizei, const void*);
using PFN_glDrawArrays = void(__stdcall*)(GLenum, GLint, GLsizei);
using PFN_glDrawElements = void(__stdcall*)(GLenum, GLsizei, GLenum, const void*);
using PFN_glGenVertexArrays = void(__stdcall*)(GLsizei, GLuint*);
using PFN_glBindVertexArray = void(__stdcall*)(GLuint);
using PFN_glBindAttribLocation = void(__stdcall*)(GLuint, GLuint, const GLchar*);
using PFN_glGetUniformLocation = GLint(__stdcall*)(GLuint, const GLchar*);
using PFN_glUniform1i = void(__stdcall*)(GLint, GLint);
using PFN_glUniform3f = void(__stdcall*)(GLint, GLfloat, GLfloat, GLfloat);
using PFN_glUniformMatrix4fv = void(__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat*);
using PFN_glUniformMatrix3fv = void(__stdcall*)(GLint, GLsizei, GLboolean, const GLfloat*);
using PFN_glActiveTexture = void(__stdcall*)(GLenum);
using PFN_glGenerateMipmap = void(__stdcall*)(GLenum);
using PFN_glGenFramebuffers = void(__stdcall*)(GLsizei, GLuint*);
using PFN_glBindFramebuffer = void(__stdcall*)(GLenum, GLuint);
using PFN_glFramebufferTexture2D = void(__stdcall*)(GLenum, GLenum, GLenum, GLuint, GLint);
using PFN_glCheckFramebufferStatus = GLenum(__stdcall*)(GLenum);

#define LOAD(name) auto name = (PFN_##name)wglGetProcAddress(#name)

static const GLenum GL_ARRAY_BUFFER = 0x8892;
static const GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
static const GLenum GL_STATIC_DRAW = 0x88E4;
static const GLenum GL_VERTEX_SHADER = 0x8B31;
static const GLenum GL_FRAGMENT_SHADER = 0x8B30;
static const GLenum GL_TEXTURE0 = 0x84C0;
// GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR
// and GL_DEPTH_COMPONENT are already in <GL/gl.h> (core GL1.1) -- redefining
// them here would corrupt the macro expansion.
static const GLenum GL_FRAMEBUFFER = 0x8D40;
static const GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
static const GLenum GL_DEPTH_STENCIL_ATTACHMENT = 0x821A;
static const GLenum GL_DEPTH_STENCIL = 0x84F9;
static const GLenum GL_UNSIGNED_INT_24_8 = 0x84FA;
static const GLenum GL_DEPTH24_STENCIL8 = 0x88F0;
static const GLenum GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
static const GLenum GL_COMPILE_STATUS = 0x8B81;
static const GLenum GL_LINK_STATUS = 0x8B82;

// Cube shader: transforms + per-vertex normal, samples a texture and
// modulates it by simple directional diffuse + ambient lighting.
static const char* kCubeVS =
    "attribute vec3 aPos;\n"
    "attribute vec3 aNormal;\n"
    "attribute vec2 aTexCoord;\n"
    "uniform mat4 uModel;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProj;\n"
    "uniform mat3 uNormalMat;\n"
    "varying vec3 vNormal;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "    vec4 worldPos = uModel * vec4(aPos, 1.0);\n"
    "    gl_Position = uProj * uView * worldPos;\n"
    "    vNormal = uNormalMat * aNormal;\n"
    "    vTexCoord = aTexCoord;\n"
    "}\n";
static const char* kCubeFS =
    "uniform sampler2D uTex;\n"
    "uniform vec3 uLightDir;\n"
    "varying vec3 vNormal;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "    vec3 n = normalize(vNormal);\n"
    "    float diff = max(dot(n, normalize(uLightDir)), 0.0);\n"
    "    vec3 lit = vec3(0.15) + vec3(diff);\n"
    "    vec4 texColor = texture2D(uTex, vTexCoord);\n"
    "    gl_FragColor = vec4(texColor.rgb * lit, texColor.a);\n"
    "}\n";

// Display shader: draws the FBO's color attachment as a full-window quad.
static const char* kQuadVS =
    "attribute vec2 aPos;\n"
    "attribute vec2 aTexCoord;\n"
    "varying vec2 vTexCoord;\n"
    "void main() {\n"
    "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
    "    vTexCoord = aTexCoord;\n"
    "}\n";
static const char* kQuadFS =
    "uniform sampler2D uTex;\n"
    "varying vec2 vTexCoord;\n"
    "void main() { gl_FragColor = texture2D(uTex, vTexCoord); }\n";

// ---- tiny row-major 4x4/3x3 matrix helpers (upload with transpose=GL_TRUE) ----
struct Mat4 { float m[16]; };

Mat4 Mat4Identity() {
    Mat4 r{};
    r.m[0] = r.m[5] = r.m[10] = r.m[15] = 1.0f;
    return r;
}

Mat4 Mat4Multiply(const Mat4& a, const Mat4& b) {
    Mat4 r{};
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            for (int k = 0; k < 4; ++k)
                r.m[row * 4 + col] += a.m[row * 4 + k] * b.m[k * 4 + col];
    return r;
}

Mat4 Mat4Translate(float x, float y, float z) {
    Mat4 r = Mat4Identity();
    r.m[3] = x;
    r.m[7] = y;
    r.m[11] = z;
    return r;
}

Mat4 Mat4RotateY(float a) {
    Mat4 r = Mat4Identity();
    float c = cosf(a), s = sinf(a);
    r.m[0] = c;  r.m[2] = s;
    r.m[8] = -s; r.m[10] = c;
    return r;
}

Mat4 Mat4RotateX(float a) {
    Mat4 r = Mat4Identity();
    float c = cosf(a), s = sinf(a);
    r.m[5] = c;  r.m[6] = -s;
    r.m[9] = s;  r.m[10] = c;
    return r;
}

Mat4 Mat4Perspective(float fovyRadians, float aspect, float nearZ, float farZ) {
    Mat4 r{};
    float f = 1.0f / tanf(fovyRadians * 0.5f);
    r.m[0] = f / aspect;
    r.m[5] = f;
    r.m[10] = (farZ + nearZ) / (nearZ - farZ);
    r.m[11] = (2.0f * farZ * nearZ) / (nearZ - farZ);
    r.m[14] = -1.0f;
    return r;
}

void ExtractMat3UpperLeft(const Mat4& m, float out[9]) {
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            out[row * 3 + col] = m.m[row * 4 + col];
}

// ---- cube geometry: 24 verts (pos.xyz, normal.xyz, uv) x 6 faces, 36 indices ----
struct CubeGeometry {
    std::vector<float> vertices; // 8 floats per vertex
    std::vector<unsigned short> indices;
};

CubeGeometry BuildCube() {
    CubeGeometry g;
    struct Face { float n[3]; float p[4][3]; };
    const Face faces[6] = {
        {{0, 0, 1},  {{-0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}}},
        {{0, 0, -1}, {{0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}}},
        {{-1, 0, 0}, {{-0.5f, -0.5f, -0.5f}, {-0.5f, -0.5f, 0.5f}, {-0.5f, 0.5f, 0.5f}, {-0.5f, 0.5f, -0.5f}}},
        {{1, 0, 0},  {{0.5f, -0.5f, 0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, 0.5f}}},
        {{0, 1, 0},  {{-0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, 0.5f}, {0.5f, 0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}}},
        {{0, -1, 0}, {{-0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, -0.5f}, {0.5f, -0.5f, 0.5f}, {-0.5f, -0.5f, 0.5f}}},
    };
    const float uv[4][2] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
    for (int f = 0; f < 6; ++f) {
        unsigned short base = static_cast<unsigned short>(g.vertices.size() / 8);
        for (int v = 0; v < 4; ++v) {
            g.vertices.push_back(faces[f].p[v][0]);
            g.vertices.push_back(faces[f].p[v][1]);
            g.vertices.push_back(faces[f].p[v][2]);
            g.vertices.push_back(faces[f].n[0]);
            g.vertices.push_back(faces[f].n[1]);
            g.vertices.push_back(faces[f].n[2]);
            g.vertices.push_back(uv[v][0]);
            g.vertices.push_back(uv[v][1]);
        }
        unsigned short quad[6] = {0, 1, 2, 2, 3, 0};
        for (unsigned short q : quad) g.indices.push_back(base + q);
    }
    return g;
}

std::vector<unsigned char> BuildCheckerboardRGBA(int size, int tile) {
    std::vector<unsigned char> pixels(size * size * 4);
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            bool light = ((x / tile) + (y / tile)) % 2 == 0;
            unsigned char* p = &pixels[(y * size + x) * 4];
            p[0] = light ? 235 : 40;
            p[1] = light ? 200 : 60;
            p[2] = light ? 120 : 180;
            p[3] = 255;
        }
    }
    return pixels;
}

GLuint CompileShader(PFN_glCreateShader glCreateShader, PFN_glShaderSource glShaderSource,
                      PFN_glCompileShader glCompileShader, PFN_glGetShaderiv glGetShaderiv,
                      GLenum type, const char* src) {
    GLuint sh = glCreateShader(type);
    glShaderSource(sh, 1, &src, nullptr);
    glCompileShader(sh);
    GLint ok = 0;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) fprintf(stderr, "shader compile failed (type 0x%X)\n", type);
    return sh;
}

void CheckLinked(PFN_glGetProgramiv glGetProgramiv, GLuint prog, const char* label) {
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) fprintf(stderr, "%s: program link failed\n", label);
}

LRESULT CALLBACK WndProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProc(h, m, w, l);
}

int main() {
    WNDCLASSA wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "GLCaptureTestApp";
    RegisterClassA(&wc);
    HWND hwnd = CreateWindowA("GLCaptureTestApp", "gl_capture test app", WS_OVERLAPPEDWINDOW,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, wc.hInstance, nullptr);
    ShowWindow(hwnd, SW_SHOW);
    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd{};
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 24;
    int fmt = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, fmt, &pfd);
    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    LOAD(glGenBuffers);
    LOAD(glBindBuffer);
    LOAD(glBufferData);
    LOAD(glCreateShader);
    LOAD(glShaderSource);
    LOAD(glCompileShader);
    LOAD(glGetShaderiv);
    LOAD(glCreateProgram);
    LOAD(glAttachShader);
    LOAD(glLinkProgram);
    LOAD(glGetProgramiv);
    LOAD(glUseProgram);
    LOAD(glEnableVertexAttribArray);
    LOAD(glVertexAttribPointer);
    LOAD(glGenVertexArrays);
    LOAD(glBindVertexArray);
    LOAD(glBindAttribLocation);
    LOAD(glGetUniformLocation);
    LOAD(glUniform1i);
    LOAD(glUniform3f);
    LOAD(glUniformMatrix4fv);
    LOAD(glUniformMatrix3fv);
    LOAD(glActiveTexture);
    LOAD(glGenerateMipmap);
    LOAD(glGenFramebuffers);
    LOAD(glBindFramebuffer);
    LOAD(glFramebufferTexture2D);
    LOAD(glCheckFramebufferStatus);
    // glDrawArrays/glDrawElements are core GL1.1: wglGetProcAddress can
    // return null for them since they're already statically exported --
    // use the ones <GL/gl.h> declares instead of fetching dynamically.

    printf("GL_VERSION: %s\n", (const char*)glGetString(GL_VERSION));
    fflush(stdout);
    bool haveModern = glGenBuffers && glCreateShader && glCreateProgram &&
                       glGenFramebuffers && glFramebufferTexture2D &&
                       glUniformMatrix4fv && glActiveTexture;
    if (!haveModern) {
        printf("modern GL entry points unavailable on this driver; nothing to render\n");
        fflush(stdout);
    }

    GLuint cubeProg = 0, quadProg = 0;
    GLint cubeModelLoc = -1, cubeViewLoc = -1, cubeProjLoc = -1, cubeNormalMatLoc = -1, cubeLightLoc = -1, cubeTexLoc = -1;
    GLint quadTexLoc = -1;
    GLuint cubeVao = 0, cubeVbo = 0, cubeIbo = 0;
    GLuint quadVbo = 0;
    GLuint cubeTex = 0;
    GLuint fbo = 0, fboColorTex = 0, fboDepthStencilTex = 0;
    const int kFboSize = 512;
    size_t cubeIndexCount = 0;

    if (haveModern) {
        // ---- cube shader program ----
        GLuint cvs = CompileShader(glCreateShader, glShaderSource, glCompileShader, glGetShaderiv, GL_VERTEX_SHADER, kCubeVS);
        GLuint cfs = CompileShader(glCreateShader, glShaderSource, glCompileShader, glGetShaderiv, GL_FRAGMENT_SHADER, kCubeFS);
        cubeProg = glCreateProgram();
        glBindAttribLocation(cubeProg, 0, "aPos");
        glBindAttribLocation(cubeProg, 1, "aNormal");
        glBindAttribLocation(cubeProg, 2, "aTexCoord");
        glAttachShader(cubeProg, cvs);
        glAttachShader(cubeProg, cfs);
        glLinkProgram(cubeProg);
        CheckLinked(glGetProgramiv, cubeProg, "cubeProg");
        cubeModelLoc = glGetUniformLocation(cubeProg, "uModel");
        cubeViewLoc = glGetUniformLocation(cubeProg, "uView");
        cubeProjLoc = glGetUniformLocation(cubeProg, "uProj");
        cubeNormalMatLoc = glGetUniformLocation(cubeProg, "uNormalMat");
        cubeLightLoc = glGetUniformLocation(cubeProg, "uLightDir");
        cubeTexLoc = glGetUniformLocation(cubeProg, "uTex");

        // ---- quad (FBO display) shader program ----
        GLuint qvs = CompileShader(glCreateShader, glShaderSource, glCompileShader, glGetShaderiv, GL_VERTEX_SHADER, kQuadVS);
        GLuint qfs = CompileShader(glCreateShader, glShaderSource, glCompileShader, glGetShaderiv, GL_FRAGMENT_SHADER, kQuadFS);
        quadProg = glCreateProgram();
        glBindAttribLocation(quadProg, 0, "aPos");
        glBindAttribLocation(quadProg, 1, "aTexCoord");
        glAttachShader(quadProg, qvs);
        glAttachShader(quadProg, qfs);
        glLinkProgram(quadProg);
        CheckLinked(glGetProgramiv, quadProg, "quadProg");
        quadTexLoc = glGetUniformLocation(quadProg, "uTex");

        // ---- cube geometry: VAO + VBO + index buffer ----
        CubeGeometry cube = BuildCube();
        cubeIndexCount = cube.indices.size();
        glGenVertexArrays(1, &cubeVao);
        glBindVertexArray(cubeVao);
        glGenBuffers(1, &cubeVbo);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
        glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(float), cube.vertices.data(), GL_STATIC_DRAW);
        glGenBuffers(1, &cubeIbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * sizeof(unsigned short), cube.indices.data(), GL_STATIC_DRAW);
        const GLsizei stride = 8 * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, 0, stride, (const void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, 0, stride, (const void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, 0, stride, (const void*)(6 * sizeof(float)));
        glBindVertexArray(0);

        // ---- quad geometry (position.xy, texcoord) covering the whole window ----
        float quadVerts[] = {
            -1, -1, 0, 0,
             1, -1, 1, 0,
            -1,  1, 0, 1,
             1,  1, 1, 1,
        };
        glGenBuffers(1, &quadVbo);
        glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVerts), quadVerts, GL_STATIC_DRAW);

        // ---- checkerboard texture for the cube ----
        auto pixels = BuildCheckerboardRGBA(64, 8);
        glGenTextures(1, &cubeTex);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
        if (glGenerateMipmap) glGenerateMipmap(GL_TEXTURE_2D);

        // ---- FBO: color texture + combined depth-stencil texture ----
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &fboColorTex);
        glBindTexture(GL_TEXTURE_2D, fboColorTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, kFboSize, kFboSize, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboColorTex, 0);

        glGenTextures(1, &fboDepthStencilTex);
        glBindTexture(GL_TEXTURE_2D, fboDepthStencilTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, kFboSize, kFboSize, 0,
                     GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fboDepthStencilTex, 0);

        GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status != GL_FRAMEBUFFER_COMPLETE) fprintf(stderr, "FBO incomplete: 0x%X\n", status);
        for (GLenum err; (err = glGetError()) != 0;) fprintf(stderr, "GL error during FBO setup: 0x%X\n", err);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glEnable(GL_DEPTH_TEST);
    }

    for (int frame = 0; frame < 60; ++frame) {
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) { TranslateMessage(&msg); DispatchMessage(&msg); }

        if (haveModern) {
            float angle = frame * 0.05f;
            Mat4 model = Mat4Multiply(Mat4RotateY(angle), Mat4RotateX(angle * 0.6f));
            Mat4 view = Mat4Translate(0, 0, -3.0f);
            Mat4 proj = Mat4Perspective(3.14159f / 4.0f, 1.0f, 0.1f, 100.0f);
            float normalMat[9];
            ExtractMat3UpperLeft(model, normalMat);

            // ---- pass 1: render the lit, textured cube into the FBO ----
            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glViewport(0, 0, kFboSize, kFboSize);
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.05f, 0.05f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glUseProgram(cubeProg);
            glUniformMatrix4fv(cubeModelLoc, 1, GL_TRUE, model.m);
            glUniformMatrix4fv(cubeViewLoc, 1, GL_TRUE, view.m);
            glUniformMatrix4fv(cubeProjLoc, 1, GL_TRUE, proj.m);
            glUniformMatrix3fv(cubeNormalMatLoc, 1, GL_TRUE, normalMat);
            glUniform3f(cubeLightLoc, 0.4f, 0.8f, 0.5f);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, cubeTex);
            glUniform1i(cubeTexLoc, 0);

            glBindVertexArray(cubeVao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIbo);
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(cubeIndexCount), GL_UNSIGNED_SHORT, nullptr);
            glBindVertexArray(0);

            // ---- pass 2: display the FBO's color texture on a full-window quad ----
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            RECT rc;
            GetClientRect(hwnd, &rc);
            glViewport(0, 0, rc.right - rc.left, rc.bottom - rc.top);
            glDisable(GL_DEPTH_TEST);
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glUseProgram(quadProg);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, fboColorTex);
            glUniform1i(quadTexLoc, 0);

            glBindBuffer(GL_ARRAY_BUFFER, quadVbo);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, 0, 4 * sizeof(float), (const void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, 0, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
            glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        } else {
            glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        SwapBuffers(hdc);
        Sleep(16);
    }

    wglMakeCurrent(nullptr, nullptr);
    wglDeleteContext(hglrc);
    return 0;
}

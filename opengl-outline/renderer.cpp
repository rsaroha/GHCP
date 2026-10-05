#include <windows.h>
#include <gl/GL.h>
#include <stddef.h>
#include <math.h>
#include <fstream>
#include <iterator>
#include <stdio.h>
#include <string>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "../third_party/tiny_obj_loader.h"
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
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
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
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE_MIN_FILTER 0x2801
#define GL_TEXTURE_MAG_FILTER 0x2800
#define GL_TEXTURE_WRAP_S 0x2802
#define GL_TEXTURE_WRAP_T 0x2803
#define GL_CLAMP_TO_EDGE 0x812F
#define GL_RGBA8 0x8058
#define GL_RGBA32F 0x8814
#define GL_DEPTH_COMPONENT24 0x81A6
#define GL_DEPTH_COMPONENT 0x1902
#define GL_UNSIGNED_INT 0x1405
#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#define GL_COLOR_BUFFER_BIT 0x00004000
#define GL_DEPTH_BUFFER_BIT 0x00000100
#define GL_DEBUG_SOURCE_APPLICATION 0x824A
#define GL_DEBUG_TYPE_MARKER 0x8268
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
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
typedef void (APIENTRY* PFNGLUNIFORM1FPROC)(GLint, GLfloat);
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
typedef void (APIENTRY* PFNGLBLITFRAMEBUFFERPROC)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);

typedef void (APIENTRY* PFNGLACTIVETEXTUREPROC)(GLenum);
typedef void (APIENTRY* PFNGLGENERATEMIPMAPPROC)(GLenum);
typedef void (APIENTRY* PFNGLDEBUGMESSAGEINSERTPROC)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar*);

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
static PFNGLUNIFORM1FPROC glUniform1f;
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
static PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
static PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;
static PFNGLACTIVETEXTUREPROC glActiveTexture;
static PFNGLDEBUGMESSAGEINSERTPROC glDebugMessageInsert;

HDC g_deviceContext = 0;
HWND g_window = 0;
static GLuint g_cubeVao = 0;
static GLuint g_cubeVbo = 0;
static GLsizei g_meshVertexCount = 0;
static GLuint g_cubeProgram = 0;
static GLuint g_screenProgram = 0;
static GLuint g_jfaSeedProgram = 0;
static GLuint g_jfaStepProgram = 0;
static GLuint g_jfaComposeProgram = 0;
static GLuint g_betterJfaSeedProgram = 0;
static GLuint g_betterJfaAxisProgram = 0;
static GLuint g_betterJfaComposeProgram = 0;
static GLuint g_presentProgram = 0;
static GLuint g_framebuffer = 0;
static GLuint g_msaaFramebuffer = 0;
static GLuint g_colorTexture = 0;
static GLuint g_depthTexture = 0;
static GLuint g_msaaColorTexture = 0;
static GLuint g_msaaDepthTexture = 0;
static GLuint g_outlineFramebuffer = 0;
static GLuint g_outlineTexture = 0;
static GLuint g_jfaFramebuffer = 0;
static GLuint g_jfaTextureA = 0;
static GLuint g_jfaTextureB = 0;
static GLint g_cubeMatrix = -1;
static GLint g_cubeModelView = -1;
static GLint g_screenTexture = -1;
static GLint g_screenStencil = -1;
static GLint g_screenTexelSize = -1;
static GLint g_screenOutlineImplementation = -1;
static GLint g_screenOutlineWidth = -1;
static GLint g_screenOutlineAntialiasing = -1;
static GLint g_screenInteriorOutline = -1;
static GLint g_jfaSeedStencil = -1;
static GLint g_jfaStepInput = -1;
static GLint g_jfaStepJumpDistance = -1;
static GLint g_jfaComposeScene = -1;
static GLint g_jfaComposeStencil = -1;
static GLint g_jfaComposeResult = -1;
static GLint g_jfaComposeOutlineWidth = -1;
static GLint g_jfaComposeAntialiasing = -1;
static GLint g_jfaComposeInteriorOutline = -1;
static GLint g_betterJfaSeedStencil = -1;
static GLint g_betterJfaAxisInput = -1;
static GLint g_betterJfaAxisWidth = -1;
static GLint g_betterJfaComposeScene = -1;
static GLint g_betterJfaComposeStencil = -1;
static GLint g_betterJfaComposeResult = -1;
static GLint g_betterJfaComposeOutlineWidth = -1;
static GLint g_betterJfaComposeAntialiasing = -1;
static GLint g_betterJfaComposeInteriorOutline = -1;
static GLint g_presentTexture = -1;
int g_width = 960;
int g_height = 640;
struct Quaternion { float w, x, y, z; };
static Quaternion g_rotation = { 1.0f, 0.0f, 0.0f, 0.0f };

static const float g_distance = 6.0f;
static float g_fieldOfView = 60.0f;
static float g_backgroundColor[3] = { 1.0f, 1.0f, 1.0f };
static int g_outlineImplementation = 0;
static float g_outlineWidthPixels = 4.0f;
static bool g_outlineAntialiasing = true;
static bool g_interiorOutline = false;
static bool g_msaaEnabled = false;
static float g_panX = 0.0f;
static float g_panY = 0.0f;
static bool g_rotating = false;
static bool g_panning = false;
static int g_lastMouseX = 0;
static int g_lastMouseY = 0;

static void UploadMeshVertices(const std::vector<float>& vertices)
{
    glBindVertexArray(g_cubeVao);
    glBindBuffer(GL_ARRAY_BUFFER, g_cubeVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    g_meshVertexCount = (GLsizei)(vertices.size() / 6);
    glBindVertexArray(0);
}

static void UploadDefaultMesh(void)
{
    const float vertices[] = {
        -1,-1,1, 0,0,1,   1,-1,1, 0,0,1,   1,1,1, 0,0,1,
        -1,-1,1, 0,0,1,   1,1,1, 0,0,1,  -1,1,1, 0,0,1,
         1,-1,-1, 0,0,-1, -1,-1,-1, 0,0,-1, -1,1,-1, 0,0,-1,
         1,-1,-1, 0,0,-1, -1,1,-1, 0,0,-1,  1,1,-1, 0,0,-1,
        -1,-1,-1, -1,0,0, -1,-1,1, -1,0,0, -1,1,1, -1,0,0,
        -1,-1,-1, -1,0,0, -1,1,1, -1,0,0, -1,1,-1, -1,0,0,
         1,-1,1, 1,0,0,   1,-1,-1, 1,0,0,  1,1,-1, 1,0,0,
         1,-1,1, 1,0,0,   1,1,-1, 1,0,0,   1,1,1, 1,0,0,
        -1,1,1, 0,1,0,    1,1,1, 0,1,0,    1,1,-1, 0,1,0,
        -1,1,1, 0,1,0,    1,1,-1, 0,1,0,   -1,1,-1, 0,1,0,
        -1,-1,-1, 0,-1,0,  1,-1,-1, 0,-1,0,  1,-1,1, 0,-1,0,
        -1,-1,-1, 0,-1,0,  1,-1,1, 0,-1,0, -1,-1,1, 0,-1,0
    };
    UploadMeshVertices(std::vector<float>(vertices, vertices + sizeof(vertices) / sizeof(float)));
}

static bool LoadObjMesh(const char* filename, std::string& errorMessage)
{
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning;
    std::string error;
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, filename, nullptr, true, true))
    {
        errorMessage = error.empty() ? "The OBJ file could not be loaded." : error;
        return false;
    }

    if (attrib.vertices.empty())
    {
        errorMessage = "The OBJ file does not contain any vertex positions.";
        return false;
    }

    float minimum[3] = { attrib.vertices[0], attrib.vertices[1], attrib.vertices[2] };
    float maximum[3] = { minimum[0], minimum[1], minimum[2] };
    for (size_t index = 0; index < attrib.vertices.size(); index += 3)
    {
        for (int component = 0; component < 3; ++component)
        {
            minimum[component] = fminf(minimum[component], attrib.vertices[index + component]);
            maximum[component] = fmaxf(maximum[component], attrib.vertices[index + component]);
        }
    }

    const float center[3] = {
        (minimum[0] + maximum[0]) * 0.5f,
        (minimum[1] + maximum[1]) * 0.5f,
        (minimum[2] + maximum[2]) * 0.5f
    };
    const float extent = fmaxf(maximum[0] - minimum[0], fmaxf(maximum[1] - minimum[1], maximum[2] - minimum[2]));
    if (extent <= 0.0f)
    {
        errorMessage = "The OBJ file has no measurable geometry.";
        return false;
    }
    const float scale = 2.0f / extent;
    std::vector<float> vertices;

    for (const tinyobj::shape_t& shape : shapes)
    {
        size_t indexOffset = 0;
        for (size_t face = 0; face < shape.mesh.num_face_vertices.size(); ++face)
        {
            const size_t faceVertexCount = shape.mesh.num_face_vertices[face];
            if (faceVertexCount != 3 || indexOffset + faceVertexCount > shape.mesh.indices.size())
            {
                errorMessage = "The OBJ file contains a non-triangulated or invalid face.";
                return false;
            }

            const tinyobj::index_t& firstIndex = shape.mesh.indices[indexOffset];
            const tinyobj::index_t& secondIndex = shape.mesh.indices[indexOffset + 1];
            const tinyobj::index_t& thirdIndex = shape.mesh.indices[indexOffset + 2];
            const int positionIndices[3] = { firstIndex.vertex_index, secondIndex.vertex_index, thirdIndex.vertex_index };
            for (int vertex = 0; vertex < 3; ++vertex)
            {
                if (positionIndices[vertex] < 0 || (size_t)(positionIndices[vertex] * 3 + 2) >= attrib.vertices.size())
                {
                    errorMessage = "The OBJ file contains an invalid position index.";
                    return false;
                }
            }

            const float* firstPosition = &attrib.vertices[positionIndices[0] * 3];
            const float* secondPosition = &attrib.vertices[positionIndices[1] * 3];
            const float* thirdPosition = &attrib.vertices[positionIndices[2] * 3];
            const float edgeA[3] = {
                secondPosition[0] - firstPosition[0],
                secondPosition[1] - firstPosition[1],
                secondPosition[2] - firstPosition[2]
            };
            const float edgeB[3] = {
                thirdPosition[0] - firstPosition[0],
                thirdPosition[1] - firstPosition[1],
                thirdPosition[2] - firstPosition[2]
            };
            float faceNormal[3] = {
                edgeA[1] * edgeB[2] - edgeA[2] * edgeB[1],
                edgeA[2] * edgeB[0] - edgeA[0] * edgeB[2],
                edgeA[0] * edgeB[1] - edgeA[1] * edgeB[0]
            };
            const float normalLength = sqrtf(faceNormal[0] * faceNormal[0] + faceNormal[1] * faceNormal[1] + faceNormal[2] * faceNormal[2]);
            if (normalLength > 0.0f)
            {
                faceNormal[0] /= normalLength;
                faceNormal[1] /= normalLength;
                faceNormal[2] /= normalLength;
            }

            for (int vertex = 0; vertex < 3; ++vertex)
            {
                const tinyobj::index_t& objIndex = shape.mesh.indices[indexOffset + vertex];
                const float* position = &attrib.vertices[positionIndices[vertex] * 3];
                vertices.push_back((position[0] - center[0]) * scale);
                vertices.push_back((position[1] - center[1]) * scale);
                vertices.push_back((position[2] - center[2]) * scale);

                float normal[3] = { faceNormal[0], faceNormal[1], faceNormal[2] };
                if (objIndex.normal_index >= 0 && (size_t)(objIndex.normal_index * 3 + 2) < attrib.normals.size())
                {
                    normal[0] = attrib.normals[objIndex.normal_index * 3];
                    normal[1] = attrib.normals[objIndex.normal_index * 3 + 1];
                    normal[2] = attrib.normals[objIndex.normal_index * 3 + 2];
                    const float length = sqrtf(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
                    if (length > 0.0f)
                    {
                        normal[0] /= length;
                        normal[1] /= length;
                        normal[2] /= length;
                    }
                }
                vertices.push_back(normal[0]);
                vertices.push_back(normal[1]);
                vertices.push_back(normal[2]);
            }
            indexOffset += faceVertexCount;
        }
    }

    if (vertices.empty())
    {
        errorMessage = "The OBJ file does not contain any triangular faces.";
        return false;
    }

    UploadMeshVertices(vertices);
    return true;
}

static void Fail(const char* message)
{
    MessageBoxA(g_window, message, "OpenGL initialization error", MB_ICONERROR | MB_OK);
}

static bool AttachFramebufferTexture(GLenum attachment, GLenum textureTarget, GLuint texture, const char* attachmentName)
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        char message[256] = {};
        sprintf_s(message, "OpenGL error before attaching the %s texture: 0x%04X.", attachmentName, error);
        Fail(message);
        return false;
    }

    glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, texture, 0);
    error = glGetError();
    if (error != GL_NO_ERROR)
    {
        char message[256] = {};
        sprintf_s(message, "glFramebufferTexture2D failed for the %s texture: 0x%04X.", attachmentName, error);
        Fail(message);
        return false;
    }

    return true;
}

static bool CheckFramebufferComplete(const char* framebufferName)
{
    const GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status == GL_FRAMEBUFFER_COMPLETE)
    {
        return true;
    }

    const char* reason = "unknown framebuffer status";
    switch (status)
    {
    case GL_FRAMEBUFFER_UNDEFINED:
        reason = "default framebuffer is undefined";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
        reason = "attachment is incomplete";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
        reason = "no image is attached";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
        reason = "draw buffer is incomplete";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
        reason = "read buffer is incomplete";
        break;
    case GL_FRAMEBUFFER_UNSUPPORTED:
        reason = "attachment combination is unsupported";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
        reason = "multisample configuration is incomplete";
        break;
    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
        reason = "layered attachment configuration is incomplete";
        break;
    }

    char message[256] = {};
    sprintf_s(message, "%s is incomplete: %s (status 0x%04X).", framebufferName, reason, status);
    Fail(message);
    return false;
}

static void* GetGLProc(const char* name)
{
    void* address = (void*)wglGetProcAddress(name);
    if (address == 0 || address == (void*)0x1 || address == (void*)0x2 || address == (void*)0x3 || address == (void*)-1)
    {
        HMODULE module = GetModuleHandleA("opengl32.dll");
        address = (void*)GetProcAddress(module, name);
    }
    return address;
}

static void DebugMessage(const char* message)
{
    if (glDebugMessageInsert)
    {
        glDebugMessageInsert(
            GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER,
            0,
            GL_DEBUG_SEVERITY_NOTIFICATION,
            -1,
            message);
    }
}

static bool LoadFunctions(void)
{
#define LOAD_REQUIRED(name) name = (decltype(name))GetGLProc(#name); if (!name) return false
    LOAD_REQUIRED(glGenVertexArrays);
    LOAD_REQUIRED(glBindVertexArray);
    LOAD_REQUIRED(glDeleteVertexArrays);
    LOAD_REQUIRED(glGenBuffers);
    LOAD_REQUIRED(glBindBuffer);
    LOAD_REQUIRED(glBufferData);
    LOAD_REQUIRED(glDeleteBuffers);
    LOAD_REQUIRED(glCreateShader);
    LOAD_REQUIRED(glShaderSource);
    LOAD_REQUIRED(glCompileShader);
    LOAD_REQUIRED(glGetShaderiv);
    LOAD_REQUIRED(glGetShaderInfoLog);
    LOAD_REQUIRED(glDeleteShader);
    LOAD_REQUIRED(glCreateProgram);
    LOAD_REQUIRED(glAttachShader);
    LOAD_REQUIRED(glLinkProgram);
    LOAD_REQUIRED(glGetProgramiv);
    LOAD_REQUIRED(glGetProgramInfoLog);
    LOAD_REQUIRED(glUseProgram);
    LOAD_REQUIRED(glDeleteProgram);
    LOAD_REQUIRED(glGetUniformLocation);
    LOAD_REQUIRED(glUniformMatrix4fv);
    LOAD_REQUIRED(glUniform1i);
    LOAD_REQUIRED(glUniform1f);
    LOAD_REQUIRED(glUniform2f);
    LOAD_REQUIRED(glUniform4f);
    LOAD_REQUIRED(glEnableVertexAttribArray);
    LOAD_REQUIRED(glDisableVertexAttribArray);
    LOAD_REQUIRED(glVertexAttribPointer);
    LOAD_REQUIRED(glGenFramebuffers);
    LOAD_REQUIRED(glBindFramebuffer);
    LOAD_REQUIRED(glDeleteFramebuffers);
    LOAD_REQUIRED(glCheckFramebufferStatus);
    LOAD_REQUIRED(glFramebufferTexture2D);
    LOAD_REQUIRED(glTexImage2DMultisample);
    LOAD_REQUIRED(glBlitFramebuffer);
    LOAD_REQUIRED(glActiveTexture);
    glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)GetGLProc("glDebugMessageInsert");
    if (!glDebugMessageInsert)
    {
        glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)GetGLProc("glDebugMessageInsertKHR");
    }
    if (!glDebugMessageInsert)
    {
        glDebugMessageInsert = (PFNGLDEBUGMESSAGEINSERTPROC)GetGLProc("glDebugMessageInsertARB");
    }
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
    if (!status)
    {
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
    if (!status)
    {
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
    for (int i = 0; i < 16; ++i)
    {
        m[i] = 0.0f;
    }
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
    if (length <= 0.000001f)
    {
        return { 1.0f, 0.0f, 0.0f, 0.0f };
    }
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
    m[0] = 1.0f - 2.0f * (yy + zz);
    m[1] = 2.0f * (xy + wz);
    m[2] = 2.0f * (xz - wy);
    m[4] = 2.0f * (xy - wz);
    m[5] = 1.0f - 2.0f * (xx + zz);
    m[6] = 2.0f * (yz + wx);
    m[8] = 2.0f * (xz + wy);
    m[9] = 2.0f * (yz - wx);
    m[10] = 1.0f - 2.0f * (xx + yy);
}

static void BuildModelView(float* m)
{
    QuaternionToMatrix(g_rotation, m);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = -g_distance;
    m[15] = 1.0f;
}
static void Multiply(const float* a, const float* b, float* out)
{
    float result[16] = {};
    for (int column = 0; column < 4; ++column)
    {
        for (int row = 0; row < 4; ++row)
        {
            for (int k = 0; k < 4; ++k)
            {
                result[column * 4 + row] += a[k * 4 + row] * b[column * 4 + k];
            }
        }
    }

    for (int i = 0; i < 16; ++i)
    {
        out[i] = result[i];
    }
}

static bool CreateRenderTarget(int width, int height)
{
    if (g_framebuffer) glDeleteFramebuffers(1, &g_framebuffer);
    if (g_msaaFramebuffer) glDeleteFramebuffers(1, &g_msaaFramebuffer);
    if (g_outlineFramebuffer) glDeleteFramebuffers(1, &g_outlineFramebuffer);
    if (g_jfaFramebuffer) glDeleteFramebuffers(1, &g_jfaFramebuffer);
    if (g_colorTexture) glDeleteTextures(1, &g_colorTexture);
    if (g_depthTexture) glDeleteTextures(1, &g_depthTexture);
    if (g_msaaColorTexture) glDeleteTextures(1, &g_msaaColorTexture);
    if (g_msaaDepthTexture) glDeleteTextures(1, &g_msaaDepthTexture);
    if (g_outlineTexture) glDeleteTextures(1, &g_outlineTexture);
    if (g_jfaTextureA) glDeleteTextures(1, &g_jfaTextureA);
    if (g_jfaTextureB) glDeleteTextures(1, &g_jfaTextureB);

    glGenFramebuffers(1, &g_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
    glGenTextures(1, &g_colorTexture);
    glBindTexture(GL_TEXTURE_2D, g_colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_colorTexture, "color"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    glGenTextures(1, &g_depthTexture);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 0);
    if (!AttachFramebufferTexture(GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, g_depthTexture, "depth-stencil"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    if (!CheckFramebufferComplete("Main framebuffer"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    if (g_msaaEnabled)
    {
        glGenFramebuffers(1, &g_msaaFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, g_msaaFramebuffer);

        glGenTextures(1, &g_msaaColorTexture);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, g_msaaColorTexture);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGBA8, width, height, GL_TRUE);
        if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, g_msaaColorTexture, "msaa-color"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return false;
        }

        glGenTextures(1, &g_msaaDepthTexture);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, g_msaaDepthTexture);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_DEPTH24_STENCIL8, width, height, GL_TRUE);
        if (!AttachFramebufferTexture(GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, g_msaaDepthTexture, "msaa-depth-stencil"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return false;
        }

        if (!CheckFramebufferComplete("MSAA framebuffer"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return false;
        }
    }

    glGenFramebuffers(1, &g_outlineFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
    glGenTextures(1, &g_outlineTexture);
    glBindTexture(GL_TEXTURE_2D, g_outlineTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_outlineTexture, "outline"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }
    const bool outlineComplete = CheckFramebufferComplete("Outline framebuffer");
    if (!outlineComplete)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    glGenFramebuffers(1, &g_jfaFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, g_jfaFramebuffer);
    glGenTextures(1, &g_jfaTextureA);
    glBindTexture(GL_TEXTURE_2D, g_jfaTextureA);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);

    glGenTextures(1, &g_jfaTextureB);
    glBindTexture(GL_TEXTURE_2D, g_jfaTextureB);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);

    if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_jfaTextureA, "jfa-a"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    if (!CheckFramebufferComplete("JFA framebuffer"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return true;
}

static GLuint RunJfaPasses(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, g_jfaFramebuffer);
    glViewport(0, 0, g_width, g_height);
    glDisable(GL_DEPTH_TEST);

    if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_jfaTextureA, "jfa-seed-target"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return 0;
    }

    glUseProgram(g_jfaSeedProgram);
    glUniform1i(g_jfaSeedStencil, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    GLuint inputTexture = g_jfaTextureA;
    GLuint outputTexture = g_jfaTextureB;
    int maxDimension = g_width > g_height ? g_width : g_height;
    int jumpDistance = 1;
    while (jumpDistance < maxDimension)
    {
        jumpDistance <<= 1;
    }
    jumpDistance >>= 1;
    if (jumpDistance < 1)
    {
        jumpDistance = 1;
    }

    while (jumpDistance >= 1)
    {
        if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, "jfa-step-target"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return 0;
        }

        glUseProgram(g_jfaStepProgram);
        glUniform1i(g_jfaStepInput, 0);
        glUniform1f(g_jfaStepJumpDistance, (float)jumpDistance);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, inputTexture);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        GLuint temporary = inputTexture;
        inputTexture = outputTexture;
        outputTexture = temporary;
        jumpDistance >>= 1;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return inputTexture;
}

static void RenderJfaOutline(void)
{
    GLuint jfaResult = RunJfaPasses();
    if (!jfaResult)
    {
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
    glViewport(0, 0, g_width, g_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glUseProgram(g_jfaComposeProgram);
    glUniform1i(g_jfaComposeScene, 0);
    glUniform1i(g_jfaComposeStencil, 1);
    glUniform1i(g_jfaComposeResult, 2);
    glUniform1f(g_jfaComposeOutlineWidth, g_outlineWidthPixels);
    glUniform1i(g_jfaComposeAntialiasing, g_outlineAntialiasing ? 1 : 0);
    glUniform1i(g_jfaComposeInteriorOutline, g_interiorOutline ? 1 : 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_colorTexture);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, jfaResult);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

static GLuint RunBetterJfaPasses(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, g_jfaFramebuffer);
    glViewport(0, 0, g_width, g_height);
    glDisable(GL_DEPTH_TEST);

    if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_jfaTextureA, "better-jfa-seed-target"))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return 0;
    }

    glUseProgram(g_betterJfaSeedProgram);
    glUniform1i(g_betterJfaSeedStencil, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    GLuint inputTexture = g_jfaTextureA;
    GLuint outputTexture = g_jfaTextureB;
    int iterationCount = 0;
    int stepWidth = 1;
    const int requiredWidth = (int)ceil(g_outlineWidthPixels + 1.0f);
    while (stepWidth < requiredWidth)
    {
        stepWidth <<= 1;
        ++iterationCount;
    }

    for (int iteration = iterationCount - 1; iteration >= 0; --iteration)
    {
        const float width = (float)(1 << iteration) + 0.5f;

        if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, "better-jfa-horizontal"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return 0;
        }
        glUseProgram(g_betterJfaAxisProgram);
        glUniform1i(g_betterJfaAxisInput, 0);
        glUniform2f(g_betterJfaAxisWidth, width, 0.0f);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, inputTexture);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        GLuint temporary = inputTexture;
        inputTexture = outputTexture;
        outputTexture = temporary;

        if (!AttachFramebufferTexture(GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, "better-jfa-vertical"))
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            return 0;
        }
        glUniform2f(g_betterJfaAxisWidth, 0.0f, width);
        glBindTexture(GL_TEXTURE_2D, inputTexture);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        temporary = inputTexture;
        inputTexture = outputTexture;
        outputTexture = temporary;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return inputTexture;
}

static void RenderBetterJfaOutline(void)
{
    GLuint jfaResult = RunBetterJfaPasses();
    if (!jfaResult)
    {
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
    glViewport(0, 0, g_width, g_height);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);
    glUseProgram(g_betterJfaComposeProgram);
    glUniform1i(g_betterJfaComposeScene, 0);
    glUniform1i(g_betterJfaComposeStencil, 1);
    glUniform1i(g_betterJfaComposeResult, 2);
    glUniform1f(g_betterJfaComposeOutlineWidth, g_outlineWidthPixels);
    glUniform1i(g_betterJfaComposeAntialiasing, g_outlineAntialiasing ? 1 : 0);
    glUniform1i(g_betterJfaComposeInteriorOutline, g_interiorOutline ? 1 : 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_colorTexture);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, g_depthTexture);
    glActiveTexture(GL_TEXTURE0 + 2);
    glBindTexture(GL_TEXTURE_2D, jfaResult);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
bool Renderer_Initialize(void)
{
    if (!LoadFunctions())
    {
        Fail("Required OpenGL 3.3 compatibility functions are unavailable.");
        return false;
    }

    std::string cubeVertex, cubeFragment, screenVertex, screenFragment, presentFragment;
    std::string jfaSeedFragment, jfaStepFragment, jfaComposeFragment;
    std::string betterJfaSeedFragment, betterJfaAxisFragment, betterJfaComposeFragment;
    if (!LoadShaderSource("cube.vert", cubeVertex) ||
        !LoadShaderSource("cube.frag", cubeFragment) ||
        !LoadShaderSource("fullscreen.vert", screenVertex) ||
        !LoadShaderSource("outline.frag", screenFragment) ||
        !LoadShaderSource("jfa_seed.frag", jfaSeedFragment) ||
        !LoadShaderSource("jfa_step.frag", jfaStepFragment) ||
        !LoadShaderSource("jfa_compose.frag", jfaComposeFragment) ||
        !LoadShaderSource("better_jfa_seed.frag", betterJfaSeedFragment) ||
        !LoadShaderSource("better_jfa_axis.frag", betterJfaAxisFragment) ||
        !LoadShaderSource("better_jfa_compose.frag", betterJfaComposeFragment) ||
        !LoadShaderSource("present.frag", presentFragment))
    {
        Fail("Unable to load shader files from the shaders directory.");
        return false;
    }
    g_cubeProgram = CreateProgram(cubeVertex.c_str(), cubeFragment.c_str());
    g_screenProgram = CreateProgram(screenVertex.c_str(), screenFragment.c_str());
    g_jfaSeedProgram = CreateProgram(screenVertex.c_str(), jfaSeedFragment.c_str());
    g_jfaStepProgram = CreateProgram(screenVertex.c_str(), jfaStepFragment.c_str());
    g_jfaComposeProgram = CreateProgram(screenVertex.c_str(), jfaComposeFragment.c_str());
    g_betterJfaSeedProgram = CreateProgram(screenVertex.c_str(), betterJfaSeedFragment.c_str());
    g_betterJfaAxisProgram = CreateProgram(screenVertex.c_str(), betterJfaAxisFragment.c_str());
    g_betterJfaComposeProgram = CreateProgram(screenVertex.c_str(), betterJfaComposeFragment.c_str());
    g_presentProgram = CreateProgram(screenVertex.c_str(), presentFragment.c_str());
    if (!g_cubeProgram || !g_screenProgram || !g_jfaSeedProgram || !g_jfaStepProgram || !g_jfaComposeProgram ||
        !g_betterJfaSeedProgram || !g_betterJfaAxisProgram || !g_betterJfaComposeProgram || !g_presentProgram) return false;
    g_cubeMatrix = glGetUniformLocation(g_cubeProgram, "mvp");
    g_cubeModelView = glGetUniformLocation(g_cubeProgram, "modelView");
    g_screenTexture = glGetUniformLocation(g_screenProgram, "sceneColor");
    g_screenStencil = glGetUniformLocation(g_screenProgram, "stencilMask");
    g_screenTexelSize = glGetUniformLocation(g_screenProgram, "texelSize");
    g_screenOutlineImplementation = glGetUniformLocation(g_screenProgram, "outlineImplementation");
    g_screenOutlineWidth = glGetUniformLocation(g_screenProgram, "outlineWidth");
    g_screenOutlineAntialiasing = glGetUniformLocation(g_screenProgram, "outlineAntialiasing");
    g_screenInteriorOutline = glGetUniformLocation(g_screenProgram, "interiorOutline");
    g_jfaSeedStencil = glGetUniformLocation(g_jfaSeedProgram, "stencilMask");
    g_jfaStepInput = glGetUniformLocation(g_jfaStepProgram, "jfaInput");
    g_jfaStepJumpDistance = glGetUniformLocation(g_jfaStepProgram, "jumpDistance");
    g_jfaComposeScene = glGetUniformLocation(g_jfaComposeProgram, "sceneColor");
    g_jfaComposeStencil = glGetUniformLocation(g_jfaComposeProgram, "stencilMask");
    g_jfaComposeResult = glGetUniformLocation(g_jfaComposeProgram, "jfaResult");
    g_jfaComposeOutlineWidth = glGetUniformLocation(g_jfaComposeProgram, "outlineWidth");
    g_jfaComposeAntialiasing = glGetUniformLocation(g_jfaComposeProgram, "outlineAntialiasing");
    g_jfaComposeInteriorOutline = glGetUniformLocation(g_jfaComposeProgram, "interiorOutline");
    g_betterJfaSeedStencil = glGetUniformLocation(g_betterJfaSeedProgram, "stencilMask");
    g_betterJfaAxisInput = glGetUniformLocation(g_betterJfaAxisProgram, "jfaInput");
    g_betterJfaAxisWidth = glGetUniformLocation(g_betterJfaAxisProgram, "axisWidth");
    g_betterJfaComposeScene = glGetUniformLocation(g_betterJfaComposeProgram, "sceneColor");
    g_betterJfaComposeStencil = glGetUniformLocation(g_betterJfaComposeProgram, "stencilMask");
    g_betterJfaComposeResult = glGetUniformLocation(g_betterJfaComposeProgram, "jfaResult");
    g_betterJfaComposeOutlineWidth = glGetUniformLocation(g_betterJfaComposeProgram, "outlineWidth");
    g_betterJfaComposeAntialiasing = glGetUniformLocation(g_betterJfaComposeProgram, "outlineAntialiasing");
    g_betterJfaComposeInteriorOutline = glGetUniformLocation(g_betterJfaComposeProgram, "interiorOutline");
    g_presentTexture = glGetUniformLocation(g_presentProgram, "screenTexture");

    glGenVertexArrays(1, &g_cubeVao);
    glBindVertexArray(g_cubeVao);
    glGenBuffers(1, &g_cubeVbo);
    glBindBuffer(GL_ARRAY_BUFFER, g_cubeVbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
    UploadDefaultMesh();
    if (!CreateRenderTarget(g_width, g_height))
    {
        Fail("The texture-backed framebuffer is incomplete.");
        return false;
    }
    return true;
}

void Renderer_Render(void)
{
    if (g_width <= 0 || g_height <= 0) return;
    DebugMessage("Begin render pass");
    GLuint renderFramebuffer = g_msaaEnabled ? g_msaaFramebuffer : g_framebuffer;
    glBindFramebuffer(GL_FRAMEBUFFER, renderFramebuffer);
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
    glUseProgram(g_cubeProgram);
    glUniformMatrix4fv(g_cubeMatrix, 1, GL_FALSE, mvp);
    glUniformMatrix4fv(g_cubeModelView, 1, GL_FALSE, modelView);
    glBindVertexArray(g_cubeVao);
    glDrawArrays(GL_TRIANGLES, 0, g_meshVertexCount);
    DebugMessage("End render pass");

    if (g_msaaEnabled)
    {
        DebugMessage("Begin MSAA resolve pass");
        glBindFramebuffer(GL_READ_FRAMEBUFFER, g_msaaFramebuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, g_framebuffer);
        glBlitFramebuffer(
            0, 0, g_width, g_height,
            0, 0, g_width, g_height,
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT,
            GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, g_framebuffer);
        DebugMessage("End MSAA resolve pass");
    }

    DebugMessage("Begin outline pass");
    glDisable(GL_STENCIL_TEST);
    if (g_outlineImplementation == 2)
    {
        RenderJfaOutline();
    }
    else if (g_outlineImplementation == 4)
    {
        RenderBetterJfaOutline();
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, g_outlineFramebuffer);
        glViewport(0, 0, g_width, g_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glUseProgram(g_screenProgram);
        glUniform1i(g_screenTexture, 0);
        glUniform1i(g_screenStencil, 1);
        glUniform1i(g_screenOutlineImplementation, g_outlineImplementation);
        glUniform1f(g_screenOutlineWidth, g_outlineWidthPixels);
        glUniform1i(g_screenOutlineAntialiasing, g_outlineAntialiasing ? 1 : 0);
        glUniform1i(g_screenInteriorOutline, g_interiorOutline ? 1 : 0);
        glUniform2f(g_screenTexelSize, 1.0f / (float)g_width, 1.0f / (float)g_height);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, g_colorTexture);
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, g_depthTexture);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    DebugMessage("End outline pass");

    DebugMessage("Begin blend back to renderframe pass");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, g_width, g_height);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(g_presentProgram);
    glUniform1i(g_presentTexture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, g_outlineTexture);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    DebugMessage("End blend back to renderframe pass");

}


void Renderer_MouseButton(int button, bool down, int x, int y)
{
    if (button == 0) g_rotating = down;
    if (button == 1) g_panning = down;
    if (down)
    {
        g_lastMouseX = x;
        g_lastMouseY = y;
    }
}

void Renderer_MouseMove(int x, int y)
{
    const int deltaX = x - g_lastMouseX;
    const int deltaY = y - g_lastMouseY;
    g_lastMouseX = x;
    g_lastMouseY = y;
    if (g_rotating)
    {
        const float radiansPerPixel = 0.5f * 0.01745329252f;
        const Quaternion yaw = QuaternionFromAxisAngle(0.0f, 1.0f, 0.0f, deltaX * radiansPerPixel);
        const Quaternion pitch = QuaternionFromAxisAngle(1.0f, 0.0f, 0.0f, deltaY * radiansPerPixel);
        g_rotation = NormalizeQuaternion(MultiplyQuaternion(yaw, MultiplyQuaternion(pitch, g_rotation)));
    }
    if (g_panning)
    {
        const float width = (float)(g_width > 0 ? g_width : 1);
        const float height = (float)(g_height > 0 ? g_height : 1);
        g_panX -= 2.0f * deltaX / width;
        g_panY += 2.0f * deltaY / height;
    }
}

void Renderer_MouseWheel(int delta)
{
    g_fieldOfView *= (float)pow(0.85, (double)delta / 120.0);
    if (!isfinite(g_fieldOfView) || g_fieldOfView < 0.001f)
    {
        g_fieldOfView = 0.001f;
    }
    else if (g_fieldOfView > 179.999f)
    {
        g_fieldOfView = 179.999f;
    }
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
    if (g_jfaSeedProgram) glDeleteProgram(g_jfaSeedProgram);
    if (g_jfaStepProgram) glDeleteProgram(g_jfaStepProgram);
    if (g_jfaComposeProgram) glDeleteProgram(g_jfaComposeProgram);
    if (g_betterJfaSeedProgram) glDeleteProgram(g_betterJfaSeedProgram);
    if (g_betterJfaAxisProgram) glDeleteProgram(g_betterJfaAxisProgram);
    if (g_betterJfaComposeProgram) glDeleteProgram(g_betterJfaComposeProgram);
    if (g_presentProgram) glDeleteProgram(g_presentProgram);
    if (g_framebuffer) glDeleteFramebuffers(1, &g_framebuffer);
    if (g_msaaFramebuffer) glDeleteFramebuffers(1, &g_msaaFramebuffer);
    if (g_outlineFramebuffer) glDeleteFramebuffers(1, &g_outlineFramebuffer);
    if (g_jfaFramebuffer) glDeleteFramebuffers(1, &g_jfaFramebuffer);
    if (g_colorTexture) glDeleteTextures(1, &g_colorTexture);
    if (g_depthTexture) glDeleteTextures(1, &g_depthTexture);
    if (g_msaaColorTexture) glDeleteTextures(1, &g_msaaColorTexture);
    if (g_msaaDepthTexture) glDeleteTextures(1, &g_msaaDepthTexture);
    if (g_outlineTexture) glDeleteTextures(1, &g_outlineTexture);
    if (g_jfaTextureA) glDeleteTextures(1, &g_jfaTextureA);
    if (g_jfaTextureB) glDeleteTextures(1, &g_jfaTextureB);
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

bool Renderer_LoadObj(const char* filename)
{
    std::string errorMessage;
    if (!LoadObjMesh(filename, errorMessage))
    {
        MessageBoxA(g_window, errorMessage.c_str(), "OBJ load error", MB_ICONERROR | MB_OK);
        return false;
    }

    return true;
}

void Renderer_SetOutlineImplementation(int implementation)
{
    if (implementation < 0)
    {
        g_outlineImplementation = 0;
        return;
    }

    if (implementation > 4)
    {
        g_outlineImplementation = 4;
        return;
    }

    g_outlineImplementation = implementation;
}

void Renderer_SetOutlineThickness(float pixels)
{
    pixels = (float)floor(pixels + 0.5f);
    if (pixels < 1.0f)
    {
        g_outlineWidthPixels = 1.0f;
        return;
    }

    if (pixels > 100.0f)
    {
        g_outlineWidthPixels = 100.0f;
        return;
    }

    g_outlineWidthPixels = pixels;
}

void Renderer_SetOutlineAntialiasing(bool enabled)
{
    g_outlineAntialiasing = enabled;
}

void Renderer_SetInteriorOutline(bool enabled)
{
    g_interiorOutline = enabled;
}

void Renderer_SetMsaaEnabled(bool enabled)
{
    if (g_msaaEnabled == enabled)
    {
        return;
    }

    g_msaaEnabled = enabled;
    if (g_framebuffer && !CreateRenderTarget(g_width, g_height))
    {
        Fail("Unable to recreate render targets after changing MSAA mode.");
    }
}

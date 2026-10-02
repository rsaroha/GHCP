#include "renderer_gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <commdlg.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"

#include "mesh_loader.h"
#include "texture_util.h"
#include "ui_helpers.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

// ─── Embedded GLSL shaders ───────────────────────────────────────────────────

static const char* MAIN_VERT = R"GLSL(
#version 460 core

layout(std140, binding=0) uniform SceneUBO {
    mat4  mvp;
    mat4  mv;
    vec4  selColor;
    vec4  lightPos;
    vec4  lightColor;
    int   shaderMode;
    int   hasAlbedoTex;
    int   hasEnvMap;
    float iblIntensity;
    uvec4 selMask;
} scene;

layout(location=0)  in vec3  inPosition;
layout(location=9)  in vec3  inNormal;
layout(location=10) in vec2  inUV;
layout(location=1)  in vec4  instCol0;
layout(location=2)  in vec4  instCol1;
layout(location=3)  in vec4  instCol2;
layout(location=4)  in vec4  instCol3;
layout(location=5)  in vec4  instColor;
layout(location=6)  in vec4  instMaterial;
layout(location=7)  in int   instMatType;
layout(location=8)  in vec4  instMatParams;

layout(location=0) out vec4  fragColor;
layout(location=1) out vec3  viewPos;
layout(location=2) out float isSelected;
layout(location=3) out flat int outShaderMode;
layout(location=4) out vec4  fragMaterial;
layout(location=5) out flat int fragMatType;
layout(location=6) out vec4  fragMatParams;
layout(location=7) out vec3  fragNormal;
layout(location=8) out vec2  fragUV;

void main() {
    mat4 inst   = mat4(instCol0, instCol1, instCol2, instCol3);
    vec4 lp     = inst * vec4(inPosition, 1.0);
    gl_Position = scene.mvp * lp;
    fragColor   = instColor;
    viewPos     = (scene.mv * lp).xyz;
    fragNormal  = normalize(mat3(scene.mv) * mat3(inst) * inNormal);
    fragUV      = inUV;

    uint bitIdx  = uint(gl_InstanceID);
    uint wordIdx = bitIdx / 32u;
    uint bitPos  = bitIdx % 32u;
    isSelected   = float((scene.selMask[wordIdx] >> bitPos) & 1u);

    outShaderMode = scene.shaderMode;
    fragMaterial  = instMaterial;
    fragMatType   = instMatType;
    fragMatParams = instMatParams;
}
)GLSL";

// Shared shadeSolid body used in both opaque and OIT frag shaders
static const char* SHADE_FUNC = R"GLSL(
layout(std140, binding=0) uniform SceneUBO {
    mat4  mvp;
    mat4  mv;
    vec4  selColor;
    vec4  lightPos;
    vec4  lightColor;
    int   shaderMode;
    int   hasAlbedoTex;
    int   hasEnvMap;
    float iblIntensity;
    uvec4 selMask;
} scene;

layout(binding=2) uniform sampler2D   albedoTex;
layout(binding=3) uniform samplerCube irradianceMap;
layout(binding=4) uniform samplerCube prefilteredEnv;
layout(binding=5) uniform sampler2D   brdfLUT;

layout(location=0) in vec4  fragColor;
layout(location=1) in vec3  viewPos;
layout(location=2) in float isSelected;
layout(location=3) in flat int shaderMode;
layout(location=4) in vec4  fragMaterial;
layout(location=5) in flat int fragMatType;
layout(location=6) in vec4  fragMatParams;
layout(location=7) in vec3  fragNormal;
layout(location=8) in vec2  fragUV;

const float PI = 3.14159265358979;

vec3 shadeSolid(vec3 N, vec3 L, vec3 viewDir, vec3 baseColor,
                float ambient, float diffuse, float specular, float shininess,
                int matType, vec4 p) {
    vec3 lit = baseColor * ambient;
    if (matType == 0) {
        vec3 H = normalize(L + viewDir);
        float dif = max(dot(N,L),0.0)*diffuse;
        float spc = pow(max(dot(N,H),0.0),shininess)*specular;
        lit = baseColor*(ambient+dif*scene.lightColor.rgb)+scene.lightColor.rgb*spc;
    } else if (matType == 1) {
        float NdotL=max(dot(N,L),0.0);
        float toon=floor(NdotL*max(p.x,1.0))/max(p.x,1.0);
        vec3 H=normalize(L+viewDir);
        float spc=(max(dot(N,H),0.0)>p.y?1.0:0.0)*specular;
        float rim=pow(clamp(1.0-max(dot(N,viewDir),0.0),0.0,1.0),max(p.z,0.1))*p.w;
        lit=baseColor*(ambient+toon*diffuse*scene.lightColor.rgb)+spc*scene.lightColor.rgb+rim*vec3(1.0);
    } else if (matType == 2) {
        float t=(dot(N,L)+1.0)*0.5;
        vec3 warm=mix(vec3(0.8,0.6,0.0),baseColor,p.x);
        vec3 cool=mix(vec3(0.0,0.2,0.8),baseColor,p.x);
        float spc=pow(max(dot(N,normalize(L+viewDir)),0.0),64.0)*p.y;
        lit=mix(cool,warm,t)+spc*scene.lightColor.rgb;
    } else if (matType == 3) {
        vec3 H=normalize(L+viewDir);
        float dif=max(dot(N,L),0.0)*diffuse;
        float spc=pow(max(dot(N,H),0.0),shininess)*specular;
        float rim=pow(clamp(1.0-max(dot(N,viewDir),0.0),0.0,1.0),max(p.x,0.1));
        lit=baseColor*(ambient+dif*scene.lightColor.rgb)+spc*scene.lightColor.rgb+rim*p.yzw;
    } else if (matType == 4) {
        float sigma=clamp(p.x,0.0,1.0),sigma2=sigma*sigma;
        float A=1.0-sigma2/(2.0*sigma2+0.66);
        float B=0.45*sigma2/(sigma2+0.09);
        float NdotL=max(dot(N,L),0.0),NdotV=max(dot(N,viewDir),0.0);
        float s=dot(L,viewDir)-NdotL*NdotV;
        float t_on=s<=0.0?1.0:max(NdotL,NdotV)+0.001;
        lit=baseColor*(ambient+NdotL*(A+B*s/t_on)*diffuse*scene.lightColor.rgb);
    } else if (matType == 5) {
        float NdotL=max(dot(N,L),0.001),NdotV=max(dot(N,viewDir),0.001);
        float k=clamp(p.x,0.1,2.0);
        lit=baseColor*(ambient+pow(NdotL*NdotV,k)/NdotV*diffuse*scene.lightColor.rgb);
    } else if (matType == 6) {
        float metal=clamp(p.x,0.0,1.0),rough=clamp(p.y,0.04,1.0);
        vec3 F0=mix(vec3(0.04),baseColor,metal);
        vec3 H=normalize(L+viewDir);
        float NdotL=max(dot(N,L),0.0),NdotV=max(dot(N,viewDir),0.001);
        float NdotH=max(dot(N,H),0.0),LdotH=max(dot(L,H),0.0);
        float a2=pow(rough,4.0),d=NdotH*NdotH*(a2-1.0)+1.0;
        float D=a2/(PI*d*d);
        vec3 F=F0+(vec3(1.0)-F0)*pow(1.0-LdotH,5.0);
        float k2=(rough+1.0)*(rough+1.0)/8.0;
        float G=(NdotL/(NdotL*(1.0-k2)+k2))*(NdotV/(NdotV*(1.0-k2)+k2));
        lit=((vec3(1.0)-F)*(1.0-metal)*baseColor/PI+D*F*G/max(4.0*NdotL*NdotV,0.001))*NdotL*scene.lightColor.rgb+baseColor*ambient;
    } else if (matType == 7) {
        vec3 up=abs(N.z)<0.999?vec3(0,0,1):vec3(1,0,0);
        vec3 T=normalize(cross(up,N)),B=cross(N,T);
        float angle=p.z*PI/180.0;
        vec3 Tr=cos(angle)*T+sin(angle)*B,Br=-sin(angle)*T+cos(angle)*B;
        vec3 H=normalize(L+viewDir);
        float NdotL=max(dot(N,L),0.0),NdotV=max(dot(N,viewDir),0.001),NdotH=dot(N,H);
        float ax=max(p.x,0.01),ay=max(p.y,0.01);
        float ex=-(dot(Tr,H)*dot(Tr,H)/(ax*ax)+dot(Br,H)*dot(Br,H)/(ay*ay))/max(NdotH*NdotH,0.001);
        float D_aniso=NdotH>0.0?exp(ex)/(4.0*PI*ax*ay*sqrt(max(NdotL*NdotV,0.001))):0.0;
        lit=baseColor*(ambient+NdotL*diffuse*scene.lightColor.rgb)+scene.lightColor.rgb*max(D_aniso,0.0)*p.w;
    } else {
        float wrap=clamp(p.x,0.0,1.0),NdotL=dot(N,L);
        float wrapDif=max((NdotL+wrap)/(1.0+wrap),0.0)*diffuse;
        float backLit=max(dot(-N,L),0.0)*p.y;
        vec3 scatter=mix(baseColor,baseColor*vec3(1.5,0.7,0.5),clamp(p.z,0.0,1.0));
        lit=baseColor*(ambient+wrapDif*scene.lightColor.rgb)+scatter*backLit*scene.lightColor.rgb;
    }
    return lit;
}

// Image-based lighting contribution (diffuse + specular IBL)
vec3 applyIBL(vec3 N, vec3 V, vec3 albedo, int matType, vec4 p, vec3 litColor) {
    if (bool(scene.hasEnvMap) == false) return litColor;
    // Reconstruct a view-space N for cubemap sampling (need world-space N)
    // For the irradiance/prefiltered lookups we use the fragment normal as a direction.
    // Since our view matrix is orthonormal we can use the normal directly and get a
    // reasonable result; for a proper implementation one would pass world-space N.
    vec3 irrDir = mat3(transpose(mat3(scene.mv))) * N;  // approximate world normal
    vec3 irradiance = texture(irradianceMap, irrDir).rgb;
    litColor += irradiance * albedo * scene.iblIntensity * 0.5;

    if (matType == 6) {
        float metalness = clamp(p.x, 0.0, 1.0);
        float roughness = clamp(p.y, 0.04, 1.0);
        vec3 F0 = mix(vec3(0.04), albedo, metalness);
        vec3 R = mat3(transpose(mat3(scene.mv))) * reflect(-V, N);
        float lod = roughness * float(4);   // NUM_ENV_MIPS - 1 = 4
        vec3 prefilt = textureLod(prefilteredEnv, R, lod).rgb;
        float NdotV = max(dot(N, V), 0.0);
        vec2 brdf = texture(brdfLUT, vec2(NdotV, roughness)).rg;
        vec3 F = F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - NdotV, 5.0);
        litColor += prefilt * (F * brdf.x + brdf.y) * scene.iblIntensity;
    }
    return litColor;
}
)GLSL";

static const char* OPAQUE_FRAG_HEADER = "#version 460 core\n";
static const char* OPAQUE_FRAG_MAIN = R"GLSL(
layout(location=0) out vec4 outColor;
void main() {
    if (shaderMode != 1 && fragColor.a < 0.99) discard;
    vec3 N = normalize(fragNormal);
    N = faceforward(N, viewPos, N);
    vec3 L       = normalize(scene.lightPos.xyz - viewPos);
    vec3 viewDir = normalize(-viewPos);
    vec3 albedo  = bool(scene.hasAlbedoTex)
        ? texture(albedoTex, fragUV).rgb * fragColor.rgb
        : fragColor.rgb;
    vec3 litColor;
    if (shaderMode == 1) {
        outColor = vec4(0.0, 0.0, 0.0, 1.0); return;
    } else if (shaderMode == 2) {
        litColor = albedo;
    } else if (shaderMode == 3) {
        outColor = vec4(N*0.5+0.5, 1.0); return;
    } else {
        litColor = shadeSolid(N, L, viewDir, albedo,
                              fragMaterial.x, fragMaterial.y, fragMaterial.z, fragMaterial.w,
                              fragMatType, fragMatParams);
        litColor = applyIBL(N, viewDir, albedo, fragMatType, fragMatParams, litColor);
    }
    if (isSelected > 0.5) litColor = mix(litColor, scene.selColor.rgb, 0.6);
    outColor = vec4(litColor, 1.0);
}
)GLSL";

static const char* OIT_FRAG_MAIN = R"GLSL(
layout(location=0) out vec4  outAccum;
layout(location=1) out float outReveal;
float oitWeight(float z, float a) {
    float b = 1.0 - z * 0.99;
    return clamp(a * (0.01 + b*b*b*3e3), 1e-2, 3e2);
}
void main() {
    float alpha = fragColor.a;
    if (shaderMode == 1 || alpha >= 0.99) discard;
    vec3 N = normalize(fragNormal);
    N = faceforward(N, viewPos, N);
    vec3 L       = normalize(scene.lightPos.xyz - viewPos);
    vec3 viewDir = normalize(-viewPos);
    vec3 albedo  = bool(scene.hasAlbedoTex)
        ? texture(albedoTex, fragUV).rgb * fragColor.rgb
        : fragColor.rgb;
    vec3 litColor;
    if (shaderMode == 2) {
        litColor = albedo;
    } else if (shaderMode == 3) {
        litColor = N*0.5+0.5;
    } else {
        litColor = shadeSolid(N, L, viewDir, albedo,
                              fragMaterial.x, fragMaterial.y, fragMaterial.z, fragMaterial.w,
                              fragMatType, fragMatParams);
        litColor = applyIBL(N, viewDir, albedo, fragMatType, fragMatParams, litColor);
    }
    if (isSelected > 0.5) litColor = mix(litColor, scene.selColor.rgb, 0.6);
    float w = oitWeight(gl_FragCoord.z, alpha);
    outAccum  = vec4(litColor * alpha * w, alpha * w);
    outReveal = alpha;
}
)GLSL";

static const char* COMPOSITE_VERT = R"GLSL(
#version 460 core
void main() {
    vec2 pos[3] = vec2[3](vec2(-1,-1), vec2(3,-1), vec2(-1,3));
    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
}
)GLSL";

static const char* COMPOSITE_FRAG = R"GLSL(
#version 460 core
layout(binding=0) uniform sampler2D accumSampler;
layout(binding=1) uniform sampler2D revealSampler;
layout(location=0) out vec4 outColor;
void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    float reveal = texelFetch(revealSampler, coord, 0).r;
    if (abs(reveal - 1.0) < 1e-4) discard;
    vec4 accum = texelFetch(accumSampler, coord, 0);
    vec3 avgColor = accum.rgb / max(accum.a, 1e-5);
    outColor = vec4(avgColor, 1.0 - reveal);
}
)GLSL";

static const char* SKYBOX_VERT = R"GLSL(
#version 460 core
uniform mat4 invPVR;
out vec3 outDir;
void main() {
    int  i   = gl_VertexID;
    vec2 ndc = vec2((i << 1) & 2, i & 2) * 2.0 - 1.0;
    gl_Position = vec4(ndc, 1.0, 1.0);
    vec4 w  = invPVR * vec4(ndc, 1.0, 1.0);
    outDir  = normalize(w.xyz / w.w);
}
)GLSL";

static const char* SKYBOX_FRAG = R"GLSL(
#version 460 core
in  vec3 outDir;
out vec4 outColor;
layout(binding=6) uniform sampler2D equirectTex;
uniform float iblIntensity;
const float PI = 3.14159265359;
vec2 dirToEquirectUV(vec3 dir) {
    float phi   = acos(clamp(dir.y, -1.0, 1.0));
    float theta = atan(dir.z, dir.x);
    return vec2((theta + PI) / (2.0 * PI), 1.0 - phi / PI);
}
vec3 tonemap(vec3 c) { c = c / (c + 1.0); return pow(c, vec3(1.0 / 2.2)); }
void main() {
    vec2 uv  = dirToEquirectUV(normalize(outDir));
    vec3 col = texture(equirectTex, uv).rgb * iblIntensity;
    outColor  = vec4(tonemap(col), 1.0);
}
)GLSL";

// highlight frag main: discard non-selected, shade with selection color using per-instance material
static const char* HIGHLIGHT_FRAG_MAIN = R"GLSL(
layout(location=0) out vec4 outMask;
void main() {
    if (isSelected < 0.5) discard;
    vec3 N = normalize(fragNormal);
    N = faceforward(N, viewPos, N);
    vec3 L       = normalize(scene.lightPos.xyz - viewPos);
    vec3 viewDir = normalize(-viewPos);
    vec3 albedo  = scene.selColor.rgb;
    vec3 litColor = shadeSolid(N, L, viewDir, albedo,
                               fragMaterial.x, fragMaterial.y,
                               fragMaterial.z, fragMaterial.w,
                               fragMatType, fragMatParams);
    litColor = applyIBL(N, viewDir, albedo, fragMatType, fragMatParams, litColor);
    outMask = vec4(litColor, 1.0);
}
)GLSL";

static const char* OUTLINE_VERT = R"GLSL(
#version 460 core
void main() {
    int  i   = gl_VertexID;
    vec2 ndc = vec2((i << 1) & 2, i & 2) * 2.0 - 1.0;
    gl_Position = vec4(ndc, 0.0, 1.0);
}
)GLSL";

static const char* OUTLINE_FRAG = R"GLSL(
#version 460 core
layout(binding=7) uniform sampler2D highlightMask;
uniform vec2  texelSize;
uniform vec4  outlineColor;
uniform float outlineThickness;
uniform float antialiased;
layout(location=0) out vec4 outColor;
void main() {
    vec2  uv  = gl_FragCoord.xy * texelSize;
    vec4  src = texture(highlightMask, uv);
    float mask = step(0.001, src.a);
    float s    = outlineThickness * 0.5;
    #define S(off) step(0.001, texture(highlightMask, uv + (off)*texelSize*s).a)
    float d = mask;
    d = max(d, S(vec2( 1.0,  0.0)));
    d = max(d, S(vec2(-1.0,  0.0)));
    d = max(d, S(vec2( 0.0,  1.0)));
    d = max(d, S(vec2( 0.0, -1.0)));
    d = max(d, S(vec2( 2.0,  0.0)));
    d = max(d, S(vec2(-2.0,  0.0)));
    d = max(d, S(vec2( 0.0,  2.0)));
    d = max(d, S(vec2( 0.0, -2.0)));
    d = max(d, S(vec2( 1.0,  1.0)));
    d = max(d, S(vec2(-1.0,  1.0)));
    d = max(d, S(vec2( 1.0, -1.0)));
    d = max(d, S(vec2(-1.0, -1.0)));
    #undef S
    float isOutline = clamp(d - mask, 0.0, 1.0);
    if (antialiased > 0.5) {
        outColor = mix(src, vec4(outlineColor.rgb, 1.0), smoothstep(0.0, 1.0, isOutline));
    } else {
        outColor = isOutline > 0.5 ? vec4(outlineColor.rgb, 1.0) : src;
    }
}
)GLSL";

static const char* MASKING_VERT = R"GLSL(
#version 460 core
void main() {
    int  i   = gl_VertexID;
    vec2 ndc = vec2((i << 1) & 2, i & 2) * 2.0 - 1.0;
    gl_Position = vec4(ndc, 0.0, 1.0);
}
)GLSL";

static const char* MASKING_FRAG = R"GLSL(
#version 460 core
layout(binding=7) uniform sampler2D mainDepth;
layout(binding=8) uniform sampler2D highlightDepth;
layout(binding=9) uniform sampler2D highlightMask;
uniform float occlusionAlpha;
layout(location=0) out vec4 outMask;
void main() {
    ivec2 c   = ivec2(gl_FragCoord.xy);
    float md  = texelFetch(mainDepth,      c, 0).r;
    float hd  = texelFetch(highlightDepth, c, 0).r;
    vec4  src = texelFetch(highlightMask,  c, 0);
    float a   = src.a * ((hd > md + 0.0001) ? occlusionAlpha : 1.0);
    outMask = vec4(src.rgb, a);
}
)GLSL";

static const char* BLEND_FRAG = R"GLSL(
#version 460 core
layout(binding=7) uniform sampler2D outlineTex;
uniform vec2 texelSize;
layout(location=0) out vec4 outColor;
void main() {
    outColor = texture(outlineTex, gl_FragCoord.xy * texelSize);
}
)GLSL";

// ─── GLFW callbacks ──────────────────────────────────────────────────────────

static void mouseButtonCB(GLFWwindow* w, int btn, int action, int mods) {
    if (ImGui::GetIO().WantCaptureMouse) return;
    auto* h = static_cast<InputHandler*>(glfwGetWindowUserPointer(w));
    double mx, my; glfwGetCursorPos(w, &mx, &my);
    h->onMouseButton(btn, action, mods, mx, my);
}
static void cursorPosCB(GLFWwindow* w, double mx, double my) {
    if (ImGui::GetIO().WantCaptureMouse) return;
    static_cast<InputHandler*>(glfwGetWindowUserPointer(w))->onCursorPos(mx, my);
}
static void scrollCB(GLFWwindow* w, double /*dx*/, double dy) {
    if (ImGui::GetIO().WantCaptureMouse) return;
    auto* h = static_cast<InputHandler*>(glfwGetWindowUserPointer(w));
    h->state.zoomDist *= (float)std::pow(0.9, dy);
    h->state.zoomDist = std::clamp(h->state.zoomDist, 1.0f, 80.0f);
}
static void fbResizeCB(GLFWwindow* w, int, int) {
    glfwGetFramebufferSize(w, nullptr, nullptr); // just mark dirty
}

// ─── Shader compilation ───────────────────────────────────────────────────────

GLuint RendererGL::compileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char buf[2048]; glGetShaderInfoLog(s, sizeof(buf), nullptr, buf);
        glDeleteShader(s);
        throw std::runtime_error(std::string("Shader compile error:\n") + buf);
    }
    return s;
}

GLuint RendererGL::linkProgram(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs); glAttachShader(p, fs);
    glLinkProgram(p);
    glDeleteShader(vs); glDeleteShader(fs);
    GLint ok; glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char buf[2048]; glGetProgramInfoLog(p, sizeof(buf), nullptr, buf);
        glDeleteProgram(p);
        throw std::runtime_error(std::string("Program link error:\n") + buf);
    }
    return p;
}

void RendererGL::createPrograms() {
    // Opaque frag = header + shared UBO/inputs + shadeSolid + opaque main
    std::string opaqueFrag = OPAQUE_FRAG_HEADER;
    opaqueFrag += SHADE_FUNC;
    opaqueFrag += OPAQUE_FRAG_MAIN;

    std::string oitFrag = OPAQUE_FRAG_HEADER;
    oitFrag += SHADE_FUNC;
    oitFrag += OIT_FRAG_MAIN;

    GLuint vs0 = compileShader(GL_VERTEX_SHADER, MAIN_VERT);
    GLuint fs0 = compileShader(GL_FRAGMENT_SHADER, opaqueFrag.c_str());
    progMain = linkProgram(vs0, fs0);

    GLuint vs1 = compileShader(GL_VERTEX_SHADER, MAIN_VERT);
    GLuint fs1 = compileShader(GL_FRAGMENT_SHADER, oitFrag.c_str());
    progOit = linkProgram(vs1, fs1);

    GLuint cvs = compileShader(GL_VERTEX_SHADER, COMPOSITE_VERT);
    GLuint cfs = compileShader(GL_FRAGMENT_SHADER, COMPOSITE_FRAG);
    progComposite = linkProgram(cvs, cfs);

    GLuint svs = compileShader(GL_VERTEX_SHADER,   SKYBOX_VERT);
    GLuint sfs = compileShader(GL_FRAGMENT_SHADER, SKYBOX_FRAG);
    progSkybox = linkProgram(svs, sfs);
    skyboxLocInvPVR = glGetUniformLocation(progSkybox, "invPVR");
    skyboxLocIBL    = glGetUniformLocation(progSkybox, "iblIntensity");
    glProgramUniform1i(progSkybox, glGetUniformLocation(progSkybox, "equirectTex"), 6);

    std::string highlightFrag = OPAQUE_FRAG_HEADER;
    highlightFrag += SHADE_FUNC;
    highlightFrag += HIGHLIGHT_FRAG_MAIN;
    GLuint hvs = compileShader(GL_VERTEX_SHADER,   MAIN_VERT);
    GLuint hfs = compileShader(GL_FRAGMENT_SHADER, highlightFrag.c_str());
    progHighlight = linkProgram(hvs, hfs);

    GLuint mvs = compileShader(GL_VERTEX_SHADER,   MASKING_VERT);
    GLuint mfs = compileShader(GL_FRAGMENT_SHADER, MASKING_FRAG);
    progMasking     = linkProgram(mvs, mfs);
    maskingLocAlpha = glGetUniformLocation(progMasking, "occlusionAlpha");

    GLuint ovs = compileShader(GL_VERTEX_SHADER,   OUTLINE_VERT);
    GLuint ofs = compileShader(GL_FRAGMENT_SHADER, OUTLINE_FRAG);
    progOutline       = linkProgram(ovs, ofs);
    outlineLocTexelSize   = glGetUniformLocation(progOutline, "texelSize");
    outlineLocColor       = glGetUniformLocation(progOutline, "outlineColor");
    outlineLocThickness   = glGetUniformLocation(progOutline, "outlineThickness");
    outlineLocAntialiased = glGetUniformLocation(progOutline, "antialiased");
    glProgramUniform1i(progOutline, glGetUniformLocation(progOutline, "highlightMask"), 7);

    GLuint bvs = compileShader(GL_VERTEX_SHADER,   MASKING_VERT);  // reuse fullscreen vert
    GLuint bfs = compileShader(GL_FRAGMENT_SHADER, BLEND_FRAG);
    progBlend       = linkProgram(bvs, bfs);
    blendLocTexelSize = glGetUniformLocation(progBlend, "texelSize");
    glProgramUniform1i(progBlend, glGetUniformLocation(progBlend, "outlineTex"), 7);
}

// ─── VAO helper ──────────────────────────────────────────────────────────────

void RendererGL::setupInstanceAttribs(GLuint vao, GLuint instVbo) {
    // Binding 1: instance buffer, one advance per instance
    glVertexArrayVertexBuffer(vao, 1, instVbo, 0, (GLsizei)sizeof(InstanceData));
    glVertexArrayBindingDivisor(vao, 1, 1);

    // Locs 1-4: mat4 columns, offsets 0,16,32,48
    for (int i = 0; i < 4; i++) {
        glVertexArrayAttribFormat(vao, 1+i, 4, GL_FLOAT, GL_FALSE, (GLuint)(i*16));
        glVertexArrayAttribBinding(vao, 1+i, 1);
        glEnableVertexArrayAttrib(vao, 1+i);
    }
    // Loc 5: color (offset 64)
    glVertexArrayAttribFormat(vao, 5, 4, GL_FLOAT, GL_FALSE, 64);
    glVertexArrayAttribBinding(vao, 5, 1);
    glEnableVertexArrayAttrib(vao, 5);
    // Loc 6: material (ambient,diffuse,specular,shininess) (offset 80)
    glVertexArrayAttribFormat(vao, 6, 4, GL_FLOAT, GL_FALSE, 80);
    glVertexArrayAttribBinding(vao, 6, 1);
    glEnableVertexArrayAttrib(vao, 6);
    // Loc 7: materialType int (offset 96) — must use IFormat
    glVertexArrayAttribIFormat(vao, 7, 1, GL_INT, 96);
    glVertexArrayAttribBinding(vao, 7, 1);
    glEnableVertexArrayAttrib(vao, 7);
    // Loc 8: matParams vec4 (offset 100)
    glVertexArrayAttribFormat(vao, 8, 4, GL_FLOAT, GL_FALSE, 100);
    glVertexArrayAttribBinding(vao, 8, 1);
    glEnableVertexArrayAttrib(vao, 8);
}

// ─── Geometry setup ───────────────────────────────────────────────────────────

void RendererGL::createGeometry() {
    // Generate rounded cube
    std::vector<Vertex> verts;
    std::vector<uint16_t> idxs16;

    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
          GL_DEBUG_SEVERITY_NOTIFICATION, -1, "createGeometry - Start");

    generateRoundedCube(verts, idxs16);
    cubeIndexCount = (uint32_t)idxs16.size();

    // Cube VAO
    glCreateVertexArrays(1, &cubeVao);
    glCreateBuffers(1, &cubeVbo);
    glCreateBuffers(1, &cubeIbo);
    glCreateBuffers(1, &cubeInstanceVbo);

    glNamedBufferStorage(cubeVbo, (GLsizeiptr)(verts.size()*sizeof(Vertex)), verts.data(), 0);
    glNamedBufferStorage(cubeIbo, (GLsizeiptr)(idxs16.size()*sizeof(uint16_t)), idxs16.data(), 0);

    // Build initial instance data
    instanceData = buildInstanceData(_input->state.defaultMaterial);
    for (int i = 0; i < INSTANCE_COUNT; i++) {
        const Mat4& m = instanceData[i].transform;
        cubePositions[i] = { m[12], m[13], m[14] };
    }
    glNamedBufferStorage(cubeInstanceVbo, sizeof(instanceData), instanceData.data(),
                         GL_DYNAMIC_STORAGE_BIT);

    // Vertex attribs (binding 0: vertex data)
    glVertexArrayVertexBuffer(cubeVao, 0, cubeVbo, 0, (GLsizei)sizeof(Vertex));
    // loc 0: pos (offset 0)
    glVertexArrayAttribFormat(cubeVao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(cubeVao, 0, 0);
    glEnableVertexArrayAttrib(cubeVao, 0);
    // loc 9: nrm (offset 12)
    glVertexArrayAttribFormat(cubeVao, 9, 3, GL_FLOAT, GL_FALSE, 12);
    glVertexArrayAttribBinding(cubeVao, 9, 0);
    glEnableVertexArrayAttrib(cubeVao, 9);
    // loc 10: uv (offset 24)
    glVertexArrayAttribFormat(cubeVao, 10, 2, GL_FLOAT, GL_FALSE, 24);
    glVertexArrayAttribBinding(cubeVao, 10, 0);
    glEnableVertexArrayAttrib(cubeVao, 10);

    glVertexArrayElementBuffer(cubeVao, cubeIbo);
    setupInstanceAttribs(cubeVao, cubeInstanceVbo);

    // Fullscreen quad VAO (no buffers; uses gl_VertexID)
    glCreateVertexArrays(1, &quadVao);

    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
          GL_DEBUG_SEVERITY_NOTIFICATION, -1, "createGeometry - End");
}

void RendererGL::createSceneUbo() {
    glCreateBuffers(1, &sceneUbo);
    glNamedBufferStorage(sceneUbo, sizeof(SceneUBO), nullptr, GL_DYNAMIC_STORAGE_BIT);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, sceneUbo);
}

// ─── FBO creation ────────────────────────────────────────────────────────────

void RendererGL::createFbos(int w, int h) {
    fbWidth = w; fbHeight = h;

    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
          GL_DEBUG_SEVERITY_NOTIFICATION, -1, "createFbos : Start");

    // Shared depth texture (1x) — used as FBO attachment and sampled by masking pass
    glCreateTextures(GL_TEXTURE_2D, 1, &depthTex);
    glTextureStorage2D(depthTex, 1, GL_DEPTH24_STENCIL8, w, h);
    glTextureParameteri(depthTex, GL_TEXTURE_MIN_FILTER,    GL_NEAREST);
    glTextureParameteri(depthTex, GL_TEXTURE_MAG_FILTER,    GL_NEAREST);
    glTextureParameteri(depthTex, GL_TEXTURE_COMPARE_MODE,  GL_NONE);

    // Main FBO: RGBA8 color + depth
    glCreateTextures(GL_TEXTURE_2D, 1, &mainColorTex);
    glTextureStorage2D(mainColorTex, 1, GL_RGBA8, w, h);
    glCreateFramebuffers(1, &mainFbo);
    glNamedFramebufferTexture(mainFbo, GL_COLOR_ATTACHMENT0, mainColorTex, 0);
    glNamedFramebufferTexture(mainFbo, GL_DEPTH_STENCIL_ATTACHMENT, depthTex, 0);

    // OIT FBO: RGBA32F accum + R32F reveal + shared depth
    glCreateTextures(GL_TEXTURE_2D, 1, &accumTex);
    glTextureStorage2D(accumTex, 1, GL_RGBA32F, w, h);
    glCreateTextures(GL_TEXTURE_2D, 1, &revealTex);
    glTextureStorage2D(revealTex, 1, GL_R32F, w, h);
    glCreateFramebuffers(1, &oitFbo);
    glNamedFramebufferTexture(oitFbo, GL_COLOR_ATTACHMENT0, accumTex,  0);
    glNamedFramebufferTexture(oitFbo, GL_COLOR_ATTACHMENT1, revealTex, 0);
    glNamedFramebufferTexture(oitFbo, GL_DEPTH_STENCIL_ATTACHMENT, depthTex, 0);
    GLenum oitBufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glNamedFramebufferDrawBuffers(oitFbo, 2, oitBufs);

    // Bind textures for the composite shader
    glBindTextureUnit(0, accumTex);
    glBindTextureUnit(1, revealTex);

    // Highlight FBO: RGBA8 mask + own depth texture (records selected objects' depths)
    glCreateTextures(GL_TEXTURE_2D, 1, &highlightTex);
    glTextureStorage2D(highlightTex, 1, GL_RGBA8, w, h);
    glTextureParameteri(highlightTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(highlightTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCreateTextures(GL_TEXTURE_2D, 1, &highlightDepthTex);
    glTextureStorage2D(highlightDepthTex, 1, GL_DEPTH24_STENCIL8, w, h);
    glTextureParameteri(highlightDepthTex, GL_TEXTURE_MIN_FILTER,   GL_NEAREST);
    glTextureParameteri(highlightDepthTex, GL_TEXTURE_MAG_FILTER,   GL_NEAREST);
    glTextureParameteri(highlightDepthTex, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    glCreateFramebuffers(1, &highlightFbo);
    glNamedFramebufferTexture(highlightFbo, GL_COLOR_ATTACHMENT0, highlightTex,     0);
    glNamedFramebufferTexture(highlightFbo, GL_DEPTH_STENCIL_ATTACHMENT, highlightDepthTex, 0);

    // Masking FBO: RGBA8 dimmed mask output
    glCreateTextures(GL_TEXTURE_2D, 1, &maskedHighlightTex);
    glTextureStorage2D(maskedHighlightTex, 1, GL_RGBA8, w, h);
    glTextureParameteri(maskedHighlightTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(maskedHighlightTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCreateFramebuffers(1, &maskingFbo);
    glNamedFramebufferTexture(maskingFbo, GL_COLOR_ATTACHMENT0, maskedHighlightTex, 0);

    // Outline FBO: RGBA8 outline image (dilation output, fed to blend pass)
    glCreateTextures(GL_TEXTURE_2D, 1, &outlineTex);
    glTextureStorage2D(outlineTex, 1, GL_RGBA8, w, h);
    glTextureParameteri(outlineTex, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(outlineTex, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glCreateFramebuffers(1, &outlineFbo);
    glNamedFramebufferTexture(outlineFbo, GL_COLOR_ATTACHMENT0, outlineTex, 0);

    // MSAA FBO (created only when msaa8 is enabled)
    if (msaa8) {
        glCreateRenderbuffers(1, &msaaColorRbo);
        glNamedRenderbufferStorageMultisample(msaaColorRbo, 8, GL_RGBA8, w, h);
        glCreateRenderbuffers(1, &msaaDepthRbo);
        glNamedRenderbufferStorageMultisample(msaaDepthRbo, 8, GL_DEPTH24_STENCIL8, w, h);
        glCreateFramebuffers(1, &msaaFbo);
        glNamedFramebufferRenderbuffer(msaaFbo, GL_COLOR_ATTACHMENT0,        GL_RENDERBUFFER, msaaColorRbo);
        glNamedFramebufferRenderbuffer(msaaFbo, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, msaaDepthRbo);
    }

    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
          GL_DEBUG_SEVERITY_NOTIFICATION, -1, "createFbos : End");
}

void RendererGL::cleanupFbos() {
    glDeleteFramebuffers(1, &mainFbo);  mainFbo = 0;
    glDeleteFramebuffers(1, &oitFbo);   oitFbo  = 0;
    glDeleteTextures(1, &mainColorTex); mainColorTex = 0;
    glDeleteTextures(1, &accumTex);     accumTex = 0;
    glDeleteTextures(1, &revealTex);    revealTex = 0;
    glDeleteTextures(1, &depthTex);     depthTex = 0;
    glDeleteFramebuffers(1, &highlightFbo);       highlightFbo = 0;
    glDeleteFramebuffers(1, &maskingFbo);         maskingFbo = 0;
    glDeleteFramebuffers(1, &outlineFbo);         outlineFbo = 0;
    glDeleteTextures(1, &highlightTex);           highlightTex = 0;
    glDeleteTextures(1, &highlightDepthTex);      highlightDepthTex = 0;
    glDeleteTextures(1, &maskedHighlightTex);     maskedHighlightTex = 0;
    glDeleteTextures(1, &outlineTex);             outlineTex = 0;
    if (msaaFbo)      { glDeleteFramebuffers(1,  &msaaFbo);      msaaFbo = 0; }
    if (msaaColorRbo) { glDeleteRenderbuffers(1, &msaaColorRbo); msaaColorRbo = 0; }
    if (msaaDepthRbo) { glDeleteRenderbuffers(1, &msaaDepthRbo); msaaDepthRbo = 0; }
}

// ─── Window / GL init ─────────────────────────────────────────────────────────

void RendererGL::initWindow() {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Renderer", nullptr, nullptr);
    if (!window) throw std::runtime_error("glfwCreateWindow failed (OpenGL)");
    glfwSetWindowPos(window, 100, 50);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("gladLoadGLLoader failed");

    // Match Vulkan coordinate conventions (Y-up, depth [0,1])
    glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glfwSetWindowUserPointer(window, _input);
    glfwSetMouseButtonCallback(window, mouseButtonCB);
    glfwSetCursorPosCallback(window,   cursorPosCB);
    glfwSetScrollCallback(window,      scrollCB);
    glfwSetFramebufferSizeCallback(window, fbResizeCB);
    glfwSetKeyCallback(window, [](GLFWwindow* w, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(w, GLFW_TRUE);
    });
}

void RendererGL::initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
}

// ─── UBO update ──────────────────────────────────────────────────────────────

void RendererGL::uploadUBO(int shaderMode, const uint32_t selMask[4], bool hasAlbedo) {
    auto& s  = _input->state;
    Mat4  arc = s.arcball.matrix();

    Vec3 eye      = { s.camTarget.x, s.camTarget.y, s.camTarget.z - s.zoomDist };
    Mat4 baseView = lookAt(eye, s.camTarget, {0,1,0});
    Mat4 view     = mat4mul(baseView, arc);   // arcball rotates scene, not camera
    float asp     = fbWidth > 0 ? (float)fbWidth / fbHeight : 1.0f;
    Mat4  proj    = perspective(1.0472f, asp, 0.1f, 200.0f);
    Mat4  mvp     = mat4mul(proj, view);

    // Transform light by baseView only — arcball must not rotate the light
    auto& lp = s.light;
    float wx = lp.pos[0], wy = lp.pos[1], wz = lp.pos[2];
    Vec3 lvp = {
        baseView[0]*wx + baseView[4]*wy + baseView[8]*wz  + baseView[12],
        baseView[1]*wx + baseView[5]*wy + baseView[9]*wz  + baseView[13],
        baseView[2]*wx + baseView[6]*wy + baseView[10]*wz + baseView[14]
    };
    float inten = lp.intensity;

    SceneUBO u{};
    memcpy(u.mvp, mvp.data(), 64);
    memcpy(u.mv,  view.data(), 64);
    auto& sc = s.selectionColor;
    u.selColor[0] = sc.x; u.selColor[1] = sc.y; u.selColor[2] = sc.z; u.selColor[3] = 1.0f;
    u.lightPos[0]   = lvp.x;        u.lightPos[1]   = lvp.y;        u.lightPos[2]   = lvp.z;
    u.lightColor[0] = lp.color[0]*inten;
    u.lightColor[1] = lp.color[1]*inten;
    u.lightColor[2] = lp.color[2]*inten;
    u.shaderMode    = shaderMode;
    u.hasAlbedoTex  = (hasAlbedo && albedoLoaded) ? 1 : 0;
    u.hasEnvMap     = envLoaded ? 1 : 0;
    u.iblIntensity  = _input->state.iblIntensity;
    memcpy(u.selMask, selMask, 16);

    glNamedBufferSubData(sceneUbo, 0, sizeof(u), &u);
}

// ─── Mesh load / upload ───────────────────────────────────────────────────────

void RendererGL::uploadMeshBuffers(const std::vector<Vertex>& verts,
                                    const std::vector<uint32_t>& idxs) {
    glCreateVertexArrays(1, &meshVao);
    glCreateBuffers(1, &meshVbo);
    glCreateBuffers(1, &meshIbo);
    glCreateBuffers(1, &meshInstanceVbo);

    glNamedBufferStorage(meshVbo, (GLsizeiptr)(verts.size()*sizeof(Vertex)), verts.data(), 0);
    glNamedBufferStorage(meshIbo, (GLsizeiptr)(idxs.size()*sizeof(uint32_t)), idxs.data(), 0);
    meshIndexCount = (uint32_t)idxs.size();

    // Build identity instance data for the mesh
    meshMaterial = _input->state.defaultMaterial;
    meshInstanceData = {};
    meshInstanceData.transform[0] = meshInstanceData.transform[5] =
    meshInstanceData.transform[10] = meshInstanceData.transform[15] = 1.0f;
    meshInstanceData.color[0] = meshMaterial.color[0];
    meshInstanceData.color[1] = meshMaterial.color[1];
    meshInstanceData.color[2] = meshMaterial.color[2];
    meshInstanceData.color[3] = meshMaterial.alpha;
    meshInstanceData.ambient      = meshMaterial.ambient;
    meshInstanceData.diffuse      = meshMaterial.diffuse;
    meshInstanceData.specular     = meshMaterial.specular;
    meshInstanceData.shininess    = meshMaterial.shininess;
    meshInstanceData.materialType = meshMaterial.materialType;
    meshInstanceData.p0 = meshMaterial.p0; meshInstanceData.p1 = meshMaterial.p1;
    meshInstanceData.p2 = meshMaterial.p2; meshInstanceData.p3 = meshMaterial.p3;
    glNamedBufferStorage(meshInstanceVbo, sizeof(InstanceData), &meshInstanceData,
                         GL_DYNAMIC_STORAGE_BIT);

    // Vertex attribs for mesh VAO (same layout as cube VAO)
    glVertexArrayVertexBuffer(meshVao, 0, meshVbo, 0, (GLsizei)sizeof(Vertex));
    glVertexArrayAttribFormat(meshVao, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(meshVao, 0, 0);
    glEnableVertexArrayAttrib(meshVao, 0);
    glVertexArrayAttribFormat(meshVao, 9, 3, GL_FLOAT, GL_FALSE, 12);
    glVertexArrayAttribBinding(meshVao, 9, 0);
    glEnableVertexArrayAttrib(meshVao, 9);
    glVertexArrayAttribFormat(meshVao, 10, 2, GL_FLOAT, GL_FALSE, 24);
    glVertexArrayAttribBinding(meshVao, 10, 0);
    glEnableVertexArrayAttrib(meshVao, 10);
    glVertexArrayElementBuffer(meshVao, meshIbo);
    setupInstanceAttribs(meshVao, meshInstanceVbo);

    meshLoaded = true;
    meshError.clear();

    // Bounding sphere for mouse picking
    if (!verts.empty()) {
        Vec3 center{0,0,0};
        for (auto& v : verts) { center.x+=v.pos[0]; center.y+=v.pos[1]; center.z+=v.pos[2]; }
        float inv = 1.0f/(float)verts.size();
        center.x*=inv; center.y*=inv; center.z*=inv;
        float radius = 0.0f;
        for (auto& v : verts) {
            float dx=v.pos[0]-center.x, dy=v.pos[1]-center.y, dz=v.pos[2]-center.z;
            float d=std::sqrt(dx*dx+dy*dy+dz*dz);
            if (d>radius) radius=d;
        }
        if (_input) _input->setMeshPickContext(center, radius, true);
    }
}

void RendererGL::loadMesh(const std::string& path) {
    if (meshLoaded) unloadMesh();
    std::vector<Vertex> verts; std::vector<uint32_t> idxs;
    auto ext = path.size() >= 4 ? path.substr(path.size()-4) : "";
    for (auto& c : ext) c = (char)tolower((unsigned char)c);
    bool ok = (ext == ".obj") ? parseMeshObj(path, verts, idxs, meshError)
                              : parseMeshGltf(path, verts, idxs, meshError);
    if (!ok) return;
    uploadMeshBuffers(verts, idxs);
}

void RendererGL::unloadMesh() {
    if (!meshLoaded) return;
    glDeleteVertexArrays(1, &meshVao); meshVao = 0;
    glDeleteBuffers(1, &meshVbo);      meshVbo = 0;
    glDeleteBuffers(1, &meshIbo);      meshIbo = 0;
    glDeleteBuffers(1, &meshInstanceVbo); meshInstanceVbo = 0;
    meshLoaded = false; meshIndexCount = 0; meshError.clear();
    if (_input) {
        _input->setMeshPickContext({}, 0.0f, false);
        _input->state.meshSelected = false;
    }
}

// ─── Scene rendering ──────────────────────────────────────────────────────────

void RendererGL::drawScene(int shaderMode, bool oitPass) {
    GLuint prog = oitPass ? progOit : progMain;
    glUseProgram(prog);

    // Always bind IBL textures to their units (dummy 1x1 if not loaded)
    glBindTextureUnit(2, albedoTex);
    glBindTextureUnit(3, irradianceCube);
    glBindTextureUnit(4, prefilteredEnv);
    glBindTextureUnit(5, brdfLUT);

    // Build cube selection mask
    uint32_t cubeSelMask[4] = {0,0,0,0};
    for (int idx : _input->state.selectedCubes) {
        cubeSelMask[idx/32] |= (1u << (idx%32));
    }

    uploadUBO(shaderMode, cubeSelMask, true);

    // Draw cubes
    glBindVertexArray(cubeVao);
    glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)cubeIndexCount,
                            GL_UNSIGNED_SHORT, nullptr, INSTANCE_COUNT);

    // Draw loaded mesh with its own selection mask and albedo texture
    if (meshLoaded) {
        uint32_t meshSelMask[4] = {0,0,0,0};
        if (_input->state.meshSelected) meshSelMask[0] = 0xFFFFFFFFu;
        uploadUBO(shaderMode, meshSelMask, true);  // mesh: use albedo if loaded
        glBindVertexArray(meshVao);
        glDrawElements(GL_TRIANGLES, (GLsizei)meshIndexCount, GL_UNSIGNED_INT, nullptr);
    }
}

// ─── Frame rendering ──────────────────────────────────────────────────────────

void RendererGL::drawFrame() {
    // Check for resize
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    if (w == 0 || h == 0) { glfwSwapBuffers(window); return; }
    if (w != fbWidth || h != fbHeight) {
        cleanupFbos();
        createFbos(w, h);
        glExtent.width  = (uint32_t)w;
        glExtent.height = (uint32_t)h;
        _input->setPickContext(&glExtent, &cubePositions);
    }

    // Determine shader mode
    DisplayMode dm = _input->state.displayMode;
    int smode = SHADER_MODE_SOLID;
    if (dm == DisplayMode::Wireframe)
        smode = SHADER_MODE_WIREFRAME;
    else if (dm == DisplayMode::Unlit)
        smode = SHADER_MODE_UNLIT;
    else if (dm == DisplayMode::Normals)
        smode = SHADER_MODE_NORMALS;

    bool needOIT = (dm == DisplayMode::Solid ||
                    dm == DisplayMode::SolidWireframe ||
                    dm == DisplayMode::Unlit ||
                    dm == DisplayMode::Normals);

    // Always clear OIT FBO so revealTex starts at 1.0 (not 0).
    // Without this the composite pass draws opaque black on the first frame
    // and whenever the OIT pass is skipped (e.g. wireframe).
    {
        glBindFramebuffer(GL_FRAMEBUFFER, oitFbo);
        float zero[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        float one[4]  = {1.0f, 1.0f, 1.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, zero);
        glClearBufferfv(GL_COLOR, 1, one);
    }

    // ── Pass 1: opaque ──────────────────────────────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 1: Opaque");
    glBindFramebuffer(GL_FRAMEBUFFER, msaa8 ? msaaFbo : mainFbo);
    glViewport(0, 0, w, h);
    glDepthMask(GL_TRUE);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor(0.87f, 0.89f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ── Skybox: fullscreen background before geometry ─────────────────────────
    if (envLoaded) {
        auto& s   = _input->state;
        Mat4  arc = s.arcball.matrix();
        Vec3  eye = { s.camTarget.x, s.camTarget.y, s.camTarget.z - s.zoomDist };
        Mat4  bv  = lookAt(eye, s.camTarget, {0,1,0});
        Mat4  view = mat4mul(bv, arc);
        float asp  = fbWidth > 0 ? (float)fbWidth / fbHeight : 1.0f;
        Mat4  proj = perspective(1.0472f, asp, 0.1f, 200.0f);

        // Strip translation → pure view rotation, then invert(proj × rot)
        Mat4 viewRot = view;
        viewRot[12] = viewRot[13] = viewRot[14] = 0.0f;
        Mat4 envProj = proj;
        envProj[0] *= s.envZoom; envProj[5] *= s.envZoom; // scale focal lengths (Alt+Ctrl zoom)
        Mat4 envRot  = quatToMat4(s.envArcball.current);  // Alt+MMB rotate/pan
        Mat4 invPVR  = mat4mul(envRot, mat4inverse(mat4mul(envProj, viewRot)));

        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glUseProgram(progSkybox);
        glBindTextureUnit(6, equirectTex2D);
        glUniformMatrix4fv(skyboxLocInvPVR, 1, GL_FALSE, invPVR.data());
        glUniform1f(skyboxLocIBL, s.iblIntensity);
        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
    }

    if (dm == DisplayMode::Wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        drawScene(SHADER_MODE_WIREFRAME, false);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    } else {
        drawScene(smode, false);
        if (dm == DisplayMode::SolidWireframe) {
            glEnable(GL_POLYGON_OFFSET_LINE);
            glPolygonOffset(-1.0f, -1.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            drawScene(SHADER_MODE_WIREFRAME, false);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDisable(GL_POLYGON_OFFSET_LINE);
        }
    }

    // ── MSAA resolve: blit to regular mainFbo before OIT ─────────────────────
    if (msaa8) {
        glBlitNamedFramebuffer(msaaFbo, mainFbo,
            0, 0, w, h, 0, 0, w, h,
            GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    }

    // ── Pass 2: OIT accumulation ─────────────────────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 2,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 2: OIT Accum");
    if (needOIT) {
        glBindFramebuffer(GL_FRAMEBUFFER, oitFbo);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunci(0, GL_ONE, GL_ONE);
        glBlendFunci(1, GL_ZERO, GL_ONE_MINUS_SRC_COLOR);
        drawScene(smode, true);
    }

    // ── Pass 3: composite transparent over opaque ────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 3,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 3: OIT Composite");
    if (needOIT) {
        glBindFramebuffer(GL_FRAMEBUFFER, mainFbo);
        glDepthMask(GL_FALSE);
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(progComposite);
        glBindTextureUnit(0, accumTex);
        glBindTextureUnit(1, revealTex);
        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // ── Pass 4: selection highlight mask ─────────────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 4,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 4: Highlight");
    {
        auto& s = _input->state;
        glDepthMask(GL_TRUE);   // must be true before glClear affects depth
        glBindFramebuffer(GL_FRAMEBUFFER, highlightFbo);
        glViewport(0, 0, w, h);
        float zero = 0.0f;
        glClearBufferfv(GL_COLOR, 0, &zero);
        glClear(GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST); glDisable(GL_BLEND);
        glUseProgram(progHighlight);

        // Cubes: UBO selMask controls which fragments pass in highlight frag
        uint32_t cubeSelMask[4] = {0,0,0,0};
        for (int idx : s.selectedCubes) cubeSelMask[idx/32] |= (1u << (idx%32));
        uploadUBO(0, cubeSelMask, false);
        glBindVertexArray(cubeVao);
        glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)cubeIndexCount,
                                GL_UNSIGNED_SHORT, nullptr, INSTANCE_COUNT);

        if (meshLoaded && s.meshSelected) {
            uint32_t allSel[4] = {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu};
            uploadUBO(0, allSel, false);
            glBindVertexArray(meshVao);
            glDrawElements(GL_TRIANGLES, (GLsizei)meshIndexCount, GL_UNSIGNED_INT, nullptr);
        }
    }

    // ── Pass 4.5: masking — dim highlight mask where occluded by main scene ─────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 5,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 4.5: Masking");
    {
        glBindFramebuffer(GL_FRAMEBUFFER, maskingFbo);
        glViewport(0, 0, w, h);
        float zero = 0.0f;
        glClearBufferfv(GL_COLOR, 0, &zero);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDisable(GL_BLEND);
        glUseProgram(progMasking);
        glUniform1f(maskingLocAlpha, _input->state.occlusionAlpha);
        glBindTextureUnit(7, depthTex);           // binding=7: main scene depth
        glBindTextureUnit(8, highlightDepthTex);  // binding=8: selected objects' depths
        glBindTextureUnit(9, highlightTex);        // binding=9: raw R8 mask
        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // ── Pass 5: outline → outline FBO ────────────────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 6,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 5: Outline");
    {
        const Vec3& oc = _input->state.outlineColor;
        glBindFramebuffer(GL_FRAMEBUFFER, outlineFbo);
        glViewport(0, 0, w, h);
        float zero[4] = {};
        glClearBufferfv(GL_COLOR, 0, zero);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glDisable(GL_BLEND);
        glUseProgram(progOutline);
        glBindTextureUnit(7, maskedHighlightTex);
        glUniform2f(outlineLocTexelSize, 1.0f / w, 1.0f / h);
        glUniform4f(outlineLocColor, oc.x, oc.y, oc.z, 1.0f);
        glUniform1f(outlineLocThickness,  _input->state.outlineThickness);
        glUniform1f(outlineLocAntialiased, _input->state.outlineAntialiased ? 1.0f : 0.0f);
        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // ── Pass 6: blend outline onto main FBO ──────────────────────────────────
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 7,
        GL_DEBUG_SEVERITY_NOTIFICATION, -1, "Pass 6: Blend");
    {
        glBindFramebuffer(GL_FRAMEBUFFER, mainFbo);
        glViewport(0, 0, w, h);
        glDisable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(progBlend);
        glBindTextureUnit(7, outlineTex);
        glUniform2f(blendLocTexelSize, 1.0f / w, 1.0f / h);
        glBindVertexArray(quadVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    // ── ImGui ────────────────────────────────────────────────────────────────
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    renderUI();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // ── Blit main FBO to screen ───────────────────────────────────────────────
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mainFbo);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glfwSwapBuffers(window);
}

// ─── Texture helpers ─────────────────────────────────────────────────────────

void RendererGL::createDefaultTextures() {
    // Albedo: 1x1 white
    float white[4] = {1,1,1,1};
    glCreateTextures(GL_TEXTURE_2D, 1, &albedoTex);
    glTextureStorage2D(albedoTex, 1, GL_RGBA32F, 1, 1);
    glTextureSubImage2D(albedoTex, 0, 0, 0, 1, 1, GL_RGBA, GL_FLOAT, white);
    glTextureParameteri(albedoTex, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(albedoTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Irradiance: 1x1 black cubemap
    float black[4] = {0,0,0,1};
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &irradianceCube);
    glTextureStorage2D(irradianceCube, 1, GL_RGBA32F, 1, 1);
    for (int f = 0; f < 6; f++)
        glTextureSubImage3D(irradianceCube, 0, 0, 0, f, 1, 1, 1, GL_RGBA, GL_FLOAT, black);
    glTextureParameteri(irradianceCube, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(irradianceCube, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Prefiltered env: 1x1 black cubemap (NUM_ENV_MIPS mip levels)
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &prefilteredEnv);
    glTextureStorage2D(prefilteredEnv, NUM_ENV_MIPS, GL_RGBA32F, 1, 1);
    for (int m = 0; m < NUM_ENV_MIPS; m++)
        for (int f = 0; f < 6; f++)
            glTextureSubImage3D(prefilteredEnv, m, 0, 0, f, 1, 1, 1, GL_RGBA, GL_FLOAT, black);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MAX_LEVEL, NUM_ENV_MIPS - 1);

    // BRDF LUT: 1x1 dummy — real LUT is computed in loadEnvMap() when first needed
    float lutDummy[4] = {1,0,0,1};
    glCreateTextures(GL_TEXTURE_2D, 1, &brdfLUT);
    glTextureStorage2D(brdfLUT, 1, GL_RGBA32F, 1, 1);
    glTextureSubImage2D(brdfLUT, 0, 0, 0, 1, 1, GL_RGBA, GL_FLOAT, lutDummy);
    glTextureParameteri(brdfLUT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(brdfLUT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(brdfLUT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(brdfLUT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void RendererGL::loadAlbedoTexture(const std::string& path) {
    auto img = loadImageLDR(path.c_str());
    if (img.data.empty()) { std::cerr << "Failed to load texture: " << path << "\n"; return; }

    glDeleteTextures(1, &albedoTex); albedoTex = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &albedoTex);
    int mips = 1 + (int)std::floor(std::log2(std::max(img.w, img.h)));
    glTextureStorage2D(albedoTex, mips, GL_RGBA8, img.w, img.h);

    // Convert back to RGBA8 for upload
    std::vector<uint8_t> bytes(img.data.size());
    for (size_t i = 0; i < bytes.size(); i++)
        bytes[i] = (uint8_t)std::clamp(img.data[i] * 255.f, 0.f, 255.f);
    glTextureSubImage2D(albedoTex, 0, 0, 0, img.w, img.h, GL_RGBA, GL_UNSIGNED_BYTE, bytes.data());
    glGenerateTextureMipmap(albedoTex);
    glTextureParameteri(albedoTex, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(albedoTex, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Anisotropic filtering
    float maxAniso = 1.f;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAniso);
    glTextureParameterf(albedoTex, GL_TEXTURE_MAX_ANISOTROPY, std::min(maxAniso, 16.f));

    _input->state.albedoTexPath = path;
    albedoLoaded = true;
}

void RendererGL::loadEnvMap(const std::string& path) {
    auto hdr = loadImageHDR(path.c_str());
    if (hdr.data.empty()) { std::cerr << "Failed to load HDR: " << path << "\n"; return; }

    // Convert equirectangular → cubemap → irradiance + prefiltered
    auto envCube   = equirectToCubemap(hdr, 512);
    auto irr       = computeIrradiance(envCube, 32);
    auto prefilter = computePrefilteredEnv(envCube, 128, NUM_ENV_MIPS, 128);

    // Upload irradiance cubemap
    glDeleteTextures(1, &irradianceCube); irradianceCube = 0;
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &irradianceCube);
    glTextureStorage2D(irradianceCube, 1, GL_RGBA32F, irr.size, irr.size);
    for (int f = 0; f < 6; f++)
        glTextureSubImage3D(irradianceCube, 0, 0, 0, f,
            irr.size, irr.size, 1, GL_RGBA, GL_FLOAT, irr.faces[f].data());
    glTextureParameteri(irradianceCube, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(irradianceCube, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(irradianceCube, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(irradianceCube, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(irradianceCube, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Upload prefiltered env cubemap (one mip per roughness level)
    glDeleteTextures(1, &prefilteredEnv); prefilteredEnv = 0;
    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &prefilteredEnv);
    glTextureStorage2D(prefilteredEnv, NUM_ENV_MIPS, GL_RGBA32F,
                       prefilter[0].size, prefilter[0].size);
    for (int m = 0; m < NUM_ENV_MIPS; m++)
        for (int f = 0; f < 6; f++)
            glTextureSubImage3D(prefilteredEnv, m, 0, 0, f,
                prefilter[m].size, prefilter[m].size, 1,
                GL_RGBA, GL_FLOAT, prefilter[m].faces[f].data());
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTextureParameteri(prefilteredEnv, GL_TEXTURE_MAX_LEVEL, NUM_ENV_MIPS - 1);

    // Upload original equirect HDR as 2D float texture for skybox background
    glDeleteTextures(1, &equirectTex2D); equirectTex2D = 0;
    glCreateTextures(GL_TEXTURE_2D, 1, &equirectTex2D);
    glTextureStorage2D(equirectTex2D, 1, GL_RGBA16F, hdr.w, hdr.h);
    // Convert float32 → float16 on upload (driver handles via GL_FLOAT source)
    glTextureSubImage2D(equirectTex2D, 0, 0, 0, hdr.w, hdr.h, GL_RGBA, GL_FLOAT, hdr.data.data());
    glTextureParameteri(equirectTex2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(equirectTex2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(equirectTex2D, GL_TEXTURE_WRAP_S, GL_REPEAT);       // longitude wraps
    glTextureParameteri(equirectTex2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// latitude clamps

    // BRDF LUT — compute once on first env map load
    if (!envLoaded) {
        auto lut = computeBRDFLUT(256, 512);
        glDeleteTextures(1, &brdfLUT); brdfLUT = 0;
        glCreateTextures(GL_TEXTURE_2D, 1, &brdfLUT);
        glTextureStorage2D(brdfLUT, 1, GL_RGBA32F, lut.w, lut.h);
        glTextureSubImage2D(brdfLUT, 0, 0, 0, lut.w, lut.h, GL_RGBA, GL_FLOAT, lut.data.data());
        glTextureParameteri(brdfLUT, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(brdfLUT, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(brdfLUT, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(brdfLUT, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    _input->state.envMapPath = path;
    envLoaded = true;
}

// ─── UI ──────────────────────────────────────────────────────────────────────

void RendererGL::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos (ImVec2(10, 10),   ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(260, 400),  ImGuiCond_FirstUseEver);
    ImGui::Begin("Scene");

    // ── Renderer ──────────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Renderer", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::TextDisabled("Active: OpenGL 4.6");
        if (ImGui::Button("Switch to Vulkan"))
            _input->state.switchRenderer = true;
        if (ImGui::Checkbox("MSAA 8x", &msaa8)) {
            cleanupFbos();
            createFbos(fbWidth, fbHeight);
        }
    }

    // ── Display mode ─────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Display Mode", ImGuiTreeNodeFlags_DefaultOpen)) {
        int mode = (int)_input->state.displayMode;
        ImGui::RadioButton("Solid",           &mode, (int)DisplayMode::Solid);
        ImGui::RadioButton("Wireframe",       &mode, (int)DisplayMode::Wireframe);
        ImGui::RadioButton("Solid+Wireframe", &mode, (int)DisplayMode::SolidWireframe);
        ImGui::RadioButton("Unlit",           &mode, (int)DisplayMode::Unlit);
        ImGui::RadioButton("Normals",         &mode, (int)DisplayMode::Normals);
        _input->state.displayMode = (DisplayMode)mode;

        ImGui::Spacing();
        Vec3& sc = _input->state.selectionColor;
        float hcol[3] = { sc.x, sc.y, sc.z };
        ImGui::Text("Highlight"); ImGui::SameLine();
        if (ImGui::ColorEdit3("##selcolor", hcol,
                ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel |
                ImGuiColorEditFlags_NoLabel))
            sc = { hcol[0], hcol[1], hcol[2] };
        Vec3& oc = _input->state.outlineColor;
        float ocol[3] = { oc.x, oc.y, oc.z };
        ImGui::Text("Outline"); ImGui::SameLine();
        if (ImGui::ColorEdit3("##outcolor", ocol,
                ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel |
                ImGuiColorEditFlags_NoLabel))
            oc = { ocol[0], ocol[1], ocol[2] };
        ImGui::SliderFloat("Outline Thickness", &_input->state.outlineThickness, 1.0f, 8.0f, "%.1f");
        ImGui::Checkbox("Antialiased Outline", &_input->state.outlineAntialiased);
        ImGui::SliderFloat("Occluded Alpha",    &_input->state.occlusionAlpha,   0.0f, 1.0f, "%.2f");
    }

    // ── Lighting ─────────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Lighting", ImGuiTreeNodeFlags_DefaultOpen)) {
        LightParams& lp = _input->state.light;
        ImGui::SliderFloat("X##lx", &lp.pos[0], -20.0f, 20.0f, "%.1f");
        ImGui::SliderFloat("Y##ly", &lp.pos[1], -20.0f, 20.0f, "%.1f");
        ImGui::SliderFloat("Z##lz", &lp.pos[2], -20.0f, 20.0f, "%.1f");
        ImGui::Text("Color"); ImGui::SameLine();
        ImGui::ColorEdit3("##lcolor", lp.color,
            ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel |
            ImGuiColorEditFlags_NoLabel);
        ImGui::SliderFloat("Intensity", &lp.intensity, 0.0f, 5.0f, "%.2f");
    }

    // ── Material ─────────────────────────────────────────────────────────────
    {
        bool meshSel     = meshLoaded && _input->state.meshSelected;
        const auto& csel = _input->state.selectedCubes;

        char matHeader[64];
        if (meshSel)
            snprintf(matHeader, sizeof(matHeader), "Material (Loaded Model)");
        else if (csel.size() == 1)
            snprintf(matHeader, sizeof(matHeader), "Material (1 cube)");
        else if (csel.size() > 1)
            snprintf(matHeader, sizeof(matHeader), "Material (%d cubes)", (int)csel.size());
        else
            snprintf(matHeader, sizeof(matHeader), "Material (Default)");

        if (ImGui::CollapsingHeader(matHeader, ImGuiTreeNodeFlags_DefaultOpen)) {
            if (meshSel) {
                if (materialEditor("mat",
                        meshMaterial.color, meshMaterial.alpha,
                        meshMaterial.ambient, meshMaterial.diffuse,
                        meshMaterial.specular, meshMaterial.shininess,
                        meshMaterial.materialType,
                        meshMaterial.p0, meshMaterial.p1,
                        meshMaterial.p2, meshMaterial.p3)) {
                    meshInstanceData.color[0]     = meshMaterial.color[0];
                    meshInstanceData.color[1]     = meshMaterial.color[1];
                    meshInstanceData.color[2]     = meshMaterial.color[2];
                    meshInstanceData.color[3]     = meshMaterial.alpha;
                    meshInstanceData.ambient      = meshMaterial.ambient;
                    meshInstanceData.diffuse      = meshMaterial.diffuse;
                    meshInstanceData.specular     = meshMaterial.specular;
                    meshInstanceData.shininess    = meshMaterial.shininess;
                    meshInstanceData.materialType = meshMaterial.materialType;
                    meshInstanceData.p0 = meshMaterial.p0; meshInstanceData.p1 = meshMaterial.p1;
                    meshInstanceData.p2 = meshMaterial.p2; meshInstanceData.p3 = meshMaterial.p3;
                    glNamedBufferSubData(meshInstanceVbo, 0, sizeof(InstanceData), &meshInstanceData);
                }
            } else if (!csel.empty()) {
                int first = *csel.begin();
                InstanceData& ref = instanceData[first];
                float col[3] = { ref.color[0], ref.color[1], ref.color[2] };
                float alpha  = ref.color[3];
                if (materialEditor("mat",
                        col, alpha,
                        ref.ambient, ref.diffuse, ref.specular, ref.shininess,
                        ref.materialType, ref.p0, ref.p1, ref.p2, ref.p3)) {
                    for (int idx : csel) {
                        instanceData[idx].color[0]     = col[0];
                        instanceData[idx].color[1]     = col[1];
                        instanceData[idx].color[2]     = col[2];
                        instanceData[idx].color[3]     = alpha;
                        instanceData[idx].ambient      = ref.ambient;
                        instanceData[idx].diffuse      = ref.diffuse;
                        instanceData[idx].specular     = ref.specular;
                        instanceData[idx].shininess    = ref.shininess;
                        instanceData[idx].materialType = ref.materialType;
                        instanceData[idx].p0 = ref.p0; instanceData[idx].p1 = ref.p1;
                        instanceData[idx].p2 = ref.p2; instanceData[idx].p3 = ref.p3;
                    }
                    glNamedBufferSubData(cubeInstanceVbo, 0, sizeof(instanceData), instanceData.data());
                }
            } else {
                // No selection — changes apply to all cubes immediately
                Material& dm = _input->state.defaultMaterial;
                if (materialEditor("mat",
                        dm.color, dm.alpha,
                        dm.ambient, dm.diffuse,
                        dm.specular, dm.shininess,
                        dm.materialType,
                        dm.p0, dm.p1,
                        dm.p2, dm.p3)) {
                    for (auto& d : instanceData) {
                        d.color[0] = dm.color[0];
                        d.color[1] = dm.color[1];
                        d.color[2] = dm.color[2];
                        d.color[3] = dm.alpha;
                        d.ambient      = dm.ambient;
                        d.diffuse      = dm.diffuse;
                        d.specular     = dm.specular;
                        d.shininess    = dm.shininess;
                        d.materialType = dm.materialType;
                        d.p0 = dm.p0; d.p1 = dm.p1;
                        d.p2 = dm.p2; d.p3 = dm.p3;
                    }
                    glNamedBufferSubData(cubeInstanceVbo, 0, sizeof(instanceData), instanceData.data());
                }
            }
        }
    }

    // ── Textures & IBL ───────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Texture & Environment", ImGuiTreeNodeFlags_DefaultOpen)) {
        // Albedo texture
        if (ImGui::Button("Load Albedo Texture...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFilter = "Images\0*.png;*.jpg;*.jpeg;*.bmp\0All Files\0*.*\0";
            ofn.lpstrFile = buf; ofn.nMaxFile = sizeof(buf);
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle = "Load Albedo Texture";
            if (GetOpenFileNameA(&ofn)) loadAlbedoTexture(buf);
        }
        if (albedoLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Clear##atex")) {
                albedoLoaded = false;
                _input->state.albedoTexPath.clear();
            }
            ImGui::TextDisabled("%s", _input->state.albedoTexPath.c_str());
        }

        ImGui::Spacing();

        // HDR environment map
        if (ImGui::Button("Load HDR Environment...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFilter = "HDR Images\0*.hdr;*.exr\0All Files\0*.*\0";
            ofn.lpstrFile = buf; ofn.nMaxFile = sizeof(buf);
            ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle = "Load HDR Environment";
            if (GetOpenFileNameA(&ofn)) loadEnvMap(buf);
        }
        if (envLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Clear##env")) {
                envLoaded = false;
                _input->state.envMapPath.clear();
            }
            ImGui::SliderFloat("IBL Intensity", &_input->state.iblIntensity, 0.0f, 5.0f, "%.2f");
            ImGui::TextDisabled("%s", _input->state.envMapPath.c_str());
        }
    }

    // ── 3D Model loader ───────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("3D Model", ImGuiTreeNodeFlags_DefaultOpen)) {
        static char meshPath[512] = "";

        if (ImGui::Button("Open File...")) {
            OPENFILENAMEA ofn{};
            char buf[512] = {};
            ofn.lStructSize = sizeof(ofn);
            ofn.lpstrFilter = "3D Models\0*.gltf;*.glb;*.obj\0"
                              "GLTF\0*.gltf;*.glb\0"
                              "Wavefront OBJ\0*.obj\0"
                              "All Files\0*.*\0";
            ofn.lpstrFile   = buf;
            ofn.nMaxFile    = sizeof(buf);
            ofn.Flags       = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;
            ofn.lpstrTitle  = "Open 3D Model";
            if (GetOpenFileNameA(&ofn)) {
                memcpy(meshPath, buf, sizeof(meshPath));
                loadMesh(meshPath);
            }
        }
        ImGui::SetNextItemWidth(-1);
        if (ImGui::InputText("##meshpath", meshPath, sizeof(meshPath),
                             ImGuiInputTextFlags_EnterReturnsTrue))
            loadMesh(meshPath);

        if (meshLoaded) {
            ImGui::SameLine();
            if (ImGui::Button("Unload")) unloadMesh();
            ImGui::TextDisabled("%u tris — click to select", meshIndexCount / 3);
        }
        if (!meshError.empty())
            ImGui::TextColored(ImVec4(1,0.3f,0.3f,1), "%s", meshError.c_str());
    }

    ImGui::End();
}

// ─── Main loop ───────────────────────────────────────────────────────────────

void RendererGL::mainLoop() {
    while (!glfwWindowShouldClose(window) && !_input->state.switchRenderer) {
        glfwPollEvents();
        drawFrame();
    }
}

void RendererGL::cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    if (meshLoaded) unloadMesh();

    glDeleteTextures(1, &albedoTex);
    glDeleteTextures(1, &irradianceCube);
    glDeleteTextures(1, &prefilteredEnv);
    glDeleteTextures(1, &brdfLUT);

    glDeleteProgram(progMain);
    glDeleteProgram(progOit);
    glDeleteProgram(progComposite);
    glDeleteVertexArrays(1, &cubeVao);
    glDeleteVertexArrays(1, &quadVao);
    glDeleteBuffers(1, &cubeVbo);
    glDeleteBuffers(1, &cubeIbo);
    glDeleteBuffers(1, &cubeInstanceVbo);
    glDeleteBuffers(1, &sceneUbo);
    cleanupFbos();

    glfwDestroyWindow(window);
}

// ─── Entry point ─────────────────────────────────────────────────────────────

void RendererGL::run(InputHandler& input) {
    _input = &input;

    if (!glfwInit()) throw std::runtime_error("glfwInit failed");

    initWindow();
    createPrograms();
    createGeometry();
    createSceneUbo();
    createDefaultTextures();

    // Restore textures from previous renderer session
    if (!_input->state.albedoTexPath.empty()) loadAlbedoTexture(_input->state.albedoTexPath);
    if (!_input->state.envMapPath.empty())    loadEnvMap(_input->state.envMapPath);

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    createFbos(w, h);
    glExtent.width  = (uint32_t)w;
    glExtent.height = (uint32_t)h;
    _input->setPickContext(&glExtent, &cubePositions);

    initImGui();
    mainLoop();
    cleanup();

    glfwTerminate();
}

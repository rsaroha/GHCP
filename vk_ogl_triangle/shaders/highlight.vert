#version 450

layout(push_constant) uniform PC {
    mat4  mvp_base;
    mat4  mv_base;
    vec4  selectionColor;
    vec4  lightPos;
    vec4  lightColor;
    int   shaderMode;
    int   hasAlbedoTex;
    int   hasEnvMap;
    float iblIntensity;
    uint  selectionMask[4];
} pc;

layout(location = 0)  in vec3 inPosition;
layout(location = 9)  in vec3 inNormal;
layout(location = 10) in vec2 inUV;

layout(location = 1) in vec4 instCol0;
layout(location = 2) in vec4 instCol1;
layout(location = 3) in vec4 instCol2;
layout(location = 4) in vec4 instCol3;
layout(location = 5) in vec4 instColor;
layout(location = 6) in vec4 instMaterial;
layout(location = 7) in int  instMatType;
layout(location = 8) in vec4 instMatParams;

layout(location = 0) out vec4      fragColor;
layout(location = 1) out vec3      viewPos;
layout(location = 2) out float     isSelected;
layout(location = 3) out flat int  outShaderMode;
layout(location = 4) out vec4      fragMaterial;
layout(location = 5) out flat int  fragMatType;
layout(location = 6) out vec4      fragMatParams;
layout(location = 7) out vec3      fragNormal;
layout(location = 8) out vec2      fragUV;

void main() {
    mat4 inst   = mat4(instCol0, instCol1, instCol2, instCol3);
    vec4 lp     = inst * vec4(inPosition, 1.0);
    gl_Position = pc.mvp_base * lp;
    fragColor   = instColor;
    viewPos     = (pc.mv_base * lp).xyz;
    fragNormal  = normalize(mat3(pc.mv_base) * mat3(inst) * inNormal);
    fragUV      = inUV;
    uint bitIdx  = uint(gl_InstanceIndex);
    uint wordIdx = bitIdx / 32u;
    uint bitPos  = bitIdx % 32u;
    isSelected   = float((pc.selectionMask[wordIdx] >> bitPos) & 1u);
    outShaderMode = pc.shaderMode;
    fragMaterial  = instMaterial;
    fragMatType   = instMatType;
    fragMatParams = instMatParams;
}

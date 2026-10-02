#version 450

layout(set = 0, binding = 0) uniform sampler2D mainDepth;
layout(set = 0, binding = 1) uniform sampler2D highlightDepth;
layout(set = 0, binding = 2) uniform sampler2D highlightMask;

layout(push_constant) uniform PC { float occlusionAlpha; } pc;

layout(location = 0) out vec4 outMask;

void main() {
    ivec2 c   = ivec2(gl_FragCoord.xy);
    float md  = texelFetch(mainDepth,      c, 0).r;
    float hd  = texelFetch(highlightDepth, c, 0).r;
    vec4  src = texelFetch(highlightMask,  c, 0);
    float a   = src.a * ((hd > md + 0.0001) ? pc.occlusionAlpha : 1.0);
    outMask = vec4(src.rgb, a);
}

#version 450

layout(set = 0, binding = 0) uniform sampler2D accumInput;
layout(set = 0, binding = 1) uniform sampler2D revealInput;

layout(location = 0) out vec4 outColor;

void main() {
    ivec2 coord = ivec2(gl_FragCoord.xy);
    float reveal = texelFetch(revealInput, coord, 0).r;
    if (abs(reveal - 1.0) < 1e-4) discard;

    vec4 accum = texelFetch(accumInput, coord, 0);
    vec3 avgColor = accum.rgb / max(accum.a, 1e-5);
    outColor = vec4(avgColor, 1.0 - reveal);
}

#version 450

layout(set = 0, binding = 0) uniform sampler2D outlineTex;

layout(push_constant) uniform PC { vec2 texelSize; } pc;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = texture(outlineTex, gl_FragCoord.xy * pc.texelSize);
}

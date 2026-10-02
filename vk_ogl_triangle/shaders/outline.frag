#version 450

layout(set = 0, binding = 0) uniform sampler2D highlightMask;

layout(push_constant) uniform PC {
    vec2  texelSize;      // offset  0
    float thickness;      // offset  8
    float antialiased;    // offset 12
    vec4  outlineColor;   // offset 16
} pc;

layout(location = 0) out vec4 outColor;

void main() {
    vec2  uv  = gl_FragCoord.xy * pc.texelSize;
    vec4  src = texture(highlightMask, uv);
    // Binarize: any non-zero alpha (visible or occluded selection) counts as inside
    float mask = step(0.001, src.a);
    float s    = pc.thickness * 0.5;

    #define S(off) step(0.001, texture(highlightMask, uv + (off) * pc.texelSize * s).a)
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
    if (pc.antialiased > 0.5) {
        outColor = mix(src, vec4(pc.outlineColor.rgb, 1.0), smoothstep(0.0, 1.0, isOutline));
    } else {
        outColor = isOutline > 0.5 ? vec4(pc.outlineColor.rgb, 1.0) : src;
    }
}

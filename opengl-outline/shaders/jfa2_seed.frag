#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
out vec4 color;

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    bool inside = texelFetch(stencilMask, pixel, 0).r != 0u;
    float signedDistance = inside ? -1.0e4 : 1.0e4;
    color = vec4(vec2(pixel) + vec2(0.5), signedDistance, 1.0);
}

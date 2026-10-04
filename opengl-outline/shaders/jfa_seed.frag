#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
out vec4 color;

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    uint stencil = texelFetch(stencilMask, pixel, 0).r;
    if (stencil >= 1u)
    {
        color = vec4(float(pixel.x) + 0.5, float(pixel.y) + 0.5, 0.0, 1.0);
    }
    else
    {
        color = vec4(-1.0, -1.0, 0.0, 1.0);
    }
}

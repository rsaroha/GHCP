#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
out vec4 color;

uint ReadStencil(ivec2 pixel, ivec2 size)
{
    return texelFetch(stencilMask, clamp(pixel, ivec2(0), size - 1), 0).r;
}

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    uint center = ReadStencil(pixel, size);
    vec2 position = vec2(pixel) + vec2(0.5);

    if (center != 0u)
    {
        color = vec4(position, 0.0, 1.0);
        return;
    }

    float values[9];
    int index = 0;
    bool hasSilhouetteNeighbor = false;
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            values[index] = ReadStencil(pixel + ivec2(x, y), size) == 0u ? 0.0 : 1.0;
            hasSilhouetteNeighbor = hasSilhouetteNeighbor || values[index] > 0.0;
            ++index;
        }
    }

    if (!hasSilhouetteNeighbor)
    {
        color = vec4(-1.0, -1.0, 0.0, 1.0);
        return;
    }

    float gx = values[0] + 2.0 * values[3] + values[6]
             - values[2] - 2.0 * values[5] - values[8];
    float gy = values[0] + 2.0 * values[1] + values[2]
             - values[6] - 2.0 * values[7] - values[8];
    vec2 direction = -vec2(gx, gy);
    float directionLength = length(direction);

    if (directionLength <= 0.005)
    {
        color = vec4(position, 0.0, 1.0);
        return;
    }

    direction /= directionLength;
    vec2 subpixelPosition = position + direction * 0.5;
    color = vec4(subpixelPosition, 0.0, 1.0);
}

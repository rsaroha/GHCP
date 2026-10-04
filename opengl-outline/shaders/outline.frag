#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneColor;
uniform usampler2D stencilMask;
uniform vec2 texelSize;
uniform int outlineImplementation;
uniform float outlineWidth;
out vec4 color;

uint ReadStencil(ivec2 pixel, ivec2 size)
{
    ivec2 clamped = clamp(pixel, ivec2(0), size - 1);
    return texelFetch(stencilMask, clamped, 0).r;
}

int ComputeOutlineRadius()
{
    int radius = int(outlineWidth + 0.5);
    radius = clamp(radius, 1, 32);
    return radius;
}

uint ComputeBruteForceNeighbor(ivec2 pixel, ivec2 size, int radius)
{
    uint neighbor = 0u;
    for (int y = -32; y <= 32; ++y)
    {
        if (abs(y) > radius)
        {
            continue;
        }

        for (int x = -32; x <= 32; ++x)
        {
            if (abs(x) > radius)
            {
                continue;
            }
            neighbor = max(neighbor, ReadStencil(pixel + ivec2(x, y), size));
        }
    }
    return neighbor;
}

uint ComputeCrossNeighbor(ivec2 pixel, ivec2 size, int radius)
{
    uint neighbor = 0u;
    for (int step = -32; step <= 32; ++step)
    {
        if (abs(step) > radius)
        {
            continue;
        }
        neighbor = max(neighbor, ReadStencil(pixel + ivec2(step, 0), size));
        neighbor = max(neighbor, ReadStencil(pixel + ivec2(0, step), size));
    }
    return neighbor;
}

void main()
{
    vec4 scene = texture(sceneColor, uv);
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    int radius = ComputeOutlineRadius();
    uint center = ReadStencil(pixel, size);
    uint neighbor = 0u;

    if (outlineImplementation == 0)
    {
        neighbor = ComputeBruteForceNeighbor(pixel, size, radius);
    }
    else
    {
        neighbor = ComputeCrossNeighbor(pixel, size, radius);
    }

    bool outsideEdge = neighbor >= 1u && center == 0u;
    vec3 result = mix(scene.rgb, vec3(1.0, 0.0, 0.0), outsideEdge);
    color = vec4(result, 1.0);
}

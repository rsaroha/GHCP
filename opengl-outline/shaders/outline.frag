#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneColor;
uniform usampler2D stencilMask;
uniform vec2 texelSize;
uniform int outlineImplementation;
uniform float outlineWidth;
uniform int outlineAntialiasing;
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

float ComputeBruteForceDistance(ivec2 pixel, ivec2 size, int radius, uint targetStencil)
{
    float nearestDistance = 1.0e30;
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
            if (ReadStencil(pixel + ivec2(x, y), size) == targetStencil)
            {
                vec2 offset = vec2(float(x), float(y));
                nearestDistance = min(nearestDistance, length(offset));
            }
        }
    }
    return nearestDistance;
}

float ComputeCrossDistance(ivec2 pixel, ivec2 size, int radius, uint targetStencil)
{
    float nearestDistance = 1.0e30;
    for (int step = -32; step <= 32; ++step)
    {
        if (abs(step) > radius)
        {
            continue;
        }
        if (ReadStencil(pixel + ivec2(step, 0), size) == targetStencil)
        {
            nearestDistance = min(nearestDistance, abs(float(step)));
        }
        if (ReadStencil(pixel + ivec2(0, step), size) == targetStencil)
        {
            nearestDistance = min(nearestDistance, abs(float(step)));
        }
    }
    return nearestDistance;
}

float ComputeGaussianCoverage(ivec2 pixel, ivec2 size)
{
    float sigma = max(outlineWidth * 0.5, 0.5);
    float twoSigmaSquared = 2.0 * sigma * sigma;
    int radius = clamp(int(ceil(outlineWidth)), 1, 32);
    float weightedMask = 0.0;
    float totalWeight = 0.0;

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

            float distanceSquared = float(x * x + y * y);
            float weight = exp(-distanceSquared / twoSigmaSquared);
            ivec2 samplePixel = clamp(pixel + ivec2(x, y), ivec2(0), size - 1);
            float mask = ReadStencil(samplePixel, size) == 0u ? 0.0 : 1.0;
            weightedMask += mask * weight;
            totalWeight += weight;
        }
    }

    float blurredMask = weightedMask / totalWeight;
    if (outlineAntialiasing != 0)
    {
        return smoothstep(0.02, 0.5, blurredMask);
    }

    return blurredMask >= 0.05 ? 1.0 : 0.0;
}

void main()
{
    vec4 scene = texture(sceneColor, uv);
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    int radius = ComputeOutlineRadius();
    uint center = ReadStencil(pixel, size);
    uint targetStencil = 1u;
    float nearestDistance;
    float outlineCoverage;

    if (outlineImplementation == 3)
    {
        outlineCoverage = center == 0u ? ComputeGaussianCoverage(pixel, size) : 0.0;
    }
    else if (outlineImplementation == 0)
    {
        nearestDistance = ComputeBruteForceDistance(pixel, size, radius, targetStencil);
    }
    else
    {
        nearestDistance = ComputeCrossDistance(pixel, size, radius, targetStencil);
    }

    if (outlineImplementation != 3 && outlineAntialiasing != 0)
    {
        float antialiasWidth = max(fwidth(nearestDistance), 1.0);
        outlineCoverage = 1.0 - smoothstep(
            outlineWidth - antialiasWidth,
            outlineWidth + antialiasWidth,
            nearestDistance);
    }
    else
    {
        outlineCoverage = nearestDistance <= outlineWidth ? 1.0 : 0.0;
    }
    if (center != 0u)
    {
        outlineCoverage = 0.0;
    }
    vec3 result = mix(scene.rgb, vec3(1.0, 0.0, 0.0), outlineCoverage);
    color = vec4(result, 1.0);
}

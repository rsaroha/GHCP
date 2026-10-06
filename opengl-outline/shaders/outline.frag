#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
uniform int outlineImplementation;
uniform float outlineWidth;
uniform int outlineAntialiasing;
uniform int interiorOutline;
uniform int exteriorOutline;
out vec4 color;

uint ReadStencil(ivec2 pixel, ivec2 size)
{
    return texelFetch(stencilMask, clamp(pixel, ivec2(0), size - 1), 0).r;
}

float OutlineRadiusPixels()
{
    return max(0.5, outlineWidth * 0.5);
}

int OutlineRadius()
{
    return clamp(int(ceil(OutlineRadiusPixels())), 1, 100);
}

float ComputeBruteForceDistance(ivec2 pixel, ivec2 size, int radius)
{
    float nearestDistance = 1.0e30;
    for (int y = -100; y <= 100; ++y)
    {
        if (abs(y) > radius) continue;
        for (int x = -100; x <= 100; ++x)
        {
            if (abs(x) > radius) continue;
            if (ReadStencil(pixel + ivec2(x, y), size) != 0u)
            {
                nearestDistance = min(nearestDistance, length(vec2(x, y)));
            }
        }
    }
    return nearestDistance;
}

float ComputeCrossDistance(ivec2 pixel, ivec2 size, int radius)
{
    float nearestDistance = 1.0e30;
    for (int offset = -100; offset <= 100; ++offset)
    {
        if (abs(offset) > radius) continue;
        if (ReadStencil(pixel + ivec2(offset, 0), size) != 0u)
            nearestDistance = min(nearestDistance, abs(float(offset)));
        if (ReadStencil(pixel + ivec2(0, offset), size) != 0u)
            nearestDistance = min(nearestDistance, abs(float(offset)));
    }
    return nearestDistance;
}

float ComputeInteriorCoverage(ivec2 pixel, ivec2 size, int radius)
{
    float nearestDistance = 1.0e30;
    for (int y = -100; y <= 100; ++y)
    {
        if (abs(y) > radius) continue;
        for (int x = -100; x <= 100; ++x)
        {
            if (abs(x) > radius) continue;
            if (ReadStencil(pixel + ivec2(x, y), size) == 0u)
                nearestDistance = min(nearestDistance, length(vec2(x, y)));
        }
    }
    if (nearestDistance >= 1.0e29) return 0.0;
    if (outlineAntialiasing != 0)
    {
        return 1.0 - smoothstep(
            OutlineRadiusPixels() - 1.0,
            OutlineRadiusPixels() + 1.0,
            nearestDistance);
    }
    return nearestDistance <= OutlineRadiusPixels() ? 1.0 : 0.0;
}

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    int radius = OutlineRadius();
    bool inside = ReadStencil(pixel, size) != 0u;
    float coverage = 0.0;

    if (inside)
    {
        if (interiorOutline != 0)
            coverage = ComputeInteriorCoverage(pixel, size, radius);
    }
    else if (exteriorOutline != 0)
    {
        float distanceToSilhouette = outlineImplementation == 1
            ? ComputeBruteForceDistance(pixel, size, radius)
            : ComputeCrossDistance(pixel, size, radius);
        if (outlineAntialiasing != 0)
        {
            float antialiasWidth = max(fwidth(distanceToSilhouette), 1.0);
            coverage = 1.0 - smoothstep(
                OutlineRadiusPixels() - antialiasWidth,
                OutlineRadiusPixels() + antialiasWidth,
                distanceToSilhouette);
        }
        else
        {
            coverage = distanceToSilhouette <= OutlineRadiusPixels() ? 1.0 : 0.0;
        }
    }

    color = vec4(vec3(1.0, 0.0, 0.0), coverage);
}

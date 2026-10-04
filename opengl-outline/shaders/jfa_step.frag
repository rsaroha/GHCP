#version 330 compatibility
in vec2 uv;
uniform sampler2D jfaInput;
uniform float jumpDistance;
out vec4 color;

vec2 ReadSeed(ivec2 pixel, ivec2 size)
{
    ivec2 clamped = clamp(pixel, ivec2(0), size - 1);
    return texelFetch(jfaInput, clamped, 0).rg;
}

bool IsValidSeed(vec2 seed)
{
    return seed.x >= 0.0 && seed.y >= 0.0;
}

void main()
{
    ivec2 size = textureSize(jfaInput, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    vec2 pixelCenter = vec2(float(pixel.x) + 0.5, float(pixel.y) + 0.5);
    int stepSize = int(jumpDistance + 0.5);
    if (stepSize < 1)
    {
        stepSize = 1;
    }

    vec2 bestSeed = vec2(-1.0, -1.0);
    float bestDistance = 1.0e30;
    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            ivec2 samplePixel = pixel + ivec2(x, y) * stepSize;
            vec2 candidate = ReadSeed(samplePixel, size);
            if (!IsValidSeed(candidate))
            {
                continue;
            }

            vec2 delta = candidate - pixelCenter;
            float distanceSquared = dot(delta, delta);
            if (distanceSquared < bestDistance)
            {
                bestDistance = distanceSquared;
                bestSeed = candidate;
            }
        }
    }

    color = vec4(bestSeed, 0.0, 1.0);
}

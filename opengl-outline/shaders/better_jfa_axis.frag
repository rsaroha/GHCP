#version 330 compatibility
in vec2 uv;
uniform sampler2D jfaInput;
uniform vec2 axisWidth;
out vec4 color;

void main()
{
    ivec2 size = textureSize(jfaInput, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    vec2 pixelCenter = vec2(pixel) + vec2(0.5);
    vec2 bestSeed = vec2(-1.0);
    float bestDistance = 1.0e30;
    int stepSize = max(int(abs(axisWidth.x) + abs(axisWidth.y) + 0.5), 1);

    for (int i = -1; i <= 1; ++i)
    {
        ivec2 samplePixel = clamp(pixel + ivec2(axisWidth * float(i)), ivec2(0), size - 1);
        vec2 candidate = texelFetch(jfaInput, samplePixel, 0).rg;
        if (candidate.x < 0.0 || candidate.y < 0.0)
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

    color = vec4(bestSeed, 0.0, 1.0);
}

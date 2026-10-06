#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
uniform sampler2D sobelInput;
uniform float outlineWidth;
uniform int outlineAntialiasing;
uniform int interiorOutline;
uniform int exteriorOutline;
uniform int passMode;
out vec4 color;

float Mask(ivec2 pixel, ivec2 size)
{
    return texelFetch(stencilMask, clamp(pixel, ivec2(0), size - 1), 0).r == 0u ? 0.0 : 1.0;
}

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);

    if (passMode == 0)
    {
        float left = Mask(pixel + ivec2(-1, 0), size);
        float center = Mask(pixel, size);
        float right = Mask(pixel + ivec2(1, 0), size);
        float horizontalDerivative = right - left;
        float horizontalSmooth = left + 2.0 * center + right;
        color = vec4(horizontalDerivative, horizontalSmooth, 0.0, 1.0);
        return;
    }

    bool inside = Mask(pixel, size) > 0.5;
    if ((inside && interiorOutline == 0) || (!inside && exteriorOutline == 0))
    {
        color = vec4(0.0);
        return;
    }

    int radius = clamp(int(ceil(max(0.5, outlineWidth * 0.5))), 1, 100);
    float edge = 0.0;
    for (int offset = -100; offset <= 100; ++offset)
    {
        if (abs(offset) > radius) continue;
        ivec2 samplePixel = clamp(pixel + ivec2(0, offset), ivec2(0), size - 1);
        float leftDerivative = texelFetch(sobelInput, clamp(samplePixel + ivec2(0, -1), ivec2(0), size - 1), 0).r;
        float centerDerivative = texelFetch(sobelInput, samplePixel, 0).r;
        float rightDerivative = texelFetch(sobelInput, clamp(samplePixel + ivec2(0, 1), ivec2(0), size - 1), 0).r;
        float gx = leftDerivative + 2.0 * centerDerivative + rightDerivative;

        float smoothBelow = texelFetch(sobelInput, clamp(samplePixel + ivec2(0, -1), ivec2(0), size - 1), 0).g;
        float smoothAbove = texelFetch(sobelInput, clamp(samplePixel + ivec2(0, 1), ivec2(0), size - 1), 0).g;
        float gy = smoothAbove - smoothBelow;
        edge = max(edge, clamp(length(vec2(gx, gy)) / 8.0, 0.0, 1.0));
    }

    float coverage = outlineAntialiasing != 0 ? smoothstep(0.05, 0.75, edge) : step(0.5, edge);
    color = vec4(vec3(1.0, 0.0, 0.0), coverage);
}

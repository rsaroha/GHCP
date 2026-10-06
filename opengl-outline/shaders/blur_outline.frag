#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
uniform sampler2D blurInput;
uniform sampler2D sceneColor;
uniform int passMode;
uniform int blurRadius;
uniform int blurType;
uniform vec2 blurDirection;
uniform int interiorOutline;
uniform int exteriorOutline;
out vec4 color;

uint ReadStencil(ivec2 pixel, ivec2 size)
{
    return texelFetch(stencilMask, clamp(pixel, ivec2(0), size - 1), 0).r;
}

float GaussianWeight(float distance, float sigma)
{
    return exp(-(distance * distance) / (2.0 * sigma * sigma));
}

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);

    if (passMode != 2)
    {
        float sigma = max(float(blurRadius) * 0.5, 0.5);
        float weightedMask = 0.0;
        float totalWeight = 0.0;
        for (int offset = -100; offset <= 100; ++offset)
        {
            if (abs(offset) > blurRadius)
            {
                continue;
            }
            float weight = blurType == 0 ? GaussianWeight(float(offset), sigma) : 1.0;
            ivec2 samplePixel = pixel + ivec2(blurDirection * float(offset));
            float mask = passMode == 0
                ? (ReadStencil(samplePixel, size) == 0u ? 0.0 : 1.0)
                : texelFetch(blurInput, clamp(samplePixel, ivec2(0), size - 1), 0).r;
            weightedMask += mask * weight;
            totalWeight += weight;
        }
        color = vec4(weightedMask / totalWeight, 0.0, 0.0, 1.0);
        return;
    }

    vec4 scene = texture(sceneColor, uv);
    float blurredMask = texelFetch(blurInput, pixel, 0).r;
    uint center = ReadStencil(pixel, size);
    float coverage = 0.0;
    if (center == 0u)
    {
        coverage = exteriorOutline != 0 ? smoothstep(0.02, 0.5, blurredMask) : 0.0;
    }
    else if (interiorOutline != 0)
    {
        coverage = smoothstep(0.02, 0.5, 1.0 - blurredMask);
    }
    color = vec4(mix(scene.rgb, vec3(1.0, 0.0, 0.0), coverage), 1.0);
}

#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneColor;
uniform usampler2D stencilMask;
uniform sampler2D jfaResult;
uniform float outlineWidth;
uniform int outlineAntialiasing;
uniform int interiorOutline;
out vec4 color;

float InteriorCoverage(ivec2 pixel, ivec2 size, int radius)
{
    float nearestDistance = 1.0e30;
    for (int y = -radius; y <= radius; ++y)
    {
        for (int x = -radius; x <= radius; ++x)
        {
            if (texelFetch(stencilMask, clamp(pixel + ivec2(x, y), ivec2(0), size - 1), 0).r == 0u)
                nearestDistance = min(nearestDistance, length(vec2(x, y)));
        }
    }
    if (nearestDistance >= 1.0e29) return 0.0;
    return outlineAntialiasing != 0
        ? 1.0 - smoothstep(float(radius) - 1.0, float(radius) + 1.0, nearestDistance)
        : (nearestDistance <= float(radius) ? 1.0 : 0.0);
}

void main()
{
    vec4 scene = texture(sceneColor, uv);
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    if (texelFetch(stencilMask, pixel, 0).r != 0u)
    {
        float coverage = interiorOutline != 0 ? InteriorCoverage(pixel, size, int(outlineWidth + 0.5)) : 0.0;
        color = vec4(mix(scene.rgb, vec3(1.0, 0.0, 0.0), coverage), 1.0);
        return;
    }

    vec2 seed = texelFetch(jfaResult, pixel, 0).rg;
    if (seed.x < 0.0 || seed.y < 0.0)
    {
        color = scene;
        return;
    }

    float distanceToSilhouette = length(seed - (vec2(pixel) + vec2(0.5)));
    float coverage;
    if (outlineAntialiasing != 0)
    {
        coverage = clamp(outlineWidth - distanceToSilhouette + 1.0, 0.0, 1.0);
    }
    else
    {
        coverage = distanceToSilhouette <= outlineWidth ? 1.0 : 0.0;
    }

    color = vec4(mix(scene.rgb, vec3(1.0, 0.0, 0.0), coverage), 1.0);
}

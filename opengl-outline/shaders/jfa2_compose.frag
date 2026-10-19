#version 330 compatibility
in vec2 uv;
uniform usampler2D stencilMask;
uniform sampler2D jfaResult;
uniform float outlineWidth;
uniform int outlineAntialiasing;
uniform int interiorOutline;
uniform int exteriorOutline;
out vec4 color;

float OutlineRadiusPixels()
{
    return max(0.5, outlineWidth * 0.5);
}

float Coverage(float distanceToBoundary)
{
    if (outlineAntialiasing != 0)
    {
        float antialiasWidth = max(fwidth(distanceToBoundary), 1.0);
        return 1.0 - smoothstep(
            OutlineRadiusPixels() - antialiasWidth,
            OutlineRadiusPixels() + antialiasWidth,
            distanceToBoundary);
    }
    return distanceToBoundary <= OutlineRadiusPixels() ? 1.0 : 0.0;
}

void main()
{
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    bool inside = texelFetch(stencilMask, pixel, 0).r != 0u;
    float signedDistance = texelFetch(jfaResult, pixel, 0).b;
    float coverage = 0.0;

    if (abs(signedDistance) < 1.0e29)
    {
        if (inside && interiorOutline != 0)
        {
            coverage = Coverage(abs(signedDistance));
        }
        else if (!inside && exteriorOutline != 0)
        {
            coverage = Coverage(abs(signedDistance));
        }
    }

    color = vec4(vec3(1.0, 0.0, 0.0), coverage);
}

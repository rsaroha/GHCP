#version 330 compatibility
in vec2 uv;
uniform sampler2D outlineTexture;
uniform int alphaOnly;
out vec4 color;

float Luma(vec4 sampleColor)
{
    return alphaOnly != 0
        ? sampleColor.a
        : dot(sampleColor.rgb, vec3(0.299, 0.587, 0.114));
}

void main()
{
    vec2 texelSize = 1.0 / vec2(textureSize(outlineTexture, 0));
    vec4 centerSample = texture(outlineTexture, uv);
    vec4 northSample = texture(outlineTexture, uv + vec2(0.0, texelSize.y));
    vec4 southSample = texture(outlineTexture, uv - vec2(0.0, texelSize.y));
    vec4 eastSample = texture(outlineTexture, uv + vec2(texelSize.x, 0.0));
    vec4 westSample = texture(outlineTexture, uv - vec2(texelSize.x, 0.0));
    float center = Luma(centerSample);
    float north = Luma(northSample);
    float south = Luma(southSample);
    float east = Luma(eastSample);
    float west = Luma(westSample);

    float minimum = min(center, min(min(north, south), min(east, west)));
    float maximum = max(center, max(max(north, south), max(east, west)));
    float contrast = maximum - minimum;
    if (contrast < max(0.0312, maximum * 0.125))
    {
        color = centerSample;
        return;
    }

    vec2 direction = vec2(-(north - south), east - west);
    float directionReduce = max((north + south + east + west) * 0.25 * 0.25, 0.0078125);
    float reciprocal = 1.0 / (min(abs(direction.x), abs(direction.y)) + directionReduce);
    direction = clamp(direction * reciprocal, -8.0, 8.0) * texelSize;

    vec4 colorA = 0.5 * (
        texture(outlineTexture, uv + direction * (1.0 / 3.0 - 0.5)) +
        texture(outlineTexture, uv + direction * (2.0 / 3.0 - 0.5)));
    vec4 colorB = colorA * 0.5 + 0.25 * (
        texture(outlineTexture, uv + direction * -0.5) +
        texture(outlineTexture, uv + direction * 0.5));
    float lumaB = Luma(colorB);
    vec4 result = lumaB < minimum || lumaB > maximum ? colorA : colorB;
    color = alphaOnly != 0
        ? vec4(centerSample.rgb, result.a)
        : result;
}

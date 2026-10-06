#version 330 compatibility
in vec2 uv;
uniform sampler2D outlineTexture;
uniform vec2 texelSize;
out vec4 color;

float Luma(float alpha)
{
    return alpha;
}

void main()
{
    float center = Luma(texture(outlineTexture, uv).a);
    float north = Luma(texture(outlineTexture, uv + vec2(0.0, texelSize.y)).a);
    float south = Luma(texture(outlineTexture, uv - vec2(0.0, texelSize.y)).a);
    float east = Luma(texture(outlineTexture, uv + vec2(texelSize.x, 0.0)).a);
    float west = Luma(texture(outlineTexture, uv - vec2(texelSize.x, 0.0)).a);

    float minimum = min(center, min(min(north, south), min(east, west)));
    float maximum = max(center, max(max(north, south), max(east, west)));
    float contrast = maximum - minimum;
    if (contrast < max(0.0312, maximum * 0.125))
    {
        color = texture(outlineTexture, uv);
        return;
    }

    vec2 direction = vec2(-(north - south), east - west);
    float directionReduce = max((north + south + east + west) * 0.25 * 0.25, 0.0078125);
    float reciprocal = 1.0 / (min(abs(direction.x), abs(direction.y)) + directionReduce);
    direction = clamp(direction * reciprocal, -8.0, 8.0) * texelSize;

    float alphaA = 0.5 * (
        texture(outlineTexture, uv + direction * (1.0 / 3.0 - 0.5)).a +
        texture(outlineTexture, uv + direction * (2.0 / 3.0 - 0.5)).a);
    float alphaB = alphaA * 0.5 + 0.25 * (
        texture(outlineTexture, uv + direction * -0.5).a +
        texture(outlineTexture, uv + direction * 0.5).a);
    float resultAlpha = alphaB < minimum || alphaB > maximum ? alphaA : alphaB;
    color = vec4(vec3(1.0, 0.0, 0.0), resultAlpha);
}

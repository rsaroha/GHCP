#version 330 compatibility
in vec2 uv;
uniform sampler2D jfaInput;
uniform int stepSize;
out vec4 color;

void main()
{
    ivec2 size = textureSize(jfaInput, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    vec3 result = texelFetch(jfaInput, pixel, 0).rgb;
    float resultSign = sign(result.z);

    for (int y = -1; y <= 1; ++y)
    {
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            ivec2 otherPixel = pixel + ivec2(x, y) * stepSize;
            if (otherPixel.x < 0 || otherPixel.x >= size.x ||
                otherPixel.y < 0 || otherPixel.y >= size.y)
            {
                continue;
            }

            vec3 other = texelFetch(jfaInput, otherPixel, 0).rgb;
            if (other.z == 0.0)
            {
                continue;
            }

            if (resultSign != sign(other.z))
            {
                float distanceToOther = length(vec2(pixel - otherPixel));
                if (distanceToOther < result.z * resultSign)
                {
                    result = vec3(vec2(otherPixel), distanceToOther * resultSign);
                }
            }
            else if (ivec2(other.rg) != otherPixel)
            {
                float distanceToSeed = length(vec2(pixel - ivec2(other.rg)));
                if (distanceToSeed < result.z * resultSign)
                {
                    result = vec3(other.rg, distanceToSeed * resultSign);
                }
            }
        }
    }

    color = vec4(result, 1.0);
}

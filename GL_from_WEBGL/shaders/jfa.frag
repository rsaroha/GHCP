#version 330 core
in vec2 vUv;
uniform sampler2D source, mask;
uniform int step;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Propagate the nearest signed-distance seed for one jump-flood pass.
 *
 **********************************************************************************/
void main()
{
    ivec2 size = textureSize(source, 0), p = ivec2(gl_FragCoord.xy);
    vec3 result = texelFetch(source, p, 0).rgb;
    if (texture(mask, vUv).r < 0.5)
    {
        outColor = vec4(0, 0, 0, 1);
        return;
    }
    float sg = sign(result.z);
    for (int y = -1; y <= 1; y++)
        for (int x = -1; x <= 1; x++)
        {
            if (x == 0 && y == 0)
                continue;
            ivec2 q = p + ivec2(x, y) * step;
            if (any(lessThan(q, ivec2(0))) || any(greaterThanEqual(q, size)))
                continue;
            vec3 other = texelFetch(source, q, 0).rgb;
            if (other.b == 0.0)
                continue;
            if (sg != sign(other.z))
            {
                float d = length(vec2(p - q));
                if (d < result.z * sg)
                    result = vec3(vec2(q), d * sg);
            }
            else if (ivec2(other.rg) != q)
            {
                float d = length(vec2(p - ivec2(other.rg)));
                if (d < result.z * sg)
                    result = vec3(other.rg, d * sg);
            }
        }
    outColor = vec4(result, 1.0);
}

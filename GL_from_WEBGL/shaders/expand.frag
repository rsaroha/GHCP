#version 330 core
in vec2 vUv;
uniform sampler2D source;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Expand the silhouette mask by one pixel using neighboring texels.
 *
 **********************************************************************************/
void main()
{
    ivec2 p = ivec2(gl_FragCoord.xy), size = textureSize(source, 0);
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
                continue;
            ivec2 q = clamp(p + ivec2(x, y), ivec2(0), size - 1);
            if (texelFetch(source, q, 0).r != 0.0)
            {
                outColor = vec4(1);
                return;
            }
        }
    outColor = vec4(0);
}

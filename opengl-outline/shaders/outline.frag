#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneColor;
uniform sampler2D stencilMask;
uniform vec2 texelSize;
out vec4 color;

void main()
{
    vec4 scene = texture(sceneColor, uv);
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = ivec2(gl_FragCoord.xy);
    float center = texelFetch(stencilMask, pixel, 0).r;
    float neighbor = 0.0;
    for (int y = -4; y <= 4; ++y)
    {
        for (int x = -4; x <= 4; ++x)
        {
            ivec2 samplePixel = clamp(pixel + ivec2(x, y), ivec2(0), size - 1);
            neighbor = max(neighbor, texelFetch(stencilMask, samplePixel, 0).r);
        }
    }
    float outsideEdge = step(0.5, neighbor) * (1.0 - step(0.5, center));
    vec3 result = mix(scene.rgb, vec3(1.0, 0.0, 0.0), outsideEdge);
    color = vec4(result, 1.0);
}

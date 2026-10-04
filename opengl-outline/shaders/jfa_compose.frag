#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneColor;
uniform usampler2D stencilMask;
uniform sampler2D jfaResult;
uniform float outlineWidth;
out vec4 color;

void main()
{
    vec4 scene = texture(sceneColor, uv);
    ivec2 size = textureSize(stencilMask, 0);
    ivec2 pixel = clamp(ivec2(gl_FragCoord.xy), ivec2(0), size - 1);
    uint center = texelFetch(stencilMask, pixel, 0).r;
    if (center >= 1u)
    {
        color = scene;
        return;
    }

    vec2 seed = texelFetch(jfaResult, pixel, 0).rg;
    if (seed.x < 0.0 || seed.y < 0.0)
    {
        color = scene;
        return;
    }

    vec2 pixelCenter = vec2(float(pixel.x) + 0.5, float(pixel.y) + 0.5);
    vec2 delta = seed - pixelCenter;
    float distanceToSilhouette = sqrt(dot(delta, delta));
    float outsideEdge = distanceToSilhouette <= outlineWidth ? 1.0 : 0.0;
    vec3 result = mix(scene.rgb, vec3(1.0, 0.0, 0.0), outsideEdge);
    color = vec4(result, 1.0);
}

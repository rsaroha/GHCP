#version 330 compatibility
in vec2 uv;
uniform sampler2D sceneTexture;
uniform sampler2D outlineTexture;
out vec4 color;

void main()
{
    vec4 scene = texture(sceneTexture, uv);
    vec4 outline = texture(outlineTexture, uv);
    color = vec4(mix(scene.rgb, outline.rgb, outline.a), 1.0);
}

#version 330 compatibility
in vec2 uv;
uniform sampler2D screenTexture;
out vec4 color;

void main()
{
    color = texture(screenTexture, uv);
}

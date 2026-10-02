#version 330 compatibility
layout(location=0) in vec3 position;
layout(location=1) in vec3 normal;
uniform mat4 mvp;
uniform mat4 modelView;
out vec3 vertexNormal;
out vec3 viewPosition;

void main()
{
    vec4 viewSpacePosition = modelView * vec4(position, 1.0);
    gl_Position = mvp * vec4(position, 1.0);
    viewPosition = viewSpacePosition.xyz;
    vertexNormal = mat3(modelView) * normal;
}

#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
uniform mat4 viewProj;
uniform vec2 viewportSize;
uniform vec2 imagePan;
uniform float imageZoom;
out vec3 vNormal;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Transform mesh vertices and pass normals to the lighting shader.
 *
 **********************************************************************************/
void main()
{
    vNormal = normal;
    vec4 clipPosition = viewProj * vec4(position, 1.0);
    clipPosition.xy = clipPosition.xy * imageZoom +
                      vec2(2.0 * imagePan.x / viewportSize.x, -2.0 * imagePan.y / viewportSize.y) *
                          clipPosition.w;
    gl_Position = clipPosition;
}

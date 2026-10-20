#version 330 core
in vec3 vNormal;
uniform int negative;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Seed the signed distance field with the mesh surface position.
 *
 **********************************************************************************/
void main()
{
    outColor = vec4(gl_FragCoord.xy, 1e4 * float(negative), 1.0);
}

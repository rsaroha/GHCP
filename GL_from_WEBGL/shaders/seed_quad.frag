#version 330 core
in vec2 vUv;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Initialize the distance field with the far-away sentinel seed.
 *
 **********************************************************************************/
void main()
{
    outColor = vec4(gl_FragCoord.xy, 1e4, 1.0);
}

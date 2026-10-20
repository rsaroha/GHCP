#version 330 core
in vec3 vNormal;
uniform vec3 lightDir;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Shade the mesh with directional and hemisphere lighting.
 *
 **********************************************************************************/
void main()
{
    vec3 n = normalize(vNormal);
    if (!gl_FrontFacing)
        n = -n;
    float hemi = 0.5 + 0.5 * n.y, diff = max(dot(n, lightDir), 0.0);
    outColor = vec4(vec3(0.72, 0.74, 0.78) * (0.25 + 0.35 * hemi + 0.8 * diff), 1.0);
}

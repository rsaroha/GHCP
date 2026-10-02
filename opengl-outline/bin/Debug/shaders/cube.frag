#version 330 compatibility
in vec3 vertexNormal;
in vec3 viewPosition;
out vec4 color;

void main()
{
    vec3 normal = normalize(vertexNormal);
    vec3 lightDirection = normalize(vec3(-0.45, 0.7, 1.0));
    float diffuse = max(dot(normal, lightDirection), 0.0);
    vec3 viewDirection = normalize(-viewPosition);
    vec3 halfDirection = normalize(lightDirection + viewDirection);
    float specular = pow(max(dot(normal, halfDirection), 0.0), 32.0);
    vec3 material = vec3(0.58);
    vec3 lighting = material * (0.2 + 0.8 * diffuse) + vec3(0.28) * specular;
    color = vec4(lighting, 1.0);
}

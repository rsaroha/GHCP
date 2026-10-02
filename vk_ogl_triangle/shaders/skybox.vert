#version 450

// Push constant layout mirrors the main shaders (208 bytes).
// For the skybox draw, the 'mvp' slot (offset 0) is repurposed to hold
// invProjViewRot = inverse(proj * viewRotationOnly), used to unproject
// each fragment's NDC coordinate back to a world-space view direction.
layout(push_constant) uniform PC {
    mat4  invProjViewRot;  // offset 0
    mat4  _mv;             // offset 64 (unused)
    vec4  _selColor;       // offset 128
    vec4  _lightPos;       // offset 144
    vec4  _lightColor;     // offset 160
    int   _shaderMode;     // offset 176
    int   _hasAlbedoTex;   // offset 180
    int   _hasEnvMap;      // offset 184
    float _iblIntensity;   // offset 188
    uvec4 _sel;            // offset 192
} pc;

layout(location = 0) out vec3 outDir;

void main() {
    // Fullscreen triangle — no vertex buffer, driven by vertex index
    vec2 uv  = vec2((gl_VertexIndex << 1) & 2, gl_VertexIndex & 2);
    vec2 ndc = uv * 2.0 - 1.0;
    gl_Position = vec4(ndc, 1.0, 1.0);  // z=w → NDC depth=1 (far plane)

    // Unproject NDC → world-space direction for cubemap sampling
    vec4 w = pc.invProjViewRot * vec4(ndc, 1.0, 1.0);
    outDir = normalize(w.xyz / w.w);
}

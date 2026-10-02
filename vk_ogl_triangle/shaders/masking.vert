#version 450

void main() {
    int  i   = gl_VertexIndex;
    vec2 ndc = vec2((i << 1) & 2, i & 2) * 2.0 - 1.0;
    gl_Position = vec4(ndc, 0.0, 1.0);
}

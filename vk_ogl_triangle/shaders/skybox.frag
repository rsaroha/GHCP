#version 450

layout(location = 0) in  vec3 inDir;
layout(location = 0) out vec4 outColor;

// Original equirectangular HDR map (binding 4, same descriptor set)
layout(set = 0, binding = 4) uniform sampler2D equirectTex;

layout(push_constant) uniform PC {
    mat4  _invPVR;
    mat4  _mv;
    vec4  _selColor;
    vec4  _lightPos;
    vec4  _lightColor;
    int   _shaderMode;
    int   _hasAlbedoTex;
    int   hasEnvMap;
    float iblIntensity;
    uvec4 _sel;
} pc;

const float PI = 3.14159265359;

// Match the equirectDir() convention in texture_util.h:
//   phi   = (1-v)*PI   →  v = 1 - phi/PI
//   theta = u*2*PI-PI  →  u = (theta+PI)/(2*PI)
//   dir   = (sin(phi)*cos(theta), cos(phi), sin(phi)*sin(theta))
vec2 dirToEquirectUV(vec3 dir) {
    float phi   = acos(clamp(dir.y, -1.0, 1.0));
    float theta = atan(dir.z, dir.x);           // GLSL atan(y,x) == atan2
    return vec2((theta + PI) / (2.0 * PI), 1.0 - phi / PI);
}

vec3 tonemap(vec3 c) {
    c = c / (c + vec3(1.0));
    return pow(c, vec3(1.0 / 2.2));
}

void main() {
    if (pc.hasEnvMap == 0) discard;
    vec2 uv  = dirToEquirectUV(normalize(inDir));
    vec3 col = texture(equirectTex, uv).rgb * pc.iblIntensity;
    outColor  = vec4(tonemap(col), 1.0);
}

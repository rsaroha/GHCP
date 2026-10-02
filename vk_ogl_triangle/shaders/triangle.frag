#version 450

layout(push_constant) uniform PC {
    mat4  mvp_base;
    mat4  mv_base;
    vec4  selectionColor;
    vec4  lightPos;
    vec4  lightColor;
    int   shaderMode;
    int   hasAlbedoTex;
    int   hasEnvMap;
    float iblIntensity;
    uint  selectionMask[4];
} pc;

layout(set=0, binding=0) uniform sampler2D   albedoTex;
layout(set=0, binding=1) uniform samplerCube irradianceMap;
layout(set=0, binding=2) uniform samplerCube prefilteredEnv;
layout(set=0, binding=3) uniform sampler2D   brdfLUT;

layout(location = 0) in vec4  fragColor;
layout(location = 1) in vec3  viewPos;
layout(location = 2) in float isSelected;
layout(location = 3) in flat int shaderMode;
layout(location = 4) in vec4  fragMaterial;
layout(location = 5) in flat int fragMatType;
layout(location = 6) in vec4  fragMatParams;
layout(location = 7) in vec3  fragNormal;
layout(location = 8) in vec2  fragUV;

layout(location = 0) out vec4 outColor;

const float PI = 3.14159265358979;
const float MAX_PREFILTER_LOD = 4.0;   // NUM_ENV_MIPS - 1

// ── Shared per-fragment lighting ──────────────────────────────────────────────
vec3 shadeSolid(vec3 N, vec3 L, vec3 viewDir, vec3 baseColor,
                float ambient, float diffuse, float specular, float shininess,
                int matType, vec4 p)
{
    vec3 lit = baseColor * ambient;

    if (matType == 0) {
        vec3 H = normalize(L + viewDir);
        float dif = max(dot(N, L), 0.0) * diffuse;
        float spc = pow(max(dot(N, H), 0.0), shininess) * specular;
        lit = baseColor * (ambient + dif * pc.lightColor.rgb)
            + pc.lightColor.rgb * spc;

    } else if (matType == 1) {
        float NdotL = max(dot(N, L), 0.0);
        float bands = max(p.x, 1.0);
        float toon  = floor(NdotL * bands) / bands;
        vec3 H = normalize(L + viewDir);
        float NdotH = max(dot(N, H), 0.0);
        float spc = (NdotH > p.y ? 1.0 : 0.0) * specular;
        float rimDot = 1.0 - max(dot(N, viewDir), 0.0);
        float rim = pow(clamp(rimDot, 0.0, 1.0), max(p.z, 0.1)) * p.w;
        lit = baseColor * (ambient + toon * diffuse * pc.lightColor.rgb)
            + spc * pc.lightColor.rgb + rim * vec3(1.0);

    } else if (matType == 2) {
        float t = (dot(N, L) + 1.0) * 0.5;
        vec3 warm = mix(vec3(0.8, 0.6, 0.0), baseColor, p.x);
        vec3 cool = mix(vec3(0.0, 0.2, 0.8), baseColor, p.x);
        vec3 H = normalize(L + viewDir);
        float spc = pow(max(dot(N, H), 0.0), 64.0) * p.y;
        lit = mix(cool, warm, t) + spc * pc.lightColor.rgb;

    } else if (matType == 3) {
        vec3 H = normalize(L + viewDir);
        float dif = max(dot(N, L), 0.0) * diffuse;
        float spc = pow(max(dot(N, H), 0.0), shininess) * specular;
        float rimDot = 1.0 - max(dot(N, viewDir), 0.0);
        float rim = pow(clamp(rimDot, 0.0, 1.0), max(p.x, 0.1));
        vec3 rimCol = p.yzw;
        lit = baseColor * (ambient + dif * pc.lightColor.rgb)
            + spc * pc.lightColor.rgb + rim * rimCol;

    } else if (matType == 4) {
        float sigma  = clamp(p.x, 0.0, 1.0);
        float sigma2 = sigma * sigma;
        float A = 1.0 - sigma2 / (2.0 * sigma2 + 0.66);
        float B = 0.45 * sigma2 / (sigma2 + 0.09);
        float NdotL = max(dot(N, L), 0.0);
        float NdotV = max(dot(N, viewDir), 0.0);
        float LdotV = dot(L, viewDir);
        float s = LdotV - NdotL * NdotV;
        float t_on = s <= 0.0 ? 1.0 : max(NdotL, NdotV) + 0.001;
        float orenNayar = NdotL * (A + B * s / t_on) * diffuse;
        lit = baseColor * (ambient + orenNayar * pc.lightColor.rgb);

    } else if (matType == 5) {
        float NdotL = max(dot(N, L), 0.001);
        float NdotV = max(dot(N, viewDir), 0.001);
        float k = clamp(p.x, 0.1, 2.0);
        float minnaert = pow(NdotL * NdotV, k) / NdotV * diffuse;
        lit = baseColor * (ambient + minnaert * pc.lightColor.rgb);

    } else if (matType == 6) {
        float metalness = clamp(p.x, 0.0, 1.0);
        float roughness = clamp(p.y, 0.04, 1.0);
        vec3 F0 = mix(vec3(0.04), baseColor, metalness);
        vec3 H  = normalize(L + viewDir);
        float NdotL = max(dot(N, L), 0.0);
        float NdotV = max(dot(N, viewDir), 0.001);
        float NdotH = max(dot(N, H), 0.0);
        float LdotH = max(dot(L, H), 0.0);
        float a  = roughness * roughness;
        float a2 = a * a;
        float d  = NdotH * NdotH * (a2 - 1.0) + 1.0;
        float D  = a2 / (PI * d * d);
        vec3  F  = F0 + (vec3(1.0) - F0) * pow(1.0 - LdotH, 5.0);
        float k  = (roughness + 1.0) * (roughness + 1.0) / 8.0;
        float GL = NdotL / (NdotL * (1.0 - k) + k);
        float GV = NdotV / (NdotV * (1.0 - k) + k);
        float G  = GL * GV;
        vec3 spec = D * F * G / max(4.0 * NdotL * NdotV, 0.001);
        vec3 kD   = (vec3(1.0) - F) * (1.0 - metalness);
        lit = (kD * baseColor / PI + spec) * NdotL * pc.lightColor.rgb
            + baseColor * ambient;

    } else if (matType == 7) {
        vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
        vec3 T  = normalize(cross(up, N));
        vec3 B  = cross(N, T);
        float angle = p.z * PI / 180.0;
        vec3 Tr = cos(angle)*T + sin(angle)*B;
        vec3 Br = -sin(angle)*T + cos(angle)*B;
        vec3 H = normalize(L + viewDir);
        float NdotL = max(dot(N, L), 0.0);
        float NdotV = max(dot(N, viewDir), 0.001);
        float NdotH = dot(N, H);
        float TdotH = dot(Tr, H);
        float BdotH = dot(Br, H);
        float ax = max(p.x, 0.01), ay = max(p.y, 0.01);
        float exponent = -(TdotH*TdotH/(ax*ax) + BdotH*BdotH/(ay*ay))
                         / max(NdotH*NdotH, 0.001);
        float D_aniso = (NdotH > 0.0)
            ? exp(exponent) / (4.0*PI*ax*ay * sqrt(max(NdotL*NdotV, 0.001)))
            : 0.0;
        float spc = max(D_aniso, 0.0) * p.w;
        lit = baseColor * (ambient + NdotL * diffuse * pc.lightColor.rgb)
            + pc.lightColor.rgb * spc;

    } else {
        float wrap   = clamp(p.x, 0.0, 1.0);
        float NdotL  = dot(N, L);
        float wrapDif = max((NdotL + wrap) / (1.0 + wrap), 0.0) * diffuse;
        float backLit = max(dot(-N, L), 0.0) * p.y;
        vec3 scatter = mix(baseColor, baseColor * vec3(1.5, 0.7, 0.5), clamp(p.z, 0.0, 1.0));
        lit = baseColor * (ambient + wrapDif * pc.lightColor.rgb)
            + scatter * backLit * pc.lightColor.rgb;
    }
    return lit;
}

// Image-based lighting (view-space N and V → world via inverse transpose of mv)
vec3 applyIBL(vec3 N, vec3 V, vec3 albedo, int matType, vec4 p, vec3 litColor) {
    if (pc.hasEnvMap == 0) return litColor;
    mat3 invMV = transpose(mat3(pc.mv_base));
    vec3 irrDir = invMV * N;
    vec3 irradiance = texture(irradianceMap, irrDir).rgb;
    litColor += irradiance * albedo * pc.iblIntensity * 0.5;
    if (matType == 6) {
        float metalness = clamp(p.x, 0.0, 1.0);
        float roughness = clamp(p.y, 0.04, 1.0);
        vec3 F0 = mix(vec3(0.04), albedo, metalness);
        vec3 R = invMV * reflect(-V, N);
        vec3 prefilt = textureLod(prefilteredEnv, R, roughness * MAX_PREFILTER_LOD).rgb;
        float NdotV = max(dot(N, V), 0.0);
        vec2 brdf = texture(brdfLUT, vec2(NdotV, roughness)).rg;
        vec3 F = F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - NdotV, 5.0);
        litColor += prefilt * (F * brdf.x + brdf.y) * pc.iblIntensity;
    }
    return litColor;
}

void main() {
    if (shaderMode != 1 && fragColor.a < 0.99) discard;

    vec3 N = normalize(fragNormal);
    N = faceforward(N, viewPos, N);
    vec3 L       = normalize(pc.lightPos.xyz - viewPos);
    vec3 viewDir = normalize(-viewPos);
    vec3 albedo  = (pc.hasAlbedoTex != 0)
        ? texture(albedoTex, fragUV).rgb * fragColor.rgb
        : fragColor.rgb;

    vec3 litColor;
    if (shaderMode == 1) {
        outColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    } else if (shaderMode == 2) {
        litColor = albedo;
    } else if (shaderMode == 3) {
        outColor = vec4(N * 0.5 + 0.5, 1.0);
        return;
    } else {
        litColor = shadeSolid(N, L, viewDir, albedo,
                              fragMaterial.x, fragMaterial.y,
                              fragMaterial.z, fragMaterial.w,
                              fragMatType, fragMatParams);
        litColor = applyIBL(N, viewDir, albedo, fragMatType, fragMatParams, litColor);
    }

    if (isSelected > 0.5)
        litColor = mix(litColor, pc.selectionColor.rgb, 0.6);
    outColor = vec4(litColor, 1.0);
}

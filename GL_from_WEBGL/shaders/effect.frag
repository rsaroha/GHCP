#version 330 core
in vec2 vUv;
uniform float time, thickness;
uniform sampler2D map, mask;
uniform int mode, inside;
uniform vec3 color;
out vec4 outColor;

/**********************************************************************************
 *   Function Name  : fw
 *   Purpose : Estimate a scalar value's screen-space derivative magnitude.
 *
 **********************************************************************************/
float fw(float v)
{
    return length(vec2(dFdy(v), dFdx(v)));
}

/**********************************************************************************
 *   Function Name  : main
 *   Purpose : Apply the selected distance-field visualization effect.
 *
 **********************************************************************************/
void main()
{
    vec2 size = vec2(textureSize(map, 0));
    ivec2 p = ivec2(vUv * size);
    vec3 s = texelFetch(map, p, 0).rgb;
    if (s.b == 0.0)
        discard;
    vec4 c = vec4(0);
    if (mode == -1)
    {
        float v = texture(mask, vUv).r;
        c = vec4(v, v, v, 1);
    }
    else if (mode == 0)
        c = vec4(s / vec3(size, 1), 1);
    else if (mode == 1)
    {
        float d = abs(s.b) / thickness;
        c = vec4(d, d, d, 1);
    }
    else if (mode == 2)
    {
        float d = s.b * float(inside), w = .5;
        float v = (1 - smoothstep(thickness - w, thickness + w, d)) * smoothstep(-w - 1, w - 1, d);
        c = vec4(color, clamp(v, 0, 1));
    }
    else if (mode == 3)
    {
        float d = s.b * float(inside);
        c = vec4(color, (1 - d / thickness) * smoothstep(-1.5, -.5, d));
    }
    else if (mode == 4)
    {
        float d = s.b * float(inside), w = clamp(fw(d), -1, 1) * .5;
        float clip =
                  (1 - smoothstep(thickness - w, thickness + w, d)) * smoothstep(-w - 1, w - 1, d),
              n = d / thickness;
        float pulse = sin(time * -.01 + 20 * pow(n + .2, 4));
        c.rgb = mix(color, vec3(1), .5 * pow(1 - n, 4));
        c.a = clip * (1 - pow(n, 2)) * smoothstep(0, fw(pulse), pulse);
    }
    else if (mode == 5)
    {
        float radius = 13 * min(thickness, 40) * .02, width = radius * 2;
        vec2 center = floor(vec2(p) / width) * width + vec2(radius);
        float alpha = 0;
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
            {
                vec2 q = center + vec2(x, y) * width;
                float strength = texelFetch(map, clamp(ivec2(q), ivec2(0), ivec2(size) - 1), 0).b *
                                 float(inside);
                if (strength == 0)
                    continue;
                strength = (strength + radius * 1.3) / 1.5;
                strength = clamp(1 - strength / thickness, 0, 1);
                strength = 1 - pow(1 - strength, .75);
                float a =
                    1 - smoothstep(strength * width - 1, strength * width, length(vec2(p) - q));
                alpha = max(alpha, a);
            }
        c = vec4(color, alpha * smoothstep(-1.5, -.5, s.b * float(inside)));
    }
    else if (mode == 6)
    {
        float d = s.b * float(inside), value = clamp(1 - d / thickness, 0, 1), stride = 15, w = .5;
        c.rgb = color;
        c.a = (1 - smoothstep(.2 - w / thickness, .2 + w / thickness,
                              mod((1 - value) * thickness / stride, 1))) *
              smoothstep(-w - 1, w - 1, d) *
              (1 - smoothstep(stride * floor(thickness / stride) - w,
                              stride * floor(thickness / stride) + w, d + 1));
    }
    if (c.a <= 0)
        discard;
    outColor = c;
}

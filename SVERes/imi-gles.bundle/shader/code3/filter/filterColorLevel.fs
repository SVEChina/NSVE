precision mediump float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;
uniform vec2 colorLevel;
uniform float gamma;

vec3 levelFunc(vec3 src, vec2 colorLevel)
{
    return clamp((src - colorLevel.x) / (colorLevel.y - colorLevel.x), 0.0, 1.0);
}

vec3 gammaFunc(vec3 src, float value) //value: 0~1
{
    return clamp(pow(src, vec3(value)), 0.0, 1.0);
}

void main()
{
    vec4 src = texture(aTexture0, v_texcoord0);
    src.rgb = levelFunc(src.rgb, colorLevel);
    src.rgb = gammaFunc(src.rgb, gamma);
    color0 = src;
}

precision highp float;

in vec2 vTexcoord0;
in vec2 vTexcoord1;
in vec4 vColor;
uniform sampler2D aTexture0;//mask图
uniform sampler2D aTexture1;//底图
uniform float intensity;

out vec4 color0;
//正常
vec3 blendNormal(vec3 base, vec3 blend) {
    return blend;
}

vec3 blendNormal(vec3 base, vec3 blend, float opacity) {
    return (blendNormal(base, blend) * opacity + blend * (1.0 - opacity));
}

#define blendModel blendNormal

void main()
{
    vec4 srcColor = texture(aTexture1, vTexcoord1);
    vec4 maskColor = texture(aTexture0, vTexcoord0);
    vec3 color = blendModel(srcColor.rgb, clamp(maskColor.rgb * (1.0 / maskColor.a), 0.0, 1.0));
    float opacity = vColor.a;
    color = mix(srcColor.rgb, color, maskColor.a);
    color = mix(srcColor.rgb, color, intensity * opacity);
    color0 = vec4(color, 1.0);
//    color0 = vec4(1.0, 0.0, 0.0, 1.0);
}

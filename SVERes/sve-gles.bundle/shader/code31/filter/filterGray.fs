precision highp float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;

void main() {
    vec4 col = texture(aTexture0, v_texcoord0.xy);
    float gray = dot(col.rgb,vec3(0.299,0.587,0.114));
    color0 = vec4(vec3(gray),col.a);
}

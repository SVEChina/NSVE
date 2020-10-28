precision mediump float;

//对比度
in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;
uniform float intensity;
 
void main(){
    vec4 col = texture(aTexture0, v_texcoord0);
    color0 = vec4(((col.rgb - vec3(0.5)) * intensity + vec3(0.5)), col.a);
}
 

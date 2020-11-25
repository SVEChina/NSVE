precision mediump float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;

void main(){
    color0 = texture(aTexture0, v_texcoord0);
    color0.a = 1.0;
//    color0 = vec4(0.0f,0.0,1.0,1.0);
}

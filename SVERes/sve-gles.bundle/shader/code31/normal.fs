precision mediump float;

in vec2 v_texcoord0;

out vec4 color0;

uniform sampler2D aTexture0;

void main(){
    color0 = texture2D(aTexture0,v_texcoord0);
    return color0;
}

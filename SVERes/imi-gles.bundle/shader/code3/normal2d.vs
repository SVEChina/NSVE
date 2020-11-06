precision mediump float;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord0;

uniform mat4 matModel;
uniform mat4 matVP;
uniform vec2 uInvert;
//
out vec2 v_texcoord0;
//
void main(){
    v_texcoord0 = aTexcoord0;
    gl_Position = matVP*matModel*vec4(aPosition.xy*uInvert,0.0,1.0);
    gl_PointSize = 3.0;
}

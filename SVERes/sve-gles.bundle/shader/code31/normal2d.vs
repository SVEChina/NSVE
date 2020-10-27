precision mediump float;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexcoord0;

uniform mat4 matw;
uniform mat4 matvp;
uniform vec2 texcoordClip;
//
out vec2 v_texcoord0;
//
void main(){
    v_texcoord0 = aTexcoord0;
    gl_Position = matvp*matw*vec4(aPosition.xyz,1.0);
}

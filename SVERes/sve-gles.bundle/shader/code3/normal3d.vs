attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexcoord0;

varying vec3 v_Normal;
varying vec2 v_texcoord0;

uniform mat4 matw;
uniform mat4 matvp;

void main(){
    v_Normal = aNormal;
    v_texcoord0 = aTexcoord0;
    gl_Position = matvp*matw*vec4(aPosition.xyz,1.0);
}

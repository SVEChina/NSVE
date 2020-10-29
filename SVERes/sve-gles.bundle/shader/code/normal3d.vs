attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aTexcoord0;

varying vec3 v_Normal;
varying vec2 v_texcoord0;

uniform mat4 matModel;
uniform mat4 matVP;

void main(){
    v_Normal = aNormal;
    v_texcoord0 = aTexcoord0;
    gl_Position = matVP*matModel*vec4(aPosition.xyz,1.0);
}

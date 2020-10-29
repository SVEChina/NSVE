#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 aPosition;
attribute vec2 aTexcoord0;
//
uniform mat4 matModel;
uniform mat4 matVP;
uniform vec2 texcoordClip;
//
varying vec2 v_texcoord0;
//
void main(){
    v_texcoord0 = aTexcoord0;
    //v_texcoord0 = (aTexcoord0 - 0.5)*texcoordClip + 0.5;
    gl_Position = matVP*matModel*vec4(aPosition.xyz,1.0);
}

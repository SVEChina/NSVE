#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 aPosition;

uniform mat4 matModel;
uniform mat4 matVP;

void main(){
    gl_Position = matVP*matModel*vec4(aPosition.xyz,1.0);
    gl_PointSize = 3.0;
}

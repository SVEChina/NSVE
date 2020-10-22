#ifdef GL_ES
precision mediump float;
#endif

attribute vec3 aPosition;

uniform mat4 matw;
uniform mat4 matvp;

void main(){
    gl_Position = matvp*matw*vec4(aPosition.xyz,1.0);
    gl_PointSize = 3.0;
}

#ifdef GL_ES
precision mediump float;
#endif

attribute vec2 aPosition;

uniform vec2 u_scale;

void main(){
    gl_Position = vec4(aPosition.xy*u_scale,0.0,1.0);
}
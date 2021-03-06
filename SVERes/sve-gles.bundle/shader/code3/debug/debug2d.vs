precision mediump float;

layout(location = 0) in vec2 aPosition;

uniform vec2 u_scale;
uniform vec2 u_off;

void main(){
    gl_Position = vec4((aPosition.xy +u_off)*u_scale,0.0,1.0);
    gl_PointSize = 3.0;
}

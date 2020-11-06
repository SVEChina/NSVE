precision mediump float;

out vec4 color0;

uniform vec3 u_color;

void main(){
    color0 = vec4(u_color,1.0);
}

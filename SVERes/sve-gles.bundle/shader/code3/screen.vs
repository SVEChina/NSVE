precision mediump float;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexcoord0;

out vec2 v_texcoord0;

void main(){
    v_texcoord0 = aTexcoord0;
    gl_Position = vec4(aPosition.xy,0.0,1.0);
}

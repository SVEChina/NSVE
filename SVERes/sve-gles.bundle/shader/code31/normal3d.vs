precision mediump float;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexcoord0;

out vec3 v_Normal;
out vec2 v_texcoord0;

uniform mat4 matw;
uniform mat4 matvp;

void main(){
    v_Normal = aNormal;
    v_texcoord0 = aTexcoord0;
    gl_Position = matvp*matw*vec4(aPosition.xyz,1.0);
}

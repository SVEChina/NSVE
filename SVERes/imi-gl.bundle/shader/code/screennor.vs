layout (location = 0) in vec2 aPosition; // 位置变量的属性position为0
layout (location = 1) in vec2 aTexcoord0;

out vec2 v_texcoord0;
 
void main(){
    v_texcoord0 = aTexcoord0;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}

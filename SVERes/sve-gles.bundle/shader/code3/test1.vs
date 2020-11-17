precision mediump float;

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexcoord0;

layout(location = 2) in vec4 aBoneID;
layout(location = 3) in vec4 aBoneWeight;

uniform mat4 aBones[100];
uniform mat4 matModel;
uniform mat4 matVP;
//
out vec2 v_texcoord0;

//
mat4 getSkinningMatrix() {
    mat4 skin = mat4(0);
    skin += aBoneWeight.x * aBones[int(floor(aBoneID.x))];
    skin += aBoneWeight.y * aBones[int(floor(aBoneID.y))];
    skin += aBoneWeight.z * aBones[int(floor(aBoneID.z))];
    skin += aBoneWeight.w * aBones[int(floor(aBoneID.w))];
    return skin;
}
//
void main(){
    v_texcoord0 = aTexcoord0;
    
    mat4 skinningMat4 = getSkinningMatrix();
    vec4 pos = skinningMat4*vec4(aPosition.xyz, 1.0);
    
    gl_Position = matVP*matModel*vec4(pos.xyz, 1.0);
    
}

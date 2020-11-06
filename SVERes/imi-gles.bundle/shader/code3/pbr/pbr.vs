precision mediump float;

layout(location = 0) in vec3 aPosition;

#ifdef HAS_NORMALS
layout(location = 1) in vec3 aNormal;
#endif

#ifdef HAS_TANGENTS
layout(location = 2) in vec3 aTangent;
#endif

#ifdef HAS_UV
layout(location = 3) in vec2 aTexcoord0;
#endif

uniform mat4 matVP;
uniform mat4 matModel;
uniform mat4 matNor;

out vec3 v_Position;
out vec2 v_UV;

#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
out mat3 v_TBN;
#else
out vec3 v_Normal;
#endif
#endif

void main(){
    vec4 pos = matModel * vec4(aPosition,1.0f);
    v_Position = vec3(pos.xyz) / pos.w;
#ifdef HAS_NORMALS
#ifdef HAS_TANGENTS
    vec3 normalW = normalize(vec3(matNor * vec4(aNormal.xyz, 0.0)));
    vec3 tangentW = normalize(vec3(matModel * vec4(aTangent.xyz, 0.0)));
    vec3 bitangentW = cross(normalW, tangentW) * aTangent.w;
    v_TBN = mat3(tangentW, bitangentW, normalW);
#else // HAS_TANGENTS != 1
    v_Normal = normalize(vec3(matModel * vec4(aNormal.xyz, 0.0)));
#endif
#endif

#ifdef HAS_UV
    v_UV = aTexcoord0;
#else
    v_UV = vec2(0.,0.);
#endif
    gl_Position = matVP * vec4(aPosition,1.0f);
    // needs w for proper perspective correction
}


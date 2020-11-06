
precision highp float;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord0;
layout(location = 2) in vec2 aTexcoord1;
//layout(location = 3) in vec2 aColor;
uniform vec2 uResolution;
uniform vec2 uTex0size;
uniform vec2 uTex1size;
uniform vec2 texcoord0Clip;
uniform vec2 texcoord1Clip;
uniform vec2 uInvert;

out vec2 vTexcoord0;
out vec2 vTexcoord1;
out vec2 vColor;
void main()
{
//    vColor = aColor;
    vTexcoord0 = (aTexcoord0*(1.0/uTex0size) - 0.5)*texcoord0Clip  + 0.5;
    vTexcoord1 = (aTexcoord1*(1.0/uTex1size) - 0.5)*texcoord1Clip  + 0.5;
    vec2 position = (aPosition*(1.0/uResolution))*2.0 - 1.0;
    gl_Position = vec4(position.xy*uInvert,0.0,1.0);
    gl_PointSize = 8.0;
}


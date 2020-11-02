
precision highp float;

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTexcoord0;
layout(location = 2) in vec2 aTexcoord1;
layout(location = 3) in vec2 aColor;
uniform mat4 matModel;
uniform mat4 matVP;
uniform vec2 uTex0size;
uniform vec2 uTex1size;
uniform vec2 uTtexcoord0Clip;
uniform vec2 uTtexcoord1Clip;

out vec2 vTexcoord0;
out vec2 vTexcoord1;
out vec2 vColor;
void main()
{
    vColor = aColor;
    vTexcoord0 = (aTexcoord0*uTex0size - 0.5)*uTtexcoord0Clip  + 0.5;
    vTexcoord1 = (aTexcoord1*uTex1size - 0.5)*uTtexcoord1Clip  + 0.5;
    gl_Position = matVP*matModel*vec4(aPosition.x,aPosition.y,0.0,1.0);
    gl_PointSize = 8.0;
}


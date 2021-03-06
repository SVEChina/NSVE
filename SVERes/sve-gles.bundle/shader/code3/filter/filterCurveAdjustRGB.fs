precision mediump float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;
uniform float curveArrayRGB[256]; // The array size is defined by "CURVE_PRECISION".

const float curvePrecision = 256.0; //The same to above.

void main()
{
    vec4 src = texture(aTexture0, v_texcoord0);
    color0 = vec4(curveArrayRGB[int(src.r * curvePrecision)],
                        curveArrayRGB[int(src.g * curvePrecision)],
                        curveArrayRGB[int(src.b * curvePrecision)],
                        src.a);
}

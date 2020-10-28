precision mediump float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;
uniform vec3 curveArray[256]; // The array size is defined by "CURVE_PRECISION".
const float curvePrecision = 256.0; //The same to above.

void main()
{
    vec4 src = texture(aTexture0, v_texcoord0);
    color0 = vec4(curveArray[int(src.r * curvePrecision)].r,
                        curveArray[int(src.g * curvePrecision)].g,
                        curveArray[int(src.b * curvePrecision)].b,
                        src.a);
}

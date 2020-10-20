precision highp float;

varying vec2 coord;

uniform sampler2D aTexture0;

void main() {
lowp vec4 col = texture2D(texture, coord.xy);
lowp vec3 map = texture2D(smoothMap, distortionCoord).rgb;

vec3 base = col.rgb * matRGBtoROMM;

float base_lum = luma(col.rgb);
float map_lum = luma_romm(map * matRGBtoROMM);

float exposure = mix(highlights, shadows, 1.0 - map_lum) * col.a;

float a = abs(exposure) * col.a + epsilon;
float v = pow(2.0, a+1.0)-2.0;
float m = mx - exp(-v);
vec3 res = (exposure > 0.0) ? (1.0 - exp(-v*base)) / m : log(1.0-base*m) / -v;
res = mix(base, res, min(a*100.0, 1.0));
res = setHue(res, base);

res = res * matROMMtoRGB;

gl_FragColor = vec4(res, col.a);
}

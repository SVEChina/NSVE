precision highp float;

uniform vec3                iResolution;
uniform float               iGlobalTime;
uniform sampler2D           aTexture0;
uniform sampler2D           aTexture1;
varying vec2                v_texcoord0;

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 uv = fragCoord.xy;

	vec4 bump = texture2D(aTexture1, uv + iGlobalTime * 0.05);

	vec2 vScale = vec2 (0.01, 0.01);
	vec2 newUV = uv + bump.xy * vScale.xy;

	vec4 col = texture2D(aTexture0, newUV);

	fragColor = vec4(col.xyz, 1.0);
}

void main() {
	mainImage(gl_FragColor, v_texcoord0);
}

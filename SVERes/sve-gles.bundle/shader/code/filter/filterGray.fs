precision highp float;

varying vec2 v_texcoord0;

uniform sampler2D aTexture0;

void main() {
    vec4 col = texture2D(texture, v_texcoord0.xy);
    float gray = dot(col.rgb,vec3(0.299,0.587,0.114));
    gl_FragColor = vec4(vec3(gray),col.a);
}

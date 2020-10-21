//#version 450 core
#ifdef GL_ES
precision highp float;
#endif

uniform sampler2D hdr_img;
uniform vec2 hdr_size;

void main(void){
    int i;
    vec2 tc;
    vec3 col;
    vec2 off;
    float lum[25];
    vec2 tex_scale = vec2(1.0) / hdr_size;
    //计算平均亮度
    for (i = 0; i < 25; i++){
        off.x = float(i - 5*(i/5) - 2);
        off.y = float(i/5-2);
        //tc = (2.0 * gl_FragCoord.xy + 3.5 * off);
        tc = gl_FragCoord.xy + off;
        col = texture2D(hdr_img, tc * tex_scale).rgb;
        lum[i] = dot(col, vec3(0.3, 0.59, 0.11));
    }
    //Calculate weighted color of region
    vec2 sc_coord = vec2(gl_FragCoord.xy) * tex_scale ;//* 2.0;
    vec3 vColor = texture2D( hdr_img, sc_coord ).rgb;
    //vec3 vColor = texelFetch( hdr_img, 2 * ivec2(gl_FragCoord.xy), 0).rgb;
    float kernelLuminance = ((1.0*(lum[0] + lum[4] + lum[20] + lum[24])) +
        (4.0 * (lum[1] + lum[3] + lum[5] + lum[9] + lum[15] + lum[19] + lum[21] + lum[23])) +
        (7.0 * (lum[2] + lum[10] + lum[14] + lum[22])) +
        (16.0 * (lum[6] + lum[8] + lum[16] + lum[18])) +
        (26.0 * (lum[7] + lum[11] + lum[13] + lum[17])) +
        (41.0 * lum[12])
    ) / 273.0;
    
    // Compute the corresponding exposure
    float exposure = sqrt(8.0 / (kernelLuminance + 0.25));
    // Apply the exposure to this texel
    gl_FragColor.rgb = 1.0 - exp2(-vColor * exposure);
    gl_FragColor.a = 1.0;
}

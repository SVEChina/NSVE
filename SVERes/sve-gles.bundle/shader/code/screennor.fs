#ifdef GL_ES
precision mediump float;
#endif

varying vec2 v_texcoord0;
uniform sampler2D aTexture0;

void main(){
    gl_FragColor = vec4(0.0,1.0,0.0,1.0);//texture2D(aTexture0,v_texcoord0);
}

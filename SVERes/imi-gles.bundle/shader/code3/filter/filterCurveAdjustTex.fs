precision mediump float;

in vec2 v_texcoord0;
out vec4 color0;

uniform sampler2D aTexture0;
uniform sampler2D curveTexture; //We do not use sampler1D because GLES dosenot support that.

void main()
{
    vec4 src = texture(aTexture0, v_texcoord0);
    color0 = vec4(texture(curveTexture, vec2(src.r, 0.0)).r,
                        texture(curveTexture, vec2(src.g, 0.0)).g,
                        texture(curveTexture, vec2(src.b, 0.0)).b,
                        src.a);
}

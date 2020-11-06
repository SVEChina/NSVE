//
//  screen.metal
//  IMITools
//
//  Created by 付一洲 on 2020/7/18.
//  Copyright © 2020 付一洲. All rights reserved.
//

#include <metal_stdlib>

//look-up-table

//lut 纹理要求512*512，64*64一个格子

using namespace metal;

struct Vertex {
    float2 position [[attribute(0)]];
    float2 texcoord0 [[attribute(1)]];
};

struct VertexOut {
    float4 position [[position]];
    float2 texcoord0;
};

struct FSInput{
    sampler sam0 [[sampler(0)]];
    sampler sam1 [[sampler(1)]];
    texture2d<float> tex0 [[texture(0)]];
    texture2d<float> tex1 [[texture(1)]];
};

struct FSOut{
    float4 frag0 [[color(0)]];
};

//
vertex VertexOut vsMain( Vertex input [[stage_in]] ) {
    VertexOut vert;
    vert.position = float4(input.position,0.0,1.0);
    vert.texcoord0 = input.texcoord0;
    return vert;
}

//
fragment FSOut fsMain( VertexOut input [[stage_in]],FSInput fsin) {
    //
    const float pa = 0.125;         // 1.0/8.0
    const float pb = 0.00195312;    // 1.0/512.0
    const float pc = 0.00097656;    // 0.5/512.0
    //
    FSOut out;
    float4 textureColor = fsin.tex0.sample(fsin.sam0, input.texcoord0);
    float blueColor = textureColor.b * 63.0;
    //
    float2 quad1;
    quad1.y = floor( floor(blueColor) * 0.125 );
    quad1.x = floor(blueColor) - (quad1.y * 8.0);
    //
    float2 quad2;
    quad2.y = floor(ceil(blueColor)  * 0.125 );
    quad2.x = ceil(blueColor) - (quad2.y * 8.0);
    //
    float2 texPos1;
    texPos1.x = (quad1.x * 0.125) + pc + ( (0.125 - pb) * textureColor.r );
    texPos1.y = (quad1.y * 0.125) + ( (0.125 - pb) * textureColor.g);
    //
    float2 texPos2;
    texPos2.x = (quad2.x * 0.125) + pc + ( (0.125 - pb) * textureColor.r );
    texPos2.y = (quad2.y * 0.125) + pc + ( (0.125 - pb) * textureColor.g );
    //
    float4 newColor1 = fsin.tex1.sample(fsin.sam1, texPos1);
    float4 newColor2 = fsin.tex1.sample(fsin.sam1, texPos2);
    //
    float4 newColor = mix(newColor1, newColor2, fract(blueColor));
    out.frag0 = mix(textureColor, float4(newColor.rgb, textureColor.w),1.0);
    return out;
}

//
//  screen.metal
//  SVETools
//
//  Created by 付一洲 on 2020/7/18.
//  Copyright © 2020 付一洲. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

//
struct Vertex {
    float2 position [[attribute(0)]];
    float2 texcoord0 [[attribute(1)]];
};

//
struct Uniforms {
    float4x4 matw;
    float4x4 matv;
    float4x4 matp;
};

//
struct VertexOut {
    float4 position [[position]];
    float2 texcoord0;
};

//
struct FSOutput{
    float4 frag_data0 [[color(0)]];
};

//
vertex VertexOut vertexShader( Vertex input [[stage_in]] ,
                              constant Uniforms & uniforms [[ buffer(1) ]] ) {
    VertexOut vert;
    vert.position = float4(input.position,0.0,1.0) * uniforms.matw * uniforms.matv * uniforms.matp;
    vert.position = vert.position/vert.position.w;
    vert.texcoord0 = input.texcoord0;
    return vert;
}

fragment FSOutput fragmentShader( VertexOut input [[stage_in]],
                                  sampler sam [[sampler(0)]],
                                  texture2d<float> tex0 [[texture(0)]] ) {
    FSOutput out;
    float4 tex_clr0 = tex0.sample(sam, input.texcoord0);
    out.frag_data0 = tex_clr0;
    return out;
}

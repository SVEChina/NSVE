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
    float4x4 matModel;
    float4x4 matV;
    float4x4 matp;
};

//
struct VertexOut {
    float4 position [[position]];
    float2 texcoord0;
};

//
struct FSInput{
    sampler sam0 [[sampler(0)]];
    texture2d<float> tex0 [[texture(0)]];
};

//
struct FSOutput{
    float4 frag0 [[color(0)]];
};

//
vertex VertexOut vsMain(Vertex input [[stage_in]] ,constant Uniforms & uniforms [[ buffer(1) ]] ) {
    VertexOut vert;
    vert.position = float4(input.position,0.0,1.0) * uniforms.matModel * uniforms.matV * uniforms.matp;
    vert.position = vert.position/vert.position.w;
    vert.texcoord0 = input.texcoord0;
    return vert;
}

//
fragment FSOutput fsMain(VertexOut input [[stage_in]],FSInput fsin) {
    FSOutput out;
    out.frag0 = fsin.tex0.sample(fsin.sam0, input.texcoord0);
    return out;
}

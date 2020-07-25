//
//  screen.metal
//  SVETools
//
//  Created by 付一洲 on 2020/7/18.
//  Copyright © 2020 付一洲. All rights reserved.
//

#include <metal_stdlib>

using namespace metal;

struct Vertex {
    float2 position [[attribute(0)]];
};

struct VertexOut {
    float4 position [[position]];
};

struct FSOutput
{
    half4 frag_data0 [[color(0)]];
    half4 frag_data1 [[color(1)]];
};

//
vertex VertexOut vertexShader( Vertex input [[stage_in]] ) {
    VertexOut vert;
    //vert.position = position[vid];
    return vert;
}

//
fragment FSOutput fragmentShader( VertexOut in [[stage_in]]) {
    FSOutput out;
    out.frag_data0 = half4(1.0f, 0.0f, 0.0f, 1.0f);
    return out;
}

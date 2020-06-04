//
// SVRMeshMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshMetal.h"
#include "SVRTargetMetal.h"
#include "../SVRenderMesh.h"

using namespace sv;

SVRMeshMetal::SVRMeshMetal(SVInstPtr _app)
:SVRMesh(_app){
    m_indexID = -1;
}

SVRMeshMetal::~SVRMeshMetal() {
}

void SVRMeshMetal::create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh) {
    SVRTargetMetalPtr t_tar = std::dynamic_pointer_cast<SVRTargetMetal>(_target);
    //创建buf
    
    //更新数据
    [t_tar->m_cmdEncoder setVertexBuffer:m_buf offset:_rmesh->off atIndex:m_indexID];
    // 设置顶点缓存
}

void SVRMeshMetal::render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh) {
    //创建
    if(m_create) {
        create(_renderer,_target,_rmesh);
    }
    //销毁
    if(m_destroy){
        destroy(_renderer,_target);
        return ;
    }
    //绘制
    SVRTargetMetalPtr t_tar = std::dynamic_pointer_cast<SVRTargetMetal>(_target);
    //
    if(_rmesh->vertices_up){
        //数据更新
    }
    //
    [t_tar->m_cmdEncoder drawPrimitives:MTLPrimitiveTypeTriangle
                            vertexStart:_rmesh->start
                            vertexCount:_rmesh->numVertices];
    [t_tar->m_cmdEncoder endEncoding]; // 结束
}

void SVRMeshMetal::destroy(SVRendererPtr _renderer,SVRTargetPtr _target){
    
}

//MTLVertexDescriptor _unityVertexDescriptor = [[MTLVertexDescriptor alloc] init];
//    
//    // Positions.
//    _unityVertexDescriptor.attributes[0].format = MTLVertexFormatFloat2;
//    _unityVertexDescriptor.attributes[0].offset = 0;
//    _unityVertexDescriptor.attributes[0].bufferIndex = 0;
//    
//    // Texture coordinates.
//    _unityVertexDescriptor.attributes[1].format = MTLVertexFormatFloat2;
//    _unityVertexDescriptor.attributes[1].offset = 0;
//    _unityVertexDescriptor.attributes[1].bufferIndex = 0;
//
//    // Position Buffer Layout
//    _unityVertexDescriptor.layouts[0].stride = 8;
//    _unityVertexDescriptor.layouts[0].stepRate = 1;
//    _unityVertexDescriptor.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
//    
//    _unityVertexDescriptor.layouts[1].stride = 8;
//    _unityVertexDescriptor.layouts[1].stepRate = 1;
//    _unityVertexDescriptor.layouts[1].stepFunction = MTLVertexStepFunctionPerVe


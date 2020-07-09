//
// SVRMeshMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshMetal.h"
#include "SVRFboMetal.h"
#include "SVRendererMetal.h"
#include "../SVRenderMesh.h"

using namespace sv;

SVRMeshMetal::SVRMeshMetal(SVInstPtr _app)
:SVRMesh(_app){
    m_ibuf = nullptr;
    m_vertStart = 0;
    m_vertCnt = 0;
    m_iCnt = 0;
    m_ibufOff = 0;
    m_instCnt = 0;
}

SVRMeshMetal::~SVRMeshMetal() {
    destroy(nullptr, nullptr);
}

void SVRMeshMetal::create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh) {
//    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
//    SVRFboMetalPtr t_tar = std::dynamic_pointer_cast<SVRFboMetal>(_target);
//    //创建buf
//    if(_rmesh->m_index.m_pdata ) {
//        m_ibuf = [t_rm->m_pDevice newBufferWithBytes:_rmesh->m_index.m_pdata
//                                                 length: _rmesh->m_index.m_size
//                                                 options: MTLResourceStorageModeShared ];
//        //更新索引参数
//    }
//
//    for(s32 i=0;i<_rmesh->m_vertPool.size();i++) {
//        s32 t_off = 0;
//        id<MTLBuffer> posBuf = [t_rm->m_pDevice newBufferWithBytes:_rmesh->m_vertPool[i].m_pdata
//                                                 length: _rmesh->m_vertPool[i].m_size
//                                                options: MTLResourceStorageModeShared ];
//        m_dbufs.append(posBuf);
//        [t_tar->m_cmdEncoder setVertexBuffer:posBuf offset:t_off atIndex:i];
//    }
//    //更新vert参数
}

void SVRMeshMetal::render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh) {
//    SVRFboMetalPtr t_tar = std::dynamic_pointer_cast<SVRFboMetal>();
//    //创建
//    if(m_create) {
//        create(_renderer,_target,_rmesh);
//    }
//    //销毁
//    if(m_destroy){
//        destroy(_renderer,_target);
//        return ;
//    }
//    //数据更新 有肯能更新一堆数据呢
//    if(_rmesh->m_vert_up.m_pdata){
//        //[t_tar->m_cmdEncoder setVertexBuffer:m_dbufs[_rmesh->m_vert_up.m_order] offset:0 atIndex:0];
//        //[//t_tar->m_cmdEncoder setVertexBufferOffset:0 atIndex:0];
////        - (void)setVertexBuffers:(const id <MTLBuffer> __nullable [__nonnull])buffers offsets:(const NSUInteger [__nonnull])offsets withRange:(NSRange)range;
//    }
//    //
//    if( m_ibuf ) {
//        [t_tar->m_cmdEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
//                                        indexCount:m_iCnt
//                                         indexType:MTLIndexTypeUInt16
//                                       indexBuffer:m_ibuf
//                                 indexBufferOffset:m_ibufOff
//                                 instanceCount:m_instCnt ];
//    }else{
//        [t_tar->m_cmdEncoder drawPrimitives:MTLPrimitiveTypeTriangle
//        vertexStart:m_vertStart
//        vertexCount:m_vertCnt];
//    }
//    [t_tar->m_cmdEncoder endEncoding]; // 结束
}

void SVRMeshMetal::destroy(SVRendererPtr _renderer,SVRTargetPtr _target){
    if(m_ibuf) {
        m_ibuf = nullptr;
    }
    for(s32 i=0;i<m_dbufs.size();i++) {
        m_dbufs[i] = nullptr;
    }
    m_dbufs.clear();
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


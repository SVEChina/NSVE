//
// SVRBufferMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRBufferMetal.h"
#include "SVRendererMetal.h"
#include "SVRFboMetal.h"
#include "../SVRenderMesh.h"
#include "../SVRTarget.h"
#include "../../base/SVDataSwap.h"

using namespace sv;

SVRBufferMetal::SVRBufferMetal(SVInstPtr _app)
:SVRBuffer(_app){
    //
    m_dbufs.resize(SV_MAX_STREAM_NUM);
    for(s32 i=0;i<SV_MAX_STREAM_NUM;i++) {
        m_dbufs[i] = nullptr;
    }
    //
    m_ibuf = nullptr;
    m_vertStart = 0;
    m_vertCnt = 0;
    m_iCnt = 0;
    m_ibufOff = 0;
    m_instCnt = 0;
    m_bufmode = E_BFM_AOS;
}

SVRBufferMetal::~SVRBufferMetal() {
    destroy(nullptr, nullptr);
}

void SVRBufferMetal::create(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVRenderMeshPtr t_rendermesh = std::dynamic_pointer_cast<SVRenderMesh>(m_logic_obj);
    if(t_rm && t_rendermesh) {
        //索引
        BufferDsp* t_index_dsp = t_rendermesh->getIndexDsp();
        if(t_index_dsp && t_index_dsp->_bufVertDsp ==E_VF_INDEX) {
            m_iCnt = t_index_dsp->_vertCnt;
            m_ibuf = [t_rm->m_pDevice newBufferWithBytes:t_index_dsp->_bufData->getData() length: t_index_dsp->_bufSize options: MTLResourceStorageModeShared ];
        }
        //多实例
        BufferDsp* t_instance_dsp = t_rendermesh->getInstanceDsp();
        if(t_instance_dsp && t_instance_dsp->_bufSize>0) {
            if(t_instance_dsp->_bufData) {
                m_instance_buf = [t_rm->m_pDevice newBufferWithBytes:t_instance_dsp->_bufData->getData() length: t_instance_dsp->_bufSize options: MTLResourceStorageModeShared ];
            }else{
                m_instance_buf = [t_rm->m_pDevice newBufferWithLength:t_instance_dsp->_bufSize options: MTLResourceStorageModeShared ];
            }
        }
        //创建buf
        BufferDsp* t_buf_dsp = t_rendermesh->getStreamDsp();
        //E_BFM_AOS
        m_bufmode = t_buf_dsp->_bufMode;
        if( t_buf_dsp->_bufMode == E_BFM_AOS ) {
            m_vert_dsp = [[MTLVertexDescriptor alloc] init];
            VFTYPE _vf = t_buf_dsp->_bufVertDsp;
            s32 t_attri_index = 0;
            s32 t_vert_size = 0;
            s32 t_off = 0;
            if (_vf & D_VF_V2) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 2*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_V3) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 3*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_NOR) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 3*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_TAG) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 3*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_BTAG) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 3*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_C0) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUChar4;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 4*sizeof(u8);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_T0) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 2*sizeof(f32);
            }
            if (_vf & D_VF_T1) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 2*sizeof(f32);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_BONE) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUShort4;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 4*sizeof(u16);
                t_off = t_vert_size;
            }
            if (_vf & D_VF_BONE_W) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat4;
                m_vert_dsp.attributes[t_attri_index].offset = t_off;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                t_attri_index++;
                t_vert_size += 4*sizeof(f32);
                t_off = t_vert_size;
            }
            // Position Buffer Layout
            m_vert_dsp.layouts[0].stride = t_vert_size;
            //stepRate和stepFunction 在inst技术和tess技术中可以被设置
            m_vert_dsp.layouts[0].stepRate = 1;
            m_vert_dsp.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
            //创建一个buf
            id<MTLBuffer> posBuf = [t_rm->m_pDevice newBufferWithBytes:t_buf_dsp->_bufData->getData()
                                                     length: t_buf_dsp->_bufSize
                                                    options: MTLResourceStorageModeShared ];
            //单一流
            m_dbufs[0] = posBuf;
            m_streanNum = 1;
        }else {
            //混合流模式
            m_vert_dsp = [[MTLVertexDescriptor alloc] init];
            VFTYPE _vf = t_buf_dsp->_bufVertDsp;
            s32 t_attri_index = 0;
            s32 t_vert_size = 0;
            s8* t_pointer = (s8*)(t_buf_dsp->_bufData->getData());
            s32 t_pointer_off = 0;
            if (_vf & D_VF_V2) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 2*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_V3) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 3*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_NOR) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 3*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_TAG) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 3*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BTAG) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat3;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                //
                m_vert_dsp.layouts[t_attri_index].stride = 3*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_C0) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUChar4;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 4*sizeof(u8);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 4*sizeof(u8)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_T0) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 2*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_T1) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat2;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 2*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BONE) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatUShort4;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 4*sizeof(u16);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 4*sizeof(u16)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BONE_W) {
                m_vert_dsp.attributes[t_attri_index].format = MTLVertexFormatFloat4;
                m_vert_dsp.attributes[t_attri_index].offset = 0;
                m_vert_dsp.attributes[t_attri_index].bufferIndex = 0;
                m_vert_dsp.layouts[t_attri_index].stride = 4*sizeof(f32);
                m_vert_dsp.layouts[t_attri_index].stepRate = 1;
                m_vert_dsp.layouts[t_attri_index].stepFunction = MTLVertexStepFunctionPerVertex;
                //
                t_vert_size += 4*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            m_streanNum = t_attri_index;
        }
        m_exist = true;
    }
}

void SVRBufferMetal::destroy(SVRendererPtr _renderer) {
}

void SVRBufferMetal::render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVRFboMetalPtr t_fbo = std::dynamic_pointer_cast<SVRFboMetal>( _target->getResFbo() );
    if(t_rm && t_fbo) {
        //绑定
        for(s32 i=0;i<SV_MAX_STREAM_NUM;i++) {
            if(m_dbufs[i]) {
                [t_fbo->m_cmdEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];    //i表示的buf和索引的对应
            }
        }
        //绘制
        if( m_ibuf ) {
            if(m_instance_buf) {
                //多实体
                [t_fbo->m_cmdEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff
                                         instanceCount:m_instCnt];
            }else{
                //非多实例，索引绘制
                [t_fbo->m_cmdEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff];
            }
        }else{
            //正常顶点绘制
            if(m_instance_buf) {
                //多实体
                [t_fbo->m_cmdEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt instanceCount:m_instCnt baseInstance:0];
            }else{
                //非多实例，顶点绘制
                [t_fbo->m_cmdEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt];
            }
        }
        [t_fbo->m_cmdEncoder endEncoding]; // 结束
    }
    
//    -(void)setTessellationFactorBuffer:(nullable id <MTLBuffer>)buffer offset:(NSUInteger)offset instanceStride:(NSUInteger)instanceStride API_AVAILABLE(macos(10.12), ios(10.0));
}

void SVRBufferMetal::destroy(SVRendererPtr _renderer,SVRTargetPtr _target){
    if(m_ibuf) {
        m_ibuf = nullptr;
    }
    for(s32 i=0;i<m_dbufs.size();i++) {
        m_dbufs[i] = nullptr;
    }
    m_dbufs.clear();
}

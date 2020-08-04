//
// SVRMeshMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshMetal.h"
#include "SVRendererMetal.h"
#include "SVRFboMetal.h"
#include "../SVRenderMesh.h"
#include "../SVRTarget.h"
#include "../../base/SVDataSwap.h"

using namespace sv;

SVRMeshMetal::SVRMeshMetal(SVInstPtr _app)
:SVRMeshRes(_app){
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

SVRMeshMetal::~SVRMeshMetal() {
    //destroy(nullptr);
}

void SVRMeshMetal::create(SVRendererPtr _renderer) {
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
        BufferDsp* t_buf_dsp = t_rendermesh->getStreamDsp();
        if( t_buf_dsp->_bufMode == E_BFM_AOS ) {
            //创建一个buf
            id<MTLBuffer> posBuf = [t_rm->m_pDevice newBufferWithBytes:t_buf_dsp->_bufData->getData()
                                                     length: t_buf_dsp->_bufSize
                                                    options: MTLResourceStorageModeShared ];
            //单一流
            m_dbufs[0] = posBuf;
            m_streanNum = 1;
        }else{
            //混合流模式
            VFTYPE _vf = t_buf_dsp->_bufVertDsp;
            s32 t_attri_index = 0;
            s32 t_vert_size = 0;
            s8* t_pointer = (s8*)(t_buf_dsp->_bufData->getData());
            s32 t_pointer_off = 0;
            if (_vf & D_VF_V2) {
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_V3) {
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_NOR) {
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_TAG) {
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BTAG) {
                t_vert_size += 3*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_C0) {
                t_vert_size += 4*sizeof(u8)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_T0) {
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_T1) {
                t_vert_size += 2*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BONE) {
                t_vert_size += 4*sizeof(u16)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            if (_vf & D_VF_BONE_W) {
                t_vert_size += 4*sizeof(f32)*t_buf_dsp->_vertCnt;
                m_dbufs[t_attri_index] = [t_rm->m_pDevice newBufferWithBytes:t_pointer + t_pointer_off
                                                         length: t_vert_size
                                                        options: MTLResourceStorageModeShared ];
                t_pointer_off = t_vert_size;
                t_attri_index++;
            }
            m_streanNum = t_attri_index;
        }
    }
    m_exist = true;
}

void SVRMeshMetal::destroy(SVRendererPtr _renderer) {
    if(m_ibuf) {
        m_ibuf = nullptr;
    }
    for(s32 i=0;i<m_dbufs.size();i++) {
        m_dbufs[i] = nullptr;
    }
    m_dbufs.clear();
}

s32 SVRMeshMetal::process(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && t_rm->m_pCurEncoder) {
        for(s32 i=0;i<SV_MAX_STREAM_NUM;i++) {
            if(m_dbufs[i]) {
                [t_rm->m_pCurEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];    //i表示的buf和索引的对应
            }
        }
    }
    return 0;
}

void SVRMeshMetal::draw(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && t_rm->m_pCurEncoder) {
        if( m_ibuf ) {
            if(m_instance_buf) {
                //多实体
                [t_rm->m_pCurEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff
                                         instanceCount:m_instCnt];
            }else{
                //非多实例，索引绘制
                [t_rm->m_pCurEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff];
            }
        }else{
            //正常顶点绘制
            if(m_instance_buf) {
                //多实体
                [t_rm->m_pCurEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt instanceCount:m_instCnt baseInstance:0];
            }else{
                //非多实例，顶点绘制
                [t_rm->m_pCurEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt];
            }
        }
        [t_rm->m_pCurEncoder endEncoding]; // 结束
    }
}

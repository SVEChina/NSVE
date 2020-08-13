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
}

void SVRMeshMetal::create(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVRenderMeshPtr t_rendermesh = std::dynamic_pointer_cast<SVRenderMesh>(m_logic_obj);
    if(t_rm && t_rendermesh) {
        //索引
        BufferDspPtr t_index_dsp = t_rendermesh->getIndexDsp();
        if(t_index_dsp && t_index_dsp->getVertType() == E_VF_INDEX) {
            m_iCnt = t_index_dsp->_vertCnt;
            if(t_index_dsp->_bufData) {
                void* t_p = t_index_dsp->_bufData->getData();
                s32 t_len = t_index_dsp->_bufData->getSize();
                m_ibuf = [t_rm->m_pDevice newBufferWithBytes:t_p length:t_len options: MTLResourceStorageModeShared ];
            }else{
                s32 t_len = t_index_dsp->_bufSize;
                m_ibuf = [t_rm->m_pDevice newBufferWithLength:t_len options: MTLResourceStorageModeShared ];
            }
        }
        //多实例
        BufferDspPtr t_instance_dsp = t_rendermesh->getInstanceDsp();
        if(t_instance_dsp && t_instance_dsp->_bufSize>0) {
            if(t_instance_dsp->_bufData) {
                void* t_p = t_instance_dsp->_bufData->getData();
                s32 t_len = t_instance_dsp->_bufData->getSize();
                m_instance_buf = [t_rm->m_pDevice newBufferWithBytes:t_p length:t_len options: MTLResourceStorageModeShared ];
            }else{
                m_instance_buf = [t_rm->m_pDevice newBufferWithLength:t_instance_dsp->_bufSize options: MTLResourceStorageModeShared ];
            }
        }
        //顶点数据
        BufferDspPtr t_buf_dsp = t_rendermesh->getStreamDsp();
        if( t_buf_dsp->_bufMode == E_BFM_AOS ) {
            //单流
            if(t_buf_dsp->_bufData) {
                void* t_p = t_buf_dsp->_bufData->getData();
                s32 t_len = t_buf_dsp->_bufData->getSize();
                m_dbufs[0] = [t_rm->m_pDevice newBufferWithBytes:t_p length: t_len options:MTLResourceStorageModeShared ];
            }else{
                s32 t_len = t_buf_dsp->_bufSize;
                m_dbufs[0] = [t_rm->m_pDevice newBufferWithLength:t_len options:MTLResourceStorageModeShared ];
            }
            m_streanNum = 1;
        }else{
            //多流
            m_streanNum = s32(t_buf_dsp->m_streamDsp.size());
            for(s32 i=0;i<m_streanNum;i++) {
                s32 t_smt = t_buf_dsp->m_streamDsp[i];
                SVDataSwapPtr t_data = t_buf_dsp->m_streamData[t_smt];
                if(t_data) {
                    void* t_point = t_data->getData();
                    s32 t_len = t_data->getSize();
                    m_dbufs[i] = [t_rm->m_pDevice newBufferWithBytes:t_point length:t_len options:MTLResourceStorageModeShared];
                }else{
                    s32 t_len = t_buf_dsp->_vertCnt*BufferDsp::getVertSize(t_buf_dsp->getVertType());
                    m_dbufs[i] = [t_rm->m_pDevice newBufferWithLength:t_len options:MTLResourceStorageModeShared];
                }
            }
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

//处理
s32 SVRMeshMetal::process(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && t_rm->m_curEncoder) {
        for(s32 i=0;i<SV_MAX_STREAM_NUM;i++) {
            if(m_dbufs[i]) {
                [t_rm->m_curEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];
            }
        }
    }
    return 0;
}

void SVRMeshMetal::submit(SVDataSwapPtr _data,s32 _offset,s32 _size,s32 _bufid,s32 _buftype) {
    //提交数据
}

//绘制
void SVRMeshMetal::draw(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && t_rm->m_curEncoder) {
        if( m_ibuf ) {
            if(m_instance_buf) {
                //多实体
                [t_rm->m_curEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff
                                         instanceCount:m_instCnt];
            }else{
                //非多实例，索引绘制
                [t_rm->m_curEncoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff];
            }
        }else{
            //正常顶点绘制
            if(m_instance_buf) {
                //多实体
                [t_rm->m_curEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt instanceCount:m_instCnt baseInstance:0];
            }else{
                //非多实例，顶点绘制
                [t_rm->m_curEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:m_vertStart vertexCount:m_vertCnt];
            }
        }
    }
}

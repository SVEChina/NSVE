//
// SVRMeshMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshMetal.h"
#include "SVRendererMetal.h"
#include "SVRFboMetal.h"
#include "SVRMeshMetal.h"
#include "SVRTexMetal.h"
#include "SVRShaderMetal.h"
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
    m_ibuf = nullptr;
    m_instance_buf = nullptr;
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

void SVRMeshMetal::create(SVRendererPtr _renderer,
                          SVIndexStreamDspPtr _indexdsp,
                          SVVertStreamDspPtr _streamdsp,
                          SVInstStreamDspPtr _instdsp,
                          SVRMeshDsp* _SVRMeshDsp) {
    SVRMeshRes::create(_renderer, _indexdsp, _streamdsp, _instdsp,_SVRMeshDsp);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm ) {
        //索引
        if(m_index_dsp) {
            m_rmesh_dsp->m_draw_num = m_index_dsp->_indexCnt;
            if(m_index_dsp->_bufData) {
                void* t_p = m_index_dsp->_bufData->getData();
                s32 t_len = m_index_dsp->_bufData->getSize();
                m_ibuf = [t_rm->m_pDevice newBufferWithBytes:t_p length:t_len options: MTLResourceStorageModeShared ];
            }else{
                s32 t_len = m_index_dsp->_bufSize;
                m_ibuf = [t_rm->m_pDevice newBufferWithLength:t_len options: MTLResourceStorageModeShared ];
            }
        }
        //多实例
        if(m_instance_dsp && m_instance_dsp->_bufSize>0) {
            if(m_instance_dsp->_bufData) {
                void* t_p = m_instance_dsp->_bufData->getData();
                s32 t_len = m_instance_dsp->_bufData->getSize();
                m_instance_buf = [t_rm->m_pDevice newBufferWithBytes:t_p length:t_len options: MTLResourceStorageModeShared ];
            }else{
                m_instance_buf = [t_rm->m_pDevice newBufferWithLength:m_instance_dsp->_bufSize options: MTLResourceStorageModeShared ];
            }
        }
        //顶点数据
        if( m_vert_dsp->_bufMode == E_BFM_AOS ) {
            //单流
            if(m_vert_dsp->_bufData) {
                void* t_p = m_vert_dsp->_bufData->getData();
                s32 t_len = m_vert_dsp->_bufData->getSize();
                m_dbufs[0] = [t_rm->m_pDevice newBufferWithBytes:t_p length: t_len options:MTLResourceStorageModeShared ];
            }else{
                s32 t_len = m_vert_dsp->_bufSize;
                m_dbufs[0] = [t_rm->m_pDevice newBufferWithLength:t_len options:MTLResourceStorageModeShared ];
            }
            m_streanNum = 1;
        }else{
            //多流
            m_streanNum = s32(m_vert_dsp->m_streamDsp.size());
            for(s32 i=0;i<m_streanNum;i++) {
                VFTYPE t_smt = m_vert_dsp->m_streamDsp[i];
                SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_smt];
                if(t_data) {
                    void* t_point = t_data->getData();
                    s32 t_len = t_data->getSize();
                    m_dbufs[i] = [t_rm->m_pDevice newBufferWithBytes:t_point length:t_len options:MTLResourceStorageModeShared];
                }else{
                    s32 t_len = m_vert_dsp->_vertCnt*SVVertStreamDsp::getVertSize(m_vert_dsp->getVertType());
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
        //数据更新
        m_data_lock->lock();
        if(m_index && m_ibuf) {
            void* t_pointer = m_index->getData();
            s32 t_len = m_index->getSize();
            memcpy( m_ibuf.contents , t_pointer ,t_len);
        }
        if(m_inst && m_instance_buf) {
            void* t_pointer = m_inst->getData();
            s32 t_len = m_inst->getSize();
            memcpy( m_instance_buf.contents , t_pointer ,t_len);
        }
        for(s32 i=0;i<m_verts.size();i++) {
            s32 t_chn = m_verts[i]._chn;
            SVDataSwapPtr t_data = m_verts[i]._data;
            if( t_data && t_chn<m_dbufs.size() && m_dbufs[i]  ) {
                void* t_pointer = t_data->getData();
                s32 t_len = t_data->getSize();
                memcpy( m_dbufs[i].contents , t_pointer ,t_len);
            }
        }
        //
        for(s32 i=0;i<SV_MAX_STREAM_NUM;i++) {
            if(m_dbufs[i]) {
                [t_rm->m_curEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];
            }
        }
        m_data_lock->unlock();
    }
    return 0;
}

//绘制
void SVRMeshMetal::draw(SVRendererPtr _renderer) {
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && t_rm->m_curEncoder) {
        //
        MTLPrimitiveType t_method = MTLPrimitiveTypeTriangle;
        if(m_rmesh_dsp->m_draw_method == E_DRAW_POINTS) {
            t_method = MTLPrimitiveTypePoint;
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINES) {
            t_method = MTLPrimitiveTypeLine;
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINE_LOOP) {
            //不支持
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINE_STRIP) {
            t_method = MTLPrimitiveTypeLineStrip;
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLES) {
            t_method = MTLPrimitiveTypeTriangle;
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLE_STRIP) {
            t_method = MTLPrimitiveTypeTriangleStrip;
        }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLE_FAN) {
            //不支持
        }
        //
        if( m_ibuf ) {
            m_iCnt = m_rmesh_dsp->m_draw_num;
            if(m_instance_buf) {
                //多实体
                [t_rm->m_curEncoder drawIndexedPrimitives:t_method
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff
                                         instanceCount:m_instCnt];
            }else{
                //非多实例，索引绘制
                [t_rm->m_curEncoder drawIndexedPrimitives:t_method
                                                indexCount:m_iCnt
                                                 indexType:MTLIndexTypeUInt16
                                               indexBuffer:m_ibuf
                                         indexBufferOffset:m_ibufOff];
            }
        }else{
            m_vertCnt = m_rmesh_dsp->m_draw_num;
            //正常顶点绘制
            if(m_instance_buf) {
                //多实体
                [t_rm->m_curEncoder drawPrimitives:t_method vertexStart:m_vertStart vertexCount:m_vertCnt instanceCount:m_instCnt baseInstance:0];
            }else{
                //非多实例，顶点绘制
                [t_rm->m_curEncoder drawPrimitives:t_method vertexStart:m_vertStart vertexCount:m_vertCnt];
            }
        }
    }
}

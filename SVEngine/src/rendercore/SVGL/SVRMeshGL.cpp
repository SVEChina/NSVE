//
// SVRMeshGL.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRMeshGL.h"
#include "SVRendererGL.h"
#include "SVRShaderGL.h"
#include "../SVRenderMesh.h"
#include "../../base/SVDataSwap.h"

using namespace sv;

SVRMeshGL::SVRMeshGL(SVInstPtr _app)
:SVRMeshRes(_app)
,m_indexID(0)
,m_instanceID(0){
}

SVRMeshGL::~SVRMeshGL() {
}

void SVRMeshGL::load(SVRendererPtr _renderer,
                     SVIndexStreamDspPtr _indexdsp,
                     SVVertStreamDspPtr _streamdsp,
                     SVInstStreamDspPtr _instdsp,
                     SVRMeshDsp* _SVRMeshDsp) {
    SVRMeshRes::load(_renderer, _indexdsp, _streamdsp, _instdsp,_SVRMeshDsp);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    if(t_rm) {
        //索引
        if(m_index_dsp ){
            glGenBuffers(1, &m_indexID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
            s32 t_pool_type = GL_STATIC_DRAW;
            if(m_index_dsp->_bufType == E_BFT_STATIC_DRAW) {
                t_pool_type = GL_STATIC_DRAW;
            }else if(m_index_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
                t_pool_type = GL_DYNAMIC_DRAW;
            }else if(m_index_dsp->_bufType == E_BFT_STREAM_DRAW) {
                t_pool_type = GL_STREAM_DRAW;
            }
            if(m_index_dsp->_bufData) {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             m_index_dsp->_bufData->getSize(),
                             m_index_dsp->_bufData->getData(),
                             t_pool_type);
            }else{
                glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                             m_index_dsp->_bufSize,
                             0,
                             t_pool_type);
            }
        }
        //多实例
        if(m_instance_dsp ){
            glGenBuffers(1, &m_instanceID);
            glBindBuffer(GL_ARRAY_BUFFER, m_instanceID);
            s32 t_pool_type = GL_STATIC_DRAW;
            if(m_instance_dsp->_bufType == E_BFT_STATIC_DRAW) {
                t_pool_type = GL_STATIC_DRAW;
            }else if(m_instance_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
                t_pool_type = GL_DYNAMIC_DRAW;
            }else if(m_instance_dsp->_bufType == E_BFT_STREAM_DRAW) {
                t_pool_type = GL_STREAM_DRAW;
            }
            if(m_instance_dsp->_bufData) {
                glBufferData(GL_ARRAY_BUFFER,
                             m_instance_dsp->_bufData->getSize(),
                             m_instance_dsp->_bufData->getData(),
                             t_pool_type);
            }else{
                glBufferData(GL_ARRAY_BUFFER,
                             m_instance_dsp->_bufSize,
                             0,
                             t_pool_type);
            }
        }
        
        //顶点数据
        if(m_vert_dsp) {
            s32 t_pool_type = GL_STATIC_DRAW;
            if(m_vert_dsp->_bufType == E_BFT_STATIC_DRAW) {
               t_pool_type = GL_STATIC_DRAW;
            }else if(m_vert_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
               t_pool_type = GL_DYNAMIC_DRAW;
            }else if(m_vert_dsp->_bufType == E_BFT_STREAM_DRAW) {
               t_pool_type = GL_STREAM_DRAW;
            }
            if(m_vert_dsp->_bufMode == E_BFM_AOS) {
                //单一混合流
                s32 t_stream_num = 1;
                glGenBuffers(t_stream_num, m_bufID);
                if(m_vert_dsp->_bufData) {
                    glBufferData(GL_ARRAY_BUFFER,
                                 m_vert_dsp->_bufData->getSize(),
                                 m_vert_dsp->_bufData->getData(),
                                 t_pool_type);
                }else{
                    glBufferData(GL_ARRAY_BUFFER,m_vert_dsp->_bufSize,0,t_pool_type);
                }
            }else{
                //多流
                s32 t_stream_num = s32(m_vert_dsp->m_streamDsp.size());
                glGenBuffers(t_stream_num, m_bufID);
                for(s32 i=0;i<t_stream_num;i++) {
                    VFTYPE t_stream_type = VFTYPE(m_vert_dsp->m_streamDsp[i]);
                    SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_stream_type];
                    if(t_data) {
                        glBufferData(GL_ARRAY_BUFFER,t_data->getSize(),t_data->getData(),t_pool_type);
                    }else{
                        s32 t_size = m_vert_dsp->_vertCnt * SVVertStreamDsp::getVertSize(VFTYPE(t_stream_type));  //顶点数*类型
                        glBufferData(GL_ARRAY_BUFFER,t_size,0,t_pool_type);
                    }
                }
            }
        }
        m_exist = true;
    }
}

void SVRMeshGL::unload() {
    if(m_exist) {
        m_exist = false;
        if(m_indexID>0) {
            glDeleteBuffers(1, &m_indexID);
        }
        if(m_instanceID>0) {
            glDeleteBuffers(1, &m_instanceID);
        }
        if(m_vert_dsp) {
            s32 t_bufnum = m_vert_dsp->m_streamDsp.size();
            glDeleteBuffers(t_bufnum, m_bufID);
        }
    }
}

s32 SVRMeshGL::process(SVRendererPtr _renderer){
    SVRRes::process(_renderer);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    //数据更新
    m_data_lock->lock();
    //index
    if(m_index_dsp && m_index_dsp->_bufData && m_indexID>0) {
        void* t_pointer =  m_index_dsp->_bufData->getData();
        s32 t_len =  m_index_dsp->_bufData->getSize();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
        glBufferSubData(GL_ARRAY_BUFFER,0,t_len,t_pointer);
    }
    
    //inst
    if(m_instance_dsp && m_instance_dsp->_bufData && m_instanceID>0) {
        void* t_pointer = m_instance_dsp->_bufData->getData();
        s32 t_len = m_instance_dsp->_bufData->getSize();
        glBindBuffer(GL_ARRAY_BUFFER,m_instanceID);
        glBufferSubData(GL_ARRAY_BUFFER,0,t_len,t_pointer);
    }
    
    if( m_vert_dsp ) {
        if( m_vert_dsp->_bufMode == E_BFM_AOS ) {
            //混合流模式
            VFTYPE t_vf_type = m_vert_dsp->m_streamDsp[0];  //流描述
            SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_vf_type];
            if(t_data) {
                void* t_pointer = t_data->getData();
                s32 t_len = t_data->getSize();
                glBindBuffer(GL_ARRAY_BUFFER, m_bufID[0]);
                glBufferSubData(GL_ARRAY_BUFFER,0,t_len,t_pointer);
            }
        } else {
            //单一流模式
            for(s32 i=0;i<m_vert_dsp->m_streamDsp.size();i++) {
                VFTYPE t_vf_type = m_vert_dsp->m_streamDsp[i];  //流描述
                SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_vf_type];
                if(t_data) {
                    void* t_pointer = t_data->getData();
                    s32 t_len = t_data->getSize();
                    glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
                    glBufferSubData(GL_ARRAY_BUFFER,0,t_len,t_pointer);
                }
            }
        }
    }
    m_data_lock->unlock();
    //
    if(m_vert_dsp->m_streamDsp.size()>0) {
        u32 t_program = t_rm->m_cur_program;
        for(s32 i=0;i<m_vert_dsp->m_streamDsp.size();i++) {
            glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
            VFTYPE _vf = m_vert_dsp->m_streamDsp[i];
            s8* t_off = 0;
            if (_vf & E_VF_V2) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & E_VF_V3) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 3 * sizeof(f32);
            }
            if (_vf & E_VF_NOR) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_NORMAL);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 3 * sizeof(f32);
            }
            if (_vf & E_VF_TAG) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TAGENT);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
            if (_vf & E_VF_BTAG) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_BNOR);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
            if (_vf & E_VF_C0) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_COLOR);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void *)t_off);
                t_off += 4 * sizeof(u8);
            }
            if (_vf & E_VF_T0) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD0);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & E_VF_T1) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD1);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & E_VF_BONE) {
                //骨骼ID
                s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_ID);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(u16);
            }
            if (_vf & E_VF_BONE_W) {
                //骨骼权重
                s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_WEIGHT);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
        }
    }
    return 1;
}

void SVRMeshGL::draw(SVRendererPtr _renderer) {
    if(!m_rmesh_dsp)
        return ;
    //绘制
    s32 t_method = GL_TRIANGLES;
    if(m_rmesh_dsp->m_draw_method == E_DRAW_POINTS) {
        t_method = GL_POINTS;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINES) {
        t_method = GL_LINES;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINE_LOOP) {
        t_method = GL_LINE_LOOP;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_LINE_STRIP) {
        t_method = GL_LINE_STRIP;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLES) {
        t_method = GL_TRIANGLES;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLE_STRIP) {
        t_method = GL_TRIANGLE_STRIP;
    }else if(m_rmesh_dsp->m_draw_method == E_DRAW_TRIANGLE_FAN) {
        t_method = GL_TRIANGLE_FAN;
    }
    //draw
    if(m_instanceID>0) {
        if(m_indexID>0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
            glDrawElementsInstanced(t_method, m_rmesh_dsp->m_draw_num, GL_UNSIGNED_SHORT, 0, m_instacne_count);
       }else{
           glDrawArraysInstanced(t_method, 0, m_rmesh_dsp->m_draw_num, m_instacne_count);
       }
    }else{
        if(m_indexID>0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
            glDrawElements(t_method, m_rmesh_dsp->m_draw_num, GL_UNSIGNED_SHORT, 0);
        }else{
            glDrawArrays(t_method, 0, m_rmesh_dsp->m_draw_num);
        }
    }
}

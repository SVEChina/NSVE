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
,m_bufnum(0)
,m_instanceID(0){
    m_mode = E_BFM_AOS;
}

SVRMeshGL::~SVRMeshGL() {
}

void SVRMeshGL::create(SVRendererPtr _renderer,
                       BufferDspPtr _indexdsp,
                       BufferDspPtr _streamdsp,
                       BufferDspPtr _instdsp) {
    SVRMeshRes::create(_renderer, _indexdsp, _streamdsp, _instdsp);
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
            //m_instacne_count = t_dsp->_bufSize;
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
            m_mode = m_vert_dsp->_bufMode;
            s32 t_pool_type = GL_STATIC_DRAW;
            if(m_vert_dsp->_bufType == E_BFT_STATIC_DRAW) {
               t_pool_type = GL_STATIC_DRAW;
            }else if(m_vert_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
               t_pool_type = GL_DYNAMIC_DRAW;
            }else if(m_vert_dsp->_bufType == E_BFT_STREAM_DRAW) {
               t_pool_type = GL_STREAM_DRAW;
            }
            if(m_mode == E_BFM_AOS) {
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
                    m_ver_dsp.push_back(t_stream_type);
                    SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_stream_type];
                    if(t_data) {
                        glBufferData(GL_ARRAY_BUFFER,t_data->getSize(),t_data->getData(),t_pool_type);
                    }else{
                        s32 t_size = m_vert_dsp->_vertCnt * BufferDsp::getVertSize(VFTYPE(t_stream_type));  //顶点数*类型
                        glBufferData(GL_ARRAY_BUFFER,t_size,0,t_pool_type);
                    }
                }
            }
        }
        m_exist = true;
    }
}

void SVRMeshGL::destroy(SVRendererPtr _renderer) {
    if(m_exist) {
        m_exist = false;
        if(m_indexID>0) {
            glDeleteBuffers(1, &m_indexID);
        }
        if(m_instanceID>0) {
            glDeleteBuffers(1, &m_instanceID);
        }
        glDeleteBuffers(m_bufnum, m_bufID);
    }
}

s32 SVRMeshGL::process(SVRendererPtr _renderer){
    SVRRes::process(_renderer);
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    //数据更新
    m_data_lock->lock();    
    //index
    if(m_index && m_indexID>0) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
        glBufferSubData(GL_ARRAY_BUFFER,0,m_index->getSize(),m_index->getData());
    }
    
    //inst
    if(m_inst && m_instanceID>0) {
        glBindBuffer(GL_ARRAY_BUFFER,m_instanceID);
        glBufferSubData(GL_ARRAY_BUFFER,0,m_inst->getSize(),m_inst->getData());
    }
    
    //vert
    if(m_mode == E_BFM_AOS) {
        //单一数据，混合流
        
    }else{
        //多流方式
    }
    m_data_lock->unlock();
    //
    if(m_ver_dsp.size()>0) {
        u32 t_program = t_rm->m_cur_program;
        if(m_ver_dsp.size()!=m_bufnum) {
            return -1;  //流的数目和buf数目不相等，就错误的
        }
        for(s32 i=0;i<m_ver_dsp.size();i++) {
            //绑定buf
            glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
            //设置顶点描述
            VFTYPE _vf = m_ver_dsp[i];
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
    //绘制
    s32 t_method = GL_TRIANGLES;
    if(m_draw_method == E_DRAW_POINTS) {
        t_method = GL_POINTS;
    }else if(m_draw_method == E_DRAW_LINES) {
        t_method = GL_LINES;
    }else if(m_draw_method == E_DRAW_LINE_LOOP) {
        t_method = GL_LINE_LOOP;
    }else if(m_draw_method == E_DRAW_LINE_STRIP) {
        t_method = GL_LINE_STRIP;
    }else if(m_draw_method == E_DRAW_TRIANGLES) {
        t_method = GL_TRIANGLES;
    }else if(m_draw_method == E_DRAW_TRIANGLE_STRIP) {
        t_method = GL_TRIANGLE_STRIP;
    }else if(m_draw_method == E_DRAW_TRIANGLE_FAN) {
        t_method = GL_TRIANGLE_FAN;
    }
    //draw
    if(m_instanceID>0) {
        if(m_indexID>0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
            glDrawElementsInstanced(t_method, m_draw_num, GL_UNSIGNED_SHORT, 0, m_instacne_count);
       }else{
           glDrawArraysInstanced(t_method, 0, m_draw_num, m_instacne_count);
       }
    }else{
        if(m_indexID>0) {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
            glDrawElements(t_method, m_draw_num, GL_UNSIGNED_SHORT, 0);
        }else{
            glDrawArrays(t_method, 0, m_draw_num);
        }
    }
}

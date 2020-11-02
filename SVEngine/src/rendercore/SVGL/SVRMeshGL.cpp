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
    for(s32 i=0;i<MAX_VERTEX_STEAM_NUM;i++) {
        m_bufID[i] = 0;
    }
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
                m_index_dsp->_bufData = nullptr;
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
                m_instance_dsp->_bufData = nullptr;
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
                if(m_vert_dsp->m_mixStreamData) {
                    glBindBuffer(GL_ARRAY_BUFFER, m_bufID[0]);
                    glBufferData(GL_ARRAY_BUFFER,
                                 m_vert_dsp->m_mixStreamData->getSize(),
                                 m_vert_dsp->m_mixStreamData->getData(),
                                 t_pool_type);
                    m_vert_dsp->m_mixStreamData = nullptr;
                }else{
                    glBindBuffer(GL_ARRAY_BUFFER, m_bufID[0]);
                    glBufferData(GL_ARRAY_BUFFER,m_vert_dsp->_bufSize,0,t_pool_type);
                }
            }else{
                //多流
                s32 t_stream_num = s32(m_vert_dsp->m_streamDsp.size());
                glGenBuffers(t_stream_num, m_bufID);
                for(s32 i=0;i<t_stream_num;i++) {
                    VFTYPE t_vft = VFTYPE(m_vert_dsp->m_streamDsp[i]);
                    SVDataSwapPtr t_data = m_vert_dsp->m_streamData[t_vft];
                    if(t_data) {
                        glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
                        glBufferData(GL_ARRAY_BUFFER,t_data->getSize(),t_data->getData(),t_pool_type);
                        m_vert_dsp->m_streamData[t_vft] = nullptr;
                    }else{
                        glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
                        s32 t_size = m_vert_dsp->_vertCnt * m_vert_dsp->getVertSize(t_vft);
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
    //
    if( m_vert_dsp ) {
        if( m_vert_dsp->_bufMode == E_BFM_AOS ) {
            //混合流模式
            if(m_vert_dsp->m_mixStreamData) {
                void* t_pointer = m_vert_dsp->m_mixStreamData->getData();
                s32 t_len = m_vert_dsp->m_mixStreamData->getSize();
                glBindBuffer(GL_ARRAY_BUFFER, m_bufID[0]);
                glBufferSubData(GL_ARRAY_BUFFER,0,t_len,t_pointer);
                m_vert_dsp->m_mixStreamData = nullptr;
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
                    m_vert_dsp->m_streamData[t_vf_type] = nullptr;
                }
            }
        }
    }
    m_data_lock->unlock();
    //数据描述
    if( m_vert_dsp->_bufMode == E_BFM_AOS ) {
        //混合流描述
        glBindBuffer(GL_ARRAY_BUFFER, m_bufID[0]);
        if(m_vert_dsp->m_streamDsp.size()>0) {
            s8* t_off = 0;
            u32 t_program = t_rm->m_cur_program;
            s32 t_vert_size = m_vert_dsp->getVertSize();
            for(s32 i=0;i<m_vert_dsp->m_streamDsp.size();i++) {
                VFTYPE _vf = m_vert_dsp->m_streamDsp[i];
                if (_vf == E_VF_V2) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, t_vert_size,(void *)t_off);
                    }
                    t_off += 2 * sizeof(f32);
                } else if (_vf == E_VF_V3) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 3 * sizeof(f32);
                } else if (_vf == E_VF_NOR) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_NORMAL);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 3 * sizeof(f32);
                } else if (_vf == E_VF_TAG) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TAGENT);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 4 * sizeof(f32);
                } else if (_vf == E_VF_BTAG) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BNOR);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 4 * sizeof(f32);
                } else if (_vf == E_VF_C0) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_COLOR);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_BYTE, GL_TRUE, t_vert_size, (void *)t_off);
                    }
                    t_off += 4 * sizeof(u8);
                } else if (_vf == E_VF_T0) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD0);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 2 * sizeof(f32);
                } else if (_vf == E_VF_T1) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD1);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 2 * sizeof(f32);
                } else if (_vf == E_VF_BONE) {
                    //骨骼ID
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_ID);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_SHORT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 4 * sizeof(u16);
                } else if (_vf == E_VF_BONE_W) {
                    //骨骼权重
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_WEIGHT);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, t_vert_size, (void *)t_off);
                    }
                    t_off += 4 * sizeof(f32);
                }
            }
        }
    } else {
        //单一流描述
        if(m_vert_dsp->m_streamDsp.size()>0) {
            u32 t_program = t_rm->m_cur_program;
            for(s32 i=0;i<m_vert_dsp->m_streamDsp.size();i++) {
                glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
                VFTYPE _vf = m_vert_dsp->m_streamDsp[i];
                s8* t_off = 0;
                if (_vf == E_VF_V2) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 2*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_V3) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_NOR) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_NORMAL);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 3*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_TAG) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TAGENT);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 4*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_BTAG) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BNOR);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 4*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_C0) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_COLOR);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_BYTE, GL_TRUE, 4*sizeof(s8), 0);
                    }
                } else if (_vf == E_VF_T0) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD0);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 2*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_T1) {
                    s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD1);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 2*sizeof(f32), 0);
                    }
                } else if (_vf == E_VF_BONE) {
                    //骨骼ID
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_ID);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_SHORT, GL_FALSE, 4*sizeof(s16), 0);
                    }
                } else if (_vf & E_VF_BONE_W) {
                    //骨骼权重
                    s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_WEIGHT);
                    if(t_attr>=0) {
                        glEnableVertexAttribArray(t_attr);
                        glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 4*sizeof(f32), 0);
                    }
                }
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
    if(m_instance_dsp ) { //多实例
        if(m_instance_dsp->_instCnt>0) {
            if( m_index_dsp ) {
                //索引方式
                s32 t_index_formate;
                if(m_index_dsp->_dataType == 16) {
                    t_index_formate = GL_UNSIGNED_SHORT;
                }else{
                    t_index_formate = GL_UNSIGNED_INT;
                }
                //
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
                glDrawElementsInstanced(t_method,
                                        m_rmesh_dsp->m_draw_num,
                                        t_index_formate,
                                        0,
                                        m_instance_dsp->_instCnt);
            }else{
                //非索引方式
                glDrawArraysInstanced(t_method,
                                      0,
                                      m_rmesh_dsp->m_draw_num,
                                      m_instance_dsp->_instCnt);
            }
        }
    } else {
        if( m_index_dsp ) {
            s32 t_index_formate;
            if(m_index_dsp->_dataType == 16) {
                t_index_formate = GL_UNSIGNED_SHORT;
            }else{
                t_index_formate = GL_UNSIGNED_INT;
            }
            if( m_indexID>0) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
                glDrawElements(t_method, m_rmesh_dsp->m_draw_num,t_index_formate, 0);
//                s32 t_error = glGetError();
//                if(t_error>GL_NO_ERROR) {
//                    if(t_error!=GL_INVALID_ENUM) {
//                        int a = 0;
//                    }
//                }
            }
        }else {
            glDrawArrays(t_method, 0, m_rmesh_dsp->m_draw_num);
        }
    }
    //该关闭关闭
    for(s32 i=0;i<8;i++) {
        glDisableVertexAttribArray(i);
    }
}

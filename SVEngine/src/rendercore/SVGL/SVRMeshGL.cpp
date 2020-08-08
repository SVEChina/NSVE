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
}

SVRMeshGL::~SVRMeshGL() {
}

void SVRMeshGL::create(SVRendererPtr _renderer) {
    SVRendererGLPtr t_rm = std::dynamic_pointer_cast<SVRendererGL>(_renderer);
    SVRenderMeshPtr t_rendermesh = std::dynamic_pointer_cast<SVRenderMesh>(m_logic_obj);
    if(t_rm && t_rendermesh) {
        if( t_rendermesh->useIndex() ) {
            glGenBuffers(1, &m_indexID);
            BufferDspPtr t_dsp = t_rendermesh->getIndexDsp();
            if(t_dsp ){
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexID);
                s32 t_pool_type = GL_STATIC_DRAW;
                if(t_dsp->_bufType == E_BFT_STATIC_DRAW) {
                    t_pool_type = GL_STATIC_DRAW;
                }else if(t_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
                    t_pool_type = GL_DYNAMIC_DRAW;
                }else if(t_dsp->_bufType == E_BFT_STREAM_DRAW) {
                    t_pool_type = GL_STREAM_DRAW;
                }
                if(t_dsp->_bufData) {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                 t_dsp->_bufData->getSize(),
                                 t_dsp->_bufData->getData(),
                                 t_pool_type);
                }else{
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                 t_dsp->_bufSize,
                                 0,
                                 t_pool_type);
                }
            }
        }
        //
        s32 t_stream_num = t_rendermesh->getStreamNum();
        if(t_stream_num>0 && t_stream_num<MAX_VERTEX_STEAM_NUM) {
            m_bufnum = t_stream_num;
            glGenBuffers(t_stream_num, m_bufID);
            BufferDspPtr t_dsp = t_rendermesh->getStreamDsp();
//            for(s32 i=0;i<t_stream_num;i++) {
//                glBindBuffer(GL_ARRAY_BUFFER, m_bufID[i]);
//                m_ver_dsp.push_back(t_dsp->_bufVertDsp);
//                //
//                s32 t_pool_type = GL_STATIC_DRAW;
//                if(t_dsp->_bufType == E_BFT_STATIC_DRAW) {
//                    t_pool_type = GL_STATIC_DRAW;
//                }else if(t_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
//                    t_pool_type = GL_DYNAMIC_DRAW;
//                }else if(t_dsp->_bufType == E_BFT_STREAM_DRAW) {
//                    t_pool_type = GL_STREAM_DRAW;
//                }
//                //
//                if(t_dsp->_bufData) {
//                    glBufferData(GL_ARRAY_BUFFER,
//                                 t_dsp->_bufData->getSize(),
//                                 t_dsp->_bufData->getData(),
//                                 t_pool_type);
//                    
//                }else{
//                    glBufferData(GL_ARRAY_BUFFER,
//                                 t_dsp->_bufSize,
//                                 0,
//                                 t_pool_type);
//                }
//            }//!for
        }
        //多实例
        if( t_rendermesh->useInstance() ) {
            glGenBuffers(1, &m_instanceID);
            BufferDspPtr t_dsp = t_rendermesh->getInstanceDsp();
            if(t_dsp ){
                //m_instacne_count = t_dsp->_bufSize;
                glBindBuffer(GL_ARRAY_BUFFER, m_instanceID);
                s32 t_pool_type = GL_STATIC_DRAW;
                if(t_dsp->_bufType == E_BFT_STATIC_DRAW) {
                    t_pool_type = GL_STATIC_DRAW;
                }else if(t_dsp->_bufType == E_BFT_DYNAMIC_DRAW) {
                    t_pool_type = GL_DYNAMIC_DRAW;
                }else if(t_dsp->_bufType == E_BFT_STREAM_DRAW) {
                    t_pool_type = GL_STREAM_DRAW;
                }
                if(t_dsp->_bufData) {
                    glBufferData(GL_ARRAY_BUFFER,
                                 t_dsp->_bufData->getSize(),
                                 t_dsp->_bufData->getData(),
                                 t_pool_type);
                }else{
                    glBufferData(GL_ARRAY_BUFFER,
                                 t_dsp->_bufSize,
                                 0,
                                 t_pool_type);
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
            if (_vf & SV_SMT_V2) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & SV_SMT_V3) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_POSITION);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 3 * sizeof(f32);
            }
            if (_vf & SV_SMT_NOR) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_NORMAL);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 3, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 3 * sizeof(f32);
            }
            if (_vf & SV_SMT_TAG) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TAGENT);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
            if (_vf & SV_SMT_BTAG) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_BNOR);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
            if (_vf & SV_SMT_C0) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_COLOR);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void *)t_off);
                t_off += 4 * sizeof(u8);
            }
            if (_vf & SV_SMT_T0) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD0);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & SV_SMT_T1) {
                s32 t_attr = glGetAttribLocation(t_program,NAME_TEXCOORD1);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 2, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 2 * sizeof(f32);
            }
            if (_vf & SV_SMT_BONE) {
                //骨骼ID
                s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_ID);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_UNSIGNED_SHORT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(u16);
            }
            if (_vf & SV_SMT_BONE_W) {
                //骨骼权重
                s32 t_attr = glGetAttribLocation(t_program,NAME_BONE_WEIGHT);
                glEnableVertexAttribArray(t_attr);
                glVertexAttribPointer(t_attr, 4, GL_FLOAT, GL_FALSE, 0,(void *)t_off);
                t_off += 4 * sizeof(f32);
            }
        }
        s32 t_method = GL_TRIANGLES;
        if(m_draw_method == E_DM_POINTS) {
            t_method = GL_POINTS;
        }else if(m_draw_method == E_DM_LINES) {
            t_method = GL_LINES;
        }else if(m_draw_method == E_DM_LINE_LOOP) {
            t_method = GL_LINE_LOOP;
        }else if(m_draw_method == E_DM_LINE_STRIP) {
            t_method = GL_LINE_STRIP;
        }else if(m_draw_method == E_DM_TRIANGLES) {
            t_method = GL_TRIANGLES;
        }else if(m_draw_method == E_DM_TRIANGLE_STRIP) {
            t_method = GL_TRIANGLE_STRIP;
        }else if(m_draw_method == E_DM_TRIANGLE_FAN) {
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
    return 1;
}

void SVRMeshGL::submit(SVDataSwapPtr _data,s32 _offset,s32 _size,s32 _bufid,s32 _buftype) {
    //提交数据
    
}

void SVRMeshGL::draw(SVRendererPtr _renderer) {
    
}


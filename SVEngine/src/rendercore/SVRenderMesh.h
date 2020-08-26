//
// SVRenderMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMESH_H
#define SV_RENDERMESH_H

#include "SVRMeshRes.h"
#include "SVRenderDef.h"
#include "../core/SVVertDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVDataSwap.h"
#include <vector>
#include <map>

namespace sv {

    //最大支持10个流
    #define SV_MAX_STREAM_NUM 10
    //
    //1.AOS模式  混合流
    //2.SOA模式  拆分流
    //
    DECLARE_SHAREPTR(BufferDsp);
    class BufferDsp :public SVObject {
    public:
        BufferDsp(BUFFERMODE _mode) {
            _bufMode = _mode;           //E_BFM_AOS;
            _bufType = E_BFT_STATIC_DRAW;
            _vertCnt = 0;
            _bufSize = 0;
            reset();
        };
        
        ~BufferDsp() {
            _bufMode = E_BFM_AOS;
            _bufType = E_BFT_STATIC_DRAW;
            _vertCnt = 0;
            _bufSize = 0;
            reset();
        };
        
        //推送类型
        void push(VFTYPE _stype) {
            std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
            if( it == m_streamData.end() ) {
                m_streamDsp.push_back(_stype);
                m_streamData.insert(std::make_pair(_stype,nullptr));
            }
        }
        
        //设置BUF-TYPE
        void setBufType(BUFFERTYPE _btype) {
            _bufType = _btype;
        }
        
        //设置顶点数
        void setVertCnt(s32 _cnt) {
            _vertCnt = _cnt;
        }
        
        void build(BUFFERTYPE _btype,s32 _cnt) {
            setBufType(_btype);
            setVertCnt(_cnt);
        }
        
        //重置
        void reset() {
            _bufData = nullptr;
            m_streamDsp.clear();
            m_streamData.clear();
        }
        
        //数据顶点描述
        VFTYPE getVertType() {
            s32 t_vt = 0;
            for(s32 i=0;i<m_streamDsp.size();i++) {
                t_vt = t_vt | s32(m_streamDsp[i]);
            }
            return VFTYPE(t_vt);
        }
        
        static s32 getVertSize(VFTYPE _vf) {
            s32 t_size = 0;
            if (_vf & E_VF_INDEX) {
                t_size += sizeof(u16);
            }
            if (_vf & E_VF_V2) {
                t_size += 2 * sizeof(f32);
            }
            if (_vf & E_VF_V3) {
                t_size += 3 * sizeof(f32);
            }
            if (_vf & E_VF_NOR) {
                t_size += 3 * sizeof(f32);
            }
            if (_vf & E_VF_TAG) {
                t_size += 4 * sizeof(f32);
            }
            if (_vf & E_VF_BTAG) {
                t_size += 4 * sizeof(f32);
            }
            if (_vf & E_VF_C0) {
                t_size += 4 * sizeof(u8);
            }
            if (_vf & E_VF_T0) {
                t_size += 2 * sizeof(f32);
            }
            if (_vf & E_VF_T1) {
                t_size += 2 * sizeof(f32);
            }
            if (_vf & E_VF_BONE) {
                t_size += 4 * sizeof(u16);
            }
            if (_vf & E_VF_BONE_W) {
                t_size += 4 * sizeof(f32);
            }
            return t_size;
        }
        
        //设置流数据
        bool setStreamData(VFTYPE _stype,SVDataSwapPtr _data) {
            if(_bufMode == E_BFM_AOS) {
                //混合流模式，设定给单一目标就好
                _bufData = _data;
                return true;
            } else {
                //单一流模式，需要按流分开存储
                std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
                if( it == m_streamData.end() ) {
                    return false;
                }
                m_streamData[_stype] = _data;
                return true;
            }
        }
        
        bool setStreamData(VFTYPE _stype,void* _data,s32 _len) {
               if(_bufMode == E_BFM_AOS) {
                   //混合流模式，设定给单一目标就好
                   if(!_bufData) {
                       _bufData = MakeSharedPtr<SVDataSwap>();
                   }
                   _bufData->appendData(_data,_len);
                   return true;
               } else {
                   //单一流模式，需要按流分开存储
                   std::map<VFTYPE,SVDataSwapPtr>::iterator it = m_streamData.find(_stype);
                   if( it == m_streamData.end() ) {
                       return false;
                   }
                   if( !m_streamData[_stype] ) {
                       m_streamData[_stype] = MakeSharedPtr<SVDataSwap>();
                   }
                   m_streamData[_stype]->appendData(_data,_len);
                   return true;
               }
           }
        
        //
        BUFFERMODE _bufMode;    //E_BFM_AOS 混合流，E_BFM_SOA 单一流
        //数据类型
        BUFFERTYPE _bufType;    //BUFFER类型
        //数据个数
        s32 _vertCnt;           //顶点数目
        //数据尺寸
        s32 _bufSize;           //buf 尺寸
        //流描述
        std::vector<VFTYPE> m_streamDsp;  //流描述
        //流数据
        std::map<VFTYPE,SVDataSwapPtr> m_streamData;
        //数据
        SVDataSwapPtr _bufData;
    };

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */
    class SVRenderMesh : public SVGBaseEx { 
    public:
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        //设置各种描述
        void setIndexDsp(BufferDspPtr _dsp);
        
        void setVertDsp(BufferDspPtr _dsp);
        
        void setInstanceDsp(BufferDspPtr _dsp);
        
        //是否使用索引
        bool useIndex();
        
        bool useInstance();
        
        //获取索引数据描述
        BufferDspPtr getIndexDsp();
        
        //获取流数据描述
        BufferDspPtr getStreamDsp();
    
        //获取多实例描述
        BufferDspPtr getInstanceDsp();

        //获取流数目
        s32 getStreamNum();
        
        //设置数据
        void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        void setVertexData(SVDataSwapPtr _data);
        
        void setVertexData(SVDataSwapPtr _data,s32 _streamnum);
        
        void setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount);

        //设置其他属性
        void setDrawMethod(s32 _method);
        
        //设置绘制顶点数目
        void setDrawVertNum(s32 _vertexNum);
        
    public:
        bool m_use_index;
        bool m_use_instance;
        //BUF描述
        BufferDspPtr m_index_dsp;
        BufferDspPtr m_vert_dsp;
        BufferDspPtr m_instance_dsp;
        //
        s32 m_draw_method;
        //
        void bindRes(SVRMeshResPtr _res);
        //
        void unbindRes();
        //
        SVRMeshResPtr getResBuffer();
        
    protected:
        SVRMeshResPtr m_res_buffer;      //最主要的是它
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H

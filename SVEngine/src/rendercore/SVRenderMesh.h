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
#include <vector>

namespace sv {

    //最大支持10个流
    #define SV_MAX_STREAM_NUM 10
    //
    //1.AOS模式  混合流
    //2.SOA模式  拆分流
    //
    struct BufferDsp {
        BufferDsp() {
            _bufMode = E_BFM_AOS;
            _bufVertDsp = E_VF_BASE;
            _bufType = E_BFT_STATIC_DRAW;
            _vertCnt = 0;
            _bufSize = 0;
            _bufData = nullptr;
        };
        
        ~BufferDsp() {
            _bufMode = E_BFM_AOS;
            _bufVertDsp = E_VF_BASE;
            _bufType = E_BFT_STATIC_DRAW;
            _vertCnt = 0;
            _bufSize = 0;
            _bufData = nullptr;
        };
        //
        BUFFERMODE _bufMode;
        //数据顶点描述
        VFTYPE _bufVertDsp;
        //数据类型
        BUFFERTYPE _bufType;
        //数据个数
        s32 _vertCnt;
        //数据尺寸
        s32 _bufSize;
        //数据
        SVDataSwapPtr _bufData;
    };

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */
    class SVRenderMesh : public SVGBaseEx {
    public:
        static void buildBufferDsp(VFTYPE _vertype,
                                   BUFFERTYPE _buftype,
                                   s32 _vertCnt,
                                   s32 _bufsize,
                                   void* _data,
                                   BufferDsp* _dsp);
        
    public:
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        //设置各种描述
        void setIndexDsp(BufferDsp& _dsp);
        
        void setVertDsp(BufferDsp& _dsp);
        
        void setInstanceDsp(BufferDsp& _dsp);
        
        //是否使用索引
        bool useIndex();
        
        bool useInstance();
        
        //获取索引数据描述
        BufferDsp* getIndexDsp();
        
        //获取流数据描述
        BufferDsp* getStreamDsp();
    
        //获取多实例描述
        BufferDsp* getInstanceDsp();

        //获取流数目
        s32 getStreamNum();
        
        //设置数据
        void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        void setVertexData(SVDataSwapPtr _data);
        
        void setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount);

        //设置其他属性
        void setDrawMethod(s32 _method);
        
        void setVertNum(s32 _vertexNum);
        
    public:
        bool m_use_index;
        bool m_use_instance;
        //索引数据
        BufferDsp m_index_dsp;
        BufferDsp m_vert_dsp;
        BufferDsp m_instance_dsp;
        //
        s32 m_draw_method;

        void bindRes(SVRMeshResPtr _res);
        
        void unbindRes();
        
        SVRMeshResPtr getResBuffer();
        
    protected:
        SVRMeshResPtr m_res_buffer;      //最主要的是它
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H

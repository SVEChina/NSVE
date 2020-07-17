//
// SVRenderMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMESH_H
#define SV_RENDERMESH_H

#include "SVRBuffer.h"
#include "SVRenderDef.h"
#include "../core/SVVertDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#include <vector>

namespace sv {

//最大支持10个流
#define SV_MAX_STREAM_NUM 10
    //
    struct BufferDsp {
        BufferDsp() {
            _bufData = nullptr;
            _bufSize = 0;
            _bufType = E_BFT_STATIC_DRAW;
            _bufVertDsp = E_VF_BASE;
        };
        
        ~BufferDsp() {
            _bufData = nullptr;
            _bufSize = 0;
            _bufType = E_BFT_STATIC_DRAW;
            _bufVertDsp = E_VF_BASE;
        };
        //数据
        SVDataSwapPtr _bufData;
        //数据尺寸
        s32 _bufSize;
        //数据类型
        BUFFERTYPE _bufType;
        //数据顶点描述
        VFTYPE _bufVertDsp;
    };

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */
    class SVRenderMesh : public SVGBaseEx {
    public:
        static void buildBufferDsp(VFTYPE _vertype,BUFFERTYPE _buftype,s32 _bufsize,void* _data,BufferDsp* _dsp);
        
    public:
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
    
        virtual void render(SVRendererPtr _renderer);
        
        //设置各种描述
        void setIndexDsp(BufferDsp& _dsp);
        
        void setVertDsp(BufferDsp& _dsp,s32 _index = 0);
        
        void setInstanceDsp(BufferDsp& _dsp);
        
        //是否使用索引
        bool useIndex();
        
        //获取索引数据描述
        BufferDsp* getIndexDsp();
        
        //获取流数目
        s32 getStreamNum();
        
        //获取流数据描述
        BufferDsp* getStreamDsp(s32 _index);
        
        bool useInstance();
        
        //获取多实例描述
        BufferDsp* getInstanceDsp();
        
        //设置数据
        void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        void setVertexData(SVDataSwapPtr _data,s32 _index = 0,VFTYPE type = E_VF_BASE);
        
        void setInstanceData(SVDataSwapPtr _pdata, u32 _instanceCount);

        //设置其他属性
        void setDrawMethod(DRAWMETHOD drawtype);
        
        void setVertNum(s32 _vertexNum);
        
    public:
        bool m_use_index;
        bool m_use_instance;
        //索引数据
        BufferDsp m_index_dsp;
        std::vector<BufferDsp> m_vert_dsp;
        BufferDsp m_instance_dsp;
       
    public:
        void bindRes(SVRBufferPtr _res);
        
        void unbindRes();
        
        SVRBufferPtr getResBuffer();
        
    protected:
        SVRBufferPtr m_res_buffer;      //最主要的是他
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H

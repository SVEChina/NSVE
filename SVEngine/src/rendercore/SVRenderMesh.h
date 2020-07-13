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

    //定点说一句
    struct BufferDsp {
        BufferDsp() {
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
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
    
        virtual void render(SVRendererPtr _renderer);
        
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
        
        //
        void setIndexPoolType(u32 itype);
        
        void setVertexPoolType(u32 vtype);
        
        void setVertexType(VFTYPE type,s32 _channel = 0);
        
        void setSeqMode(s32 _mode);    //数据排列模式
        
        void setDrawMethod(DRAWMETHOD drawtype);
        
        virtual void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        virtual void setVertexData(SVDataSwapPtr _data,s32 _channel = 0,VFTYPE type = E_VF_BASE);
        
        virtual void setVertNum(s32 _vertexNum);
        
        void setInstanceOffsetData(SVDataSwapPtr _pdata, u32 _instanceCount);
        
        void createMesh();
        
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

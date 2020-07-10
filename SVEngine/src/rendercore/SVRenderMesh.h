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
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"

namespace sv {

    //定点说一句
    struct dataTag {
        void* m_pdata;      //数据指针
        s32 m_size;         //数据大小
        s32 m_vertdsp;      //顶点描述
        void* m_pdatad_up;  //更新的数据
        s32 m_size_up;      //更新数据大小
        s32 m_order;
    };

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */

    //存描述信息和数据

    class SVRenderMesh : public SVGBaseEx {
    public:
        SVRenderMesh(SVInstPtr _app);
        
        ~SVRenderMesh();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
    
        virtual void render(SVRendererPtr _renderer);
        
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
        //索引数据
        dataTag m_index;
        //顶点数据
        SVArray<dataTag> m_vertPool;
        //更新数据
        dataTag m_vert_up;
       
    public:
        void bindRes(SVRBufferPtr _res);
        
        void unbindRes();
        
        SVRBufferPtr getResBuffer();
        
    protected:
        SVRBufferPtr m_res_buffer;      //最主要的是他
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H

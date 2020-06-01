//
// SVRenderMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMESH_H
#define SV_RENDERMESH_H

#include "SVResVBO.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"

namespace sv {

    /*
     逻辑和渲染之间的桥梁，其实就是数据和数据描述
     */

    class SVRenderMesh : public SVRObjBase {
    public:
        enum MESHSTATE{
            MESHDATA_WAIT = 0,
            MESHDATA_READY,
            MESHDATA_CREATE
        };
        
        SVRenderMesh(SVInst* _app);
        
        ~SVRenderMesh();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
    
        virtual void render(SVRendererPtr _renderer);
        
        void setIndexPoolType(u32 itype);
        
        void setVertexPoolType(u32 vtype);
        
        void setVertexType(VFTYPE type);
        
        void setSeqMode(s32 _mode);    //数据排列模式
        
        void setDrawMethod(DRAWMETHOD drawtype);
        
        void setvisible(bool bVis);
        
        virtual void setIndexData(SVDataSwapPtr _data,s32 _num);
        
        virtual void setVertexDataNum(s32 _vertexNum);
        
        virtual void setVertexData(SVDataSwapPtr _data);
        
        void setInstanceOffsetData(SVDataSwapPtr _pdata, u32 _instanceCount);
        
        virtual void getIndexData(SVDataSwapPtr _data,s32 &_num);
        
        virtual void getVertexData(SVDataSwapPtr _data);
        
        virtual void getVertexNum(s32 &_vertexNum);
        
        void createMesh();
        
    protected:
        virtual void _updateData();
        
        bool  m_created;
        
        RENDERMESHCONF m_renderMeshConf;
        
        RENDERMESHDATA m_renderMeshData;
        
        //
        struct dataTag {
            void* m_pdata;  //数据指针s
            s32 m_size;     //数据大小
            s32 m_vertdsp;  //顶点描述
        };
        SVArray<dataTag> dataPool;
        
        //
        void* m_pindex;
        
        SVRMeshPtr m_pRMesh;
    };
    

}//!namespace sv


#endif //SV_RENDERMESH_H

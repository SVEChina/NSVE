//
// SVRenderObject.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDEROBJECT_H
#define SV_RENDEROBJECT_H

#include "SVRenderDef.h"
#include "../mtl/SVMtlDeclare.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../base/SVObject.h"
#include "../base/SVRect.h"
#include "../base/SVBounds.h"

//只是负责正确的生成RenderCmd 并不负责RenderMesh和材质的生命周期管理

namespace sv {
    
//    class SVRenderObjInst{
//    public:
//        static void pushLineCmd(SVRenderScenePtr _rs,
//                                RENDERSTREAMTYPE streamtype,
//                                FVec3 _start,
//                                FVec3 _end,
//                                SVMtlCorePtr _mtl,
//                                cptr8 tag = "null");
//
//        static void pushRectCmd(SVRenderScenePtr _rs,
//                                RENDERSTREAMTYPE streamtype,
//                                SVRect& _rect,
//                                SVMtlCorePtr _mtl,
//                                cptr8 tag = "null");
//
//        static void pushAABBCmd(SVRenderScenePtr _rs,
//                                RENDERSTREAMTYPE streamtype,
//                                SVBoundBox& _aabb,
//                                SVMtlCorePtr _mtl,
//                                cptr8 tag = "null");
//    };
    
    //
    class SVRenderObject : public SVObject {
    public:
        SVRenderObject();
        
        ~SVRenderObject();
        
//        virtual void pushCmd(SVRenderScenePtr _rs,
//                             RENDERSTREAMTYPE streamtype,
//                             cptr8 tag = "null");
        
        void setMesh(SVRenderMeshPtr _mesh);
        
        void setMtl(SVMtlCorePtr _mtl,bool _copy = true);
        
        SVRenderMeshPtr getMesh(){ return m_pMesh; };
        
        SVMtlCorePtr getMtl(){ return m_pMtl; }
        
    protected:
        SVRenderMeshPtr m_pMesh;
        
        SVMtlCorePtr m_pMtl;
    };
        

}//!namespace sv





#endif //SV_RENDEROBJECT_H

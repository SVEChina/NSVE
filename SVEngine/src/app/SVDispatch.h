//
// SVInst.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DISPATCH_H
#define SV_DISPATCH_H

#include "../base/SVObject.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../rendercore/SVRenderDeclare.h"
//#include "SVGlobalMgr.h"
//#include "SVGlobalParam.h"

namespace sv {
    
    /*
     分发 投递器
     */

    class SVDispatch : public SVObject {
    public:
        //投递shader create
        static void dispatchShaderCreate(SVInstPtr _app,SVShaderPtr _shader);
        
        //投递mesh create
        static void dispatchMeshCreate(SVInstPtr _app,SVRenderMeshPtr _mesh);
        
        //投递texture create
        static void dispatchTextureCreate(SVInstPtr _app,SVTexturePtr _tex);
        
        //投递target
        static void dispatchTargetCreate(SVInstPtr _app,SVRTargetPtr _target);
        
        //target 大小重置
        static void dispatchTargetResize(SVInstPtr _app,SVRTargetPtr _target);
        
        //投递rendermesh
        static void dispatchMeshDraw(SVInstPtr _app,SVRenderMeshPtr _mesh,s32 _mtlID);
        
        //投递rendermesh
        static void dispatchMeshDraw(SVInstPtr _app,SVRenderMeshPtr _mesh,cptr8 _mtlname);
        
        //投递rendermesh
        static void dispatchMeshDraw(SVInstPtr _app,SVRenderMeshPtr _mesh,s32 _mtlID,SVRTargetPtr _target);
        
    };
    
}//!namespace sv



#endif //SV_DISPATCH_H

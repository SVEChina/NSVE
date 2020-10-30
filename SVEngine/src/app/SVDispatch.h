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
        
       /*
        投递PreZMesh
        */
        static void dispatchMeshPreZ(SVInstPtr _app,
                                     SVRenderMeshPtr _mesh,
                                     SVSurfacePtr _surface);
        
        /*普通mesh绘制*/
        static void dispatchMeshDraw(SVInstPtr _app,
                                     SVRenderMeshPtr _mesh,
                                     SVMtlCorePtr _mtl,
                                     SVSurfacePtr _surface,
                                     SV_RSTREAM _stype,
                                     SVString _tag = "SVDrawMesh");
        
        //投递rendermesh-pre
        static void dispatchMeshDrawPre(SVInstPtr _app,
                                        SVRenderMeshPtr _mesh,
                                        SVMtlCorePtr _mtl,
                                        SVSurfacePtr _surface,
                                        SVString _tag = "SVDrawMeshPre");
        
        //投递rendermesh-after
        static void dispatchMeshDrawAfter(SVInstPtr _app,
                                          SVRenderMeshPtr _mesh,
                                          SVMtlCorePtr _mtl,
                                          SVSurfacePtr _surface,
                                          SVString _tag = "SVDrawMeshAfter");
        
        //投递rendermesh
        static void dispatchMeshDraw(SVInstPtr _app,
                                     SVRenderMeshPtr _mesh,
                                     SVMtlCorePtr _mtl,
                                     SVSurfacePtr _surface,
                                     SVRTargetPtr _target,
                                     SV_RSTREAM _stype,
                                     SVString _tag = "SVDrawMesh");
        
        //投递rendermesh-pre
        static void dispatchMeshDrawPre(SVInstPtr _app,
                                        SVRenderMeshPtr _mesh,
                                        SVMtlCorePtr _mtl,
                                        SVSurfacePtr _surface,
                                        SVRTargetPtr _target,
                                        SVString _tag = "SVDrawMeshPre");
        
        //投递rendermesh-after
        static void dispatchMeshDrawAfter(SVInstPtr _app,
                                          SVRenderMeshPtr _mesh,
                                          SVMtlCorePtr _mtl,
                                          SVSurfacePtr _surface,
                                          SVRTargetPtr _target,
                                          SVString _tag = "SVDrawMeshAfter");
    };
    
}//!namespace sv



#endif //SV_DISPATCH_H

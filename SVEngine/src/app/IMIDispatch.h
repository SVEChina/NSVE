//
// IMIInst.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DISPATCH_H
#define IMI_DISPATCH_H

#include "../base/IMIObject.h"
#include "../base/IMIPreDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../rendercore/IMIRenderDeclare.h"
//#include "IMIGlobalMgr.h"
//#include "IMIGlobalParam.h"

namespace imi {
    
    /*
     分发 投递器
     */

    class IMIDispatch : public IMIObject {
    public:
        //投递shader create
        static void dispatchShaderCreate(IMIInstPtr _app,IMIShaderPtr _shader);
        
        //投递mesh create
        static void dispatchMeshCreate(IMIInstPtr _app,IMIRenderMeshPtr _mesh);
        
        //投递texture create
        static void dispatchTextureCreate(IMIInstPtr _app,IMITexturePtr _tex);
        
        //投递target
        static void dispatchTargetCreate(IMIInstPtr _app,IMIRTargetPtr _target);
        
        //target 大小重置
        static void dispatchTargetResize(IMIInstPtr _app,IMIRTargetPtr _target);
        
       /*
        投递PreZMesh
        */
        static void dispatchMeshPreZ(IMIInstPtr _app,
                                     IMIRenderMeshPtr _mesh,
                                     IMISurfacePtr _surface);
        
        /*普通mesh绘制*/
        static void dispatchMeshDraw(IMIInstPtr _app,
                                     IMIRenderMeshPtr _mesh,
                                     IMIMtlCorePtr _mtl,
                                     IMISurfacePtr _surface,
                                     IMI_RSTREAM _stype,
                                     IMIString _tag = "IMIDrawMesh");
        
        //投递rendermesh-pre
        static void dispatchMeshDrawPre(IMIInstPtr _app,
                                        IMIRenderMeshPtr _mesh,
                                        IMIMtlCorePtr _mtl,
                                        IMISurfacePtr _surface,
                                        IMIString _tag = "IMIDrawMeshPre");
        
        //投递rendermesh-after
        static void dispatchMeshDrawAfter(IMIInstPtr _app,
                                          IMIRenderMeshPtr _mesh,
                                          IMIMtlCorePtr _mtl,
                                          IMISurfacePtr _surface,
                                          IMIString _tag = "IMIDrawMeshAfter");
        
        //投递rendermesh
        static void dispatchMeshDraw(IMIInstPtr _app,
                                     IMIRenderMeshPtr _mesh,
                                     IMIMtlCorePtr _mtl,
                                     IMISurfacePtr _surface,
                                     IMIRTargetPtr _target,
                                     IMI_RSTREAM _stype,
                                     IMIString _tag = "IMIDrawMesh");
        
        //投递rendermesh-pre
        static void dispatchMeshDrawPre(IMIInstPtr _app,
                                        IMIRenderMeshPtr _mesh,
                                        IMIMtlCorePtr _mtl,
                                        IMISurfacePtr _surface,
                                        IMIRTargetPtr _target,
                                        IMIString _tag = "IMIDrawMeshPre");
        
        //投递rendermesh-after
        static void dispatchMeshDrawAfter(IMIInstPtr _app,
                                          IMIRenderMeshPtr _mesh,
                                          IMIMtlCorePtr _mtl,
                                          IMISurfacePtr _surface,
                                          IMIRTargetPtr _target,
                                          IMIString _tag = "IMIDrawMeshAfter");
    };
    
}//!namespace imi



#endif //IMI_DISPATCH_H

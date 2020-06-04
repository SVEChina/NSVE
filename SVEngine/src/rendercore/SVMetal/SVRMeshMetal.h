//
// SVRMeshMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_METAL_H
#define SV_RMESH_METAL_H

#include "../SVRMesh.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render mesh metal
     */

    class SVRMeshMetal : public SVRMesh {
    public:
        SVRMeshMetal(SVInstPtr _app);
        
        ~SVRMeshMetal();
        
        void create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh);
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh);
        
        void destroy(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        id<MTLBuffer> m_buf;
        
        s32 m_indexID;
    };
    

}//!namespace sv


#endif //SV_RMESH_METAL_H

//
// SVRMeshMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_METAL_H
#define SV_RMESH_METAL_H

#include "../SVRenderMesh.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"

namespace sv {

    /*
     render mesh metal
     */

    class SVRMeshMetal : public SVRenderMesh {
    public:
        SVRMeshMetal(SVInstPtr _app);
        
        ~SVRMeshMetal();
        
        void render(SVRendererPtr _renderer);
        
    };
    

}//!namespace sv


#endif //SV_RMESH_METAL_H

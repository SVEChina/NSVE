//
// SVRMeshGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_GL_H
#define SV_RMESH_GL_H

#include "../SVRMesh.h"
#include "../SVRenderMesh.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"

namespace sv {

    /*
     render mesh gl
     */

    class SVRMeshGL : public SVRMesh {
    public:
        SVRMeshGL(SVInstPtr _app);
        
        ~SVRMeshGL();
        
        void create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh);
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh);
        
        void destroy(SVRendererPtr _renderer,SVRTargetPtr _target);
        
    };
    

}//!namespace sv


#endif //SV_RMESH_GL_H

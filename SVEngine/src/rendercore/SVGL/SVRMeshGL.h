//
// SVRMeshGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_GL_H
#define SV_RMESH_GL_H

#include "../SVRenderMesh.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"

namespace sv {

    /*
     render mesh gl
     */

    class SVRMeshGL : public SVRenderMesh {
    public:
        SVRMeshGL(SVInstPtr _app);
        
        ~SVRMeshGL();
        
        void render(SVRendererPtr _renderer);
        
    };
    

}//!namespace sv


#endif //SV_RMESH_GL_H

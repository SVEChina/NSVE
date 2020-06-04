//
// SVRMesh.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_H
#define SV_RMESH_H

#include "../base/SVGBase.h"
#include "SVRenderMesh.h"
//#include "SVRenderDef.h"
//#include "../mtl/SVShaderMgr.h"
//#include "../base/SVPreDeclare.h"

namespace sv {

    /*
     render mesh
     */

    class SVRMesh : public SVGBaseEx {
    public:
        SVRMesh(SVInstPtr _app);
        
        ~SVRMesh();
        
        virtual void create(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh){}
        
        virtual void render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh){}
        
        virtual void destroy(SVRendererPtr _renderer,SVRTargetPtr _target){}
        
        bool m_create;
        
        bool m_destroy;
        
    };
    

}//!namespace sv


#endif //SV_RMESH_GL_H

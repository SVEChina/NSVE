//
// SVMesh2DNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_NODE_MESH2D_H
#define SV_NODE_MESH2D_H

#include "SVNode.h"
namespace sv {
    
    /*
     2D-mesh节点
    */

    class SVMesh2DNode : public SVNode {
    public:
        SVMesh2DNode(SVInstPtr _app);
        
        ~SVMesh2DNode();

        void update(f32 _dt);

        void render();
        
        void setMesh(SVRenderMeshPtr _mesh);
        
    protected:
        SVRenderMeshPtr m_pMesh;
    };

}//!namespace sv

#endif //SV_NODE_MESH2D_H

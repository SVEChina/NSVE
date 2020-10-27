//
// SVFacePointNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#ifndef SV_FACEPOINTNODE_H
#define SV_FACEPOINTNODE_H

#include "SVNode.h"
#define MAX_FACEPOINTS_NUM 800
namespace sv {
    class SVFacePointNode : public SVNode {
        public :
        SVFacePointNode(SVInstPtr _app);
    
        ~SVFacePointNode();
    
        void update(f32 _dt);
    
        void render();
    protected:
        SVRenderMeshPtr m_pMesh;
        SVMtlCorePtr m_pMtl;
    };
}

#endif /* SV_FACEPOINTNODE_H */

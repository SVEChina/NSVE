//
// IMIFacePointNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#ifndef IMI_FACEPOINTNODE_H
#define IMI_FACEPOINTNODE_H

#include "IMINode.h"
#define MAX_FACEPOINTS_NUM 800
namespace imi {
    class IMIFacePointNode : public IMINode {
        public :
        IMIFacePointNode(IMIInstPtr _app);
    
        ~IMIFacePointNode();
    
        void update(f32 _dt);
    
        void render();
    protected:
        IMIRenderMeshPtr m_pMesh;
        IMIMtlCorePtr m_pMtl;
    };
}

#endif /* IMI_FACEPOINTNODE_H */

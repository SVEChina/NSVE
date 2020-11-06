//
// IMIFaceShapeNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FACESHAPENODE_H
#define IMI_FACESHAPENODE_H

#include "IMINode.h"

namespace imi {
    
    class IMIFaceShapeNode : public IMINode {
    public :
        IMIFaceShapeNode(IMIInstPtr _app);
        
        ~IMIFaceShapeNode();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        void render();
        
        bool procEvent(IMIEventPtr _event);
        
        void addPass(IMIPassPtr _pass);
        
        void clearPass();
        
    protected:
        IMIRenderMeshPtr m_pMesh;
        IMIMtlFaceShapePtr m_pMtl;

        typedef IMIArray<IMIPassPtr> PASSPOOL;
        PASSPOOL m_passPool;
    };

}//!namespace imi

#endif /* IMI_FACESHAPENODE_H */

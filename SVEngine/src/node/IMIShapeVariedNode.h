//
// IMIShapeVariedNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SHAPEVARIEDNODE_H
#define IMI_SHAPEVARIEDNODE_H

#include "IMINode.h"

namespace imi {

    // face shape douyin
    
    class IMIShapeVariedNode : public IMINode {
    public:
        IMIShapeVariedNode(IMIInstPtr _app);
        
        virtual ~IMIShapeVariedNode();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        void render();
        
        void addPass(IMIPassPtr _pass);
        
        void clearPass();
        
    protected:
        IMIRenderMeshPtr m_pMesh;
        IMIMtlFaceShapeVariedPtr m_pMtl;

        typedef IMIArray<IMIPassPtr> PASSPOOL;
        PASSPOOL m_passPool;
        //IMIRenderTexturePtr m_fbo;
    };
        
    
    
}//!namespace imi

#endif /* IMI_SHAPEVARIEDNODE_H */

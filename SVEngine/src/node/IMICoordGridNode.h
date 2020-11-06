//
// IMICoordGridNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_COORD_GRID_NODE_H
#define IMI_COORD_GRID_NODE_H

#include "IMINode.h"

namespace imi {
    
    //笛卡尔坐标系
    
    class IMICoordGridNode : public IMINode {
    public :
        IMICoordGridNode(IMIInstPtr _app);
        
        ~IMICoordGridNode();
        
        void update(f32 dt);
        
        void render();
        
        f32 getUnit();
        
    protected:
        void _refreshUnit();
        
        f32 m_unit;
        IMIRenderMeshPtr m_pMeshX;
        IMIRenderMeshPtr m_pMeshY;
        IMIRenderMeshPtr m_pMeshZ;
        
        IMITexturePtr m_gridTex;
    };

}//!namespace imi



#endif /* IMI_COORD_GRID_NODE_H */

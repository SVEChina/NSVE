//
// SV3DBox.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_3DBOX_H
#define SV_3DBOX_H

#include "SVNode.h"
#include "../base/SVBounds.h"
#include "../base/SVVec3.h"

namespace sv {
    
    class SV3DBox : public SVNode {
    public:
        SV3DBox(SVInstPtr _app);
        
        virtual ~SV3DBox();
        
        virtual void update(f32 dt);
        
        virtual void render();
        
        void setSize(FVec3 _size);
        
        SVMtlCorePtr getMtl();
        
        SVMtlGeo3dPtr m_mtl_box;

        SVRenderMeshPtr m_pMesh;
        
        SVColor m_color;
        
        FVec3& getSize() { return m_size; }
        
    private:
        FVec3 m_size;
    };
    
}//!namespace sv



#endif //SV_3DBOX_H

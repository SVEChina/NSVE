//
// SVCube.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_CUBE_H
#define SV_CUBE_H

#include "SVNode.h"
#include "../base/SVBounds.h"
#include "../base/SVVec3.h"

namespace sv {
    
    class SVCube : public SVNode {
    public:
        SVCube(SVInstPtr _app);
        
        virtual ~SVCube();
        
        virtual void update(f32 dt);
        
        virtual void render();
        
        void setMtl(cptr8 _name);
        
        void setSize(FVec3& _size);
        
        FVec3 getSize() { return m_size; }
        
    private:
        SVRenderMeshPtr m_cube_mesh;
        
        FVec3 m_size;
        
        SVString m_mtl_name;
    };
    
}//!namespace sv



#endif //SV_CUBE_H

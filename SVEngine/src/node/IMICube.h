//
// IMICube.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_CUBE_H
#define IMI_CUBE_H

#include "IMINode.h"
#include "../base/IMIBounds.h"
#include "../base/IMIVec3.h"

namespace imi {
    
    //绘制cube
    class IMICube : public IMINode {
    public:
        IMICube(IMIInstPtr _app);
        
        virtual ~IMICube();
        
        virtual void update(f32 dt);
        
        virtual void render();

        void setSize(FVec3& _size);
        
        FVec3 getSize() { return m_size; }
        
    private:
        IMIRenderMeshPtr m_cube_mesh;
        
        FVec3 m_size;
    };
    
}//!namespace imi



#endif //IMI_CUBE_H

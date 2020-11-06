//
// IMIPhysicsBodyRope.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BODIES_PHYSICSBODYROPE_H
#define IMI_BODIES_PHYSICSBODYROPE_H
#include "IMIPhysicsBodySoft.h"
#include "../../base/IMIVec3.h"
namespace imi {
    
    
        
        class IMIPhysicsBodyRope : public IMIPhysicsBodySoft {
        public:
            IMIPhysicsBodyRope(IMIInstPtr _app, btSoftBodyWorldInfo& _worldInfo, FVec3 &_from, FVec3 &_to, s32 _resCount, s32 _fixeds = 1+2);
            
            ~IMIPhysicsBodyRope();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            void *getLineVertexData();
            
            u32   getLineVertexDataSize();
            
            u32   getLineVertexCount();
        private:
            void _updateLineVertexData();
        protected:
            u32 m_vertexCount;
            IMIDataSwapPtr m_pVertexData;

        };
    
}//!namespace imi

#endif //IMI_BODIES_PHYSICSBODYROPE_H

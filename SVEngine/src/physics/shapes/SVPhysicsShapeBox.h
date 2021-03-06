//
// SVPhysicsShapeBox.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PHYSICSSHAPEBOX_H
#define SV_PHYSICSSHAPEBOX_H

#include "SVPhysicsShape.h"
namespace sv {
    
    
        
        class SVPhysicsShapeBox : public SVPhysicsShape {
        public:
            SVPhysicsShapeBox(SVInstPtr _app);
            
            SVPhysicsShapeBox(SVInstPtr _app, FVec3 _size);
            
            ~SVPhysicsShapeBox();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            void setSize(const FVec3& _size);
            
            const FVec3& getSize() const;
        };
            
    
    
}//!namespace sv

#endif //SV_PHYSICSSHAPEBOX_H

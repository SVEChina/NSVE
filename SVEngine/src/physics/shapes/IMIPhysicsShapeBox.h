//
// IMIPhysicsShapeBox.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSSHAPEBOX_H
#define IMI_PHYSICSSHAPEBOX_H

#include "IMIPhysicsShape.h"
namespace imi {
    
    
        
        class IMIPhysicsShapeBox : public IMIPhysicsShape {
        public:
            IMIPhysicsShapeBox(IMIInstPtr _app);
            
            IMIPhysicsShapeBox(IMIInstPtr _app, FVec3 _size);
            
            ~IMIPhysicsShapeBox();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            void setSize(const FVec3& _size);
            
            const FVec3& getSize() const;
        };
            
    
    
}//!namespace imi

#endif //IMI_PHYSICSSHAPEBOX_H

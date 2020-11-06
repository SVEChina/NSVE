//
// IMIPhysicsShapeSphere.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSSHAPESPHERE_H
#define IMI_PHYSICSSHAPESPHERE_H

#include "IMIPhysicsShape.h"
namespace imi {
    
    
        
        class IMIPhysicsShapeSphere : public IMIPhysicsShape {
        public:
            IMIPhysicsShapeSphere(IMIInstPtr _app);
            
            IMIPhysicsShapeSphere(IMIInstPtr _app, f32 _radius);
            
            ~IMIPhysicsShapeSphere();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
            
            void setRadius(const f32 _radius);
            
            const f32 getRadius() const;
        protected:
            f32 m_radius;
        };
            
    
    
}//!namespace imi

#endif //IMI_PHYSICSSHAPESPHERE_H

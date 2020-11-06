//
// IMIPhysicsCollider.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSCOLLIDER_H
#define IMI_PHYSICSCOLLIDER_H

#include "../../base/IMIGBase.h"
namespace imi {
    
    
        
        class IMIPhysicsCollider : public IMIGBaseEx {
        public:
            IMIPhysicsCollider(IMIInstPtr _app);
            
            ~IMIPhysicsCollider();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
            
            
        };
            
    
    
}//!namespace imi



#endif //IMI_PHYSICSCOLLIDER_H

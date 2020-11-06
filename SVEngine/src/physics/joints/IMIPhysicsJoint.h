//
// IMIPhysicsJoint.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSJOINT_H
#define IMI_PHYSICSJOINT_H

#include "../../base/IMIGBase.h"
namespace imi {
    
    
        
        class IMIPhysicsJoint : public IMIGBaseEx {
        public:
            IMIPhysicsJoint(IMIInstPtr _app);
            
            ~IMIPhysicsJoint();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
        };
            
    
    
}//!namespace imi



#endif //IMI_PHYSICSJOINT_H

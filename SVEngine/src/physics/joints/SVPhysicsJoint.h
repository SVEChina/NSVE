//
// SVPhysicsJoint.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PHYSICSJOINT_H
#define SV_PHYSICSJOINT_H

#include "../../base/SVGBase.h"
namespace sv {
    
    
        
        class SVPhysicsJoint : public SVGBaseEx {
        public:
            SVPhysicsJoint(SVInstPtr _app);
            
            ~SVPhysicsJoint();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
        };
            
    
    
}//!namespace sv



#endif //SV_PHYSICSJOINT_H

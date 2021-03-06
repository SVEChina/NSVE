//
// SVPhysicsCollider.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PHYSICSCOLLIDER_H
#define SV_PHYSICSCOLLIDER_H

#include "../../base/SVGBase.h"
namespace sv {
    
    
        
        class SVPhysicsCollider : public SVGBaseEx {
        public:
            SVPhysicsCollider(SVInstPtr _app);
            
            ~SVPhysicsCollider();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
            
            
        };
            
    
    
}//!namespace sv



#endif //SV_PHYSICSCOLLIDER_H

//
// IMIPhysicsWorldBase.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICS_WORLDBASE_H
#define IMI_PHYSICS_WORLDBASE_H

#include "../base/IMIGBase.h"
#include "../work/IMITdCore.h"
#include "../base/IMIVec3.h"
#include "btBulletDynamicsCommon.h"
#define PHYSICSWORLDSTEP 1.0f/30.0f
namespace imi {
    
    
        enum IMI_PHYSICSWORLDTYPE {
            E_PHYSICS_WORLD_BASE = 0,
            E_PHYSICS_WORLD_RIGID,
            E_PHYSICS_WORLD_SOFT_RIGID
        };
        class IMIPhysicsWorldBase : public IMIGBaseEx {
        public:
            IMIPhysicsWorldBase(IMIInstPtr _app);
            
            ~IMIPhysicsWorldBase();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            const IMI_PHYSICSWORLDTYPE getType() const;
            
            virtual void setGravity(const FVec3 &_gravity);
            
            const FVec3& getGravity() const;
            
        protected:
            IMI_PHYSICSWORLDTYPE m_type;
            FVec3 m_gravity;
            IMILockPtr m_lock;
        };
            
    
    
}//!namespace imi

#endif //IMI_PHYSICS_WORLDBASE_H

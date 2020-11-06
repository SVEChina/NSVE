//
// IMIPhysicsShape.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSSHAPE_H
#define IMI_PHYSICSSHAPE_H

#include "../../base/IMIGBase.h"
#include "../../base/IMIVec3.h"
#include "BulletCollision/CollisionShapes/btCollisionShape.h"
namespace imi {
    
    
        enum PHYSICSSHAPETYPE{
            E_PHYSICS_SHAPE_BASE = 0,
            E_PHYSICS_SHAPE_BOX,
            E_PHYSICS_SHAPE_SPHERE
        };
        class IMIPhysicsShape : public IMIGBaseEx {
        public:
            IMIPhysicsShape(IMIInstPtr _app);
            
            ~IMIPhysicsShape();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            btCollisionShape* getShape();
            
            PHYSICSSHAPETYPE getType() const;
            
            inline void setMass(f32 _mass){
                m_mass = _mass;
            }
            
            inline f32 getMass(){
                return m_mass;
            }
            
            inline void setLocalInertia(FVec3 _m_localInertia){
                m_localInertia = _m_localInertia;
            }
            
            inline FVec3 getLocalInertia(){
                return m_localInertia;
            }
            
        protected:
            PHYSICSSHAPETYPE m_type;
            FVec3 m_size;
            f32 m_mass;
            FVec3 m_localInertia;
            btCollisionShape* m_pColShape;
            
        };
            
    
    
}//!namespace imi



#endif //IMI_PHYSICSSHAPE_H

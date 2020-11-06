//
// IMIPhysicsSoftRigidWorld.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICS_SOFTRIGIDWORLD_H
#define IMI_PHYSICS_SOFTRIGIDWORLD_H

#include "IMIPhysicsWorldBase.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
namespace imi {
    
    
        
        class IMIPhysicsSoftRigidWorld : public IMIPhysicsWorldBase {
        public:
            IMIPhysicsSoftRigidWorld(IMIInstPtr _app);
            
            ~IMIPhysicsSoftRigidWorld();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            virtual void setGravity(const FVec3 &_gravity);
            
            const FVec3& getGravity() const;
            
            btSoftBodyWorldInfo& getWorldInfo();
            
            void addSoftBody(IMIPhysicsBodySoftPtr _body);
            
            bool removeSoftBody(IMIPhysicsBodySoftPtr _body);
            
            bool removeAllSoftBodies();
        protected:
            bool _hasSoftBody(IMIPhysicsBodySoftPtr _body);
        private:
            btBroadphaseInterface       *m_broadPhase;
            btCollisionConfiguration    *m_collisionConfiguration;
            btCollisionDispatcher       *m_collisionDispatcher;
            btConstraintSolver          *m_solver;
            btSoftRigidDynamicsWorld    *m_softWorld;
            typedef IMIArray<IMIPhysicsBodySoftPtr> SOFTBODYPOOL;
            SOFTBODYPOOL m_bodies;
        };
            
    
    
}//!namespace imi



#endif //IMI_PHYSICS_SOFTRIGIDWORLD_H

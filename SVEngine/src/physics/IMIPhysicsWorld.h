//
// IMIPhysicsWorld.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSWORLD_H
#define IMI_PHYSICSWORLD_H

#include "IMIPhysicsWorldBase.h"

namespace imi {
    
    
        
        class IMIPhysicsWorld : public IMIPhysicsWorldBase {
        public:
            IMIPhysicsWorld(IMIInstPtr _app);
            
            ~IMIPhysicsWorld();
            
            virtual void init();
            
            virtual void destroy();
            
            virtual void update(f32 _dt);
            
            void addBody(IMIPhysicsBodyRigidPtr _body);
            
            void removeBody(IMIPhysicsBodyRigidPtr _body);
            
            void addShape(IMIPhysicsShapePtr _shape, IMIPhysicsBodyPtr _body);
            
            void addJoint(IMIPhysicsJointPtr _joint);
            
            void addConstraint(btPoint2PointConstraint* _con);
            
            void removeConstraint(btPoint2PointConstraint* _con);
            
            void setp();
            
            inline void setFps(f32 _timeStep){
                m_timeStep = _timeStep;
            }
            
            
        public :
            btDefaultCollisionConfiguration* m_pCollisionConfiguration;
            btCollisionDispatcher* m_pDispatcher;
            btBroadphaseInterface* m_pOverlappingPairCache;
            btSequentialImpulseConstraintSolver* m_pSolver;
            btDiscreteDynamicsWorld* m_pDynamicsWorld;
        protected:
            f32 m_timeStep;
            IMIArray<IMIPhysicsBodyRigidPtr> m_bodyArray;
           // BODYARRAY m_bodyArray;
            
        };
            
}//!namespace imi



#endif //IMI_PHYSICSWORLD_H

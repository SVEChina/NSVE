//
// IMIPhysicsWorldMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BASESYS_PHYSICSWORLDMGR_H
#define IMI_BASESYS_PHYSICSWORLDMGR_H

#include "../basesys/IMISysBase.h"
namespace imi{


        class IMIPhysicsWorldMgr : public IMISysBase {
        public:
            IMIPhysicsWorldMgr(IMIInstPtr _app);
            
            ~IMIPhysicsWorldMgr();
            
            void init();
            
            void destroy();
            
            void update(f32 _dt);
            
            void setRigidWorld(IMIPhysicsWorldPtr _world);
            
            void setSoftWorld(IMIPhysicsSoftRigidWorldPtr _world);
            
            IMIPhysicsWorldPtr getRigidWorld();
            
            IMIPhysicsSoftRigidWorldPtr getSoftWorld();
        protected:
            IMIPhysicsWorldPtr m_rigidWorld;
            IMIPhysicsSoftRigidWorldPtr m_softWorld;
        };


}//!namespace imi
#endif //IMI_BASESYS_PHYSICSWORLDMGR_H

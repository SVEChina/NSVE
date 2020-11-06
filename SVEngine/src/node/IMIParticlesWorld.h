#ifndef IMI_PARTICLE_WORLD_H
#define IMI_PARTICLE_WORLD_H

#include "IMINode.h"
#include "../base/IMIBounds.h"
#include "../base/IMIVec3.h"
#include "../core/IMIParticles.h"

namespace imi {
    
    
    
        //
        class IMIParticlesWorld : public IMIParticlesWorldBase {
        public:
            IMIParticlesWorld(IMIInstPtr _app);
            
            virtual ~IMIParticlesWorld();
            
            virtual void setEmitterEnabled(s32 enable);

            virtual s32 getFields(IMIArray<WorldField> &fields);
    
            virtual s32 getForces(IMIArray<WorldForce> &forces);
    
            virtual s32 getNoises(IMIArray<WorldNoise> &noises);

            virtual s32 getIntersection(const FVec3 &p0,const FVec3 &p1,WorldContact &contact);

            virtual s32 getCollision(const FVec3 &point,const FVec3 &velocity,f32 radius,IMIArray<WorldContact> &contacts,f32 ifps);

            virtual s32 getRandomPoint(FVec3 &ret_point,FVec3 &ret_normal,FVec3 &ret_velocity);
            
        private:
            IMIParticlesNodePtr m_particleNode;
        };
        
    
    
}//!namespace imi

#endif /* IMI_PARTICLE_WORLD_H */

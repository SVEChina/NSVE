//
// IMIPhysicsBodySoft.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICS_BODYSOFT_H
#define IMI_PHYSICS_BODYSOFT_H


#include "IMIPhysicsBody.h"
#include "BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"
#include "BulletSoftBody/btSoftBodyHelpers.h"
#include "BulletSoftBody/btSoftBody.h"
namespace imi {
    
        
        typedef IMIArray<btSoftBody::Cluster*> IMISoftBodyClusterArray;
        typedef IMIArray<btSoftBody::Note> IMISoftBodyNoteArray;//Note!!
        typedef IMIArray<btSoftBody::Node> IMISoftBodyNodeArray;//Node!!
        typedef IMIArray<btSoftBody::Link> IMISoftBodyLinkArray;
        typedef IMIArray<btSoftBody::Face> IMISoftBodyFaceArray;
        typedef IMIArray<btSoftBody::Tetra> IMISoftBodyTetraArray;
        typedef IMIArray<btSoftBody::Anchor> IMISoftBodyAnchorArray;
        typedef IMIArray<btSoftBody::RContact> IMISoftBodyRContactArray;
        typedef IMIArray<btSoftBody::Material*> IMISoftBodyMaterialArray;
        typedef IMIArray<btSoftBody::Joint*> IMISoftBodyJointArray;
        typedef IMIArray<btSoftBody*> IMISoftBodyArray;
        
        class IMIPhysicsBodySoft : public IMIPhysicsBody {
        public:
            IMIPhysicsBodySoft(IMIInstPtr _app);

            ~IMIPhysicsBodySoft();

            virtual void init();

            virtual void destroy();

            virtual void update(f32 _dt);
            
            btSoftBody* getBody();
            
            void setTotalMass(f32 _mass);
            
            void setMass(s32 _bulletnode, f32 _mass);
            
            void setTimeScale(f32 _timescale);
            
            void getNodes(IMISoftBodyNodeArray &_nodearray);
            
            s32 getNodesSize();
            
            void getLinks(IMISoftBodyLinkArray &_linkarray);
            
            s32 getLinksSize();
            
            void getFaces(IMISoftBodyFaceArray &_facearray);
            
            s32 getFacesSize();
            
            void appendAnchor(s32 _node,
                              IMIPhysicsBodyRigidPtr _body, bool _disableCollisionBetweenLinkedBodies = false, f32 _influence = 1);
        protected:
            btSoftBody* m_softBody;
            
        };

    

}//!namespace imi
#endif //IMI_PHYSICS_BODYSOFT_H

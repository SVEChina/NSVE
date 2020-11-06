//
// IMIPhysicsBody.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PHYSICSBODY_H
#define IMI_PHYSICSBODY_H

#include "../../base/IMIGBase.h"
#include "../../node/IMINodeDef.h"

namespace imi {

    
        enum PHYSICSBODYTYPE {
            E_PHYSICS_BODY_BASE = 0,
            E_PHYSICS_BODY_RIGID,
            E_PHYSICS_BODY_SOFT,
            E_PHYSICS_BODY_ROPE,
            E_PHYSICS_BODY_CLOTH
        };
       
        class IMIPhysicsBody : public IMIGBaseEx {
        public:
            IMIPhysicsBody(IMIInstPtr _app);

            ~IMIPhysicsBody();

            virtual void init();

            virtual void destroy();

            virtual void update(f32 _dt);
            
            PHYSICSBODYTYPE getType() const;

            void setNode(IMINodePtr _node);
            
            IMINodePtr getNode();
        protected:
            PHYSICSBODYTYPE m_type;
            
            IMINodePtr m_pNode;
        };

    

}//!namespace imi



#endif //IMI_PHYSICSBODY_H

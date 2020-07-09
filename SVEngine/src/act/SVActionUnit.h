//
// SVActionUnit.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ACTIONUNIT_H
#define SV_ACTIONUNIT_H

#include "SVAniBase.h"
#include "../node/SVNodeDeclare.h"

namespace sv{
    
    
        enum SVACTIONSTATE{
            SV_ACTION_STATE_WAIT,
            SV_ACTION_STATE_PLAY,
            SV_ACTION_STATE_STOP
        };
        class SVActionUnit : public SVAniBase {
        public:
            SVActionUnit(SVInstPtr _app);
            
            SVActionUnit(SVInstPtr _app, SVActBasePtr _action, SVNodePtr _node);
            
            ~SVActionUnit();
            
            void init();
            
            void destroy();
            
            virtual bool isEnd();
            
            virtual void update(f32 _dt);
            
            void play();
            
            void stop();
            
            SVActBasePtr getAct();
            
            SVNodePtr getNode();
        protected:
            bool m_isEnd;
            SVACTIONSTATE m_state;
            SVActBasePtr m_actPtr;
            SVNodePtr m_nodePtr;
        };
        
    
}//!namespace sv





#endif //SV_ACTIONUNIT_H

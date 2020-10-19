//
// SVAniMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ANI_MGR_H
#define SV_ANI_MGR_H

#include "../basesys/SVSysBase.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "ani/SVAniUnit.h"
#include <vector>
#include <map>

namespace sv {

    /*
     动画处理系统
     */

    class SVAniMgr : public SVSysBase {
    public:
        SVAniMgr(SVInstPtr _app);
        
        ~SVAniMgr();
        
        void init();
        
        void destroy();

        void update(f32 _dt);
        
        void addAni(SVNodePtr _node,SVAniUnitPtr _unit);
        
        void removeAni(SVNodePtr _node);
        
        void clearAni();
        
        bool hasAni(SVNodePtr _node);
        
    protected:
        struct ANICELL {
            ANICELL() {
                reset();
            };
            
            void reset() {
                _node = nullptr;
                _unit = nullptr;
            };
            SVNodePtr _node;
            SVAniUnitPtr _unit;
        };
        
        typedef std::vector<ANICELL> ANIPOOLS;
        ANIPOOLS m_ani_pool;
        
        SVLockSpinPtr m_ani_lock;
        
    public:
        //可以提供一些简单的运动的标准API
    };

}//!namespace




#endif //SV_ANI_MGR_H

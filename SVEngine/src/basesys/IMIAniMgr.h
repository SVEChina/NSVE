//
// IMIAniMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ANI_MGR_H
#define IMI_ANI_MGR_H

#include "../basesys/IMISysBase.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "ani/IMIAniUnit.h"
#include <vector>
#include <map>

namespace imi {

    /*
     动画处理系统
     */

    class IMIAniMgr : public IMISysBase {
    public:
        IMIAniMgr(IMIInstPtr _app);
        
        ~IMIAniMgr();
        
        void init();
        
        void destroy();

        void update(f32 _dt);
        
        void addAni(IMINodePtr _node,IMIAniUnitPtr _unit);
        
        void removeAni(IMINodePtr _node);
        
        void clearAni();
        
        bool hasAni(IMINodePtr _node);
        
    protected:
        struct ANICELL {
            ANICELL() {
                reset();
            };
            
            void reset() {
                _node = nullptr;
                _unit = nullptr;
            };
            IMINodePtr _node;
            IMIAniUnitPtr _unit;
        };
        
        typedef std::vector<ANICELL> ANIPOOLS;
        ANIPOOLS m_ani_pool;
        
        IMILockSpinPtr m_ani_lock;
        
    public:
        //可以提供一些简单的运动的标准API
    };

}//!namespace




#endif //IMI_ANI_MGR_H

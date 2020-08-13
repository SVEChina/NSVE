//
// SVARBackgroundMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ARBACKGROUND_MGR_H
#define SV_ARBACKGROUND_MGR_H

#include "../basesys/SVSysBase.h"
#include "../rendercore/SVRenderDeclare.h"

namespace sv {

    /*
        AR背景系统，包含相片渲染和相机图片处理
     */

    class SVARBackgroundMgr : public SVSysBase {
    public:
        SVARBackgroundMgr(SVInstPtr _app);
        
        ~SVARBackgroundMgr();
        
        void init();
        
        void destroy();

        void update(f32 dt);
        
        void enable();
        
        void disable();
        
        SVRTargetPtr getTarget() { return m_ar_target; }
        
        bool isEnable() { return m_enable; }
        
    protected:
        SVRTargetPtr m_ar_target;
        
        bool m_enable;
    };

}//!namespace




#endif //SV_ARBACKGROUND_MGR_H

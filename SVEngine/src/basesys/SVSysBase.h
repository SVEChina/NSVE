//
// SVSysBase.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SYSBASE_H
#define SV_SYSBASE_H

#include "../event/SVEventProc.h"
#include "../node/SVNodeDeclare.h"

namespace sv {
    
    class SVSysBase : public SVEventProc {
    public:
        SVSysBase(SVInstPtr _app);
        
        ~SVSysBase();
        
        virtual void renderCache() {}
        
    protected:
        s32 m_subsysType;
    };
    
}//!namespace sv


#endif //SV_SYSBASE_H

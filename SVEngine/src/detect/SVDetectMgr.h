//
// SVDetectMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DETECTMGR_H
#define SV_DETECTMGR_H

#include "../basesys/SVSysBase.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVDatatDef.h"
#include "SVPersonModule.h"

namespace sv {
    
    class SVDetectMgr : public SVSysBase {
    public:
        SVDetectMgr(SVInstPtr _app);
        
        ~SVDetectMgr();
        
        void init(DETECTTYPE type);
        
        void destroy();
        
        void update(f32 _dt);
        
        SVDetectBasePtr getDetect();
        
        SVPersonModulePtr getPersonModule();
        
    protected:
        
        DETECTTYPE m_detectType;
        
        SVDetectBasePtr m_pDetectBase;
        
        SVPersonModulePtr m_pernson_sys;
    
    };

}//!namespace sv





#endif //SV_DETECTMGR_H

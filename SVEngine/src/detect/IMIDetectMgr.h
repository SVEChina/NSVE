//
// IMIDetectMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_DETECTMGR_H
#define IMI_DETECTMGR_H

#include "../basesys/IMISysBase.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIDatatDef.h"
#include "IMIPersonModule.h"

namespace imi {
    
    class IMIDetectMgr : public IMISysBase {
    public:
        IMIDetectMgr(IMIInstPtr _app);
        
        ~IMIDetectMgr();
        
        void init(DETECTTYPE type);
        
        void destroy();
        
        void update(f32 _dt);
        
        IMIDetectBasePtr getDetect();
        
        IMIPersonModulePtr getPersonModule();
        
    protected:
        
        DETECTTYPE m_detectType;
        
        IMIDetectBasePtr m_pDetectBase;
        
        IMIPersonModulePtr m_pernson_sys;
    
    };

}//!namespace imi





#endif //IMI_DETECTMGR_H

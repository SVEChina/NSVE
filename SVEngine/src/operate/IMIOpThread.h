//
// IMIOpThread.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATETHREAD_H
#define IMI_OPERATETHREAD_H

#include "IMIOpBase.h"
#include "../base/IMIDatatDef.h"

namespace imi {
    
    class IMIOpAppMode : public IMIOpBase {
    public:
        IMIOpAppMode(IMIInstPtr _app,IMI_STATE _mode);
        
        ~IMIOpAppMode();
        
    protected:
        void _process(f32 _dt);
        
        IMI_STATE m_EngMode;
    };
    
}//!namespace imi



#endif //IMI_OPERATETHREAD_H

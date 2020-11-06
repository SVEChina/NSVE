//
// IMIBasicSys.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PROCESS_H
#define IMI_PROCESS_H

#include "../event/IMIEventProc.h"
#include "IMILogicDeclare.h"

//一种处理....

namespace imi{
    
    class IMIProcess : public IMIEventProc {
    public:
        IMIProcess(IMIInstPtr _app);
        
        ~IMIProcess();
        
        void update(f32 _dt){}
        
    protected:
        IMIString m_subProcType;
    };
    
}//!namespace imi





#endif //IMI_PROCESS_H

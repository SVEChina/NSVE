//
// IMIRecycleProcess.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RECYCLESYS_H
#define IMI_RECYCLESYS_H

#include "IMIProcess.h"

namespace imi {
    
    //回收系统
    
    class IMIRecycleProcess : public IMIProcess {
    public:
        IMIRecycleProcess(IMIInstPtr _app);
        
        ~IMIRecycleProcess();
        
        //更新
        void update(f32 _dt);
        
        virtual bool procEvent(IMIEventPtr _event);
    };

    
}//!namespace imi



#endif //IMI_RECYCLESYS_H

//
// SVRecycleProcess.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RECYCLESYS_H
#define SV_RECYCLESYS_H

#include "SVProcess.h"

namespace sv {
    
    //回收系统
    
    class SVRecycleProcess : public SVProcess {
    public:
        SVRecycleProcess(SVInstPtr _app);
        
        ~SVRecycleProcess();
        
        //更新
        void update(f32 _dt);
        
        virtual bool procEvent(SVEventPtr _event);
    };

    
}//!namespace sv



#endif //SV_RECYCLESYS_H

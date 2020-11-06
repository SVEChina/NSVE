//
// IMIThread.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MIS_H
#define IMI_MIS_H

//线程基类

#include "../base/IMIObject.h"

namespace imi {

    class IMIMis: public IMIObject {
    public:
        IMIMis();
        
        ~IMIMis();
        
        //执行一次
        void exec(f32 _dt);
    };
    
//!namespace
}



#endif //IMI_MIS_H

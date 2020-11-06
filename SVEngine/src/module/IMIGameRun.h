//
// IMIGameRun.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GAMERUN_H
#define IMI_GAMERUN_H

#include "IMIModuleDef.h"
#include "IMIGamePart.h"

namespace imi{
    class IMIGameRun : public IMIGamePart {
    public:
        IMIGameRun(IMIInstPtr _app);
        
        ~IMIGameRun();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        bool isEnd();
        
    protected:
        
    };
}//!namespace imi





#endif //IMI_GAMEREADY_H

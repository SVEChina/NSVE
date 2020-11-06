//
// IMIGameReady.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GAMEREADY_H
#define IMI_GAMEREADY_H

#include "IMIModuleDef.h"
#include "IMIGamePart.h"

namespace imi{
    class IMIGameReady : public IMIGamePart{
    public:
        IMIGameReady(IMIInstPtr _app);
        
        ~IMIGameReady();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        bool isEnd();
        
    protected:
        
    };
}//!namespace imi





#endif //IMI_GAMEREADY_H

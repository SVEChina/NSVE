//
// IMIGameEnd.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GAMEEND_H
#define IMI_GAMEEND_H

#include "IMIModuleDef.h"
#include "IMIGamePart.h"

namespace imi{
    class IMIGameEnd : public IMIGamePart {
    public:
        IMIGameEnd(IMIInstPtr _app);
        
        ~IMIGameEnd();
        
        void init();
        
        void destroy();
        
        void update(f32 _dt);
        
        bool isEnd();
        
    protected:
        
    };
    
}//!namespace imi





#endif //IMI_GAMEREADY_H

//
// IMIOpDetect.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#ifndef IMI_OPERATEDETECT_H
#define IMI_OPERATEDETECT_H

#include "IMIOpBase.h"
#include "../base/IMIDatatDef.h"

namespace imi {
    
    //
    class IMIOpOpenDetect : public IMIOpBase {
    public:
        IMIOpOpenDetect(IMIInstPtr _app, s32 detecttype);
        
    protected:
        void _process(f32 dt);
        
        DETECTTYPE m_detectType;
    };
    
    class IMIOpCloseDetect : public IMIOpBase {
    public:
        IMIOpCloseDetect(IMIInstPtr _app);
        
    protected:
        void _process(f32 dt);
    };
    
}//!namespace imi



#endif //IMI_OPERATEDETECT_H

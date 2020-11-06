//
// IMIEventProc.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EVENTPROC_H
#define IMI_EVENTPROC_H

#include "../base/IMIGBase.h"
#include "IMIEventDef.h"

//消息处理器

namespace imi {

    class IMIEventProc : public IMIGBaseEx {
    public:
        IMIEventProc(IMIInstPtr _app);
        
        ~IMIEventProc();
        
        virtual void startListen();
        
        virtual void stopListen();
        
        virtual bool procEvent(IMIEventPtr _event);
    };
    
}//!namespace imi


#endif //IMI_EVENTPROC_H

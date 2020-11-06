//
// IMIEventThread.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_THREADEVENT_H
#define IMI_THREADEVENT_H


#include "IMIEvent.h"

namespace imi {
    
    //
    enum THREADSTATE{
        E_THREAD_S_NULL = 0,
        E_THREAD_S_START,
        E_THREAD_S_DESTROY
    };
    
    class IMIThread;
    class IMIEventThread : public IMIEvent {
    public:
        IMIEventThread();
        IMIString m_name;
        THREADSTATE m_tate;
    };
    
}//!namespace imi



#endif //IMI_THREADEVENT_H

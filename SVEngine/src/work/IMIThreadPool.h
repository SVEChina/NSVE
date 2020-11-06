// IMIThreadPool.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_THREADPOOL_H
#define IMI_THREADPOOL_H

#include "IMIWorkDeclare.h"
#include "IMIThread.h"

//线程池之
/*  1.单一任务线程
 *  2.线程组 同时进行 同时等待
 */

namespace imi {
    
    /*
        要做成单例
     */
    
    class IMIThreadPool: public IMIObject {
    public:
        IMIThreadPool();
        
        ~IMIThreadPool();
        
        IMIThreadPtr applyThread();
        
        IMIThreadPtr getThread(s32 && _index);
        
        IMIArray<IMIThreadPtr> m_threadPool;
    };
    
}//!namespace imi



#endif //IMI_THREADPOOL_H

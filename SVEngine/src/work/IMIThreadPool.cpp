// IMIThreadPool.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include <sys/time.h>
#include "IMIThreadPool.h"

using namespace imi;

IMIThreadPool::IMIThreadPool(){
}

IMIThreadPool::~IMIThreadPool(){
    m_threadPool.clear();
}

//申请一个线程
IMIThreadPtr IMIThreadPool::applyThread() {
    for(s32 i=0;i<m_threadPool.size();i++) {
        if( m_threadPool[i]->m_use == false ) {
            m_threadPool[i]->m_use  = true;
            return m_threadPool[i];
        }
    }
    //
    IMIThreadPtr t_thread = MakeSharedPtr<IMIThread>();
    t_thread->m_use = false;
    m_threadPool.append(t_thread);
    //
    return nullptr;
}

//获取线程
IMIThreadPtr IMIThreadPool::getThread(s32 && _index) {
    if( _index<m_threadPool.size() ) {
        return m_threadPool[_index];
    }
    return nullptr;
}


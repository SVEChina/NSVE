// IMIThreadGroup.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIThreadGroup.h"

using namespace imi;

IMIThreadGroup::IMIThreadGroup(){
    pthread_mutex_init(&m_mutex, nullptr);
    m_cond = MakeSharedPtr<IMICond>();
    m_sem =  MakeSharedPtr<IMISem>(0);
    m_count = 0;
}

IMIThreadGroup::~IMIThreadGroup(){
    m_sem = nullptr;
    m_cond = nullptr;
    pthread_mutex_destroy(&m_mutex);
}

void IMIThreadGroup::create(s32 _num) {
    if(threadIDPool.size()>0) {
        return ;
    }
    m_count = _num;
    for(s32 i=0;i<m_count;i++) {
        inThreadPtr t_in_td = MakeSharedPtr<inThread>(THIS_TO_SHAREPTR(IMIThreadGroup));
        threadIDPool.append(t_in_td);
    }
}

void IMIThreadGroup::destroy() {
    threadIDPool.clear();
    m_count = 0;
}

void IMIThreadGroup::setMis(s32 _index,IMIMisPtr _mis) {
    if( _index<threadIDPool.size() ) {
        threadIDPool[_index]->setMis(_mis,false);
    }
}

//线程组执行线程
void IMIThreadGroup::run(bool _sync) {
    if(_sync) {
        //同步模式
        m_count = 0;
        m_cond->broad();   //通知所有子线成跑起来
        m_sem->wait();  //自己阻塞，等待
    }else{
        //异步模式
        m_count = 0;
        m_cond->broad();   //通知所有子线成跑起来
    }
}

void IMIThreadGroup::thread_wait() {
    
}

void IMIThreadGroup::thread_back() {
    //线程回来了
    pthread_mutex_lock(&m_mutex);
    m_count++;
    pthread_mutex_unlock(&m_mutex);
    if( m_count == threadIDPool.size() ) {
        m_sem->post();  //自己继续执行
    }
}

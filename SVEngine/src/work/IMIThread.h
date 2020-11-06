//
// IMIThread.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_THREAD_H
#define IMI_THREAD_H

//线程基类

#include "../base/IMIObject.h"
#include "IMIWorkDeclare.h"
#include "IMITdCore.h"
#include <thread>

namespace imi {

    typedef bool (*thread_cb_init)();
    typedef bool (*thread_cb_do)();
    typedef bool (*thread_cb_destroy)();
    
    /*
     单纯线程
     */

    class IMIThread: public IMIObject {
    public:
        IMIThread();
        
        IMIThread(IMICondPtr _cond);
        
        ~IMIThread();
        
        //(创建)
        bool start(bool _once = true);
        
        //(销毁)
        void stop();
        
        bool notice();
        
        //设置任务
        void setMis(IMIMisPtr _mis,bool _clean = false);
        
    protected:
        void _wait();       //wait阶段
        
        virtual void _update();
        
    public:
        IMI_THREAD_STATE m_svTState;     //IMI线程状态
        IMICondPtr m_cond;       //条件变量
        std::thread *m_pThread; //线程
        IMIMisPtr m_mis;         //任务
        bool m_use;
        bool m_once;
        bool m_run;
        bool m_misclean;
        //
        thread_cb_init m_callback_init;
        thread_cb_do m_callback_do;
        thread_cb_destroy m_callback_destroy;
    };
    

}//!namespace imi



#endif //IMI_MAMGRBASE_H

//
// SVThread.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_THREAD_H
#define SV_THREAD_H

//线程基类

#include "../base/SVObject.h"
#include "SVWorkDeclare.h"
#include "SVTdCore.h"
#include <thread>

namespace sv {

    typedef bool (*thread_cb_init)();
    typedef bool (*thread_cb_do)();
    typedef bool (*thread_cb_destroy)();
    
    /*
     单纯线程
     */

    class SVThread: public SVObject {
    public:
        SVThread();
        
        SVThread(SVCondPtr _cond);
        
        ~SVThread();
        
        //(创建)
        bool start(bool _once = true);
        
        //(销毁)
        void stop();
        
        bool notice();
        
        //设置任务
        void setMis(SVMisPtr _mis,bool _clean = false);
        
    protected:
        void _wait();       //wait阶段
        
        virtual void _update();
        
    public:
        SV_THREAD_STATE m_svTState;     //SV线程状态
        SVCondPtr m_cond;       //条件变量
        std::thread *m_pThread; //线程
        SVMisPtr m_mis;         //任务
        bool m_use;
        bool m_once;
        bool m_run;
        bool m_misclean;
        //
        thread_cb_init m_callback_init;
        thread_cb_do m_callback_do;
        thread_cb_destroy m_callback_destroy;
    };
    

}//!namespace sv



#endif //SV_MAMGRBASE_H

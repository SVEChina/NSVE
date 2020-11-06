// IMIThreadGroup.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_THREADGROUP_H
#define IMI_THREADGROUP_H

#include "IMIThread.h"
#include "IMIMis.h"

//协同 线程组

namespace imi {

    //线程组(控制线程同步逻辑的)

    class IMIThreadGroup: public IMIObject {
    public:
        IMIThreadGroup();
        
        ~IMIThreadGroup();
        
        void create(s32 _num);
        
        void destroy();
        
        void run(bool _sync);
        
        void thread_wait();
        
        void thread_back();
        
        void setMis(s32 _index,IMIMisPtr _mis);
        
    private:
        IMICondPtr m_cond;
        IMISemPtr m_sem;
        s32 m_count;
        pthread_mutex_t m_mutex;
        
    protected:
        DECLARE_SHAREPTR(inThread);
        //内部线程
        class inThread {
        public:
            inThread(IMIThreadGroupPtr _gp) {
                m_gp = _gp;
                m_mis = nullptr;
                m_misclean = true;
                m_svTState = TS_INIT;
                m_run = true;
                m_pThread = nullptr;
                if( m_gp->m_cond->trylock() == 0 ) {
                    m_pThread = new std::thread(&inThread::_update, this);  //创建线程
                    m_pThread->detach();     //线程自动启动，不会等待
                    m_gp->m_cond->unlock();
                }
            }
            //
            ~inThread() {
                if ( m_pThread && m_pThread->joinable() ) {
                    m_pThread->join();
                    delete m_pThread;
                    m_pThread = nullptr;
                }
                m_gp = nullptr;
            }

            void setMis(IMIMisPtr _mis,bool _clean){
                if(m_svTState == TS_WORK)
                    return ;
                m_mis = _mis;
                m_misclean = _clean;
            }
            
            void _update() {
                //进入逻辑主循环
                while( 1 ) {
                    try {
                        //挂起来
                        m_gp->m_cond->lock();
                        m_svTState = TS_FREE;
                        m_gp->m_cond->wait();
                        m_gp->m_cond->unlock();
                        //IMI_LOG_ERROR(m_pThread->id);
                        if(!m_run) {
                            break;
                        }
                        //执行逻辑
                        m_svTState = TS_WORK;
                        //
                        if(m_mis) {
                            m_mis->exec(0.0f);
                        }
                        if(m_misclean) {
                            m_mis = nullptr;
                        }
                        m_gp->thread_back();
                    }catch( ... ) {
                        m_pThread->join();
                        throw;
                    }
                }
                //表示线程已死
                m_svTState = TS_DESTROY;
            }
            //
            IMIThreadGroupPtr m_gp;
            IMI_THREAD_STATE m_svTState; //IMI线程状态
            std::thread *m_pThread;     //线程
            imi::IMIMisPtr m_mis;         //任务
            bool m_run;
            bool m_misclean;
        };
        //
        IMIArray<inThreadPtr> threadIDPool; //内部线程数组
    };
    
}//!namespace imi



#endif //IMI_THREADGROUP_H

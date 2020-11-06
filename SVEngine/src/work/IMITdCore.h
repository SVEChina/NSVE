//
// Created by yizhou Fu on 2017/3/20.
//

#ifndef IMI_TDCORE_H
#define IMI_TDCORE_H

#include "../base/IMIObject.h"
#include <pthread.h>
#include <semaphore.h>
#include <atomic>

/*
 多线程 core 包含各种锁，信号量，互斥量等
 */

namespace imi {
    
    /*自旋锁
     1.循环等待
     2.无线程挂起-切换等操作
     3.开销小于线程等待等操作
     4.c++11不带自旋锁，需要自己手动实现
     */

    class IMILockSpin :public IMIObject{
    public:
        IMILockSpin();
        
        ~IMILockSpin();
        
        void lock();
        
        void unlock();
        
    private:
        std::atomic_flag mflag = ATOMIC_FLAG_INIT;     //原子操作
    };

    /*
     1.正常的线程锁
     */

    class IMILock :public IMIObject{
    public:
        IMILock();
        
        ~IMILock();
        
        void lock();
        
        void unlock();
        
        s32 trylock();
        
        pthread_mutex_t mutex;
    };

    /*条件变量
     */
    class IMICond :public IMIObject{
    public:
        IMICond();
        
        ~IMICond();
        
        s32 trylock();
        
        void lock();
        
        void unlock();
        
        virtual void wait();
        
        virtual void notice();
        
        virtual void broad();
        
    protected:
        pthread_cond_t m_cond;
        pthread_mutex_t m_mutex;
    };

    /*信号量
     */
    class IMISem :public IMIObject{
    public:
        IMISem(s32 _resvalue);
        
        ~IMISem();
        
        void wait();
        
        void post();
        
        void lastcheck();
        
        sem_t psem;
        
    };


}//!namespace imi



#endif //IMI_TDCORE_H

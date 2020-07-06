#include <sys/time.h>
#include "SVThread.h"
#include "SVMis.h"

using namespace sv;

SVThread::SVThread(){
    m_callback_init = nullptr;
    m_callback_do = nullptr;
    m_callback_destroy = nullptr;
    m_mis = nullptr;
    m_misclean = true;
    m_cond = MakeSharedPtr<SVCond>();
    m_svTState = TS_INIT;
    m_use = false;
    m_once = true;
    m_run = true;
    m_pThread = nullptr;
}

SVThread::SVThread(SVCondPtr _cond) {
    m_callback_init = nullptr;
    m_callback_do = nullptr;
    m_callback_destroy = nullptr;
    m_mis = nullptr;
    m_misclean = true;
    m_cond = _cond;
    m_svTState = TS_INIT;
    m_use = false;
    m_once = true;
    m_run = true;
    m_pThread = nullptr;
}

SVThread::~SVThread(){
    if ( m_pThread && m_pThread->joinable() ) {
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
    m_cond = nullptr;
}

//如果被多次调用很显然是不行的
bool SVThread::start(bool _once){
    if( m_cond->trylock() == 0 ) {
        m_pThread = new std::thread(&SVThread::_update, this);  //创建线程
        m_cond->unlock();
        return true;
    }
    return false;
//    if(m_svTState == TS_FREE) {
//        m_cond->notice();
//        return true;
//    }
//    return false;
}

bool SVThread::notice(){
    if( m_svTState == TS_FREE ) {
        if(m_cond) {
            m_cond->notice();
        }
        return true;
    }
    return false;
}

void SVThread::_wait() {
    if(m_run) {
        m_cond->lock();
        m_svTState = TS_FREE;
        m_cond->wait();
        m_cond->unlock();
    }
}

//同步接口
void SVThread::stop(){
    m_cond->lock();
    m_run = false;
    m_cond->unlock();
    notice();
}

void SVThread::setMis(SVMisPtr _mis,bool _clean) {
    if(m_svTState == TS_WORK)
        return ;
    m_mis = _mis;
    m_misclean = _clean;
}

void SVThread::_update(){
    //初始化
    
    //进入逻辑主循环
    while( 1 ) {
        try {
            //挂起来
            _wait();
            //检测
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
        }catch( ... ) {
            m_pThread->join();
            throw;
        }
    }
    //结束
    
    //表示线程已死
    m_svTState = TS_DESTROY;
}

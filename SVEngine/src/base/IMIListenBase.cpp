#include "IMIListenBase.h"
#include "IMITdCore.h"

using namespace imi;

IMIListenBase::IMIListenBase(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_listenDirty = true;
    m_listenlock = MakeSharedPtr<IMILock>();
}

IMIListenBase::~IMIListenBase() {
    m_listenlock = nullptr;
}

//
void IMIListenBase::registListenFunc(IMIObject *listener, dataListenFunc func) {
    m_listenlock->lock();
    //放置重复注册
    for (s32 i = 0; i < m_listenfunc_pool.size(); i++) {
        if (m_listenfunc_pool[i].listener == listener && (m_listenfunc_pool[i].func == func)) {
            m_listenlock->unlock();
            return;
        }
    }
    //
    LISTENFUNC t_listenfunc;
    t_listenfunc.listener = listener;
    t_listenfunc.func = func;
    m_listenfunc_pool.append(t_listenfunc);
    m_listenlock->unlock();
}

void IMIListenBase::unregistListenFunc(IMIObject *listener, dataListenFunc func) {
    m_listenlock->lock();
    for (s32 i = 0; i < m_listenfunc_pool.size(); i++) {
        if (m_listenfunc_pool[i].listener == listener && (m_listenfunc_pool[i].func == func)) {
            m_listenfunc_pool[i].listener = nullptr;
            m_listenfunc_pool[i].func = nullptr;
            m_listenfunc_pool.removeForce(i);
            m_listenlock->unlock();
            return;
        }
    }
    m_listenlock->unlock();
}

void IMIListenBase::noticeListener(f32 dt) {
    m_listenlock->lock();
    _updateSelf(dt);
    if (m_listenDirty) {
        m_listenDirty = false;
        _notice(dt);
    }
    m_listenlock->unlock();
}

void IMIListenBase::_updateSelf(f32 dt) {
}

void IMIListenBase::_notice(f32 dt) {
    //通知监听函数
    for (int i = 0; i < m_listenfunc_pool.size(); i++) {
        IMIObject *t_obj = m_listenfunc_pool[i].listener;
        dataListenFunc listenfunc = m_listenfunc_pool[i].func;
        (t_obj->*listenfunc)(shared_from_this());
    }
}

//
// IMIEventMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIEventMgr.h"
#include "IMIEvent.h"
#include "IMIEventProc.h"

using namespace imi;

IMIEventMgr::IMIEventMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_active_pool = nullptr;
    m_waitevent_pool = nullptr;
}

IMIEventMgr::~IMIEventMgr() {
}

void IMIEventMgr::init() {
    reset();
}

void IMIEventMgr::destroy() {
    clearAllEventProcer();
    clearAllEvent();
}

void IMIEventMgr::reset() {
    m_waitlock.lock();
    m_active_pool = &m_exe_eventList0;
    m_waitevent_pool = &m_exe_eventList1;
    m_waitlock.unlock();
}

void IMIEventMgr::update(f32 dt) {
    //激活消息池
    if (m_active_pool) {
        for(s32 i=0;i<m_active_pool->size();i++) {
            IMIEventPtr t_event = (*m_active_pool)[i];
            _processEvent(t_event);
        }
        m_active_pool->clear();
    }
    //第二消息池
    for(s32 i=0;i<m_cachevent_pool.size();i++) {
        IMIEventPtr t_event = m_cachevent_pool[i];
        _processEvent(t_event);
    }
    m_cachevent_pool.clear();
    //交换消息池
    m_waitlock.lock();
    EVENTPOOL *tmp = m_active_pool;
    m_active_pool = m_waitevent_pool;
    m_waitevent_pool = tmp;
    m_waitlock.unlock();
}

void IMIEventMgr::_processEvent(IMIEventPtr _event) {
    //如果是系统消息走系统消息处理
    if( _event->isSys() ) {
        //系统消息处理
        SYS_LISTEN_CB_POOL::iterator it = m_sys_listen_pool.begin();
        while (it!=m_sys_listen_pool.end()) {
            IMIObjectPtr t_caller = (*it).caller;
            proc_sys_event t_cb = (*it)._cb;
            (*t_cb)(t_caller,_event);
            it++;
        }
    } else {
        //普通消息处理
        for (s32 i = 0; i < m_event_procers.size(); i++) {
            if (m_event_procers[i]->procEvent(_event) == false)
                return;
        }
    }
}

void IMIEventMgr::pushEvent(IMIEventPtr _event,bool _cache) {
    if(_cache) {
        m_cachevent_pool.push_back(_event);
    }else{
        m_waitlock.lock();
        if (m_waitevent_pool) {
            m_waitevent_pool->push_back(_event);
        }
        m_waitlock.unlock();
    }
}

//系统消息处理
//监听某一个系统消息
void IMIEventMgr::listenSysEvent(IMIObjectPtr _caller,proc_sys_event _cb) {
    SYS_LISTEN_CB_POOL::iterator it = m_sys_listen_pool.begin();
    while (it!=m_sys_listen_pool.end()) {
        if((*it).caller == _caller) {
            return;
        }
        it++;
    }
    //
    IMIEventMgr::SYSEVTPROC _proc;
    _proc.caller = _caller;
    _proc._cb = _cb;
    m_sys_listen_pool.push_back(_proc);
}

//不监听某一个系统消息
void IMIEventMgr::unlistenSysEvent(IMIObjectPtr caller) {
    SYS_LISTEN_CB_POOL::iterator it = m_sys_listen_pool.begin();
    while (it!=m_sys_listen_pool.end()) {
        if((*it).caller == caller) {
            (*it).caller = nullptr;
            m_sys_listen_pool.erase(it);
            return;
        }
        it++;
    }
}

//清理监听的系统消息
void IMIEventMgr::clearListenSysEvent() {
    SYS_LISTEN_CB_POOL::iterator it = m_sys_listen_pool.begin();
    while (it!=m_sys_listen_pool.end()) {
        (*it).caller = nullptr;
        it++;
    }
    m_sys_listen_pool.clear();
}

//消息处理器
bool IMIEventMgr::hasRegist(IMIEventProcPtr _procer) {
    if (!_procer)
        return true;
    for (s32 i = 0; i < m_event_procers.size(); i++) {
        if (m_event_procers[i] == _procer)
            return true;
    }
    return false;
}

void IMIEventMgr::registProcer(IMIEventProcPtr _procer) {
    if (hasRegist(_procer))
        return;
    if (_procer) {
        m_event_procers.push_back(_procer);
    }
}

void IMIEventMgr::unregistProcer(IMIEventProcPtr _procer) {
    if (!_procer)
        return;
    PROCERPOOL::iterator it = m_event_procers.begin();
    while (it!=m_event_procers.end()) {
        if( (*it) == _procer ) {
            m_event_procers.erase(it);
            return;
        }
        it++;
    }
}

void IMIEventMgr::clearAllEvent() {
    m_active_pool = nullptr;
    m_waitevent_pool = nullptr;
    m_exe_eventList0.clear();
    m_exe_eventList1.clear();
}

void IMIEventMgr::clearAllEventProcer() {
    m_event_procers.clear();
}

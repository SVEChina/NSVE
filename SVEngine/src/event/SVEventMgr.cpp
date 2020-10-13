//
// SVEventMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVEventMgr.h"
#include "SVEvent.h"
#include "SVEventProc.h"

using namespace sv;

SVEventMgr::SVEventMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_active_pool = nullptr;
    m_waitevent_pool = nullptr;
}

SVEventMgr::~SVEventMgr() {
}

void SVEventMgr::init() {
    reset();
}

void SVEventMgr::destroy() {
    clearAllEventProcer();
    clearAllEvent();
}

void SVEventMgr::reset() {
    m_waitlock.lock();
    m_active_pool = &m_exe_eventList0;
    m_waitevent_pool = &m_exe_eventList1;
    m_waitlock.unlock();
}

void SVEventMgr::update(f32 dt) {
    //激活消息池
    if (m_active_pool) {
        for(s32 i=0;i<m_active_pool->size();i++) {
            SVEventPtr t_event = (*m_active_pool)[i];
            _processEvent(t_event);
        }
        m_active_pool->destroy();
    }
    //第二消息池
    for(s32 i=0;i<m_cachevent_pool.size();i++) {
        SVEventPtr t_event = m_cachevent_pool[i];
        _processEvent(t_event);
    }
    m_cachevent_pool.destroy();
    //交换消息池
    m_waitlock.lock();
    EVENTPOOL *tmp = m_active_pool;
    m_active_pool = m_waitevent_pool;
    m_waitevent_pool = tmp;
    m_waitlock.unlock();
}

void SVEventMgr::_processEvent(SVEventPtr _event) {
    for (s32 i = 0; i < m_event_procers.size(); i++) {
        if (m_event_procers[i]->procEvent(_event) == false)
            return;
    }
}

void SVEventMgr::pushEvent(SVEventPtr _event,bool _cache) {
    if(_cache) {
        m_cachevent_pool.append(_event);
    }else{
        m_waitlock.lock();
        if (m_waitevent_pool) {
            m_waitevent_pool->append(_event);
        }
        m_waitlock.unlock();
    }
}

//消息处理器
bool SVEventMgr::hasRegist(SVEventProcPtr _procer) {
    if (!_procer)
        return true;
    for (s32 i = 0; i < m_event_procers.size(); i++) {
        if (m_event_procers[i] == _procer)
            return true;
    }
    return false;
}

void SVEventMgr::registProcer(SVEventProcPtr _procer) {
    if (hasRegist(_procer))
        return;
    if (_procer) {
        m_event_procers.append(_procer);
    }
}

void SVEventMgr::unregistProcer(SVEventProcPtr _procer) {
    if (!_procer)
        return;
    for (s32 i = 0; i < m_event_procers.size(); i++) {
        if (m_event_procers[i] == _procer) {
            m_event_procers.removeForce(i);
            return;
        }
    }
}

void SVEventMgr::clearAllEvent() {
    m_active_pool = nullptr;
    m_waitevent_pool = nullptr;
    m_exe_eventList0.clear();
    m_exe_eventList1.clear();
}

void SVEventMgr::clearAllEventProcer() {
    m_event_procers.destroy();
}

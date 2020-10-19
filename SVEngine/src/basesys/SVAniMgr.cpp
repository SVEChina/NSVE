//
// SVAniMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVAniMgr.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../work/SVTdCore.h"
#include "ani/SVAniUnit.h"

using namespace sv;

SVAniMgr::SVAniMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_ani_lock = MakeSharedPtr<SVLockSpin>();;
}

SVAniMgr::~SVAniMgr() {
    m_ani_lock = nullptr;
}

//
void SVAniMgr::init() {
}

//
void SVAniMgr::destroy() {
}

//
void SVAniMgr::update(f32 _dt) {
    m_ani_lock->lock();
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if(m_ani_pool[i]._unit) {
            m_ani_pool[i]._unit->update(_dt, m_ani_pool[i]._node);
        }
    }
    m_ani_lock->unlock();
}

void SVAniMgr::addAni(SVNodePtr _node,SVAniUnitPtr _unit) {
    m_ani_lock->lock();
    if( !hasAni(_node) ) {
        SVAniMgr::ANICELL t_cell;
        t_cell._node = _node;
        t_cell._unit = _unit;
        m_ani_pool.push_back(t_cell);
        //
        _unit->bind(_node);
    }
    m_ani_lock->unlock();
}

void SVAniMgr::removeAni(SVNodePtr _node) {
    m_ani_lock->lock();
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if( m_ani_pool[i]._node == _node) {
            ANIPOOLS::iterator it = m_ani_pool.begin() + i;
            m_ani_pool[i].reset();
            m_ani_pool.erase(it);
            break ;
        }
    }
    m_ani_lock->unlock();
}

void SVAniMgr::clearAni() {
    m_ani_lock->lock();
    for(s32 i=0;i<m_ani_pool.size();i++) {
        m_ani_pool[i].reset();
    }
    m_ani_pool.clear();
    m_ani_lock->unlock();
}

bool SVAniMgr::hasAni(SVNodePtr _node) {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if( m_ani_pool[i]._node == _node)
            return true;
    }
    return false;
}

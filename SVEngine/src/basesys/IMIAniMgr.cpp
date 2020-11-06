//
// IMIAniMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIAniMgr.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../work/IMITdCore.h"
#include "ani/IMIAniUnit.h"

using namespace imi;

IMIAniMgr::IMIAniMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_ani_lock = MakeSharedPtr<IMILockSpin>();;
}

IMIAniMgr::~IMIAniMgr() {
    m_ani_lock = nullptr;
}

//
void IMIAniMgr::init() {
}

//
void IMIAniMgr::destroy() {
}

//
void IMIAniMgr::update(f32 _dt) {
    m_ani_lock->lock();
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if(m_ani_pool[i]._unit) {
            m_ani_pool[i]._unit->update(_dt, m_ani_pool[i]._node);
        }
    }
    m_ani_lock->unlock();
}

void IMIAniMgr::addAni(IMINodePtr _node,IMIAniUnitPtr _unit) {
    m_ani_lock->lock();
    if( !hasAni(_node) ) {
        IMIAniMgr::ANICELL t_cell;
        t_cell._node = _node;
        t_cell._unit = _unit;
        m_ani_pool.push_back(t_cell);
        //
        _unit->bind(_node);
    }
    m_ani_lock->unlock();
}

void IMIAniMgr::removeAni(IMINodePtr _node) {
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

void IMIAniMgr::clearAni() {
    m_ani_lock->lock();
    for(s32 i=0;i<m_ani_pool.size();i++) {
        m_ani_pool[i].reset();
    }
    m_ani_pool.clear();
    m_ani_lock->unlock();
}

bool IMIAniMgr::hasAni(IMINodePtr _node) {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if( m_ani_pool[i]._node == _node)
            return true;
    }
    return false;
}

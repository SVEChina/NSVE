//
// SVAniMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVAniMgr.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "ani/SVAniUnit.h"

using namespace sv;

SVAniMgr::SVAniMgr(SVInstPtr _app)
:SVSysBase(_app) {
//    m_filter_lock = MakeSharedPtr<SVLockSpin>();
//    m_enable = false;
//    m_method = 0;
//    m_subsysType = 0;
//    m_ar_target = nullptr;
//    m_tex0 = nullptr;
//    m_tex1 = nullptr;
//    m_tex2 = nullptr;
}

SVAniMgr::~SVAniMgr() {
}

//
void SVAniMgr::init() {
}

//
void SVAniMgr::destroy() {
}

//
void SVAniMgr::update(f32 _dt) {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if(m_ani_pool[i]._unit) {
            m_ani_pool[i]._unit->update(_dt, m_ani_pool[i]._node);
        }
    }
}

void SVAniMgr::addAni(SVNodePtr _node,SVAniUnitPtr _unit) {
    if( !hasAni(_node) ) {
        SVAniMgr::ANICELL t_cell;
        t_cell._node = _node;
        t_cell._unit = _unit;
        m_ani_pool.push_back(t_cell);
    }
}

void SVAniMgr::removeAni(SVNodePtr _node) {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if( m_ani_pool[i]._node == _node) {
            ANIPOOLS::iterator it = m_ani_pool.begin() + i;
            m_ani_pool[i].reset();
            m_ani_pool.erase(it);
            return ;
        }
    }
}

void SVAniMgr::clearAni() {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        m_ani_pool[i].reset();
    }
    m_ani_pool.clear();
}

bool SVAniMgr::hasAni(SVNodePtr _node) {
    for(s32 i=0;i<m_ani_pool.size();i++) {
        if( m_ani_pool[i]._node == _node)
            return true;
    }
    return false;
}

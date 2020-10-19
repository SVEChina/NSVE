//
// SVSceneMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVSceneMgr.h"
#include "SVScene.h"
#include "SVComData.h"
#include "../work/SVTdCore.h"
#include "../basesys/SVBasicSys.h"
#include "../mtl/SVFilterBase.h"

using namespace sv;

SVSceneMgr::SVSceneMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 6;
    m_main_scene = nullptr;
    m_scene_lock = MakeSharedPtr<SVLockSpin>();
    m_filter_lock = MakeSharedPtr<SVLockSpin>();
}

SVSceneMgr::~SVSceneMgr() {
    m_main_scene = nullptr;
    m_scene_lock = nullptr;
    m_filter_lock = nullptr;
}

void SVSceneMgr::init() {
    m_main_scene = MakeSharedPtr<SVScene>(mApp,"testScene");
    m_main_scene->create();
}

void SVSceneMgr::destroy() {
}

//加载场景
void SVSceneMgr::loadScene(cptr8 _fname) {
}

//切换场景
void SVSceneMgr::changeScene(cptr8 _name) {
}

void SVSceneMgr::setScene(SVScenePtr _scene){
    m_scene_lock->lock();
    m_main_scene = _scene;
    m_scene_lock->unlock();
}

SVScenePtr SVSceneMgr::getScene(){
    return m_main_scene;
}

//反适配
void SVSceneMgr::uiToScene(f32& _x,f32& _y) {
    //invert Y
    //_y = mApp->m_global_param.sv_height - _y;
}

//更新
void SVSceneMgr::update(f32 _dt) {
    //
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( m_filter_pool[i]._filter ) {
            m_filter_pool[i]._filter->update(_dt);
        }
    }
    m_filter_lock->unlock();
    //
    m_scene_lock->lock();
    if(m_main_scene){
        m_main_scene->update(_dt);
    }
    m_scene_lock->unlock();
}

bool SVSceneMgr::addFilter(cptr8 _name,SVFilterBasePtr _filter) {
    if( hasFilter(_name) ) {
        return false;
    }
    m_filter_lock->lock();
    FilterUnit t_unit;
    t_unit._name = _name;
    t_unit._filter = _filter;
    m_filter_pool.push_back(t_unit);
    m_filter_lock->unlock();
    return true;
}

void SVSceneMgr::delFilter(cptr8 _name) {
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( m_filter_pool[i]._name == _name ) {
            m_filter_pool[i]._filter = nullptr;
            m_filter_pool.erase(m_filter_pool.begin() + i);
            break;
        }
    }
    m_filter_lock->unlock();
}

void SVSceneMgr::clearFilter() {
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        m_filter_pool[i]._filter = nullptr;
    }
    m_filter_pool.clear();
    m_filter_lock->unlock();
}

bool SVSceneMgr::hasFilter(cptr8 _name) {
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( m_filter_pool[i]._name == _name ) {
            return true;
        }
    }
    return false;
}

void SVSceneMgr::test() {
    if(m_main_scene) {
        m_main_scene->test();
    }
}

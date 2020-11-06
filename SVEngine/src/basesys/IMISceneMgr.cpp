//
// IMISceneMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISceneMgr.h"
#include "IMIScene.h"
#include "IMIComData.h"
#include "../work/IMITdCore.h"
#include "../basesys/IMIBasicSys.h"
#include "../mtl/IMIFilterBase.h"

using namespace imi;

IMISceneMgr::IMISceneMgr(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 6;
    m_main_scene = nullptr;
    m_scene_lock = MakeSharedPtr<IMILockSpin>();
    m_filter_lock = MakeSharedPtr<IMILockSpin>();
}

IMISceneMgr::~IMISceneMgr() {
    m_main_scene = nullptr;
    m_scene_lock = nullptr;
    m_filter_lock = nullptr;
}

void IMISceneMgr::init() {
    m_main_scene = MakeSharedPtr<IMIScene>(mApp,"testScene");
    m_main_scene->create();
}

void IMISceneMgr::destroy() {
}

//加载场景
void IMISceneMgr::loadScene(cptr8 _fname) {
}

//切换场景
void IMISceneMgr::changeScene(cptr8 _name) {
}

void IMISceneMgr::setScene(IMIScenePtr _scene){
    m_scene_lock->lock();
    m_main_scene = _scene;
    m_scene_lock->unlock();
}

IMIScenePtr IMISceneMgr::getScene(){
    return m_main_scene;
}

//反适配
void IMISceneMgr::uiToScene(f32& _x,f32& _y) {
    //invert Y
    //_y = mApp->m_global_param.sv_height - _y;
}

//更新
void IMISceneMgr::update(f32 _dt) {
    //
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        m_filter_pool[i]->update(_dt);
    }
    m_filter_lock->unlock();
    //
    m_scene_lock->lock();
    if(m_main_scene){
        m_main_scene->update(_dt);
    }
    m_scene_lock->unlock();
}

bool IMISceneMgr::addFilter(cptr8 _name,IMIFilterBasePtr _filter) {
    if( hasFilter(_name) ) {
        return false;
    }
    m_filter_lock->lock();
    m_filter_pool.push_back(_filter);
    m_filter_lock->unlock();
    return true;
}

bool IMISceneMgr::delFilter(cptr8 _name) {
    bool t_flag = false;
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( strcmp(m_filter_pool[i]->getName() ,_name) == 0 ) {
            m_filter_pool[i]->destroy();
            m_filter_pool.erase(m_filter_pool.begin() + i);
            t_flag = true;
            break;
        }
    }
    m_filter_lock->unlock();
    return t_flag;
}

void IMISceneMgr::clearFilter() {
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        m_filter_pool[i]->destroy();
    }
    m_filter_pool.clear();
    m_filter_lock->unlock();
}

bool IMISceneMgr::hasFilter(cptr8 _name) {
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( strcmp(m_filter_pool[i]->getName() ,_name) == 0  ) {
            return true;
        }
    }
    return false;
}

IMIFilterBasePtr IMISceneMgr::getFilter(cptr8 _name) {
    for(s32 i=0;i<m_filter_pool.size();i++) {
        if( strcmp(m_filter_pool[i]->getName() ,_name) == 0 ) {
            return m_filter_pool[i];
        }
    }
    return nullptr;
}

void IMISceneMgr::test() {
    if(m_main_scene) {
        m_main_scene->test();
    }
}

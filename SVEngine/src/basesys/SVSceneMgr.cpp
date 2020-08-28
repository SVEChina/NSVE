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

using namespace sv;

SVSceneMgr::SVSceneMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 6;
    m_main_scene = nullptr;
    m_scene_lock = MakeSharedPtr<SVLockSpin>();
}

SVSceneMgr::~SVSceneMgr() {
    m_main_scene = nullptr;
    m_scene_lock = nullptr;
}

void SVSceneMgr::init() {
    m_main_scene = MakeSharedPtr<SVScene>(mApp,"testScene");
    m_main_scene->create();
    m_main_scene->test();
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
    //_y = mApp->m_global_param.m_sv_height - _y;
}

//更新
void SVSceneMgr::update(f32 _dt) {
    m_scene_lock->lock();
    if(m_main_scene){
        m_main_scene->update(_dt);
    }
    m_scene_lock->unlock();
}


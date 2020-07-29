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
    m_pMainScene = nullptr;
    m_sceneLock = MakeSharedPtr<SVLockSpin>();
}

SVSceneMgr::~SVSceneMgr() {
    m_pMainScene = nullptr;
    m_sceneLock = nullptr;
}

void SVSceneMgr::init() {
    m_pMainScene = MakeSharedPtr<SVScene>(mApp,"testScene");
    m_pMainScene->create();
    m_pMainScene->test();
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
    m_sceneLock->lock();
    m_pMainScene = _scene;
    m_sceneLock->unlock();
}

SVScenePtr SVSceneMgr::getScene(){
    return m_pMainScene;
}

//反适配
void SVSceneMgr::uiToScene(f32& _x,f32& _y) {
    //invert Y
    //_y = mApp->m_pGlobalParam->m_inner_height - _y;
}

//更新
void SVSceneMgr::update(f32 dt) {
    m_sceneLock->lock();
    if(m_pMainScene){
        //激活场景
//        mApp->m_pGlobalParam->m_curScene = m_pMainScene;
//        m_pMainScene->active();
//        m_pMainScene->update(dt);
//        m_pMainScene->unactive();
//        mApp->m_pGlobalParam->m_curScene = nullptr;
    }
    m_sceneLock->unlock();
}


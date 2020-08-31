//
// SVBasicSys.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVBasicSys.h"
#include "SVRecycleProcess.h"
#include "SVPickProcess.h"
#include "SVFontProcess.h"
#include "SVStreamIn.h"
#include "SVStreamOut.h"
#include "SVSensorProcess.h"

using namespace sv;

SVBasicSys::SVBasicSys(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 2;
    m_pRecycleModule = nullptr;
    m_picker = nullptr;
    m_fonter = nullptr;
}

SVBasicSys::~SVBasicSys() {
}

void SVBasicSys::init() {
    //
    m_pRecycleModule = MakeSharedPtr<SVRecycleProcess>(mApp);
    m_pRecycleModule->startListen();
    //
    m_picker = MakeSharedPtr<SVPickProcess>(mApp);
    m_picker->disablePick();
    m_picker->startListen();
    //
    m_fonter = MakeSharedPtr<SVFontProcess>(mApp);
    //
    m_sensor = MakeSharedPtr<SVSensorProcess>(mApp);
    m_sensor->startListen();
}

void SVBasicSys::loadDefaultFMFont(){
    if (m_fonter) {
        m_fonter->loadDefBMFont();
    }
}

void SVBasicSys::destroy() {
    //
    m_fonter = nullptr;
    //
    m_picker->stopListen();
    m_picker = nullptr;
    //
    m_pRecycleModule->stopListen();
    m_pRecycleModule = nullptr;
    //
    if (m_sensor) {
        m_sensor->stopListen();
        m_sensor = nullptr;
    }
}

void SVBasicSys::update(f32 dt) {
    //回收系统
    if (m_pRecycleModule) {
        m_pRecycleModule->update(dt);
    }
    if (m_sensor) {
        m_sensor->update(dt);
    }
}

//
void SVBasicSys::output() {
}

SVRecycleProcessPtr SVBasicSys::getRecycleModule(){
    return m_pRecycleModule;
}

SVPickProcessPtr SVBasicSys::getPickModule(){
    return m_picker;
}

SVFontProcessPtr SVBasicSys::getFontModule(){
    return m_fonter;
}

SVSensorProcessPtr SVBasicSys::getSensorModule(){
    return m_sensor;
}

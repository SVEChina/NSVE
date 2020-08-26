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
#include "SVPictureProcess.h"
#include "SVSensorProcess.h"

using namespace sv;

SVBasicSys::SVBasicSys(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 2;
    m_pRecycleModule = nullptr;
    m_picker = nullptr;
    m_fonter = nullptr;
    m_stream_in = nullptr;
    m_stream_out = nullptr;
}

SVBasicSys::~SVBasicSys() {
    m_stream_in = nullptr;
    m_stream_out = nullptr;
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
    m_stream_in = MakeSharedPtr<SVStreamIn>(mApp);
    //
    m_stream_out = MakeSharedPtr<SVStreamOut>(mApp);
    //
    m_pic_proc = MakeSharedPtr<SVPictureProcess>(mApp);
    m_pic_proc->init();
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
    m_stream_in = nullptr;
    //
    m_stream_out = nullptr;
    //
    if(m_pic_proc){
        m_pic_proc->destroy();
        m_pic_proc = nullptr;
    }
    
    if (m_sensor) {
        m_sensor->stopListen();
        m_sensor = nullptr;
    }
}

void SVBasicSys::update(f32 dt) {
    //输入流系统更新
    if(m_stream_in){
        m_stream_in->update(dt);
    }
    //相片处理更新
    if(m_pic_proc){
        m_pic_proc->update(dt);
    }
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
    //输出流系统更新
    if(m_stream_out){
        m_stream_out->output();
    }
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

SVStreamInPtr SVBasicSys::getStreamIn(){
    return m_stream_in;
}

SVStreamOutPtr SVBasicSys::getStreamOut(){
    return m_stream_out;
}

SVPictureProcessPtr SVBasicSys::getPicProc() {
    return m_pic_proc;
}

SVSensorProcessPtr SVBasicSys::getSensorModule(){
    return m_sensor;
}

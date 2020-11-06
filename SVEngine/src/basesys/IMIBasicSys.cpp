//
// IMIBasicSys.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIBasicSys.h"
#include "IMIRecycleProcess.h"
#include "IMIPickProcess.h"
#include "IMIFontProcess.h"
#include "IMIStreamIn.h"
#include "IMIStreamOut.h"

using namespace imi;

IMIBasicSys::IMIBasicSys(IMIInstPtr _app)
:IMISysBase(_app) {
    m_subsysType = 2;
    m_pRecycleModule = nullptr;
    m_picker = nullptr;
    m_fonter = nullptr;
}

IMIBasicSys::~IMIBasicSys() {
}

void IMIBasicSys::init() {
    //
    m_pRecycleModule = MakeSharedPtr<IMIRecycleProcess>(mApp);
    m_pRecycleModule->startListen();
    //
    m_picker = MakeSharedPtr<IMIPickProcess>(mApp);
    m_picker->disablePick();
    m_picker->startListen();
    //
    m_fonter = MakeSharedPtr<IMIFontProcess>(mApp);
}

void IMIBasicSys::loadDefaultFMFont(){
    if (m_fonter) {
        m_fonter->loadDefBMFont();
    }
}

void IMIBasicSys::destroy() {
    //
    m_fonter = nullptr;
    //
    m_picker->stopListen();
    m_picker = nullptr;
    //
    m_pRecycleModule->stopListen();
    m_pRecycleModule = nullptr;
}

void IMIBasicSys::update(f32 dt) {
    //回收系统
    if (m_pRecycleModule) {
        m_pRecycleModule->update(dt);
    }
}

//
void IMIBasicSys::output() {
}

IMIRecycleProcessPtr IMIBasicSys::getRecycleModule(){
    return m_pRecycleModule;
}

IMIPickProcessPtr IMIBasicSys::getPickModule(){
    return m_picker;
}

IMIFontProcessPtr IMIBasicSys::getFontModule(){
    return m_fonter;
}

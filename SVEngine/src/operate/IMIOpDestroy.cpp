//
// IMIOpDestroy.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpDestroy.h"
#include "../app/IMIInst.h"
#include "../module/IMIModuleSys.h"
#include "../module/IMIModuleBase.h"
#include "../module/IMIGameBase.h"
#include "../base/IMIPreDeclare.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIPickProcess.h"

using namespace imi;

IMIOpDestroyEffect::IMIOpDestroyEffect(IMIInstPtr _app, cptr8 _name)
:IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyEffect::_process(float dt) {
    s32 len = m_name.size();
    s32 pos = m_name.rfind('/');
    IMIString t_moduleName = IMIString::substr(m_name.c_str(), pos+1, len - pos - 1);
    IMIModuleBasePtr t_module = mApp->getModuleSys()->getModule(t_moduleName.c_str());
    if (t_module) {
        mApp->getModuleSys()->unregist(t_moduleName.c_str());
        t_module->close();
        t_module->destroy();
    }
}

IMIOpDestroyGameZCMgr::IMIOpDestroyGameZCMgr(IMIInstPtr _app)
:IMIOpBase(_app) {
    
}

void IMIOpDestroyGameZCMgr::_process(float dt) {
//    IMIString t_name = "sv_gamezc_module";
//    IMIModuleBasePtr t_module = mApp->getModuleSys()->getModule(t_name.c_str());
//    if (t_module) {
//        mApp->getModuleSys()->unregist(t_name.c_str());
//        t_module->close();
//        t_module->destroy();
//    }
}

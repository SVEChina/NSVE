//
// IMIPersonModule.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIPersonModule.h"
#include "IMIPerson.h"
#include "../basesys/IMIConfig.h"

using namespace imi;

IMIPersonModule::IMIPersonModule(IMIInstPtr _app)
:IMIEventProc(_app){
}

IMIPersonModule::~IMIPersonModule() {
}

void IMIPersonModule::initModule() {
    for (int i = 0; i < SUPPORT_MAX_PERSON_NUM; i++) {
        m_persons[i] = MakeSharedPtr<IMIPerson>(mApp);
        m_persons[i]->setPersonID(i + 1);
        m_persons[i]->setDetectType(DETECT_T_ST);
    }
}

void IMIPersonModule::destoryModule(){
    for (int i = 0; i < SUPPORT_MAX_PERSON_NUM; i++) {
        m_persons[i] = nullptr;
    }
}

IMIPersonPtr IMIPersonModule::getPerson(s32 _personId){
    for (s32 i = 0; i < SUPPORT_MAX_PERSON_NUM; i++) {
        if (m_persons[i]->getPersonID() == _personId)
            return m_persons[i];
    }
    return nullptr;
}


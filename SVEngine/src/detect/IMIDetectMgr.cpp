//
// IMIDetectMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIDetectMgr.h"
#include "IMIDetectST.h"
#include "../app/IMIInst.h"
#include "../basesys/IMIConfig.h"

using namespace imi;

#define DETECT_RESULT_BUFFER_SIZE 4000
#define STANDARDEYEDIS 190

IMIDetectMgr::IMIDetectMgr(IMIInstPtr _app)
: IMISysBase(_app) {
    m_detectType = DETECT_T_NULL;
    m_pDetectBase = nullptr;
    m_pernson_sys = nullptr;
}

IMIDetectMgr::~IMIDetectMgr() {
}

//初始化识别数据类型
void IMIDetectMgr::init(DETECTTYPE type) {
    if (m_detectType != type) {
        m_detectType = type;
        m_pDetectBase = MakeSharedPtr<IMIDetectST>(mApp);
    }
    m_pernson_sys = MakeSharedPtr<IMIPersonModule>(mApp);
    m_pernson_sys->initModule();
}

//析够
void IMIDetectMgr::destroy() {
    m_detectType = DETECT_T_NULL;
    m_pDetectBase=nullptr;
}

IMIDetectBasePtr IMIDetectMgr::getDetect() {
    return m_pDetectBase;
}

void IMIDetectMgr::update(f32 _dt){
    if (m_pDetectBase) {
        m_pDetectBase->noticeListener(_dt);
    }
}

IMIPersonModulePtr IMIDetectMgr::getPersonModule(){
    if (m_pernson_sys) {
        return m_pernson_sys;
    }
    return nullptr;
}

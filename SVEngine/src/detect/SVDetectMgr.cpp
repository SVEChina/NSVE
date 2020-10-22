//
// SVDetectMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDetectMgr.h"
#include "SVDetectST.h"
#include "../app/SVInst.h"
#include "../basesys/SVConfig.h"

using namespace sv;

#define DETECT_RESULT_BUFFER_SIZE 4000
#define STANDARDEYEDIS 190

SVDetectMgr::SVDetectMgr(SVInstPtr _app)
: SVSysBase(_app) {
    m_detectType = DETECT_T_NULL;
    m_pDetectBase = nullptr;
    m_pernson_sys = nullptr;
}

SVDetectMgr::~SVDetectMgr() {
}

//初始化识别数据类型
void SVDetectMgr::init(DETECTTYPE type) {
    if (m_detectType != type) {
        m_detectType = type;
        m_pDetectBase = MakeSharedPtr<SVDetectST>(mApp);
    }
    m_pernson_sys = MakeSharedPtr<SVPersonModule>(mApp);
    m_pernson_sys->initModule();
}

//析够
void SVDetectMgr::destroy() {
    m_detectType = DETECT_T_NULL;
    m_pDetectBase=nullptr;
}

SVDetectBasePtr SVDetectMgr::getDetect() {
    return m_pDetectBase;
}

void SVDetectMgr::update(f32 _dt){
    if (m_pDetectBase) {
        m_pDetectBase->noticeListener(_dt);
    }
}

SVPersonModulePtr SVDetectMgr::getPersonModule(){
    if (m_pernson_sys) {
        return m_pernson_sys;
    }
    return nullptr;
}

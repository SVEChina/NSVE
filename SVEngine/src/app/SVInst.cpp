//
// SVInst.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVInst.h"
#include "SVGlobalMgr.h"
#include "SVGlobalParam.h"
#include "../basesys/SVRPath.h"
#include "../work/SVTdCore.h"
#include "../work/SVThreadPool.h"
#include "../file/SVFileMgr.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/SVConfig.h"
#include "../operate/SVOpBase.h"
#include "../operate/SVOpCreate.h"
#include "../operate/SVOpThread.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderState.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVMetal/SVRendererMetal.h"
#include "../rendercore/SVGL/SVRendererGL.h"


using namespace sv;

SVInst::SVInst() {
    m_svst = SV_ST_NULL;
    m_engTimeState = ENG_TS_NOR;
    m_pRPath = nullptr;
}

SVInst::~SVInst() {
}

SVInstPtr SVInst::makeCreate() {
    SVInstPtr t_inst = MakeSharedPtr<SVInst>();
    return t_inst;
}

//构建各个模块的逻辑部分，引擎可以运行的最简模式
void SVInst::init() {
    m_pRM = nullptr;
    //
    m_pGlobalMgr = MakeSharedPtr<SVGlobalMgr>( std::dynamic_pointer_cast<SVInst>(shareObject()) );
    m_pGlobalMgr->init();
    //
    m_pGlobalMgr->m_pConfig = MakeSharedPtr<SVConfig>(this);
    m_pGlobalMgr->m_pConfig->init();
    //默认渲染路径是普通
    m_pRPath = MakeSharedPtr<SVRPathNor>(std::dynamic_pointer_cast<SVInst>(shareObject()) );
    m_pRPath->init();
    //
    m_pGlobalParam = MakeSharedPtr<SVGlobalParam>(this);
    m_svst = SV_ST_WAIT;
}

void SVInst::destroy() {
    m_pRPath = nullptr;
    m_pGlobalMgr = nullptr;
    m_pGlobalParam = nullptr;
    m_svst = SV_ST_NULL;
}

//创建渲染器
SVRendererPtr SVInst::createRM(SV_RM_TYPE _type) {
    if(_type == E_M_METAL) {
        m_pRM = MakeSharedPtr<SVRendererMetal>( std::dynamic_pointer_cast<SVInst>(shareObject())  );    //SVRendererPtr;
    }else if(_type == E_M_GLES) {
        m_pRM = MakeSharedPtr<SVRendererGL>( std::dynamic_pointer_cast<SVInst>(shareObject())  );       //SVRendererPtr;
    }else if(_type == E_M_VUNKAN) {
        //m_pRM = MakeSharedPtr<>();
    }
    return m_pRM;
}

//销毁渲染器
void SVInst::destroyRM() {
    //
}

//跑线程模型 就是引擎运行
void SVInst::start() {
    m_svst = SV_ST_RUN;
}

//引擎的线程模型，停止运行
//开启一个线程，销毁引擎，引擎销毁完毕以后，调用返回
void SVInst::stop() {
    m_svst = SV_ST_WAIT;
}

void SVInst::updateSVE(f32 _dt) {
    //处理一般逻辑，例如运动，消息处理等等
    m_pGlobalMgr->update(_dt);
    //开始做渲染指令的生成（只有这里才会产生真正的渲染指令）
    m_pRPath->render(_dt);
}

void SVInst::renderSVE() {
    if( m_pGlobalMgr->m_pRenderMgr ) {
        m_pGlobalMgr->m_pRenderMgr->render();
    }
}

void SVInst::svSuspend(){
}

void SVInst::svResume(){
}

void SVInst::clearCache(){
}

//
void SVInst::addRespath(cptr8 path) {
    m_pGlobalMgr->m_pFileMgr->addRespath(path);
}

void SVInst::setTimeState(SV_ENG_TIMESTATE _mode){
    m_engTimeState = _mode;
}

SV_ENG_TIMESTATE SVInst::getTimeState(){
    return m_engTimeState;
}

//
SVFileMgrPtr SVInst::getFileMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pFileMgr;
}

SVConfigPtr SVInst::getConfig(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pConfig;
}

SVEventMgrPtr SVInst::getEventMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pEventMgr;
}

SVBasicSysPtr SVInst::getBasicSys(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pBasicSys;
}

SVCameraMgrPtr SVInst::getCameraMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pCameraMgr;
}

SVSceneMgrPtr SVInst::getSceneMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pSceneMgr;
}

SVLightSysPtr SVInst::getLightSys() {
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pLightSys;
}

SVModuleSysPtr SVInst::getModuleSys(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pModuleSys;
}

SVShaderMgrPtr SVInst::getShaderMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pShaderMgr;
}

SVTexMgrPtr SVInst::getTexMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pTexMgr;
}

SVRenderMgrPtr SVInst::getRenderMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pRenderMgr;
}

SVDetectMgrPtr SVInst::getDetectMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pDetectMgr;
}

SVDeformMgrPtr SVInst::getDeformMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pDeformSys;
}

SVStaticDataPtr SVInst::getDataMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pStaticData;
}

SVModelMgrPtr SVInst::getModelMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pModelMgr;
}

SVPhysicsWorldMgrPtr SVInst::getPhysicsWorldMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pPhysicSys;
}

SVRendererPtr SVInst::getRenderer() {
    return m_pRM;
}

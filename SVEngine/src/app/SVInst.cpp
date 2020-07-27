//
// SVInst.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVInst.h"
#include "SVGlobalMgr.h"
#include "SVGlobalParam.h"
#include "../env/SVCtxBase.h"
#include "../basesys/SVRPath.h"
#include "../work/SVTdCore.h"
#include "../work/SVThreadPool.h"
#include "../file/SVFileMgr.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/SVConfig.h"
#include "../file/SVFileMgr.h"
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
    m_ctx = nullptr;
    m_pFileMgr = nullptr;
    m_pConfig = nullptr;
}

SVInst::~SVInst() {
    m_ctx = nullptr;
    m_pFileMgr = nullptr;
    m_pConfig = nullptr;
}

SVInstPtr SVInst::makeCreate() {
    SVInstPtr t_inst = MakeSharedPtr<SVInst>();
    return t_inst;
}

SVInstPtr SVInst::share() {
    return std::dynamic_pointer_cast<SVInst>(shareObject()) ;
}

#include "../mtl/SVMtlLib.h"
#include "../mtl/SVMtlCore.h"

//构建各个模块的逻辑部分，引擎可以运行的最简模式
void SVInst::init() {
    m_pRM = nullptr;
    //
    if(!m_pFileMgr) {
        m_pFileMgr = MakeSharedPtr<SVFileMgr>(share());
    }
    //配置系统
    if (!m_pConfig) {
        m_pConfig = MakeSharedPtr<SVConfig>(share());
        m_pConfig->init();
    }
    //加载配置
    m_pConfig->loadConfig();
    //
    m_pGlobalParam = MakeSharedPtr<SVGlobalParam>( share() );
    m_pGlobalMgr = MakeSharedPtr<SVGlobalMgr>( share() );
    m_pGlobalMgr->init();
    //
    //test
    SVMtlCorePtr t_mtl = SVMtlLib::createMtl(share(), "scene.mtl");
    //
    m_svst = SV_ST_WAIT;
}

void SVInst::destroy() {
    m_pGlobalMgr = nullptr;
    m_pGlobalParam = nullptr;
    m_pFileMgr = nullptr;
    m_svst = SV_ST_NULL;
}

//创建渲染器
SVRendererPtr SVInst::createRM(SV_RM_TYPE _type) {
    if(_type == E_M_METAL) {
        m_pRM = MakeSharedPtr<SVRendererMetal>( share() );
    }else if(_type == E_M_GLES) {
        m_pRM = MakeSharedPtr<SVRendererGL>( share() );
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
    //m_pRPath->render(_dt);
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
    if(!m_pFileMgr) {
         m_pFileMgr = MakeSharedPtr<SVFileMgr>(share());
    }
    m_pFileMgr->addRespath(path);
}

void SVInst::setTimeState(SV_ENG_TIMESTATE _mode){
    m_engTimeState = _mode;
}

SV_ENG_TIMESTATE SVInst::getTimeState(){
    return m_engTimeState;
}

//
SVFileMgrPtr SVInst::getFileMgr(){
    return m_pFileMgr;
}

SVConfigPtr SVInst::getConfig(){
    return m_pConfig;
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

SVComDataPtr SVInst::getDataMgr(){
    if(!m_pGlobalMgr)
        return nullptr;
    return m_pGlobalMgr->m_pComData
;
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

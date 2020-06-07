//
// SVRenderMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderMgr.h"
#include "SVRenderScene.h"
#include "SVRenderCmd.h"
#include "SVRenderStream.h"
#include "SVRTarget.h"
#include "SVRenderPipline.h"
#include "SVRenderer.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVMtlCore.h"
#include "../work/SVTdCore.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVStaticData.h"
#include "../app/SVInst.h"

using namespace sv;

SVRenderMgr::SVRenderMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_mainRT = nullptr;
    m_preRT.clear();
    m_afterRT.clear();
    m_renderLock = MakeSharedPtr<SVLock>();
    m_logicLock = MakeSharedPtr<SVLock>();
    m_adaptMode = 0;
}

SVRenderMgr::~SVRenderMgr() {
    m_logicLock = nullptr;
    m_renderLock = nullptr;
}

void SVRenderMgr::init() {
}

void SVRenderMgr::destroy() {
    clear();
}

void SVRenderMgr::setMainRT(SVRTargetPtr _rt) {
    m_mainRT = _rt;
}

void SVRenderMgr::addRTarget(SVRTargetPtr _rt,bool _pre) {
    if(_pre) {
        m_preRT.append(_rt);    //push 前向
    }else{
        m_afterRT.append(_rt);
    }
}

SVRTargetPtr SVRenderMgr::getRTarget(cptr8 _name) {
    return nullptr;
}

//只关心渲染，不应该关心环境的切换 环境放到外面去调用

//这边应该又个渲染路径（RPath）的概念

void SVRenderMgr::render(){
    //前向RT
    for(s32 i=0;i<m_preRT.size();i++) {
        m_preRT[i]->render( mApp->getRenderer() );
    }
    //中间RT
    if( m_mainRT ) {
        m_mainRT->render(  mApp->getRenderer() );
    }
    //后向RT
    for(s32 i=0;i<m_afterRT.size();i++) {
        m_afterRT[i]->render(  mApp->getRenderer() );
    }
}

void SVRenderMgr::_sort() {
    //前向与后向都需要排序
    
}

void SVRenderMgr::_adapt() {
//    if(m_pRenderer) {
//        if(m_adaptMode == 0) {
//            //形变 填充
//            SVMtlCorePtr t_pMtl = MakeSharedPtr<SVMtlCore>(mApp, "screennor");
//            t_pMtl->setTexture(0,E_TEX_MAIN);    //那第一张纹理
//            t_pMtl->setBlendEnable(false);
//            t_pMtl->setBlendState(MTL_BLEND_ONE,MTL_BLEND_ZERO);
//            bool t_mirror = mApp->getConfig()->mirror;
//            if( !t_mirror ) {
//                t_pMtl->setTexcoordFlip(-1.0f, 1.0f);
//            }else {
//                t_pMtl->setTexcoordFlip(1.0f, 1.0f);
//            }
//            SVRenderCmdAdaptPtr t_cmd = MakeSharedPtr<SVRenderCmdAdapt>();
//            t_cmd->mTag = "adaptscene";
//            t_cmd->setRenderer(m_pRenderer);
//            t_cmd->setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//            t_cmd->setWinSize(mApp->m_pGlobalParam->m_inner_width,mApp->m_pGlobalParam->m_inner_height);
//            t_cmd->setMesh(mApp->getDataMgr()->m_screenMesh);
//            t_cmd->setMaterial(t_pMtl->clone());
//
//        }else if(m_adaptMode == 1) {
//            //非形变 固定
//
//        }else if(m_adaptMode == 2) {
//            //非形变 固定 内接
//
//        }else if(m_adaptMode == 3) {
//            //非形变 固定 外接
//        }
//    }
}

void SVRenderMgr::clear() {
    m_renderLock->lock();
    m_renderLock->unlock();
}


//这里相当于准备数据
void SVRenderMgr::swapData(){
//    m_logicLock->lock();
//    m_renderLock->lock();
////    //交换全局(逻辑流,渲染流)
////    if(m_pRenderScene && m_pRenderer){
////        //准备的cache推送到流中
////        for(s32 i=0;i<m_RStreamCache->m_cmdArray.size();i++){
////            m_RStreamCache->m_cmdArray[i]->setRenderer(m_pRenderer);
////            m_pRenderScene->pushCacheCmd(RST_BEGIN,m_RStreamCache->m_cmdArray[i]);
////        }
////        m_RStreamCache->clearSVRenderCmd();
////        //交换管线
////        m_pRenderScene->swapPipline();
////    }
//    m_renderLock->unlock();
//    m_logicLock->unlock();
}

void SVRenderMgr::pushRCmdCreate(SVRObjBasePtr _robj){
    m_logicLock->lock();
    if(_robj){
//        SVRCmdCreatePtr t_cmd= MakeSharedPtr<SVRCmdCreate>(_robj);
//        m_RStreamCache->addSVRenderCmd(t_cmd);
    }
    m_logicLock->unlock();
}

SVRenderScenePtr SVRenderMgr::getRenderScene() {
    return nullptr;
}

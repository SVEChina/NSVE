//
// SVOpCreate.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li，daming Li
//

#include "SVOpCreate.h"
#include "../app/SVInst.h"
#include "../app/SVGlobalParam.h"
#include "../core/SVSpine.h"
#include "../core/SVBMFont.h"
#include "../core/SVModel.h"
#include "../core/SVMesh3d.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMesh.h"
#include "../base/SVDataSwap.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/SVPickProcess.h"
#include "../basesys/SVPhysicsWorldMgr.h"
#include "../event/SVEventMgr.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVCameraNode.h"
#include "../node/SVFrameOutNode.h"
#include "../node/SVNodeVisit.h"
#include "../node/SVSkyNode.h"
#include "../node/SVSpriteNode.h"
#include "../node/SVBillboardNode.h"
#include "../node/SVParticlesNode.h"
#include "../node/SVFreeTypeNode.h"
#include "../node/SVBMFontNode.h"
#include "../node/SVSkinNode.h"
#include "../node/SVModelNode.h"
#include "../node/SVFrameAniNode.h"
#include "../file/SVParseMain.h"
#include "../file/SVBMFontLoader.h"
#include "../module/SVModuleSys.h"
#include "../module/SVModuleBase.h"
#include "../module/SVEffectPackage.h"
#include "../detect/SVDetectMgr.h"
#include "../detect/SVDetectBase.h"
#include "../physics/SVPhysicsWorld.h"
#include "../physics/bodies/SVPhysicsBodyRigid.h"
#include "../physics/shapes/SVPhysicsShapeBox.h"
#include "../physics/shapes/SVPhysicsShapeSphere.h"
#include "../physics/SVPhysicsSoftRigidWorld.h"
#include "../physics/bodies/SVPhysicsBodyRope.h"
#include "../physics/bodies/SVPhysicsBodyCloth.h"

using namespace sv;

//创建场景OP
SVOpCreateScene::SVOpCreateScene(SVInstPtr _app,cptr8 name)
: SVOpBase(_app) {
    m_scenename = name;
}

void SVOpCreateScene::_process(f32 dt) {
    //创建逻辑场景
    SVScenePtr t_pScene = MakeSharedPtr<SVScene>(mApp,m_scenename.c_str());
    if (t_pScene) {
        t_pScene->create(); //创建场景树
        mApp->getSceneMgr()->setScene(t_pScene);//设置主场景
    }
}


//删除逻辑场景OP
SVOpDestroyScene::SVOpDestroyScene(SVInstPtr _app,cptr8 name)
: SVOpBase(_app) {
    m_scenename = name;
}

void SVOpDestroyScene::_process(f32 dt) {
}

//
SVOpCameraControl::SVOpCameraControl(SVInstPtr _app, bool bOpen, s32 iResId)
: SVOpBase(_app)
, m_bOpen(bOpen)
, m_iResId(iResId) {
}

SVOpCameraControl::~SVOpCameraControl() {
    
}

void SVOpCameraControl::_process(f32 dt) {
    if (m_bOpen == true) {
//        SVNode *pCam = mApp->m_global_mgr->m_pNodeMgr->getNode(CAMERACONTROL);
//        if (pCam != NULL)
//            return;
//        pCam = mApp->m_global_mgr->m_pNodeMgr->pCreator->createNode(E_NT_CAMERACONTROLFP, "cameraControl");
//        pCam->setname(CAMERACONTROL);
//        mApp->m_global_mgr->m_pNodeMgr->addNode(pCam);
    }
}

//创建天空
SVOpCreateSkyDome::SVOpCreateSkyDome(SVInstPtr _app,cptr8 pStrPath,s32 resId)
: SVOpBase(_app)
, m_strPath(pStrPath)
,m_iResId(resId) {
}

SVOpCreateSkyDome::~SVOpCreateSkyDome() {
}

void SVOpCreateSkyDome::_process(f32 dt) {
}

//创建粒子节点
SVOpCreateParticle::SVOpCreateParticle(SVInstPtr _app,cptr8 pStrPath)
: SVOpBase(_app)
, m_strPath(pStrPath) {
}

SVOpCreateParticle::~SVOpCreateParticle() {
}

void SVOpCreateParticle::_process(f32 dt) {
}

//创建特效
SVOpCreateEffcet::SVOpCreateEffcet(SVInstPtr _app,cptr8 pStrPath)
: SVOpBase(_app)
, m_strPath(pStrPath) {
}

SVOpCreateEffcet::~SVOpCreateEffcet() {
}

void SVOpCreateEffcet::_process(f32 dt) {
    s32 len = m_strPath.size();
    s32 pos = m_strPath.rfind('/');
    SVString t_moduleName = SVString::substr(m_strPath.c_str(), pos+1, len - pos - 1);
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_moduleName.c_str());
    if (t_modulePtr == nullptr) {
        SVParseMain t_parssMain(mApp);
        t_modulePtr = t_parssMain.parse(m_strPath.c_str(),123);
        if (t_modulePtr) {
            t_modulePtr->setOpCallBack(m_pCB, m_obj);
            t_modulePtr->setModuleName(t_moduleName.c_str());
            t_modulePtr->open();
            mApp->getModuleSys()->regist(t_modulePtr, t_moduleName.c_str());
            if (m_pCB) {
                SVString msg = SVString::format("effectpackageloadsucceed_%s",t_moduleName.c_str());
                (*m_pCB)(msg.c_str(), m_obj);
            }
            SVEffectPackagePtr t_effectPackage = DYN_TO_SHAREPTR(SVEffectPackage, t_modulePtr);
            if (t_effectPackage) {
//                for (s32 i = 0; i<10; i++) {
//                    SVAniTexAttachmentPtr t_texAtt = t_effectPackage->getTexAttachment(i);
//                    if (t_texAtt) {
//                        SVAniTexAttachment::TEXATTACHSPARAM t_param = t_texAtt->getParam();
//                        if (m_pCB) {
//                            SVString msg = SVString::format("effectpackagetexattachment_%s_channel:%d_metadata:%s",t_moduleName.c_str(), i, t_param.matadata.c_str());
//                            (*m_pCB)(msg.c_str(), m_obj);
//                        }
//                    }
//                }
            }
            
        }else{
            if (m_pCB) {
                SVString msg = SVString::format("effectpackageloadfailed_%s",t_moduleName.c_str());
                (*m_pCB)(msg.c_str(), m_obj);
            }
        }
    }else{
        if (m_pCB) {
            SVString msg = SVString::format("effectpackageloadfailed_%s",t_moduleName.c_str());
            (*m_pCB)(msg.c_str(), m_obj);
        }
    }
}


SVOpTexAttachment::SVOpTexAttachment(SVInstPtr _app, cptr8 _strPath, s32 _channel, void *_data, s32 _width, s32 _height):SVOpBase(_app){
    m_strPath = _strPath;
    m_data = _data;
    m_width = _width;
    m_height = _height;
    m_channel = _channel;
}

SVOpTexAttachment::~SVOpTexAttachment(){
    
}

void SVOpTexAttachment::_process(f32 dt) {
    s32 len = m_strPath.size();
    s32 pos = m_strPath.rfind('/');
    SVString t_moduleName = SVString::substr(m_strPath.c_str(), pos+1, len - pos - 1);
    SVModuleBasePtr t_module = mApp->getModuleSys()->getModule(t_moduleName.c_str());
    if (t_module) {
        SVEffectPackagePtr t_effect = std::dynamic_pointer_cast<SVEffectPackage>(t_module);
//        if (t_effect) {
//            SVAniTexAttachmentPtr t_attachment = t_effect->getTexAttachment(m_channel);
//            if (t_attachment) {
//                t_attachment->setAttachmentTex(m_data, m_width, m_height);
//            }
//        }
    }
}


SVOpEngineResume::SVOpEngineResume(SVInstPtr _app) : SVOpBase(_app){
    
}

SVOpEngineResume::~SVOpEngineResume(){
    
}

void SVOpEngineResume::_process(f32 dt){
    mApp->resume();
}

SVOpEngineSuspend::SVOpEngineSuspend(SVInstPtr _app) : SVOpBase(_app){
    
}

SVOpEngineSuspend::~SVOpEngineSuspend(){
    
}

void SVOpEngineSuspend::_process(f32 dt){
    mApp->suspend();
}

SVOpPushFaceData::SVOpPushFaceData(SVInstPtr _app, void *_data)
: SVOpBase(_app){
    m_data = _data;
}

SVOpPushFaceData::~SVOpPushFaceData(){
    
}

void SVOpPushFaceData::_process(f32 dt){
    if( mApp->getDetectMgr() ) {
        SVDetectBasePtr t_detect = mApp->getDetectMgr()->getDetect();
        if( t_detect ) {
            t_detect->pushData(m_data);
        }
    }
}

//测试操作
SVOpCreateTest::SVOpCreateTest(SVInstPtr _app)
: SVOpBase(_app){
    
}

SVOpCreateTest::~SVOpCreateTest(){
    
}

void SVOpCreateTest::_process(f32 dt) {
    
}


//测试操作
SVOpCreateDebugFacePt::SVOpCreateDebugFacePt(SVInstPtr _app)
: SVOpBase(_app){

}

SVOpCreateDebugFacePt::~SVOpCreateDebugFacePt(){
    
}

void SVOpCreateDebugFacePt::_process(f32 dt) {    
}

SVOpCreateGameZCMgr::SVOpCreateGameZCMgr(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpCreateGameZCMgr::~SVOpCreateGameZCMgr(){
    
}

void SVOpCreateGameZCMgr::_process(f32 dt) {
//    SVString t_name = "sv_gamezc_module";
//    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
//    if (t_modulePtr == nullptr) {
//        t_modulePtr = MakeSharedPtr<zc::ZCMgr>(mApp);
//        t_modulePtr->init();
//        t_modulePtr->open();
//        mApp->getModuleSys()->regist(t_modulePtr, t_name.c_str());
//        if (m_pCB) {
//            (*m_pCB)("", m_obj);
//        }
//    }
}

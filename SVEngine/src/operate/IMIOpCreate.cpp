//
// IMIOpCreate.cpp
// IMIngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li，daming Li
//

#include "IMIOpCreate.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalParam.h"
#include "../core/IMISpine.h"
#include "../core/IMIBMFont.h"
#include "../core/IMIModel.h"
#include "../core/IMIMesh3d.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../base/IMIDataSwap.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIConfig.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIPickProcess.h"
#include "../basesys/IMIPhysicsWorldMgr.h"
#include "../event/IMIEventMgr.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMICameraNode.h"
#include "../node/IMIFrameOutNode.h"
#include "../node/IMINodeVisit.h"
#include "../node/IMISkyNode.h"
#include "../node/IMISpriteNode.h"
#include "../node/IMIBillboardNode.h"
#include "../node/IMIParticlesNode.h"
#include "../node/IMIFreeTypeNode.h"
#include "../node/IMIBMFontNode.h"
#include "../node/IMISkinNode.h"
#include "../node/IMIModelNode.h"
#include "../node/IMIFrameAniNode.h"
#include "../file/IMIParseMain.h"
#include "../file/IMIBMFontLoader.h"
#include "../module/IMIModuleSys.h"
#include "../module/IMIModuleBase.h"
#include "../module/IMIEffectPackage.h"
#include "../detect/IMIDetectMgr.h"
#include "../detect/IMIDetectBase.h"
#include "../physics/IMIPhysicsWorld.h"
#include "../physics/bodies/IMIPhysicsBodyRigid.h"
#include "../physics/shapes/IMIPhysicsShapeBox.h"
#include "../physics/shapes/IMIPhysicsShapeSphere.h"
#include "../physics/IMIPhysicsSoftRigidWorld.h"
#include "../physics/bodies/IMIPhysicsBodyRope.h"
#include "../physics/bodies/IMIPhysicsBodyCloth.h"

using namespace imi;

//创建场景OP
IMIOpCreateScene::IMIOpCreateScene(IMIInstPtr _app,cptr8 name)
: IMIOpBase(_app) {
    m_scenename = name;
}

void IMIOpCreateScene::_process(f32 dt) {
    //创建逻辑场景
    IMIScenePtr t_pScene = MakeSharedPtr<IMIScene>(mApp,m_scenename.c_str());
    if (t_pScene) {
        t_pScene->create(); //创建场景树
        mApp->getSceneMgr()->setScene(t_pScene);//设置主场景
    }
}


//删除逻辑场景OP
IMIOpDestroyScene::IMIOpDestroyScene(IMIInstPtr _app,cptr8 name)
: IMIOpBase(_app) {
    m_scenename = name;
}

void IMIOpDestroyScene::_process(f32 dt) {
}

//
IMIOpCameraControl::IMIOpCameraControl(IMIInstPtr _app, bool bOpen, s32 iResId)
: IMIOpBase(_app)
, m_bOpen(bOpen)
, m_iResId(iResId) {
}

IMIOpCameraControl::~IMIOpCameraControl() {
    
}

void IMIOpCameraControl::_process(f32 dt) {
    if (m_bOpen == true) {
//        IMINode *pCam = mApp->m_global_mgr->m_pNodeMgr->getNode(CAMERACONTROL);
//        if (pCam != NULL)
//            return;
//        pCam = mApp->m_global_mgr->m_pNodeMgr->pCreator->createNode(E_NT_CAMERACONTROLFP, "cameraControl");
//        pCam->setname(CAMERACONTROL);
//        mApp->m_global_mgr->m_pNodeMgr->addNode(pCam);
    }
}

//创建天空
IMIOpCreateSkyDome::IMIOpCreateSkyDome(IMIInstPtr _app,cptr8 pStrPath,s32 resId)
: IMIOpBase(_app)
, m_strPath(pStrPath)
,m_iResId(resId) {
}

IMIOpCreateSkyDome::~IMIOpCreateSkyDome() {
}

void IMIOpCreateSkyDome::_process(f32 dt) {
}

//创建粒子节点
IMIOpCreateParticle::IMIOpCreateParticle(IMIInstPtr _app,cptr8 pStrPath)
: IMIOpBase(_app)
, m_strPath(pStrPath) {
}

IMIOpCreateParticle::~IMIOpCreateParticle() {
}

void IMIOpCreateParticle::_process(f32 dt) {
}

//创建特效
IMIOpCreateEffcet::IMIOpCreateEffcet(IMIInstPtr _app,cptr8 pStrPath)
: IMIOpBase(_app)
, m_strPath(pStrPath) {
}

IMIOpCreateEffcet::~IMIOpCreateEffcet() {
}

void IMIOpCreateEffcet::_process(f32 dt) {
    s32 len = m_strPath.size();
    s32 pos = m_strPath.rfind('/');
    IMIString t_moduleName = IMIString::substr(m_strPath.c_str(), pos+1, len - pos - 1);
    IMIModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_moduleName.c_str());
    if (t_modulePtr == nullptr) {
        IMIParseMain t_parssMain(mApp);
        t_modulePtr = t_parssMain.parse(m_strPath.c_str(),123);
        if (t_modulePtr) {
            t_modulePtr->setOpCallBack(m_pCB, m_obj);
            t_modulePtr->setModuleName(t_moduleName.c_str());
            t_modulePtr->open();
            mApp->getModuleSys()->regist(t_modulePtr, t_moduleName.c_str());
            if (m_pCB) {
                IMIString msg = IMIString::format("effectpackageloadsucceed_%s",t_moduleName.c_str());
                (*m_pCB)(msg.c_str(), m_obj);
            }
            IMIffectPackagePtr t_effectPackage = DYN_TO_SHAREPTR(IMIffectPackage, t_modulePtr);
            if (t_effectPackage) {
//                for (s32 i = 0; i<10; i++) {
//                    IMIAniTexAttachmentPtr t_texAtt = t_effectPackage->getTexAttachment(i);
//                    if (t_texAtt) {
//                        IMIAniTexAttachment::TEXATTACHSPARAM t_param = t_texAtt->getParam();
//                        if (m_pCB) {
//                            IMIString msg = IMIString::format("effectpackagetexattachment_%s_channel:%d_metadata:%s",t_moduleName.c_str(), i, t_param.matadata.c_str());
//                            (*m_pCB)(msg.c_str(), m_obj);
//                        }
//                    }
//                }
            }
            
        }else{
            if (m_pCB) {
                IMIString msg = IMIString::format("effectpackageloadfailed_%s",t_moduleName.c_str());
                (*m_pCB)(msg.c_str(), m_obj);
            }
        }
    }else{
        if (m_pCB) {
            IMIString msg = IMIString::format("effectpackageloadfailed_%s",t_moduleName.c_str());
            (*m_pCB)(msg.c_str(), m_obj);
        }
    }
}


IMIOpTexAttachment::IMIOpTexAttachment(IMIInstPtr _app, cptr8 _strPath, s32 _channel, void *_data, s32 _width, s32 _height):IMIOpBase(_app){
    m_strPath = _strPath;
    m_data = _data;
    m_width = _width;
    m_height = _height;
    m_channel = _channel;
}

IMIOpTexAttachment::~IMIOpTexAttachment(){
    
}

void IMIOpTexAttachment::_process(f32 dt) {
    s32 len = m_strPath.size();
    s32 pos = m_strPath.rfind('/');
    IMIString t_moduleName = IMIString::substr(m_strPath.c_str(), pos+1, len - pos - 1);
    IMIModuleBasePtr t_module = mApp->getModuleSys()->getModule(t_moduleName.c_str());
    if (t_module) {
        IMIffectPackagePtr t_effect = std::dynamic_pointer_cast<IMIffectPackage>(t_module);
//        if (t_effect) {
//            IMIAniTexAttachmentPtr t_attachment = t_effect->getTexAttachment(m_channel);
//            if (t_attachment) {
//                t_attachment->setAttachmentTex(m_data, m_width, m_height);
//            }
//        }
    }
}


IMIOpEngineResume::IMIOpEngineResume(IMIInstPtr _app) : IMIOpBase(_app){
    
}

IMIOpEngineResume::~IMIOpEngineResume(){
    
}

void IMIOpEngineResume::_process(f32 dt){
    mApp->resume();
}

IMIOpEngineSuspend::IMIOpEngineSuspend(IMIInstPtr _app) : IMIOpBase(_app){
    
}

IMIOpEngineSuspend::~IMIOpEngineSuspend(){
    
}

void IMIOpEngineSuspend::_process(f32 dt){
    mApp->suspend();
}

IMIOpPushFaceData::IMIOpPushFaceData(IMIInstPtr _app, void *_data)
: IMIOpBase(_app){
    m_data = _data;
}

IMIOpPushFaceData::~IMIOpPushFaceData(){
    
}

void IMIOpPushFaceData::_process(f32 dt){
    if( mApp->getDetectMgr() ) {
        IMIDetectBasePtr t_detect = mApp->getDetectMgr()->getDetect();
        if( t_detect ) {
            t_detect->pushData(m_data);
        }
    }
}

//测试操作
IMIOpCreateTest::IMIOpCreateTest(IMIInstPtr _app)
: IMIOpBase(_app){
    
}

IMIOpCreateTest::~IMIOpCreateTest(){
    
}

void IMIOpCreateTest::_process(f32 dt) {
    
}


//测试操作
IMIOpCreateDebugFacePt::IMIOpCreateDebugFacePt(IMIInstPtr _app)
: IMIOpBase(_app){

}

IMIOpCreateDebugFacePt::~IMIOpCreateDebugFacePt(){
    
}

void IMIOpCreateDebugFacePt::_process(f32 dt) {    
}

IMIOpCreateGameZCMgr::IMIOpCreateGameZCMgr(IMIInstPtr _app) :  IMIOpBase(_app){
    
}

IMIOpCreateGameZCMgr::~IMIOpCreateGameZCMgr(){
    
}

void IMIOpCreateGameZCMgr::_process(f32 dt) {
//    IMIString t_name = "sv_gamezc_module";
//    IMIModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
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

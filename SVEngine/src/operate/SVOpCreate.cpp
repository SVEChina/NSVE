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
#include "../node/SVPatchNode.h"
#include "../node/SVModelNode.h"
#include "../node/SVFrameAniNode.h"
#include "../file/SVParseMain.h"
#include "../file/SVBMFontLoader.h"
#include "../file/SVLoaderGLTF.h"
#include "../module/SVModuleSys.h"
#include "../module/SVModuleBase.h"
#include "../module/SVDivisonFilter.h"
#include "../module/SVMark.h"
#include "../module/SVARAnchor.h"
#include "../module/SVEffectPackage.h"
#include "../module/pendraw/SVPenDraw.h"
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
    mApp->svResume();
}

SVOpEngineSuspend::SVOpEngineSuspend(SVInstPtr _app) : SVOpBase(_app){
    
}

SVOpEngineSuspend::~SVOpEngineSuspend(){
    
}

void SVOpEngineSuspend::_process(f32 dt){
    mApp->svSuspend();
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
    SVString t_name = "sv_aranchor_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr == nullptr) {
        t_modulePtr = MakeSharedPtr<SVARAnchor>(mApp);
        t_modulePtr->init();
        t_modulePtr->open();
        t_modulePtr->setOpCallBack(m_pCB, m_obj);
        mApp->getModuleSys()->regist(t_modulePtr, t_name.c_str());
    }
}


//测试操作
SVOpCreateDebugFacePt::SVOpCreateDebugFacePt(SVInstPtr _app)
: SVOpBase(_app){

}

SVOpCreateDebugFacePt::~SVOpCreateDebugFacePt(){
    
}

void SVOpCreateDebugFacePt::_process(f32 dt) {    
}


//测试操作
SVOpCreateTestLine::SVOpCreateTestLine(SVInstPtr _app)
: SVOpBase(_app){
    
}

SVOpCreateTestLine::~SVOpCreateTestLine(){
    
}

void SVOpCreateTestLine::_process(f32 dt) {
//    SVScenePtr t_pScene = mApp->getSceneMgr()->getScene();
//    if (t_pScene) {
//        SVMesh2DNodePtr t_lineNode = MakeSharedPtr<SVMesh2DNode>(mApp);
//        t_pScene->addNode(t_lineNode);
//        
//        f32 t_testLine[6] = {0, 300.0f, 0.0f, 200.0f, 300.0f, 0.0f};
//        SVPhysicsSoftRigidWorldPtr t_softWorld = mApp->getPhysicsWorldMgr()->getSoftWorld();
//        FVec3 t_from = FVec3(t_testLine[0], t_testLine[1], t_testLine[2]);
//        FVec3 t_to = FVec3(t_testLine[3], t_testLine[4], t_testLine[5]);
//        SVPhysicsBodyRopePtr t_bodyRope = MakeSharedPtr<SVPhysicsBodyRope>(mApp, t_softWorld->getWorldInfo(), t_from, t_to, 30, 1);
//        t_bodyRope->setTimeScale(2);
//        t_softWorld->addSoftBody(t_bodyRope);
//    }
}

//测试操作
SVOpCreateTestPatch::SVOpCreateTestPatch(SVInstPtr _app)
: SVOpBase(_app){
    
}

SVOpCreateTestPatch::~SVOpCreateTestPatch(){
}

void SVOpCreateTestPatch::_process(f32 dt) {
    SVScenePtr t_pScene = mApp->getSceneMgr()->getScene();
    if (t_pScene) {
        SVPatchNodePtr t_patchNode = MakeSharedPtr<SVPatchNode>(mApp);
        t_pScene->addNode(t_patchNode);
        
        //
        SVPhysicsSoftRigidWorldPtr t_softWorld = mApp->getPhysicsWorldMgr()->getSoftWorld();
        FVec3 t_corner00 = FVec3(-200.0, 60.0f, 0.0f);
        FVec3 t_corner10 = FVec3(200.0, 60.0f, 0.0f);
        FVec3 t_corner01 = FVec3(-200.0, 300.0f, 0.0f);
        FVec3 t_corner11 = FVec3(200.0, 300.0f, 0.0f);
        
        SVPhysicsBodyClothPtr t_bodyPatch = MakeSharedPtr<SVPhysicsBodyCloth>(mApp, t_softWorld->getWorldInfo(), t_corner00, t_corner10, t_corner01, t_corner11, 20, 20);
        t_bodyPatch->setTimeScale(3);
        t_softWorld->addSoftBody(t_bodyPatch);
}

////测试操作
//SVOpCreateTestMianSha::SVOpCreateTestMianSha(SVInstPtr _app)
//: SVOpBase(_app){
//
//}
//
//SVOpCreateTestMianSha::~SVOpCreateTestMianSha(){
//}
//
//void SVOpCreateTestMianSha::_process(f32 dt) {
//}

//SVOpCreateDivision::SVOpCreateDivision(SVInstPtr _app) :  SVOpBase(_app){
//    
//}
//
//SVOpCreateDivision::~SVOpCreateDivision(){
//    
//}
//
//void SVOpCreateDivision::_process(f32 dt) {
//    SVString t_name = "sv_filter_division";
//    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
//    if (t_modulePtr == nullptr) {
//        t_modulePtr = MakeSharedPtr<SVDivisonFilter>(mApp);
//        t_modulePtr->init();
//        t_modulePtr->open();
//        mApp->getModuleSys()->regist(t_modulePtr, t_name.c_str());
//    }
}
//about mark
SVOpCreateMark::SVOpCreateMark(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpCreateMark::~SVOpCreateMark(){
    
}

void SVOpCreateMark::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr == nullptr) {
        t_modulePtr = MakeSharedPtr<SVMark>(mApp);
        t_modulePtr->init();
        t_modulePtr->open();
        mApp->getModuleSys()->regist(t_modulePtr, t_name.c_str());
    }
}

SVOpMarkContent::SVOpMarkContent(SVInstPtr _app, SVString _content) :  SVOpBase(_app){
    m_content = _content;
}

SVOpMarkContent::~SVOpMarkContent(){
    
}

void SVOpMarkContent::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setContent(m_content);
    }
}

SVOpMarkAlpha::SVOpMarkAlpha(SVInstPtr _app, f32 _alpha) :  SVOpBase(_app){
    m_alpha = _alpha;
}

SVOpMarkAlpha::~SVOpMarkAlpha(){
    
}

void SVOpMarkAlpha::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setAlpha(m_alpha);
    }
}

SVOpMarkScale::SVOpMarkScale(SVInstPtr _app, f32 _scale) :  SVOpBase(_app){
    m_scale = _scale;
}

SVOpMarkScale::~SVOpMarkScale(){
    
}

void SVOpMarkScale::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setScale(m_scale);
    }
}

SVOpMarkRotation::SVOpMarkRotation(SVInstPtr _app, f32 _roation) :  SVOpBase(_app){
    m_rotation = _roation;
}

SVOpMarkRotation::~SVOpMarkRotation(){
    
}

void SVOpMarkRotation::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setRotation(m_rotation);
    }
}

SVOpMarkAlphaTime::SVOpMarkAlphaTime(SVInstPtr _app, f32 _alphaTime) :  SVOpBase(_app){
    m_alphaTime = _alphaTime;
}

SVOpMarkAlphaTime::~SVOpMarkAlphaTime(){
    
}

void SVOpMarkAlphaTime::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setAlphaTime(m_alphaTime);
    }
}

SVOpMarkAlphaRange::SVOpMarkAlphaRange(SVInstPtr _app, f32 _srcAlpha, f32 _tarAlpha) :  SVOpBase(_app){
    m_srcAlpha = _srcAlpha;
    m_tarAlpha = _tarAlpha;
}

SVOpMarkAlphaRange::~SVOpMarkAlphaRange(){
    
}

void SVOpMarkAlphaRange::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setAlphaRange(m_srcAlpha, m_tarAlpha);
    }
}

SVOpMarkAppearTime::SVOpMarkAppearTime(SVInstPtr _app, f32 _appearTime) :  SVOpBase(_app){
    m_appearTime = _appearTime;
}

SVOpMarkAppearTime::~SVOpMarkAppearTime(){
    
}

void SVOpMarkAppearTime::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setAppearRate(m_appearTime);
    }
}

SVOpMarkPosition::SVOpMarkPosition(SVInstPtr _app, FVec3 _pos) :  SVOpBase(_app){
    m_pos = _pos;
}

SVOpMarkPosition::~SVOpMarkPosition(){
    
}

void SVOpMarkPosition::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        f32 t_x = m_pos.x;
        f32 t_y = m_pos.y;
        s32 t_camera_w = mApp->m_global_param.m_sv_width;
        s32 t_camera_h = mApp->m_global_param.m_sv_height;
        f32 t_mod_x = t_x;
        f32 t_mod_y = t_camera_h - t_y;
        f32 t_n_targetX = t_mod_x - t_camera_w*0.5;
        f32 t_n_targetY =  t_camera_h*0.5 - t_mod_y;
        t_mark->setPosition(t_n_targetX, t_n_targetY, 0.0f);
    }
}

SVOpMarkEnableRandom::SVOpMarkEnableRandom(SVInstPtr _app, bool _enable) :  SVOpBase(_app){
    m_enable = _enable;
}

SVOpMarkEnableRandom::~SVOpMarkEnableRandom(){
    
}

void SVOpMarkEnableRandom::_process(f32 dt) {
    SVString t_name = "sv_mark_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    SVMarkPtr t_mark = DYN_TO_SHAREPTR(SVMark, t_modulePtr);
    if (t_mark) {
        t_mark->setEnableRandomPosition(m_enable);
    }
}

//about pen
SVOpOpenPen::SVOpOpenPen(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpOpenPen::~SVOpOpenPen(){
    
}

void SVOpOpenPen::_process(f32 dt) {
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr == nullptr) {
        t_modulePtr = MakeSharedPtr<SVPenDraw>(mApp);
        SVGameBasePtr gameBasePtr = DYN_TO_SHAREPTR(SVGameBase, t_modulePtr);
        if (gameBasePtr) {
            gameBasePtr->init(nullptr, nullptr, nullptr);
            gameBasePtr->open();
            mApp->getModuleSys()->regist(gameBasePtr, t_name.c_str());
        }

    }
}

SVOpSetPenEffcet::SVOpSetPenEffcet(SVInstPtr _app,cptr8 pStrPath)
: SVOpBase(_app)
, m_strPath(pStrPath) {
}

SVOpSetPenEffcet::~SVOpSetPenEffcet() {
}

void SVOpSetPenEffcet::_process(f32 dt) {
//    SVString t_name = "sv_pen_module";
//    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
//    if (t_modulePtr) {
//        SVParsePen t_parssPen(mApp);
//        t_parssPen.parse(m_strPath.c_str(),123);
//    }
}


SVOpSavePenEffcet::SVOpSavePenEffcet(SVInstPtr _app,cptr8 pStrPath)
: SVOpBase(_app)
, m_strPath(pStrPath) {
}

SVOpSavePenEffcet::~SVOpSavePenEffcet() {
}

void SVOpSavePenEffcet::_process(f32 dt) {
    SVString result = "false";
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            if (t_penDraw->save(m_strPath)) {
                result = "true";
            }
        }
    }
    if (m_pCB) {
        (*m_pCB)(result, mApp.get());
    }
}

SVOpClearPen::SVOpClearPen(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpClearPen::~SVOpClearPen(){
    
}

void SVOpClearPen::_process(f32 dt) {
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            t_penDraw->clear();
        }
    }
}

SVOpPenUndo::SVOpPenUndo(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpPenUndo::~SVOpPenUndo(){
    
}

void SVOpPenUndo::_process(f32 dt) {
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            t_penDraw->undo();
        }
    }
}

SVOpPenRedo::SVOpPenRedo(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpPenRedo::~SVOpPenRedo(){
    
}

void SVOpPenRedo::_process(f32 dt) {
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            t_penDraw->redo();
        }
    }
}

SVOpPenUndoIsEnable::SVOpPenUndoIsEnable(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpPenUndoIsEnable::~SVOpPenUndoIsEnable(){
    
}

void SVOpPenUndoIsEnable::_process(f32 dt) {
    SVString result = "false";
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            if (t_penDraw->isUndoEnable()) {
                result = "true";
            }
        }
    }
    if (m_pCB) {
        (*m_pCB)(result, m_obj);
    }
}

SVOpPenRedoIsEnable::SVOpPenRedoIsEnable(SVInstPtr _app) :  SVOpBase(_app){
    
}

SVOpPenRedoIsEnable::~SVOpPenRedoIsEnable(){
    
}

void SVOpPenRedoIsEnable::_process(f32 dt) {
    SVString result = "false";
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            if (t_penDraw->isRedoEnable()) {
                result = "true";
            }
        }
    }
    if (m_pCB) {
        (*m_pCB)(result, m_obj);
    }
}

SVOpPenMode::SVOpPenMode(SVInstPtr _app, s32 _mode) :  SVOpBase(_app){
    m_mode = _mode;
}

SVOpPenMode::~SVOpPenMode(){
    
}

void SVOpPenMode::_process(f32 dt) {
    SVString result = "false";
    SVString t_name = "sv_pen_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        SVPenDrawPtr t_penDraw = DYN_TO_SHAREPTR(SVPenDraw, t_modulePtr);
        if (t_penDraw) {
            t_penDraw->setPenMode(SVPENMODE(m_mode));
        }
    }
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

SVOpEnableTouchAnchor::SVOpEnableTouchAnchor(SVInstPtr _app)
: SVOpBase(_app){
    
}

SVOpEnableTouchAnchor::~SVOpEnableTouchAnchor(){
    
}

void SVOpEnableTouchAnchor::_process(f32 dt) {
    SVString t_name = "sv_aranchor_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr == nullptr) {
        t_modulePtr = MakeSharedPtr<SVARAnchor>(mApp);
        t_modulePtr->init();
        t_modulePtr->open();
        t_modulePtr->setOpCallBack(m_pCB, m_obj);
        mApp->getModuleSys()->regist(t_modulePtr, t_name.c_str());
    }
}

SVOpDisableTouchAnchor::SVOpDisableTouchAnchor(SVInstPtr _app)
: SVOpBase(_app){
    
}

SVOpDisableTouchAnchor::~SVOpDisableTouchAnchor(){
    
}

void SVOpDisableTouchAnchor::_process(f32 dt) {
    SVString t_name = "sv_aranchor_module";
    SVModuleBasePtr t_modulePtr = mApp->getModuleSys()->getModule(t_name.c_str());
    if (t_modulePtr) {
        t_modulePtr->close();
        t_modulePtr->destroy();
        mApp->getModuleSys()->unregist(t_name.c_str());
    }
}

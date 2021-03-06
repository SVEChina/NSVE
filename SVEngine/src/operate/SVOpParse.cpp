//
// SVOpParse.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVOpParse.h"
#include "../work/SVThreadPool.h"
#include "../basesys/SVSceneMgr.h"
#include "../file/SVParseMain.h"
#include "../node/SVNodeVisit.h"
#include "../basesys/SVScene.h"
#include "../event/SVEvent.h"
#include "../event/SVEventMgr.h"
#include "../app/SVInst.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../file/SVParseData.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderMgr.h"
#include "../module/SVModuleBase.h"

using namespace sv;

SVOpParse::SVOpParse(SVInstPtr _app, s32 _resid, cptr8 _path )
: SVOpBase(_app) {
    resid = _resid;
    path = _path;
    restype = 0;
}

SVOpParse::SVOpParse(SVInstPtr _app, s32 _resid,  cptr8 _path,s32 _restype)
: SVOpBase(_app) {
    resid = _resid;
    path = _path;
    restype = _restype;
}


void SVOpParse::_process(f32 dt) {
//    mApp->m_config.loadEffectIsScreen=false;
//    //清理特效
//    SVOpFilterEftPtr t_op = MakeSharedPtr<SVOpFilterEft>(mApp, restype, resid);
//    mApp->m_pTPool->getMainThread()->pushThreadOp(t_op);
//    //
//    SVParseMain t_parseMain(mApp);
//    t_parseMain.parseTexHeadStream(&tesHeadSet);
//    
//    if (hasHeadSet && tesHeadSet.size() > 0) {
//        t_parseMain.parseTexHeadStream(&tesHeadSet);
//    }
//    //
//    bool loadSuccess = t_parseMain.parse(path.c_str(), resid);
//    //
//    SVParseEventPtr t_event = MakeSharedPtr<SVParseEvent>();
//    t_event->isloadEffect = loadSuccess;
//    t_event->resid = resid;
//    mApp->getEventMgr()->pushEvent(t_event);
}

//
SVOperateDelEft::SVOperateDelEft(SVInstPtr _app, s32 _resid)
: SVOpBase(_app) {
    resid = _resid;
}

void SVOperateDelEft::_process(f32 dt) {
    SVScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if(t_scene){
    }
}

//
SVOpSaveEft::SVOpSaveEft(SVInstPtr _app, s32 _resid, cptr8 _path)
: SVOpBase(_app) {
    resid = _resid;
    path = _path;
}

void SVOpSaveEft::_process(f32 dt) {
    SVVisitCollectResID visit(resid);
    SVScenePtr t_scene = mApp->getSceneMgr()->getScene();
}

SVOpFilterEft::SVOpFilterEft(SVInstPtr _app, s32 _resType, s32 _resId)
: SVOpBase(_app) {
    resType = _resType;
    resId = _resId;
}

void SVOpFilterEft::_process(f32 dt) {
//    //清理等待挂在到主线程中的任务
//    if (mApp->m_global_mgr->m_pDiySys->detectResType(resType)) {
//        int t_oldresid = mApp->m_global_mgr->m_pDiySys->setResType(resType, resId);
//        if (t_oldresid != -1) {
//            SVScene* t_scene = mApp->getSceneMgr()->getScene();
//            if(t_scene){
//                SVVisitCollectResID visit(resId);
//                t_scene->deep_visit(&visit);
//            }
//        }
//    }
}

//生成节点
SVOpGenerate::SVOpGenerate(SVInstPtr _app, SVParseDataPtr _parsedataPtr, s32 _resid,cptr8 _path)
: SVOpBase(_app) {
    mParseDataPtr = _parsedataPtr;
    mResid = _resid;
    mPath = _path;
}

void SVOpGenerate::_process(f32 dt) {
    if (mParseDataPtr) {
        //主线程生成节点
        mParseDataPtr->generate(mResid,mPath.c_str());
        mParseDataPtr->suspend();
    }
}

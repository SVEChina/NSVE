//
// IMIOpParse.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpParse.h"
#include "../work/IMIThreadPool.h"
#include "../basesys/IMISceneMgr.h"
#include "../file/IMIParseMain.h"
#include "../node/IMINodeVisit.h"
#include "../basesys/IMIScene.h"
#include "../event/IMIEvent.h"
#include "../event/IMIEventMgr.h"
#include "../app/IMIInst.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../file/IMIParseData.h"
#include "../basesys/IMIConfig.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../module/IMIModuleBase.h"

using namespace imi;

IMIOpParse::IMIOpParse(IMIInstPtr _app, s32 _resid, cptr8 _path )
: IMIOpBase(_app) {
    resid = _resid;
    path = _path;
    restype = 0;
}

IMIOpParse::IMIOpParse(IMIInstPtr _app, s32 _resid,  cptr8 _path,s32 _restype)
: IMIOpBase(_app) {
    resid = _resid;
    path = _path;
    restype = _restype;
}


void IMIOpParse::_process(f32 dt) {
//    mApp->m_config.loadEffectIsScreen=false;
//    //清理特效
//    IMIOpFilterEftPtr t_op = MakeSharedPtr<IMIOpFilterEft>(mApp, restype, resid);
//    mApp->m_pTPool->getMainThread()->pushThreadOp(t_op);
//    //
//    IMIParseMain t_parseMain(mApp);
//    t_parseMain.parseTexHeadStream(&tesHeadSet);
//    
//    if (hasHeadSet && tesHeadSet.size() > 0) {
//        t_parseMain.parseTexHeadStream(&tesHeadSet);
//    }
//    //
//    bool loadSuccess = t_parseMain.parse(path.c_str(), resid);
//    //
//    IMIParseEventPtr t_event = MakeSharedPtr<IMIParseEvent>();
//    t_event->isloadEffect = loadSuccess;
//    t_event->resid = resid;
//    mApp->getEventMgr()->pushEvent(t_event);
}

//
IMIOperateDelEft::IMIOperateDelEft(IMIInstPtr _app, s32 _resid)
: IMIOpBase(_app) {
    resid = _resid;
}

void IMIOperateDelEft::_process(f32 dt) {
    IMIScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if(t_scene){
    }
}

//
IMIOpSaveEft::IMIOpSaveEft(IMIInstPtr _app, s32 _resid, cptr8 _path)
: IMIOpBase(_app) {
    resid = _resid;
    path = _path;
}

void IMIOpSaveEft::_process(f32 dt) {
    IMIVisitCollectResID visit(resid);
    IMIScenePtr t_scene = mApp->getSceneMgr()->getScene();
}

IMIOpFilterEft::IMIOpFilterEft(IMIInstPtr _app, s32 _resType, s32 _resId)
: IMIOpBase(_app) {
    resType = _resType;
    resId = _resId;
}

void IMIOpFilterEft::_process(f32 dt) {
//    //清理等待挂在到主线程中的任务
//    if (mApp->m_global_mgr->m_pDiySys->detectResType(resType)) {
//        int t_oldresid = mApp->m_global_mgr->m_pDiySys->setResType(resType, resId);
//        if (t_oldresid != -1) {
//            IMIScene* t_scene = mApp->getSceneMgr()->getScene();
//            if(t_scene){
//                IMIVisitCollectResID visit(resId);
//                t_scene->deep_visit(&visit);
//            }
//        }
//    }
}

//生成节点
IMIOpGenerate::IMIOpGenerate(IMIInstPtr _app, IMIParseDataPtr _parsedataPtr, s32 _resid,cptr8 _path)
: IMIOpBase(_app) {
    mParseDataPtr = _parsedataPtr;
    mResid = _resid;
    mPath = _path;
}

void IMIOpGenerate::_process(f32 dt) {
    if (mParseDataPtr) {
        //主线程生成节点
        mParseDataPtr->generate(mResid,mPath.c_str());
        mParseDataPtr->suspend();
    }
}

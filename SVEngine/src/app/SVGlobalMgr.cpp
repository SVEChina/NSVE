//
// SVGlobalMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVGlobalMgr.h"
#include "SVInst.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/script/SVPythonSys.h"
#include "../basesys/SVFontProcess.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVCameraMgr.h"
#include "../basesys/SVComData.h"
#include "../basesys/SVDeformMgr.h"
#include "../basesys/SVModelMgr.h"
#include "../basesys/SVPhysicsWorldMgr.h"
#include "../module/SVModuleSys.h"
#include "../light/SVLightSys.h"
#include "../event/SVEventMgr.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVShaderMgr.h"
#include "../mtl/SVMtlLib.h"
#include "../detect/SVDetectMgr.h"
#include "../rendercore/SVRenderMgr.h"
#include "../act/SVActionMgr.h"
#include "../base/svstr.h"
#include <sys/time.h>
//#include <Python/Python.h>

using namespace sv;

SVGlobalMgr::SVGlobalMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    //引擎系统和操作指令系统要先建立起来
    m_pEventMgr = nullptr;
    m_pBasicSys = nullptr;
    m_pSceneMgr = nullptr;
    m_pCameraMgr = nullptr;
    m_pShaderMgr = nullptr;
    m_pTexMgr = nullptr;
    m_pRenderMgr = nullptr;
    m_pDetectMgr = nullptr;
    m_pComData = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_pMtlLib = nullptr;
    
    //SVMtlLibPtr m_pMtlLib;
}

SVGlobalMgr::~SVGlobalMgr() {
    m_pEventMgr = nullptr;
    m_pBasicSys = nullptr;
    m_pSceneMgr = nullptr;
    m_pCameraMgr = nullptr;
    m_pShaderMgr = nullptr;
    m_pTexMgr = nullptr;
    m_pRenderMgr = nullptr;
    m_pDetectMgr = nullptr;
    m_pComData = nullptr;
    m_pModelMgr = nullptr;
    m_pDeformSys = nullptr;
    m_pPhysicSys =nullptr;
    m_pLightSys = nullptr;
    m_pMtlLib = nullptr;
}

void SVGlobalMgr::init() {
    //渲染管理
    m_pRenderMgr = MakeSharedPtr<SVRenderMgr>(mApp);
    m_pRenderMgr->init();
    SV_LOG_ERROR("sve init m_pRenderMgr end!\n");
    //构建静态数据
    m_pComData = MakeSharedPtr<SVComData>(mApp);
    m_pComData->init();
    SV_LOG_ERROR("sve init m_pComData end!\n");
//    //消息系统建立起来
//    m_pEventMgr = MakeSharedPtr<SVEventMgr>(mApp);
//    m_pEventMgr->init();
//    //基础系统
//    m_pBasicSys = MakeSharedPtr<SVBasicSys>(mApp));
//    m_pBasicSys->init();
//    //
//    m_pPythonSys = MakeSharedPtr<SVPythonSys>(mApp));
//    m_pPythonSys->init();
    //相机系统
    m_pCameraMgr = MakeSharedPtr<SVCameraMgr>(mApp);
    m_pCameraMgr->init();
//    //灯光系统
//    m_pLightSys = MakeSharedPtr<SVLightSys>(mApp);
//    m_pLightSys->init();
//    //组件系统
//    m_pModuleSys = MakeSharedPtr<SVModuleSys>(mApp));
//    m_pModuleSys->init();
    //纹理管理器初始化
    m_pTexMgr = MakeSharedPtr<SVTexMgr>(mApp);
    m_pTexMgr->init();
    SV_LOG_ERROR("sve init m_pTexMgr end!\n");
    //shader程序初始化
    m_pShaderMgr = MakeSharedPtr<SVShaderMgr>(mApp);
    m_pShaderMgr->init();
    SV_LOG_ERROR("sve init m_pShaderMgr end!\n");
    //场景系统
    m_pSceneMgr = MakeSharedPtr<SVSceneMgr>(mApp);
    m_pSceneMgr->init();
    SV_LOG_ERROR("sve init SVSceneMgr end!\n");
    //材质库
    m_pMtlLib = MakeSharedPtr<SVMtlLib>(mApp);
    m_pMtlLib->init();
    SV_LOG_ERROR("sve init SVMtlLib end! \n");
//    //模型管理部分
//    m_pModelMgr = MakeSharedPtr<SVModelMgr>(mApp.get());
//    m_pModelMgr->init();

//    //创建识别对象成功
//    m_pDetectMgr = MakeSharedPtr<SVDetectMgr>(mApp.get());
//    m_pDetectMgr->init(DETECT_T_ST);
//    //变形系统
//    m_pDeformSys = MakeSharedPtr<SVDeformMgr>(mApp.get());
//    m_pDeformSys->init();
//    //
//    m_pPhysicSys = MakeSharedPtr<SVPhysicsWorldMgr>(mApp.get());
//    m_pPhysicSys->init();
//    //加载默认字体
//    m_pBasicSys->loadDefaultFMFont();
}

void SVGlobalMgr::destroy() {
//    if (m_pDetectMgr) {
//        //识别模块
//        m_pDetectMgr->destroy();
//        SV_LOG_ERROR("SVDetectMgr:destroy sucess");
//    }
    //相机析构
    if (m_pCameraMgr) {
        //要先析构相机上的节点，才能析构场景
        m_pCameraMgr->destroy();
        SV_LOG_ERROR("SVCameraMgr:destroy sucess");
    }
    //场景析构
    if (m_pSceneMgr) {
        //场景析够(场景虽然也是节点 但是需要单独管理,因为节点需要挂在场景上,所以在节点没析够前,场景不能析构掉)
        m_pSceneMgr->destroy();
        SV_LOG_ERROR("SVSceneMgr:destroy sucess");
    }

    //纹理析够 析构都要用到渲染模块
    if (m_pTexMgr) {
        m_pTexMgr->destroy();
        SV_LOG_ERROR("SVTexMgr:destroy sucess");
    }
    //shader析构
    if (m_pShaderMgr) {
        //shader 析构都要用到渲染模块
        m_pShaderMgr->destroy();
        SV_LOG_ERROR("SVShaderMgr:destroy sucess");
    }
//    //模型析构
//    if (m_pModelMgr) {
//        m_pModelMgr->destroy();
//        SV_LOG_ERROR("SVModelMgr:destroy sucess");
//    }
//    //组件系统析构
//    if(m_pModuleSys) {
//        m_pModuleSys->destroy();
//        SV_LOG_ERROR("m_pModuleSys:destroy sucess");
//    }
    if (m_pRenderMgr) {
        //渲染析够
        m_pRenderMgr->destroy();
        SV_LOG_ERROR("SVRenderMgr:destroy sucess");
    }
//    if(m_pBasicSys){
//        //基础系统
//        m_pBasicSys->destroy();
//        SV_LOG_ERROR("SVBasicSys:destroy sucess");
//    }
//    if (m_pEventMgr) {
//        //事件系统最后析够,因为很多其他模块 会注册监听事件
//        m_pEventMgr->destroy();
//        SV_LOG_ERROR("SVEventMgr:destroy sucess");
//    }
//    if (m_pConfig) {
//        //配置系统析够
//        m_pConfig->destroy();
//        SV_LOG_ERROR("SVConfig:destroy sucess");
//    }
//    if(m_pDeformSys){
//        //
//        m_pDeformSys->destroy();
//        SV_LOG_ERROR("m_pDeformSys:destroy sucess");
//    }
//    if(m_pPhysicSys){
//        //物理销毁
//        m_pPhysicSys->destroy();
//        SV_LOG_ERROR("m_pPhysics:destroy sucess");
//    }
//    
//    if(m_pLightSys) {
//        //灯光销毁
//        m_pLightSys->destroy();
//        SV_LOG_ERROR("m_pLightSys:destroy sucess");
//    }
}

void SVGlobalMgr::update(f32 dt) {
//    //
//    m_pDetectMgr->update(dt);           //识别数据新更新
//    timeTag(false,"detect cost");
//    //
//    m_pModuleSys->update(dt);           //组件系统更新
//    timeTag(false,"module cost");
//    m_pBasicSys->update(dt);            //基础系统更新
//    timeTag(false,"basesys cost");
//    m_pEventMgr->update(dt);            //事件处理系统更新
//    timeTag(false,"event cost");
//    m_pModelMgr->update(dt);            //模型管理
//    timeTag(false,"model cost");
//    m_pPhysicSys->update(dt);             //物理更新
//    timeTag(false,"physics cost");
    if(m_pCameraMgr) {
        //相机更新
        m_pCameraMgr->update(dt);
        timeTag(false,"camera cost");
    }
//    m_pLightSys->update(dt);            //灯光系统更新
//    timeTag(false,"light cost");
    if(m_pSceneMgr) {
        //场景更新(节点系统)
        m_pSceneMgr->update(dt);
        timeTag(false,"scene cost");
    }
//    m_pDeformSys->update(dt);           //变形更新
//    timeTag(false,"deform cost");
//    m_pTexMgr->update(dt);              //删除不用的纹理
//    timeTag(false,"texmgr cost");
}

void SVGlobalMgr::timeTag(bool _clear,cptr8 _tag){
    if(_clear){
        gettimeofday(&timTagLast, nullptr);
        SV_LOG_INFO("timeTag reset %s \n",_tag);
    }else{
        timeval timTagCur;
        gettimeofday(&timTagCur, nullptr);
        s32 dt = s32((timTagCur.tv_sec - timTagLast.tv_sec) * 1000.0f + (timTagCur.tv_usec - timTagLast.tv_usec) * 0.001f);
        timTagLast = timTagCur;
        SV_LOG_INFO("timeTag %d %s\n",dt,_tag);
    }
}

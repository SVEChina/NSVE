//
// SVDispatch.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDispatch.h"
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

void SVDispatch::dispatchShaderCreate(SVInstPtr _app,SVRShaderPtr _shader) {
    //投体到renderMgr的创建队列中
    _app->getRenderMgr()->pushRCmdCreate(nullptr);
}

//投递mesh create
void SVDispatch::dispatchMeshCreate(SVInstPtr _app,SVRMeshPtr _mesh) {
    
}

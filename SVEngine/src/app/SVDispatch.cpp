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

void SVDispatch::dispatchShaderCreate(SVInstPtr _app,SVShaderPtr _shader) {
    //投体到renderMgr的创建队列中
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _shader) {
        //
        SVRShaderPtr t_rshader = t_renderer->createResShader() ;
        t_rshader->m_logic_obj = _shader;
        _shader->bindRes(t_rshader);
        //
        SVRCmdCreatePtr t_cmd = MakeSharedPtr<SVRCmdCreate>(_shader);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchMeshCreate(SVInstPtr _app,SVRenderMeshPtr _mesh) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _mesh) {
        //
        SVRBufferPtr t_rbuffer = t_renderer->createResBuf() ;
        t_rbuffer->m_logic_obj = _mesh;
        _mesh->bindRes(t_rbuffer);
        //
        SVRCmdCreatePtr t_cmd = MakeSharedPtr<SVRCmdCreate>(t_rbuffer);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTextureCreate(SVInstPtr _app,SVTexturePtr _tex) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer) {
        //
        SVRTexPtr t_rtex = t_renderer->createResTexture() ;
        t_rtex->m_logic_obj = _tex;
        _tex->bindRes(t_rtex);
        //
        SVRCmdCreatePtr t_cmd = MakeSharedPtr<SVRCmdCreate>(t_rtex);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTargetCreate(SVInstPtr _app,SVRTargetPtr _target) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer) {
        //
        SVRFboPtr t_rfbo = t_renderer->createResFbo() ;
        t_rfbo->m_logic_obj = _target;
        _target->bindRes(t_rfbo);
        //
        SVRCmdCreatePtr t_cmd = MakeSharedPtr<SVRCmdCreate>(t_rfbo);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

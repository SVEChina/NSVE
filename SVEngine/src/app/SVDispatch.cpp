//
// SVDispatch.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDispatch.h"
#include "SVInst.h"
#include "../rendercore/SVRenderCmdRes.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVShader.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRShader.h"
#include "../rendercore/SVRFbo.h"
#include "../rendercore/SVRTex.h"

using namespace sv;

void SVDispatch::dispatchShaderCreate(SVInstPtr _app,SVShaderPtr _shader) {
    //投体到renderMgr的创建队列中
    if(_shader) {
        SVRCmdCreateShaderPtr t_cmd = MakeSharedPtr<SVRCmdCreateShader>(_shader);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchMeshCreate(SVInstPtr _app,SVRenderMeshPtr _mesh) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(_mesh) {
        SVRCmdCreateMeshPtr t_cmd = MakeSharedPtr<SVRCmdCreateMesh>(_mesh);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTextureCreate(SVInstPtr _app,SVTexturePtr _tex) {
    if(_tex) {
        SVRCmdCreateTexPtr t_cmd = MakeSharedPtr<SVRCmdCreateTex>(_tex);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTargetCreate(SVInstPtr _app,SVRTargetPtr _target) {
    if(_target) {
        SVRCmdCreateFboPtr t_cmd = MakeSharedPtr<SVRCmdCreateFbo>(_target);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTargetResize(SVInstPtr _app,SVRTargetPtr _target) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        SVRFboPtr t_rfbo = _target->getResFbo() ;
        if(t_rfbo) {
            //
            s32 t_w = _target->getTargetDsp()->m_width;
            s32 t_h = _target->getTargetDsp()->m_height;
            SVRenderCmdFboResizePtr t_cmd = MakeSharedPtr<SVRenderCmdFboResize>(t_rfbo,t_w,t_h);
            _app->getRenderMgr()->pushRCmdCreate(t_cmd);
        }
    }
}

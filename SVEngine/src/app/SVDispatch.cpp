//
// SVDispatch.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDispatch.h"
#include "SVInst.h"
#include "../rendercore/SVRenderCmdRes.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVShader.h"
#include "../mtl/SVSurface.h"
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
        SVRCmdCreateTargetPtr t_cmd = MakeSharedPtr<SVRCmdCreateTarget>(_target);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void SVDispatch::dispatchTargetResize(SVInstPtr _app,SVRTargetPtr _target) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        SVRFboPtr t_rfbo = _target->getResFbo() ;
        if(t_rfbo) {
            s32 t_w = _target->getTargetDsp()->m_width;
            s32 t_h = _target->getTargetDsp()->m_height;
            SVRCmdTargetResizePtr t_cmd = MakeSharedPtr<SVRCmdTargetResize>(t_rfbo,t_w,t_h);
            _app->getRenderMgr()->pushRCmdCreate(t_cmd);
        }
    }
}

//投递rendermesh
void SVDispatch::dispatchMeshDraw(SVInstPtr _app,
                                  SVRenderMeshPtr _mesh,
                                  SVMtlCorePtr _mtl,
                                  SVSurfacePtr _surface,
                                  SV_RSTREAM _stype) {
    
    SVRendererPtr t_renderer = _app->getRenderer();
    SVRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target) {
        //投递到主目标，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        //投递命令
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommand(t_cmd_nor,_stype);
        }
    }
}

//投递rendermesh
void SVDispatch::dispatchMeshDraw(SVInstPtr _app,
                                  SVRenderMeshPtr _mesh,
                                  SVMtlCorePtr _mtl,
                                  SVSurfacePtr _surface,
                                  SVRTargetPtr _target,
                                  SV_RSTREAM _stype) {
    
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommand(t_cmd_nor,_stype);
        }
    }
}

//投递rendermesh-pre
void SVDispatch::dispatchMeshDrawPre(SVInstPtr _app,
                                     SVRenderMeshPtr _mesh,
                                     SVMtlCorePtr _mtl,
                                     SVSurfacePtr _surface) {
    SVRendererPtr t_renderer = _app->getRenderer();
    SVRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target ) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommandPre(t_cmd_nor);
        }
    }
}

//投递rendermesh-pre
void SVDispatch::dispatchMeshDrawPre(SVInstPtr _app,
                                     SVRenderMeshPtr _mesh,
                                     SVMtlCorePtr _mtl,
                                     SVSurfacePtr _surface,
                                     SVRTargetPtr _target) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommandPre(t_cmd_nor);
        }
    }
}

//投递rendermesh-pre
void SVDispatch::dispatchMeshDrawAfter(SVInstPtr _app,
                                       SVRenderMeshPtr _mesh,
                                       SVMtlCorePtr _mtl,
                                       SVSurfacePtr _surface) {
    SVRendererPtr t_renderer = _app->getRenderer();
    SVRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target ) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommandAfter(t_cmd_nor);
        }
    }
}

//投递rendermesh-after
void SVDispatch::dispatchMeshDrawAfter(SVInstPtr _app,
                                       SVRenderMeshPtr _mesh,
                                       SVMtlCorePtr _mtl,
                                       SVSurfacePtr _surface,
                                       SVRTargetPtr _target) {
    SVRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matp", t_mat_p);
        }
        if(_mtl) {
            SVRCmdNorPtr t_cmd_nor = MakeSharedPtr<SVRCmdNor>();
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommandAfter(t_cmd_nor);
        }
    }
}

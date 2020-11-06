//
// IMIDispatch.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIDispatch.h"
#include "IMIInst.h"
#include "../rendercore/IMIRenderCmdRes.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIShader.h"
#include "../mtl/IMISurface.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderPath.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRShader.h"
#include "../rendercore/IMIRFbo.h"
#include "../rendercore/IMIRTex.h"

using namespace imi;

void IMIDispatch::dispatchShaderCreate(IMIInstPtr _app,IMIShaderPtr _shader) {
    //投体到renderMgr的创建队列中
    if(_shader) {
        IMIRCmdCreateShaderPtr t_cmd = MakeSharedPtr<IMIRCmdCreateShader>(_shader);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void IMIDispatch::dispatchMeshCreate(IMIInstPtr _app,IMIRenderMeshPtr _mesh) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    if(_mesh) {
        IMIRCmdCreateMeshPtr t_cmd = MakeSharedPtr<IMIRCmdCreateMesh>(_mesh);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void IMIDispatch::dispatchTextureCreate(IMIInstPtr _app,IMITexturePtr _tex) {
    if(_tex) {
        IMIRCmdCreateTexPtr t_cmd = MakeSharedPtr<IMIRCmdCreateTex>(_tex);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void IMIDispatch::dispatchTargetCreate(IMIInstPtr _app,IMIRTargetPtr _target) {
    if(_target) {
        IMIRCmdCreateTargetPtr t_cmd = MakeSharedPtr<IMIRCmdCreateTarget>(_target);
        _app->getRenderMgr()->pushRCmdCreate(t_cmd);
    }
}

void IMIDispatch::dispatchTargetResize(IMIInstPtr _app,IMIRTargetPtr _target) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        IMIRFboPtr t_rfbo = _target->getResFbo() ;
        if(t_rfbo) {
            s32 t_w = _target->getTargetDsp()->m_width;
            s32 t_h = _target->getTargetDsp()->m_height;
            IMIRCmdTargetResizePtr t_cmd = MakeSharedPtr<IMIRCmdTargetResize>(t_rfbo,t_w,t_h);
            _app->getRenderMgr()->pushRCmdCreate(t_cmd);
        }
    }
}

void IMIDispatch::dispatchMeshPreZ(IMIInstPtr _app,
                                  IMIRenderMeshPtr _mesh,
                                  IMISurfacePtr _surface) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    IMIRTargetPtr t_z_target = _app->getRenderPath()->m_target_preZ;
    IMIRTargetPtr t_main_target = _app->getRenderMgr()->getMainRT();
    IMIMtlCorePtr t_z_mtl = _app->getMtlLib()->getMtl("preZ");
    if(t_renderer && _mesh && _surface && t_z_target && t_main_target && t_z_mtl) {
        //投递到主目标，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_main_target->viewMat();
            FMat4 t_mat_p = t_main_target->projMat();
            FMat4 t_mat_vp = t_main_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        //投递命令
        IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
        t_cmd_nor->setMesh(_mesh);
        t_cmd_nor->setMaterial(t_z_mtl);
        t_cmd_nor->setSurface(_surface);
        t_z_target->pushCommand(t_cmd_nor,E_RSM_SOLID);
    }
}

//投递rendermesh
void IMIDispatch::dispatchMeshDraw(IMIInstPtr _app,
                                  IMIRenderMeshPtr _mesh,
                                  IMIMtlCorePtr _mtl,
                                  IMISurfacePtr _surface,
                                  IMI_RSTREAM _stype,
                                  IMIString _tag) {
    
    IMIRendererPtr t_renderer = _app->getRenderer();
    IMIRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target) {
        //投递到主目标，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        //投递命令
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommand(t_cmd_nor,_stype);
        }
    }
}

//投递rendermesh
void IMIDispatch::dispatchMeshDraw(IMIInstPtr _app,
                                  IMIRenderMeshPtr _mesh,
                                  IMIMtlCorePtr _mtl,
                                  IMISurfacePtr _surface,
                                  IMIRTargetPtr _target,
                                  IMI_RSTREAM _stype,
                                  IMIString _tag) {
    
    IMIRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommand(t_cmd_nor,_stype);
        }
    }
}

//投递rendermesh-pre
void IMIDispatch::dispatchMeshDrawPre(IMIInstPtr _app,
                                     IMIRenderMeshPtr _mesh,
                                     IMIMtlCorePtr _mtl,
                                     IMISurfacePtr _surface,
                                     IMIString _tag) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    IMIRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target ) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommandPre(t_cmd_nor);
        }
    }
}

//投递rendermesh-pre
void IMIDispatch::dispatchMeshDrawPre(IMIInstPtr _app,
                                     IMIRenderMeshPtr _mesh,
                                     IMIMtlCorePtr _mtl,
                                     IMISurfacePtr _surface,
                                     IMIRTargetPtr _target,
                                     IMIString _tag) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommandPre(t_cmd_nor);
        }
    }
}

//投递rendermesh-pre
void IMIDispatch::dispatchMeshDrawAfter(IMIInstPtr _app,
                                       IMIRenderMeshPtr _mesh,
                                       IMIMtlCorePtr _mtl,
                                       IMISurfacePtr _surface,
                                       IMIString _tag) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    IMIRTargetPtr t_target = _app->getRenderMgr()->getMainRT();
    if(t_renderer && t_target ) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = t_target->viewMat();
            FMat4 t_mat_p = t_target->projMat();
            FMat4 t_mat_vp = t_target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            t_target->pushCommandAfter(t_cmd_nor);
        }
    }
}

//投递rendermesh-after
void IMIDispatch::dispatchMeshDrawAfter(IMIInstPtr _app,
                                       IMIRenderMeshPtr _mesh,
                                       IMIMtlCorePtr _mtl,
                                       IMISurfacePtr _surface,
                                       IMIRTargetPtr _target,
                                       IMIString _tag) {
    IMIRendererPtr t_renderer = _app->getRenderer();
    if(t_renderer && _target) {
        //投递到Target，在这里更新VP矩阵
        if(_surface) {
            FMat4 t_mat_v = _target->viewMat();
            FMat4 t_mat_p = _target->projMat();
            FMat4 t_mat_vp = _target->vpMat();
            _surface->setParam("matVP", t_mat_vp);
            _surface->setParam("matV", t_mat_v);
            _surface->setParam("matP", t_mat_p);
        }
        if(_mtl) {
            IMIRCmdNorPtr t_cmd_nor = MakeSharedPtr<IMIRCmdNor>();
            t_cmd_nor->mTag = _tag;
            t_cmd_nor->setMesh(_mesh);
            t_cmd_nor->setMaterial(_mtl);
            t_cmd_nor->setSurface(_surface);
            _target->pushCommandAfter(t_cmd_nor);
        }
    }
}

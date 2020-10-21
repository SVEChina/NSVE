//
// SVARBackgroundMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVARBackgroundMgr.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../basesys/SVComData.h"
#include "../mtl/SVFilterBase.h"
#include "../work/SVTdCore.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRTargetMgr.h"
#include "../rendercore/SVRTarget.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVMtlCore.h"

using namespace sv;

SVARBackgroundMgr::SVARBackgroundMgr(SVInstPtr _app)
:SVSysBase(_app) {
    m_enable = false;
    m_method = 0;
    m_width = 0;
    m_height = 0;
    m_subsysType = 0;
    m_mtl = nullptr;
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
    
}

SVARBackgroundMgr::~SVARBackgroundMgr() {
    m_ar_target = nullptr;
    m_mtl = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

void SVARBackgroundMgr::init() {
}

void SVARBackgroundMgr::destroy() {
}

bool SVARBackgroundMgr::enable() {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer) {
        if(!m_enable) {
            m_width = mApp->m_global_param.sv_width;
            m_height = mApp->m_global_param.sv_height;
            m_ar_target = mApp->getTargetMgr()->createTarget(E_TEX_CAMERA,false,false);
            m_ar_target->pushStreamQuene(E_RSM_NOR);    //推送NOR流
            mApp->getRenderMgr()->addRTarget(m_ar_target,true);
            m_enable = true;
            return true;
        }
        return false;
    }
    return false;
}

bool SVARBackgroundMgr::enable(s32 _w,s32 _h) {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer) {
        if(!m_enable) {
            m_width = _w;
            m_height = _h;
            m_ar_target = mApp->getTargetMgr()->createTarget(E_TEX_CAMERA,_w,_h,false,false);
            m_ar_target->pushStreamQuene(E_RSM_NOR);    //推送NOR流
            mApp->getRenderMgr()->addRTarget(m_ar_target,true);
            m_enable = true;
            return true;
        }
        return false;
    }
    return false;
}

void SVARBackgroundMgr::disable() {
    if(m_enable) {
        if(m_ar_target) {
            m_ar_target = nullptr;
        }
        m_enable = false;
    }
}

void SVARBackgroundMgr::update(f32 _dt) {
    if(m_ar_target && m_enable) {
        //将AR-相机图片渲染到主目标上
        if(m_method == 1 ) {
            if(m_mtl) {
                m_mtl->update(_dt);
            }
            //直接绘制图片
            SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
            t_surface->setTexture(1,0,m_tex0);
            FVec2 t_invert = FVec2(1.0f,-1.0f);
            t_surface->setParam("u_invert", t_invert);
            SVDispatch::dispatchMeshDraw(mApp,
                                         mApp->getComData()->screenMesh(),
                                         m_mtl,
                                         t_surface,
                                         m_ar_target,
                                         E_RSM_NOR);
            t_surface = nullptr;
        }else if(m_method == 2 ) {
            //格式转换
            
        }else if(m_method == 3 ) {
            //外部渲染
            
        }
        //渲染相机
        _renderCameraImg(_dt);
    }
}

void SVARBackgroundMgr::_renderCameraImg(f32 _dt) {
    //将相机图片绘制到主纹理上
    SVTexturePtr t_cam_tex = mApp->getRenderer()->getInTexture(E_TEX_CAMERA);
    if(t_cam_tex) {
        SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screen");
        if(t_mtl) {
            t_mtl->update(_dt);
            SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
            t_surface->setTexture(1,0,t_cam_tex);
            FVec2 t_invert = FVec2(1.0f,1.0f);
            t_surface->setParam("u_invert", t_invert);
            SVDispatch::dispatchMeshDraw(mApp,
                                         mApp->getComData()->screenMesh(),
                                         t_mtl,
                                         t_surface,
                                         E_RSM_SKY);
        }
    }
}

//设置输入文件方式纹理
void SVARBackgroundMgr::setInputCameraTex(cptr8 _fname) {
    m_method = 1;
    m_tex0 = mApp->getTexMgr()->getTexture(_fname);
    m_mtl = mApp->getMtlLib()->getMtl("screen");
}

//数据纹理方式
void SVARBackgroundMgr::setInputCameraTex(SVDataSwapPtr _data,SV_PIC_FORMATE _formate) {
    m_method = 2;
    //这里创建纹理，创建材质，更新数据
    if(_formate == SV_PF_GRAY8) {
        
    }else if(_formate == SV_PF_YV12) {
        
    }else if(_formate == SV_PF_I420) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_R8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
        m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp);    //u
        m_tex2 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG2,t_dsp);    //v
        //
        m_mtl = mApp->getMtlLib()->getMtl("i420-rgba");
        //
        if(_data) {
            
        }
    }else if(_formate == SV_PF_NV12) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_R8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
        //
        SVTextureDsp t_dsp1;
        t_dsp1.m_image_type = SV_IMAGE_2D;
        t_dsp1.m_data_formate = SV_FORMAT_RG8;
        t_dsp1.m_width = m_width;    //宽
        t_dsp1.m_height = m_height;  //高
        t_dsp1.m_depth = 1; //深度
        t_dsp1.m_minmap = false;         //是否开启mipmap
        t_dsp1.m_computeWrite = true;    //metal 是否可以
        t_dsp1.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp1);    //uv
        //
        m_mtl = mApp->getMtlLib()->getMtl("nv12-rgba");
    }else if(_formate == SV_PF_NV21) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_R8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
        //
        SVTextureDsp t_dsp1;
        t_dsp1.m_image_type = SV_IMAGE_2D;
        t_dsp1.m_data_formate = SV_FORMAT_RG8;
        t_dsp1.m_width = m_width;    //宽
        t_dsp1.m_height = m_height;  //高
        t_dsp1.m_depth = 1; //深度
        t_dsp1.m_minmap = false;         //是否开启mipmap
        t_dsp1.m_computeWrite = true;    //metal 是否可以
        t_dsp1.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp1);    //uv
        //
        m_mtl = mApp->getMtlLib()->getMtl("nv21-rgba");
    }else if(_formate == SV_PF_BGRA) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_BGRA8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
        //
        m_mtl = mApp->getMtlLib()->getMtl("bgra-rgba");
    }else if(_formate == SV_PF_RGBA) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_RGBA8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
        //
        m_mtl = mApp->getMtlLib()->getMtl("rgba-rgba");
    }else if(_formate == SV_PF_RGB) {
        SVTextureDsp t_dsp;
        t_dsp.m_image_type = SV_IMAGE_2D;
        t_dsp.m_data_formate = SV_FORMAT_RGB8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
        //
        m_mtl = mApp->getMtlLib()->getMtl("rgb-rgba");
    }
}

//其他方式，例如共享纹理方式
void SVARBackgroundMgr::setInputCameraTex(s32 _texid) {
    m_method = 3;
    //外部共享ID，渲染方式
}

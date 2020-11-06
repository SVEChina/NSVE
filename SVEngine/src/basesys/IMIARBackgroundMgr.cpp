//
// IMIARBackgroundMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIARBackgroundMgr.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../basesys/IMIComData.h"
#include "../mtl/IMIFilterBase.h"
#include "../work/IMITdCore.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRTargetMgr.h"
#include "../rendercore/IMIRTarget.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMISurface.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMIMtlCore.h"

using namespace imi;

IMIARBackgroundMgr::IMIARBackgroundMgr(IMIInstPtr _app)
:IMISysBase(_app) {
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

IMIARBackgroundMgr::~IMIARBackgroundMgr() {
    m_ar_target = nullptr;
    m_mtl = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

void IMIARBackgroundMgr::init() {
}

void IMIARBackgroundMgr::destroy() {
}

bool IMIARBackgroundMgr::enable() {
    IMIRendererPtr t_renderer = mApp->getRenderer();
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

bool IMIARBackgroundMgr::enable(s32 _w,s32 _h) {
    if(!m_enable) {
        IMIRendererPtr t_renderer = mApp->getRenderer();
        if(t_renderer) {
            m_width = _w;
            m_height = _h;
            m_ar_target = mApp->getTargetMgr()->createTarget(E_TEX_CAMERA,_w,_h,false,false);
            m_ar_target->pushStreamQuene(E_RSM_NOR);    //推送NOR流
            mApp->getRenderMgr()->addRTarget(m_ar_target,true);
            m_enable = true;
            return true;
        }
    }
    return false;
}

void IMIARBackgroundMgr::disable() {
    if(m_enable) {
        if(m_ar_target) {
            m_ar_target = nullptr;
        }
        m_enable = false;
    }
}

void IMIARBackgroundMgr::update(f32 _dt) {
    if(m_ar_target && m_enable) {
        //将AR-相机图片渲染到主目标上
        if(m_method == 1 ) {
            if(m_mtl) {
                m_mtl->update(_dt);
                //直接绘制图片
                IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
                t_surface->setTexture(1,0,m_tex0);
                FVec2 t_invert = FVec2(1.0f,1.0f);
                t_surface->setParam("u_invert", t_invert);
                IMIDispatch::dispatchMeshDraw(mApp,
                                             mApp->getComData()->screenMesh(),
                                             m_mtl,
                                             t_surface,
                                             m_ar_target,
                                             E_RSM_NOR);
                t_surface = nullptr;
            }
        }else if(m_method == 2 ) {
            //格式转换
            if(m_mtl) {
                m_mtl->update(_dt);
                //直接绘制图片
                IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
                if(m_tex0) {
                    t_surface->setTexture(1,0,m_tex0);
                }
                if(m_tex1) {
                    t_surface->setTexture(1,1,m_tex1);
                }
                if(m_tex2) {
                    t_surface->setTexture(1,2,m_tex2);
                }
                FVec2 t_invert = FVec2(1.0f,1.0f);
                t_surface->setParam("u_invert", t_invert);
                IMIDispatch::dispatchMeshDraw(mApp,
                                             mApp->getComData()->screenMesh(),
                                             m_mtl,
                                             t_surface,
                                             m_ar_target,
                                             E_RSM_NOR);
                t_surface = nullptr;
            }
        }else if(m_method == 3 ) {
            //外部渲染
            
        }
        //渲染相机
        _renderCameraImg(_dt);
    }
}

void IMIARBackgroundMgr::_renderCameraImg(f32 _dt) {
    //将相机图片绘制到主纹理上
    IMITexturePtr t_cam_tex = mApp->getRenderer()->getInTexture(E_TEX_CAMERA);
    if(t_cam_tex) {
        IMIMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screen");
        if(t_mtl) {
            t_mtl->update(_dt);
            IMISurfacePtr t_surface = MakeSharedPtr<IMISurface>();
            t_surface->setTexture(1,0,t_cam_tex);
            FVec2 t_invert = FVec2(1.0f, -1.0f);
            t_surface->setParam("u_invert", t_invert);
            IMIDispatch::dispatchMeshDraw(mApp,
                                         mApp->getComData()->screenMesh(),
                                         t_mtl,
                                         t_surface,
                                         E_RSM_SKY);
        }
    }
}

//设置输入文件方式纹理
void IMIARBackgroundMgr::setInputCameraTex(cptr8 _fname) {
    if(!m_enable) {
        return;
    }
    m_method = 1;
    m_tex0 = mApp->getTexMgr()->getTexture(_fname);
    m_mtl = mApp->getMtlLib()->getMtl("screen");
}

//数据纹理方式
void IMIARBackgroundMgr::setInputCameraTex(IMIDataSwapPtr _data,IMI_PIC_FORMATE _formate) {
    if(!m_enable) {
        return;
    }
    m_method = 2;
    //这里创建纹理，创建材质，更新数据
    if(_formate == IMI_PF_GRAY8) {
        
    }else if(_formate == IMI_PF_YV12) {
        
    }else if(_formate == IMI_PF_I420) {
        if(_data) {
            //构建三张纹理
        }
        IMITextureDsp t_dsp;
        t_dsp.m_image_type = IMI_IMAGE_2D;
        t_dsp.m_data_formate = IMI_FORMAT_R8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
        m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp);    //u
        m_tex2 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG2,t_dsp);    //v
        m_mtl = mApp->getMtlLib()->getMtl("i420-rgba");
    }else if(_formate == IMI_PF_NV12) {
        if(_data) {
            //构建二张纹理
        }
        IMITextureDsp t_dsp;
        t_dsp.m_image_type = IMI_IMAGE_2D;
        t_dsp.m_data_formate = IMI_FORMAT_R8;
        t_dsp.m_width = m_width;    //宽
        t_dsp.m_height = m_height;  //高
        t_dsp.m_depth = 1; //深度
        t_dsp.m_minmap = false;         //是否开启mipmap
        t_dsp.m_computeWrite = true;    //metal 是否可以
        t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
        //
        IMITextureDsp t_dsp1;
        t_dsp1.m_image_type = IMI_IMAGE_2D;
        t_dsp1.m_data_formate = IMI_FORMAT_RG8;
        t_dsp1.m_width = m_width;    //宽
        t_dsp1.m_height = m_height;  //高
        t_dsp1.m_depth = 1; //深度
        t_dsp1.m_minmap = false;         //是否开启mipmap
        t_dsp1.m_computeWrite = true;    //metal 是否可以
        t_dsp1.m_renderTarget = false;    //metal 是否是renderTarget
        m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp1);    //uv
        //
        m_mtl = mApp->getMtlLib()->getMtl("nv12-rgba");
    }else if(_formate == IMI_PF_NV21) {
        if(!m_tex0) {
            IMITextureDsp t_dsp;
            t_dsp.m_image_type = IMI_IMAGE_2D;
            t_dsp.m_data_formate = IMI_FORMAT_R8;
            t_dsp.m_width = m_width;    //宽
            t_dsp.m_height = m_height;  //高
            t_dsp.m_depth = 1; //深度
            t_dsp.m_minmap = false;         //是否开启mipmap
            t_dsp.m_computeWrite = true;    //metal 是否可以
            t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
            m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);    //y
            m_mtl = mApp->getMtlLib()->getMtl("nv21-rgba");
        }
        if(!m_tex1) {
            IMITextureDsp t_dsp1;
            t_dsp1.m_image_type = IMI_IMAGE_2D;
            t_dsp1.m_data_formate = IMI_FORMAT_RG8;
            t_dsp1.m_width = m_width;    //宽
            t_dsp1.m_height = m_height;  //高
            t_dsp1.m_depth = 1; //深度
            t_dsp1.m_minmap = false;         //是否开启mipmap
            t_dsp1.m_computeWrite = true;    //metal 是否可以
            t_dsp1.m_renderTarget = false;    //metal 是否是renderTarget
            m_tex1 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG1,t_dsp1);    //uv
        }
        //设置数据
        
    }else if(_formate == IMI_PF_BGRA) {
        if(!m_tex0) {
            IMITextureDsp t_dsp;
            t_dsp.m_image_type = IMI_IMAGE_2D;
            t_dsp.m_data_formate = IMI_FORMAT_BGRA8;
            t_dsp.m_width = m_width;    //宽
            t_dsp.m_height = m_height;  //高
            t_dsp.m_depth = 1; //深度
            t_dsp.m_minmap = false;         //是否开启mipmap
            t_dsp.m_computeWrite = true;    //metal 是否可以
            t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
            t_dsp.m_pData[0] = _data;
            m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
            m_mtl = mApp->getMtlLib()->getMtl("screen");
        }else{
            m_tex0->setTexData(_data);
        }
    }else if(_formate == IMI_PF_RGBA) {
        if(!m_tex0) {
            IMITextureDsp t_dsp;
            t_dsp.m_image_type = IMI_IMAGE_2D;
            t_dsp.m_data_formate = IMI_FORMAT_RGBA8;
            t_dsp.m_width = m_width;    //宽
            t_dsp.m_height = m_height;  //高
            t_dsp.m_depth = 1; //深度
            t_dsp.m_minmap = false;         //是否开启mipmap
            t_dsp.m_computeWrite = true;    //metal 是否可以
            t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
            t_dsp.m_pData[0] = _data;
            m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
            m_mtl = mApp->getMtlLib()->getMtl("screen");
        }else{
            m_tex0->setTexData(_data);
        }
    }else if(_formate == IMI_PF_RGB) {
        if(!m_tex0) {
            IMITextureDsp t_dsp;
            t_dsp.m_image_type = IMI_IMAGE_2D;
            t_dsp.m_data_formate = IMI_FORMAT_RGB8;
            t_dsp.m_width = m_width;    //宽
            t_dsp.m_height = m_height;  //高
            t_dsp.m_depth = 1; //深度
            t_dsp.m_minmap = false;         //是否开启mipmap
            t_dsp.m_computeWrite = true;    //metal 是否可以
            t_dsp.m_renderTarget = false;    //metal 是否是renderTarget
            m_tex0 = mApp->getTexMgr()->createInTexture(E_TEX_AR_BG0,t_dsp);
            //
            m_mtl = mApp->getMtlLib()->getMtl("rgb-rgba");
        }else{
            m_tex0->setTexData(_data);
        }
    }
}

//其他方式，例如共享纹理方式
void IMIARBackgroundMgr::setInputCameraTex(s32 _texid) {
    if(!m_enable) {
        return;
    }
    m_method = 3;
    //外部共享ID，渲染方式
}

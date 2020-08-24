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
#include "../work/SVTdCore.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
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
    m_subsysType = 0;
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

SVARBackgroundMgr::~SVARBackgroundMgr() {
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

//
void SVARBackgroundMgr::init() {
}

//
void SVARBackgroundMgr::destroy() {
}

//
bool SVARBackgroundMgr::enable() {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer) {
        if(!m_enable) {
            m_ar_target = t_renderer->createTarget(E_TEX_CAMERA,false,false);
            m_ar_target->pushStreamQuene(E_RSM_NOR);    //推送NOR流
            //推送到前向渲染
            mApp->getRenderMgr()->addRTarget(m_ar_target,true);
            m_enable = true;
            return true;
        }
        return false;
    }
    return false;
}

//
void SVARBackgroundMgr::disable() {
    if(m_enable) {
        if(m_ar_target) {
            m_ar_target = nullptr;
        }
        m_enable = false;
    }
}

//
void SVARBackgroundMgr::update(f32 dt) {
    if(m_ar_target) {
        //将AR-相机图片渲染到主目标上
        if(m_method == 1 ) {
            SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screenCamera");
            if(t_mtl) {
                t_mtl->update(dt);
            }
            //直接绘制图片
            SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
            t_surface->setTexture(0,m_tex0,1);
            SVDispatch::dispatchMeshDraw(mApp,
                                         mApp->getComData()->screenMesh(),
                                         "screenCamera",
                                         t_surface,
                                         m_ar_target,
                                         E_RSM_NOR);
            t_surface = nullptr;
        }else if(m_method == 2 ) {
            //格式转换
            
        }else if(m_method == 3 ) {
            //外部渲染
        }
        //各种pass
        
    }
}

//文件纹理方式
void SVARBackgroundMgr::setInputCameraTex(cptr8 _fname) {
    m_method = 1;
    m_tex0 = mApp->getTexMgr()->getTexture(_fname);
}

//数据纹理方式
void SVARBackgroundMgr::setInputCameraTex(SVDataSwapPtr _data,s32 _formate) {
    m_method = 2;
    //这里有格式转换
    
}

//其他方式，例如共享纹理方式
void SVARBackgroundMgr::setInputCameraTex(s32 _texid) {
    m_method = 3;
}

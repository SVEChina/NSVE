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
    m_filter_lock = MakeSharedPtr<SVLockSpin>();
    m_enable = false;
    m_method = 0;
    m_subsysType = 0;
    m_ar_target = nullptr;
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
}

SVARBackgroundMgr::~SVARBackgroundMgr() {
    m_filter_lock = nullptr;
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
    clearFilter();
}

//
bool SVARBackgroundMgr::enable() {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(t_renderer) {
        if(!m_enable) {
            m_ar_target = mApp->getTargetMgr()->createTarget(E_TEX_CAMERA,false,false);
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
void SVARBackgroundMgr::update(f32 _dt) {
    if(m_ar_target && m_enable) {
        //将AR-相机图片渲染到主目标上
        if(m_method == 1 ) {
            SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("screenCamera");
            if(t_mtl) {
                t_mtl->update(_dt);
            }
            //直接绘制图片
            SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
            t_surface->setTexture(1,0,m_tex0);
            SVDispatch::dispatchMeshDraw(mApp,
                                         mApp->getComData()->screenMesh(),
                                         nullptr,//"screenCamera"
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
        _renderCameraPass(_dt);
        //渲染相机
        _renderCameraImg(_dt);
    }
}

void SVARBackgroundMgr::_renderCameraPass(f32 _dt) {
    m_filter_lock->lock();
    for(s32 i=0;i<m_filter_pool.size();i++) {
        m_filter_pool[i]->update(_dt);
    }
    m_filter_lock->unlock();
}

void SVARBackgroundMgr::_renderCameraImg(f32 _dt) {
    //直接绘制图片
    SVTexturePtr t_cam_tex = mApp->getRenderer()->getInTexture(E_TEX_CAMERA);
    if(t_cam_tex) {
        SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("skycamera");
        if(t_mtl) {
            t_mtl->update(_dt);
        }
        SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
        t_surface->setTexture(1,0,t_cam_tex);
        SVDispatch::dispatchMeshDraw(mApp,
                                     mApp->getComData()->screenMesh(),
                                     nullptr,//"skycamera",
                                     t_surface,
                                     E_RSM_SKY);
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

//推送滤镜
void SVARBackgroundMgr::pushFilter(SVFilterBasePtr _filter) {
    m_filter_lock->lock();
    if(_filter) {
        //m_ar_target
        //_filter->setTarget();
        m_filter_pool.push_back(_filter);
    }
    m_filter_lock->unlock();
}

//清理滤镜
void SVARBackgroundMgr::clearFilter() {
    m_filter_lock->lock();
    m_filter_pool.clear();
    m_filter_lock->unlock();
}

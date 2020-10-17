//
// SVRTargetMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTargetMgr.h"
#include "SVRTarget.h"
#include "SVRenderMgr.h"
#include "../work/SVTdCore.h"
#include "../app/SVGlobalParam.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../mtl/SVTexMgr.h"

using namespace sv;

SVRTargetMgr::SVRTargetMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    m_res_lock = MakeSharedPtr<SVLockSpin>();
}

SVRTargetMgr::~SVRTargetMgr() {
    m_res_lock = nullptr;
}

void SVRTargetMgr::init() {
    //内置Target
    m_target_pool.resize(E_TEX_END);
    for(s32 i=0;i<E_TEX_END;i++) {
        m_target_pool[i] = nullptr;
    }
}

void SVRTargetMgr::destroy() {
}

void SVRTargetMgr::loadDefault() {
    //创建主target,设置主RT
    SVRTargetPtr t_target = createTarget(E_TEX_MAIN,true,true);
    if(t_target) {
        t_target->pushStreamQuene(E_RSM_SKY );
        t_target->pushStreamQuene(E_RSM_SOLID);
        t_target->setClearColor(1.0f, 1.0f, 0.0f, 1.0f);
        mApp->getRenderMgr()->setMainRT(t_target);
    }
}

//重置大小
void SVRTargetMgr::resize(s32 _w,s32 _h) {
    m_res_lock->lock();
    for(s32 i=0;i<E_TEX_END;i++) {
        if( m_target_pool[i] ) {
            m_target_pool[i]->resize(_w, _h);
        }
    }
    m_res_lock->unlock();
}

//创建target资源
SVRTargetPtr SVRTargetMgr::createTarget(SV_TEXIN _texid,bool _depth,bool _stencil) {
    SVTexMgrPtr t_tex_mgr = mApp->getTexMgr();
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_image_type = SV_IMAGE_2D;
    t_tex_dsp.m_data_formate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = mApp->m_global_param.sv_width;    //宽
    t_tex_dsp.m_height = mApp->m_global_param.sv_height;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    SVTexturePtr t_target_tex = t_tex_mgr->createInTexture(_texid,t_tex_dsp);
    if(!t_target_tex) {
        return nullptr;
    }
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp,_texid);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_color_texid[0] = _texid;
    t_dsp->m_target_num = 1;
    t_dsp->m_width = mApp->m_global_param.sv_width;
    t_dsp->m_height = mApp->m_global_param.sv_height;
    t_dsp->m_use_depth = _depth;
    t_dsp->m_use_stencil = _stencil;
    //创建RT
    t_target->dispatch();
    //增加target
    _addTarget(_texid,t_target);
    return t_target;
}

SVRTargetPtr SVRTargetMgr::createTarget(SV_TEXIN _texid,s32 _w,s32 _h,bool _depth,bool _stencil){
    SVTexMgrPtr t_tex_mgr = mApp->getTexMgr();
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_image_type = SV_IMAGE_2D;
    t_tex_dsp.m_data_formate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = _w;    //宽
    t_tex_dsp.m_height = _h;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    SVTexturePtr t_target_tex = t_tex_mgr->createInTexture(_texid,t_tex_dsp);
    if(!t_target_tex) {
        return nullptr;
    }
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp,_texid);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_color_texid[0] = _texid;
    t_dsp->m_target_num = 1;
    t_dsp->m_width = _w;
    t_dsp->m_height = _h;
    t_dsp->m_use_depth = _depth;
    t_dsp->m_use_stencil = _stencil;
    //创建RT
    t_target->dispatch();
    //增加target
    _addTarget(_texid,t_target);
    return t_target;
}


//获取target
SVRTargetPtr SVRTargetMgr::getTarget(SV_TEXIN _texid) {
    return m_target_pool[_texid];
}

//销毁Target
void SVRTargetMgr::destroyTarget(SV_TEXIN _texid) {
    m_res_lock->lock();
    if(m_target_pool[_texid]) {
        m_target_pool[_texid] = nullptr;
    }
    m_res_lock->unlock();
}

//private

void SVRTargetMgr::_addTarget(SV_TEXIN _texid,SVRTargetPtr _target) {
    m_res_lock->lock();
    m_target_pool[_texid] = _target;
    m_res_lock->unlock();
}

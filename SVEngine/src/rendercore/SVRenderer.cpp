//
// SVRenderer.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderer.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTextureIOS.h"
#include "SVRenderMgr.h"
#include "SVRTarget.h"
#include "SVRRes.h"
#include "SVRenderState.h"

using namespace sv;

SVRenderer::SVRenderer(SVInstPtr _app)
:SVGBaseEx(_app)
,m_pRState(nullptr)
,m_cur_target(nullptr)
,m_inWidth(256)
,m_inHeight(256)
,m_outWidth(256)
,m_outHeight(256){
    m_resLock = MakeSharedPtr<SVLockSpin>();
}

SVRenderer::~SVRenderer(){
    m_resLock = nullptr;
    m_cur_target = nullptr;
}

void SVRenderer::init(s32 _w,s32 _h){
    m_inWidth = _w;
    m_inHeight = _h;
}

void SVRenderer::destroy(){
    clearRes();
    m_resLock = nullptr;
}

//获取状态
SVRenderStatePtr SVRenderer::getState(){
    return m_pRState;
}

//重置状态
void SVRenderer::resetState() {
    if(m_pRState){
        m_pRState->resetState();
    }
}

void SVRenderer::resize(s32 _w,s32 _) {
}

void SVRenderer::clearRes() {
    m_resLock->lock();
    for(s32 i=0;i<m_robjList.size();i++) {
        SVRResPtr t_robj = m_robjList[i];
        t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
    }
    m_robjList.destroy();
    m_resLock->unlock();
}

void SVRenderer::addRes(SVRResPtr _res) {
    m_resLock->lock();
    m_robjList.append(_res);
    m_resLock->unlock();
}

void SVRenderer::removeRes(SVRResPtr _res) {
    m_resLock->lock();
    for(s32 i=0;i<m_robjList.size();i++) {
        SVRResPtr t_robj = m_robjList[i];
        if(t_robj == _res) {
            t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
            m_robjList.removeForce(i);
            break;
        }
    }
    m_resLock->unlock();
}

//移除不使用的资源
void SVRenderer::removeUnuseRes() {
    m_resLock->lock();
    //小心复值引用计数会加 1！！！！！！！！！！！！！！ 晓帆。。
    for(s32 i=0;i<m_robjList.size();) {
        if(m_robjList[i].use_count() == 1) {
            m_robjList[i]->destroy(nullptr);
            m_robjList.remove(i);
        }else{
            i++;
        }
    }
    m_robjList.reserveForce(m_robjList.size());
    m_resLock->unlock();
}

//需要控制当前的fbo
void SVRenderer::setCurTarget(SVRTargetPtr _target) {
    m_cur_target = _target;
}

//视口
void SVRenderer::svPushViewPort(u32 _x,u32 _y,u32 _w,u32 _h) {
    VPParam t_pm;
    t_pm.m_x = _x;
    t_pm.m_y = _y;
    t_pm.m_width = _w;
    t_pm.m_height = _h;
    m_vpStack.push(t_pm);
}

//退出视口
void SVRenderer::svPopViewPort() {
    m_vpStack.pop();
}

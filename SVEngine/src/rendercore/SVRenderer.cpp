//
// SVRenderer.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderer.h"
#include "SVRenderMgr.h"
#include "SVRTargetMgr.h"
#include "SVRTarget.h"
#include "SVRRes.h"
#include "SVRFbo.h"
#include "SVRTex.h"
#include "SVRMeshRes.h"
#include "SVRShader.h"
#include "../base/SVObjectPool.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTextureIOS.h"

using namespace sv;

SVRenderer::SVRenderer(SVInstPtr _app)
:SVGBaseEx(_app)
,m_cur_target(nullptr){
    m_res_lock = MakeSharedPtr<SVLockSpin>();
}

SVRenderer::~SVRenderer(){
    m_res_lock = nullptr;
    m_cur_target = nullptr;
}

void SVRenderer::init(){
    m_cur_target = nullptr;
}

void SVRenderer::destroy(){
    m_cur_target = nullptr;
    m_res_lock = nullptr;
}

//重置大小
void SVRenderer::resize(s32 _w,s32 _h) {
    m_res_lock->lock();
    m_res_lock->unlock();
}

//需要控制当前的fbo
void SVRenderer::setCurTarget(SVRTargetPtr _target) {
    m_cur_target = _target;
}

SVRTargetPtr SVRenderer::getTarget(SV_TEXIN _texid) {
    if(mApp->getTargetMgr()) {
        return mApp->getTargetMgr()->getTarget(_texid);
    }
    return nullptr;
}

SVTexturePtr SVRenderer::getInTexture(SV_TEXIN _texid) {
    if(mApp->getTexMgr()) {
        return mApp->getTexMgr()->getInTexture(_texid);
    }
    return nullptr;
}

//交换纹理
void SVRenderer::swapInTexture(SV_TEXIN _tex1,SV_TEXIN _tex2) {
    SVTexturePtr tex1 = getInTexture(_tex1);
    SVTexturePtr tex2 = getInTexture(_tex2);
    if( tex1 != tex2) {
        tex1->swap(tex2);
    }
}

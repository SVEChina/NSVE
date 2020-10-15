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
    clearRes();
    m_cur_target = nullptr;
    m_res_lock = nullptr;
}

//重置大小
void SVRenderer::resize(s32 _w,s32 _h) {
    m_res_lock->lock();
    m_res_lock->unlock();
}

//增加资源
void SVRenderer::addRes(SVRResPtr _res) {
    m_res_lock->lock();
    m_robjList.push_back(_res);
    m_res_lock->unlock();
}

//移除资源
void SVRenderer::removeRes(SVRResPtr _res) {
    m_res_lock->lock();
    ROBJLIST::iterator it = m_robjList.begin();
    while(it!=m_robjList.end()) {
        SVRResPtr t_robj = (*it) ;
        if(_res == t_robj) {
            t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
            m_robjList.erase(it);
            break;
        }
        it++;
    }
    m_res_lock->unlock();
}

//移除不使用的资源
void SVRenderer::removeUnuseRes() {
    m_res_lock->lock();
    ROBJLIST::iterator it = m_robjList.begin();
    while(it!=m_robjList.end()) {
        SVRResPtr t_robj = (*it) ;
        if(t_robj.use_count() == 1) {
            t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
            it = m_robjList.erase(it);
        }else{
            it++;
        }
    }
    m_res_lock->unlock();
}

//清理资源
void SVRenderer::clearRes() {
    m_res_lock->lock();
    ROBJLIST::iterator it = m_robjList.begin();
    while(it!=m_robjList.end()) {
        SVRResPtr t_robj = (*it);
        t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
        it = m_robjList.erase(it);
    }
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

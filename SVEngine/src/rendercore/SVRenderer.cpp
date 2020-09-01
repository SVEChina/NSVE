//
// SVRenderer.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderer.h"
#include "SVRenderMgr.h"
#include "SVRTarget.h"
#include "SVRRes.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVTextureIOS.h"

using namespace sv;

SVRenderer::SVRenderer(SVInstPtr _app)
:SVGBaseEx(_app)
,m_cur_target(nullptr){
    m_target_pool.resize(E_TEX_END);
    for(s32 i=0;i<E_TEX_END;i++) {
        m_target_pool[i] = nullptr;
    }
    m_res_lock = MakeSharedPtr<SVLockSpin>();
}

SVRenderer::~SVRenderer(){
    m_res_lock = nullptr;
    m_cur_target = nullptr;
}

void SVRenderer::init(s32 _w,s32 _h){
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
    for(s32 i=0;i<E_TEX_END;i++) {
        if( m_target_pool[i] ) {
            m_target_pool[i]->resize(_w, _h);
        }
    }
    m_res_lock->unlock();
}

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

void SVRenderer::addRes(SVRResPtr _res) {
    m_res_lock->lock();
    m_robjList.push_back(_res);
    m_res_lock->unlock();
}

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

//需要控制当前的fbo
void SVRenderer::setCurTarget(SVRTargetPtr _target) {
    m_cur_target = _target;
}

//获取target
SVRTargetPtr SVRenderer::getTarget(SVINTEX _texid) {
    return m_target_pool[_texid];
}

//销毁Target
void SVRenderer::destroyTarget(SVINTEX _texid) {
    m_res_lock->lock();
    if(m_target_pool[_texid]) {
        m_target_pool[_texid] = nullptr;
    }
    m_res_lock->unlock();
}

void SVRenderer::_addTarget(SVINTEX _texid,SVRTargetPtr _target) {
    m_res_lock->lock();
    m_target_pool[_texid] = _target;
    m_res_lock->unlock();
}

void SVRenderer::swapInTexture(SVINTEX _tex1,SVINTEX _tex2) {
    //交换纹理
    SVTexturePtr tex1 = mApp->getTexMgr()->getInTexture(_tex1);
    SVTexturePtr tex2 = mApp->getTexMgr()->getInTexture(_tex2);
    if(tex1!=tex2) {
        tex1->swap(tex2);
    }
}

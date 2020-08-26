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
,m_cur_target(nullptr){
    m_resLock = MakeSharedPtr<SVLockSpin>();
}

SVRenderer::~SVRenderer(){
    m_resLock = nullptr;
    m_cur_target = nullptr;
}

void SVRenderer::init(s32 _w,s32 _h){
}

void SVRenderer::destroy(){
    clearRes();
    m_resLock = nullptr;
}

void SVRenderer::resize(s32 _w,s32 _) {
}

void SVRenderer::clearRes() {
    m_resLock->lock();
    ROBJLIST::iterator it = m_robjList.begin();
    while(it!=m_robjList.end()) {
        SVRResPtr t_robj = (*it);
        t_robj->destroy( std::dynamic_pointer_cast<SVRenderer>(shareObject())  );
        it = m_robjList.erase(it);
    }
    m_resLock->unlock();
}

void SVRenderer::addRes(SVRResPtr _res) {
    m_resLock->lock();
    m_robjList.push_back(_res);
    m_resLock->unlock();
}

void SVRenderer::removeRes(SVRResPtr _res) {
    m_resLock->lock();
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
    m_resLock->unlock();
}

//移除不使用的资源
void SVRenderer::removeUnuseRes() {
    m_resLock->lock();
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
    m_resLock->unlock();
}

//需要控制当前的fbo
void SVRenderer::setCurTarget(SVRTargetPtr _target) {
    m_cur_target = _target;
}

//获取target
SVRTargetPtr SVRenderer::getTarget(SVINTEX _texid) {
    TARGETPOOL::iterator it = m_target_pool.find(_texid);
    if( it!=m_target_pool.end() ) {
        return it->second;
    }
    return nullptr;
}

//销毁Target
void SVRenderer::destroyTarget(SVINTEX _texid) {
    TARGETPOOL::iterator it = m_target_pool.find(_texid);
    if( it!=m_target_pool.end() ) {
        SVRTargetPtr t_target = it->second;
        m_target_pool.erase(it);
        //析构target
        t_target = nullptr;
    }
}

void SVRenderer::_addTarget(SVINTEX _texid,SVRTargetPtr _target) {
    if(_target) {
        m_target_pool.insert(std::make_pair(_texid, _target));
    }
}

void SVRenderer::swapInTexture(SVINTEX _tex1,SVINTEX _tex2) {
    //交换纹理
    SVTexturePtr tex1 = mApp->getTexMgr()->getInTexture(_tex1);
    SVTexturePtr tex2 = mApp->getTexMgr()->getInTexture(_tex2);
    if(tex1!=tex2) {
        tex1->swap(tex2);
    }
}

//
// IMIRenderer.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderer.h"
#include "IMIRenderMgr.h"
#include "IMIRTargetMgr.h"
#include "IMIRTarget.h"
#include "IMIRRes.h"
#include "IMIRFbo.h"
#include "IMIRTex.h"
#include "IMIRMeshRes.h"
#include "IMIRShader.h"
#include "../base/IMIObjectPool.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../work/IMITdCore.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"

using namespace imi;

IMIRenderer::IMIRenderer(IMIInstPtr _app)
:IMIGBaseEx(_app)
,m_cur_target(nullptr){
    m_res_lock = MakeSharedPtr<IMILockSpin>();
}

IMIRenderer::~IMIRenderer(){
    m_res_lock = nullptr;
    m_cur_target = nullptr;
}

void IMIRenderer::init(){
    m_cur_target = nullptr;
}

void IMIRenderer::destroy(){
    m_cur_target = nullptr;
    m_res_lock = nullptr;
}

//重置大小
void IMIRenderer::resize(s32 _w,s32 _h) {
    m_res_lock->lock();
    m_res_lock->unlock();
}

//需要控制当前的fbo
void IMIRenderer::setCurTarget(IMIRTargetPtr _target) {
    m_cur_target = _target;
}

IMIRTargetPtr IMIRenderer::getTarget(IMI_TEXIN _texid) {
    if(mApp->getTargetMgr()) {
        return mApp->getTargetMgr()->getTarget(_texid);
    }
    return nullptr;
}

IMITexturePtr IMIRenderer::getInTexture(IMI_TEXIN _texid) {
    if(mApp->getTexMgr()) {
        return mApp->getTexMgr()->getInTexture(_texid);
    }
    return nullptr;
}

//交换纹理
void IMIRenderer::swapInTexture(IMI_TEXIN _tex1,IMI_TEXIN _tex2) {
    IMITexturePtr tex1 = getInTexture(_tex1);
    IMITexturePtr tex2 = getInTexture(_tex2);
    if( tex1 != tex2) {
        tex1->swap(tex2);
    }
}

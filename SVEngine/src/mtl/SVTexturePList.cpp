//
// SVTexturePList.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVTexturePList.h"
#include "../app/SVInst.h"
#include "../rendercore/SVRenderMgr.h"
#include "../work/SVTdCore.h"
#include "../rendercore/SVGL/SVRendererGL.h"
#include "../rendercore/SVGL/SVRTexGL.h"
#include "../rendercore/SVVulkan/SVRendererVK.h"

using namespace sv;

SVTexturePList::SVTexturePList(SVInstPtr _app)
: SVTexture(_app) {
    m_rot = false;
    m_trim = false;
    m_srcw = 1;
    m_srch = 1;
    m_bApply = false;
    m_bApplyData = false;
    m_btexSet = false;
}

SVTexturePList::~SVTexturePList() {
    m_restex = nullptr;
}

void SVTexturePList::init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate){
    m_name = _name;
//    m_width = _width;
//    m_height = _height;
//    m_type = _type;
//    m_informate = _informate;
//    m_dataformate = _dateformate;
}


void SVTexturePList::create(SVRendererPtr _renderer){
//    SVRRes::create(_renderer);
//    if (!m_bCreated) {
//        m_bCreated = true;
//        SVRendererPtr t_renderBasePtr = mApp->getRenderer();
//        SVRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<SVRendererGL>(t_renderBasePtr);
//        if (t_renderGLPtr) {
//            //渲染器类型E_RENDERER_GLES,
//            m_restex = MakeSharedPtr<SVRTexGLPlist>(mApp);
//
//        }
//        SVRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<SVRendererVK>(t_renderBasePtr);
//        if (t_rendeVKPtr) {
//            //渲染器类型E_RENDERER_VUNKAN,
//
//        }
//        //    SVRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<SVRendererMetal>(t_renderBasePtr);
//        //    if (t_rendeMetalPtr) {
//        //        //渲染器类型E_RENDERER_METAL,
//        //
//        //    }
//    }
}

void SVTexturePList::destroy(SVRendererPtr _renderer){
    //SVRRes::destroy(_renderer);
}

void SVTexturePList::refreshParam(){
//    SVRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        t_tmp->refreshParam();
//    }
}

void SVTexturePList::apply(){
    m_bApply = true;
}

void SVTexturePList::apply(void *data){
//    m_pApplyData->writeData(data, m_srcw*m_srch*4);
//    m_bApplyData = true;
    m_bApply = true;
}

void SVTexturePList::commit(){
//    SVRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        t_tmp->commit();
//    }
}

SVRect *SVTexturePList::getSrcRect() {
//    SVRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        return t_tmp->getSrcRect();
//    }
    return nullptr;
}

SVRect *SVTexturePList::getDstRect() {
//    SVRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<SVRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        return t_tmp->getDstRect();
//    }
    return nullptr;
}

void SVTexturePList::setRot(bool _rot){
    m_rot = _rot;
}

void SVTexturePList::setTrim(bool _trim){
    m_trim = _trim;
}

void SVTexturePList::setSrcw(bool _srcw){
    m_srcw = _srcw;
}

void SVTexturePList::setSrch(bool _srch){
    m_srch = _srch;
}

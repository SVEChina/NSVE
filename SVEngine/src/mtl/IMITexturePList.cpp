//
// IMITexturePList.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITexturePList.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../work/IMITdCore.h"
#include "../rendercore/IMIGL/IMIRendererGL.h"
#include "../rendercore/IMIGL/IMIRTexGL.h"

using namespace imi;

IMITexturePList::IMITexturePList(IMIInstPtr _app)
: IMITexture(_app) {
    m_rot = false;
    m_trim = false;
    m_srcw = 1;
    m_srch = 1;
    m_bApply = false;
    m_bApplyData = false;
    m_btexSet = false;
}

IMITexturePList::~IMITexturePList() {
}

void IMITexturePList::init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate){
    m_name = _name;
//    m_width = _width;
//    m_height = _height;
//    m_type = _type;
//    m_informate = _informate;
//    m_dataformate = _dateformate;
}


void IMITexturePList::create(IMIRendererPtr _renderer){
//    IMIRRes::create(_renderer);
//    if (!m_bCreated) {
//        m_bCreated = true;
//        IMIRendererPtr t_renderBasePtr = mApp->getRenderer();
//        IMIRendererGLPtr t_renderGLPtr = std::dynamic_pointer_cast<IMIRendererGL>(t_renderBasePtr);
//        if (t_renderGLPtr) {
//            //渲染器类型E_RENDERER_GLES,
//            m_restex = MakeSharedPtr<IMIRTexGLPlist>(mApp);
//
//        }
//        IMIRendererVKPtr t_rendeVKPtr = std::dynamic_pointer_cast<IMIRendererVK>(t_renderBasePtr);
//        if (t_rendeVKPtr) {
//            //渲染器类型E_RENDERER_VUNKAN,
//
//        }
//        //    IMIRendererMetalPtr t_rendeMetalPtr = std::dynamic_pointer_cast<IMIRendererMetal>(t_renderBasePtr);
//        //    if (t_rendeMetalPtr) {
//        //        //渲染器类型E_RENDERER_METAL,
//        //
//        //    }
//    }
}

void IMITexturePList::destroy(IMIRendererPtr _renderer){
    //IMIRRes::destroy(_renderer);
}

void IMITexturePList::refreshParam(){
//    IMIRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<IMIRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        t_tmp->refreshParam();
//    }
}

void IMITexturePList::apply(){
    m_bApply = true;
}

void IMITexturePList::apply(void *data){
//    m_pApplyData->writeData(data, m_srcw*m_srch*4);
//    m_bApplyData = true;
    m_bApply = true;
}

void IMITexturePList::commit(){
//    IMIRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<IMIRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        t_tmp->commit();
//    }
}

IMIRect *IMITexturePList::getSrcRect() {
//    IMIRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<IMIRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        return t_tmp->getSrcRect();
//    }
    return nullptr;
}

IMIRect *IMITexturePList::getDstRect() {
//    IMIRTexGLPlistPtr t_tmp = std::dynamic_pointer_cast<IMIRTexGLPlist>(m_restex);
//    if (t_tmp) {
//        return t_tmp->getDstRect();
//    }
    return nullptr;
}

void IMITexturePList::setRot(bool _rot){
    m_rot = _rot;
}

void IMITexturePList::setTrim(bool _trim){
    m_trim = _trim;
}

void IMITexturePList::setSrcw(bool _srcw){
    m_srcw = _srcw;
}

void IMITexturePList::setSrch(bool _srch){
    m_srch = _srch;
}

//
// SVADFilterBase.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVADFilterBase.h"
#include "SVTexMgr.h"
#include "SVTexture.h"
#include "SVMtlBasedOn.h"
#include "SVMtlShinning.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

SVADFilterBase::SVADFilterBase(SVInstPtr _app, SVMtlCorePtr _mtl)
:SVFilterBase(_app){
    m_name = "SVADFilterBase";
    m_mtl = _mtl;
}

SVADFilterBase::~SVADFilterBase(){
    m_mtl = nullptr;
}

bool SVADFilterBase::create(){
    if (!m_mtl) {
        return false;
    }
//    SVRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return false;
//    //SVTexturePtr t_tex = t_renderer->getSVTex(E_TEX_MAIN);
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<SVMultPassNode>(mApp);
//    m_pPassNode->setname("SVAdvanceFilterNode");
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //创建pass
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>();
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setOutTex(E_TEX_FILTER_1);
//    m_pPassNode->addPass(t_pass1);
//
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    SVMtlCorePtr t_mtl_back= MakeSharedPtr<SVMtlCore>(mApp,"screen");
//    //t_pass2->setMtl(t_mtl_back);
//    t_pass2->setInTex(0, E_TEX_FILTER_1);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void SVADFilterBase::destroy(){
}

void SVADFilterBase::update(f32 dt){
//    //
//    if(m_pPassNode && m_mtl){
//        m_mtl->update(dt);
//    }
}

void SVADFilterBase::setFilterMtl(SVMtlADFilterBasePtr _mtl){
//    if (_mtl && m_pPassNode) {
//        m_mtl = _mtl;
////        SVPassPtr t_pass1 = m_pPassNode->getPass(0);
////        if (t_pass1) {
////            //t_pass1->setMtl(m_mtl);
////            t_pass1->setInTex(0,E_TEX_MAIN);
////            t_pass1->setOutTex(E_TEX_FILTER_1);
////        }
//    }
}

void SVADFilterBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                         RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void SVADFilterBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    if (item.HasMember("data") && item["data"].IsString()) {
//        SVRendererPtr t_renderer = mApp->getRenderer();
//        if(t_renderer){
//            t_renderer->createSVTex(E_TEX_FILTER_LUT, 512, 512, GL_RGBA,GL_RGBA);
//            SVTexturePtr t_tex=t_renderer->getSVTex(E_TEX_FILTER_LUT);
//            t_tex->setTexData((void*)item["data"].GetString(), item["data"].GetStringLength());
//            setLUTTex(t_tex);
//        }
//    }
}


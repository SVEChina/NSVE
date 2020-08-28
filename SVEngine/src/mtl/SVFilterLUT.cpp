//
//  SVFilterLUT.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVFilterLUT.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

SVFilterLUT::SVFilterLUT(SVInstPtr _app)
:SVFilterBase(_app){
    m_name = "SVFilterLUT";
    m_texLUT = nullptr;
    m_dirtyLUT = false;
}

SVFilterLUT::~SVFilterLUT(){
    m_texLUT = nullptr;
}

bool SVFilterLUT::create(){
//    SVTexturePtr t_tex = t_renderer->getSVTex(E_TEX_MAIN);
//    s32 t_w = 0;//t_tex->m_width;
//    s32 t_h = 0;//t_tex->m_height;
////    t_renderer->createSVTex(E_TEX_FILTER_LUT_OUT, t_w, t_h, GL_RGBA);
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<SVMultPassNode>(mApp);
//    m_pPassNode->setname("SVLookUpTableNode");
//    //m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //创建pass
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>(mApp);
    //SVMtlCorePtr t_lkMtl=MakeSharedPtr<SVMtlCore>(mApp,"lookup");
    //t_lkMtl->setTexcoordFlip(1.0f, 1.0f);
    //t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setInTex(1,m_texLUT);
//    t_pass1->setOutTex(E_TEX_FILTER_LUT_OUT);
//    m_pPassNode->addPass(t_pass1);
//    SVSpriteNodePtr node=MakeSharedPtr<SVSpriteNode>(mApp,512,512);
//    node->setTexture(E_TEX_FILTER_LUT);
//
//    SVScenePtr t_sc = mApp->getSceneMgr()->getScene();
//    if(t_sc){
//        if(node){
//            t_sc->addNode(node);
//        }
//    }
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>(mApp);
//    SVMtlCorePtr t_mtl_back=MakeSharedPtr<SVMtlCore>(mApp,"screennor");
//  t_mtl_back->setTexcoordFlip(1.0f, 1.0f);
    //t_pass2->setMtl(t_mtl_back);
//    t_pass2->setInTex(0, E_TEX_FILTER_LUT_OUT);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void SVFilterLUT::destroy(){
    m_texLUT = nullptr;
}

void SVFilterLUT::setLUTTex(SVTexturePtr _looktex) {
    if(m_texLUT!=_looktex) {
        m_texLUT = _looktex;
        m_dirtyLUT = true;
    }
}

SVTexturePtr SVFilterLUT::getLUTTex() {
    return m_texLUT;
}

void SVFilterLUT::update(f32 _dt){
    m_mtl = mApp->getMtlLib()->getMtl("filter-lut");
    if(m_mtl) {
        m_mtl->update(_dt);
    }
    if(m_surface) {
        m_surface->setTexture(1, m_texLUT, 1);
    }
    SVFilterBase::update(_dt);
}

void SVFilterLUT::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void SVFilterLUT::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
//    if (item.HasMember("data") && item["data"].IsString()) {
//    }
}


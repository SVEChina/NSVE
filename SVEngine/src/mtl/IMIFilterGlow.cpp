//
//  IMIFilterGlow.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/27.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIFilterGlow.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIFilterGlow::IMIFilterGlow(IMIInstPtr _app)
:IMIFilterBase(_app){
    m_name="IMIFilterGlow";
    m_smooth=0.0f;
}

IMIFilterGlow::~IMIFilterGlow(){
}

bool IMIFilterGlow::create(IMI_TEXIN _inType,IMI_TEXIN _outType){
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return false;
//    IMITexturePtr t_tex = t_renderer->getIMITex(_inType);
//    s32 t_w = t_tex->m_width;
//    s32 t_h = t_tex->m_height;
//
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GLOW_1) ){
//        t_renderer->createIMITex(E_TEX_FILTER_GLOW_1,t_w, t_h, GL_RGBA);
//    }
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GLOW_2) ){
//        t_renderer->createIMITex(E_TEX_FILTER_GLOW_2,t_w/2, t_h/2, GL_RGBA);
//    }
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GLOW_3) ){
//        t_renderer->createIMITex(E_TEX_FILTER_GLOW_3,t_w/2, t_h/2, GL_RGBA);
//    }
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->setname("IMIFilterGlowNode");
//    m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(m_rstype);
//    //创建pass
//    IMIPassPtr t_pass1 = MakeSharedPtr<IMIPass>();
//    IMIMtlCorePtr t_lkMtl=MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    t_lkMtl->setTexcoordFlip(1.0f, 1.0f);
//    t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,_inType);
//    t_pass1->setOutTex(E_TEX_FILTER_GLOW_1);
//    m_pPassNode->addPass(t_pass1);
//
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    IMIMtlSmoothPtr t_lkMtl02=MakeSharedPtr<IMIMtlSmooth>(mApp,"blurtex");
//    t_lkMtl02->setTexcoordFlip(1.0f, 1.0f);
//    t_lkMtl02->setImgWH(4.0/t_w,0.0);
//    t_lkMtl02->setTextureParam(0, E_T_PARAM_WRAP_S, E_T_WRAP_REPEAT);
//    t_lkMtl02->setTextureParam(0, E_T_PARAM_WRAP_T, E_T_WRAP_REPEAT);
//    t_pass1->setMtl(t_lkMtl02);
//    t_pass1->setInTex(0,E_TEX_FILTER_GLOW_1);
//    t_pass1->setOutTex(E_TEX_FILTER_GLOW_2);
//    m_pPassNode->addPass(t_pass1);
////
//    IMIMtlSmoothPtr t_lkMtl01=MakeSharedPtr<IMIMtlSmooth>(mApp,"blurtex");
//    t_lkMtl01->setTexcoordFlip(1.0f, 1.0f);
//    t_lkMtl01->setImgWH(0.0 ,4.0/t_h);
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    t_pass1->setMtl(t_lkMtl01);
//    t_pass1->setInTex(0,E_TEX_FILTER_GLOW_2);
//    t_pass1->setOutTex(E_TEX_FILTER_GLOW_3);
//    m_pPassNode->addPass(t_pass1);
//
//    IMIPassPtr t_pass2 = MakeSharedPtr<IMIPass>();
//    m_mtl_smooth =MakeSharedPtr<IMIMtlSmooth>(mApp,"glow");
//    m_mtl_smooth->setTexcoordFlip(1.0, 1.0);
//    m_mtl_smooth->setImgWH(t_w,t_h);
//    t_pass2->setMtl(m_mtl_smooth);
//    t_pass2->setInTex(0, E_TEX_FILTER_GLOW_3);
//    t_pass2->setInTex(1, _inType);
//    t_pass2->setOutTex(_outType);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void IMIFilterGlow::destroy(){
}

void IMIFilterGlow::update(f32 dt){
   // m_mtl_smooth->setSmooth(1.0);
}

void IMIFilterGlow::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                         RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void IMIFilterGlow::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

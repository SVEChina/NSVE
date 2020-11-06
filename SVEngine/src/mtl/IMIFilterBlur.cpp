//
//  IMIFilterBlur.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/27.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIFilterBlur.h"
#include "../core/IMIPass.h"
#include "IMIMtlSmooth.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIFilterBlur::IMIFilterBlur(IMIInstPtr _app)
:IMIFilterBase(_app){
    m_name="IMIFilterBlur";
    m_smooth=1.0f;
}

IMIFilterBlur::~IMIFilterBlur(){
}

bool IMIFilterBlur::create(IMI_TEXIN _inType,IMI_TEXIN _outType){
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return false;
//    IMITexturePtr t_tex = t_renderer->getIMITex(_inType);
//    s32 t_w = t_tex->m_width;
//    s32 t_h = t_tex->m_height;
//    
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GLOW_2) ){
//        t_renderer->createIMITex(E_TEX_FILTER_GLOW_2,t_w/2, t_h/2, GL_RGBA);
//        t_renderer->createIMITex(E_TEX_FILTER_GLOW_3,t_w/2, t_h/2, GL_RGBA);
//    }
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->setname("IMIFilterBlurNode");
//    m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(m_rstype);
//    //创建pass
//    IMIPassPtr t_pass1 = MakeSharedPtr<IMIPass>();
//    m_lkMtl01=MakeSharedPtr<IMIMtlSmooth>(mApp,"newblur");
//    m_lkMtl01->setTexcoordFlip(1.0f, 1.0f);
//    m_lkMtl01->setImgWH(1.0/(t_w/2),0.0);
//    m_lkMtl01->setSmooth(m_smooth);
//    t_pass1->setMtl(m_lkMtl01);
//    t_pass1->setInTex(0,_inType);
//    t_pass1->setOutTex(E_TEX_FILTER_GLOW_2);
//    m_pPassNode->addPass(t_pass1);
//    //
//    m_lkMtl02=MakeSharedPtr<IMIMtlSmooth>(mApp,"newblur");
//    m_lkMtl02->setTexcoordFlip(1.0f, 1.0f);
//    m_lkMtl02->setImgWH(0.0 ,1.0/(t_h/2));
//    m_lkMtl02->setSmooth(m_smooth);
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    t_pass1->setMtl(m_lkMtl02);
//    t_pass1->setInTex(0,E_TEX_FILTER_GLOW_2);
//    t_pass1->setOutTex(E_TEX_FILTER_GLOW_3);
//    m_pPassNode->addPass(t_pass1);
//    
//    IMIMtlCorePtr t_lkMtl=MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    t_lkMtl->setTexcoordFlip(1.0f, 1.0f);
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,E_TEX_FILTER_GLOW_3);
//    t_pass1->setOutTex(_outType);
//    m_pPassNode->addPass(t_pass1);
   
    return true;
}

void IMIFilterBlur::destroy(){
}


void IMIFilterBlur::update(f32 dt){
    m_lkMtl01->setSmooth(m_smooth);
    m_lkMtl02->setSmooth(m_smooth);
}

void IMIFilterBlur::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                          RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void IMIFilterBlur::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

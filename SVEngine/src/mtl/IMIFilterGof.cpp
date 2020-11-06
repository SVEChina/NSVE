//
//  IMIFilterGof.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/27.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIFilterGof.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIFilterGof::IMIFilterGof(IMIInstPtr _app)
:IMIFilterBase(_app){
    m_name="IMIFilterGof";
    m_smooth=0.0f;
}

IMIFilterGof::~IMIFilterGof(){
}

bool IMIFilterGof::create(){
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer)
        return false;
    //IMITexturePtr t_tex = t_renderer->getIMITex(E_TEX_MAIN);
//    s32 t_w = t_tex->m_width;
//    s32 t_h = t_tex->m_height;
//    if(! t_renderer->getIMITex(E_TEX_HELP0) ){
//        t_renderer->createIMITex(E_TEX_HELP0,t_w, t_h, GL_RGBA);
//    }
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GOF_1) ){
//        t_renderer->createIMITex(E_TEX_FILTER_GOF_1,t_w, t_h, GL_RGBA);
//    }
//    if(! t_renderer->getIMITex(E_TEX_FILTER_GOF_2) ){
//         t_renderer->createIMITex(E_TEX_FILTER_GOF_2,t_w/2, t_h/2, GL_RGBA);
//    }
//
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->setname("IMIFilterGOFNode");
//    //m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //创建pass
//    IMIPassPtr t_pass1 = MakeSharedPtr<IMIPass>();
//    IMIMtlCorePtr t_lkMtl=MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    //t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setOutTex(E_TEX_HELP0);
//    m_pPassNode->addPass(t_pass1);
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    IMIMtlSmoothPtr t_lkMtl02=MakeSharedPtr<IMIMtlSmooth>(mApp,"blurtex");
//    //t_lkMtl02->setImgWH(t_w/2,t_h/2);
//    //t_pass1->setMtl(t_lkMtl02);
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setOutTex(E_TEX_FILTER_GOF_1);
//    m_pPassNode->addPass(t_pass1);
//    
//    IMIMtlSmoothPtr t_lkMtl01=MakeSharedPtr<IMIMtlSmooth>(mApp,"blurtex");
//    ///t_lkMtl01->setImgWH(t_w/2,t_h/2);
//    t_pass1 = MakeSharedPtr<IMIPass>();
//    //t_pass1->setMtl(t_lkMtl01);
//    t_pass1->setInTex(0,E_TEX_FILTER_GOF_1);
//    t_pass1->setOutTex(E_TEX_FILTER_GOF_2);
//    m_pPassNode->addPass(t_pass1);
//    
//    IMIPassPtr t_pass2 = MakeSharedPtr<IMIPass>();
//    m_mtl_smooth =MakeSharedPtr<IMIMtlSmooth>(mApp,"gof");
//    //m_mtl_smooth->setImgWH(t_w,t_h);
//    //t_pass2->setMtl(m_mtl_smooth);
//    t_pass2->setInTex(0, E_TEX_HELP0);
//    t_pass2->setInTex(1, E_TEX_FILTER_GOF_2);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void IMIFilterGof::destroy(){
}

void IMIFilterGof::update(f32 dt){
    //m_mtl_smooth->setSmooth(3.5);
}

void IMIFilterGof::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                             RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void IMIFilterGof::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

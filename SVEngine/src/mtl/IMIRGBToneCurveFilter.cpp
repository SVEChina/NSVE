//
// IMIRGBToneCurveFilter.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRGBToneCurveFilter.h"
#include "../core/IMIPass.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlBasedOn.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIRGBToneCurveFilter::IMIRGBToneCurveFilter(IMIInstPtr _app)
:IMIFilterBase(_app){
    m_name="IMIRGBToneCurveFilter";
    m_mtl_rgba = nullptr;
    m_mtl_back = nullptr;
    texrgb = nullptr;
}

IMIRGBToneCurveFilter::~IMIRGBToneCurveFilter(){
    destroy();
}

bool IMIRGBToneCurveFilter::create() {
//    IMIRendererPtr t_renderer = mApp->getRenderer();
//    if(!t_renderer)
//        return false;
//    s32 t_w =  mApp->m_global_param.sv_width;
//    s32 t_h =  mApp->m_global_param.sv_height;
//    //增加pass
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //
//    texrgb = mApp->getTexMgr()->createUnctrlTexture(256, 1, GL_RGBA, GL_RGBA);
//    //
//    if(! t_renderer->getIMITex(E_TEX_HELP1) ){
//        t_renderer->createIMITex(E_TEX_HELP1,t_w, t_h, GL_RGBA);
//    }
//    //
//    m_mtl_rgba = MakeSharedPtr<IMIMtlCore>(mApp,"rgbaFilter");
//    m_mtl_rgba->setTexcoordFlip(1.0f, 1.0f);
//    m_mtl_rgba->setTexSizeIndex(1,0.5/t_w,0.5/ t_h);
//    IMIPassPtr t_pass = MakeSharedPtr<IMIPass>();
//    //t_pass->setMtl(m_mtl_rgba);
//    t_pass->setInTex(0, E_TEX_MAIN);
//    t_pass->setInTex(1, texrgb);
//    t_pass->setOutTex(E_TEX_HELP0);
//    m_pPassNode->addPass(t_pass);
//    //写回
//    m_mtl_back = MakeSharedPtr<IMIMtlCore>(mApp,"screen");
//    m_mtl_back->setTexcoordFlip(1.0f, 1.0f);
//    t_pass = MakeSharedPtr<IMIPass>();
//    //t_pass->setMtl(m_mtl_back);
//    t_pass->setInTex(0, E_TEX_HELP0);
//    t_pass->setOutTex( E_TEX_MAIN );
//    m_pPassNode->addPass(t_pass);
    return true;
}

void IMIRGBToneCurveFilter::destroy() {
    m_mtl_rgba = nullptr;
    m_mtl_back = nullptr;
    texrgb = nullptr;
}

void IMIRGBToneCurveFilter::update(f32 dt){
    
}

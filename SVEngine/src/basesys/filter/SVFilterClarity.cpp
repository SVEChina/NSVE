//
//  SVFilterClarity.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2019/3/25.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "SVFilterClarity.h"
#include "../../core/SVPass.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVMtlSmooth.h"
#include "../../rendercore/SVRenderer.h"
#include "../../rendercore/SVRenderMgr.h"

using namespace sv;

SVFilterClarity::SVFilterClarity(SVInstPtr _app)
:SVFilterBase(_app){
    m_type=SV_FUNC_CLARITY;
    m_name="SVFilterClarity";
    m_smooth=0.0f;
}

SVFilterClarity::~SVFilterClarity(){
}

bool SVFilterClarity::create(){
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer)
        return false;
    //SVTexturePtr t_tex = t_renderer->getSVTex(E_TEX_MAIN);
//    s32 t_w = t_tex->m_width;
//    s32 t_h = t_tex->m_height;
//    if(! t_renderer->getSVTex(E_TEX_FILTER_MIP_1) ){
//        t_renderer->createSVTex(E_TEX_FILTER_MIP_1,t_w, t_h, GL_RGBA,true);
//    }
//    //创建多passnode
//    m_pPassNode = MakeSharedPtr<SVMultPassNode>(mApp);
//    m_pPassNode->setname("SVFilterClarityNode");
//    //m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //创建pass
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>();
//    SVMtlCorePtr t_lkMtl=MakeSharedPtr<SVMtlCore>(mApp,"screennor");
//    //t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setOutTex(E_TEX_FILTER_MIP_1);
//    m_pPassNode->addPass(t_pass1);
//
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    m_mtl_smooth =MakeSharedPtr<SVMtlSmooth>(mApp,"Clarity");
//    //m_mtl_smooth->setImgWH(t_w,t_h);
//    //t_pass2->setMtl(m_mtl_smooth);
//    t_pass2->setInTex(0, E_TEX_FILTER_MIP_1);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void SVFilterClarity::destroy(){
}

void SVFilterClarity::update(f32 dt){
    //m_mtl_smooth->setSmooth(m_smooth);
}

void SVFilterClarity::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                         RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void SVFilterClarity::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

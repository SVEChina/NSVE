//
//  SVFilterHaze.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2019/3/25.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "SVFilterHaze.h"
#include "../../core/SVPass.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVMtlSmooth.h"
#include "../../rendercore/SVRenderer.h"
#include "../../rendercore/SVRenderMgr.h"

using namespace sv;

SVFilterHaze::SVFilterHaze(SVInstPtr _app)
:SVFilterBase(_app){
    m_type=SV_FUNC_HAZE;
    m_name="SVFilterHaze";
    m_smooth=0.0f;
}

SVFilterHaze::~SVFilterHaze(){
}

bool SVFilterHaze::create(){
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer)
        return false;
    //SVTexturePtr t_tex = t_renderer->getSVTex(E_TEX_MAIN);
    //创建多passnode
//    m_pPassNode = MakeSharedPtr<SVMultPassNode>(mApp);
//    m_pPassNode->setname("SVFilterHazeNode");
//    //m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_IMGFILTER);
//    //创建pass
//    SVPassPtr t_pass1 = MakeSharedPtr<SVPass>();
//    SVMtlCorePtr t_lkMtl=MakeSharedPtr<SVMtlCore>(mApp,"screennor");
//    //t_pass1->setMtl(t_lkMtl);
//    t_pass1->setInTex(0,E_TEX_MAIN);
//    t_pass1->setOutTex(E_TEX_HELP0);
//    m_pPassNode->addPass(t_pass1);
//    
//    SVPassPtr t_pass2 = MakeSharedPtr<SVPass>();
//    m_mtl_smooth =MakeSharedPtr<SVMtlSmooth>(mApp,"haze");
//    //t_pass2->setMtl(m_mtl_smooth);
//    t_pass2->setInTex(0, E_TEX_HELP0);
//    t_pass2->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass2);
    return true;
}

void SVFilterHaze::destroy(){
}

void SVFilterHaze::update(f32 dt){
    //m_mtl_smooth->setSmooth(m_smooth);
}

void SVFilterHaze::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                             RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void SVFilterHaze::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

//
//  IMIMtlSmooth.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/26.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIMtlSmooth.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMIMtlSmooth::IMIMtlSmooth(IMIInstPtr _app , IMIString _name)
:IMIMtlCore(_app,_name.c_str()) {
    m_smooth = 0.0f;
    m_w = 0.0f;
    m_h = 0.0f;
}

IMIMtlSmooth::IMIMtlSmooth(IMIMtlSmooth* _mtl)
:IMIMtlCore(_mtl){
    m_smooth = _mtl->m_smooth;
    m_w = _mtl->m_w;
    m_h = _mtl->m_h;
}

IMIMtlSmooth::~IMIMtlSmooth(){
    
}

IMIMtlCorePtr IMIMtlSmooth::clone(){
    return PointerSharedPtr<IMIMtlSmooth>(new IMIMtlSmooth(this));
}

void IMIMtlSmooth::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("m_smooth", m_smooth);
//    _render->submitUniformf("m_width", m_w);
//    _render->submitUniformf("m_height", m_h);
}

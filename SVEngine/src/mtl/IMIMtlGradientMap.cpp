//
//  IMIMtlGradientMap.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/3/22.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIMtlGradientMap.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMIMtlGradientMap::IMIMtlGradientMap(IMIInstPtr _app)
:IMIMtlCore(_app,"GradientMap") {
    
}

IMIMtlGradientMap::IMIMtlGradientMap(IMIMtlGradientMap* _mtl)
:IMIMtlCore(_mtl){
    m_lSmoothSize = _mtl->m_lSmoothSize;
}

IMIMtlGradientMap::~IMIMtlGradientMap(){
}

IMIMtlCorePtr IMIMtlGradientMap::clone(){
     return PointerSharedPtr<IMIMtlGradientMap>(new IMIMtlGradientMap(this));
}

void IMIMtlGradientMap::setSmooth(f32 _smooth){
    if (_smooth >= 0.0) {
        m_lSmoothSize = clamp(0.0f,_smooth,1.0f);
    }
}

void IMIMtlGradientMap::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformf("softenStrength", m_lSmoothSize);
}


//
//  IMIMtlShadowMapping.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2019/9/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "IMIMtlShadowMapping.h"
#include "../mtl/IMITexMgr.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

//
IMIMtlShadowMapping::IMIMtlShadowMapping(IMIInstPtr _app)
:IMIMtlCore(_app,"depthPlan") {
 
}

IMIMtlShadowMapping::IMIMtlShadowMapping(IMIMtlShadowMapping* _mtl)
:IMIMtlCore(_mtl) {
    memcpy(m_LightVPMat, _mtl->m_LightVPMat, sizeof(f32) * 16);
}

IMIMtlShadowMapping::~IMIMtlShadowMapping(){
}

void IMIMtlShadowMapping::setLightVPMat(f32 *_vp){
      memcpy(m_LightVPMat, _vp, sizeof(f32) * 16);
}

IMIMtlCorePtr IMIMtlShadowMapping::clone() {
    return PointerSharedPtr<IMIMtlShadowMapping>(new IMIMtlShadowMapping(this));
}

void IMIMtlShadowMapping::_submitMtl(IMIRendererPtr _render) {
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformMatrix("aMatrixVPlight", m_LightVPMat);
}




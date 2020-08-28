//
//  SVFilterCommon.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVFilterCommon.h"
#include "../../basesys/SVComData.h"
#include "../../mtl/SVMtlLib.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVSurface.h"
#include "../../rendercore/SVRenderCmd.h"
#include "../../rendercore/SVRenderer.h"
#include "../../rendercore/SVRTarget.h"

using namespace sv;

SVFilterCommon::SVFilterCommon(SVInstPtr _app)
:SVFilterBase(_app){
    m_name = "SVFilterCommon";
    m_mtl_name = "";
}

SVFilterCommon::~SVFilterCommon(){
}

bool SVFilterCommon::create(){
    SVFilterBase::create();
    return false;
}

void SVFilterCommon::destroy() {
    SVFilterBase::destroy();
}

void SVFilterCommon::update(f32 _dt) {
    //获取材质
    m_mtl = mApp->getMtlLib()->getMtl(m_mtl_name.c_str());
    if(m_mtl) {
        m_mtl->update(_dt);
    }
    SVFilterBase::update(_dt);
}

//
//  SVLuaSys.cpp
//  SVEngine
//
//  Created by 付一洲 on 2019/2/28.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "SVLuaSys.h"

using namespace sv;

SVLuaSys::SVLuaSys(SVInstPtr _app)
:SVSysBase(_app) {
    m_subsysType = 1;
}

SVLuaSys::~SVLuaSys() {
}

void SVLuaSys::init() {
    //Py_Initialize();    // 初始化
}

void SVLuaSys::destroy() {
}

void SVLuaSys::update(f32 dt) {
}

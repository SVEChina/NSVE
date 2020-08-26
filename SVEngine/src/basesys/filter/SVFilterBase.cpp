//
//  SVFilterBase.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVFilterBase.h"
#include "../../node/SVMultPassNode.h"
#include "../../rendercore/SVRenderCmd.h"

using namespace sv;

SVFilterBase::SVFilterBase(SVInstPtr _app)
:SVGBaseEx(_app){
    m_name = "SVFilterBase";
    m_mtl = nullptr;
    m_type = SV_FUNC_NONE;
    m_rstype = RST_IMGFILTER;
}

SVFilterBase::~SVFilterBase(){
     m_mtl = nullptr;
}

bool SVFilterBase::create(){
    return false;
}

void SVFilterBase::destroy() {
    m_mtl = nullptr;
}

void SVFilterBase::update(f32 dt) {
    //使用辅助的的target
    
    //产生pass 投递到不同的对方
    SVRCmdPassPtr t_pass = MakeSharedPtr<SVRCmdPass>();
    //t_pass->setTarget
}

void SVFilterBase::setFilterParam(f32 _smooth,SVFILTERITEMTYPE _type) {
}

f32 SVFilterBase::getFilterParam(SVFILTERITEMTYPE _type) {
    return 0;
}

void SVFilterBase::setVisible(bool _visible) {
}

//序列化
void SVFilterBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

void SVFilterBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    
}

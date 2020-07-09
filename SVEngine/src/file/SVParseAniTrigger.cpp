//
// SVParseAniTrigger.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVParseAniTrigger.h"
#include "../act/SVAniTrigger.h"

using namespace sv;

SVAniTriggerPtr SVParseAniTrigger::parseAniTrigger(SVInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    SVAniTriggerPtr trigger = MakeSharedPtr<SVAniTrigger>(_app);
    trigger->init();
    trigger->fromJson(item);
    return trigger;
}

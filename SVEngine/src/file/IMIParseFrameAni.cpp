//
// IMIParseFrameAni.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseFrameAni.h"
#include "../node/IMIFrameAniNode.h"

using namespace imi;

IMINodePtr
IMIParseFrameAni::parseFrameAni(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMIFrameAniNodePtr t_aniNode = MakeSharedPtr<IMIFrameAniNode>(_app);
    t_aniNode->m_rootPath = _path;
    t_aniNode->fromJSON(item);
    return t_aniNode;
}



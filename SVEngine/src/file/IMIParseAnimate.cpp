//
// IMIParseAnimate.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseAnimate.h"
#include "../node/IMISpineNode.h"

using namespace imi;

IMINodePtr
IMIParseAnimate::parseAnim(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMISpineNodePtr t_spineNode = MakeSharedPtr<IMISpineNode>(_app);
    t_spineNode->m_rootPath = _path;
    t_spineNode->fromJSON(item);
    return t_spineNode;
}

IMINodePtr IMIParseGLTF::parseGLTF(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
//    IMISpineNodePtr t_spineNode = MakeSharedPtr<IMISpineNode>(_app);
//    t_spineNode->m_rootPath = _path;
//    t_spineNode->fromJSON(item);
//    return t_spineNode;
    return nullptr;
}


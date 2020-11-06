//
// IMIParseBMFont.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseBMFont.h"
#include "../node/IMIBMFontNode.h"

using namespace imi;

IMINodePtr
IMIParseBMFont::parseBMFont(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMIBMFontNodePtr t_bmFontNode = MakeSharedPtr<IMIBMFontNode>(_app);
    t_bmFontNode->m_rootPath = _path;
    t_bmFontNode->fromJSON(item);
    return t_bmFontNode;
}

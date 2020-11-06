//
// IMIParseBitfont.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseBitfont.h"
#include "../node/IMIBitFontNode.h"

using namespace imi;

//解析面具
IMINodePtr
IMIParseBitfont::parseBitfont(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMIBitFontNodePtr t_bitFontNode = MakeSharedPtr<IMIBitFontNode>(_app);
    t_bitFontNode->m_rootPath = _path;
    t_bitFontNode->fromJSON(item);
    return t_bitFontNode;
}

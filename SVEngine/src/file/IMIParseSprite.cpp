//
// IMIParseSprite.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseSprite.h"
#include "../node/IMISpriteNode.h"

using namespace imi;

IMINodePtr
IMIParseSprite::parseSprite(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path) {
    IMISpriteNodePtr t_spriteNode = MakeSharedPtr<IMISpriteNode>(_app);
    t_spriteNode->m_rootPath = _path;
    t_spriteNode->fromJSON(item);
    return t_spriteNode;
}


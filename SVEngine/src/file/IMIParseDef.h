//
// IMIParseDef.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEDEF_H
#define IMI_PARSEDEF_H

#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"
#include "../base/IMIObject.h"
#include "../node/IMINodeDeclare.h"

typedef imi::IMINodePtr (*prase_content_fun)(imi::IMIInstPtr app,
                                  RAPIDJSON_NAMESPACE::Value &item,
                                  s32 _resid,
                                  cptr8 _path);

#endif //IMI_PARSEDEF_H

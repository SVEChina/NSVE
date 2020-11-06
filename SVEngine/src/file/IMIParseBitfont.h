//
// IMIParseBitfont.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEBITFONT_H
#define IMI_PARSEBITFONT_H

#include "IMIParseData.h"

namespace imi {
    
    
        
        class IMIParseBitfont : public IMIParseData {
        public:
            static IMINodePtr parseBitfont(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid,cptr8 _path);
        };

        
    
    
}//!namespace imi



#endif //IMI_PARSEBITFONT_H

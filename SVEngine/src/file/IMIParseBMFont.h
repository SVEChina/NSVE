//
// IMIParseBMFont.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEBMFONT_H
#define IMI_PARSEBMFONT_H

#include "IMIParseData.h"

namespace imi {
    
    
        
        class IMIParseBMFont : public IMIParseData {
        public:
            static IMINodePtr parseBMFont(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid,cptr8 _path);
        };

        
    
    
}//!namespace imi



#endif //IMI_PARSEBMFONT_H

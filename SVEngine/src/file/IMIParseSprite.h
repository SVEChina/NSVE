//
// IMIParseSprite.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSESPRITE_H
#define IMI_PARSESPRITE_H

#include "IMIParseData.h"

namespace imi {
    
    
        
        class IMIParseSprite : public IMIParseData {
        public:
            static IMINodePtr parseSprite(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid,cptr8 _path);
        };

        
    
    
}//!namespace imi



#endif //IMI_PARSESPRITE_H

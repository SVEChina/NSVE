//
// IMIParseMask.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEMASK_H
#define IMI_PARSEMASK_H

#include "IMIParseData.h"

namespace imi {
    
    
        
        class IMIParseMask : public IMIParseData {
        public:
            static IMINodePtr parseMask(IMIInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };

        
    
    
}//!namespace imi



#endif //IMI_PARSEMASK_H

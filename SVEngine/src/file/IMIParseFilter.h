//
// IMIParseFilter.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEFILTER_H
#define IMI_PARSEFILTER_H

#include "IMIParseData.h"
namespace imi {
    
    
        
        class IMIParseFilter : public IMIParseData {
        public:
            static IMIFilterBasePtr parseFilter(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace imi
#endif //IMI_PARSEFILTER_H

//
// SVParseFilter.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PARSEFILTER_H
#define SV_PARSEFILTER_H

#include "SVParseData.h"
namespace sv {
    
    
        
        class SVParseFilter : public SVParseData {
        public:
            static SVFilterBasePtr parseFilter(SVInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace sv
#endif //SV_PARSEFILTER_H

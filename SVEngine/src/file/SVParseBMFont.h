//
// SVParseBMFont.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PARSEBMFONT_H
#define SV_PARSEBMFONT_H

#include "SVParseData.h"

namespace sv {
    
    
        
        class SVParseBMFont : public SVParseData {
        public:
            static SVNodePtr parseBMFont(SVInstPtr _app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid,cptr8 _path);
        };

        
    
    
}//!namespace sv



#endif //SV_PARSEBMFONT_H

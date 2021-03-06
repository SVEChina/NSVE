//
// SVParseAnimate.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PARSEANIMATE_H
#define SV_PARSEANIMATE_H

#include "SVParseData.h"
//spine动画解析

namespace sv {
    
    
        
        class SVParseAnimate : public SVParseData {
        public:
            static SVNodePtr parseAnim(SVInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        //
        class SVParseGLTF : public SVParseData {
        public:
            static SVNodePtr parseGLTF(SVInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace sv



#endif //SV_PARSEANIMATE_H

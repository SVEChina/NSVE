//
// SVParseParticles.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PARSEPARTICLES_H
#define SV_PARSEPARTICLES_H

#include "SVParseData.h"
namespace sv {
    
    
        
        class SVParseParticles : public SVParseData {
        public:
            static SVNodePtr parseParticles(SVInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace sv
#endif //SV_PARSEPARTICLES_H

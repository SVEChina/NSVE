//
// IMIParseParticles.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEPARTICLES_H
#define IMI_PARSEPARTICLES_H

#include "IMIParseData.h"
namespace imi {
    
    
        
        class IMIParseParticles : public IMIParseData {
        public:
            static IMINodePtr parseParticles(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace imi
#endif //IMI_PARSEPARTICLES_H

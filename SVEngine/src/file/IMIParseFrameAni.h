//
// IMIParseFrameAni.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEFRAMEANI_H
#define IMI_PARSEFRAMEANI_H

#include "IMIParseData.h"
//spine动画解析

namespace imi {
    
    
        
        class IMIParseFrameAni : public IMIParseData {
        public:
            static IMINodePtr parseFrameAni(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace imi



#endif //IMI_PARSEFRAMEANI_H

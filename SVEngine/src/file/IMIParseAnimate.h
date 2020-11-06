//
// IMIParseAnimate.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PARSEANIMATE_H
#define IMI_PARSEANIMATE_H

#include "IMIParseData.h"
//spine动画解析

namespace imi {
    
    
        
        class IMIParseAnimate : public IMIParseData {
        public:
            static IMINodePtr parseAnim(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        //
        class IMIParseGLTF : public IMIParseData {
        public:
            static IMINodePtr parseGLTF(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace imi



#endif //IMI_PARSEANIMATE_H

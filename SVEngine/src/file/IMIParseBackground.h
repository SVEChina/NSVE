//
//  IMIParseBackground.h
//  IMIngine
//
//  Created by 徐子昱 on 2018/10/29.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef IMI_PARSEBACKGROUND_H
#define IMI_PARSEBACKGROUND_H

#include "IMIParseData.h"
//spine动画解析

namespace imi {
    
    
        
        class IMIParseBackground : public IMIParseData {
        public:
            static IMINodePtr parseDeform(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        };
        
    
    
}//!namespace imi


#endif /* IMI_PARSEBACKGROUND_H */

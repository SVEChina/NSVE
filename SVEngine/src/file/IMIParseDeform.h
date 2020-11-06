//
//  IMIParseDeform.h
//  IMIngine
//
//  Created by 徐子昱 on 2018/10/29.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef IMI_PARSEDEFORM_H
#define IMI_PARSEDEFORM_H

#include "IMIParseData.h"

//spine动画解析

namespace imi {
    
    class IMIParseDeform : public IMIParseData {
    public:
        static IMIDeformImageMovePtr parseDeform(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        static void parse(IMIInstPtr app,cptr8 path, s32 resid,IMIDeformImageMovePtr _deform);
    };
        
    
    
}//!namespace imi



#endif //IMI_PARSEDEFORM_H


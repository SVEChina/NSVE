//
//  SVParseDeform.h
//  SVEngine
//
//  Created by 徐子昱 on 2018/10/29.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#ifndef SV_PARSEDEFORM_H
#define SV_PARSEDEFORM_H

#include "SVParseData.h"

//spine动画解析

namespace sv {
    
    class SVParseDeform : public SVParseData {
    public:
        static SVDeformImageMovePtr parseDeform(SVInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path);
        static void parse(SVInstPtr app,cptr8 path, s32 resid,SVDeformImageMovePtr _deform);
    };
        
    
    
}//!namespace sv



#endif //SV_PARSEDEFORM_H


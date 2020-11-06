//
// IMIStringHelper.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_JSONTOOL_H
#define IMI_JSONTOOL_H

#include "IMIObject.h"

namespace imi {
    
    //数据基准类型
    class IMIStringHelper : public IMIObject{
    public:
        IMIStringHelper();
        
        ~IMIStringHelper();
        
        static IMIString jsonFormat(const IMIString inString);
        
        static void encrypt(c8 *_str, s32 *_keys, u32 _keyCount);
        
        static void decrypt(c8 *_str, s32 *_keys, u32 _keyCount);
    };
        
}//!namespace imi

#endif //IMI_JSONTOOL_H

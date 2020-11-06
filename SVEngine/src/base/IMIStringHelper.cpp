//
// IMIStringHelper.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIStringHelper.h"

using namespace imi;

IMIStringHelper::IMIStringHelper() {
}

IMIStringHelper::~IMIStringHelper(){
    
}

void IMIStringHelper::encrypt(c8 *_str, s32 *_keys, u32 _keyCount){
    u32 len= (u32)strlen(_str);//获取长度
    for(u32 i=0;i<len;i++){
        s32 key = _keys[i%_keyCount]%9;
        *(_str+i) = *(_str+i) ^ key;
    }
}

void IMIStringHelper::decrypt(c8 *_str, s32 *_keys, u32 _keyCount){
    u32 len= (u32)strlen(_str);//获取长度
    for(u32 i=0;i<len;i++){
        s32 key = _keys[i%_keyCount]%9;
        *(_str+i) = *(_str+i) ^ key;
    }
}

IMIString IMIStringHelper::jsonFormat(const IMIString inString){
    IMIString outString;
    outString.allocate(inString.size());
    s32 index = 0;
    s32 count = 0;
    while(index < inString.size()){
        char ch = inString.get(index);
        if(ch == '{' || ch == '['){
            outString.append(ch);
            outString.append('\n');
            count++;
            for (s32 i = 0; i < count; i++) {
                outString.append('\t');
            }
        }
        else if(ch == '}' || ch == ']'){
            outString.append('\n');
            count--;
            for (s32 i = 0; i < count; i++) {
                outString.append('\t');
            }
            outString.append(ch);
        }
        else if(ch == ','){
            outString.append(ch);
            outString.append('\n');
            for (s32 i = 0; i < count; i++) {
                outString.append('\t');
            }
        }
        else {
            outString.append(ch);
        }
        index ++;
    }
    return outString;
}

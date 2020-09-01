//
// SVObjectLua.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_LUA_BASE_H
#define SV_LUA_BASE_H

#include "SVDef.h"
#include "SVPreDeclare.h"
#include <vector>

namespace sv {

//注册静态类
class SVLuaBase {
public:
    SVLuaBase() {
        m_ref++;
    }
protected:
    static s32 m_ref;
    
public:
    static std::vector<lua_regist> gLuaRegistPool;
};

//注册声明
#define LUA_REG_DECLARE(classname,func) \
class classname##_lua: public SVLuaBase {\
    public:\
        classname##_lua(func) {\
            gLuaRegistPool.push_back(func);\
        }\
    };\

//注册实现
#define LUA_REG_IMP(classname)\
static classname##_lua m_##classname##_lua;\



}//!namespace sv



#endif //SV_LUA_BASE_H

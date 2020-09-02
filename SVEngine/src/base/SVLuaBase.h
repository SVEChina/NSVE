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
#include "../third/lua-5.4.0/src/lua.hpp"

namespace sv {

//注册静态类
class SVLuaBase {
public:
    SVLuaBase(lua_regist func);
    
protected:
    static s32 m_ref;
    
public:
    static std::vector<lua_regist>* gLuaRegistPool;
};

//注册声明
#define LUA_REG_DECLARE(classname) \
class classname##_lua: public SVLuaBase {\
    public:\
        classname##_lua(lua_regist func):SVLuaBase(func) {}\
    };\

//注册实现
#define LUA_REG_IMP(classname,func)\
static classname##_lua g_##classname##_lua(func);\



}//!namespace sv



#endif //SV_LUA_BASE_H

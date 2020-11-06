//
// IMIObjectLua.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_LUA_BASE_H
#define IMI_LUA_BASE_H

#include "IMIDef.h"
#include "IMIPreDeclare.h"
#include <vector>
#include "../third/lua-5.4.0/src/lua.hpp"

namespace imi {

//注册静态类
class IMILuaBase {
public:
    IMILuaBase(lua_regist func);
    
protected:
    static s32 m_ref;
    
public:
    static std::vector<lua_regist>* gLuaRegistPool;
};

//注册声明
#define LUA_REG_DECLARE(classname) \
class classname##_lua: public IMILuaBase {\
    public:\
        classname##_lua(lua_regist func):IMILuaBase(func) {}\
    };\

//注册实现
#define LUA_REG_IMP(classname,func)\
static classname##_lua g_##classname##_lua(func);\



}//!namespace imi



#endif //IMI_LUA_BASE_H

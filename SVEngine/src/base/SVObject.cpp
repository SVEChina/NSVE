#include "SVObject.h"

using namespace sv;

static void lua_regist_SVObject(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
       //lua_pushcfunction(L, &SVObject::SVObject);
//       lua_pushglobal(L, "SVObject");
//       // 创建userdata要用的元表(其名为Foo), 起码要定义__gc方法, 以便回收内存
//       luaL_newmetatable(L, "SVObject");
//       lua_pushstring(L, "__gc");
//       //lua_pushcfunction(L, &SVObject::gc_obj);
//       lua_settable(L, -3);
    }
}

LUA_REG_IMP(SVObject,lua_regist_SVObject);

//
SVObject::SVObject(){}

SVObject::~SVObject(){}



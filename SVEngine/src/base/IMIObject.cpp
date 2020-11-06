#include "IMIObject.h"

using namespace imi;

static void lua_regist_IMIObject(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
       //lua_pushcfunction(L, &IMIObject::IMIObject);
//       lua_pushglobal(L, "IMIObject");
//       // 创建userdata要用的元表(其名为Foo), 起码要定义__gc方法, 以便回收内存
//       luaL_newmetatable(L, "IMIObject");
//       lua_pushstring(L, "__gc");
//       //lua_pushcfunction(L, &IMIObject::gc_obj);
//       lua_settable(L, -3);
    }
}

LUA_REG_IMP(IMIObject,lua_regist_IMIObject);

//
IMIObject::IMIObject(){}

IMIObject::~IMIObject(){}



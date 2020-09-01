#include "SVObject.h"

using namespace sv;

//LUA_REG_IMP(SVObject,SVObject::lua_regist_SVObject);
static SVObject_lua g_SVObject_lua(SVObject::lua_regist_SVObject);

SVObject::SVObject(){}

SVObject::~SVObject(){}

void SVObject::lua_regist_SVObject(void* ls) {
    int a = 0;
}

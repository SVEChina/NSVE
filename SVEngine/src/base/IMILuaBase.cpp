#include "IMILuaBase.h"

using namespace imi;

//
s32 IMILuaBase::m_ref = 0;

std::vector<lua_regist>* IMILuaBase::gLuaRegistPool = nullptr;

IMILuaBase::IMILuaBase(lua_regist func) {
    if(!gLuaRegistPool) {
        gLuaRegistPool = new std::vector<lua_regist>();
        gLuaRegistPool->clear();
    }
    //
    if(func) {
      gLuaRegistPool->push_back(func);
    }
    m_ref++;
}


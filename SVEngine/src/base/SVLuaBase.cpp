#include "SVLuaBase.h"

using namespace sv;

//
s32 SVLuaBase::m_ref = 0;

std::vector<lua_regist>* SVLuaBase::gLuaRegistPool = nullptr;

SVLuaBase::SVLuaBase(lua_regist func) {
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


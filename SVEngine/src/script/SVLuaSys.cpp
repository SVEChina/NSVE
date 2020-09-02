//
//  SVLuaSys.cpp
//  SVEngine
//
//  Created by 付一洲 on 2019/2/28.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#include "SVLuaSys.h"
#include "../file/SVFileMgr.h"
#include "../base/SVLuaBase.h"

using namespace sv;

SVLuaSys::SVLuaSys(SVInstPtr _app)
:SVSysBase(_app) {
    L_S = nullptr;
    m_subsysType = 1;
}

SVLuaSys::~SVLuaSys() {
}

void SVLuaSys::init() {
    //创建state
    L_S = luaL_newstate();
    //打开库
    luaL_openlibs(L_S);
    //加载默认的主脚本
    //SVString t_main_lua = mApp->m_file_sys->;
//    //加载lua文件
//    s32 bRet = luaL_loadfile(L_S, "main.lua");
//    if (bRet){
//        //cout << "load test.lua file failed" << endl;
//        return;
//    }
    //调用注册函数
    for(s32 i=0;i<SVLuaBase::gLuaRegistPool->size();i++) {
        (*SVLuaBase::gLuaRegistPool)[i]((void*)L_S);
    }
}

void SVLuaSys::destroy() {
    lua_close(L_S); //关闭
}

void SVLuaSys::update(f32 dt) {
    //执行lua文件
//    s32 t_ret = lua_pcall(L_S, 0, 0, 0);
//    if (t_ret){
//        //cout << "call test.lua file failed" << endl;
//    }
}

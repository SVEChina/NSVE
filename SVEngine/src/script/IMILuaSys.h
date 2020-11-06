//
//  IMIPythonMgr.hpp
//  IMIngine
//
//  Created by 付一洲 on 2019/2/28.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_LUASYS_H
#define IMI_LUASYS_H

#include "../basesys/IMISysBase.h"
#include "../third/lua-5.4.0/src/lua.hpp"

namespace imi{
    
    class IMILuaSys : public IMISysBase {
    public:
        IMILuaSys(IMIInstPtr _app);
        
        ~IMILuaSys();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        //运行目标脚本
        void runLua(cptr8 _script);
        
    protected:
        lua_State* L_S;
    };

}//!namespace imi

#endif /* IMI_LUASYS_H */

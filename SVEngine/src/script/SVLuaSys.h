//
//  SVPythonMgr.hpp
//  SVEngine
//
//  Created by 付一洲 on 2019/2/28.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef SV_LUASYS_H
#define SV_LUASYS_H

#include "../basesys/SVSysBase.h"
#include "../base/SVLuaBase.h"
#include "../third/lua-5.4.0/src/lua.hpp"

namespace sv{
    
    class SVLuaSys : public SVSysBase {
    public:
        SVLuaSys(SVInstPtr _app);
        
        ~SVLuaSys();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
    protected:
        lua_State* L_S;
    };

}//!namespace sv

#endif /* SV_LUASYS_H */

//
// IMIMtlLib.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTLLIB_H
#define IMI_MTLLIB_H

#include "../event/IMIEventProc.h"
#include "IMIMtlDef.h"
#include "IMIMtlDeclare.h"
#include "../base/IMIObject.h"

#include <map>
#include <vector>
#include <string>

namespace imi {
    
    /*材质包内的材质不可更改*/
    //同步材质是同步参数，还是同步对象？

    class IMIMtlPack : public IMIGBaseEx {
    public:
        IMIMtlPack(IMIInstPtr _app);
        
        virtual ~IMIMtlPack();
        
        bool hasMtl(cptr8 _name);
        
        //材质包名
        IMIString m_pack_name;
        //材质对象
        typedef std::vector<IMIMtlCorePtr> MTLVEC;
        MTLVEC m_mtl_vec;
    };
    
    /*引擎提供的默认材质库*/
    class IMIMtlLib : public IMIEventProc {
    public:
        IMIMtlLib(IMIInstPtr _app);
        
        ~IMIMtlLib();
        
        void init();
        
        void destroy();
        
        //加载默认材质包
        void loadDefaultPack();
        
        //加载材质包
        void loadMtlPack(cptr8 _pack);

        //获取材质包
        IMIMtlPackPtr getPack(cptr8 _name);
        
        //清理材质
        void clear();
        
        //获取材质
        IMIMtlCorePtr getMtl(cptr8 _mtlname);
        
        //创建材质
        IMIMtlCorePtr createMtlFromFile(cptr8 _fname);
        
        //
        IMIMtlCorePtr createMtlFromJson(RAPIDJSON_NAMESPACE::Value& _obj,cptr8 _mtlname);
        
        //处理消息
        static void procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event);
        
    protected:
        
        //材质库(静态，模版)
        typedef std::map<IMIString,IMIMtlCorePtr> MTLPOOL;
        MTLPOOL m_mtlPool;
        
        //材质包
        typedef std::vector<IMIMtlPackPtr> PACKPOOL;
        PACKPOOL m_pack_pool;
    };

}//!namespace imi


#endif //IMI_MTLLIB_H

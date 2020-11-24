//
// SVMtlLib.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLLIB_H
#define SV_MTLLIB_H

#include "../event/SVEventProc.h"
#include "SVMtlDef.h"
#include "SVMtlDeclare.h"
#include "../base/SVObject.h"

#include <map>
#include <vector>
#include <string>

namespace sv {
    
    /*材质包内的材质不可更改*/
    //同步材质是同步参数，还是同步对象？

    class SVMtlPack : public SVGBaseEx {
    public:
        SVMtlPack(SVInstPtr _app);
        
        virtual ~SVMtlPack();
        
        bool hasMtl(cptr8 _name);
        
        //材质包名
        SVString m_pack_name;
        //材质对象
        typedef std::vector<SVMtlCorePtr> MTLVEC;
        MTLVEC m_mtl_vec;
    };
    
    /*引擎提供的默认材质库*/
    class SVMtlLib : public SVEventProc {
    public:
        SVMtlLib(SVInstPtr _app);
        
        ~SVMtlLib();
        
        void init();
        
        void destroy();
        
        //加载默认材质包
        void loadDefaultPack();
        
        //加载材质包
        void loadMtlPack(cptr8 _pack);

        //获取材质包
        SVMtlPackPtr getPack(cptr8 _name);
        
        //清理材质
        void clear();
        
        //获取材质
        SVMtlCorePtr getMtl(cptr8 _mtlname);
        
        //创建材质
        SVMtlCorePtr createMtlFromFile(cptr8 _fname);
        
        //从JSON创建材质
        SVMtlCorePtr createMtlFromJson(RAPIDJSON_NAMESPACE::Value& _obj,cptr8 _mtlname);
        
        //处理消息
        static void procSysEvent(SVObjectPtr _caller,SVEventPtr _event);
        
    protected:
        
        //材质库(静态，模版)
        typedef std::map<SVString,SVMtlCorePtr> MTLPOOL;
        MTLPOOL m_mtlPool;
        
        //材质包
        typedef std::vector<SVMtlPackPtr> PACKPOOL;
        PACKPOOL m_pack_pool;
    };

}//!namespace sv


#endif //SV_MTLLIB_H

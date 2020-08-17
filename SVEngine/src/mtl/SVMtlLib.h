//
// SVMtlLib.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLLIB_H
#define SV_MTLLIB_H

#include "../base/SVGBase.h"
#include "SVMtlDef.h"
#include "SVMtlDeclare.h"
#include "../base/SVObject.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/document.h"

#include <map>
#include <vector>
#include <string>

namespace sv {
    
    /*材质包*/

    class SVMtlPack : public SVGBaseEx {
    public:
        SVMtlPack(SVInstPtr _app):SVGBaseEx(_app) {
        }
    
        ~SVMtlPack() {
            
        }
        
        bool hasMtl(cptr8 _mtlname) {
            return false;
        }
        
    protected:
        SVString m_pack_name;    //材质包名
        //
        typedef std::vector<SVMtlCorePtr> MTLVEC;
        MTLVEC m_mtl_vec;
    };

    
    /*引擎提供的默认材质库*/
    class SVMtlLib : public SVGBaseEx {
    public:
        SVMtlLib(SVInstPtr _app);
        
        ~SVMtlLib();
        
        void init();
        
        void destroy();
        
        void loadMtlPack(cptr8 _pack);
        
        void clear();
        
        SVMtlCorePtr getMtl(s32 _mtlID);
        
        SVMtlCorePtr getMtl(cptr8 _mtlname);
        
        SVMtlCorePtr createMtl(cptr8 _mtlname);
        
    protected:
        
        static bool parseMtl1(SVMtlCorePtr _mtl,RAPIDJSON_NAMESPACE::Document& _doc);
        
        //材质库(静态，模版)
        typedef std::map<SVString,SVMtlCorePtr> MTLPOOL;
        MTLPOOL m_mtlPool;
        
        //材质包
        typedef std::vector<SVMtlPackPtr> PACKPOOL;
        PACKPOOL m_pack_pool;
        
        //运行时的材质库
        typedef std::vector<SVMtlCorePtr> MTLPOOLRUN;
        MTLPOOLRUN m_mtlpool_run;
        
        //空闲的材质
        typedef std::vector<s32> EMPTYMTLPOOL;
        EMPTYMTLPOOL m_empty_mtl_ool;
    };

}//!namespace sv


#endif //SV_MTLLIB_H

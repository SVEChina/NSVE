//
// SVShaderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MTLLIB_H
#define SV_MTLLIB_H

#include "SVMtlDef.h"
#include "SVMtlDeclare.h"
#include "../base/SVObject.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/document.h"

namespace sv {
    
    /*引擎提供的默认材质库*/
    
    class SVMtlLib : public SVObject {
    public:
        static void clear();
        
        static SVMtlCorePtr getSkinMtl(SVInstPtr _app);
        
        static SVMtlCorePtr get3DNorMtl(SVInstPtr _app);
        
        static SVMtlCorePtr genMtl(SVInstPtr _app,cptr8 _name);
        
        static SVMtlCorePtr createMtl(SVInstPtr _app,cptr8 _mtlname);
        
    protected:
        static SVMtlCorePtr m_pSkinMtl;
        
        static SVString mapName(cptr8 _name);
        
        static bool parseMtl1(SVMtlCorePtr _mtl,RAPIDJSON_NAMESPACE::Document& _doc);
    };
    
}//!namespace sv


#endif //SV_MTLLIB_H

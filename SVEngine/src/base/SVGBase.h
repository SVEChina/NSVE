//
// Created by yizhou Fu on 2017/4/29.
//

#ifndef SV_GBASE_H
#define SV_GBASE_H

//管理基类

#include "SVObject.h"
#include "SVPreDeclare.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"

namespace sv {
    
    class SVGBaseEx: public SVObject {
    public:
        SVGBaseEx(SVInstPtr _app);
    
        ~SVGBaseEx();
        
        inline u32 getUID(){ return m_uid; }
        
    protected:
        SVInstPtr mApp;
        u32 m_uid;          //唯一对象id
    };
    
}//!namespace sv


#endif //SV_GBASE_H

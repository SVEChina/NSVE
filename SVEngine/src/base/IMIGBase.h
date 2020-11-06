//
// Created by yizhou Fu on 2017/4/29.
//

#ifndef IMI_GBASE_H
#define IMI_GBASE_H

//管理基类

#include "IMIObject.h"
#include "IMIPreDeclare.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/document.h"
#include "../third/rapidjson/stringbuffer.h"
#include "../third/rapidjson/writer.h"

namespace imi {
    
    class IMIGBaseEx: public IMIObject {
    public:
        IMIGBaseEx(IMIInstPtr _app);
    
        ~IMIGBaseEx();
        
        inline u32 getUID(){ return m_uid; }
        
    protected:
        IMIInstPtr mApp;
        u32 m_uid;          //唯一对象id
    };
    
}//!namespace imi


#endif //IMI_GBASE_H

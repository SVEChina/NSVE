//
// SVJson.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_JSON_H
#define SV_JSON_H

#include "SVFileLoader.h"
#include "../base/SVArray.h"
#include "../base/SVTable.h"
#include "../third/rapidjson/rapidjson.h"
#include "../third/rapidjson/writer.h"

#define SVJsonBuf RAPIDJSON_NAMESPACE::StringBuffer
#define SVJsonWrite rapidjson::Writer<SVJsonBuf>

namespace sv {

    //对rapidjson的再次封装使用
    class SVJson : public SVObject {
    public:
        SVJson();
        
//        rapidjson::StringBuffer strBuf;
//        rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
        
    };
    
}//!namespace sv



#endif //SV_BATLOADER_H

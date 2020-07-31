//
// SVParamTbl.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PAEAMTBL_H
#define SV_PAEAMTBL_H

#include "../basesys/SVSysBase.h"
#include "SVVec2.h"
#include "SVVec3.h"
#include "SVVec4.h"
#include "SVMat2.h"
#include "SVMat3.h"
#include "SVMat4.h"

#include <vector>
#include <string>

//参数表

namespace sv {
    
    //参数描述
    struct SVParamDsp {
        std::string m_name; //参数名称
        s32 m_type;         //参数类型
        s32 m_size;         //参数数据一共的大小
        u64 m_off;          //参数在表中数据偏移
    };

    class SVParamTbl :public SVObject {
    public:
        SVParamTbl();

        virtual ~SVParamTbl();
        
        bool hasParam(cptr8 _name);

        //设置参数值 主要是针对uniform
        void setParam(cptr8 _name,s32 _value);

        void setParam(cptr8 _name,f32 _value);

        void setParam(cptr8 _name,FVec2 _value);

        void setParam(cptr8 _name,FVec3 _value);

        void setParam(cptr8 _name,FVec4 _value);

        void setParam(cptr8 _name,FMat4 _value);
        
        //增加参数
        void addParam(cptr8 _name,cptr8 _type,cptr8 _value);

        s32 getParam(cptr8 _name);
        
        void* getParamData(cptr8 _name);
           
        void fromJSON(RAPIDJSON_NAMESPACE::Value &_item);

        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,RAPIDJSON_NAMESPACE::Value &_objValue);

    public:
        //参数表
        std::vector<SVParamDsp> m_param_dsps;    //参数表
        SVDataChunkPtr m_param_values;           //参数值

    };
    
}//!namespace sv



#endif //SV_PAEAMTBL_H

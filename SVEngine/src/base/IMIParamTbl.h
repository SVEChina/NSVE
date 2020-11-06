//
// IMIParamTbl.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PAEAMTBL_H
#define IMI_PAEAMTBL_H

#include "../basesys/IMISysBase.h"
#include "IMIVec2.h"
#include "IMIVec3.h"
#include "IMIVec4.h"
#include "IMIMat2.h"
#include "IMIMat3.h"
#include "IMIMat4.h"

#include <vector>
#include <string>

//参数表

namespace imi {
    
    //参数描述
    struct IMIParamDsp {
        s32 m_type;         //参数类型
        s32 m_size;         //参数数据一共的大小
        s32 m_cnt;
        u64 m_off;          //参数在表中数据偏移
    };

    class IMIParamTbl :public IMIObject {
    public:
        IMIParamTbl();

        virtual ~IMIParamTbl();
        
        void clear();
        
        bool hasParam(cptr8 _name);
        
        //增加参数
        bool addParam(cptr8 _name,cptr8 _type,cptr8 _value);
        
        //删除一个参数
        bool delParam(cptr8 _name);
        
        //增加 主要是针对uniform
        bool addParam(cptr8 _name,s32& _value);

        bool addParam(cptr8 _name,f32& _value);

        bool addParam(cptr8 _name,FVec2& _value);

        bool addParam(cptr8 _name,FVec3& _value);

        bool addParam(cptr8 _name,FVec4& _value);
        
        bool addParam(cptr8 _name,FMat2& _value);

        bool addParam(cptr8 _name,FMat3& _value);

        bool addParam(cptr8 _name,FMat4& _value);
        //
        bool addParam(cptr8 _name,s32* _value);

        //设置参数值 主要是针对uniform
        bool setParam(cptr8 _name,s32& _value);

        bool setParam(cptr8 _name,f32& _value);

        bool setParam(cptr8 _name,FVec2& _value);

        bool setParam(cptr8 _name,FVec3& _value);

        bool setParam(cptr8 _name,FVec4& _value);
        
        bool setParam(cptr8 _name,FMat2& _value);

        bool setParam(cptr8 _name,FMat3& _value);

        bool setParam(cptr8 _name,FMat4& _value);
        
        void getParam(cptr8 _name,s32& _value);

        void getParam(cptr8 _name,f32& _value);

        void getParam(cptr8 _name,FVec2& _value);

        void getParam(cptr8 _name,FVec3& _value);

        void getParam(cptr8 _name,FVec4& _value);
        
        void getParam(cptr8 _name,FMat2& _value);

        void getParam(cptr8 _name,FMat3& _value);

        void getParam(cptr8 _name,FMat4& _value);
        
        /*
         array
         */
        bool addParamArray(cptr8 _name,s32* _value,s32 _cnt);
        
        bool addParamArray(cptr8 _name,f32* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FVec2* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FVec3* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FVec4* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FMat2* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FMat3* _value,s32 _cnt);

        bool addParamArray(cptr8 _name,FMat4* _value,s32 _cnt);
        
        bool setParamArray(cptr8 _name,s32* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,f32* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,FVec2* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,FVec3* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,FVec4* _value,s32 _cnt);
        
        bool setParamArray(cptr8 _name,FMat2* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,FMat3* _value,s32 _cnt);

        bool setParamArray(cptr8 _name,FMat4* _value,s32 _cnt);
        
        void getParamArray(cptr8 _name,s32* _value,s32 _cnt);

        void getParamArray(cptr8 _name,f32* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FVec2* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FVec3* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FVec4* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FMat2* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FMat3* _value,s32 _cnt);

        void getParamArray(cptr8 _name,FMat4* _value,s32 _cnt);
        
        void* getParamData(cptr8 _name);
        
        void* getDataPointer();
        
        s32 getDataSize();
           
        void fromJSON(RAPIDJSON_NAMESPACE::Value &_item);

        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,RAPIDJSON_NAMESPACE::Value &_objValue);

    public:
        //参数名称
        std::vector<IMIString> m_param_names;
        //参数表
        std::vector<IMIParamDsp> m_param_dsps;
        //数据区域
        IMIDataChunkPtr m_param_values;
        
    protected:
        s32 _getParamIndex(cptr8 _name);
        u64 _getParamOff(cptr8 _name);
    };
    
}//!namespace imi



#endif //IMI_PAEAMTBL_H

//
// SVParamTbl.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVParamTbl.h"
#include "SVDataChunk.h"

using namespace sv;

//参数表

SVParamTbl::SVParamTbl(){
    m_param_values = MakeSharedPtr<SVDataChunk>();
}

SVParamTbl::~SVParamTbl() {
    m_param_dsps.clear();
    m_param_values = nullptr;
}

bool SVParamTbl::hasParam(cptr8 _name) {
    for(s32 i=0;i<m_param_dsps.size();i++) {
        if( strcmp( m_param_dsps[i].m_name.c_str() ,_name) == 0 ) {
            return true;
        }
    }
    return false;
}

void SVParamTbl::addParam(cptr8 _name,cptr8 _type,cptr8 _value)  {
    if( strcmp(_type,"s32") == 0) {
        s32 tmp = atoi(_value);
        if(strcmp(_value,"identify") == 0) {
            setParam(_name,1);
        }else{
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"f32") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            setParam(_name,1.0f);
        }else{
            f32 tmp = atof(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec2") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec2 tmp = FVec2_one;;
            setParam(_name,tmp);
        }else{
            FVec2 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec3") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec3 tmp = FVec3_one;
            setParam(_name,tmp);
        }else{
            FVec3 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec4 tmp = FVec4_one;
            setParam(_name,tmp);
        }else{
            FVec4 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat2") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat2 tmp;
            tmp.setIdentity();
            setParam(_name,tmp);
        }else{
            FMat2 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat3") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat3 tmp;
            tmp.setIdentity();
            setParam(_name,tmp);
        }else{
            FMat3 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat4 tmp;
            tmp.setIdentity();
            setParam(_name,tmp);
        }else{
            FMat4 tmp(_value);
            setParam(_name,tmp);
        }
    }
}

void SVParamTbl::setParam(cptr8 _name,s32 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_INT;
        t_param.m_size = sizeof(s32);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,f32 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FLOAT;
        t_param.m_size = sizeof(f32);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FVec2 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FVEC2;
        t_param.m_size = sizeof(FVec2);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FVec3 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FVEC3;
        t_param.m_size = sizeof(FVec3);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FVec4 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FVEC4;
        t_param.m_size = sizeof(FVec4);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FMat2 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FMAT2;
        t_param.m_size = sizeof(FMat2);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FMat3 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FMAT3;
        t_param.m_size = sizeof(FMat3);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

void SVParamTbl::setParam(cptr8 _name,FMat4 _value) {
    s32 t_index = getParam(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
    }else{
        //推送目标参数
        SVParamDsp t_param;
        t_param.m_name = _name;
        t_param.m_type = SV_FMAT4;
        t_param.m_size = sizeof(FMat4);
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
    }
}

s32 SVParamTbl::getParam(cptr8 _name) {
    for(s32 i=0;i<m_param_dsps.size();i++) {
        if( strcmp( m_param_dsps[i].m_name.c_str() ,_name) == 0 ) {
            return i;
        }
    }
    return -1;
}

void* SVParamTbl::getParamData(cptr8 _name) {
    u64 t_off = 0;
    for(s32 i=0;i<m_param_dsps.size();i++) {
        if( strcmp( m_param_dsps[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            t_off = m_param_dsps[i].m_off;
            break;
        }
    }
    return m_param_values->getPointer(t_off);
}

void* SVParamTbl::getDataPointer() {
    return m_param_values->getPointer();
}

s32 SVParamTbl::getDataSize() {
    return m_param_values->getRealSize();
}

void SVParamTbl::fromJSON(RAPIDJSON_NAMESPACE::Value &_item){
    if (_item.HasMember("param-tbl") && _item["param-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _item["param-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            SVString t_param_name = element["name"].GetString();
            SVString t_param_type = element["type"].GetString();
            SVString t_param_value = element["value"].GetString();
            addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
        }
    }
}

//
void SVParamTbl::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                       RAPIDJSON_NAMESPACE::Value &_objValue){
    
}

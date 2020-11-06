//
// IMIParamTbl.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParamTbl.h"
#include "IMIDataChunk.h"

using namespace imi;

//参数表

IMIParamTbl::IMIParamTbl(){
    m_param_names.clear();
    m_param_dsps.clear();
    m_param_values = MakeSharedPtr<IMIDataChunk>();
}

IMIParamTbl::~IMIParamTbl() {
    m_param_names.clear();
    m_param_dsps.clear();
    m_param_values = nullptr;
}

void IMIParamTbl::clear() {
    m_param_names.clear();
    m_param_dsps.clear();
    m_param_values = MakeSharedPtr<IMIDataChunk>();
}

bool IMIParamTbl::hasParam(cptr8 _name) {
    for(s32 i=0;i<m_param_names.size();i++) {
        if( m_param_names[i] == _name ) {
            return true;
        }
    }
    return false;
}

bool IMIParamTbl::addParam(cptr8 _name,cptr8 _type,cptr8 _value)  {
    if( strcmp(_type,"s32") == 0) {
        s32 tmp = atoi(_value);
        if(strcmp(_value,"identify") == 0) {
            s32 tmp = 1;
            return addParam(_name,tmp);
        }else{
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"f32") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            f32 tmp = 1.0f;
            return addParam(_name,tmp);
        }else{
            f32 tmp = atof(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec2") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec2 tmp = FVec2_one;;
            return addParam(_name,tmp);
        }else{
            FVec2 tmp(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec3") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec3 tmp = FVec3_one;
            return addParam(_name,tmp);
        }else{
            FVec3 tmp(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec4 tmp = FVec4_one;
            return addParam(_name,tmp);
        }else{
            FVec4 tmp(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat2") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat2 tmp;
            tmp.setIdentity();
            return addParam(_name,tmp);
        }else{
            FMat2 tmp(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat3") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat3 tmp;
            tmp.setIdentity();
            return addParam(_name,tmp);
        }else{
            FMat3 tmp(_value);
            return addParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat4 tmp;
            tmp.setIdentity();
            return addParam(_name,tmp);
        }else{
            FMat4 tmp(_value);
            return addParam(_name,tmp);
        }
    }
    return false;
}

bool IMIParamTbl::delParam(cptr8 _name) {
    bool ret = hasParam(_name);
    if(ret) {
//        s32 t_index = _getParamIndex(_name);
//        std::vector<IMIString>::iterator it_name = m_param_names.begin() + t_index;
//        std::vector<IMIParamDsp>::iterator it_dsp = m_param_dsps.begin() + t_index;
//        //删除名字
//        m_param_names.erase(it_name);
//        //删除数值
//        m_param_values->remove((*it_dsp).m_off,(*it_dsp).m_size);
//        //参数修正
//        //删除DSP
//        m_param_dsps.erase(it_dsp);
//        //
//        if( it_dsp!=m_param_dsps.end() ) {
//            it_dsp++;
//        }
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,s32& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_INT;
        t_param.m_size = sizeof(s32);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,f32& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FLOAT;
        t_param.m_size = sizeof(f32);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FVec2& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC2;
        t_param.m_size = sizeof(FVec2);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FVec3& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC3;
        t_param.m_size = sizeof(FVec3);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FVec4& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC4;
        t_param.m_size = sizeof(FVec4);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FMat2& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT2;
        t_param.m_size = sizeof(FMat2);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FMat3& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT3;
        t_param.m_size = sizeof(FMat3);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParam(cptr8 _name,FMat4& _value){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT4;
        t_param.m_size = sizeof(FMat4);
        t_param.m_cnt = 1;
        t_param.m_off = m_param_values->push(_value);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::setParam(cptr8 _name,s32& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,f32& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FVec2& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FVec3& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FVec4& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FMat2& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FMat3& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

bool IMIParamTbl::setParam(cptr8 _name,FMat4& _value) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value);
        return true;
    }
    return addParam(_name, _value);
}

void IMIParamTbl::getParam(cptr8 _name,s32& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,f32& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FVec2& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FVec3& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FVec4& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FMat2& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FMat3& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

void IMIParamTbl::getParam(cptr8 _name,FMat4& _value) {
    u64 t_off = _getParamOff(_name);
    m_param_values->get(t_off, _value);
}

/*
 param array
 */

bool IMIParamTbl::addParamArray(cptr8 _name,s32* _value,s32 _cnt) {
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_INT;
        t_param.m_size = sizeof(s32)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParamArray(cptr8 _name,f32* _value,s32 _cnt) {
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FLOAT;
        t_param.m_size = sizeof(f32)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::addParamArray(cptr8 _name,FVec2* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        ret = true;
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC2;
        t_param.m_size = sizeof(FVec2)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}


bool IMIParamTbl::addParamArray(cptr8 _name,FVec3* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC3;
        t_param.m_size = sizeof(FVec3)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}


bool IMIParamTbl::addParamArray(cptr8 _name,FVec4* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        IMIParamDsp t_param;
        t_param.m_type = IMI_FVEC4;
        t_param.m_size = sizeof(FVec4)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}


bool IMIParamTbl::addParamArray(cptr8 _name,FMat2* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT2;
        t_param.m_size = sizeof(FMat2)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}


bool IMIParamTbl::addParamArray(cptr8 _name,FMat3* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT3;
        t_param.m_size = sizeof(FMat3)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}


bool IMIParamTbl::IMIParamTbl::addParamArray(cptr8 _name,FMat4* _value,s32 _cnt){
    bool ret = hasParam(_name);
    if( !ret ) {
        IMIParamDsp t_param;
        t_param.m_type = IMI_FMAT4;
        t_param.m_size = sizeof(FMat4)*_cnt;
        t_param.m_cnt = _cnt;
        t_param.m_off = m_param_values->push(_value,t_param.m_size);
        m_param_dsps.push_back(t_param);
        m_param_names.push_back(_name);
    }
    return ret;
}

bool IMIParamTbl::setParamArray(cptr8 _name,s32* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(s32));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,f32* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(f32));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FVec2* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FVec2));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FVec3* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FVec3));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FVec4* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FVec4));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FMat2* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FMat2));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FMat3* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FMat3));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

bool IMIParamTbl::setParamArray(cptr8 _name,FMat4* _value,s32 _cnt) {
    s32 t_index = _getParamIndex(_name);
    if( t_index>=0 ) {
        m_param_values->set(m_param_dsps[t_index].m_off,_value,_cnt*sizeof(FMat4));
        return true;
    }
    return addParamArray(_name, _value,_cnt);
}

void IMIParamTbl::getParamArray(cptr8 _name,s32* _value,s32 _cnt) {
    
}

void IMIParamTbl::getParamArray(cptr8 _name,f32* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FVec2* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FVec3* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FVec4* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FMat2* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FMat3* _value,s32 _cnt){
    
}

void IMIParamTbl::getParamArray(cptr8 _name,FMat4* _value,s32 _cnt){
    
}

//
s32 IMIParamTbl::_getParamIndex(cptr8 _name) {
    for(s32 i=0;i<m_param_dsps.size();i++) {
        if( m_param_names[i] == _name ) {
            return i;
        }
    }
    return -1;
}

u64 IMIParamTbl::_getParamOff(cptr8 _name) {
    u64 t_off = 0;
    for(s32 i=0;i<m_param_names.size();i++) {
       if( m_param_names[i] == _name ) {
           t_off = m_param_dsps[i].m_off;   //找到目标参数 ，拷贝即可
           break;
       }
    }
    return t_off;
}

void* IMIParamTbl::getParamData(cptr8 _name) {
    u64 t_off = 0;
    for(s32 i=0;i<m_param_names.size();i++) {
        if( m_param_names[i] == _name ) {
            //找到目标参数 ，拷贝即可
            t_off = m_param_dsps[i].m_off;
            break;
        }
    }
    return m_param_values->getPointer(t_off);
}

void* IMIParamTbl::getDataPointer() {
    return m_param_values->getPointer();
}

s32 IMIParamTbl::getDataSize() {
    return s32(m_param_values->getRealSize());
}

void IMIParamTbl::fromJSON(RAPIDJSON_NAMESPACE::Value &_item){
    if (_item.HasMember("param-tbl") && _item["param-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _item["param-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            IMIString t_param_name = element["name"].GetString();
            IMIString t_param_type = element["type"].GetString();
            IMIString t_param_value = element["value"].GetString();
            addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
        }
    }
}

//
void IMIParamTbl::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                       RAPIDJSON_NAMESPACE::Value &_objValue){
    
}

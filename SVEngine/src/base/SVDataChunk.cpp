//
// SVDataChunk.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDataChunk.h"

using namespace sv;

//数据块
SVDataChunk::SVDataChunk()
:m_size(0)
,m_realsize(0)
,m_data(nullptr) {
}

SVDataChunk::~SVDataChunk() {
    if (m_size > 0) {
        free(m_data);
        m_size = 0;
        m_realsize = 0;
        m_data = nullptr;
    }
}

//
bool SVDataChunk::set(u64 _off,s32 _value) {
    return set(_off,&_value,sizeof(s32));
}

bool SVDataChunk::set(u64 _off,f32 _value) {
    return set(_off,&_value,sizeof(f32));
}

bool SVDataChunk::set(u64 _off,FVec2& _value){
    return set(_off,&_value,sizeof(FVec2));
}

bool SVDataChunk::set(u64 _off,FVec3& _value){
    return set(_off,&_value,sizeof(FVec3));
}

bool SVDataChunk::set(u64 _off,FVec4& _value){
    return set(_off,&_value,sizeof(FVec4));
}

bool SVDataChunk::set(u64 _off,FMat2& _value){
    return set(_off,_value.mat,sizeof(FMat2));
}

bool SVDataChunk::set(u64 _off,FMat3& _value){
    return set(_off,_value.mat,sizeof(FMat3));
}

bool SVDataChunk::set(u64 _off,FMat4& _value){
    return set(_off,_value.mat,sizeof(FMat4));
}

bool SVDataChunk::set(u64 _off,void* _value,s32 _size) {
    if(_off+_size > m_realsize) {
        return false;
    }
    memcpy(m_data + _off, _value, _size);
    return true;
}

void SVDataChunk::get(u64 _off,s32& _value) {
    if(_off + sizeof(s32) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(s32));
        return;
    }
    _value = 0;
}

void SVDataChunk::get(u64 _off,f32& _value) {
    if(_off + sizeof(f32) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(f32));
        return;
    }
    _value = 0.0f;
}

void SVDataChunk::get(u64 _off,FVec2& _value) {
    if(_off + sizeof(FVec2) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FVec2));
        return;
    }
    _value.set(1.0f);
}

void SVDataChunk::get(u64 _off,FVec3& _value) {
    if(_off + sizeof(FVec3) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FVec3));
        return;
    }
    _value.set(1.0f);
}

void SVDataChunk::get(u64 _off,FVec4& _value) {
    if(_off + sizeof(FVec4) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FVec4));
        return;
    }
    _value.set(1.0f);
}

void SVDataChunk::get(u64 _off,FMat2& _value) {
    if(_off + sizeof(FMat2) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FMat2));
        return;
    }
    _value.setIdentity();
}

void SVDataChunk::get(u64 _off,FMat3& _value) {
    if(_off + sizeof(FMat3) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FMat3));
        return;
    }
    _value.setIdentity();
}

void SVDataChunk::get(u64 _off,FMat4& _value) {
    if(_off + sizeof(FMat4) <= m_realsize ) {
        memcpy(&_value,m_data + _off,sizeof(FMat4));
        return;
    }
    _value.setIdentity();
}

bool SVDataChunk::get(u64 _off,void* _value,s32 _size) {
     if(_off + _size <= m_realsize ) {
         memcpy(_value, m_data + _off, _size);
         return true;
     }
     return false;
}

//
u64 SVDataChunk::push(s32 _value) {
    return push(&_value,sizeof(s32));
}

u64 SVDataChunk::push(f32 _value) {
    return push(&_value,sizeof(f32));
}

u64 SVDataChunk::push(FVec2& _value) {
    return push(&_value,sizeof(FVec2));
}

u64 SVDataChunk::push(FVec3& _value) {
    return push(&_value,sizeof(FVec3));
}

u64 SVDataChunk::push(FVec4& _value) {
    return push(&_value,sizeof(FVec4));
}

u64 SVDataChunk::push(FMat2& _value) {
    return push(_value.mat,sizeof(FMat2));
}

u64 SVDataChunk::push(FMat3& _value) {
    return push(_value.mat,sizeof(FMat3));
}

u64 SVDataChunk::push(FMat4& _value) {
    return push(_value.mat,sizeof(FMat4));
}

u64 SVDataChunk::push(void* _value,s32 _size) {
    //检测size
    u64 t_aimsize = m_realsize + _size;
    if(t_aimsize > m_size) {
        //重新分配内存,是不是要处理内存对其的问题
        u64 t_newsize = 0;//m_size*2;
        if(m_size == 0) {
            t_newsize = 4;
        }else{
            t_newsize = m_size<<1;
        }
        //每次都*2
        while (t_newsize<t_aimsize) {
            t_newsize = t_newsize<<1;
        }
        m_size = t_newsize;
        //新地址,并拷贝数据
        c8* t_newdata = (c8*)(malloc(t_newsize));
        if(m_data && m_realsize>0) {
            memcpy(t_newdata, m_data, m_realsize);
            free(m_data);
        }
        m_data = t_newdata;
    }
    //
    u64 t_off = m_realsize;
    void* t_pos = m_data + m_realsize;
    memcpy(t_pos, _value, _size);
    m_realsize += _size;
    return t_off;
}

void SVDataChunk::remove(u64 _off,s32 _len) {
     u64 t_end = _off+_len;
     if( t_end<=m_realsize ) {
          m_realsize -= _len;
          void* t_dst = (void*)(m_data + _off);
          void* t_src = (void*)(m_data + t_end);
          memmove(t_dst, t_src, _len);
     }
}

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
bool SVDataChunk::set(u64 _off,int _value) {
    return set(_off,&_value,sizeof(int));
}

bool SVDataChunk::set(u64 _off,float _value) {
    return set(_off,&_value,sizeof(float));
}

bool SVDataChunk::set(u64 _off,void* _value,int _size) {
    if(_off+_size > m_realsize) {
        return false;
    }
    memcpy(m_data + _off, _value, _size);
    return true;
}

//
u64 SVDataChunk::push(int _value) {
    return push(&_value,sizeof(int));
}

u64 SVDataChunk::push(float _value) {
    return push(&_value,sizeof(float));
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
        memcpy(t_newdata, m_data, m_realsize);
        free(m_data);
        m_data = t_newdata;
    }
    //
    u64 t_off = m_realsize;
    void* t_pos = m_data + m_realsize;
    memcpy(t_pos, &_value, _size);
    m_realsize += _size;
    return t_off;
}

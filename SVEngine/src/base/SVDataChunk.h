//
// SVDataChunk.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_DATACHUNK_H
#define SV_DATACHUNK_H

#include "../basesys/SVSysBase.h"
#include "SVVec2.h"
#include "SVVec3.h"
#include "SVVec4.h"
#include "SVMat2.h"
#include "SVMat3.h"
#include "SVMat4.h"

//文件路径管理器 增加搜索路径相关
namespace sv {
    
    class SVDataChunk :public SVObject {
    public:
        SVDataChunk();
        
        virtual ~SVDataChunk();
        
        //
        bool set(u64 _off,s32 _value);
        
        bool set(u64 _off,f32 _value);
        
        bool set(u64 _off,FVec2& _value);
        
        bool set(u64 _off,FVec3& _value);
        
        bool set(u64 _off,FVec4& _value);
        
        bool set(u64 _off,FMat2& _value);
        
        bool set(u64 _off,FMat3& _value);
        
        bool set(u64 _off,FMat4& _value);
        
        bool set(u64 _off,void* _value,s32 _size);
        
        u64 push(s32 _value);
        
        u64 push(f32 _value);
        
        u64 push(FVec2& _value);
        
        u64 push(FVec3& _value);
        
        u64 push(FVec4& _value);
        
        u64 push(FMat2& _value);
        
        u64 push(FMat3& _value);
        
        u64 push(FMat4& _value);
        
        u64 push(void* _value,s32 _size);
        
        //
        
        void* getPointer() { return m_data; }
        
        void* getPointer(u64 _off) { return (void*)(m_data + _off); }
        
        c8* getPointerChar(){ return (char*)m_data; }
        
        c8* getPointerChar(u64 _off){ return m_data + _off; }
        
        u64 getSize() { return m_size; }
        
        u64 getRealSize() { return m_realsize; }
        
    protected:

        u64 m_size;
        
        u64 m_realsize;
        
        c8 *m_data;
    };
    
}//!namespace sv



#endif //SV_DATACHUNK_H

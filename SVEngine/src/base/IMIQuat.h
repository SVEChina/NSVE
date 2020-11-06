#ifndef __IMI_QUAT_H__
#define __IMI_QUAT_H__

#include "IMIVec4.h"
#include "IMIMat4.h"

namespace imi {

    /******************************************************************************\
     *
     * IMIQuat
     *
     \******************************************************************************/
    
    //
    IMI_ALIGNED16(struct) IMIQuat {
        
        sv_inline IMIQuat() {
        }
        
        IMIQuat(const FVec3 &axis,f32 angle);
        
        IMIQuat(f32 x,f32 y,f32 z,f32 angle);
        
        IMIQuat(f32 angle_x,f32 angle_y,f32 angle_z);
        
        explicit sv_inline IMIQuat(const f32 *q)
        : x(q[0])
        , y(q[1])
        , z(q[2])
        , w(q[3]) {
        }
        
        explicit sv_inline IMIQuat(const FVec3 &v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(0.0f) {
        }
        
        explicit sv_inline IMIQuat(const FVec4 &v)
        : x(v.x)
        , y(v.y)
        , z(v.z)
        , w(v.w) {
        }
        
        explicit IMIQuat(const FMat3 &m);
        explicit IMIQuat(const FMat4 &m);
        explicit IMIQuat(const DMat4 &m);
#ifdef USE_SSE
        sv_inline IMIQuat(const IMIQuat &q)
        : vec(q.vec) {
        }
        
        explicit sv_inline IMIQuat(__m128 vec)
        : vec(vec) {
        }
#elif USE_ALTIVEC
        sv_inline IMIQuat(const IMIQuat &q)
        : vec(q.vec) {
        }
        explicit sv_inline IMIQuat(vec_float4 vec)
        : vec(vec) {
        }
#elif USE_NEON
        sv_inline IMIQuat(const IMIQuat &q)
        : vec(q.vec) {
        }
        explicit sv_inline IMIQuat(float32x4_t vec)
        : vec(vec) {
        }
#else
        sv_inline IMIQuat(const IMIQuat &q)
        : x(q.x)
        , y(q.y)
        , z(q.z)
        , w(q.w) {
        }
#endif
        
        sv_inline IMIQuat &operator=(const IMIQuat &q) {
#if defined(USE_SSE) || defined(USE_ALTIVEC) || defined(USE_NEON)
            vec = q.vec;
#else
            x = q.x; y = q.y; z = q.z; w = q.w;
#endif
            return *this;
        }
        
        IMIQuat operator-() const;
        
        IMIQuat &operator*=(f32 v);
        
        IMIQuat &operator*=(const IMIQuat &q);
        
        IMIQuat &operator+=(const IMIQuat &q);
        
        IMIQuat &operator-=(const IMIQuat &q);
        
        sv_inline operator f32*() { return q; }
        
        sv_inline operator const f32*() const { return q; }
        
        sv_inline operator void*() { return q; }
        
        sv_inline operator const void*() const { return q; }
        
        sv_inline f32 &operator[](s32 i) {
            assert((u32)i < 4 && "IMIQuat::operator[](): bad index");
            return q[i];
        }
        sv_inline f32 operator[](s32 i) const {
            assert((u32)i < 4 && "IMIQuat::operator[](): bad index");
            return q[i];
        }
        
        void set(const FVec3 &v);
        void set(const FMat3 &m);
        void set(const FMat4 &m);
        void set(const DMat4 &m);
        void set(const FVec3 &axis,f32 angle);
        void set(f32 x,f32 y,f32 z,f32 angle);
        void set(f32 angle_x,f32 angle_y,f32 angle_z);
        void get(FVec3 &axis,f32 &angle) const;
        
        sv_inline void set(const f32 *q) {
            x = q[0];
            y = q[1];
            z = q[2];
            w = q[3];
        }
        
        sv_inline void get(f32 *q) const {
            q[0] = x;
            q[1] = y;
            q[2] = z;
            q[3] = w;
        }
        
        sv_inline f32 *get() {
            return q;
        }
        
        sv_inline const f32 *get() const {
            return q;
        }
        
        FMat3 getMat3() const;
        
        f32 getAngle(const FVec3 &axis) const;
        
        sv_inline IMIQuat &normalize() {
            f32 ilength = Math::rsqrt(x * x + y * y + z * z + w * w);
            x *= ilength; y *= ilength; z *= ilength; w *= ilength;
            return *this;
        }
        
        sv_inline IMIQuat &normalizeFast() {
            f32 ilength = Math::rsqrtFast(x * x + y * y + z * z + w * w);
            x *= ilength; y *= ilength; z *= ilength; w *= ilength;
            return *this;
        }
        
        union {
            struct {
                f32 x,y,z,w;
            };
            f32 q[4];
#ifdef USE_SSE
            __m128 vec;
#elif USE_ALTIVEC
            vec_float4 vec;
#elif USE_NEON
            float32x4_t vec;
#endif
        };
    };
    
    //
    extern const IMIQuat quat_identity;
    
    s32 operator==(const IMIQuat &q0,const IMIQuat &q1);
    s32 operator!=(const IMIQuat &q0,const IMIQuat &q1);
    IMIQuat operator*(const IMIQuat &q,f32 v);
    FVec3 operator*(const IMIQuat &q,const FVec3 &v);
    FVec3 operator*(const FVec3 &v,const IMIQuat &q);
    DVec3 operator*(const IMIQuat &q,const DVec3 &v);
    DVec3 operator*(const DVec3 &v,const IMIQuat &q);
    IMIQuat operator*(const IMIQuat &q0,const IMIQuat &q1);
    IMIQuat operator+(const IMIQuat &q0,const IMIQuat &q1);
    IMIQuat operator-(const IMIQuat &q0,const IMIQuat &q1);
    
    //
    sv_inline s32 compare(const IMIQuat &q0,const IMIQuat &q1) {
        return (compare(q0.x,q1.x) && compare(q0.y,q1.y) && compare(q0.z,q1.z) && compare(q0.w,q1.w));
    }
    
    sv_inline s32 compare(const IMIQuat &q0,const IMIQuat &q1,f32 epsilon) {
        return (compare(q0.x,q1.x,epsilon) && compare(q0.y,q1.y,epsilon) && compare(q0.z,q1.z,epsilon) && compare(q0.w,q1.w,epsilon));
    }
    
    sv_inline f32 dot(const IMIQuat &q0,const IMIQuat &q1) {
        return q0.x * q1.x + q0.y * q1.y + q0.z * q1.z + q0.w * q1.w;
    }
    
    sv_inline IMIQuat &mul(IMIQuat &ret,const IMIQuat &q,f32 v) {
        ret.x = q.x * v;
        ret.y = q.y * v;
        ret.z = q.z * v;
        ret.w = q.w * v;
        return ret;
    }
    
    sv_inline IMIQuat &mad(IMIQuat &ret,const IMIQuat &q0,f32 v,const IMIQuat &q1) {
        ret.x = q0.x * v + q1.x;
        ret.y = q0.y * v + q1.y;
        ret.z = q0.z * v + q1.z;
        ret.w = q0.w * v + q1.w;
        return ret;
    }
    
    sv_inline IMIQuat &add(IMIQuat &ret,const IMIQuat &q0,const IMIQuat &q1) {
        ret.x = q0.x + q1.x;
        ret.y = q0.y + q1.y;
        ret.z = q0.z + q1.z;
        ret.w = q0.w + q1.w;
        return ret;
    }
    
    sv_inline IMIQuat &sub(IMIQuat &ret,const IMIQuat &q0,const IMIQuat &q1) {
        ret.x = q0.x - q1.x;
        ret.y = q0.y - q1.y;
        ret.z = q0.z - q1.z;
        ret.w = q0.w - q1.w;
        return ret;
    }
    
    sv_inline IMIQuat &inverse(IMIQuat &ret,const IMIQuat &q) {
        ret.x = -q.x;
        ret.y = -q.y;
        ret.z = -q.z;
        ret.w = q.w;
        return ret;
    }
    
    //
    FVec3 &mul(FVec3 &ret,const IMIQuat &q,const FVec3 &v);
    FVec3 &mul(FVec3 &ret,const FVec3 &v,const IMIQuat &q);
    DVec3 &mul(DVec3 &ret,const IMIQuat &q,const DVec3 &v);
    DVec3 &mul(DVec3 &ret,const DVec3 &v,const IMIQuat &q);
    IMIQuat &mul(IMIQuat &ret,const IMIQuat &q0,const IMIQuat &q1);
    IMIQuat &slerp(IMIQuat &ret,const IMIQuat &q0,const IMIQuat &q1,f32 k);
    
    //
    IMIQuat normalize(const IMIQuat &q);
    IMIQuat inverse(const IMIQuat &q);
    IMIQuat slerp(const IMIQuat &q0,const IMIQuat &q1,f32 k);
    
    //
    void decomposeTransform(const FMat4 &m,IMIQuat &q0,IMIQuat &q1);
    FMat4 &composeTransform(FMat4 &ret,const IMIQuat &q0,const IMIQuat &q1);

}//!namespace imi


#endif /* __IMI_QUAT_H__ */

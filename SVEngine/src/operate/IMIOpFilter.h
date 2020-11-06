//
// IMIOpFilter.h 
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATEFILTER_H
#define IMI_OPERATEFILTER_H


#include "IMIOpBase.h"

namespace imi {
    //设置美颜滤镜
    class IMIOpSetBeautyFilter : public IMIOpBase {
    public:
        IMIOpSetBeautyFilter(IMIInstPtr _app,cptr8 _scenename,cptr8 _filter, int _lows);
    protected:
        void _process(f32 _dt);
        IMIString m_scenename;
        IMIString m_filter;
        s32 m_lows;
    };
 
    class IMIOpUpdateFilterSmooth : public IMIOpBase {
    public:
        f32 m_smooth;
        u32 m_type;
        IMIOpUpdateFilterSmooth(IMIInstPtr _app,f32 _smooth,u32 _type);
    protected:
        void _process(f32 _dt);
      
    };
    
    class IMIOpUpdateBSplineFilter : public IMIOpBase {
    public:
        IMIDataSwapPtr m_pDataSwap;
        IMIOpUpdateBSplineFilter(IMIInstPtr _app,IMIDataSwapPtr _pDataSwap);
    protected:
        void _process(f32 _dt);
        
    };
    
    //关闭美颜滤镜
    class IMIOpCloseBeautyFilter : public IMIOpBase {
    public:
        IMIOpCloseBeautyFilter(IMIInstPtr _app);
    protected:
        void _process(f32 _dt);
    };
    
    //
    class IMIOpShapeFaceSmoothFilter : public IMIOpBase {
    public:
        IMIOpShapeFaceSmoothFilter(IMIInstPtr _app,f32 _face,f32 _eye);
    protected:
        void _process(f32 _dt);
        f32 m_face;
        f32 m_eye;
    };
    
    //设置查找表
    class IMIOpLUTFilterCreate : public IMIOpBase{
    public:
        IMIOpLUTFilterCreate(IMIInstPtr _app,cptr8 _scenename,cptr8 _path,s32 resid);
    protected:
        void _process(f32 _dt);
        IMIString m_path;
        s32 m_resid;
    };
    
    class IMIOpLUTFilterDestory : public IMIOpBase{
    public:
        IMIOpLUTFilterDestory(IMIInstPtr _app,cptr8 _scenename,s32 resid);
    protected:
        void _process(f32 _dt);
    };
    
}//!namespace imi


#endif //IMI_OPERATEFILTER_H

//
// IMIOpRender.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATERENDER_H
#define IMI_OPERATERENDER_H

#include "IMIOpBase.h"
#include "../base/IMIMat4.h"

namespace imi {
    
#ifdef IMI_IOS

#endif

#ifdef IMI_WIN

#endif
    
#ifdef IMI_OSX

#endif
    
#ifdef IMI_ANDROID
    
#endif
    

    //改变渲染器尺寸
    class IMIOpResizeRenderder : public IMIOpBase {
    public:
        IMIOpResizeRenderder(IMIInstPtr _app,s32 _w,s32 _h);
        
    protected:
        void _process(f32 dt);
        s32 m_width;
        s32 m_height;
    };
    
    //设置GL渲染目标
    class IMIOpSetRenderTarget : public IMIOpBase {
    public:
        IMIOpSetRenderTarget(IMIInstPtr _app);
        
        void setTargetParam(s32 _w,s32 _h,u32 _frameID,u32 _colorID, bool _mirror);
        
    protected:
        void _process(f32 dt);
        
        s32 m_width;
        s32 m_height;
        bool m_mirror;
        u32 m_frameID;
        u32 m_colorID;
    };
    
    //设置渲染目标 -- 纹理
    class IMIOpSetRenderTextureTarget : public IMIOpBase {
    public:
        IMIOpSetRenderTextureTarget(IMIInstPtr _app);

        void setTargetParam(s32 _w,s32 _h,u32 _textureId, bool _mirror);

    protected:
        void _process(f32 dt);

        s32 m_width;
        s32 m_height;
        bool m_mirror;
        u32 m_texId;
    };

    
    class IMIOpSetRenderMirror: public IMIOpBase{
    public:
        IMIOpSetRenderMirror(IMIInstPtr _app);
        
        void setTargetParam(bool _mirror);
    protected:
        void _process(f32 dt);
        
        bool m_mirror;
    };
    
}//!namespace imi




#endif //IMI_OPERATERENDER_H

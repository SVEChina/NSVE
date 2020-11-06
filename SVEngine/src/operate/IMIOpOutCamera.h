//
// IMIOpOutCamera.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_OPERATE_OUTCAMERA_H
#define IMI_OPERATE_OUTCAMERA_H

#include "IMIOpBase.h"

namespace imi {
    
    //创建ios相机
    class IMIOpCreateIOSInstream : public IMIOpBase {
    public:
        IMIOpCreateIOSInstream(IMIInstPtr _app,cptr8 _name,IMI_PIC_FORMATE _format,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void _process(f32 _dt);
        
    protected:
        IMIString m_name;
        IMI_PIC_FORMATE m_formate;
        s32 m_width;
        s32 m_height;
        f32 m_angle;
        bool m_show;
    };
    
    //创建ios相机
    class IMIOpCreateIOSTexIDInstream : public IMIOpBase {
    public:
        IMIOpCreateIOSTexIDInstream(IMIInstPtr _app,cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, IMI_PIC_FORMATE _format,s32 _w,s32 _h,f32 _angle, bool _show = false);
        
        void _process(f32 _dt);
        
    protected:
        IMIString m_name;
        IMI_PIC_FORMATE m_formate;
        s32 m_width;
        s32 m_height;
        f32 m_angle;
        u32 m_tex0ID;
        u32 m_tex1ID;
        u32 m_tex2ID;
        bool m_show;
    };
    
    //销毁ios相机
    class IMIOpDestroyIOSInstream : public IMIOpBase {
    public:
        IMIOpDestroyIOSInstream(IMIInstPtr _app,cptr8 _name);
        
        void _process(f32 _dt);
    protected:
        IMIString m_name;
    };
    
    //创建ios输出流
    class IMIOpCreateIOSOutstream : public IMIOpBase {
    public:
        IMIOpCreateIOSOutstream(IMIInstPtr _app,cptr8 _name,s32 _format, s32 _width, s32 _height, s32 _steamType = 20);
        
        void _process(f32 _dt);
        
    protected:
        IMIString m_name;
        s32 m_formate;
        s32 m_streamType;
        s32 m_width;
        s32 m_height;
    };
    
    //销毁ios输出流
    class IMIOpDestroyIOSOutstream : public IMIOpBase {
    public:
        IMIOpDestroyIOSOutstream(IMIInstPtr _app,cptr8 _name);
        
        void _process(f32 _dt);
    protected:
        IMIString m_name;
    };
    
    //打开ios输出流
    class IMIOpOpenIOSOutstream : public IMIOpBase {
    public:
        IMIOpOpenIOSOutstream(IMIInstPtr _app, cb_out_stream _cb);
        
        void _process(f32 _dt);
    protected:
        cb_out_stream m_cb;
    };
    
    //关闭ios输出流
    class IMIOpCloseIOSOutstream : public IMIOpBase {
    public:
        IMIOpCloseIOSOutstream(IMIInstPtr _app);
        
        void _process(f32 _dt);
    };
    
    //创建一个andriod相机
    class IMIOpCreateAndriodCamera: public IMIOpBase {
    public:
        IMIOpCreateAndriodCamera(IMIInstPtr _app,s32 _format,s32 _w,s32 _h,f32 _angle);
        
        void _process(f32 _dt);
        
    protected:
        s32 m_formate;
        s32 m_width;
        s32 m_height;
        f32 m_angle;
    };
    
    //销毁android相机
    class IMIOpDestroyAndoidCamera : public IMIOpBase {
    public:
        IMIOpDestroyAndoidCamera(IMIInstPtr _app,cptr8 _name);
        
        void _process(f32 _dt);
    protected:
        IMIString m_name;
    };
   
    //创建一个纹理相机
    class IMIOpCreateTextureCamera : public IMIOpBase {
    public:
        IMIOpCreateTextureCamera(IMIInstPtr _app,s32 _format,s32 _w,s32 _h,f32 _angle);
        
        void _process(f32 _dt);
        
    protected:
        s32 m_formate;
        s32 m_width;
        s32 m_height;
        f32 m_angle;
    };

    //销毁ios输出流
    class IMIOpDestroyTextureOutstream : public IMIOpBase {
    public:
        IMIOpDestroyTextureOutstream(IMIInstPtr _app,cptr8 _name);

        void _process(f32 _dt);
    protected:
        IMIString m_name;
    };


    //创建一个流相机
    class IMIOpCreateStreamCamera : public IMIOpBase {
    public:
        IMIOpCreateStreamCamera(IMIInstPtr _app,cptr8 _name,s32 _format,s32 _w,s32 _h,f32 _angle);
        
        void _process(f32 _dt);
        
    protected:
        s32 m_formate;
        s32 m_width;
        s32 m_height;
        f32 m_angle;
        IMIString m_name;
    };


    //销毁一个相机流

    class IMIOpDestroyStreamCamera : public IMIOpBase {
    public:
        IMIOpDestroyStreamCamera(IMIInstPtr _app,cptr8 _name);

        void _process(f32 _dt);
    protected:
        IMIString m_name;
    };
    

}//!namespace imi



#endif //IMI_OPERATE_OUTCAMERA_H

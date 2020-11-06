//
// IMIEGLContext.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#ifndef IMI_EGLCONTEXT_H
#define IMI_EGLCONTEXT_H

//c++层context

#include "IMICtxBase.h"

//只有一个后台  所谓多场景输出 指的是多纹理输出
#ifdef IMI_ANDROID

namespace imi {

    class IMIEGLContext : public IMICtxBase {

    public:
        IMIEGLContext(IMIInstPtr _app);

        ~IMIEGLContext();
        
        void init(void* _window, void *_context, s32 _glversion);

        virtual bool activeContext(IMIRendererPtr _renderer);
        
        virtual bool swap(IMIRendererPtr _renderer);

        virtual void* getContext();

    protected:
        EGLDisplay m_Display;
        EGLConfig *m_configsList;
        EGLConfig m_GLConfigOff;
        EGLContext m_gl_context;
        EGLContext m_gl_contextShare;
        EGLSurface m_pGLSurface;
        u32 m_color_size_;
        u32 m_depth_size_;
        GLint m_screen_width_;
        GLint m_screen_height_;
        void* m_pwindow;
        bool m_context_valid_;
        bool m_egl_context_initialized_;
        bool m_gles_initialized_;
        bool m_es3_supported_;
        s32 m_gl_version_;

        void initGLES();

        bool init(ANativeWindow* window);

        bool initEGLContext();

        void createSurface();

        EGLint resume(ANativeWindow* window);

        void destroyContext();

        bool active();
    };

}//!namespace imi
#endif  //IMI_ANDROID
#endif //IMI_EGLCONTEXT_H

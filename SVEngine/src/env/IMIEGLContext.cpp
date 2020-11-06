//
// IMIEGLContext.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMIEGLContext.h"

using namespace imi;


#ifdef IMI_ANDROID

IMIEGLContext::IMIEGLContext(IMIInstPtr _app)
: IMICtxBase(_app) {
    m_Display = nullptr;
    m_configsList = nullptr;
    //离线环境
    m_gl_context = nullptr;
    m_pGLSurface = nullptr;
    m_GLConfigOff = nullptr;
    m_gl_contextShare=_context;
    m_egl_context_initialized_=false;
    m_context_valid_=false;
    init(static_cast<ANativeWindow *>(_window));
}

IMIEGLContext::~IMIEGLContext() {
    if (m_configsList) {
        free(m_configsList);
    }
    destroyContext();
    m_configsList = nullptr;
}

void IMIEGLContext::init(void* _window,void* _context,s32 _glversion) {
    
}

void IMIEGLContext::initGLES() {
    if (m_gles_initialized_) return;
    //
    // Initialize OpenGL ES 3 if available
    //
    m_gl_version_ = 3.0f;
//    const char* versionStr = (const char*)glGetString(GL_VERSION);
//    if (strstr(versionStr, "OpenGL ES 3.") && gl3stubInit()) {
//        m_es3_supported_ = true;
//        m_gl_version_ = 3.0f;
//    } else {
//        m_gl_version_ = 2.0f;
//    }

    m_gles_initialized_ = true;
}


bool IMIEGLContext::init(ANativeWindow* window) {
    if (m_egl_context_initialized_) return true;
    //
    // Initialize EGL
    //
    m_pwindow = window;
    createSurface();
    initEGLContext();
    initGLES();

    m_egl_context_initialized_ = true;

    return true;
}

void IMIEGLContext::createSurface(){
    m_Display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(m_Display, 0, 0);

    /*
     * Here specify the attributes of the desired configuration.
     * Below, we select an EGLConfig with at least 8 bits per color
     * component compatible with on-screen windows
     */
    const EGLint attribs[] = {EGL_RENDERABLE_TYPE,
                              EGL_OPENGL_ES2_BIT,  // Request opengl ES2.0
                              EGL_RED_SIZE,
                              8,
                              EGL_GREEN_SIZE,
                              8,
                              EGL_BLUE_SIZE,
                              8,
                              EGL_ALPHA_SIZE,
                              8,
                              EGL_STENCIL_SIZE,
                              0,
                              EGL_DEPTH_SIZE,
                              8,
                              EGL_NONE};




    EGLint num_configs;
    eglChooseConfig(m_Display, attribs, &m_GLConfigOff, 1, &num_configs);
    if (!num_configs) {
        // Fall back to 16bit depth buffer
        const EGLint attribs[] = {EGL_RENDERABLE_TYPE,
                                  EGL_OPENGL_ES2_BIT,  // Request opengl ES2.0
                                  EGL_SURFACE_TYPE,
                                  EGL_WINDOW_BIT,
                                  EGL_RED_SIZE,
                                  8,
                                  EGL_GREEN_SIZE,
                                  8,
                                  EGL_BLUE_SIZE,
                                  8,
                                  EGL_ALPHA_SIZE,
                                  8,
                                  EGL_DEPTH_SIZE,
                                  16,
                                  EGL_NONE};
        eglChooseConfig(m_Display, attribs, &m_GLConfigOff, 1, &num_configs);
        m_depth_size_ = 16;
    }
    if (!num_configs) {
        IMI_LOG_ERROR("Unable to retrieve EGL config");
        return ;
    }
    ANativeWindow *windowType= static_cast<ANativeWindow *>(m_pwindow);
    m_pGLSurface = eglCreateWindowSurface(m_Display, m_GLConfigOff,
                                          windowType, NULL);
//    eglQuerySurface(m_Display, m_pGLSurface, EGL_WIDTH, &m_screen_width_);
//    eglQuerySurface(m_Display, m_pGLSurface, EGL_HEIGHT, &m_screen_height_);

}

bool IMIEGLContext::initEGLContext() {
    const EGLint context_attribs[] = {EGL_CONTEXT_CLIENT_VERSION,
                                      2,  // Request opengl ES2.0
                                      EGL_NONE};
    m_gl_context = eglCreateContext(m_Display, m_GLConfigOff, m_gl_contextShare, context_attribs);

    if (eglMakeCurrent(m_Display, m_pGLSurface, m_pGLSurface, m_gl_context) == EGL_FALSE) {
        IMI_LOG_ERROR("Unable to eglMakeCurrent EGL_ERROR");
        return false;
    }
    m_context_valid_ = true;
    return true;
}
bool IMIEGLContext::active() {

    IMI_LOG_ERROR("IMIContext::active!");
    if (m_Display && m_gl_context && m_pGLSurface) {
        bool tFlag = eglMakeCurrent(m_Display, m_pGLSurface, m_pGLSurface, m_gl_context);
        if (tFlag == false) {
//            int t_error = eglGetError();
//            IMI_LOG_DEBUG("EGL_ERROR %x", t_error);
        }
        return tFlag;
    }
    return false;
}

bool  IMIEGLContext::swap(IMIRendererPtr _renderer){
    bool b = eglSwapBuffers(m_Display, m_pGLSurface);
    if (!b) {
        EGLint err = eglGetError();
        if (err == EGL_BAD_SURFACE) {
            // Recreate surface
            createSurface();
            return EGL_SUCCESS;  // Still consider glContext is valid
        } else if (err == EGL_CONTEXT_LOST || err == EGL_BAD_CONTEXT) {
            // Context has been lost!!
            m_context_valid_ = false;
            destroyContext();
            createSurface();
        }
        return err;
    }
    return EGL_SUCCESS;
}

void IMIEGLContext::destroyContext(){
        if (m_Display != EGL_NO_DISPLAY) {
            eglMakeCurrent(m_Display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
            if (m_Display != EGL_NO_CONTEXT) {
                eglDestroyContext(m_Display, m_gl_context);
            }

            if (m_pGLSurface != EGL_NO_SURFACE) {
                eglDestroySurface(m_Display, m_pGLSurface);
            }
            eglTerminate(m_Display);
        }

    m_Display = EGL_NO_DISPLAY;
    m_gl_context = EGL_NO_CONTEXT;
    m_pGLSurface = EGL_NO_SURFACE;
    m_pwindow = nullptr;
    m_context_valid_ = false;
};

EGLint IMIEGLContext::resume(ANativeWindow* window) {
    if (m_egl_context_initialized_ == false) {
        init(window);
        return EGL_SUCCESS;
    }

    int32_t original_widhth = m_screen_width_;
    int32_t original_height = m_screen_height_;

    // Create surface
    m_pwindow = window;
    m_pGLSurface = eglCreateWindowSurface(m_Display, m_GLConfigOff,
                                          static_cast<EGLNativeWindowType>(m_pwindow), NULL);
    eglQuerySurface(m_Display, m_pGLSurface, EGL_WIDTH, &m_screen_width_);
    eglQuerySurface(m_Display, m_pGLSurface, EGL_HEIGHT, &m_screen_height_);

    if (m_screen_width_ != original_widhth || m_screen_height_ != original_height) {
        // Screen resized
        IMI_LOG_INFO("Screen resized");
    }

    if (eglMakeCurrent(m_Display, m_pGLSurface, m_pGLSurface, m_gl_context) == EGL_TRUE)
        return EGL_SUCCESS;

    EGLint err = eglGetError();
    IMI_LOG_ERROR("Unable to eglMakeCurrent %d", err);

    if (err == EGL_CONTEXT_LOST) {
        // Recreate context
        IMI_LOG_INFO("Re-creating egl context");
        initEGLContext();
    } else {
        // Recreate surface
        destroyContext();
        createSurface();
        initEGLContext();
    }

    return err;
}

bool IMIEGLContext::activeContext(IMIRendererPtr _renderer){
     if(!active()){
         IMI_LOG_ERROR("IMIContext::active! ERROR");
         return false;
     };
     IMI_LOG_ERROR("IMIContext::active! SUCESS");
     return true;
}

void* IMIEGLContext::getContext(){
    return m_gl_context;
}



#endif  //IMI_IOS

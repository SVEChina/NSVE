//
// SVRTGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RFBO_GL_H
#define SV_RFBO_GL_H

#include "../SVRFbo.h"

namespace sv {
    
    /*
     gl
     渲染目标（主目标，其他目标，都包含在内）
     */

    class SVRFboGL : public SVRFbo {
    public:
        SVRFboGL(SVInstPtr _app);
        
        ~SVRFboGL();
        
        virtual void create(SVRendererPtr _renderer,SVTargetDsp* _logic_dsp);

        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void load();
        
        virtual void unload();
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer);
        
        virtual void bind(SVRendererPtr _renderer);

        virtual void unbind(SVRendererPtr _renderer);

    protected:
        u32 m_fbo_id;
        u32 m_color_tex[SV_SUPPORT_MAX_TAREGT];
        u32 m_depth_Tex;
        u32 m_stencil_Tex;
        bool m_out_tex;
    };

}//!namespace sv



#endif //SV_RFBO_GL_H

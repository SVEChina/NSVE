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
        
        virtual void load(SVRendererPtr _renderer,SVTargetDsp* _logic_dsp);

        virtual void unload();
        
        virtual void resize(s32 _width,s32 _height,SVRendererPtr _renderer);
        
        virtual void bind(SVRendererPtr _renderer);

        virtual void unbind(SVRendererPtr _renderer);

    protected:
        s32 m_fbo_last_id;
        u32 m_fbo_id;
        //深度这块用纹理？还是用BUF？
        u32 m_depth_Tex;
        u32 m_stencil_Tex;
        bool m_out_tex;
    };

}//!namespace sv



#endif //SV_RFBO_GL_H

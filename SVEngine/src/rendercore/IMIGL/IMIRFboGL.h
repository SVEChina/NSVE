//
// IMIRTGL.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RFBO_GL_H
#define IMI_RFBO_GL_H

#include "../IMIRFbo.h"

namespace imi {
    
    /*
     gl
     渲染目标（主目标，其他目标，都包含在内）
     */

    class IMIRFboGL : public IMIRFbo {
    public:
        IMIRFboGL(IMIInstPtr _app);
        
        ~IMIRFboGL();
        
        virtual void load(IMIRendererPtr _renderer,IMITargetDsp* _logic_dsp);

        virtual void unload();
        
        virtual void resize(s32 _width,s32 _height,IMIRendererPtr _renderer);
        
        virtual void bind(IMIRendererPtr _renderer);

        virtual void unbind(IMIRendererPtr _renderer);

    protected:
        s32 m_fbo_last_id;
        u32 m_fbo_id;
        //深度这块用纹理？还是用BUF？
        u32 m_depth_Tex;
        u32 m_stencil_Tex;
        bool m_out_tex;
    };

}//!namespace imi



#endif //IMI_RFBO_GL_H

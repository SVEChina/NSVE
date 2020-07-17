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

    class SVRFboGL  : public SVRFbo {
    public:
        SVRFboGL(SVInstPtr _app);
        
        ~SVRFboGL();
        
        virtual void create(SVRendererPtr _renderer);

        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void resize(s32 _width,s32 _height);

    protected:
        u32 m_fbo_id;
        u32 m_pTargetTex[MAX_SUPPORT_TEXTAREGT];
        u32 m_pDepthTex;
        u32 m_pStencilTex;
        bool m_out_tex;
    };

    
}//!namespace sv



#endif //SV_RFBO_GL_H

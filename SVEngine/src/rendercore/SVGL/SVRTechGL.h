//
// SVRTechMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_GL_H
#define SV_RENDERTECH_GL_H

#include "../SVRTech.h"
#include "SVRenderDeclare.h"

namespace sv {

    /*
     render tech gl
     */

    class SVRTechGL : public SVRTech {
    public:
        SVRTechGL(SVInstPtr _app);
        
        ~SVRTechGL();
        
        virtual void build(SVRendererPtr _renderer);
        
        virtual void render(SVRendererPtr _renderer);
        
    protected:
        s32 _complie_shader(s32 _shadertype,cptr8 _fname);
        
        s32 m_vsf;
        s32 m_gsf;
        s32 m_tscf;
        s32 m_tsdf;
        s32 m_fsf;
        s32 m_csf;
        u32 m_p_id;
    };


}//!namespace sv


#endif //SV_RENDERTECH_GL_H

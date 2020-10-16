//
// SVRTexGL.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RTEX_GL_H
#define SV_RTEX_GL_H

#include "../SVRRes.h"
#include "../SVRTex.h"
#include "../SVRFbo.h"
#include "../SVRShader.h"
#include "../../base/SVPreDeclare.h"
#include "../../base/SVRect.h"
#include "../../core/SVVertDef.h"
#include "../../base/SVDataChunk.h"

namespace sv {

    //纹理资源
    class SVRTexGL: public SVRTex {
    public:
        SVRTexGL(SVInstPtr _app);

        virtual ~SVRTexGL();

        virtual void create(SVRendererPtr _renderer,SVTextureDsp* _tex_dsp);

        virtual void destroy(SVRendererPtr _renderer);

        virtual void commit();  //数据提交到显卡
        
        virtual void swap(SVRTexGLPtr _rtex);
        
        u32 m_res_id;
        s32 m_informate;
    };

}//!namespace sv



//
#endif //SV_RTEX_GL_H

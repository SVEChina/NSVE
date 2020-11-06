//
// IMIRTexGL.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RTEX_GL_H
#define IMI_RTEX_GL_H

#include "../IMIRRes.h"
#include "../IMIRTex.h"
#include "../IMIRFbo.h"
#include "../IMIRShader.h"
#include "../../base/IMIPreDeclare.h"
#include "../../base/IMIRect.h"
#include "../../core/IMIVertDef.h"
#include "../../base/IMIDataChunk.h"

namespace imi {

    //纹理资源
    class IMIRTexGL: public IMIRTex {
    public:
        IMIRTexGL(IMIInstPtr _app);

        virtual ~IMIRTexGL();

        virtual void load(IMIRendererPtr _renderer,IMITextureDsp* _tex_dsp);

        virtual void unload();

        virtual void commit();  //数据提交到显卡
        
        virtual void swap(IMIRTexGLPtr _rtex);
        
        u32 m_res_id;
        
        s32 m_informate;
        s32 m_dataformate;
    };

}//!namespace imi



//
#endif //IMI_RTEX_GL_H

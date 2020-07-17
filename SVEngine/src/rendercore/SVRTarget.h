//
// SVRTarget.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDER_TARGET_H
#define SV_RENDER_TARGET_H

#include "../base/SVGBase.h"
#include "SVRenderDeclare.h"

namespace sv {
    
    /*
    渲染目标（主目标，其他目标，都包含在内）
    */

    //
    struct SVTargetDsp {
        SVTargetDsp() {
            m_width = 512;
            m_height = 512;
            m_target_num = 1;
            m_use_depth = true;
            m_use_stencil = true;
            m_gl_tex = 0;
            m_oc_target = nullptr;
            m_oc_texture = nullptr;
        }
        //
        s32 m_width;
        s32 m_height;
        s32 m_target_num;
        bool m_use_depth;
        bool m_use_stencil;
        //gl
        u32 m_gl_tex;
        //metal专用参数
        void* m_oc_target;
        void* m_oc_texture;
    };

    //
    class SVRTarget : public SVGBaseEx {
    public:
        SVRTarget(SVInstPtr _app);

        ~SVRTarget();
        
        void resize(s32 _width,s32 _height);
        
        void render(SVRendererPtr _renderer);

    protected:
        virtual void _preRender(SVRendererPtr _renderer);

        virtual void _render(SVRendererPtr _renderer);

        virtual void _afterRender(SVRendererPtr _renderer);

    public:
        void bindRes(SVRFboPtr _res);

        void unbindRes();

        SVRFboPtr getResFbo();
        
        SVTargetDsp* getTargetDsp() { return &m_target_dsp; }

    protected:
        SVRFboPtr m_fbo;
        
        SVTargetDsp m_target_dsp;
    };

    
}//!namespace sv



#endif //SV_RENDER_TARGET_H

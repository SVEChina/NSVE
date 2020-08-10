//
// SVRTarget.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDER_TARGET_H
#define SV_RENDER_TARGET_H

#include "../base/SVGBase.h"
#include "../base/SVMat4.h"
#include "SVRenderDeclare.h"
#include <vector>

namespace sv {
    
    /*
    渲染目标（主目标，其他目标，都包含在内）
    */

    //目标描述
    struct SVTargetDsp {
        //
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
        
        SVRTargetPtr share();
        
        void resize(s32 _width,s32 _height);
        
        void render(SVRendererPtr _renderer);
        
        void pushRenderCommand(SVRenderCmdPtr _rcmd,SV_RSTREAM_TYPE _rstype);
        
        void clearRenderCommand();

        void bindRes(SVRFboPtr _res);

        void unbindRes();

        SVRFboPtr getResFbo();
        
        SVTargetDsp* getTargetDsp() { return &m_target_dsp; }
        
        void setFixSize() {
            m_auto = false;
        }
        
        void setAutoSize() {
            m_auto = true;
        }
        
        void setRenderPath();
        
        void setVPMat(FMat4& _mat) {
            m_vp_mat = _mat;
        }
        
        void setVMat(FMat4& _mat) {
            m_v_mat = _mat;
        }
        
        void setPMat(FMat4& _mat) {
            m_p_mat = _mat;
        }

    protected:
        std::vector<SV_RSTREAM_TYPE> m_stream_quene;    //流序，流顺的设定就是渲染路径的设定
        
        std::vector<SVRenderStreamPtr> m_stream_pool;
        
        SVRFboPtr m_fbo;
        
        SVTargetDsp m_target_dsp;
        
        bool m_auto;    //同步大小
        
    public:
        FMat4 m_v_mat;
        FMat4 m_p_mat;
        FMat4 m_vp_mat;
    };


}//!namespace sv



#endif //SV_RENDER_TARGET_H

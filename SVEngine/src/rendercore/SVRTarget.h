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
#include "../base/SVColor.h"
#include "../base/SVResDsp.h"
#include "SVRenderDeclare.h"
#include "SVNodeDeclare.h"
#include <vector>

namespace sv {
    
    /*
    渲染目标（主目标，其他目标，都包含在内）
    */

    //
    class SVRTarget : public SVGBaseEx {
    public:
        SVRTarget(SVInstPtr _app,SV_TEXIN _id);

        ~SVRTarget();
        
        SVRTargetPtr share();

        void dispatch();
        
        //
        void setClearColor(f32 _r,f32 _g,f32 _b,f32 _a);
        
        //
        void setDepth(f32 _value) ;
        
        //
        void setStencil(s32 _value) ;
        
        //
        void resize(s32 _width,s32 _height);
        
        //正常渲染
        void render(SVRendererPtr _renderer);
        
        //推送流序
        void pushStreamQuene(SV_RSTREAM _rstream);
        
        //清理流序
        void clearStreamQuene();
        
        //推送命令
        void pushCommandPre(SVRenderCmdPtr _rcmd);
        
        void pushCommandAfter(SVRenderCmdPtr _rcmd);
    
        void pushCommand(SVRenderCmdPtr _rcmd,SV_RSTREAM _rstype);
        
        void clearCommand();
        
        //绑定相机
        void bindCamera(SVCameraNodePtr _camera);

        //绑定资源
        void bindRes(s32 _instid);

        void unbindRes();

        SVRFboPtr getResFbo();
        
        SVTargetDsp* getTargetDsp() { return &m_target_dsp; }
        
        void setFixSize() {
            m_auto = false;
        }
        
        void setAutoSize() {
            m_auto = true;
        }
        
        FMat4 viewMat();
        
        FMat4 projMat();
        
        FMat4 vpMat();
        
        sv_inline SV_TEXIN getTargetID() { return m_target_id; }
        
    protected:
        //目标ID
        SV_TEXIN m_target_id;
        
        //颜色
        SVColor m_color;
        
        //深度值
        f32 m_depth_value;
        
        //模版值
        s32 m_stencil_value;
        
        //命令数目
        s32 m_cmdNum;
        
        //绑定的相机
        SVCameraNodePtr m_camera;
        
        //
        SVTargetDsp m_target_dsp;
        
        //同步大小
        bool m_auto;
        
        //是否开启输出
        bool m_output;
        
        //关联的FBO-ID
        s32 m_rfbo_id;
        
        //渲染相关
        SVRenderStreamPtr m_stream_pre;
         
        //
        SVRenderStreamPtr m_stream_after;
        
        //
        std::vector<SV_RSTREAM> m_stream_quene;    //流序，流顺的设定就是渲染路径的设定
        
        //
        std::vector<SVRenderStreamPtr> m_stream_pool;
    };

}//!namespace sv



#endif //SV_RENDER_TARGET_H

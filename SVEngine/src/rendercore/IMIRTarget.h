//
// IMIRTarget.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDER_TARGET_H
#define IMI_RENDER_TARGET_H

#include "../base/IMIGBase.h"
#include "../base/IMIMat4.h"
#include "../base/IMIColor.h"
#include "../base/IMIResDsp.h"
#include "IMIRenderDeclare.h"
#include "IMINodeDeclare.h"
#include <vector>

namespace imi {
    
    /*
    渲染目标（主目标，其他目标，都包含在内）
    */

    //
    class IMIRTarget : public IMIGBaseEx {
    public:
        IMIRTarget(IMIInstPtr _app,IMI_TEXIN _id);

        ~IMIRTarget();
        
        IMIRTargetPtr share();

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
        void render(IMIRendererPtr _renderer);
        
        //推送流序
        void pushStreamQuene(IMI_RSTREAM _rstream);
        
        //清理流序
        void clearStreamQuene();
        
        //推送命令
        void pushCommandPre(IMIRenderCmdPtr _rcmd);
        
        void pushCommandAfter(IMIRenderCmdPtr _rcmd);
    
        void pushCommand(IMIRenderCmdPtr _rcmd,IMI_RSTREAM _rstype);
        
        void clearCommand();
        
        //绑定相机
        void bindCamera(IMICameraNodePtr _camera);

        //绑定资源
        void bindRes(s32 _instid);

        void unbindRes();

        IMIRFboPtr getResFbo();
        
        IMITargetDsp* getTargetDsp() { return &m_target_dsp; }
        
        void setFixSize() {
            m_auto = false;
        }
        
        void setAutoSize() {
            m_auto = true;
        }
        
        FMat4 viewMat();
        
        FMat4 projMat();
        
        FMat4 vpMat();
        
        sv_inline IMI_TEXIN getTargetID() { return m_target_id; }
        
    protected:
        //目标ID
        IMI_TEXIN m_target_id;
        
        s32 m_cmdNum; //命令数目
        
        IMICameraNodePtr m_camera; //绑定的相机
        
        IMITargetDsp m_target_dsp;
        
        s32 m_rfbo_id; //关联的FBO-ID
        
        bool m_auto;  //同步大小
        
        bool m_output; //是否开启输出
        
        //渲染相关
        IMIRenderStreamPtr m_stream_pre;
         
        IMIRenderStreamPtr m_stream_after;
        
        std::vector<IMI_RSTREAM> m_stream_quene;    //流序，流顺的设定就是渲染路径的设定
        
        std::vector<IMIRenderStreamPtr> m_stream_pool;
    };

}//!namespace imi



#endif //IMI_RENDER_TARGET_H

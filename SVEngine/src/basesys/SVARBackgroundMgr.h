//
// SVARBackgroundMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_ARBACKGROUND_MGR_H
#define SV_ARBACKGROUND_MGR_H

#include "../basesys/SVSysBase.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../mtl/SVMtlDeclare.h"

namespace sv {

    /*
        AR背景系统，包含相片渲染和相机图片处理
     */

    class SVARBackgroundMgr : public SVSysBase {
    public:
        SVARBackgroundMgr(SVInstPtr _app);
        
        ~SVARBackgroundMgr();
        
        void init();
        
        void destroy();

        void update(f32 dt);
        
        void enable();
        
        void disable();
        
        SVRTargetPtr getTarget() { return m_ar_target; }
        
        bool isEnable() { return m_enable; }
        
        //设置输入的相机纹理
        //1文件方式
        void setInputCameraTex(cptr8 _fname);
        
        //数据方式
        void setInputCameraTex(SVDataSwapPtr _data,s32 _formate);
        
        //纹理id方式
        void setInputCameraTex(s32 _texid);
        
    protected:
        SVRTargetPtr m_ar_target;
        
        bool m_enable;
        
        s32 m_method;   //相机纹理输入方式
        
        SVTexturePtr m_tex0;
        SVTexturePtr m_tex1;
        SVTexturePtr m_tex2;
    };

}//!namespace




#endif //SV_ARBACKGROUND_MGR_H

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
#include "../work/SVWorkDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include <vector>

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

        void update(f32 _dt);
        
        bool enable();
        
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
        void _renderCameraImg(f32 _dt);
        
        //开启相机纹理
        bool m_enable;
        
        //相机格式转换的纹理和方式
        s32 m_method;
        
        //AR目标
        SVRTargetPtr m_ar_target;
        
        //用于格式转换的备用纹理
        SVTexturePtr m_tex0;
        SVTexturePtr m_tex1;
        SVTexturePtr m_tex2;
        
        //
        SVMtlCorePtr m_mtl;
    };

}//!namespace




#endif //SV_ARBACKGROUND_MGR_H

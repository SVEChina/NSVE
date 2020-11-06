//
// IMIARBackgroundMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ARBACKGROUND_MGR_H
#define IMI_ARBACKGROUND_MGR_H

#include "../basesys/IMISysBase.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include <vector>

namespace imi {

    /*
        AR背景系统，包含相片渲染和相机图片处理
     */

    class IMIARBackgroundMgr : public IMISysBase {
    public:
        IMIARBackgroundMgr(IMIInstPtr _app);
        
        ~IMIARBackgroundMgr();
        
        void init();
        
        void destroy();

        void update(f32 _dt);
        
        bool enable();
        
        bool enable(s32 _w,s32 _h);
        
        void disable();
        
        IMIRTargetPtr getTarget() { return m_ar_target; }
        
        bool isEnable() { return m_enable; }
        
        //设置输入的相机纹理
        //1文件方式
        void setInputCameraTex(cptr8 _fname);
        
        //数据方式
        void setInputCameraTex(IMIDataSwapPtr _data,IMI_PIC_FORMATE _formate);
        
        //纹理id方式
        void setInputCameraTex(s32 _texid);
        
    protected:
        void _renderCameraImg(f32 _dt);
        
        //开启相机纹理
        bool m_enable;
        
        //相机格式转换的纹理和方式
        s32 m_method;
        s32 m_width;
        s32 m_height;
        
        //AR目标
        IMIRTargetPtr m_ar_target;
        
        //用于格式转换的备用纹理
        IMITexturePtr m_tex0;
        IMITexturePtr m_tex1;
        IMITexturePtr m_tex2;
        
        //
        IMIMtlCorePtr m_mtl;
    };

}//!namespace




#endif //IMI_ARBACKGROUND_MGR_H

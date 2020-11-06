//
// IMIShaderMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TARGETMGR_H
#define IMI_TARGETMGR_H

#include "../base/IMIDef.h"
#include "../work/IMIWorkDeclare.h"
#include "IMIRenderDeclare.h"
#include "../basesys/IMISysBase.h"

namespace imi {

    class IMIRTargetMgr : public IMIGBaseEx {
    public:
        IMIRTargetMgr(IMIInstPtr _app);
        
        virtual ~IMIRTargetMgr();
        
        void init();
        
        void destroy();
        
        void loadDefault();
        
        void resize(s32 _w,s32 _h);
        
        //创建target资源
        IMIRTargetPtr createTarget(IMI_TEXIN _texid,bool _depth,bool _stencil);
        
        //创建target资源,自定义大小
        IMIRTargetPtr createTarget(IMI_TEXIN _texid,s32 _w,s32 _h,bool _depth,bool _stencil);
        
        //获取target
        IMIRTargetPtr getTarget(IMI_TEXIN _texid);
        
        //销毁Target
        void destroyTarget(IMI_TEXIN _texid);
        
    public:
        //目标池
        typedef std::vector<IMIRTargetPtr> TARGETPOOL;
        TARGETPOOL m_target_pool;
        
    protected:
        void _addTarget(IMI_TEXIN _texid,IMIRTargetPtr _target);
        
        IMILockSpinPtr m_res_lock;
    };
    
}//!namespace imi


#endif //IMI_TARGETMGR_H

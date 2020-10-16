//
// SVShaderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TARGETMGR_H
#define SV_TARGETMGR_H

#include "../base/SVDef.h"
#include "../work/SVWorkDeclare.h"
#include "SVRenderDeclare.h"
#include "../basesys/SVSysBase.h"

namespace sv {

    class SVRTargetMgr : public SVGBaseEx {
    public:
        SVRTargetMgr(SVInstPtr _app);
        
        virtual ~SVRTargetMgr();
        
        void init();
        
        void destroy();
        
        void loadDefault();
        
        void resize(s32 _w,s32 _h);
        
        //创建target资源
        SVRTargetPtr createTarget(SV_TEXIN _texid,bool _depth,bool _stencil);
        
        //创建target资源,自定义大小
        SVRTargetPtr createTarget(SV_TEXIN _texid,s32 _w,s32 _h,bool _depth,bool _stencil);
        
        //获取target
        SVRTargetPtr getTarget(SV_TEXIN _texid);
        
        //销毁Target
        void destroyTarget(SV_TEXIN _texid);
        
    public:
        //目标池
        typedef std::vector<SVRTargetPtr> TARGETPOOL;
        TARGETPOOL m_target_pool;
        
    protected:
        void _addTarget(SV_TEXIN _texid,SVRTargetPtr _target);
        
        SVLockSpinPtr m_res_lock;
    };
    
}//!namespace sv


#endif //SV_TARGETMGR_H

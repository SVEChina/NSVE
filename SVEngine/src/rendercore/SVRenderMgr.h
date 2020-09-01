//
// SVRenderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMGR_H
#define SV_RENDERMGR_H

#include "SVRenderDeclare.h"
#include "../base/SVPreDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../base/SVGBase.h"
#include "../base/SVMap.h"
#include "../base/SVMat4.h"

namespace sv {
    
    /*
     负责构建渲染器数据用的
     1.包含材质排序
     2.渲染指令的推入
     */

    class SVRenderMgr : public SVGBaseEx {
    public:
        SVRenderMgr(SVInstPtr _app);
        
        ~SVRenderMgr();
        
        void init();
        
        void destroy();
        
        void resize(s32 _w,s32 _h);
        
        void setMainRT(SVRTargetPtr _rt);
        
        SVRTargetPtr getMainRT();
        
        void clear();
        
        void render();

        void swapData();

        void pushRCmdCreate(SVRenderCmdPtr _rcmd);
        
        void pushRCmdDestory(SVRenderCmdPtr _rcmd);
        
        void pushRCmd(SVRenderCmdPtr _rcmd,SV_RSTREAM _rstype);
        
        void addRTarget(SVRTargetPtr _rt,bool _pre);
        
        void removeRTarget(SVRTargetPtr _rt);

    protected:
        void _sort();
        
        void _adapt();
        
        s32 m_adaptMode;
        
        //资源创建流
        SVRenderStreamPtr m_stream_create;
        //资源销毁流
        SVRenderStreamPtr m_stream_destroy;
        //
        SVLockSpinPtr m_renderLock;
        SVLockSpinPtr m_logicLock;
        
        //渲染的RT，不负责生命周期管理
        //前向RT
        SVArray<SVRTargetPtr> m_preRT;
        //后向RT
        SVArray<SVRTargetPtr> m_afterRT;
        //主RT
        SVRTargetPtr m_mainRT;
    };


}//!namespace sv



#endif //SV_RENDERMGR_H

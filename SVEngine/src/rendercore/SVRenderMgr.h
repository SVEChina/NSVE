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
        
        void pushRCmdPreMain(SVRenderCmdPtr _rcmd);

        void pushRCmdAftMain(SVRenderCmdPtr _rcmd);
        
        void pushRCmd(SVRenderCmdPtr _rcmd,SV_RSTREAM_TYPE _rstype);
        
        void addRTarget(SVRTargetPtr _rt,bool _pre);
        
        void delRTarget(SVRTargetPtr _rt);
        
        SVRTargetPtr getRTarget(cptr8 _name);

    protected:
        void _sort();
        
        void _adapt();
        
        s32 m_adaptMode;
        
        //资源创建流
        SVRenderStreamPtr m_stream_create;
        //资源销毁流
        SVRenderStreamPtr m_stream_destroy;
        //主流前
        SVRenderStreamPtr m_stream_main_pre;
        //主流后
        SVRenderStreamPtr m_stream_main_aft;
        
        SVLockSpinPtr m_renderLock;
        SVLockSpinPtr m_logicLock;
        //
        SVREnvPtr m_renderEnv;  //渲染环境 用于外面对接的渲染目标
        //
        SVArray<SVRTargetPtr> m_preRT; //前向RT
        SVArray<SVRTargetPtr> m_afterRT; //后向RT
        SVRTargetPtr m_mainRT; //主RT
    };


}//!namespace sv



#endif //SV_RENDERMGR_H

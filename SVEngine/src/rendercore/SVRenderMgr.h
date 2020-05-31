//
// SVRenderMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERMGR_H
#define SV_RENDERMGR_H

#include "SVRenderDef.h"
#include "../base/SVGBase.h"
#include "../base/SVMap.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVMat4d.h"
#include "../base/SVStack.h"
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
        
        void setMainRT(SVRTargetPtr _rt);
        
        void clear();
        
        void render();

        void swapData();

        void pushRCmdCreate(SVRObjBasePtr _robj);
        
        void addRTarget(SVRTargetPtr _rt,bool _pre);
        
        SVRTargetPtr getRTarget(cptr8 _name);

    
    protected:
        void _sort();
        void _adapt();
        s32 m_adaptMode;
        //渲染流(缓存流)
        SVLockPtr m_renderLock;
        SVLockPtr m_logicLock;
        
        SVArray<SVRTargetPtr> m_preRT; //前向RT
        SVArray<SVRTargetPtr> m_afterRT; //后向RT
        SVRTargetPtr m_mainRT; //主RT
        
    public:
        SVRenderScenePtr getRenderScene();
    };


}//!namespace sv



#endif //SV_RENDERMGR_H

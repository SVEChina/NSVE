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

    class SVRenderMgr : public SVGBase {
    public:
        SVRenderMgr(SVInst *_app);
        
        ~SVRenderMgr();
        
        void init();
        
        void destroy();
        
        void clear();
        
        void render();
        
        void clearScreen();
        
        void swapData();
        
        void recycleRes();  //回收GL资源
        
        SVRenderMeshPtr createMeshRObj();
        
        SVRenderScenePtr getRenderScene();
        
        void pushRCmdCreate(SVRObjBasePtr _robj);
        
        void setRenderTarget(cptr8 _name,SVRTargetPtr _rt);
        
        SVRTargetPtr getRenderTarget(cptr8 _name);
    
    protected:
        void _adapt();
        s32 m_adaptMode;
        //渲染器
        SVRendererPtr m_pRenderer;
        //渲染流(缓存流)
        SVRenderStreamPtr m_RStreamCache;
        //
        SVLockPtr m_renderLock;
        SVLockPtr m_logicLock;
    };


}//!namespace sv



#endif //SV_RENDERMGR_H

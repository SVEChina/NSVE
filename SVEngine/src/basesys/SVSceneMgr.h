//
// SVSceneMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SCENEMGR_H
#define SV_SCENEMGR_H

#include "../basesys/SVSysBase.h"
#include "../work/SVWorkDeclare.h"

namespace sv {

    /*
     场景管理
     */

    class SVSceneMgr : public SVSysBase {
    public:
        SVSceneMgr(SVInstPtr _app);
        
        ~SVSceneMgr();
        
        void init();
        
        void destroy();
        
        void setScene(SVScenePtr _scene);
        
        SVScenePtr getScene();
        
        //加载场景
        void loadScene(cptr8 _fname);
        
        //切换场景
        void changeScene(cptr8 _name);
        
        //ui变换到scene中
        void uiToScene(f32& _w,f32& _h);
        
        void update(f32 dt);
        
    protected:
        SVScenePtr m_pMainScene;    //主场景
        
        SVLockSpinPtr m_sceneLock;
    };
    
}//!namespace sv




#endif //SV_SCENEMGR_H

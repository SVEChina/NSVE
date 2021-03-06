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
#include <vector>

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
        
        void loadScene(cptr8 _fname);  //加载场景
        
        void changeScene(cptr8 _name); //切换场景
        
        void uiToScene(f32& _w,f32& _h);    //ui变换到scene中
        
        void update(f32 dt);
        
        bool addFilter(cptr8 _name,SVFilterBasePtr _filter);
        
        bool delFilter(cptr8 _name);
        
        void clearFilter();
        
        bool hasFilter(cptr8 _name);
        
        SVFilterBasePtr getFilter(cptr8 _name);
        
        void test();
        
    protected:
        SVScenePtr m_main_scene;    //主场景
        
        SVLockSpinPtr m_scene_lock;
        
        SVLockSpinPtr m_filter_lock;
        
        std::vector<SVFilterBasePtr> m_filter_pool;
    };
    
}//!namespace sv




#endif //SV_SCENEMGR_H

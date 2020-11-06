//
// IMISceneMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SCENEMGR_H
#define IMI_SCENEMGR_H

#include "../basesys/IMISysBase.h"
#include "../work/IMIWorkDeclare.h"
#include <vector>

namespace imi {
    /*
     场景管理
     */
    class IMISceneMgr : public IMISysBase {
    public:
        IMISceneMgr(IMIInstPtr _app);
        
        ~IMISceneMgr();
        
        void init();
        
        void destroy();
        
        void setScene(IMIScenePtr _scene);
        
        IMIScenePtr getScene();
        
        void loadScene(cptr8 _fname);  //加载场景
        
        void changeScene(cptr8 _name); //切换场景
        
        void uiToScene(f32& _w,f32& _h);    //ui变换到scene中
        
        void update(f32 dt);
        
        bool addFilter(cptr8 _name,IMIFilterBasePtr _filter);
        
        bool delFilter(cptr8 _name);
        
        void clearFilter();
        
        bool hasFilter(cptr8 _name);
        
        IMIFilterBasePtr getFilter(cptr8 _name);
        
        void test();
        
    protected:
        IMIScenePtr m_main_scene;    //主场景
        
        IMILockSpinPtr m_scene_lock;
        
        IMILockSpinPtr m_filter_lock;
        
        std::vector<IMIFilterBasePtr> m_filter_pool;
    };
    
}//!namespace imi




#endif //IMI_SCENEMGR_H

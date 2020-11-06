//
// IMIGlobalMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GLOBALMGR_H
#define IMI_GLOBALMGR_H

#include "../base/IMIGBase.h"
#include "../mtl/IMIMtlDeclare.h"

namespace imi {
    
    LUA_REG_DECLARE(IMIGlobalMgr);

    class IMIGlobalMgr : public IMIGBaseEx {
    public:
        IMIGlobalMgr(IMIInstPtr _app);
        
        ~IMIGlobalMgr();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        void timeTag(bool _clear,cptr8 _tag);
        
    public:
        /*基础模块*/
        /*可删减模块*/
        //基础系统
        IMIBasicSysPtr m_pBasicSys;
        //场景管理
        IMISceneMgrPtr m_scene_mgr;
        //相机管理
        IMICameraMgrPtr m_camera_mgr;
        //动画系统
        IMIAniMgrPtr m_ani_mgr;
        //模块(插件)部分
        IMIModuleSysPtr m_pModuleSys;
        //灯光部分
        IMILightSysPtr m_pLightSys;
        //识别部分
        IMIDetectMgrPtr m_detect_mgr;
        //模型部分
        IMIModelMgrPtr  m_pModelMgr;
        //变形形同
        IMIDeformMgrPtr m_pDeformSys;
        //物理世界
        IMIPhysicsWorldMgrPtr m_pPhysicSys;
        //时间标志
        timeval timTagLast;
    };
    
}//!namespace imi



#endif //IMI_GLOBALMGR_H

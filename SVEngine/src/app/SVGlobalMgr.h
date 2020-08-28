//
// SVGlobalMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_GLOBALMGR_H
#define SV_GLOBALMGR_H

#include "../base/SVGBase.h"
#include "../act/SVActDeclare.h"
#include "../mtl/SVMtlDeclare.h"

namespace sv {
    
    class SVGlobalMgr : public SVGBaseEx {
    public:
        SVGlobalMgr(SVInstPtr _app);
        
        ~SVGlobalMgr();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void update(f32 dt);
        
        void timeTag(bool _clear,cptr8 _tag);
        
    public:
        /*基础模块*/
        SVRenderMgrPtr m_render_mgr; //渲染部分
        /*可删减模块*/
        //事件部分
        SVEventMgrPtr m_pEventMgr;
        //基础系统
        SVBasicSysPtr m_pBasicSys;
        //场景管理
        SVSceneMgrPtr m_pSceneMgr;
        //相机管理
        SVCameraMgrPtr m_camera_mgr;
        //模块(插件)部分
        SVModuleSysPtr m_pModuleSys;
        //灯光部分
        SVLightSysPtr m_pLightSys;
        //shader部分
        SVShaderMgrPtr m_shader_mgr;
        //纹理部分
        SVTexMgrPtr m_tex_mgr;
        //材质库
        SVMtlLibPtr m_mtlLib;
        //识别部分
        SVDetectMgrPtr m_detect_mgr;
        //模型部分
        SVModelMgrPtr  m_pModelMgr;
        //静态数据
        SVComDataPtr m_commonData;
        //python
        SVLuaSysPtr m_lua_sys;
        //变形形同
        SVDeformMgrPtr m_pDeformSys;
        //AR背景
        SVARBackgroundMgrPtr m_arbg_mgr;
        //物理世界
        SVPhysicsWorldMgrPtr m_pPhysicSys;
        //时间标志
        timeval timTagLast;
    };
    
}//!namespace sv



#endif //SV_GLOBALMGR_H

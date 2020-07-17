//
// SVGlobalMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_GLOBALMGR_H
#define SV_GLOBALMGR_H

#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../act/SVActDeclare.h"
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
        SVRenderMgrPtr m_pRenderMgr; //渲染部分
        SVFileMgrPtr m_pFileMgr; //文件部分
        SVConfigPtr m_pConfig; //配置部分
        
        /*可删减模块*/
        //事件部分
        SVEventMgrPtr m_pEventMgr;
        //基础系统
        SVBasicSysPtr m_pBasicSys;
        //场景管理
        SVSceneMgrPtr m_pSceneMgr;
        //相机管理
        SVCameraMgrPtr m_pCameraMgr;
        //模块(插件)部分
        SVModuleSysPtr m_pModuleSys;
        //灯光部分
        SVLightSysPtr m_pLightSys;
        //shader部分
        SVShaderMgrPtr m_pShaderMgr;
        //纹理部分
        SVTexMgrPtr m_pTexMgr;

        //识别部分
        SVDetectMgrPtr m_pDetectMgr;
        //模型部分
        SVModelMgrPtr  m_pModelMgr;
        //静态数据
        SVComDataPtr m_pComData;
        //
        SVPythonSysPtr m_pPythonSys;
        //变形形同
        SVDeformMgrPtr m_pDeformSys;
        //物理世界
        SVPhysicsWorldMgrPtr m_pPhysicSys;
        //时间标志
        timeval timTagLast;
    };
    
}//!namespace sv



#endif //SV_GLOBALMGR_H

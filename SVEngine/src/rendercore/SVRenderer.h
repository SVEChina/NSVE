//
// SVRenderer.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERER_BASE_H
#define SV_RENDERER_BASE_H

#include "SVRenderDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../base/SVGBase.h"
#include "../base/SVMat4.h"
#include "../base/SVArray.h"
#include "../base/SVStack.h"
#include "../core/SVVertDef.h"

#include <list>
#include <vector>
#include <map>

//渲染器封装的是算法

namespace sv {

    //
    struct VPParam{
        u32 m_x;
        u32 m_y;
        u32 m_width;
        u32 m_height;
    };

    /*
     渲染内核
     1.渲染资源的创建与销毁
     2.渲染命令的统计（读，写流）
     3.渲染优化（材质排序，批次合并）
     4.渲染状态管理
     5.渲染
     */
    
    class SVRenderer: public SVGBaseEx {
    public:
        SVRenderer(SVInstPtr _app);
        
        ~SVRenderer();
        
        //初始化
        virtual void init(s32 _w,s32 _h);
        
        //销毁
        virtual void destroy();
        
        //重置大小
        virtual void resize(s32 _w,s32 _h);
        
        //创建纹理资源
        virtual SVRTexPtr createResTexture() { return nullptr; }
        
        //创建shader资源
        virtual SVRShaderPtr createResShader() { return nullptr; }
        
        //创建buf资源
        virtual SVRMeshResPtr createResBuf() { return nullptr; }
        
        //创建fbo资源
        virtual SVRFboPtr createResFbo() { return nullptr; }
        
        //创建target资源
        virtual SVRTargetPtr createTarget(SVINTEX _texid,bool _depth,bool _stencil){ return nullptr; }
        
        //创建target资源,自定义大小
        virtual SVRTargetPtr createTarget(SVINTEX _texid,s32 _w,s32 _h,bool _depth,bool _stencil){ return nullptr; }
        
        //获取target
        virtual SVRTargetPtr getTarget(SVINTEX _texid);
        
        //销毁Target
        virtual void destroyTarget(SVINTEX _texid);
        
        //交换纹理
        virtual void swapInTexture(SVINTEX _tex1,SVINTEX _tex2);
        
        //增加渲染内核资源
        virtual void addRes(SVRResPtr _res);
        
        //移除渲染内核资源
        virtual void removeRes(SVRResPtr _res);
        
        //清理渲染内核资源
        virtual void clearRes();
        
        //设置当前target
        virtual void setCurTarget(SVRTargetPtr _target);
    
        //处理材质
        virtual bool processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface){ return false; }
        
        //处理纹理
        virtual bool processTexture(SVRTexPtr _tex,s32 _chn,s32 _type) { return false; }
        
        //处理mesh
        virtual bool processMesh(SVRenderMeshPtr _mesh){ return false; }
        
        //绘制mesh
        virtual void drawMesh(SVRenderMeshPtr _mesh){ }
        
        //绘制屏幕
        virtual void drawScreen(SVINTEX _texid) { }
        
        //自动回收
        virtual void removeUnuseRes();

    protected:
        
        //增加target
        void _addTarget(SVINTEX _texid,SVRTargetPtr _target);
        
        //当前的target
        SVRTargetPtr m_cur_target;
        
        //资源锁
        SVLockSpinPtr m_resLock;
        
        //渲染内核资源,起到资源统计和管理的作用
        typedef std::list<SVRResPtr> ROBJLIST;
        ROBJLIST m_robjList;
        
        //目标池
        typedef std::map<SVINTEX,SVRTargetPtr> TARGETPOOL;
        TARGETPOOL m_target_pool;
    };
    
}//!namespace sv

//
#endif //SV_RENDERER_BASE_H

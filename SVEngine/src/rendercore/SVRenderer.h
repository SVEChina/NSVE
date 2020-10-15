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
#include "../base/SVObjectPool.h"
#include "../core/SVVertDef.h"

#include <list>
#include <vector>
#include <map>

//渲染器封装的是算法，不应该带有数据，带有对象是合理的

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
        
        virtual ~SVRenderer();
        
        //初始化
        virtual void init();
        
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
        
        //获取纹理资源
        virtual SVRTexPtr getResTexture(s32 _uid) const { return nullptr; }
        
        //获取shader资源
        virtual SVRShaderPtr getResShader(s32 _uid) const { return nullptr; }
        
        //获取buf资源
        virtual SVRMeshResPtr getResBuf(s32 _uid) const { return nullptr; }
        
        //获取fbo资源
        virtual SVRFboPtr getResFbo(s32 _uid) const { return nullptr; }
        
        //获取纹理资源
        virtual void destroyResTexture(s32 _uid) {}
        
        //获取shader资源
        virtual void destroyResShader(s32 _uid) {}
        
        //获取buf资源
        virtual void destroyResBuf(s32 _uid) {}
        
        //获取fbo资源
        virtual void destroyResFbo(s32 _uid) {}
        
        //获取内置Taget
        virtual SVRTargetPtr getTarget(SV_TEXIN _texid);
        
        //获取内部纹理
        virtual SVTexturePtr getInTexture(SV_TEXIN _texid);
        
        //交换纹理
        void swapInTexture(SV_TEXIN _tex1,SV_TEXIN _tex2);
        
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
        virtual void drawScreen(SV_TEXIN _texid) { }
        
        //自动回收
        virtual void removeUnuseRes();

    protected:
        //状态
        //当前的target
        SVRTargetPtr m_cur_target;
        
        //资源锁
        SVLockSpinPtr m_res_lock;
        
        //起到资源统计和管理的作用
        typedef std::list<SVRResPtr> ROBJLIST;
        ROBJLIST m_robjList;
    };
    
}//!namespace sv

//
#endif //SV_RENDERER_BASE_H

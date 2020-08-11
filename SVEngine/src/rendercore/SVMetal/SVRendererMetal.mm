//
// SVRendererMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRendererMetal.h"
#include "SVRFboMetal.h"
#include "SVRTexMetal.h"
#include "SVRShaderMetal.h"
#include "SVRMeshMetal.h"
#include "../SVRTarget.h"
#include "../../app/SVInst.h"
#include "../../app/SVDispatch.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../../rendercore/SVRenderMesh.h"
#include "../../base/SVDataSwap.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVShader.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVSurface.h"

#include <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

using namespace sv;

SVRendererMetal::SVRendererMetal(SVInstPtr _app)
:SVRenderer(_app){
    m_pDevice = nullptr;
    m_pCmdQueue = nullptr;
    m_pLibrary = nullptr;
    m_pCurEncoder = nullptr;
    //prop
    m_iOS9Runtime = false;
    m_macOS11Runtime = true;
    //
    m_hasPixelFormatDepth32Float_Stencil8 = true;
    m_samplenum = 1;    //msaa采样数
}

SVRendererMetal::~SVRendererMetal(){
}

SVRendererMetalPtr SVRendererMetal::share() {
    return std::dynamic_pointer_cast<SVRendererMetal>(shareObject());
}

void SVRendererMetal::init(s32 _w,s32 _h) {
    init( MTLCreateSystemDefaultDevice(),_w,_h );
}

void SVRendererMetal::init(id<MTLDevice> _device,s32 _w,s32 _h) {
    m_pDevice = _device;
    if (m_pDevice == nil) {
        m_pDevice = MTLCreateSystemDefaultDevice();
    }
    if (m_pDevice == nil) {
        SV_LOG_INFO("don't support metal !");
        return ;
    }
    m_pCmdQueue = m_pDevice.newCommandQueue;
    m_pLibrary = [m_pDevice newDefaultLibrary];
    //
    m_inWidth = _w;
    m_inHeight = _h;
    //创建主纹理
    mApp->m_global_param.m_sv_width = _w;
    mApp->m_global_param.m_sv_height = _h;
    
    //创建主target
    SVRTargetPtr t_target = MakeSharedPtr<SVRTarget>(mApp);
    //创建描述
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_target_num = 1;
    t_dsp->m_width = _w;
    t_dsp->m_height = _h;
    t_dsp->m_use_depth = true;
    t_dsp->m_use_stencil = true;
    //创建RT
    SVDispatch::dispatchTargetCreate(mApp,t_target);
    //设置渲染路径
    t_target->setRenderPath();
    //设置主RT
    mApp->getRenderMgr()->setMainRT(t_target);
    //重置大小
    mApp->resize(t_dsp->m_width,t_dsp->m_height);
}

//销毁
void SVRendererMetal::destroy(){
}

//重置大小
void SVRendererMetal::resize(s32 _w,s32 _h) {
    //
}

SVRTexPtr SVRendererMetal::createResTexture()  {
    return MakeSharedPtr<SVRTexMetal>(mApp);
}

//shader
SVRShaderPtr SVRendererMetal::createResShader() {
    return MakeSharedPtr<SVRShaderMetal>(mApp);
}

//buf-vbo 等
SVRMeshResPtr SVRendererMetal::createResBuf()  {
    return MakeSharedPtr<SVRMeshMetal>(mApp);
}

//fbo
SVRFboPtr SVRendererMetal::createResFbo()  {
    return MakeSharedPtr<SVRFboMetal>(mApp);
}

//处理材质
bool SVRendererMetal::processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface) {
    if(!m_pCurEncoder)
        return false;
    if(_mtl && _mtl->getShader() ) {
        if(_surface ) {
            //surface-uni到shader-uni
            _mtl->getShader()->submitParam(_surface->m_tbl);
        }
        bool t_ret = _mtl->getShader()->active();
        if(t_ret) {
            if(_surface ) {
                //更新纹理
                for(s32 i=0;i<_surface->m_vs_texs.size();i++) {
                    if( _surface->m_vs_texs[i] ) {
                        processTexture( _surface->m_vs_texs[i]->getResTex() , i , 0);
                    }
                }
                //
                for(s32 i=0;i<_surface->m_fs_texs.size();i++) {
                    if( _surface->m_fs_texs[i] ) {
                        processTexture( _surface->m_fs_texs[i]->getResTex() , i , 1);
                    }
                }
            }
            return t_ret;
        }
    }
    return false;
}

bool SVRendererMetal::processTexture(SVRTexPtr _tex,s32 _chn,s32 _stage) {
    if(_tex) {
        SVRTexMetalPtr t_tex = std::dynamic_pointer_cast<SVRTexMetal>(_tex);
        t_tex->commit();    //提交数据
        if(_stage == 0) {
            //vs纹理
            [m_pCurEncoder setVertexTexture:t_tex->getInner() atIndex:_chn];
        }else if(_stage == 1) {
            //fs纹理
            [m_pCurEncoder setFragmentTexture:t_tex->getInner() atIndex:_chn];
        }
        return true;
    }
    return false;
}

//处理mesh
bool SVRendererMetal::processMesh(SVRenderMeshPtr _mesh) {
    if(!m_pCurEncoder)
        return false;
    if(_mesh->getResBuffer()) {
        _mesh->getResBuffer()->process( share() );
        return true;
    }
    return false;
}

void SVRendererMetal::drawMesh(SVRenderMeshPtr _mesh) {
    if(!m_pCurEncoder)
        return ;
    if(_mesh->getResBuffer()) {
        _mesh->getResBuffer()->draw( share() );
    }
}

void SVRendererMetal::drawBox() {
//    - (void)setVertexBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));
}


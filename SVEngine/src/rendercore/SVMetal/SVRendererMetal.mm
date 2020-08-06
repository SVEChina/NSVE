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

void SVRendererMetal::init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
    m_pDevice = _device;
    if (m_pDevice == nil) {
        m_pDevice = MTLCreateSystemDefaultDevice();
    }
    if (m_pDevice == nil) {
        SV_LOG_INFO("don't support metal !");
        return ;
    }
    //
    m_pCmdQueue = m_pDevice.newCommandQueue;
    m_pLibrary = [m_pDevice newDefaultLibrary];
    //创建主target
    SVRTargetPtr t_target = MakeSharedPtr<SVRTarget>(mApp);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_oc_target = (__bridge_retained void*)_target;
    t_dsp->m_oc_texture = (__bridge_retained void*)_targetTex;
    SVDispatch::dispatchTargetCreate(mApp,t_target);
    //设置主RTarget
    t_target->setRenderPath();
    mApp->getRenderMgr()->setMainRT(t_target);
}

//初始化
void SVRendererMetal::init(s32 _w,s32 _h){
    if (m_pDevice == nil) {
        SV_LOG_INFO("don't support metal !");
    }
    m_pCmdQueue = m_pDevice.newCommandQueue;
    m_pLibrary = [m_pDevice newDefaultLibrary];
    //创建主fbo
    m_inWidth = _w;
    m_inHeight = _h;
    //创建主纹理
    mApp->m_pGlobalParam->m_inner_width = _w;
    mApp->m_pGlobalParam->m_inner_height = _h;
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
bool SVRendererMetal::processMtl(SVMtlCorePtr _mtl) {
    if(!m_pCurEncoder)
        return false;
    if(_mtl && _mtl->getShader() ) {
        bool t_ret = _mtl->getShader()->active();
        if(t_ret) {
            //传递uniform（单独或者block）
            processShader( _mtl->getShader()->getResShader() );
            //传递纹理
            for(s32 i=0;i<MAX_TEXUNIT;i++) {
                if( _mtl->m_texUnit[i].m_pTex ) {
                    processTexture( _mtl->m_texUnit[i].m_pTex->getResTex() , i , _mtl->m_texUnit[i].m_stage_type);
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

bool SVRendererMetal::processShader(SVRShaderPtr _shader) {
    SVRShaderMetalPtr t_shader_metal = std::dynamic_pointer_cast<SVRShaderMetal>(_shader);
    if(t_shader_metal) {
        //传递uniform buffer
        if(t_shader_metal->m_vs_ubuf) {
            [m_pCurEncoder setVertexBuffer:t_shader_metal->m_vs_ubuf offset:0 atIndex:1];
        }
        if(t_shader_metal->m_fs_ubuf) {
            [m_pCurEncoder setFragmentBuffer:t_shader_metal->m_fs_ubuf offset:0 atIndex:0];
        }
        if(t_shader_metal->m_gs_ubuf) {
            //[m_pCurEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];
        }
    }
    return true;
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


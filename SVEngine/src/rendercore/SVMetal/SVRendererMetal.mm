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

////创建纹理接口
//s32 SVRendererMetal::createTexIn(s32 _texid,SVTexDsp _tdsp) {
//    MTLPixelFormat pf = MTLPixelFormatRGBA8Uint;
//    MTLTextureDescriptor* texdsp = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:pf
//                                                                                      width:_tdsp.m_width
//                                                                                     height:_tdsp.m_height
//                                                                                  mipmapped:_tdsp.m_mipmap];
//    id <MTLTexture> t_tex = [m_pDevice newTextureWithDescriptor:texdsp];
//    m_texPoolIn.append(t_tex);
//    return m_texPoolIn.size()-1;
//}

//处理材质
void SVRendererMetal::processMtl(SVMtlCorePtr _mtl) {
    if(!m_pCurEncoder)
        return ;
    if(_mtl && _mtl->getShader() ) {
        bool t_ret = _mtl->getShader()->active();
        if(t_ret) {
            //传递uniform
            //        id<MTLBuffer> buffer = [device newBufferWithLength:bufferDataByteSize options:MTLResourceStorageModeShared];
            //        struct MyUniforms *uniforms = (struct MyUniforms*)buffer.content;
            //        uniforms->modelViewProjection = modelViewProjection;
            //        uniforms->sunPosition = sunPosition;
            
//            [encoder setVertexBuffer:myUniforms offset:0 atIndex:1];
//            [encoder setFragmentBuffer:myUniforms offset:0 atIndex:1];
            
            //[m_pCurEncoder setVertexBuffer:m_dbufs[i] offset:0 atIndex:i];
            //m_pCurEncoder
            //设置各种状态
        }
    }
}

//处理mesh
void SVRendererMetal::processMesh(SVRenderMeshPtr _mesh) {
    if(!m_pCurEncoder)
        return ;
    if(_mesh->getResBuffer()) {
        _mesh->getResBuffer()->process( share() );
    }
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


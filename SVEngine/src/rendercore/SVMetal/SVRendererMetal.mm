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
#include "SVRBufferMetal.h"

#include "../SVRTarget.h"
#include "../../app/SVInst.h"
#include "../../app/SVDispatch.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../../base/SVDataSwap.h"

using namespace sv;

SVRendererMetal::SVRendererMetal(SVInstPtr _app)
:SVRenderer(_app){
    m_pDevice = nullptr;
    m_pCmdQueue = nullptr;
    m_pLibrary = nullptr;
    m_pCurEncoder = nullptr;
}

SVRendererMetal::~SVRendererMetal(){
}

void SVRendererMetal::init(id<MTLDevice> _device,id<MTLDrawable> _target,id<MTLTexture> _targetTex) {
    m_pDevice = _device;
    if (m_pDevice == nil) {
        SV_LOG_INFO("don't support metal !");
    }
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
}

SVRTexPtr SVRendererMetal::createResTexture()  {
    return MakeSharedPtr<SVRTexMetal>(mApp);
}

//shader
SVRShaderPtr SVRendererMetal::createResShader() {
    return MakeSharedPtr<SVRShaderMetal>(mApp);
}

//buf-vbo 等
SVRBufferPtr SVRendererMetal::createResBuf()  {
    return MakeSharedPtr<SVRBufferMetal>(mApp);
}

//fbo
SVRFboPtr SVRendererMetal::createResFbo()  {
    return MakeSharedPtr<SVRFboMetal>(mApp);
}

//创建纹理接口
s32 SVRendererMetal::createTexIn(s32 _texid,SVTexDsp _tdsp) {
    MTLPixelFormat pf = MTLPixelFormatRGBA8Uint;
    MTLTextureDescriptor* texdsp = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:pf
                                                                                      width:_tdsp.m_width
                                                                                     height:_tdsp.m_height
                                                                                  mipmapped:_tdsp.m_mipmap];
    id <MTLTexture> t_tex = [m_pDevice newTextureWithDescriptor:texdsp];
    m_texPoolIn.append(t_tex);
    return m_texPoolIn.size()-1;
}

s32 SVRendererMetal::createTexOut(SVTexDsp _tdsp,void* _pdata) {
    MTLPixelFormat pf = MTLPixelFormatRGBA8Uint;
    MTLTextureDescriptor* texdsp = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:pf
                                                                                      width:_tdsp.m_width
                                                                                     height:_tdsp.m_height
                                                                                  mipmapped:_tdsp.m_mipmap];
    id <MTLTexture> t_tex = [m_pDevice newTextureWithDescriptor:texdsp];
    m_texPoolOut.append(t_tex);
    return m_texPoolOut.size()-1;
}

//s32 SVRendererMetal::createTexCubeOut(s32 _w,s32 _h,s32 _ifmt,s32 _dfmt,s32 _mipmap,s32 _size,void* _pdata) {
////    MTLPixelFormat pf = MTLPixelFormatRGBA8Uint;
////    MTLTextureDescriptor* texdsp = [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:pf
////                                                                                      width:_w
////                                                                                     height:_h
////                                                                                  mipmapped:_mipmap];
////    id <MTLTexture> t_tex = [m_pDevice newTextureWithDescriptor:texdsp];
////    m_texPoolOut.append(t_tex);
////    return m_texPoolOut.size()-1;
//    return 0;
//}

////创建纹理接口
//s32 SVRendererMetal::createTexIn(s32 _texid) {
//    //id<MTLTexture>
//    return _texid;
//    return 0;
//}
//
//s32 SVRendererMetal::createTexOut() {
//    return _texid;
//}

//创建buf
s32 SVRendererMetal::createBuf(s32 _len) {
    id<MTLBuffer> t_buf = [m_pDevice newBufferWithLength:_len options: MTLResourceStorageModeShared ];
    m_bufPool.append(t_buf);
    return m_bufPool.size()-1;
}

s32 SVRendererMetal::createBuf(s32 _len,void* _data) {
    id<MTLBuffer> t_buf = [m_pDevice newBufferWithBytes:_data length: _len options: MTLResourceStorageModeShared ];
    m_bufPool.append(t_buf);
    return m_bufPool.size()-1;
}

//处理技术
void SVRendererMetal::processTech(SVRTechPtr _tech) {
    
}

//处理材质
void SVRendererMetal::processMtl(SVMtlCorePtr _mtl) {
    
}

//处理mesh
void SVRendererMetal::processMesh(SVRenderMeshPtr _mesh) {
    
}

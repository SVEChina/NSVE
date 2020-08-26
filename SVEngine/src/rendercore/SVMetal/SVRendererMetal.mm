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
#include "../../basesys/SVComData.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../../rendercore/SVRenderMesh.h"
#include "../../mtl/SVTexture.h"
#include "../../mtl/SVTexMgr.h"
#include "../../mtl/SVSurface.h"
#include "../../mtl/SVMtlLib.h"
#include "../../mtl/SVMtlCore.h"
#include "../../mtl/SVShader.h"

#include <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

using namespace sv;

SVRendererMetal::SVRendererMetal(SVInstPtr _app)
:SVRenderer(_app){
    m_pDevice = nullptr;
    m_cmdQuene = nullptr;
    m_pLibrary = nullptr;
    m_curEncoder = nullptr;
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
    m_cmdQuene = m_pDevice.newCommandQueue;
    m_pLibrary = [m_pDevice newDefaultLibrary];
    //创建主纹理
    mApp->m_global_param.m_sv_width = _w;
    mApp->m_global_param.m_sv_height = _h;
    //创建主target,设置主RT
    SVRTargetPtr t_target = createTarget(E_TEX_MAIN,true,true);
    t_target->pushStreamQuene(E_RSM_SKY );
    t_target->pushStreamQuene(E_RSM_SOLID);
    mApp->getRenderMgr()->setMainRT(t_target);
    //重置大小
    //mApp->resize(t_dsp->m_width,t_dsp->m_height);
}

//销毁
void SVRendererMetal::destroy(){
    
}

//重置大小
void SVRendererMetal::resize(s32 _w,s32 _h) {
    //
}

//创建texture资源
SVRTexPtr SVRendererMetal::createResTexture()  {
    return MakeSharedPtr<SVRTexMetal>(mApp);
}

//创建shader资源
SVRShaderPtr SVRendererMetal::createResShader() {
    return MakeSharedPtr<SVRShaderMetal>(mApp);
}

//创建buf资源
SVRMeshResPtr SVRendererMetal::createResBuf()  {
    return MakeSharedPtr<SVRMeshMetal>(mApp);
}

//创建fbo资源
SVRFboPtr SVRendererMetal::createResFbo()  {
    return MakeSharedPtr<SVRFboMetal>(mApp);
}

//创建target资源
SVRTargetPtr SVRendererMetal::createTarget(SVINTEX _texid,bool _depth,bool _stencil) {
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_imgtype = SV_IMAGE_2D;
    t_tex_dsp.m_dataFormate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = mApp->m_global_param.m_sv_width;    //宽
    t_tex_dsp.m_height = mApp->m_global_param.m_sv_height;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    //
    SVTexturePtr t_target_tex = mApp->getTexMgr()->createInTexture(_texid,t_tex_dsp);
    if(!t_target_tex) {
        return nullptr;
    }
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp,_texid);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_color_texid[0] = _texid;
    t_dsp->m_target_num = 1;
    t_dsp->m_width = mApp->m_global_param.m_sv_width;
    t_dsp->m_height = mApp->m_global_param.m_sv_height;
    t_dsp->m_use_depth = _depth;
    t_dsp->m_use_stencil = _stencil;
    //创建RT
    SVDispatch::dispatchTargetCreate(mApp,t_target);
    //增加target
    _addTarget(_texid,t_target);
    return t_target;
}

SVRTargetPtr SVRendererMetal::createTarget(SVINTEX _texid,s32 _w,s32 _h,bool _depth,bool _stencil){
    SVRTargetPtr t_target = getTarget(_texid);
    if(t_target) {
        return t_target;
    }
    //创建主纹理
    SVTextureDsp t_tex_dsp;
    t_tex_dsp.m_imgtype = SV_IMAGE_2D;
    t_tex_dsp.m_dataFormate = SV_FORMAT_RGBA8;
    t_tex_dsp.m_width = _w;    //宽
    t_tex_dsp.m_height = _h;  //高
    t_tex_dsp.m_depth = 1;                                  //深度
    t_tex_dsp.m_minmap = false;         //是否开启mipmap
    t_tex_dsp.m_computeWrite = true;    //metal 是否可以
    t_tex_dsp.m_renderTarget = true;    //metal 是否是renderTarget
    SVTexturePtr t_target_tex = mApp->getTexMgr()->createInTexture(_texid,t_tex_dsp);
    if(!t_target_tex) {
        return nullptr;
    }
    //创建主target
    t_target = MakeSharedPtr<SVRTarget>(mApp,_texid);
    SVTargetDsp* t_dsp = t_target->getTargetDsp();
    t_dsp->m_color_texid[0] = _texid;
    t_dsp->m_target_num = 1;
    t_dsp->m_width = _w;
    t_dsp->m_height = _h;
    t_dsp->m_use_depth = _depth;
    t_dsp->m_use_stencil = _stencil;
    //创建RT
    SVDispatch::dispatchTargetCreate(mApp,t_target);
    //增加target
    _addTarget(_texid,t_target);
    return t_target;
}

//
void SVRendererMetal::pushEncoder(id<MTLRenderCommandEncoder> _encoder) {
    m_curEncoder = _encoder;
}

//
void SVRendererMetal::popEncoder() {
    m_curEncoder = nullptr;
}

//处理材质
bool SVRendererMetal::processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface) {
    if(!m_curEncoder)
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
            [m_curEncoder setVertexTexture:t_tex->getInner() atIndex:_chn];
        }else if(_stage == 1) {
            //fs纹理
            [m_curEncoder setFragmentTexture:t_tex->getInner() atIndex:_chn];
        }
        return true;
    }
    return false;
}

//处理mesh
bool SVRendererMetal::processMesh(SVRenderMeshPtr _mesh) {
    if(!m_curEncoder)
        return false;
    if(_mesh && _mesh->getResBuffer()) {
        _mesh->getResBuffer()->process( share() );
        return true;
    }
    return false;
}

void SVRendererMetal::drawMesh(SVRenderMeshPtr _mesh) {
    if(!m_curEncoder)
        return ;
    if(_mesh->getResBuffer()) {
        _mesh->getResBuffer()->draw( share() );
    }
}

void SVRendererMetal::drawBox() {
//    - (void)setVertexBytes:(const void *)bytes length:(NSUInteger)length atIndex:(NSUInteger)index API_AVAILABLE(macos(10.11), ios(8.3));
}

//屏幕空间绘制
void SVRendererMetal::drawScreen(SVINTEX _texid) {
    //
    SVTexturePtr t_tex = mApp->getTexMgr()->getInTexture(_texid);
    if(!t_tex){
        return ;
    }
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    t_surface->setTexture(0,t_tex,1);
    //
    SVRenderMeshPtr t_mesh = mApp->getComData()->screenMesh();
    bool t_ret = processMesh(t_mesh);
    if(!t_ret){
        return ;
    }
    //激活材质
    SVMtlCorePtr t_mtl = mApp->getMtlLib()->getMtl("back");
    if(t_mtl) {
        t_mtl->reloadShader();
        t_ret = processMtl(t_mtl,t_surface);
        if(t_ret){
            drawMesh(t_mesh);
        }
    }
    t_surface = nullptr;
}

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

#ifdef SV_OSX

#include <Cocoa/Cocoa.h>

#endif

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
    //
    m_rfbo_pool = MakeSharedPtr<PoolFboMetal>(_app);
    m_rmesh_pool = MakeSharedPtr<PoolMeshMetal>(_app);
    m_rshader_pool = MakeSharedPtr<PoolShaderMetal>(_app);
    m_rtex_pool = MakeSharedPtr<PoolTexMetal>(_app);
}

SVRendererMetal::~SVRendererMetal(){
}

SVRendererMetalPtr SVRendererMetal::share() {
    return std::dynamic_pointer_cast<SVRendererMetal>(shareObject());
}

void SVRendererMetal::init() {
    init( MTLCreateSystemDefaultDevice() );
}

void SVRendererMetal::init(id<MTLDevice> _device) {
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
    if(m_rtex_pool) {
        return m_rtex_pool->applyObject();
    }
    return nullptr;
}

//创建shader资源
SVRShaderPtr SVRendererMetal::createResShader() {
    if(m_rshader_pool) {
        return m_rshader_pool->applyObject();
    }
    return nullptr;
}

//创建buf资源
SVRMeshResPtr SVRendererMetal::createResBuf()  {
    if(m_rmesh_pool) {
        return m_rmesh_pool->applyObject();
    }
    return nullptr;
}

//创建fbo资源
SVRFboPtr SVRendererMetal::createResFbo()  {
    if(m_rfbo_pool) {
        return m_rfbo_pool->applyObject();
    }
    return nullptr;
}

//销毁纹理资源
void SVRendererMetal::destroyResTexture(s32 _uid){
    if(m_rtex_pool) {
        m_rtex_pool->removeObject(_uid);
    }
}

//销毁shader资源
void SVRendererMetal::destroyResShader(s32 _uid)  {
    if(m_rshader_pool) {
        m_rshader_pool->removeObject(_uid);
    }
}

//销毁buf资源
void SVRendererMetal::destroyResBuf(s32 _uid) {
    if(m_rmesh_pool) {
        m_rmesh_pool->removeObject(_uid);
    }
}

//销毁fbo资源
void SVRendererMetal::destroyResFbo(s32 _uid) {
    if(m_rfbo_pool) {
        m_rfbo_pool->removeObject(_uid);
    }
}

//获取纹理资源
SVRTexPtr SVRendererMetal::getResTexture(s32 _uid) const {
    if(m_rtex_pool) {
        return m_rtex_pool->getObject(_uid);
    }
    return nullptr;
}

//获取shader资源
SVRShaderPtr SVRendererMetal::getResShader(s32 _uid) const{
    if(m_rshader_pool) {
        return m_rshader_pool->getObject(_uid);
    }
    return nullptr;
}

//获取buf资源
SVRMeshResPtr SVRendererMetal::getResBuf(s32 _uid) const{
    if(m_rmesh_pool) {
        return m_rmesh_pool->getObject(_uid);
    }
    return nullptr;
}

//获取fbo资源
SVRFboPtr SVRendererMetal::getResFbo(s32 _uid) const {
    if(m_rfbo_pool) {
        return m_rfbo_pool->getObject(_uid);
    }
    return nullptr;
}

//
void SVRendererMetal::pushEncoder(id<MTLRenderCommandEncoder> _encoder) {
    m_curEncoder = _encoder;
}

//
void SVRendererMetal::popEncoder() {
    m_curEncoder = nullptr;
}

void SVRendererMetal::bindTarget(s32 _poolid) {
    SVRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->bind(share());
    }
}

void SVRendererMetal::unbindTarget(s32 _poolid) {
    SVRFboPtr t_fbo = getResFbo(_poolid);
    if(t_fbo) {
        t_fbo->unbind(share());
    }
}

//处理材质
bool SVRendererMetal::processMtl(SVMtlCorePtr _mtl,SVSurfacePtr _surface) {
    if(!m_curEncoder)
        return false;
    if(_mtl && _mtl->getShader() ) {
        if(_surface ) {
            //变换的uniform
            _mtl->getShader()->submitParam(_surface->m_tbl);
        }
        bool t_ret = _mtl->getShader()->active();
        if(t_ret) {
            if(_surface ) {
                //更新纹理
                //如果就没有纹理，就应该不需要更新
                //vs纹理
                for(s32 i=0;i<_surface->m_vs_texs.size();i++) {
                    if( _surface->m_vs_texs[i] ) {
                        processTexture( _surface->m_vs_texs[i]->getResTex() , i , 0);
                    }
                }
                //fs纹理
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
void SVRendererMetal::drawScreen(SV_TEXIN _texid) {
    SVTexturePtr t_tex = getInTexture(_texid);
    if(!t_tex){
        return ;
    }
    SVSurfacePtr t_surface = MakeSharedPtr<SVSurface>();
    t_surface->setTexture(1,0,t_tex);
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

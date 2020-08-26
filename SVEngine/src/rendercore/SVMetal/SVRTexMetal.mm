//
// SVRTexMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTexMetal.h"
#include "SVRendererMetal.h"
#include "../../work/SVTdCore.h"
#include "../../mtl/SVTexture.h"
#include "../../app/SVInst.h"
#include "../../base/SVDataSwap.h"

//#include "../../mtl/SVMtlDef.h"
//#include "../../base/SVDataChunk.h"
//#include "../../file/SVFileMgr.h"
//#include "../../rendercore/SVRenderMgr.h"
//#include "../SVRenderer.h"

using namespace sv;

//tex资源
SVRTexMetal::SVRTexMetal(SVInstPtr _app)
:SVRTex(_app)
,m_src_tex(nullptr)
,m_src_tex_msaa(nullptr)
,m_data(nullptr)
,m_dirty(true){
}

SVRTexMetal::~SVRTexMetal(){
    if(m_src_tex_msaa) {
    }
    if(m_src_tex) {
    }
    m_data = nullptr;
    m_dirty = false;
}

//需要支持压缩纹理格式
void SVRTexMetal:: create(SVRendererPtr _renderer) {
    SVRTex::create(_renderer);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVTexturePtr t_texture = std::dynamic_pointer_cast<SVTexture>(m_logic_obj);
    if(t_rm && t_texture) {
        //
        SVTextureDsp* t_dsp = t_texture->getTextureDsp();
        m_width = t_dsp->m_width;
        m_height = t_dsp->m_height;
        m_depth = t_dsp->m_depth;
        //
        MTLTextureDescriptor* t_descriptor = [[MTLTextureDescriptor alloc] init];
        t_descriptor.pixelFormat = MTLPixelFormatInvalid;//MTLPixelFormatRGBA8Unorm;
        s32 t_bytesPerRow = 0;
        if( t_dsp->m_dataFormate == SV_FORMAT_RGBA8 ) {
            t_bytesPerRow = m_width*4;
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Uint;
        }else if( t_dsp->m_dataFormate == SV_FORMAT_R8 ) {
            t_bytesPerRow = m_width;
            t_descriptor.pixelFormat = MTLPixelFormatA8Unorm;
        }else if( t_dsp->m_dataFormate == SV_FORMAT_RG8 ) {
            t_bytesPerRow = m_width*2;
            t_descriptor.pixelFormat = MTLPixelFormatRG8Unorm;
        }
        t_descriptor.width = t_dsp->m_width;
        t_descriptor.height = t_dsp->m_height;
        t_descriptor.depth = t_dsp->m_depth;
        t_descriptor.mipmapLevelCount = 1;
        t_descriptor.sampleCount      = t_rm->m_samplenum;  //跟msaa相关
        t_descriptor.arrayLength      = 1;
        if (t_rm->m_iOS9Runtime || t_rm->m_macOS11Runtime){
            t_descriptor.cpuCacheMode = MTLCPUCacheModeDefaultCache;
            t_descriptor.storageMode = MTLStorageModeManaged;   //存储方式 MTLStorageModeShared/MTLStorageModeManaged/MTLStorageModePrivate/MTLStorageModeMemoryless
            t_descriptor.usage = MTLTextureUsageShaderRead;
            if (t_dsp->m_computeWrite){
                t_descriptor.usage |= MTLTextureUsageShaderWrite;
            }
            if (t_dsp->m_renderTarget){
                t_descriptor.usage |= MTLTextureUsageRenderTarget;
            }
        }
        //设置类型，创建纹理
        if(t_dsp->m_imgtype == SV_IMAGE_1D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType1D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(t_dsp->m_imgtype == SV_IMAGE_2D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType2D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(t_dsp->m_imgtype == SV_IMAGE_2D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType3D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(t_dsp->m_imgtype == SV_IMAGE_CUBE) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureTypeCube;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }
        if (t_rm->m_samplenum > 1){
            t_descriptor.textureType = MTLTextureType2DMultisample;
            t_descriptor.sampleCount = t_rm->m_samplenum;

            if (t_rm->m_iOS9Runtime || t_rm->m_macOS11Runtime){
                t_descriptor.storageMode = (MTLStorageMode)(2 /* MTLStorageModePrivate */);
            }
            //m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
            m_src_tex_msaa = [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }
        //更新数据
        if(m_src_tex && t_texture->getTextureData() ) {
            SVDataSwapPtr t_data = t_texture->getTextureData();
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,m_width, m_height, m_depth);
            [m_src_tex replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
        //更新mass纹理
        if(m_src_tex_msaa && t_texture->getTextureData() ) {
            SVDataSwapPtr t_data = t_texture->getTextureData();
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,m_width, m_height, m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex_msaa replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
    }
}

void SVRTexMetal::destroy(SVRendererPtr _renderer) {
    SVRTex::destroy(_renderer);
//    if(m_id>0){
//    }
}

void SVRTexMetal::commit() {
    m_texLock->lock();
    if(m_dirty && m_data) {
        //更新数据
        if(m_src_tex) {
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,m_width, m_height, m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex replaceRegion:t_region mipmapLevel:0 withBytes:m_data->getData() bytesPerRow:t_bytesPerRow];
        }
        //更新mass纹理
        if(m_src_tex_msaa) {
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,m_width, m_height, m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex_msaa replaceRegion:t_region mipmapLevel:0 withBytes:m_data->getData() bytesPerRow:t_bytesPerRow];
        }
        m_data = nullptr;
        m_dirty = false;
    }
    m_texLock->unlock();
}

void SVRTexMetal::swap(SVRTexPtr _rtex) {
    SVRTexMetalPtr tt = dynamic_pointer_cast<SVRTexMetal>(_rtex);
    if(tt) {
        id<MTLTexture> t_src_tex = tt->m_src_tex;
        id<MTLTexture> t_src_tex_msaa = tt->m_src_tex_msaa;
        tt->m_src_tex = m_src_tex;
        tt->m_src_tex_msaa = m_src_tex_msaa;
        m_src_tex = t_src_tex;
        m_src_tex_msaa = t_src_tex_msaa;
    }
}

void SVRTexMetal::setTexData(SVDataSwapPtr _data){
    m_texLock->lock();
    m_data = _data;
    m_dirty = true;
    m_texLock->unlock();
}

id<MTLTexture> SVRTexMetal::getInner() {
    if(m_msaa) {
        return m_src_tex_msaa;
    }
    return m_src_tex;
}

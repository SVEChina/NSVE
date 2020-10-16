//
// SVRTexMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTexMetal.h"
#include "SVRendererMetal.h"
#include "../../app/SVInst.h"
#include "../../base/SVDataSwap.h"
#include "../../work/SVTdCore.h"
#include "../../mtl/SVTexture.h"

using namespace sv;

//tex资源
SVRTexMetal::SVRTexMetal(SVInstPtr _app)
:SVRTex(_app)
,m_src_tex(nullptr)
,m_src_tex_msaa(nullptr)
,m_dirty(true){
}

SVRTexMetal::~SVRTexMetal(){
    if(m_src_tex_msaa) {
        m_src_tex_msaa = nullptr;
    }
    if(m_src_tex) {
        m_src_tex = nullptr;
    }
    m_dirty = false;
}

//需要支持压缩纹理格式
void SVRTexMetal:: load(SVRendererPtr _renderer,SVTextureDsp* _tex_dsp) {
    SVRTex::load(_renderer,_tex_dsp);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    if(t_rm && m_texture_dsp) {
        MTLTextureDescriptor* t_descriptor = [[MTLTextureDescriptor alloc] init];
        t_descriptor.pixelFormat = MTLPixelFormatInvalid;//MTLPixelFormatRGBA8Unorm;
        s32 t_bytesPerRow = 0;
        if( m_texture_dsp->m_data_formate == SV_FORMAT_RGBA8 ) {
            t_bytesPerRow = m_texture_dsp->m_width*4;
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Uint;
        }else if( m_texture_dsp->m_data_formate == SV_FORMAT_R8 ) {
            t_bytesPerRow = m_texture_dsp->m_width;
            t_descriptor.pixelFormat = MTLPixelFormatA8Unorm;
        }else if( m_texture_dsp->m_data_formate == SV_FORMAT_RG8 ) {
            t_bytesPerRow = m_texture_dsp->m_width*2;
            t_descriptor.pixelFormat = MTLPixelFormatRG8Unorm;
        }
        t_descriptor.width = m_texture_dsp->m_width;
        t_descriptor.height = m_texture_dsp->m_height;
        t_descriptor.depth = m_texture_dsp->m_depth;
        t_descriptor.mipmapLevelCount = 1;
        t_descriptor.sampleCount      = t_rm->m_samplenum;  //跟msaa相关
        t_descriptor.arrayLength      = 1;
        if (t_rm->m_iOS9Runtime || t_rm->m_macOS11Runtime){
            t_descriptor.cpuCacheMode = MTLCPUCacheModeDefaultCache;
#ifdef SV_OSX
            t_descriptor.storageMode = MTLStorageModeManaged;   //存储方式 MTLStorageModeShared/MTLStorageModeManaged/MTLStorageModePrivate/MTLStorageModeMemoryless
#else
            t_descriptor.storageMode = MTLStorageModeShared;
#endif
            t_descriptor.usage = MTLTextureUsageShaderRead;
            if (m_texture_dsp->m_computeWrite){
                t_descriptor.usage |= MTLTextureUsageShaderWrite;
            }
            if (m_texture_dsp->m_renderTarget){
                t_descriptor.usage |= MTLTextureUsageRenderTarget;
            }
        }
        //设置类型，创建纹理
        if(m_texture_dsp->m_image_type == SV_IMAGE_1D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType1D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_2D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType2D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_2D) {
            t_descriptor.pixelFormat = MTLPixelFormatRGBA8Unorm;
            t_descriptor.textureType = MTLTextureType3D;
            m_src_tex =  [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }else if(m_texture_dsp->m_image_type == SV_IMAGE_CUBE) {
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
            m_src_tex_msaa = [t_rm->m_pDevice newTextureWithDescriptor:t_descriptor];
        }
        //更新数据
        if(m_src_tex && m_texture_dsp->m_pData[0] ) {
            SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,
                                                  m_texture_dsp->m_width,
                                                  m_texture_dsp->m_height,
                                                  m_texture_dsp->m_depth);
            [m_src_tex replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
        //更新mass纹理
        if(m_src_tex_msaa && m_texture_dsp->m_pData[0] ) {
            SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,
                                                  m_texture_dsp->m_width,
                                                  m_texture_dsp->m_height,
                                                  m_texture_dsp->m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex_msaa replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
    }
}

void SVRTexMetal::unload() {
    SVRTex::unload();
}

void SVRTexMetal::resize() {
    //销毁纹理
    if(m_src_tex) {
        m_src_tex = nullptr;
    }
    if(m_src_tex_msaa) {
        m_src_tex_msaa = nullptr;
    }
}

void SVRTexMetal::commit() {
    m_texLock->lock();
    if(m_dirty && m_texture_dsp && m_texture_dsp->m_pData[0] ) {
        SVDataSwapPtr t_data = m_texture_dsp->m_pData[0];
        //更新数据
        if(m_src_tex) {
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,
                                                  m_texture_dsp->m_width,
                                                  m_texture_dsp->m_height,
                                                  m_texture_dsp->m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
        //更新mass纹理
        if(m_src_tex_msaa) {
            MTLRegion t_region =  MTLRegionMake3D(0, 0, 0,
                                                  m_texture_dsp->m_width,
                                                  m_texture_dsp->m_height,
                                                  m_texture_dsp->m_depth);
            s32 t_bytesPerRow = 0;
            [m_src_tex_msaa replaceRegion:t_region mipmapLevel:0 withBytes:t_data->getData() bytesPerRow:t_bytesPerRow];
        }
        m_texture_dsp->m_pData[0] = nullptr;
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

id<MTLTexture> SVRTexMetal::getInner() {
    if(m_msaa) {
        return m_src_tex_msaa;
    }
    return m_src_tex;
}

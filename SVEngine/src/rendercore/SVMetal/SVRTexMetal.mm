//
// SVRTexMetal.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTexMetal.h"
#include "SVRendererMetal.h"
#include "../../mtl/SVTexture.h"
#include "../../app/SVInst.h"
#include "../../mtl/SVMtlDef.h"
#include "../../base/SVDataChunk.h"
#include "../../file/SVFileMgr.h"
#include "../../base/SVDataSwap.h"
#include "../../work/SVTdCore.h"
#include "../../rendercore/SVRenderMgr.h"
#include "../SVRenderer.h"

using namespace sv;

//tex资源
SVRTexMetal::SVRTexMetal(SVInstPtr _app)
:SVRTex(_app)
,m_srcTex(nullptr){
}

SVRTexMetal::~SVRTexMetal(){
}

void SVRTexMetal:: create(SVRendererPtr _renderer) {
    SVRTex::create(_renderer);
    SVRendererMetalPtr t_rm = std::dynamic_pointer_cast<SVRendererMetal>(_renderer);
    SVTexturePtr t_texture = std::dynamic_pointer_cast<SVTexture>(m_logic_obj);
    if(t_rm && t_texture) {
        
    }
//    if (t_rendeMetalPtr) {
//        MTLTextureDescriptor *dsp = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:MTLPixelFormatRGBA8Unorm width:m_width height:m_height mipmapped:m_enableMipMap];
//        m_srcTex = [t_rendeMetalPtr->m_pDevice newTextureWithDescriptor:dsp]; // 创建纹理
//        MTLRegion region;
//        region.origin.x = 0;
//        region.origin.y = 0;
//        region.origin.z = 0;
//        region.size.width = m_width;
//        region.size.height = m_height;
//        region.size.depth = 1;
//    }
}

void SVRTexMetal::destroy(SVRendererPtr _renderer) {
    SVRTex::destroy(_renderer);
//    if(m_id>0){
//    }
}

void SVRTexMetal::commit() {
    m_texLock->lock();
    //    if (m_pData) {
    //        if(m_bLoad){
    //            //更新数据
    //            m_pData->lockData();
    //            glBindTexture(GL_TEXTURE_2D, m_id);
    //            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, m_informate,GL_UNSIGNED_BYTE,m_pData->getData());
    //            m_pData->unlockData();
    //            m_pData = nullptr;
    //        }
    //    }
    m_texLock->unlock();
}

void SVRTexMetal::setTexData(SVDataSwapPtr _data){
    m_texLock->lock();
    //    if( _data && _len>0 ) {
    //        SVDataSwapPtr t_pDataSwap = MakeSharedPtr<SVDataSwap>();
    //        t_pDataSwap->writeData(_data, _len);
    //        setData(t_pDataSwap);
    //    }
    m_texLock->unlock();
}

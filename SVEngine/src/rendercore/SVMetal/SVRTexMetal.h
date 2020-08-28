//
// SVRTexMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RESMETAL_TEX_H
#define SV_RESMETAL_TEX_H

#include "../SVRTex.h"
#include "../SVRShader.h"
#import <Metal/MTLTexture.h>
#import <Metal/MTLBuffer.h>
#import <Metal/MTLLibrary.h>
#import <Metal/MTLRenderPipeline.h>

namespace sv {

    //纹理描述
    struct SVTexDsp {
        s32 m_width;
        s32 m_height;
        s32 m_dfmt;     //data-formate
        bool m_mipmap;
        bool m_cube;
    };

    /*
    纹理资源
     */
    
    //1.扩充压缩纹理
    //2.扩充部分更新机制

    class SVRTexMetal: public SVRTex {
    public:
        SVRTexMetal(SVInstPtr _app);
        
        virtual ~SVRTexMetal();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void resize();
        
        virtual void setTexData(SVDataSwapPtr _data);
        
        virtual void commit();  //数据提交到显卡
        
        virtual void swap(SVRTexPtr _rtex);    //交换纹理
        
        id<MTLTexture> getInner();
        
    protected:
        //
        id<MTLTexture> m_src_tex;
        id<MTLTexture> m_src_tex_msaa;
        //
        SVDataSwapPtr m_data;
        bool m_dirty;
        s32 m_width;
        s32 m_height;
        s32 m_depth;
    };
        
    

}//!namespace sv



//
#endif //SV_RRESMETAL_TEX_H

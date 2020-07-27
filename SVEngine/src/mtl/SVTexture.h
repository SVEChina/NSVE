//
// SVTexture.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TEXTURE_H
#define SV_TEXTURE_H

#include "SVMtlDef.h"
#include "../rendercore/SVRTex.h"
#include "../rendercore/SVRenderDef.h"

namespace sv {
    
    /*
     逻辑层面的纹理
     */
    struct SVTextureDsp {
        SVTextureDsp() {
            m_kind = SV_IMAGE_2D;
            m_inFormate = SV_FORMAT_RGBA8;   //内部格式
            m_dataFormate = SV_FORMAT_RGBA8; //数据格式
            m_warp_s = E_TEX_CLAMP;     //S方向环绕
            m_warp_t = E_TEX_CLAMP;     //T方向环绕
            m_width = 1;                //宽
            m_height = 1;               //高
            m_depth = 1;                //深度    //3d纹理使用
            m_minmap = true;            //是否开启mipmap
            m_computeWrite = false;    //metal
            m_renderTarget = false;     //是否renderTarget
            m_srgb = false;             //metal
        };
        
        s32 m_kind;
        s32 m_inFormate;   //内部格式
        s32 m_dataFormate; //数据格式
        SVTEXWRAP m_warp_s;
        SVTEXWRAP m_warp_t;
        s32 m_width;    //宽
        s32 m_height;   //高
        s32 m_depth;    //深度    //3d纹理使用
        bool m_minmap;  //是否开启mipmap
        bool m_computeWrite;    //metal 是否可以
        bool m_renderTarget;    //metal 是否是renderTarget
        bool m_srgb;
    };

    class SVTexture : public SVGBaseEx {
    public:
        SVTexture(SVInstPtr _app);
        
        ~SVTexture();
        
        void init(SVTextureDsp& _param);
        
        void init(SVTextureDsp& _param,SVDataSwapPtr _data);

        void destroy();
        
        void setTexData(SVDataSwapPtr _data);
        
        virtual void commit();  //数据提交到显卡
        
        virtual bool getbLoad();
        
        //渲染内核
        void bindRes(SVRTexPtr _res);
        
        void unbindRes();
        
        SVRTexPtr getResTex();
        
        SVTextureDsp* getTextureDsp();
        
        SVDataSwapPtr getTextureData();
        
        SVDataSwapPtr getTextureCubeData(s32 _index);
        
    protected:
        void _updateData();
        SVRTexPtr m_restex;
        
    public:
        SVString m_name;
        SVTextureDsp m_texture_dsp;
        bool m_bEnableMipMap;
        SVDataSwapPtr m_pData;
        SVDataSwapPtr m_cubData[6];
        
    public:
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace sv



#endif //SV_TEXTURE_H

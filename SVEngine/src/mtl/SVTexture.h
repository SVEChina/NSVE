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
        SVTEXKIND m_kind;
        SVTEXFORMATE m_inFormate;   //内部格式
        SVTEXFORMATE m_dataFormate; //数据格式
        SVTEXWRAP m_warp_s;
        SVTEXWRAP m_warp_t;
        s32 m_width;
        s32 m_height;
        s32 m_depth;        //3d纹理使用
        bool m_minmap;
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
        //
        s32 m_type;
        s32 m_width;
        s32 m_height;
        s32 m_informate;
        s32 m_dataformate;
        bool m_bEnableMipMap;
        bool m_bData;
        bool m_bCreated;
        SVDataSwapPtr m_pData;
        SVDataSwapPtr m_cubData[6];
        
    public:
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace sv



#endif //SV_TEXTURE_H

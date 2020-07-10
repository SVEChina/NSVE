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

    class SVTexture : public SVGBaseEx {
    public:
        SVTexture(SVInstPtr _app);
        
        ~SVTexture();
        
        void init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dataformate, bool _enableMipMap);
        
        void init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dataformate, bool _enableMipMap,SVDataSwapPtr _data);
        
        void destroy();
        
        virtual void setTexData(void *_data, s32 _len);
        
        virtual void commit();  //数据提交到显卡
        
        virtual bool getbLoad();
        
        SVRTexPtr getResTex();
        
    protected:
        void _updateData();
        SVRTexPtr m_objTexPtr;
        
    public:
        SVString m_name;
        s32 m_type;
        s32 m_width;
        s32 m_height;
        s32 m_informate;
        s32 m_dataformate;
        bool m_bEnableMipMap;
        bool m_bData;
        bool m_bCreated;
        SVDataSwapPtr m_pData;
        
    public:
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace sv



#endif //SV_TEXTURE_H

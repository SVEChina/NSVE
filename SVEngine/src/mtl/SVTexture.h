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
#include "SVTexMgr.h"

namespace sv {
    
    /*
     逻辑层面的纹理
     */

    class SVTexture : public SVGBaseEx {
    public:
        SVTexture(SVInstPtr _app);
        
        ~SVTexture();
        
        void init(SVTexParam& _param);
        
        void init(SVTexParam& _param,SVDataSwapPtr _data);

        void destroy();
        
        virtual void setTexData(SVDataSwapPtr _data);
        
        virtual void commit();  //数据提交到显卡
        
        virtual bool getbLoad();
        
        SVRTexPtr getResTex();
        
    protected:
        void _updateData();
        SVRTexPtr m_objTexPtr;
        
    public:
        SVString m_name;
        SVTexParam m_param;
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
        
    public:
        virtual void pushData(u8* _srcPtr,s32 _w,s32 _h,s32 _pixelformate){}
        
        virtual void fetchData(u8* _dstPtr,s32 _w,s32 _h){}
    };
        
}//!namespace sv



#endif //SV_TEXTURE_H

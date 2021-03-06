//
// SVTexturePList.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TEXTUREPLIST_H
#define SV_TEXTUREPLIST_H

#include "SVTexture.h"
#include "../base/SVRect.h"

namespace sv {
    
    //PList假纹理

    class SVTexturePList : public SVTexture {
    public:
        SVTexturePList(SVInstPtr _app);

        ~SVTexturePList();

        virtual void init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate);
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual void refreshParam();
        
        virtual void apply();
        
        virtual void apply(void *data);
        
        virtual void commit();
        
        SVRect *getSrcRect();

        SVRect *getDstRect();
        
        void setRot(bool _rot);
        
        void setTrim(bool _trim);
        
        void setSrcw(bool _srcw);
        
        void setSrch(bool _srch);

    private:
        bool m_rot;    //是否旋转
        bool m_trim;   //是否旋转
        f32  m_srcw;   //原有纹理的宽度
        f32  m_srch;   //原有纹理的高度
        bool m_bApply;
        bool m_bApplyData;
        bool m_btexSet;
    };

}//!namespace sv


#endif //SV_TEXTUREPLIST_H

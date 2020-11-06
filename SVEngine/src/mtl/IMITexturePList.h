//
// IMITexturePList.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TEXTUREPLIST_H
#define IMI_TEXTUREPLIST_H

#include "IMITexture.h"
#include "../base/IMIRect.h"

namespace imi {
    
    //PList假纹理

    class IMITexturePList : public IMITexture {
    public:
        IMITexturePList(IMIInstPtr _app);

        ~IMITexturePList();

        virtual void init(cptr8 _name, s32 _type, s32 _width, s32 _height, s32 _informate, s32 _dateformate);
        
        virtual void create(IMIRendererPtr _renderer);
        
        virtual void destroy(IMIRendererPtr _renderer);
        
        virtual void refreshParam();
        
        virtual void apply();
        
        virtual void apply(void *data);
        
        virtual void commit();
        
        IMIRect *getSrcRect();

        IMIRect *getDstRect();
        
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

}//!namespace imi


#endif //IMI_TEXTUREPLIST_H

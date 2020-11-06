//
// IMITrans.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TRANS_H
#define IMI_TRANS_H

#include "../base/IMIGBase.h"

namespace imi {

    class IMITrans : public IMIGBaseEx {
    public:
        IMITrans(IMIInstPtr _app);
        
        virtual ~IMITrans();
        
        virtual void init(s32 _w, s32 _h,f32 _angle,IMI_PIC_FORMATE _picformate,IMI_TEXIN _tt);

        virtual void destroy();
        
        virtual void update(f32 dt);

        virtual void render();
        
        virtual void setAngle(f32 _angle);
        
    protected:
        s32 m_width;
        s32 m_height;
        IMI_PIC_FORMATE m_picformate;
        f32 m_angle;
        IMI_TEXIN m_texTT;
    };
    
}//!namespace imi

#endif //ANDROID_IMIYUVINSTRESMNODE_H

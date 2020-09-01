//
// SVTrans.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TRANS_H
#define SV_TRANS_H

#include "../base/SVGBase.h"

namespace sv {

    class SVTrans : public SVGBaseEx {
    public:
        SVTrans(SVInstPtr _app);
        
        virtual ~SVTrans();
        
        virtual void init(s32 _w, s32 _h,f32 _angle,SV_PIC_FORMATE _picformate,SV_TEXIN _tt);

        virtual void destroy();
        
        virtual void update(f32 dt);

        virtual void render();
        
        virtual void setAngle(f32 _angle);
        
    protected:
        s32 m_width;
        s32 m_height;
        SV_PIC_FORMATE m_picformate;
        f32 m_angle;
        SV_TEXIN m_texTT;
    };
    
}//!namespace sv

#endif //ANDROID_SVYUVINSTRESMNODE_H

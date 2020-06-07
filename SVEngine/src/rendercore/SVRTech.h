//
// SVRTech.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDERTECH_H
#define SV_RENDERTECH_H

#include "../base/SVGBase.h"
#include "SVRenderDeclare.h"

namespace sv {

    /*
     render tech
     */

    class SVRTech : public SVGBaseEx {
    public:
        SVRTech(SVInstPtr _app);
        
        ~SVRTech();
        
        void setShader(cptr8 _name,SV_TECH_TYPE _type);
        
        virtual void build(SVRendererPtr _renderer);
        
        virtual void render(SVRendererPtr _renderer);
        
    protected:
        
        s32 m_techDsp;  //技术描述 SV_TECH_TYPE
        
        SVString m_vs_name;
        SVString m_fs_name;
        SVString m_gs_name;
        SVString m_tsc_name;
        SVString m_tsd_name;
        SVString m_cs_name;
        
    };


}//!namespace sv


#endif //SV_RENDERTECH_H

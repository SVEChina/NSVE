//
// SVMtlSurface.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SURFACE_H
#define SV_SURFACE_H

#include "SVMtlCore.h"
#include "../base/SVParamTbl.h"
#include "../base/SVVec2.h"
#include "../base/SVVec3.h"
#include "../base/SVVec4.h"
#include "../base/SVMat2.h"
#include "../base/SVMat3.h"
#include "../base/SVMat4.h"

namespace sv {
    
    class SVSurface : public SVObject {
    public:
        SVSurface();
        
        ~SVSurface();
        
        //设置参数
        void setParam(cptr8 _name,s32 _value);

        void setParam(cptr8 _name,f32 _value);

        void setParam(cptr8 _name,FVec2 _value);

        void setParam(cptr8 _name,FVec3 _value);

        void setParam(cptr8 _name,FVec4 _value);

        void setParam(cptr8 _name,FMat2 _value);

        void setParam(cptr8 _name,FMat3 _value);

        void setParam(cptr8 _name,FMat4 _value);
        
        //参数表
        SVParamTblPtr m_tbl;
        
        //纹理表
        void setTexture(s32 _chn,SVTexturePtr _tex);
        
        std::vector<SVTexturePtr> m_texpool;
    };

}//!namespace sv

#endif //SV_SURFACE_H
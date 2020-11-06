//
// IMIMtlSurface.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SURFACE_H
#define IMI_SURFACE_H

#include "IMIMtlCore.h"
#include "../base/IMIParamTbl.h"
#include "../base/IMIVec2.h"
#include "../base/IMIVec3.h"
#include "../base/IMIVec4.h"
#include "../base/IMIMat2.h"
#include "../base/IMIMat3.h"
#include "../base/IMIMat4.h"

#include <map>

namespace imi {

    //表示材质需要更新的数据

    class IMISurface : public IMIObject {
    public:
        IMISurface();
        
        ~IMISurface();
        
        //设置参数
        void setParam(cptr8 _name,s32 _value);

        void setParam(cptr8 _name,f32 _value);

        void setParam(cptr8 _name,FVec2& _value);

        void setParam(cptr8 _name,FVec3& _value);

        void setParam(cptr8 _name,FVec4& _value);

        void setParam(cptr8 _name,FMat2& _value);

        void setParam(cptr8 _name,FMat3& _value);

        void setParam(cptr8 _name,FMat4& _value);
        
        //
        void setParamArray(cptr8 _name,s32* _value,s32 _cnt);

        void setParamArray(cptr8 _name,f32* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FVec2* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FVec3* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FVec4* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FMat2* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FMat3* _value,s32 _cnt);

        void setParamArray(cptr8 _name,FMat4* _value,s32 _cnt);
        
        //参数表，一个就够用了啊
        IMIParamTblPtr m_tbl;
        
        //纹理表
        void setTexture(s32 _stage,s32 _chn,IMITexturePtr _tex);

        IMITexturePtr getTexture(s32 _stage,s32 _chn);
        
        void setTexture(cptr8 _name,IMITexturePtr _tex);
        
        IMITexturePtr getTexture(cptr8 _name);
        
        //设置目标纹理采样数据
        void setSamplerParam(cptr8 _name,s32 _type,s32 _param);
        
        //按通道顺序设置了纹理
        std::vector<IMITexturePtr> m_vs_texs;
        std::vector<IMITexturePtr> m_fs_texs;
        
        typedef std::map<IMIString,IMITexturePtr> TEXPOOL;
        TEXPOOL m_tex_pool;
        //
        //SamplerDsp
    };

}//!namespace imi

#endif //IMI_SURFACE_H

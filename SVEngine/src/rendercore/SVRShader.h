//
// SVRShader.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RSHADER_H
#define SV_RSHADER_H

#include "SVRRes.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../core/SVVertDef.h"

/*
  GL DEF 暂时先放这里
 */

//通道数
#define CHANNEL_POSITION    0
#define CHANNEL_NORMAL      1
#define CHANNEL_COLOR0      2
#define CHANNEL_TEXCOORD0   3
#define CHANNEL_INSOFFSET   4
#define CHANNEL_TAGENT      5
#define CHANNEL_BTAGENT     6
#define CHANNEL_TEXCOORD1   7
#define CHANNEL_BONE_ID     5
#define CHANNEL_BONE_WEIGHT 6

//
#define CHANNEL_ATTRI_0     0
#define CHANNEL_ATTRI_1     1
#define CHANNEL_ATTRI_2     2
#define CHANNEL_ATTRI_3     3
#define CHANNEL_ATTRI_4     4
#define CHANNEL_ATTRI_5     5
#define CHANNEL_ATTRI_6     6
#define CHANNEL_ATTRI_7     7

//内置变量
#define NAME_POSITION   "aPosition"
#define NAME_NORMAL     "aNormal"
#define NAME_TAGENT     "aTagent"
#define NAME_BNOR       "aBNormal"
#define NAME_COLOR      "aColor"
#define NAME_TEXCOORD0  "aTexcoord0"
#define NAME_TEXCOORD1  "aTexcoord1"
#define NAME_INSOFFSET  "aInsOffset"
//骨骼动画
#define NAME_BONE_ID     "aBoneID"
#define NAME_BONE_WEIGHT "aBoneWeight"

//
#define NAME_TEX0  "aTexture0"
#define NAME_TEX1  "aTexture1"
#define NAME_TEX2  "aTexture2"
#define NAME_TEX3  "aTexture3"
#define NAME_TEX4  "aTexture4"
#define NAME_TEX5  "aTexture5"
#define NAME_TEX6  "aTexture6"
#define NAME_TEX7  "aTexture7"

//uniform
#define NAME_M_MATRIX   "aMatrixM"
#define NAME_V_MATRIX   "aMatrixV"
#define NAME_P_MATRIX   "aMatrixP"
#define NAME_VP_MATRIX  "aMatrixVP"
#define NAME_MVP_MATRIX "aMatrixMVP"

#define BLEND_FARC      "blendfrac"
#define TEXCOORD_CLIP   "texcoordClip"
#define NAME_TEXSIZE_0  "tex0size"
#define NAME_TEXSIZE_1  "tex1size"
#define NAME_TEXSIZE_2  "tex2size"
#define NAME_TEXSIZE_3  "tex3size"

#define NAME_BLENDMODE  "blendmode"
#define NAME_POINTSIZE  "ptsize"

/*
 渲染资源 shader
*/

namespace sv {

    struct ShaderDsp;
    class SVRShader: public SVRRes {
    public:
        SVRShader(SVInstPtr _app)
        :SVRRes(_app)
        ,m_shader_dsp(nullptr){
        }

        virtual ~SVRShader() {
            m_shader_dsp = nullptr;
        }

        virtual void load(SVRendererPtr _renderer,ShaderDsp* _shader_dsp){
            m_shader_dsp = _shader_dsp;
        }

        virtual void unload(){
            
        }

        virtual bool active(SVRendererPtr _render){ return false; }
        
    protected:
        ShaderDsp* m_shader_dsp;
    };
        
}//!namespace sv


#endif /* SV_RSHADER_H */

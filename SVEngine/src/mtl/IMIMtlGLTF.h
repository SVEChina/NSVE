//
// IMIMtlGLTF.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTL_GLTF_H
#define IMI_MTL_GLTF_H


#include "IMIMtlCore.h"
#include "../base/IMIVec3.h"
#include "../base/IMIVec4.h"

//GLTF材质
namespace imi {
    
    class IMIMtlGLTF : public IMIMtlCore {
    public:
        IMIMtlGLTF(IMIInstPtr _app);
        
        IMIMtlGLTF(IMIMtlGLTF *_mtl);
        
        ~IMIMtlGLTF();
        
    protected:
        IMIMtlGLTF(IMIInstPtr _app,cptr8 _name);
    
    public:
        
        virtual IMIMtlCorePtr clone();
        
        void update(f32 dt);
        
        void refresh();
        
    public:
        IMITexturePtr m_pBaseColorTex;
        IMITexturePtr m_pMetallicRoughnessTex;
        IMITexturePtr m_pNormalTex;
        IMITexturePtr m_pOcclusionTex;
        IMITexturePtr m_pEmissiveTex;
        
        FVec4 m_baseColorFactor;
        f32 m_metallicFactor;
        f32 m_roughtnessFactor;
        f32 m_normalScale;
        f32 m_occlusionStrength;
        FVec3 m_emissiveFactor;
    };
    
#define MAX_BONES 30
#define MAX_BONES_DATA 30*16
#define MAX_BONES_DATA_SIZE 30*16*4
    
    class IMIMtlGLTFSkin : public IMIMtlGLTF {
    public:
        IMIMtlGLTFSkin(IMIInstPtr _app);
        
        IMIMtlGLTFSkin(IMIMtlGLTFSkin *_mtl);
        
        ~IMIMtlGLTFSkin();
        
        virtual IMIMtlCorePtr clone();
        
        void update(f32 dt);
        
        void refresh();
        
        void bindSke(IMISkeletonPtr _ske);
        
        void unbindSke();
        
    protected:
        virtual void _submitUniform(IMIRendererPtr _render);
        //
        f32 m_vecBoneMatrix[MAX_BONES_DATA];
        //关联骨架
        IMISkeletonPtr m_pSke;
    };


    
    
}//!namespace imi


#endif //IMI_MTL_GLTF_H

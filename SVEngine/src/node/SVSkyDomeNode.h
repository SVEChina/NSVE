//
// SVSkyDomeNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//
#ifndef SV_SKYDOME_NODE_H
#define SV_SKYDOME_NODE_H

#include "SVNode.h"

namespace sv {
    
    
        
        class SVSkyDomeNode : public SVNode {
        public:
            SVSkyDomeNode(SVInstPtr _app);
            
            virtual ~SVSkyDomeNode();
            
            void generateSkyDome(SVTexturePtr _tex , s32 _horiRes , s32 _vertRes , f32 _texCent , f32 _sphCent , f32 _radius);
            
            void update(f32 _dt);
            
            void render();
            
        private:
            void _generateMesh();
            
            s32         mHorizontalResolution;
            s32         mVerticalResoulution;
            f32         mTexturePercent,mSpherePercent,mRadius;
            SVTexturePtr      mDomeTex;
            SVRenderMeshPtr   mMesh;
            SVRenderObjectPtr m_renderObject;
        };
        
    
    
}//!namespace sv




#endif //SV_SKYDOME_NODE_H

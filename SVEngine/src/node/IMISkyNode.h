//
// IMISkyNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#ifndef IMI_SKYDOME_NODE_H
#define IMI_SKYDOME_NODE_H

#include "IMINode.h"

namespace imi {

    class IMISkyNode : public IMINode {
    public:
        IMISkyNode(IMIInstPtr _app);
        
        virtual ~IMISkyNode();
        
        void generateSkyDome(IMITexturePtr _tex , s32 _horiRes , s32 _vertRes , f32 _texCent , f32 _sphCent , f32 _radius);
        
        void update(f32 _dt);
        
        void render();
        
    private:
        void _generateMesh();
        
        s32         mHorizontalResolution;
        s32         mVerticalResoulution;
        f32         mTexturePercent,mSpherePercent,mRadius;
        IMITexturePtr      mDomeTex;
        IMIRenderMeshPtr   mMesh;
    };

}//!namespace imi




#endif //IMI_SKYDOME_NODE_H

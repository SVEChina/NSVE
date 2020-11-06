//
// IMIBGRAInstreamNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BGRAINSTREAMNODE_H
#define IMI_BGRAINSTREAMNODE_H

#include "IMINode.h"

namespace imi {

    //
    class IMIBGRAInstreamNode : public IMINode {
    public:
        IMIBGRAInstreamNode(IMIInstPtr _app);
        
        IMIBGRAInstreamNode(IMIInstPtr _app,f32 _w,f32 _h);
        
        ~IMIBGRAInstreamNode();
        
        void update(f32 _dt);
        
        void render();
        
        void setSpriteSize(f32 _w,f32 _h);
        
        inline f32 getWidth(){ return m_width; }
        
        inline f32 getHeight(){ return m_height; }
        
        void setTexture(IMITexturePtr _tex);
        
    protected:
        f32 m_width;
        f32 m_height;
        IMIRenderMeshPtr m_pMesh;
        IMITexturePtr m_pTex;
    };

}//!namespace imi


#endif //IMI_SPRITE_H

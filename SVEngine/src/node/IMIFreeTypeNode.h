//
// IMIFreeTypeNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FREETYPENODE_H
#define IMI_FREETYPENODE_H

#include "IMINode.h"

#ifdef CONFIG_IS_LOAD_FREETYPE

namespace imi {

    class IMIFreeTypeNode : public IMINode {
    public:
        IMIFreeTypeNode(IMIInstPtr _app);
        
        virtual ~IMIFreeTypeNode();
        
        virtual void update(f32 dt);
        
        virtual void render();
        
        void setText(cptr8 _text);
        
        cptr8 getText();
        
    private:
        void _updateTextTexture();  //更新文字纹理
        
        s32 m_fontPixelSize;        //字体标准像素尺寸
        s32 m_DefTextPixelSize;
        IMITexturePtr m_texture;
        IMIRenderMeshPtr m_pMesh;    //模型
        bool m_textChange;
        IMIString m_Text;
    };

}//!namespace imi

#endif //CONFIG_IS_LOAD_FREETYPE

#endif //IMI_FREETYPENODE_H

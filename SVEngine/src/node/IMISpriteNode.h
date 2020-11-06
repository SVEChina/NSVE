//
// IMISpriteNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SPRITE_H
#define IMI_SPRITE_H

#include "IMINode.h"

namespace imi {
        
    /*
     精灵节点
     */

    class IMISpriteNode : public IMINode {
    public:
        IMISpriteNode(IMIInstPtr _app);
        
        IMISpriteNode(IMIInstPtr _app,f32 _w,f32 _h);
        
        ~IMISpriteNode();
        
        void update(f32 _dt);
        
        void render();
        
        void setSize(f32 _w,f32 _h);

        f32 getWidth();
        
        f32 getHeight();
        
        virtual void setTexture(cptr8 _path);
        
        virtual void setTexture(IMI_TEXIN _textype);
        
        virtual void setTexture(IMITexturePtr _tex);
        
        IMITexturePtr getTexture();
        
        void syncTexSize();
        
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        f32 m_width;
        f32 m_height;
        IMITexturePtr m_pTex;
        IMIRenderMeshPtr m_pMesh;
    };
    
}//!namespace imi


#endif //IMI_SPRITE_H

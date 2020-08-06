//
// SVSpriteNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SPRITE_H
#define SV_SPRITE_H

#include "SVNode.h"

namespace sv {
        
    /*
     精灵节点
     */

    class SVSpriteNode : public SVNode {
    public:
        SVSpriteNode(SVInstPtr _app);
        
        SVSpriteNode(SVInstPtr _app,f32 _w,f32 _h);
        
        ~SVSpriteNode();
        
        void update(f32 _dt);
        
        void render();
        
        void setSize(f32 _w,f32 _h);

        f32 getWidth();
        
        f32 getHeight();
        
        virtual void setTexture(cptr8 _path);
        
        virtual void setTexture(SVTEXINID _textype);
        
        virtual void setTexture(SVTexturePtr _tex);
        
        SVTexturePtr getTexture();
        
        void syncTexSize();
        
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        f32 m_width;
        f32 m_height;
        SVString m_mtl_name;
        SVTexturePtr m_pTex;
        SVRenderMeshPtr m_pMesh;
    };
    
}//!namespace sv


#endif //SV_SPRITE_H

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
            
            virtual void setSize(f32 _w,f32 _h);
            
            virtual void setTexcoord(f32 x,f32 y);
            
            void syncTexSize();
            
            f32 getRelativeWidth();
            
            f32 getRelativeHeight();
            
            f32 getWidth();
            
            f32 getHeight();
            
            virtual void setMaterial(s32 _id);
            
            s32 getMaterial();
            
            cptr8 getTexturePath();
            
            virtual void setTexture(cptr8 _path, bool enableMipMap = false);
            
            virtual void setTexture(SVTEXINID _textype);
            
            virtual void setTexture(SVTexturePtr _tex);
            
            virtual void setTexture(void * _data, s32 _w, s32 _h, bool enableMipMap = false);
            
            virtual void setMesh(SVRenderMeshPtr _mesh);
            
            //序列化接口
            void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
            
            void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
            
        protected:
            f32 m_width;
            f32 m_height;
            f32 m_texcoordX;
            f32 m_texcoordY;
            SVString m_pTexPath;
            SVTEXINID m_inTexType;
            //运行时属性
            SVTexturePtr m_pTex;
            SVRenderMeshPtr m_pMesh;
            SVRenderObjectPtr m_pRenderObj;
            
        private:
            SVString m_pTexName;
        };
    
}//!namespace sv


#endif //SV_SPRITE_H

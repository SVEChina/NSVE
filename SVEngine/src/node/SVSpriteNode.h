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
    
    namespace node{
        
        /*
         精灵节点
         */
        
        class SVSpriteNode : public SVNode {
        public:
            SVSpriteNode(SVInst *_app);
            
            SVSpriteNode(SVInst *_app,f32 _w,f32 _h);
            
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
            
            virtual void setTexture(SVTEXTYPE _textype);
            
            virtual void setTexture(mtl::SVTexturePtr _tex);
            
            virtual void setTexture(void * _data, s32 _w, s32 _h, bool enableMipMap = false);
            
            virtual void setMesh(render::SVRenderMeshPtr _mesh);
            
            //序列化接口
            void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
            
            void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
            
        protected:
            f32 m_width;
            f32 m_height;
            f32 m_texcoordX;
            f32 m_texcoordY;
            util::SVString m_pTexPath;
            SVTEXTYPE m_inTexType;
            //运行时属性
            mtl::SVTexturePtr m_pTex;
            render::SVRenderMeshPtr m_pMesh;
            render::SVRenderObjectPtr m_pRenderObj;
            
        private:
            util::SVString m_pTexName;
        };

    }//!namespace node
    
}//!namespace sv


#endif //SV_SPRITE_H

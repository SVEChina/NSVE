//
// IMIBillboardNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BILLBOARD_H
#define IMI_BILLBOARD_H

#include "IMISpriteNode.h"

namespace imi {

    class IMIBillboardNode : public IMISpriteNode {
    public:
        IMIBillboardNode(IMIInstPtr _app);
        
        IMIBillboardNode(IMIInstPtr _app,f32 _w,f32 _h);
        
        ~IMIBillboardNode();
        
        void update(f32 _dt);
        
        void render();
        
        void setSize(f32 _w,f32 _h);
        
        void syncTexSize();
        
        void setTexcoord(f32 x,f32 y);
        
        inline f32 getWidth(){ return m_width; }
        
        inline f32 getHeight(){ return m_height; }
        
        cptr8 getTexturePath();
        
        virtual void setTexture(cptr8 _path, bool enableMipMap = false);
        
        virtual void setTexture(IMI_TEXIN _textype);
        
        virtual void setTexture(IMITexturePtr _tex);
        
        void setMesh(IMIRenderMeshPtr _mesh);

        void setViewPos(FVec3 &_pos);
        
        void setUp(FVec3 &_up);
        
        //序列化接口
        void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
        
        void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        f32 m_width;
        f32 m_height;
        f32 m_texcoordX;
        f32 m_texcoordY;
        FVec3 m_viewPos;
        FVec3 m_up;
        IMIString m_pTexPath;
        IMI_TEXIN m_inTexType;
        //运行时属性
        IMITexturePtr m_pTex;
        IMIRenderMeshPtr m_pMesh;
        
    private:
        IMIString m_pTexName;
    };

    
    
}//!namespace imi


#endif //IMI_BILLBOARD_H

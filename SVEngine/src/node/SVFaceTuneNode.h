//
// SVFaceTuneNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FACETUNE_NODE_H
#define SV_FACETUNE_NODE_H

#include "SVNode.h"
namespace sv {

        class SVFaceTuneNode : public SVNode {
        public:
            SVFaceTuneNode(SVInstPtr _app);
            
            ~SVFaceTuneNode();
            
            void update(f32 dt);
            
            void render();
            
            //序列化接口
            void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
            
            void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        protected:
            
            void _addPass(SVPassPtr _pass);
            void _clearPass();
            typedef SVArray<SVPassPtr> PASSPOOL;
            PASSPOOL m_passPool;
            SVRenderMeshPtr m_pFaceMesh;
            SVMtlCorePtr m_maskMtl;
            SVDataSwapPtr m_pIndexs;
            SVDataSwapPtr m_pVerts;
            SVDataSwapPtr m_pT0;
            
            u32 m_meshsize;
            f32 m_tex0width;
            f32 m_tex0height;
        };
}//!namespace sv

#endif //SV_FACETUNE_NODE_H

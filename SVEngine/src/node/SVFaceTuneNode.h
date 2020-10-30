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
            SVRenderMeshPtr m_tuneMesh;
            SVMtlCorePtr m_tuneMtl;
            SVSurfacePtr m_tuneSurface;
            SVRTargetPtr m_faceTuneTarget;
        };
}//!namespace sv

#endif //SV_FACETUNE_NODE_H

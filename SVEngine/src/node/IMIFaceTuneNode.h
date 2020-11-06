//
// IMIFaceTuneNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FACETUNE_NODE_H
#define IMI_FACETUNE_NODE_H

#include "IMINode.h"
namespace imi {

        class IMIFaceTuneNode : public IMINode {
        public:
            IMIFaceTuneNode(IMIInstPtr _app);
            
            ~IMIFaceTuneNode();
            
            void update(f32 dt);
            
            void render();
            
            //序列化接口
            void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
            
            void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        protected:
            IMIRenderMeshPtr m_tuneMesh;
            IMIMtlCorePtr m_tuneMtl;
            IMISurfacePtr m_tuneSurface;
        };
}//!namespace imi

#endif //IMI_FACETUNE_NODE_H

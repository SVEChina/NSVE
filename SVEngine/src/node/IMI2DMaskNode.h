//
// IMI2DMaskNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_2DEYEMASK_NODE_H
#define IMI_2DEYEMASK_NODE_H

#include "IMINode.h"
#define MAX_KEYPOINTS_NUM 400
namespace imi {
enum IMI_E_2DMASK_TYPE{
    IMI_E_2DMASK_NONE = 0,
    IMI_E_2DMASK_FACE,
    IMI_E_2DMASK_EYEBROW,
    IMI_E_2DMASK_EYELASH,
    IMI_E_2DMASK_EYELID
};

enum IMI_E_2DMASK_BLENDMODE{
    IMI_E_2DMASK_BLENDMODE_NONE = 0,
    IMI_E_2DMASK_BLENDMODE_NORMAL,//融合
    IMI_E_2DMASK_BLENDMODE_MULTIPLY,//叠底
    IMI_E_2DMASK_BLENDMODE_SOFTLIGHT,//柔光
    IMI_E_2DMASK_BLENDMODE_SCREEN//滤色
};

class IMI2DMaskNode : public IMINode {
public:
    IMI2DMaskNode(IMIInstPtr _app);
    
    ~IMI2DMaskNode();
    
    void update(f32 dt);
    
    void render();
    
    void setMask(cptr8 _path);
    
    //序列化接口
    void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
    
    void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
protected:
    IMIRenderMeshPtr m_maskMesh;
    IMIMtlCorePtr    m_maskMtl;
    IMISurfacePtr    m_maskSurface;
    IMIRTargetPtr    m_maskTarget;
};

}//!namespace imi


#endif //IMI_2DEYEMASK_NODE_H

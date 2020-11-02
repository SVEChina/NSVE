//
// SV2DMaskNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_2DEYEMASK_NODE_H
#define SV_2DEYEMASK_NODE_H

#include "SVNode.h"
#define MAX_KEYPOINTS_NUM 400
namespace sv {
enum SV_E_2DMASK_TYPE{
    SV_E_2DMASK_NONE = 0,
    SV_E_2DMASK_FACE,
    SV_E_2DMASK_EYEBROW,
    SV_E_2DMASK_EYELASH,
    SV_E_2DMASK_EYELID
};

enum SV_E_2DMASK_BLENDMODE{
    SV_E_2DMASK_BLENDMODE_NONE = 0,
    SV_E_2DMASK_BLENDMODE_NORMAL,//融合
    SV_E_2DMASK_BLENDMODE_MULTIPLY,//叠底
    SV_E_2DMASK_BLENDMODE_SOFTLIGHT,//柔光
    SV_E_2DMASK_BLENDMODE_SCREEN//滤色
};

class SV2DMaskNode : public SVNode {
public:
    SV2DMaskNode(SVInstPtr _app);
    
    ~SV2DMaskNode();
    
    void update(f32 dt);
    
    void render();
    
    void setMask(cptr8 _path);
    
    void setIntensity(f32 _intensity);
    
    void setBlendMode(SV_E_2DMASK_BLENDMODE _mode);
    
    void setMaskType(SV_E_2DMASK_TYPE _type);
    
    SV_E_2DMASK_TYPE getMaskType();
    
    //序列化接口
    void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue);
    
    void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
protected:
    void _addPass(SVPassPtr _pass);
    void _clearPass();
    typedef SVArray<SVPassPtr> PASSPOOL;
    PASSPOOL m_passPool;
    SVString m_texName;
    SVDataSwapPtr m_pIndexs;
    SVDataSwapPtr m_pVerts;
    SVDataSwapPtr m_pT0;
    SVDataSwapPtr m_pT1;
    SVDataSwapPtr m_pC;
    SVMtlMaskPtr m_maskMtl;
    SVTexturePtr m_maskTex;
    SVTexturePtr m_help0Tex;
    SVTexturePtr m_mainTex;
    SVPassPtr    m_maskPass;
    SV_E_2DMASK_TYPE m_maskType;
    SV_E_2DMASK_BLENDMODE m_blendMode;
    u32 m_meshsize;
    f32 m_tex0width;
    f32 m_tex0height;
    f32 m_tex1width;
    f32 m_tex1height;
    f32 m_intensity;
};

}//!namespace sv


#endif //SV_2DEYEMASK_NODE_H

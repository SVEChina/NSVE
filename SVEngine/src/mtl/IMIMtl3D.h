//
// IMIMtl3D.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MTL_3D_H
#define IMI_MTL_3D_H


#include "IMIMtlCore.h"

//3D材质
namespace imi {
    
    class IMIMtl3D : public IMIMtlCore {
    public:
        IMIMtl3D(IMIInstPtr _app, cptr8 _shader);
        
        IMIMtl3D(IMIMtl3D *_mtl);
        
        ~IMIMtl3D();
        
        virtual void reset();
        
        virtual IMIMtlCorePtr clone();
        
        void setAmbientLightIntensit(f32 _intersit);
        
        void setAmbientLightColorFactor(FVec3& _ambientColor);
        
        f32 getAmbientLightStrength();
        
        FVec3& getAmbientLightColor();
        
        void setLightPositon(FVec3& _lightPos);
        
        void setLightColor(FVec3& _lightColor);
        
        FVec3& getLightColor();
        
        FVec3& getLightPos();
        
    protected:
        void _submitMtl(IMIRendererPtr _render);
        f32   m_ambientStrength;
        FVec3 m_ambient_color;
        FVec3 m_lightPos;
        FVec3 m_lightColor;
        
    public:
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
    };

}//!namespace imi


#endif //IMI_MTL_3D_H

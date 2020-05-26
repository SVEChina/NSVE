//
// SVStaticData.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_STATICDATA_H
#define SV_STATICDATA_H

//基础渲染数据接口 包含很多 基本的数据

#include "../rendercore/SVRenderDef.h"
#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVMap.h"
#include "../base/SVVec3.h"
#include "../core/SVVertDef.h"
namespace sv {

    class SVStaticData : public SVGBase {
    public:
        SVStaticData(SVInst* _app);
        
        ~SVStaticData();
        
        void init();
        
        void destroy();
        
        SVFaceDataMeshPtr getFaceDataMesh();
        
        render::SVRenderMeshPtr generateAdaptScreenMesh(f32 _fromW, f32 _fromH, f32 _toW, f32 _toH);
        
        render::SVRenderMeshPtr generatePatchMesh(util::FVec3 &_corner00, util::FVec3 &_corner10, util::FVec3 &_corner01, util::FVec3 &_corner11, s32 _rx = 2, s32 _ry = 2);
    public:
        render::SVRenderMeshPtr m_screenMesh;
        render::SVRenderMeshPtr m_screenMeshRot90;
        render::SVRenderMeshPtr m_screenMeshRot180;
        render::SVRenderMeshPtr m_screenMeshRot270;
        render::SVRenderMeshPtr m_screenLTMesh;
        render::SVRenderMeshPtr m_screenLBMesh;
        render::SVRenderMeshPtr m_screenRTMesh;
        render::SVRenderMeshPtr m_screenRBMesh;
        render::SVRenderMeshPtr m_screenTwoDivisionMesh;
        render::SVRenderMeshPtr m_screenFourDivisionMesh;
        render::SVRenderMeshPtr m_screenFourXDivisionMesh;
        static V3_C_T0 m_baseRect[6];
    protected:
        void _initBaseRect();
        
        void _initTwoDivisionMesh();
        
        void _initFourDivisionMesh();
        
        void _initFourDivisionMesh_X();
    protected:
        SVFaceDataMeshPtr m_faceDataMesh;
        render::SVRenderMeshPtr   m_screenAdaptMesh;
    };
    
}//!namespace
#endif //SV_RENDERDATA_H

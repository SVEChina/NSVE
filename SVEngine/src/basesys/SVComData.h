//
// SVComData.h

// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_COMDATA_H
#define SV_COMDATA_H

//基础渲染数据接口 包含很多 基本的数据

#include "../rendercore/SVRenderDeclare.h"
#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVMap.h"
#include "../base/SVVec3.h"
#include "../core/SVVertDef.h"

namespace sv {

    class SVComData: public SVGBaseEx {
    public:
        SVComData(SVInstPtr _app);
        
        ~SVComData();
        
        void init();
        
        void destroy();
        
        SVFaceDataMeshPtr getFaceDataMesh();
        
        SVRenderMeshPtr generateAdaptScreenMesh(f32 _fromW, f32 _fromH, f32 _toW, f32 _toH);
        
        SVRenderMeshPtr generatePatchMesh(FVec3 &_corner00, FVec3 &_corner10, FVec3 &_corner01, FVec3 &_corner11, s32 _rx = 2, s32 _ry = 2);
        
        SVRenderMeshPtr m_screenMesh;
        
    protected:

        void _initTwoDivisionMesh();
        
        void _initFourDivisionMesh();
        
        void _initFourDivisionMesh_X();
        
    public:
        SVFaceDataMeshPtr m_faceDataMesh;
        SVRenderMeshPtr   m_screenAdaptMesh;
    };
    
}//!namespace

#endif //SV_COMDATA_H

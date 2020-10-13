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
#include "../event/SVEventProc.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVMap.h"
#include "../base/SVVec3.h"
#include "../core/SVVertDef.h"

namespace sv {

    class SVComData: public SVEventProc {
    public:
        SVComData(SVInstPtr _app);
        
        ~SVComData();
        
        void init();
        
        void destroy();
        
        bool procEvent(SVEventPtr _event);
        
        //动态初始化
        SVFaceDataMeshPtr faceMesh(s32 _type);
        
        //引擎创建初始化
        SVRenderMeshPtr screenMesh() { return m_screenMesh; }
        
        SVRenderMeshPtr generatePatchMesh(FVec3 &_corner00,
                                          FVec3 &_corner10,
                                          FVec3 &_corner01,
                                          FVec3 &_corner11,
                                          s32 _rx = 2,
                                          s32 _ry = 2);
        
    protected:
        void _initTwoDivisionMesh();
        
        void _initFourDivisionMesh();
        
        void _initFourDivisionMesh_X();
        
        SVRenderMeshPtr m_screenMesh;
    };
    
}//!namespace

#endif //SV_COMDATA_H

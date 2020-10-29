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

    enum SV_E_FACEMESH_TYPE{
        SV_E_FACEMESH_SIMPILITY = 0,//基础人脸mesh
        SV_E_FACEMESH_HEAD,//带额头的人脸mesh
        SV_E_FACEMESH_WHOLE,//带额头补过嘴的人脸mesh
        SV_E_FACEMESH_EYE,//眼睛部位的mesh
        SV_E_FACEMESH_BROW,//眉毛部位的mesh
        SV_E_FACEMESH_TUNE//面部微整形的mesh
    };

    class SVComData: public SVEventProc {
    public:
        SVComData(SVInstPtr _app);
        
        ~SVComData();
        
        void init();
        
        void destroy();
        
        void loadDefault();
        
        //动态初始化
        SVRenderMeshPtr faceMesh(SV_E_FACEMESH_TYPE _meshType);
        
        //引擎创建初始化
        SVRenderMeshPtr screenMesh() { return m_screenMesh; }
        
    protected:
        SVRenderMeshPtr m_screenMesh;
        
        SVRenderMeshPtr m_faceMesh;
        
    public:
        //标准图片的宽高
        static s32 m_standard_imgw_st;
        static s32 m_standard_imgh_st;
        static s32 m_standard_imgw_fp;
        static s32 m_standard_imgh_fp;
        static s32 m_standard_imgw_as;
        static s32 m_standard_imgh_as;
        
        static SVRenderMeshPtr createFaceMeshSt(SVInstPtr _app, SV_E_FACEMESH_TYPE _meshType);
        
        static SVRenderMeshPtr createFaceMeshFp(SVInstPtr _app,bool _simp = true);
        
        static SVRenderMeshPtr createFaceMeshAS(SVInstPtr _app,bool _simp = true);
        
    protected:
        static SVRenderMeshPtr _loadFaceMesh(SVInstPtr _app,
                                             cptr8 _indexfile,
                                             cptr8 _datafile,
                                             s32 _type);
    };
    
}//!namespace

#endif //SV_COMDATA_H

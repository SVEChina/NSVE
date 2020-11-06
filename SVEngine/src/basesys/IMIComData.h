//
// IMIComData.h

// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_COMDATA_H
#define IMI_COMDATA_H

//基础渲染数据接口 包含很多 基本的数据

#include "../rendercore/IMIRenderDeclare.h"
#include "../event/IMIEventProc.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIMap.h"
#include "../base/IMIVec3.h"
#include "../core/IMIVertDef.h"

namespace imi {

    enum IMI_E_FACEMESH_TYPE{
        IMI_E_FACEMESH_SIMPILITY = 0,//基础人脸mesh
        IMI_E_FACEMESH_HEAD,//带额头的人脸mesh
        IMI_E_FACEMESH_WHOLE,//带额头补过嘴的人脸mesh
        IMI_E_FACEMESH_EYE,//眼睛部位的mesh
        IMI_E_FACEMESH_BROW,//眉毛部位的mesh
        IMI_E_FACEMESH_TUNE//面部微整形的mesh
    };

    class IMIComData: public IMIEventProc {
    public:
        IMIComData(IMIInstPtr _app);
        
        ~IMIComData();
        
        void init();
        
        void destroy();
        
        void loadDefault();
        
        //动态初始化
        IMIRenderMeshPtr faceMesh(IMI_E_FACEMESH_TYPE _meshType);
        
        //引擎创建初始化
        IMIRenderMeshPtr screenMesh() { return m_screenMesh; }
        
    protected:
        IMIRenderMeshPtr m_screenMesh;
        
        IMIRenderMeshPtr m_faceMesh;
        
    public:
        //标准图片的宽高
        static s32 m_standard_imgw_st;
        static s32 m_standard_imgh_st;
        static s32 m_standard_imgw_fp;
        static s32 m_standard_imgh_fp;
        static s32 m_standard_imgw_as;
        static s32 m_standard_imgh_as;
        
        static IMIRenderMeshPtr createFaceMeshSt(IMIInstPtr _app, IMI_E_FACEMESH_TYPE _meshType);
        
        static IMIRenderMeshPtr createFaceMeshFp(IMIInstPtr _app,bool _simp = true);
        
        static IMIRenderMeshPtr createFaceMeshAS(IMIInstPtr _app,bool _simp = true);
        
    protected:
        static IMIRenderMeshPtr _loadFaceMesh(IMIInstPtr _app,
                                             cptr8 _indexfile,
                                             cptr8 _datafile,
                                             s32 _type);
    };
    
}//!namespace

#endif //IMI_COMDATA_H

//
// IMIMesh3d.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MESH3D_H
#define IMI_MESH3D_H

#include "IMIVertDef.h"
#include "../base/IMIGBase.h"
#include "../base/IMIPreDeclare.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../base/IMIDataChunk.h"
#include "../base/IMIMap.h"
#include "../base/IMIMat4.h"
#include "../base/IMIBounds.h"

namespace imi {
    
    //普通mesh
    class IMIMesh3d :public IMIGBaseEx {
    public:
        IMIMesh3d(IMIInstPtr _app);
        
        ~IMIMesh3d();
        
        void setName(cptr8 _name);
        
        cptr8 getName();
        
        void setRenderMesh(IMIRenderMeshPtr _mesh);
        
        IMIRenderMeshPtr getRenderMesh();
        
        void setMtl(IMIMtlCorePtr _mtl);
        
        IMIMtlCorePtr getMtl();
        
        void setSurface(IMISurfacePtr _surface);
        
        IMISurfacePtr getSurface();
        
        void setData(IMIDataSwapPtr _data,VFTYPE _vtf,s32 _count,s32 _seqMode);

        void update(f32 _dt,FMat4& _mat);
        
        void render();
        
        void setBox(IMIBoundBox& _box);
        
        IMIBoundBox getBox();
        
        void setMatrix(FMat4& _mat);
        
        void setBoneMatrix(IMIArray<FMat4> &_mats);
    protected:
        IMIString m_name;
        IMIBoundBox m_box;
        IMIRenderMeshPtr m_rendermesh;
        IMIMtlCorePtr m_mtl;
        IMISurfacePtr m_surface;
        FMat4 m_absoluteMat;    //渲染的绝对矩阵
        IMIArray<FMat4> m_boneMatrixs;
    };

}//!namespace imi

#endif //IMI_MESH3D_H

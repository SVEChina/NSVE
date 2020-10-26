//
// SVMesh3d.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_MESH3D_H
#define SV_MESH3D_H

#include "SVVertDef.h"
#include "../base/SVGBase.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../base/SVDataChunk.h"
#include "../base/SVMap.h"
#include "../base/SVMat4.h"
#include "../base/SVBounds.h"

namespace sv {
    
    //普通mesh
    class SVMesh3d :public SVGBaseEx {
    public:
        SVMesh3d(SVInstPtr _app);
        
        ~SVMesh3d();
        
        void setName(cptr8 _name);
        
        cptr8 getName();
        
        void setRenderMesh(SVRenderMeshPtr _mesh);
        
        SVRenderMeshPtr getRenderMesh();
        
        void setMtl(SVMtlCorePtr _mtl);
        
        SVMtlCorePtr getMtl();
        
        SVSurfacePtr getSurface();
        
        void setData(SVDataSwapPtr _data,VFTYPE _vtf,s32 _count,s32 _seqMode);

        void update(f32 _dt,FMat4& _mat);
        
        void render();
        
        void setBox(SVBoundBox& _box);
        
        SVBoundBox getBox();
        
        void setMatrix(FMat4& _mat);
        
    protected:
        SVString m_name;
        SVBoundBox m_box;
        SVRenderMeshPtr m_rendermesh;
        SVMtlCorePtr m_mtl;
        SVSurfacePtr m_surface;
        FMat4 m_absoluteMat;    //渲染的绝对矩阵
    };

}//!namespace sv

#endif //SV_MESH3D_H

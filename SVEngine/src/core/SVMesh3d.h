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
        
        void setData(SVDataSwapPtr _data,VFTYPE _vtf,s32 _count,s32 _seqMode);
        
        SVRenderMeshPtr getRenderMesh();
        
        void update(f32 _dt,FMat4& _mat);
        
        void render();
        
        void setBox(SVBoundBox& _box);
        
        SVBoundBox getBox();
        
    protected:
        SVString m_name;
        SVBoundBox m_box;
        SVRenderMeshPtr m_rendermesh;
    };

}//!namespace sv

#endif //SV_MESH3D_H

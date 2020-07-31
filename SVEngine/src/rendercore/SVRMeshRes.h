//
// SVRMeshRes.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_RES_h
#define SV_RMESH_RES_h

#include "SVRRes.h"
#include "../base/SVPreDeclare.h"
#include "../core/SVVertDef.h"

namespace sv {
        
    //1.AOS模式  混合流
    //2.SOA模式  拆分流

    class SVRMeshRes: public SVRRes{
    public:
        static int getVertexFormateSize(VFTYPE _type);
        
        SVRMeshRes(SVInstPtr _app);
        
        virtual ~SVRMeshRes();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual s32 process(SVRendererPtr _renderer);
        
        virtual void draw(SVRendererPtr _renderer);
        
    };
        
}//!namespace sv


#endif /* SV_RMESH_RES_h */

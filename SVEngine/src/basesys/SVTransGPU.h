//
// SVTransGPU.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TRANS_GPU_H
#define SV_TRANS_GPU_H

#include "SVTrans.h"
#include "../mtl/SVMtlDef.h"
#include "../node/SVNodeDeclare.h"

namespace sv {

    namespace logic {
        
        class SVTransGPU : public SVTrans {
        public:
            SVTransGPU(SVInst *_app,
                       mtl::SVTexturePtr _t0,
                       mtl::SVTexturePtr _t1,
                       mtl::SVTexturePtr _t2,
                       mtl::SVTexturePtr _tOut);
            
            virtual ~SVTransGPU();
            
            void init(s32 _w, s32 _h,f32 _angle,PICFORMATE _formate,SVTEXTYPE _tt);
            
            void destroy();
            
            void update(f32 dt);
            
            void render();
            
            void setAngle(f32 _angle);
            
        protected:
            mtl::SVTexturePtr m_tex0;
            mtl::SVTexturePtr m_tex1;
            mtl::SVTexturePtr m_tex2;
            mtl::SVTexturePtr m_texOut;
            f32 m_angle;
            node::SVMultPassNodePtr m_passNode;
            render::SVRenderObjectPtr m_pRenderObj;
            render::SVRenderMeshPtr m_pMesh;
            mtl::SVMtlCorePtr m_pMtl;

            void createPass(s32 _w, s32 _h, f32 _angle, SVTEXTYPE _tt);
        };
        
    }
    
}//!namespace sv

#endif //SV_TRANS_GPU_H

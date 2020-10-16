//
// SVRMeshMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_METAL_H
#define SV_RMESH_METAL_H

#include "../SVRMeshRes.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render mesh metal
     */

    class SVRMeshMetal : public SVRMeshRes {
    public:
        SVRMeshMetal(SVInstPtr _app);
        
        ~SVRMeshMetal();
        
        void create(SVRendererPtr _renderer,
                    SVIndexStreamDspPtr _indexdsp,
                    SVVertStreamDspPtr _streamdsp,
                    SVInstStreamDspPtr _instdsp,
                    SVRMeshDsp* _SVRMeshDsp);

        void destroy(SVRendererPtr _renderer);

        s32 process(SVRendererPtr _renderer);

        void draw(SVRendererPtr _renderer);
        
    public:
        id<MTLBuffer> m_ibuf;
        id<MTLBuffer> m_instance_buf;
        SVArray<id<MTLBuffer>> m_dbufs;
        //
        s32 m_vertStart;
        s32 m_vertCnt;
        s32 m_iCnt;
        s32 m_ibufOff;
        s32 m_instCnt;
        s32 m_streanNum;
        BUFFERMODE m_bufmode;
    };
    

}//!namespace sv


#endif //SV_RMESH_METAL_H

//
// SVRBufferMetal.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RMESH_METAL_H
#define SV_RMESH_METAL_H

#include "../SVRBuffer.h"
#include "SVRenderDef.h"
#include "../mtl/SVShaderMgr.h"
#include "../base/SVPreDeclare.h"
#import <Metal/Metal.h>

namespace sv {

    /*
     render mesh metal
     */

    class SVRBufferMetal : public SVRBuffer {
    public:
        SVRBufferMetal(SVInstPtr _app);
        
        ~SVRBufferMetal();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        void render(SVRendererPtr _renderer,SVRTargetPtr _target,SVRenderMeshPtr _rmesh);
        
        void destroy(SVRendererPtr _renderer,SVRTargetPtr _target);
        
        id<MTLBuffer> m_ibuf;
        id<MTLBuffer> m_instance_buf;
        SVArray<id<MTLBuffer>> m_dbufs;
        s32 m_vertStart;
        s32 m_vertCnt;
        s32 m_iCnt;
        s32 m_ibufOff;
        s32 m_instCnt;
        s32 m_streanNum;
        //
        MTLVertexDescriptor* m_vert_dsp;
        BUFFERMODE m_bufmode;
    };
    

}//!namespace sv


#endif //SV_RMESH_METAL_H

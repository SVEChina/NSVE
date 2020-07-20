//
// SVRBuffer.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RESVBO_h
#define SV_RESVBO_h

#include "SVRRes.h"
#include "../base/SVPreDeclare.h"
#include "../core/SVVertDef.h"

namespace sv {
        
    //1.AOS模式  混合流
    //2.SOA模式  拆分流

    class SVRBuffer: public SVRRes{
    public:
        static int getVertexFormateSize(VFTYPE _type);
        
        SVRBuffer(SVInstPtr _app);
        
        virtual ~SVRBuffer();
        
        virtual void create(SVRendererPtr _renderer);
        
        virtual void destroy(SVRendererPtr _renderer);
        
        virtual s32 process(SVRendererPtr _renderer);
        
    protected:
        
    };
        
    
}//!namespace sv


#endif /* SV_RESVBO_h */

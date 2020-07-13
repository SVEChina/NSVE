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

    //
    struct RENDERMESHDATA{
        u32 indexNum;    //索引数量
        u32 pointNum;    //顶点数量
        u32 instanceCount; //多实例数量
        SVDataSwapPtr pDataIndex;
        SVDataSwapPtr pDataVertex;
        //did数据
        SVDataSwapPtr pDataV2;
        SVDataSwapPtr pDataV3;
        SVDataSwapPtr pDataC0;
        SVDataSwapPtr pDataC1;
        SVDataSwapPtr pDataT0;
        SVDataSwapPtr pDataT1;
        SVDataSwapPtr pDataT2;
        SVDataSwapPtr pDataNor;
        SVDataSwapPtr pDataTag;
        SVDataSwapPtr pDataBTor;
        SVDataSwapPtr pDataInsOffset;
        bool dirty;
    };
        
    //
    struct RENDERMESHCONF{
        VFTYPE vftype;
        u32 vertPoolType;
        u32 indexPoolType;
        s32 seqMode;
        DRAWMETHOD drawmethod;
        bool bVisible;
        bool dirty;
    };
        
    //
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

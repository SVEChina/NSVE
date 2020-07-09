//
// SVPenPackData.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PENPACKDATA_H
#define SV_PENPACKDATA_H

#include "../../base/SVGBase.h"
namespace sv{
    
    class SVPenPackData : public SVGBaseEx {
    public:
        SVPenPackData(SVInstPtr _app);
        
        ~SVPenPackData();
        
        static bool writePenData(SVInstPtr _app, SVDataSwapPtr _data, cptr8 _path, bool _clearData = true);
        
        static bool loadPenData(SVInstPtr _app, SVDataSwapPtr _data, cptr8 _path, s32 _offset, s32 _length);
        
        static u64 checkPenStrokeDataLength(SVInstPtr _app, cptr8 _path);
        
    };
    
}//!namespace sv

#endif //SV_PENPACKDATA_H

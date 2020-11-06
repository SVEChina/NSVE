//
// IMIGlobalParam.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_GLOBALPARAM_H
#define IMI_GLOBALPARAM_H

#include "../base/IMIGBase.h"
#include "../base/IMIMat4d.h"
#include "../base/IMIVec4.h"
#include "../base/IMIRandom.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../node/IMINodeDeclare.h"

namespace imi {

    class IMIGlobalParam: public IMIObject {
    public:
        IMIGlobalParam();
        
        ~IMIGlobalParam();
        
        void clear();
        
        void setSeed(u32 seed);
        
        u32 getSeed() const;
        
        u32 getRandom();
        
        s32 getRandomInt(s32 from,s32 to);
        
        f32 getRandomFloat(f32 from,f32 to);
        
        f64 getRandomDouble(f64 from,f64 to) ;
        
        //内部宽高
        s32 sv_width;
        
        s32 sv_height;
        
        //UI矩阵
        IMIRandom m_random;
    };


}//!namespace imi




#endif //IMI_GLOBALPARAM_H

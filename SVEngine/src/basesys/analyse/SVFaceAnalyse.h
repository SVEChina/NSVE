//
// SVFaceAnalyse.h

// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_FACEANALYSE_H
#define SV_FACEANALYSE_H

//基础渲染数据接口 包含很多 基本的数据

#include "../rendercore/SVRenderDeclare.h"
#include "../event/SVEventProc.h"
#include "../base/SVPreDeclare.h"
#include "../base/SVObject.h"
#include "../base/SVMap.h"
#include "../base/SVVec3.h"
#include "../core/SVVertDef.h"

namespace sv {

    /*
        人脸分析
     */

    class SVFaceAnalyse: public SVObject {
    public:
        SVFaceAnalyse();
        
        ~SVFaceAnalyse();
        
    };
    
}//!namespace

#endif //SV_FACEANALYSE_H

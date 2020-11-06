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
#include "../base/SVVec2.h"
#include "../core/SVVertDef.h"

namespace sv {

    /*
        人脸分析
     */
    
enum  FACETYPE{
    
};

enum  EYEBOWTYPE{
    
};

enum  NOISETYPE{
    
};

enum  MOUTHTYPE{
    
};

class SVFaceAnalyse: public SVObject {
public:    
    //分析人脸
    static s32 analyseFace(SVInstPtr _inst,std::vector<FVec2>& points);
    
    //分析眼眉
    static s32 analyseEyebow(SVInstPtr _inst,std::vector<FVec2>& points);
    
    //分析眼睛
    static s32 analyseEye(SVInstPtr _inst,std::vector<FVec2>& points);
    
    //分析鼻子
    static s32 analyseNoise(SVInstPtr _inst,std::vector<FVec2>& points);
    
};
    
}//!namespace

#endif //SV_FACEANALYSE_H

//
// IMIFaceAnalyse.h

// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FACEANALYSE_H
#define IMI_FACEANALYSE_H

//基础渲染数据接口 包含很多 基本的数据

#include "../rendercore/IMIRenderDeclare.h"
#include "../event/IMIEventProc.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIObject.h"
#include "../base/IMIMap.h"
#include "../base/IMIVec3.h"
#include "../base/IMIVec2.h"
#include "../core/IMIVertDef.h"

namespace imi {

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

class IMIFaceAnalyse: public IMIObject {
public:    
    //分析人脸
    static s32 analyseFace(IMIInstPtr _inst,std::vector<FVec2>& points);
    
    //分析眼眉
    static s32 analyseEyebow(IMIInstPtr _inst,std::vector<FVec2>& points);
    
    //分析眼睛
    static s32 analyseEye(IMIInstPtr _inst,std::vector<FVec2>& points);
    
    //分析鼻子
    static s32 analyseNoise(IMIInstPtr _inst,std::vector<FVec2>& points);
    
};
    
}//!namespace

#endif //IMI_FACEANALYSE_H

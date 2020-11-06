//
// IMIRenderDeclare.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_RENDECLARE_H
#define IMI_RENDECLARE_H

#include "../base/IMIDef.h"
#include "../base/IMIPreDeclare.h"
#include "IMIRenderDef.h"

namespace imi {
    
    DECLARE_SHAREPTR(IMIRTargetMgr);

    //渲染资源
    DECLARE_SHAREPTR(IMIRRes);
    DECLARE_SHAREPTR(IMIRTex);
    DECLARE_SHAREPTR(IMIRFbo);
    DECLARE_SHAREPTR(IMIRMeshRes);
    DECLARE_SHAREPTR(IMIRShader);
    
    //渲染框架
    DECLARE_SHAREPTR(IMIRenderer);
    DECLARE_SHAREPTR(IMIRTarget);
    DECLARE_SHAREPTR(IMIRenderStream);
    DECLARE_SHAREPTR(IMIRenderMesh);

    //GL
    DECLARE_SHAREPTR(IMIRendererGL);
    DECLARE_SHAREPTR(IMIRFboGL);
    DECLARE_SHAREPTR(IMIRMeshGL);
    DECLARE_SHAREPTR(IMIRTexGL);
    DECLARE_SHAREPTR(IMIRShaderGL);

    //metal
#if defined(IMI_IOS) || defined(IMI_OSX)
    DECLARE_SHAREPTR(IMIRendererMetal);
    DECLARE_SHAREPTR(IMIRFboMetal);
    DECLARE_SHAREPTR(IMIRMeshMetal);
    DECLARE_SHAREPTR(IMIRTexMetal);
    DECLARE_SHAREPTR(IMIRShaderMetal);
#endif

    //vulkan
    DECLARE_SHAREPTR(IMIRendererVK);
    
    //rendercmd
    DECLARE_SHAREPTR(IMIRenderCmd);
    DECLARE_SHAREPTR(IMIRCmdTransGPU);
    DECLARE_SHAREPTR(IMIRCmdLine);
    DECLARE_SHAREPTR(IMIRCmdAABB);
    DECLARE_SHAREPTR(IMIRCmdNor);
    DECLARE_SHAREPTR(IMIRCmdPass);
    DECLARE_SHAREPTR(IMIRCmdTargetResize);
    DECLARE_SHAREPTR(IMIRCmdAdapt);
    DECLARE_SHAREPTR(IMIRCmdCreate);
    DECLARE_SHAREPTR(IMIRenderCmdGeo);
    DECLARE_SHAREPTR(IMIRCmdLine);
    DECLARE_SHAREPTR(IMIRCmdRect);
    DECLARE_SHAREPTR(IMIRCmdRectSolid);
    DECLARE_SHAREPTR(IMIRCmdCurve);
    DECLARE_SHAREPTR(IMIRCmdCircle);
    DECLARE_SHAREPTR(IMIRCmdCircleSolid);
    //
    DECLARE_SHAREPTR(IMIRCmdCreateMesh);
    DECLARE_SHAREPTR(IMIRCmdCreateShader);
    DECLARE_SHAREPTR(IMIRCmdCreateTex);
    DECLARE_SHAREPTR(IMIRCmdCreateTarget);


}//!namespace imi

#endif //IMI_RENDECLARE_H

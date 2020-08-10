//
// SVRenderDeclare.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_RENDECLARE_H
#define SV_RENDECLARE_H

#include "../base/SVDef.h"
#include "../base/SVPreDeclare.h"
#include "SVRenderDef.h"

namespace sv {
    
    //渲染资源
    DECLARE_SHAREPTR(SVRRes);
    DECLARE_SHAREPTR(SVRTex);
    DECLARE_SHAREPTR(SVRFbo);
    DECLARE_SHAREPTR(SVRMeshRes);
    DECLARE_SHAREPTR(SVRShader);
    DECLARE_SHAREPTR(SVRDPState);

    //渲染器
    DECLARE_SHAREPTR(SVRenderer);
    DECLARE_SHAREPTR(SVRenderState);
    DECLARE_SHAREPTR(SVRenderTexture);
    DECLARE_SHAREPTR(SVRTech);

    //gl
    DECLARE_SHAREPTR(SVRendererGL);
    DECLARE_SHAREPTR(SVRTechGL);
    DECLARE_SHAREPTR(SVRFboGL);
    DECLARE_SHAREPTR(SVRMeshGL);
    DECLARE_SHAREPTR(SVRenderStateGL);
    DECLARE_SHAREPTR(SVRTexGL);
    DECLARE_SHAREPTR(SVRShaderGL);
    DECLARE_SHAREPTR(SVResGLRenderTarget);
    DECLARE_SHAREPTR(SVResGLRenderTargetOut);
    DECLARE_SHAREPTR(SVResGLRenderTexture);
    DECLARE_SHAREPTR(SVResGLRenderMesh);
    DECLARE_SHAREPTR(SVResGLRenderMeshData);
    
    
    //metal
    #if defined(SV_IOS) || defined(SV_OSX)

    DECLARE_SHAREPTR(SVRendererMetal);
    DECLARE_SHAREPTR(SVRFboMetal);
    DECLARE_SHAREPTR(SVRMeshMetal);
    DECLARE_SHAREPTR(SVRTexMetal);
    DECLARE_SHAREPTR(SVRShaderMetal);

    #endif

    //vulkan
    DECLARE_SHAREPTR(SVRendererVK);
    
    //渲染框架
    DECLARE_SHAREPTR(SVFboObject);
    DECLARE_SHAREPTR(SVRTarget);
    DECLARE_SHAREPTR(SVRenderScene);
    DECLARE_SHAREPTR(SVRenderPipline);
    DECLARE_SHAREPTR(SVRenderStream);
    DECLARE_SHAREPTR(SVRenderMesh);
    
    //rendercmd
    DECLARE_SHAREPTR(SVRenderCmd);
    DECLARE_SHAREPTR(SVRCmdTransGPU);
    DECLARE_SHAREPTR(SVRCmdLine);
    DECLARE_SHAREPTR(SVRCmdAABB);
    DECLARE_SHAREPTR(SVRCmdNor);
    DECLARE_SHAREPTR(SVRCmdPass);
    DECLARE_SHAREPTR(SVRCmdPassCollection);
    DECLARE_SHAREPTR(SVRCmdTargetResize);
    DECLARE_SHAREPTR(SVRCmdAdapt);
    DECLARE_SHAREPTR(SVRenderCmdStreamOutNor);
    DECLARE_SHAREPTR(SVRenderCmdStreamOutIOS);
    DECLARE_SHAREPTR(SVRCmdCreate);
    DECLARE_SHAREPTR(SVRenderCmdGeo);
    DECLARE_SHAREPTR(SVRCmdLine);
    DECLARE_SHAREPTR(SVRCmdRect);
    DECLARE_SHAREPTR(SVRCmdRectSolid);
    DECLARE_SHAREPTR(SVRCmdCurve);
    DECLARE_SHAREPTR(SVRCmdCircle);
    DECLARE_SHAREPTR(SVRCmdCircleSolid);
    //
    DECLARE_SHAREPTR(SVRCmdCreateMesh);
    DECLARE_SHAREPTR(SVRCmdCreateShader);
    DECLARE_SHAREPTR(SVRCmdCreateTex);
    DECLARE_SHAREPTR(SVRCmdCreateTarget);

    //renderobject
    DECLARE_SHAREPTR(SVRRes);
    DECLARE_SHAREPTR(SVRenderObject);


}//!namespace sv

#endif //SV_RENDECLARE_H

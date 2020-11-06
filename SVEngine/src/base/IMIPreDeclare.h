//
// IMIPreDeclare.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PREDECLARE_H
#define IMI_PREDECLARE_H

#include "../base/IMICompileConfig.h"
#include <memory>

//定义shareptr宏

#define DECLARE_SHAREPTR(classname) \
class classname;\
typedef std::shared_ptr<classname> classname##Ptr;\

//#define DECLARE_SHAREPTR_TEMP(classname,T1,T2) \
//class classname<T1,T2>;\
//typedef std::shared_ptr<classname<T1,T2>> classname##TempPtr;\

namespace imi {

    DECLARE_SHAREPTR(IMIObject);
    DECLARE_SHAREPTR(IMIGBaseEx);
    DECLARE_SHAREPTR(IMIDataChunk);
    DECLARE_SHAREPTR(IMIParamTbl);

    //MainApp
    DECLARE_SHAREPTR(IMIInst);
    DECLARE_SHAREPTR(IMIGlobalMgr);
    
    //模块module
    DECLARE_SHAREPTR(IMIFileMgr);
    DECLARE_SHAREPTR(IMIConfig);
    DECLARE_SHAREPTR(IMIComData);
    
    //渲染路径
    DECLARE_SHAREPTR(IMIRenderPath);

    //基础
    DECLARE_SHAREPTR(IMIRandom);
    DECLARE_SHAREPTR(IMIDataSwap);
    DECLARE_SHAREPTR(IMIModify);
    DECLARE_SHAREPTR(IMILock);

    //
    DECLARE_SHAREPTR(IMIVertStreamDsp);
    DECLARE_SHAREPTR(IMIIndexStreamDsp);
    DECLARE_SHAREPTR(IMIInstStreamDsp);

    //sysbase - event
    DECLARE_SHAREPTR(IMIEventProc);
    DECLARE_SHAREPTR(IMISysBase);
    DECLARE_SHAREPTR(IMIBasicSys);
    DECLARE_SHAREPTR(IMIDetectMgr);
    DECLARE_SHAREPTR(IMIEventMgr);
    DECLARE_SHAREPTR(IMIRenderMgr);
    DECLARE_SHAREPTR(IMIShader);
    DECLARE_SHAREPTR(IMIShaderMgr);
    DECLARE_SHAREPTR(IMIResMgr);
    DECLARE_SHAREPTR(IMISceneMgr);
    DECLARE_SHAREPTR(IMIARBackgroundMgr);
    DECLARE_SHAREPTR(IMIDeformMgr);
    DECLARE_SHAREPTR(IMICameraMgr);
    DECLARE_SHAREPTR(IMITexMgr);
    DECLARE_SHAREPTR(IMILightSys);
    DECLARE_SHAREPTR(IMILuaSys);
    DECLARE_SHAREPTR(IMIModelMgr);
    DECLARE_SHAREPTR(IMIPhysicsWorldMgr);

    //ani
    DECLARE_SHAREPTR(IMIAniMgr);
    DECLARE_SHAREPTR(IMIAniUnit);
    DECLARE_SHAREPTR(IMIAniUnitRot);

    //模块
    DECLARE_SHAREPTR(IMIModuleBase);
    DECLARE_SHAREPTR(IMIModuleSys);

    //静态类......
    DECLARE_SHAREPTR(IMIGeoGen);

    //操作Operate
    DECLARE_SHAREPTR(IMIOpBase);
    DECLARE_SHAREPTR(IMIOpPushFaceData);
    DECLARE_SHAREPTR(IMIOpCreateScene);
    DECLARE_SHAREPTR(IMIOpEngineResume);
    DECLARE_SHAREPTR(IMIOpEngineSuspend);
    //Test
    DECLARE_SHAREPTR(IMIOpCreateTest);
    DECLARE_SHAREPTR(IMIOpCreateDebugFacePt);
    //
    DECLARE_SHAREPTR(IMIOpDestroyScene);
    DECLARE_SHAREPTR(IMIOpCameraControl);
    DECLARE_SHAREPTR(IMIOpCreateSkyDome);
    DECLARE_SHAREPTR(IMIOpCreateParticle);
    DECLARE_SHAREPTR(IMIOpCreateEffcet);
    DECLARE_SHAREPTR(IMIOpCloseDetect);
    DECLARE_SHAREPTR(IMIOpSetBeautyFilter);
    DECLARE_SHAREPTR(IMIOpUpdateFilterSmooth);
    DECLARE_SHAREPTR(IMIOpShapeFaceSmoothFilter);
    DECLARE_SHAREPTR(IMIOpLUTFilterCreate);
    DECLARE_SHAREPTR(IMIOpUpdateBSplineFilter);
    DECLARE_SHAREPTR(IMIOpCloseBeautyFilter);
    //
    DECLARE_SHAREPTR(IMIOpLoadBase);
    DECLARE_SHAREPTR(IMIOpPick);
    DECLARE_SHAREPTR(IMIOpRecycleNode);
    //
    DECLARE_SHAREPTR(IMIOpCreateIOSTexIDInstream);
    DECLARE_SHAREPTR(IMIOpCreateIOSInstream);
    DECLARE_SHAREPTR(IMIOpDestroyIOSInstream);
    DECLARE_SHAREPTR(IMIOpCreateIOSOutstream);
    DECLARE_SHAREPTR(IMIOpDestroyIOSOutstream);
    DECLARE_SHAREPTR(IMIOpOpenIOSOutstream);
    DECLARE_SHAREPTR(IMIOpCloseIOSOutstream);
    DECLARE_SHAREPTR(IMIOpDestroyTextureOutstream);
    DECLARE_SHAREPTR(IMIOpCreateAndriodCamera);
    DECLARE_SHAREPTR(IMIOpCreateTextureCamera);
    DECLARE_SHAREPTR(IMIOpCreateStreamCamera);
    DECLARE_SHAREPTR(IMIOpDestroyStreamCamera);
    DECLARE_SHAREPTR(IMIOpParse);
    DECLARE_SHAREPTR(IMIOperateDelEft);
    DECLARE_SHAREPTR(IMIOpSaveEft);
    DECLARE_SHAREPTR(IMIOpFilterEft);
    DECLARE_SHAREPTR(IMIOpGenerate);
    DECLARE_SHAREPTR(IMIOpTexAttachment);
    
    DECLARE_SHAREPTR(IMIOpDestroyEffect);
    
    DECLARE_SHAREPTR(IMIOpResizeRenderder);
    DECLARE_SHAREPTR(IMIOpSetRenderTarget);
    DECLARE_SHAREPTR(IMIOpSetRenderTextureTarget);
    DECLARE_SHAREPTR(IMIOpSetRenderMirror);
    DECLARE_SHAREPTR(IMIOpAppMode);
    
    //核心实用库
    //util
    DECLARE_SHAREPTR(SpineMeshData);
    DECLARE_SHAREPTR(IMIBone);
    DECLARE_SHAREPTR(IMISkeleton);
    
    DECLARE_SHAREPTR(IMIASKey);
    DECLARE_SHAREPTR(IMIASKeyPos);
    DECLARE_SHAREPTR(IMIASKeyRot);
    DECLARE_SHAREPTR(IMIASKeyScale);
    DECLARE_SHAREPTR(IMIChannel);
    DECLARE_SHAREPTR(IMIAnimateSkin);
    DECLARE_SHAREPTR(IMISkinMgr);
    DECLARE_SHAREPTR(IMIAnimateMorph);
    DECLARE_SHAREPTR(IMISpine);
    DECLARE_SHAREPTR(IMIParticlesWorldBase);
    DECLARE_SHAREPTR(IMIParticles);
    DECLARE_SHAREPTR(IMIImageUsingMove);
    //
    DECLARE_SHAREPTR(IMIMesh3d);
    DECLARE_SHAREPTR(IMIModel);
    //
    DECLARE_SHAREPTR(IMIPass);
    DECLARE_SHAREPTR(IMIParamDeform);
    DECLARE_SHAREPTR(IMIDeformScale);
    DECLARE_SHAREPTR(IMIDeformImageMove);
    //font
    DECLARE_SHAREPTR(IMIFont);
    DECLARE_SHAREPTR(IMIBMFont);
    //image
    DECLARE_SHAREPTR(IMIImage);
    DECLARE_SHAREPTR(IMINoise);

    // detect
    DECLARE_SHAREPTR(IMIDetectBase);
    DECLARE_SHAREPTR(IMIDetectST);
    DECLARE_SHAREPTR(IMIPerson);
    DECLARE_SHAREPTR(IMIPersonModule);
    DECLARE_SHAREPTR(IMITrackerFace);
    DECLARE_SHAREPTR(IMIPersonExpressionExt);
    
    //logic
    //逻辑系统下的模块
    DECLARE_SHAREPTR(IMIRecycleProcess);
    DECLARE_SHAREPTR(IMIPickProcess);
    DECLARE_SHAREPTR(IMIFontProcess);

    //功能部分
    DECLARE_SHAREPTR(IMIStreamIn);
    DECLARE_SHAREPTR(IMIStreamOut);
    //parse部分
    DECLARE_SHAREPTR(IMIParse);
    DECLARE_SHAREPTR(IMIParse2DAni);
    DECLARE_SHAREPTR(IMIParseAnimate);
    DECLARE_SHAREPTR(IMIParseMain);
    DECLARE_SHAREPTR(IMIParseParticle);
    DECLARE_SHAREPTR(IMIParseLUTFilter);
    DECLARE_SHAREPTR(IMIParseData);
    DECLARE_SHAREPTR(IMIParseMask);
    DECLARE_SHAREPTR(IMIParseStamp);
    DECLARE_SHAREPTR(IMIParseGame);

    //filter 部分
    DECLARE_SHAREPTR(IMIFilterBase);
    DECLARE_SHAREPTR(IMIFairDataBlur);
    DECLARE_SHAREPTR(IMIFaceBeautyBase);
    DECLARE_SHAREPTR(IMIGenFBParam);
    DECLARE_SHAREPTR(IMIFairLtraLow);
    DECLARE_SHAREPTR(IMIGenLUTParam);
    DECLARE_SHAREPTR(IMIDataFilter);
    DECLARE_SHAREPTR(IMIFilterGenLUT);
    DECLARE_SHAREPTR(IMIFilterGof);
    DECLARE_SHAREPTR(IMIFilterGlow);
    DECLARE_SHAREPTR(IMIFilterBlur);
    DECLARE_SHAREPTR(IMIRGBToneCurveFilter);
    DECLARE_SHAREPTR(IMIFilterPicmodify);

    //物理部分
    DECLARE_SHAREPTR(IMIPhysicsWorldBase);
    DECLARE_SHAREPTR(IMIPhysicsWorld);
    DECLARE_SHAREPTR(IMIPhysicsSoftRigidWorld);
    DECLARE_SHAREPTR(IMIPhysicsBody);
    DECLARE_SHAREPTR(IMIPhysicsBodySoft);
    DECLARE_SHAREPTR(IMIPhysicsBodyRigid);
    DECLARE_SHAREPTR(IMIPhysicsBodyRope);
    DECLARE_SHAREPTR(IMIPhysicsBodyCloth);
    DECLARE_SHAREPTR(IMIPhysicsShape);
    DECLARE_SHAREPTR(IMIPhysicsShapeBox);
    DECLARE_SHAREPTR(IMIPhysicsShapeSphere);
    DECLARE_SHAREPTR(IMIPhysicsJoint);
    DECLARE_SHAREPTR(IMIPhysicsCollider);
    

}//!namespace imi

//
template <typename T, typename... Args>
inline std::shared_ptr<T> MakeSharedPtr(Args&&... args){
    return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
inline std::shared_ptr<T> PointerSharedPtr(T* _pointer){
    std::shared_ptr<T> share_obj(_pointer);
    return share_obj;
}

template <typename T>
using ShareFromThis = std::enable_shared_from_this<T> ;


#define DYN_TO_SHAREPTR(classname,param) std::dynamic_pointer_cast<classname>(param);
#define THIS_TO_SHAREPTR(classname) std::dynamic_pointer_cast<classname>(this->shared_from_this()) 

#endif //IMI_PREDECLARE_H


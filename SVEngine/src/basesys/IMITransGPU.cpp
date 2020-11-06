//
// IMITransGPU.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITransGPU.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../core/IMIPass.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIComData.h"
#include "../app/IMIInst.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlCore.h"
#include "../core/IMIGeoGen.h"

using namespace imi;

IMITransGPU::IMITransGPU(IMIInstPtr _app,
                       IMITexturePtr _t0,
                       IMITexturePtr _t1,
                       IMITexturePtr _t2,
                       IMITexturePtr _tOut)
:IMITrans(_app)
,m_tex0(_t0)
,m_tex1(_t1)
,m_tex2(_t2)
,m_texOut(_tOut){
//    m_passNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_passNode->setRSType(RST_SKY);
    m_pMtl = nullptr;
    //m_pMesh = nullptr;
}

IMITransGPU::~IMITransGPU() {
    destroy();
    m_pMtl = nullptr;
}

void IMITransGPU::init(s32 _w, s32 _h, f32 _angle, IMI_PIC_FORMATE _picformate, IMI_TEXIN _tt) {
//    IMITrans::init(_w, _h, _angle, _picformate, _tt);
//    if (_picformate == IMI_PF_GRAY8) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "yuv2y");
//        m_pMtl->setTexture(0, m_tex0);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_YV12) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "yuv2rgbyv12");
//        m_pMtl->setTexture(0, m_tex0);
//        m_pMtl->setTexture(1, m_tex1);
//        m_pMtl->setTexture(2, m_tex2);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_I420) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "yuv2rgbi420");
//        m_pMtl->setTexture(0, m_tex0);
//        m_pMtl->setTexture(1, m_tex1);
//        m_pMtl->setTexture(2, m_tex2);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_NV12) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "yuv2rgb12");
//        m_pMtl->setTexture(0, m_tex0);
//        m_pMtl->setTexture(1, m_tex1);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_NV21) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "yuv2rgb21");
//        m_pMtl->setTexture(0, m_tex0);
//        m_pMtl->setTexture(1, m_tex1);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_BGRA) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "bgra2rgba");
//        m_pMtl->setTexture(0, m_tex0);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_RGBA) {
//        m_pMtl = MakeSharedPtr<IMIMtlCore>(mApp, "rgba");
//        m_pMtl->setTexture(0, m_tex0);
//        createPass(_w,_h,_angle,_tt);
//    } else if (_picformate == IMI_PF_RGB) {
//    }
}

void IMITransGPU::destroy() {
    m_tex0 = nullptr;
    m_tex1 = nullptr;
    m_tex2 = nullptr;
    m_texOut = nullptr;
}

void IMITransGPU::update(f32 dt) {
//    if (m_pMtl) {
//        m_pMtl->setTexcoordFlip(1.0f, -1.0f);
//        if (m_picformate == IMI_PF_GRAY8) {
// 
//        } else if (m_picformate == IMI_PF_YV12) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//            m_pMtl->setTexture(1, m_tex1);
//            m_pMtl->setTexSizeIndex(1, 1.0f / (m_tex1->getwidth() / 2),
//                                    1.0f / (m_tex1->getheight() / 2));
//        } else if (m_picformate == IMI_PF_I420) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//            m_pMtl->setTexture(1, m_tex1);
//            m_pMtl->setTexSizeIndex(1, 1.0f / (m_tex1->getwidth() / 2),
//                                    1.0f / (m_tex1->getheight() / 2));
//            m_pMtl->setTexture(1, m_tex2);
//            m_pMtl->setTexSizeIndex(1, 1.0f / (m_tex2->getwidth() / 2),
//                                    1.0f / (m_tex2->getheight() / 2));
//        } else if (m_picformate == IMI_PF_NV12) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//            m_pMtl->setTexture(1, m_tex1);
//            m_pMtl->setTexSizeIndex(1, 1.0f / (m_tex1->getwidth() / 2),
//                                    1.0f / (m_tex1->getheight() / 2));
//        } else if (m_picformate == IMI_PF_NV21) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//            m_pMtl->setTexture(1, m_tex1);
//            m_pMtl->setTexSizeIndex(1, 1.0f / (m_tex1->getwidth() / 2),
//                                    1.0f / (m_tex1->getheight() / 2));
//        } else if (m_picformate == IMI_PF_BGRA) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//        } else if (m_picformate == IMI_PF_RGBA) {
//            m_pMtl->setTexcoordFlip(1.0,1.0);
//            m_pMtl->setTexture(0, m_tex0);
//            m_pMtl->setTexSizeIndex(0, 1.0f / m_tex0->getwidth(), 1.0f / m_tex0->getheight());
//        } else if (m_picformate == IMI_PF_RGB) {
//        }
//        m_pMtl->update(dt);
//    }
//    if (m_passNode) {
//        m_passNode->update(0.0f);
//    }
}

void IMITransGPU::render(){
//    if (m_passNode) {
//        m_passNode->render();
//    }
}

void IMITransGPU::setAngle(f32 _angle){
//    if(_angle!=m_angle){
//        m_angle=_angle;
//        IMIPassPtr t_pass=m_passNode->getPass(0);
//        if (_angle == 90) {
//            t_pass->setMesh(mApp->getComData()->m_screenMeshRot90);
//        } else if (_angle == 270) {
//            t_pass->setMesh(mApp->getComData()->m_screenMeshRot270);
//        } else if(_angle == 180) {
//            t_pass->setMesh(mApp->getComData()->m_screenMeshRot180);
//        }
//    }
}

void IMITransGPU::createPass(s32 _w, s32 _h, f32 _angle, IMI_TEXIN _tt) {
//    m_passNode->create(_w, _h);
//    IMIPassPtr t_pass = MakeSharedPtr<IMIPass>();
//    m_pMtl->setTexcoordFlip(1.0,1.0);
//    m_pMtl->setDepthEnable(false);
//    m_pMtl->setTextureParam(0,E_T_PARAM_WRAP_S,E_T_WRAP_CLAMP_TO_EDAGE);
//    m_pMtl->setTextureParam(0,E_T_PARAM_WRAP_T,E_T_WRAP_CLAMP_TO_EDAGE);
//    m_pMtl->setTextureParam(1,E_T_PARAM_WRAP_S,E_T_WRAP_CLAMP_TO_EDAGE);
//    m_pMtl->setTextureParam(1,E_T_PARAM_WRAP_T,E_T_WRAP_CLAMP_TO_EDAGE);
//    m_pMtl->setTextureParam(2,E_T_PARAM_WRAP_S,E_T_WRAP_CLAMP_TO_EDAGE);
//    m_pMtl->setTextureParam(2,E_T_PARAM_WRAP_T,E_T_WRAP_CLAMP_TO_EDAGE);
//    t_pass->setMtl(m_pMtl);
//    t_pass->mTag = "IMITransGPU";
//    if (_angle == 90) {
//        t_pass->setMesh(mApp->getComData()->m_screenMeshRot90);
//    } else if (_angle == 270) {
//        t_pass->setMesh(mApp->getComData()->m_screenMeshRot270);
//    } else if(_angle == 180) {
//        t_pass->setMesh(mApp->getComData()->m_screenMeshRot180);
//    }
//    t_pass->setOutTex(_tt);
//    m_passNode->addPass(t_pass);
}

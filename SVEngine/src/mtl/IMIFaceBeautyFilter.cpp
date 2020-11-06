//
// IMIFaceBeautyFilter.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFaceBeautyFilter.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMIMtlFair1.h"
#include "../mtl/IMIMtlBeauty.h"
#include "../core/IMIPass.h"
#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIMtlBasedOn.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIFaceBeautyBase::IMIFaceBeautyBase(IMIInstPtr _app)
        : IMIFilterBase(_app) {
    m_pParam = MakeSharedPtr<IMIGenFBParam>();
    m_pParam->reset();
}

IMIFaceBeautyBase::~IMIFaceBeautyBase() {

}

bool IMIFaceBeautyBase::create() {
    return false;
}

void IMIFaceBeautyBase::destroy() {

}

void IMIFaceBeautyBase::update(f32 dt) {

}

void IMIFaceBeautyBase::refreshData(IMIGenFBParamPtr _param) {
    if (m_pParam && _param) {
        m_pParam->copy(_param);
    }
}

void IMIFaceBeautyBase::setSmooth(f32 _smooth) {
    m_pParam->m_smooth = _smooth;
}

void IMIFaceBeautyBase::setParam01(f32 _smooth) {
    m_pParam->m_param01 = _smooth;
}

void IMIFaceBeautyBase::setParam02(f32 _smooth) {
    m_pParam->m_param02 = _smooth;
}

void IMIFaceBeautyBase::setParam03(f32 _smooth) {
    m_pParam->m_param03 = _smooth;
}

void IMIFaceBeautyBase::setParam04(f32 _smooth) {
    m_pParam->m_param04 = _smooth;
}

void IMIFaceBeautyBase::setParam05(f32 _smooth) {
    m_pParam->m_param05 = _smooth;
}

void IMIFaceBeautyBase::setParam06(f32 _smooth) {
    m_pParam->m_param06 = _smooth;
}

//序列化
void IMIFaceBeautyBase::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                              RAPIDJSON_NAMESPACE::Value &_objValue) {
}

void IMIFaceBeautyBase::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
}

//
IMIFairDataBlur::IMIFairDataBlur(IMIInstPtr _app)
: IMIFaceBeautyBase(_app) {
//    m_name = "IMIFairDataBlur";
//    m_mtl_a = nullptr;
//    m_mtl_b = nullptr;
//    m_mtl_c = nullptr;
//    m_mtl_d = nullptr;
//    m_mtl_e = nullptr;
//    m_mtl_back = nullptr;
//    m_pPassNode = nullptr;
//    m_pParam->m_smooth = 0.0;
//    m_pParam->m_param01 = 2.5;
//    m_pParam->m_param02 = 2.5;
//    m_pParam->m_param03 = 2.5;
//    m_pParam->m_param04 = 2.5;
//    m_pParam->m_param05 = 2.5;
//    m_pParam->m_param06 = 3.5;
}

IMIFairDataBlur::~IMIFairDataBlur() {
}

bool IMIFairDataBlur::create() {
    IMIRendererPtr t_renderer = mApp->getRenderer();
    if (!t_renderer)
        return false;
    s32 t_w = mApp->m_global_param.sv_width;
    s32 t_h = mApp->m_global_param.sv_height;
    //
    m_mtl_a = MakeSharedPtr<IMIMtlCore>(mApp, "blur_fair_01");
    //m_mtl_a->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_a->setTexSizeIndex(0, 0.0, m_pParam->m_param01 / t_h);
    m_mtl_b = MakeSharedPtr<IMIMtlCore>(mApp, "blur_fair_01");
    //m_mtl_b->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_b->setTexSizeIndex(0, m_pParam->m_param02 / t_w, 0.0);
    m_mtl_c = MakeSharedPtr<IMIMtlCore>(mApp, "blur_fair_mean");
    //m_mtl_c->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_c->setTexSizeIndex(0, m_pParam->m_param03 / t_w, m_pParam->m_param03 / t_h);
    m_mtl_e = MakeSharedPtr<IMIMtlCore>(mApp, "blur_fair_01");
    //m_mtl_e->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_e->setTexSizeIndex(0, 0.0, m_pParam->m_param04 / t_h);
    m_mtl_f = MakeSharedPtr<IMIMtlCore>(mApp, "blur_fair_01");
    //m_mtl_f->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_f->setTexSizeIndex(0, m_pParam->m_param05 / t_w, 0.0);
    m_mtl_d = MakeSharedPtr<IMIMtlBlurFair>(mApp);
    //m_mtl_d->setTexcoordFlip(1.0f, 1.0f);
    //m_mtl_d->setTexSizeIndex(0, m_pParam->m_param06 / t_w, m_pParam->m_param06 / t_h);
    m_mtl_back = MakeSharedPtr<IMIMtlCore>(mApp, "screen");
    //m_mtl_back->setTexcoordFlip(1.0f, 1.0f);
    
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->create(t_w, t_h);
//    m_pPassNode->setRSType(RST_BEAUTY);
    //
    
//    //
//    if (!t_renderer->getIMITex(E_TEX_HELP0)) {
//        t_renderer->createIMITex(E_TEX_HELP0, t_w, t_h, GL_RGBA);
//    }
//    //
//    if (!t_renderer->getIMITex(E_TEX_HELP1)) {
//        t_renderer->createIMITex(E_TEX_HELP1, t_w, t_h, GL_RGBA);
//    }
//    //
//    if (!t_renderer->getIMITex(E_TEX_HELP2)) {
//        t_renderer->createIMITex(E_TEX_HELP2, t_w, t_h, GL_RGBA);
//    }
//    IMIPassPtr t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_a);
//    t_pass->setInTex(0, E_TEX_MAIN);
//    t_pass->setOutTex(E_TEX_HELP0);
//    t_pass->mTag = "blur_fair_01";
//    m_pPassNode->addPass(t_pass);
//
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_b);
//    t_pass->setInTex(0, E_TEX_HELP0);
//    t_pass->setOutTex(E_TEX_HELP1);
//    t_pass->mTag = "blur_fair_01";
//    m_pPassNode->addPass(t_pass);
//    //
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_c);
//    t_pass->setInTex(0, E_TEX_MAIN);
//    t_pass->setInTex(1, E_TEX_HELP1);
//    t_pass->setOutTex(E_TEX_HELP2);
//    t_pass->mTag = "blur_fair_mean";
//    m_pPassNode->addPass(t_pass);
//    //
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_e);
//    t_pass->setInTex(0, E_TEX_HELP2);
//    t_pass->setOutTex(E_TEX_HELP0);
//    m_pPassNode->addPass(t_pass);
//    //
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_f);
//    t_pass->setInTex(0, E_TEX_HELP0);
//    t_pass->setOutTex(E_TEX_HELP2);
//    t_pass->mTag = "blur_fair_01";
//    m_pPassNode->addPass(t_pass);
//    //
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_d);
//    t_pass->setInTex(0, E_TEX_MAIN);
//    t_pass->setInTex(1, E_TEX_HELP1);
//    t_pass->setInTex(2, E_TEX_HELP2);
//    t_pass->setOutTex(E_TEX_HELP0);
//    t_pass->mTag = "IMIMtlBlurFair";
//    m_pPassNode->addPass(t_pass);
//    //写回
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "IMIFairDataBlur";
//    //t_pass->setMtl(m_mtl_back);
//    t_pass->setInTex(0, E_TEX_HELP0);
//    t_pass->setOutTex(E_TEX_MAIN);
//    t_pass->mTag = "writeback";
//    m_pPassNode->addPass(t_pass);
    return true;
}

void IMIFairDataBlur::destroy() {
    m_mtl_a = nullptr;
    m_mtl_b = nullptr;
    m_mtl_c = nullptr;
    m_mtl_d = nullptr;
    m_mtl_e = nullptr;
    m_mtl_back = nullptr;
}


void IMIFairDataBlur::update(f32 dt) {
    s32 t_w = mApp->m_global_param.sv_width;
    s32 t_h = mApp->m_global_param.sv_height;
    if (m_mtl_a) {
        //m_mtl_a->setTexcoordFlip(1.0, 1.0);
        //m_mtl_a->setTexSizeIndex(0, 0.0, m_pParam->m_param01 / t_h);
    }

    if (m_mtl_b) {
        //m_mtl_b->setTexcoordFlip(1.0, 1.0);
        //m_mtl_b->setTexSizeIndex(0, m_pParam->m_param02 / t_w, 0.0);
    }

    if (m_mtl_c) {
        //m_mtl_c->setTexcoordFlip(1.0, 1.0);
        //m_mtl_c->setTexSizeIndex(0, m_pParam->m_param03 / t_w, m_pParam->m_param03 / t_h);
    }

    if (m_mtl_d) {
        //m_mtl_d->setTexcoordFlip(1.0, 1.0);
        //m_mtl_d->setTexSizeIndex(0, m_pParam->m_param06 / t_w, m_pParam->m_param06 / t_h);
        //m_mtl_d->setSmooth(m_pParam->m_smooth);
    }

    if (m_mtl_e) {
        //m_mtl_e->setTexcoordFlip(1.0, 1.0);
        //m_mtl_e->setTexSizeIndex(0, 0.0, m_pParam->m_param04 / t_h);
    }

    if (m_mtl_f) {
        //m_mtl_f->setTexcoordFlip(1.0, 1.0);
        //m_mtl_f->setTexSizeIndex(0, m_pParam->m_param05 / t_w, 0.0);
    }
}

//序列化
void IMIFairDataBlur::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);
    locationObj.AddMember("m_smooth", m_pParam->m_smooth, _allocator);
    locationObj.AddMember("param01", m_pParam->m_param01, _allocator);
    locationObj.AddMember("param02", m_pParam->m_param02, _allocator);
    locationObj.AddMember("param03", m_pParam->m_param03, _allocator);
    locationObj.AddMember("param04", m_pParam->m_param04, _allocator);
    locationObj.AddMember("param05", m_pParam->m_param05, _allocator);
    locationObj.AddMember("param06", m_pParam->m_param06, _allocator);
    _objValue.AddMember("facebeauty01", locationObj, _allocator);  //添加object到Document中
}

void IMIFairDataBlur::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {

    if (item.HasMember("m_smooth") && item["m_smooth"].IsFloat()) {
        m_pParam->m_smooth = item["m_smooth"].GetFloat();
    }

    if (item.HasMember("param01") && item["param01"].IsFloat()) {
        m_pParam->m_param01 = item["param01"].GetFloat();
    }

    if (item.HasMember("param02") && item["param02"].IsFloat()) {
        m_pParam->m_param02 = item["param02"].GetFloat();
    }

    if (item.HasMember("param03") && item["param03"].IsFloat()) {
        m_pParam->m_param03 = item["param03"].GetFloat();
    }

    if (item.HasMember("param04") && item["param04"].IsFloat()) {
        m_pParam->m_param04 = item["param04"].GetFloat();
    }

    if (item.HasMember("param05") && item["param05"].IsFloat()) {
        m_pParam->m_param05 = item["param05"].GetFloat();
    }

    if (item.HasMember("param06") && item["param06"].IsFloat()) {
        m_pParam->m_param06 = item["param06"].GetFloat();
    }

}

IMIFairLtraLow::IMIFairLtraLow(IMIInstPtr _app)
: IMIFilterBase(_app) {
    m_name = "IMIFairLtraLow";
    m_mtl_a = nullptr;
    m_mtl_back = nullptr;
    m_smooth = 0.0;
}

IMIFairLtraLow::~IMIFairLtraLow() {
}

bool IMIFairLtraLow::create() {
//    IMIRendererPtr t_renderer = mApp->getRenderMgr()->getRenderer();
//    if (!t_renderer)
//        return false;
//    s32 t_w = mApp->m_global_param.sv_width;
//    s32 t_h = mApp->m_global_param.sv_height;
//    m_mtl_a = MakeSharedPtr<IMIMtlFairLtraLow>(mApp);
//    m_mtl_a->setTexcoordFlip(1.0f, 1.0f);
//    m_mtl_back = MakeSharedPtr<IMIMtlCore>(mApp, "screen");
//    m_mtl_back->setTexcoordFlip(1.0f, 1.0f);
//
//    if (!t_renderer->getIMITex(E_TEX_HELP0)) {
//        t_renderer->createIMITex(E_TEX_HELP0, t_w, t_h, GL_RGBA);
//    }
//
//    m_pPassNode = MakeSharedPtr<IMIMultPassNode>(mApp);
//    m_pPassNode->create(t_w, t_h);
//    //  m_pPassNode->setRSType(RST_BEAUTY);
//
//    IMIPassPtr t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "filter-beauty-lows";
//    t_pass->setMtl(m_mtl_a);
//    t_pass->setInTex(0, E_TEX_MAIN);
//    t_pass->setOutTex(E_TEX_HELP0);
//    m_pPassNode->addPass(t_pass);
//    //写回
//    t_pass = MakeSharedPtr<IMIPass>();
//    t_pass->mTag = "filter-beauty-lows-back";
//    t_pass->setMtl(m_mtl_back);
//    t_pass->setInTex(0, E_TEX_HELP0);
//    t_pass->setOutTex(E_TEX_MAIN);
//    m_pPassNode->addPass(t_pass);
    return true;
}

void IMIFairLtraLow::destroy() {
    m_mtl_a = nullptr;
    m_mtl_back = nullptr;
}

void IMIFairLtraLow::update(f32 dt) {
    if (m_mtl_a) {
        IMIMtlFairLtraLowPtr t_tmp = std::dynamic_pointer_cast<IMIMtlFairLtraLow>(m_mtl_a);
        if (t_tmp) {
            //t_tmp->setTexcoordFlip(1.0, 1.0);
            t_tmp->setSmooth(m_smooth);
        }
    }
}


//
// IMIMtlBillboard.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMtlBillboard.h"
#include "../mtl/IMITexture.h"
#include "../rendercore/IMIRenderer.h"
#include "../basesys/IMICameraMgr.h"
#include "../basesys/IMICameraNode.h"

using namespace imi;

IMIMtlBillboard::IMIMtlBillboard(IMIInstPtr _app)
:IMIMtlCore(_app,"normal3d_billboard") {
    m_objPos.set(0, 0, 0);
    m_viewPos.set(0, 0, 0);
    m_up.set(0, 0, 0);
}

IMIMtlBillboard::IMIMtlBillboard(IMIMtlBillboard *_mtl)
:IMIMtlCore(_mtl){
    m_objPos = _mtl->m_objPos;
    m_viewPos = _mtl->m_viewPos;
    m_up = _mtl->m_up;
}

IMIMtlBillboard::~IMIMtlBillboard() {
    
}

IMIMtlCorePtr IMIMtlBillboard::clone() {
    return PointerSharedPtr<IMIMtlBillboard>(new IMIMtlBillboard(this));
}

void IMIMtlBillboard::reset() {
    IMIMtlCore::reset();
}

void IMIMtlBillboard::setObjectPos(FVec3 &_pos){
    m_objPos.set(_pos);
}

void IMIMtlBillboard::setViewPos(FVec3 &_viewPos){
    m_viewPos.set(_viewPos);
}

void IMIMtlBillboard::setUp(FVec3 &_up){
    m_up.set(_up);
}

void IMIMtlBillboard::_submitUniform(IMIRendererPtr _render) {
    IMIMtlCore::_submitUniform(_render);
//    _render->submitUniformf3v("u_up", m_up.get());
//    _render->submitUniformf3v("u_viewPos", m_viewPos.get());
//    _render->submitUniformf3v("u_objPos", m_objPos.get());
}


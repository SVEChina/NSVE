//
// IMIMesh.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMesh3d.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../base/IMIDataSwap.h"
#include "../work/IMITdCore.h"
#include "../mtl/IMIMtlGLTF.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMISurface.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderCmd.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIMesh3d::IMIMesh3d(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_rendermesh = nullptr;
    m_mtl = nullptr;
    m_surface = MakeSharedPtr<IMISurface>();
    m_absoluteMat.setIdentity();
}

IMIMesh3d::~IMIMesh3d() {
    m_rendermesh = nullptr;
    m_mtl = nullptr;
    m_surface = nullptr;
}

void IMIMesh3d::setRenderMesh(IMIRenderMeshPtr _mesh) {
    m_rendermesh = _mesh;
}

IMIRenderMeshPtr IMIMesh3d::getRenderMesh(){
    return m_rendermesh;
}

void IMIMesh3d::setMtl(IMIMtlCorePtr _mtl) {
    m_mtl = _mtl;
}

IMIMtlCorePtr IMIMesh3d::getMtl(){
    return m_mtl;
}

void IMIMesh3d::setSurface(IMISurfacePtr _surface) {
    m_surface = _surface;
}

IMISurfacePtr IMIMesh3d::getSurface() {
    return m_surface;
}

void IMIMesh3d::setName(cptr8 _name) {
    m_name = _name;
}

cptr8 IMIMesh3d::getName(){
    return m_name.c_str();
}

void IMIMesh3d::setBox(IMIBoundBox& _box) {
    m_box = _box;
}

IMIBoundBox IMIMesh3d::getBox() {
    return m_box;
}

void IMIMesh3d::setMatrix(FMat4& _mat) {
    m_absoluteMat = _mat;
}

void IMIMesh3d::setBoneMatrix(IMIArray<FMat4> &_mats) {
    m_boneMatrixs = _mats;
}

void IMIMesh3d::update(f32 _dt,FMat4& _mat) {
    if(m_surface) {
        //骨头矩阵
        m_surface->setParamArray("bones", (FMat4*)m_boneMatrixs.get(), m_boneMatrixs.size());
        
        FMat4 t_mat = _mat*m_absoluteMat;
        m_surface->setParam("matModel", t_mat);
    }
    if(m_mtl) {
        m_mtl->update(_dt);
    }
}

void IMIMesh3d::render() {
    //先渲染自己
    if(m_rendermesh && m_mtl && m_surface) {
        IMIDispatch::dispatchMeshDraw(mApp, m_rendermesh, m_mtl, m_surface, E_RSM_SOLID, "IMIMesh3d");
    }
}

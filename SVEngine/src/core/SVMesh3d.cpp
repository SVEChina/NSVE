//
// SVMesh.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMesh3d.h"
#include "../app/SVInst.h"
#include "../app/SVDispatch.h"
#include "../base/SVDataSwap.h"
#include "../work/SVTdCore.h"
#include "../mtl/SVMtlGLTF.h"
#include "../mtl/SVMtlLib.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVSurface.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

SVMesh3d::SVMesh3d(SVInstPtr _app)
:SVGBaseEx(_app){
    m_rendermesh = nullptr;
    m_mtl = nullptr;
    m_surface = MakeSharedPtr<SVSurface>();
    m_absoluteMat.setIdentity();
}

SVMesh3d::~SVMesh3d() {
    m_rendermesh = nullptr;
    m_mtl = nullptr;
    m_surface = nullptr;
}

void SVMesh3d::setRenderMesh(SVRenderMeshPtr _mesh) {
    m_rendermesh = _mesh;
}

SVRenderMeshPtr SVMesh3d::getRenderMesh(){
    return m_rendermesh;
}

void SVMesh3d::setMtl(SVMtlCorePtr _mtl) {
    m_mtl = _mtl;
}

SVMtlCorePtr SVMesh3d::getMtl(){
    return m_mtl;
}

void SVMesh3d::setSurface(SVSurfacePtr _surface) {
    m_surface = _surface;
}

SVSurfacePtr SVMesh3d::getSurface() {
    return m_surface;
}

void SVMesh3d::setName(cptr8 _name) {
    m_name = _name;
}

cptr8 SVMesh3d::getName(){
    return m_name.c_str();
}

void SVMesh3d::setBox(SVBoundBox& _box) {
    m_box = _box;
}

SVBoundBox SVMesh3d::getBox() {
    return m_box;
}

void SVMesh3d::setMatrix(FMat4& _mat) {
    m_absoluteMat = _mat;
}

void SVMesh3d::setBoneMatrix(SVArray<FMat4> &_mats) {
    m_boneMatrixs = _mats;
}

void SVMesh3d::update(f32 _dt,FMat4& _mat) {
    if(m_surface) {
        //骨头矩阵
        
//        for (int i = 0; i < m_boneMatrixs.size(); i++) {
//            FMat4 mat4 = m_boneMatrixs[i];
//            f32 *data = mat4.get();
//            NSLog(@"aaaaaaaaaaaa %d     %f  %f  %f  %f   %f  %f  %f  %f   %f  %f  %f  %f   %f  %f  %f  %f  ",
//                  i,
//                  data[0],data[1],data[2],data[3],
//                  data[4],data[5],data[6],data[7],
//                  data[8],data[9],data[10],data[11],
//                  data[12],data[13],data[14],data[15]
//            );
//        }
        
        
        FMat4* aaa = (FMat4*)m_boneMatrixs.get();
        
        
        
        m_surface->setParamArray("aBones", (FMat4*)m_boneMatrixs.get(), m_boneMatrixs.size());
        
        FMat4 t_mat = _mat*m_absoluteMat;
        m_surface->setParam("matModel", t_mat);
    }
    if(m_mtl) {
        m_mtl->update(_dt);
    }
}

void SVMesh3d::render() {
    //先渲染自己
    if(m_rendermesh && m_mtl && m_surface) {
        SVDispatch::dispatchMeshDraw(mApp, m_rendermesh, m_mtl, m_surface, E_RSM_SOLID, "SVMesh3d");
    }
}

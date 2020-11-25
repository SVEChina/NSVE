//
// SVModel.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVModel.h"
#include "SVMesh3d.h"
#include "../mtl/SVMtlGLTF.h"
#include "../core/SVAnimateSkin.h"

using namespace sv;

SVModel::SVModel(SVInstPtr _app)
:SVGBaseEx(_app){
    m_meshPool.clear();
}

SVModel::~SVModel() {
    clear();
}

cptr8 SVModel::getName(){
    return m_name.c_str();
}

void SVModel::setName(cptr8 _name){
    m_name = _name;
}

void SVModel::addMesh(SVMesh3dPtr _mesh) {
    m_meshPool.push_back(_mesh);
    if(m_meshPool.size() == 1) {
        m_box = _mesh->getBox();
    }else{
        m_box.expand(_mesh->getBox());
    }
}

SVMesh3dPtr SVModel::getMesh(s32 _index) {
    if(_index<0 || _index>=m_meshPool.size() )
        return nullptr;
    return m_meshPool[_index];
}

s32 SVModel::getMeshNum(){
    return m_meshPool.size();
}

void SVModel::clearMesh() {
    m_meshPool.clear();
}

SVBoundBox SVModel::getBox() {
    return m_box;
}

void SVModel::update(f32 _dt,FMat4& _mat) {
    for (s32 i = 0; i < m_meshPool.size(); i++) {
        if (m_ske) {
            m_meshPool[i]->setBoneMatrix(m_ske->m_mats);
        }
        m_meshPool[i]->update(_dt,_mat);
    }
}

void SVModel::render() {
    for (s32 i = 0; i < m_meshPool.size(); i++) {
        m_meshPool[i]->render();
    }
}

void SVModel::render(SVRTargetPtr _target) {
    for (s32 i = 0; i < m_meshPool.size(); i++) {
        m_meshPool[i]->render(_target);
    }
}

void SVModel::createShadow() {
//    for (s32 i = 0; i < m_meshPool.size(); i++) {
//        m_meshPool[i]->createShadow();
//    }
}

void SVModel::bindSke(SVSkeletonPtr _ske) {
    m_ske = _ske;
}

void SVModel::unbindSke() {
//    for (s32 i = 0; i < m_meshPool.size(); i++) {
//        SVMtlCorePtr t_mtl = m_meshPool[i]->getMtl();
//        SVMtlGLTFSkinPtr skin_mtl = DYN_TO_SHAREPTR(SVMtlGLTFSkin, t_mtl);
//        if(skin_mtl) {
//            skin_mtl->unbindSke();
//        }
//    }
}

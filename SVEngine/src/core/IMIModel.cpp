//
// IMIModel.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIModel.h"
#include "IMIMesh3d.h"
#include "../mtl/IMIMtlGLTF.h"
#include "../core/IMIAnimateSkin.h"

using namespace imi;

IMIModel::IMIModel(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_meshPool.clear();
}

IMIModel::~IMIModel() {
    clear();
}

cptr8 IMIModel::getName(){
    return m_name.c_str();
}

void IMIModel::setName(cptr8 _name){
    m_name = _name;
}

void IMIModel::addMesh(IMIMesh3dPtr _mesh) {
    m_meshPool.push_back(_mesh);
    if(m_meshPool.size() == 1) {
        m_box = _mesh->getBox();
    }else{
        m_box.expand(_mesh->getBox());
    }
}

IMIMesh3dPtr IMIModel::getMesh(s32 _index) {
    if(_index<0 || _index>=m_meshPool.size() )
        return nullptr;
    return m_meshPool[_index];
}

s32 IMIModel::getMeshNum(){
    return m_meshPool.size();
}

void IMIModel::clearMesh() {
    m_meshPool.clear();
}

IMIBoundBox IMIModel::getBox() {
    return m_box;
}

void IMIModel::update(f32 _dt,FMat4& _mat) {
    for (s32 i = 0; i < m_meshPool.size(); i++) {
        if (m_ske) {
            m_meshPool[i]->setBoneMatrix(m_ske->m_mats);
        }
        m_meshPool[i]->update(_dt,_mat);
    }
}

void IMIModel::render() {
    for (s32 i = 0; i < m_meshPool.size(); i++) {
        m_meshPool[i]->render();
    }
}

void IMIModel::createShadow() {
//    for (s32 i = 0; i < m_meshPool.size(); i++) {
//        m_meshPool[i]->createShadow();
//    }
}

void IMIModel::bindSke(IMISkeletonPtr _ske) {
    m_ske = _ske;
}

void IMIModel::unbindSke() {
//    for (s32 i = 0; i < m_meshPool.size(); i++) {
//        IMIMtlCorePtr t_mtl = m_meshPool[i]->getMtl();
//        IMIMtlGLTFSkinPtr skin_mtl = DYN_TO_SHAREPTR(IMIMtlGLTFSkin, t_mtl);
//        if(skin_mtl) {
//            skin_mtl->unbindSke();
//        }
//    }
}

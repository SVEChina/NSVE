//
// SVSkinNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVSkinNode.h"
#include "../basesys/SVCameraNode.h"
#include "../basesys/SVScene.h"
#include "../event/SVEventMgr.h"
#include "../basesys/SVConfig.h"
#include "../core/SVModel.h"
#include "../core/SVAnimateSkin.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVSurface.h"

#include "../app/SVDispatch.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderMgr.h"
#include "../core/SVGeoGen.h"
#include "../core/SVMesh3d.h"

using namespace sv;

SVSkinNode::SVSkinNode(SVInstPtr _app)
:SVNode(_app){
    ntype = "SVSkinNode";
    m_pModels = {};
    m_pSurfaces = {};
    m_pMtls = {};
    m_pActAni = nullptr;
    m_aniPool.clear();
}

SVSkinNode::~SVSkinNode() {
    clearAni();
    m_pModels.clear();
    m_pSurfaces.clear();
    m_pMtls.clear();
    m_pActAni = nullptr;
}

void SVSkinNode::update(f32 dt) {
    SVNode::update(dt);
    
    if(m_pActAni != nullptr) {
        m_pActAni->update(dt);
    }
    
    //
    size_t t_modelLen = m_pModels.size();
    for (int i = 0; i < t_modelLen; i++) {
        SVModelPtr _modelPtr = m_pModels[i];
        _modelPtr->update(dt, m_absolutMat);
    }
    
   
}

void SVSkinNode::render() {
    SVNode::render();
    size_t t_modelLen = m_pModels.size();
    for (size_t i = 0; i < t_modelLen; i++) {
        SVModelPtr _modelPtr = m_pModels[i];
        _modelPtr->render();
    }
}

//播放控制
void SVSkinNode::play(cptr8 _name) {
    ANIPOOL::Iterator it = m_aniPool.find(_name);
    if(it!=m_aniPool.end()){
        m_pActAni = it->data;
    }
}

void SVSkinNode::pause() {
}

void SVSkinNode::stop() {
}

std::vector<SVModelPtr> &SVSkinNode::getModel() {
    return m_pModels;
}

void SVSkinNode::setModel(std::vector<SVModelPtr> &_models) {
    m_pModels = _models;
//    if(m_pModel) {
//        m_pModel->bindSke(m_pSke);
//        m_aabbBox = m_pModel->getBox();
//    }
}

void SVSkinNode::clearModel() {
    size_t t_len = m_pModels.size();
    for (size_t i = 0; i < t_len; i++) {
        SVModelPtr _modelPtr = m_pModels[i];
        _modelPtr->unbindSke();
    }
    m_pModels.clear();
}

std::vector<SVSurfacePtr> &SVSkinNode::getSurface() {
    return m_pSurfaces;
}

void SVSkinNode::setSurface(std::vector<SVSurfacePtr> &_surfaces) {
    m_pSurfaces = _surfaces;
}

void SVSkinNode::clearSurface() {
    m_pSurfaces.clear();
}

std::vector<SVMtlCorePtr> &SVSkinNode::getMaterial() {
    return m_pMtls;
}

void SVSkinNode::setMaterial(std::vector<SVMtlCorePtr> &_mtls) {
    m_pMtls = _mtls;
}

void SVSkinNode::clearMaterial() {
    m_pMtls.clear();
}

//动画操作
void SVSkinNode::addAni(SVAnimateSkinPtr _ani) {
    m_aniPool.append(_ani->getName(), _ani);
//    if(m_pSke) {
        //_ani->bind(m_pSke);
//    }
    //test
//    m_pActAni = _ani;
}

void SVSkinNode::delAni(cptr8 _name) {
    ANIPOOL::Iterator it = m_aniPool.find(_name);
    if(it!=m_aniPool.end()){
        SVAnimateSkinPtr t_ani = it->data;
        //t_ani->unbind();
        m_aniPool.remove(it);
    }
}

void SVSkinNode::clearAni() {
    ANIPOOL::Iterator it = m_aniPool.begin();
    while(it!=m_aniPool.end()) {
        SVAnimateSkinPtr t_ani = it->data;
        //t_ani->unbind();
        it++;
    }
    m_aniPool.clear();
}

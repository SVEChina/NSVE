//
// IMISkinNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISkinNode.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../event/IMIEventMgr.h"
#include "../basesys/IMIConfig.h"
#include "../core/IMIModel.h"
#include "../core/IMIAnimateSkin.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMISurface.h"

#include "../app/IMIDispatch.h"
#include "../rendercore/IMIRenderMesh.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../core/IMIGeoGen.h"
#include "../core/IMIMesh3d.h"

using namespace imi;

IMISkinNode::IMISkinNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMISkinNode";
    m_pModels = {};
    m_pSurfaces = {};
    m_pMtls = {};
    m_pActAni = nullptr;
    m_aniPool.clear();
}

IMISkinNode::~IMISkinNode() {
    clearAni();
    m_pModels.clear();
    m_pSurfaces.clear();
    m_pMtls.clear();
    m_pActAni = nullptr;
}

void IMISkinNode::update(f32 dt) {
    IMINode::update(dt);
    
    if(m_pActAni != nullptr) {
        m_pActAni->update(dt);
    }
    
    //
    size_t t_modelLen = m_pModels.size();
    for (int i = 0; i < t_modelLen; i++) {
        IMIModelPtr _modelPtr = m_pModels[i];
        _modelPtr->update(dt, m_absolutMat);
    }
    
   
}

void IMISkinNode::render() {
    IMINode::render();
    size_t t_modelLen = m_pModels.size();
    for (size_t i = 0; i < t_modelLen; i++) {
        IMIModelPtr _modelPtr = m_pModels[i];
        _modelPtr->render();
    }
}

//播放控制
void IMISkinNode::play(cptr8 _name) {
    ANIPOOL::Iterator it = m_aniPool.find(_name);
    if(it!=m_aniPool.end()){
        m_pActAni = it->data;
    }
}

void IMISkinNode::pause() {
}

void IMISkinNode::stop() {
}

std::vector<IMIModelPtr> &IMISkinNode::getModel() {
    return m_pModels;
}

void IMISkinNode::setModel(std::vector<IMIModelPtr> &_models) {
    m_pModels = _models;
//    if(m_pModel) {
//        m_pModel->bindSke(m_pSke);
//        m_aabbBox = m_pModel->getBox();
//    }
}

void IMISkinNode::clearModel() {
    size_t t_len = m_pModels.size();
    for (size_t i = 0; i < t_len; i++) {
        IMIModelPtr _modelPtr = m_pModels[i];
        _modelPtr->unbindSke();
    }
    m_pModels.clear();
}

std::vector<IMISurfacePtr> &IMISkinNode::getSurface() {
    return m_pSurfaces;
}

void IMISkinNode::setSurface(std::vector<IMISurfacePtr> &_surfaces) {
    m_pSurfaces = _surfaces;
}

void IMISkinNode::clearSurface() {
    m_pSurfaces.clear();
}

std::vector<IMIMtlCorePtr> &IMISkinNode::getMaterial() {
    return m_pMtls;
}

void IMISkinNode::setMaterial(std::vector<IMIMtlCorePtr> &_mtls) {
    m_pMtls = _mtls;
}

void IMISkinNode::clearMaterial() {
    m_pMtls.clear();
}

//动画操作
void IMISkinNode::addAni(IMIAnimateSkinPtr _ani) {
    m_aniPool.append(_ani->getName(), _ani);
//    if(m_pSke) {
        //_ani->bind(m_pSke);
//    }
    //test
//    m_pActAni = _ani;
}

void IMISkinNode::delAni(cptr8 _name) {
    ANIPOOL::Iterator it = m_aniPool.find(_name);
    if(it!=m_aniPool.end()){
        IMIAnimateSkinPtr t_ani = it->data;
        //t_ani->unbind();
        m_aniPool.remove(it);
    }
}

void IMISkinNode::clearAni() {
    ANIPOOL::Iterator it = m_aniPool.begin();
    while(it!=m_aniPool.end()) {
        IMIAnimateSkinPtr t_ani = it->data;
        //t_ani->unbind();
        it++;
    }
    m_aniPool.clear();
}

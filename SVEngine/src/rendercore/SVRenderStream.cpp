//
// SVRenderStream.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderStream.h"
#include "SVRenderCmd.h"
#include "../work/SVTdCore.h"

using namespace sv;

SVRenderStream::SVRenderStream() {
    m_lock = MakeSharedPtr<SVLockSpin>();
    m_valid = false;
}

SVRenderStream::~SVRenderStream() {
    m_cmdArray.clear();
    m_valid = false;
    m_lock = nullptr;
}

void SVRenderStream::addRenderCmd(SVRenderCmdPtr cmd) {
    m_lock->lock();
    if(cmd){
        m_cmdArray.push_back(cmd);
    }
    m_lock->unlock();
}

void SVRenderStream::clearRenderCmd() {
    m_lock->lock();
    m_cmdArray.clear();
    m_lock->unlock();
}

void SVRenderStream::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    m_lock->lock();
    for (s32 i = 0; i < m_cmdArray.size(); i++) {
        m_cmdArray[i]->render(_renderer,_target);
    }
    m_cmdArray.clear();
    m_lock->unlock();
}


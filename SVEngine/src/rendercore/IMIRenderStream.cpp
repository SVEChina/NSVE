//
// IMIRenderStream.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderStream.h"
#include "IMIRenderCmd.h"
#include "../work/IMITdCore.h"

using namespace imi;

IMIRenderStream::IMIRenderStream() {
    m_lock = MakeSharedPtr<IMILockSpin>();
    m_valid = false;
}

IMIRenderStream::~IMIRenderStream() {
    m_cmdArray.clear();
    m_valid = false;
    m_lock = nullptr;
}

void IMIRenderStream::addRenderCmd(IMIRenderCmdPtr cmd) {
    m_lock->lock();
    if(cmd){
        m_cmdArray.push_back(cmd);
    }
    m_lock->unlock();
}

void IMIRenderStream::clearRenderCmd() {
    m_lock->lock();
    m_cmdArray.clear();
    m_lock->unlock();
}

#if  defined(IMI_IOS)
void IMIRenderStream::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    m_lock->lock();
    for (s32 i = 0; i < m_cmdArray.size(); i++) {
        glPushGroupMarkerEXT(0, m_cmdArray[i]->mTag.c_str());
        m_cmdArray[i]->render(_renderer,_target);
        glPopGroupMarkerEXT();
    }
    m_cmdArray.clear();
    m_lock->unlock();
}
#else
void IMIRenderStream::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    m_lock->lock();
    for (s32 i = 0; i < m_cmdArray.size(); i++) {
        m_cmdArray[i]->render(_renderer,_target);
    }
    m_cmdArray.clear();
    m_lock->unlock();
}
#endif




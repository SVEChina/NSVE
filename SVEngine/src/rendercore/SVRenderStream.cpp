//
// SVRenderStream.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderStream.h"
#include "SVRenderCmd.h"
#include "SVRenderTech.h"
#include "../work/SVTdCore.h"

using namespace sv;

SVRenderStream::SVRenderStream() {
    m_pTech = nullptr;
    //m_lock = MakeSharedPtr<SVLock>();
}

SVRenderStream::~SVRenderStream() {
    m_pTech = nullptr;
    //m_lock = nullptr;
}

void SVRenderStream::addSVRenderCmd(SVRenderCmdPtr cmd) {
//    m_lock->lock();
//    if(cmd){
//        m_cmdArray.append(cmd);
//    }
//    m_lock->unlock();
}

void SVRenderStream::clearSVRenderCmd() {
//    m_lock->lock();
//    m_cmdArray.destroy();
//    m_lock->unlock();
}

void SVRenderStream::render() {
    //渲染前先做cmd排序
    
    //做状态切换
    m_pTech->render();
//    m_lock->lock();
    //做指令渲染
    for (s32 i = 0; i < m_cmdArray.size(); i++) {
        m_cmdArray[i]->render();
    }
    m_cmdArray.destroy();
//    m_lock->unlock();
}


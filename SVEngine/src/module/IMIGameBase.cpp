//
// IMIGameBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIGameBase.h"
#include "IMIGameReady.h"
#include "IMIGameRun.h"
#include "IMIGameEnd.h"

using namespace imi;

IMIGameBase::IMIGameBase(IMIInstPtr _app)
:IMIModuleBase(_app) {
    m_pGameReady = nullptr;
    m_pGameRun = nullptr;
    m_pGameEnd = nullptr;
    m_stage = E_G_STAGE_WAIT;
}

IMIGameBase::~IMIGameBase() {
    m_pGameReady = nullptr;
    m_pGameRun = nullptr;
    m_pGameEnd = nullptr;
}

void IMIGameBase::init(IMIGameReadyPtr _ready,IMIGameRunPtr _run,IMIGameEndPtr _end) {
    IMIModuleBase::init();
    startListen();
    m_pGameReady = _ready;
    m_pGameRun = _run;
    m_pGameEnd = _end;
    //
    if(m_pGameReady) {
        m_pGameReady->init();
    }
    if( m_pGameRun ) {
        m_pGameRun->init();
    }
    if(m_pGameEnd) {
        m_pGameEnd->init();
    }
}

void IMIGameBase::destroy() {
    stopListen();
    if (m_pGameReady) {
        m_pGameReady->destroy();
    }
    if (m_pGameRun) {
        m_pGameRun->destroy();
    }
    if (m_pGameEnd) {
        m_pGameEnd->destroy();
    }
    IMIModuleBase::destroy();
}

void IMIGameBase::update(f32 _dt) {
    if(m_stage == E_G_STAGE_WAIT) {
    }
    //开始
    if(m_stage == E_G_STAGE_BEGIN) {
        if(m_pGameReady) {
            //准备逻辑
            if( m_pGameReady->isEnd() ) {
                m_stage = E_G_STAGE_RUN;
                m_pGameReady->exit();
                if(m_pGameRun) {
                    m_pGameRun->enter();
                }
            }else{
                m_pGameReady->update(_dt);
            }
        }else{
            //无准备
            m_stage = E_G_STAGE_RUN;
            if(m_pGameRun) {
                m_pGameRun->enter();
            }
        }
    }
    //循环
    if(m_stage == E_G_STAGE_RUN) {
        if(m_pGameRun) {
            if( m_pGameRun->isEnd() ) {
                m_stage = E_G_STAGE_END;
                m_pGameRun->exit();
                if(m_pGameEnd){
                    m_pGameEnd->enter();
                }
            }else{
                m_pGameRun->update(_dt);
            }
        }else{
            m_stage = E_G_STAGE_END;
            if(m_pGameEnd){
                m_pGameEnd->enter();
            }
        }
    }
    //结束
    if(m_stage == E_G_STAGE_END) {
        if(m_pGameEnd){
            if( m_pGameEnd->isEnd() ) {
                m_stage = E_G_STAGE_WAIT;
                m_pGameEnd->exit();
            }else{
                m_pGameEnd->update(_dt);
            }
        }else{
            m_stage = E_G_STAGE_WAIT;
        }
    }
}

void IMIGameBase::open() {
    IMIModuleBase::open();
    if(m_stage == E_G_STAGE_WAIT) {
        m_stage = E_G_STAGE_BEGIN;
        if(m_pGameReady){
            m_pGameReady->enter();
        }
    }
}

void IMIGameBase::close() {
    IMIModuleBase::close();
    if(m_stage != E_G_STAGE_WAIT) {
        m_stage = E_G_STAGE_WAIT;
        if(m_pGameReady) {
            m_pGameReady->exit();
        }
        if(m_pGameRun){
            m_pGameRun->exit();
        }
        if(m_pGameEnd){
            m_pGameEnd->exit();
        }
    }
}

bool IMIGameBase::procEvent(IMIEventPtr _event){
    return true;
}



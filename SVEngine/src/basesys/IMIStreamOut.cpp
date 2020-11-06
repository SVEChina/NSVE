//
// IMIStreamOut.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIStreamOut.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalMgr.h"
#include "../work/IMITdCore.h"
#include "../basesys/IMIScene.h"
#include "../node/IMIFrameOutTex.h"
#include "../basesys/IMISceneMgr.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIStreamOut::IMIStreamOut(IMIInstPtr _app)
:IMIProcess(_app){
    m_lock = MakeSharedPtr<IMILock>();
    m_missionlock = MakeSharedPtr<IMILock>();
    m_pFrameOut = nullptr;
#if defined(IMI_IOS)
    m_outMethod = E_OUT_M_IOS;
#elif defined(IMI_ANDROID)
    m_outMethod = E_OUT_M_ANDRIOD;
#else
     m_outMethod = E_OUT_M_READPIEXL;
#endif
    m_outWidth = 0;
    m_outHeight = 0;
    m_outFormat = IMI_OUT_STEAM_RGB2YUVI420;
}

IMIStreamOut::~IMIStreamOut() {
    m_lock = nullptr;
    m_missionlock = nullptr;
    m_pFrameOut = nullptr;
    m_mission.destroy();
}

//打开输出流
bool IMIStreamOut::openOutStream() {
//    if(m_pFrameOut) {
//        return false;
//    }
//    if(m_outWidth == 0) {
//        m_outWidth = mApp->m_global_param.sv_width;
//    }
//    if(m_outHeight == 0) {
//        m_outHeight = mApp->m_global_param.sv_height;
//    }
//    //根据当前类型 打开输出流
//    if( m_outMethod == E_OUT_M_NULL) {
//        IMI_LOG_INFO("please set outstream type! \n");
//        return false;
//    }else if( m_outMethod == E_OUT_M_READPIEXL) {
////        IMIFrameOutReadPtr t_streamNode = MakeSharedPtr<IMIFrameOutRead>(mApp);
////        if(t_streamNode) {
////            t_streamNode->create(m_outWidth,m_outHeight);
////            t_streamNode->setFormat(m_outFormat);
////        }
////        m_pFrameOut = t_streamNode;
//    }else if( m_outMethod == E_OUT_M_MAP) {
//
//    }else if( m_outMethod == E_OUT_M_PBO) {
//
//    }else if( m_outMethod == E_OUT_M_IOS) {
//#ifdef IMI_IOS
//        IMIFrameOutIOSPtr t_streamNode = MakeSharedPtr<IMIFrameOutIOS>(mApp);
//        if( t_streamNode ) {
//            t_streamNode->init(m_outFormat,m_outWidth,m_outHeight);
//        }
//        m_pFrameOut = t_streamNode;
//#endif
//    }else if( m_outMethod == E_OUT_M_ANDRIOD) {
//#ifdef IMI_ANDROID
//        m_pFrameOut = MakeSharedPtr<IMIFrameOutTex>(mApp);
//#endif
//    }
//    if(m_pFrameOut) {
//        return true;
//    }
    return false;
}

//关闭输出输出流
void IMIStreamOut::closeOutStream() {
}

bool IMIStreamOut::isOpen() {
    if(m_pFrameOut) {
        return true;
    }
    return false;
}

s32 IMIStreamOut::getOutWidth() {
    return m_outWidth;
}

s32 IMIStreamOut::getOutHeight() {
    return m_outHeight;
}

s32 IMIStreamOut::getOutFormat() {
    return m_outFormat;
}

void IMIStreamOut::lockData() {
    if(m_pFrameOut) {
        m_pFrameOut->lockData();
    }
}

void IMIStreamOut::unlockData() {
    if(m_pFrameOut) {
        m_pFrameOut->unlockData();
    }
}

void* IMIStreamOut::getOutData() {
    if(m_pFrameOut) {
        return m_pFrameOut->getData();
    }
    return nullptr;
}

//改变输出流方式
void IMIStreamOut::setOutMethod(OUTMETHOD _method) {
    //如果是打开状态
    if( isOpen() ) {
        changeOutMethod(_method);
    }else {
        m_outMethod = _method;
    }
}

void IMIStreamOut::setOutSize(s32 _width,s32 _height) {
    m_outWidth = _width;
    m_outHeight = _height;
}

void IMIStreamOut::setOutFormat(IMI_OUTSTEAMFORMATE _format) {
    m_outFormat = _format;
}

//改变输出流方式
void IMIStreamOut::changeOutMethod(OUTMETHOD _method) {
    if( isOpen() ) {
        m_outMethod = _method;
    }
}

//
void IMIStreamOut::_refreshOutStream() {
}

//
void IMIStreamOut::createOutStream(cptr8 _name, s32 _type, s32 _format, s32 _width, s32 _height, RENDERSTREAMTYPE _steamType) {
//    if(_type == 0){
//#ifdef IMI_IOS
//        m_pFrameOut = MakeSharedPtr<IMIFrameOutIOS>(mApp);
//        IMIFrameOutIOSPtr t_streamNode = std::dynamic_pointer_cast<IMIFrameOutIOS>(m_pFrameOut);
//        if( t_streamNode ) {
//            s32 _w = mApp->m_global_param.sv_width;
//            s32 _h = mApp->m_global_param.sv_height;
//            if (_width !=0 && _height != 0) {
//                _w = _width;
//                _h = _height;
//            }
//            t_streamNode->init(IMI_OUTSTEAMFORMATE(_format),_w,_h);
//            t_streamNode->setRSType(_steamType);
//        }
//#endif
//    }else if(_type == 1){
//#ifdef IMI_ANDROID
//        m_pFrameOut = MakeSharedPtr<IMIFrameOutTex>(mApp);
//        IMIFrameOutTexPtr t_streamNode = std::dynamic_pointer_cast<IMIFrameOutTex>(m_pFrameOut);
//#endif
//    }
}

void IMIStreamOut::destroyOutStream() {
    if(m_pFrameOut) {
        m_pFrameOut = nullptr; 
    }
}

void IMIStreamOut::active() {
    IMIScenePtr t_sc = mApp->getSceneMgr()->getScene();
    if(t_sc && m_pFrameOut){
        t_sc->addNode(m_pFrameOut);
    }
}

void IMIStreamOut::unactive() {
}

/*************************输出任务***************************/
s32 IMIStreamOut::getTexId(){
//    IMIFrameOutTexPtr t_streamNode = std::dynamic_pointer_cast<IMIFrameOutTex>(m_pFrameOut);
//    if(t_streamNode){
//        return  t_streamNode->getTexId();
//    }
    return 0;
}

void IMIStreamOut::setStreamOutCB(cb_out_stream _cb) {
//#ifdef IMI_IOS
//    m_lock->lock();
//    m_pOutStreamCB = _cb;
//    if( m_pFrameOut && m_pOutStreamCB) {
//        IMIFrameOutIOSPtr t_streamNode = std::dynamic_pointer_cast<IMIFrameOutIOS>(m_pFrameOut);
//        t_streamNode->setCallback(m_pOutStreamCB);
//    }
//    m_lock->unlock();
//#endif
}

//输出
void IMIStreamOut::output() {
    m_missionlock->lock();
    for(s32 i=0; i<m_mission.size();) {
        m_mission[i]->output();
        if( m_mission[i]->isEnd() ) {
            m_mission[i]->sendEnd();
            m_mission.removeForce(i);
        }else{
            i++;
        }
    }
    m_missionlock->unlock();
}

void IMIStreamOut::addOutMission(IMIOutMissionPtr _mission) {
    m_missionlock->lock();
    for(s32 i=0; i<m_mission.size(); i++) {
        IMIString t_name = m_mission[i]->getMissionName();
        if( t_name == _mission->getMissionName() ) {
            m_mission.remove(i);
            goto addOutMission_end;
        }
    }
    //
    m_mission.append(_mission);
    //
    addOutMission_end:
    m_missionlock->unlock();
}

void IMIStreamOut::delOutMission(cptr8 _name) {
    m_missionlock->lock();
    for(s32 i=0; i<m_mission.size(); i++) {
        IMIString t_name = m_mission[i]->getMissionName();
        if( t_name == _name ) {
            m_mission.remove(i);
            goto delOutMission_end;
        }
    }
delOutMission_end:
    m_missionlock->unlock();
}

void IMIStreamOut::clearAllMission() {
    m_missionlock->lock();
    m_mission.clear();
    m_mission.destroy();
    m_missionlock->unlock();
}

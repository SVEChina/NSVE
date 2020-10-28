//
// SVPerson.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVPerson.h"
#include "SVTrackerFace.h"
#include "SVDetectMgr.h"
#include "SVDetectST.h"

using namespace sv;

SVPerson::SVPerson(SVInstPtr _app)
:SVListenBase(_app){
    m_facePtNum = 0;
    m_personID = 0;
    m_exist = false;
    m_detectType = DETECT_T_NULL;
    m_pTracker = MakeSharedPtr<SVTrackerFace>(mApp);
    m_pOFaceData= new f32[MAX_FACE_PT_NUM * 2];
    memset(m_pOFaceData, 0, sizeof(f32) * 2 * MAX_FACE_PT_NUM);
    m_pFaceData= new f32[MAX_FACE_PT_NUM * 2];
    memset(m_pFaceData, 0, sizeof(f32) * 2 * MAX_FACE_PT_NUM);
}

SVPerson::~SVPerson() {
    m_pTracker = nullptr;
    if (m_pOFaceData) {
        delete m_pOFaceData;
    }
    if (m_pFaceData) {
        delete m_pFaceData;
    }
}

void SVPerson::update(f32 _dt) {
    if(!m_pTracker){
        return;
    }
    m_dataLock.lock();
    if(m_detectType == DETECT_T_AS){
        
    }else if(m_detectType == DETECT_T_FP){
        
    }else if(m_detectType == DETECT_T_ST){
        m_pTracker->track_st(m_pFaceData,
                             m_facePtNum,
                             m_facerect,
                             m_facerot.x,
                             m_facerot.y,
                             m_facerot.z,
                             m_personID);
    }
    m_dataLock.unlock();
}

void SVPerson::setPersonID(s32 _id){
    m_personID = _id;
}

s32 SVPerson::getPersonID() {
    return m_personID;
}

void SVPerson::setDetectType(DETECTTYPE type) {
    if (m_detectType != type) {
        //去掉原来的监听
        SVDetectBasePtr t_detect = mApp->getDetectMgr()->getDetect();
        t_detect->unregistListenFunc(this, &SVObject::listenData);
        //增加新的监听
        m_detectType = type;
        t_detect->registListenFunc(this, &SVObject::listenData);
    }
}

void SVPerson::_setFaceData(void* _pdata,s32 _len) {
    if(_len>0 && _len<sizeof(f32)*2*MAX_FACE_PT_NUM) {
        m_dataLock.lock();
        memcpy(m_pOFaceData, _pdata, _len);
        m_dataLock.unlock();
    }
}

void SVPerson::_setFaceRect(f32 _left,f32 _top,f32 _right,f32 _bottom){
    m_dataLock.lock();
    m_facerect.m_lb_pt.x = _left;
    m_facerect.m_lb_pt.y = _top;
    m_facerect.m_rt_pt.x = _right;
    m_facerect.m_rt_pt.y = _bottom;
    m_dataLock.unlock();
}

SVRect SVPerson::getFaceRect(){
    return m_facerect;
}

void SVPerson::_setFaceRot(f32 _yaw,f32 _pitch,f32 _roll){
    m_dataLock.lock();
    m_facerot.x = _pitch;
    m_facerot.y = _yaw;
    m_facerot.z = _roll;
    m_dataLock.unlock();
}

FVec3 SVPerson::getFaceRot(){
    return m_facerot;
}

f32 *SVPerson::getFaceData(s32 &_ptNum, SV_E_FACEDATA_TYPE _type) {
    if (_type == SV_E_FACEDATA_SCENE) {
        _ptNum = m_facePtNum;
        _transDataToCener(m_pOFaceData, m_pFaceData);
        return m_pFaceData;
    }else if(_type == SV_E_FACEDATA_SCREEN){
        _ptNum = m_facePtNum;
        return m_pOFaceData;
    }
    return nullptr;
}

f32 SVPerson::getFaceDataX(s32 _index) {
    if (_index >= 0 && _index < m_facePtNum) {
        return m_pFaceData[2 * _index];
    }
    return 0.0f;
}

f32 SVPerson::getFaceDataY(s32 _index) {
    if (_index >= 0 && _index < m_facePtNum) {
        return m_pFaceData[2 * _index + 1];
    }
    return 0.0f;
}

s32 SVPerson::getFacePtNum() {
    return m_facePtNum;
}

SVTrackerFacePtr SVPerson::getTracker() {
    return m_pTracker;
}

void SVPerson::listenData(SVObjectPtr datagen) {
    m_dirty = true;
    if (m_detectType == DETECT_T_AS) {
        
    } else if (m_detectType == DETECT_T_ST) {
        m_facePtNum = 106;
        SVDetectSTPtr t_detectST = std::dynamic_pointer_cast<SVDetectST>(datagen);
        if (t_detectST) {
            _listenData_ST(t_detectST);
        }
    } else if (m_detectType == DETECT_T_FP) {
        
    }
    m_dirty = false;
}

void SVPerson::_listenData_ST(SVDetectSTPtr detect) {
    PERSON_STDATA *personData = detect->getData(m_personID);
    if (!personData)
        return;
    if (!personData->has){
        //开始做数据更新
        _setExist(false);
        _setFaceRot(0, 0, 0);
        _setFaceRect(0, 0, 0, 0);
    } else {
        //开始做数据更新
        _setExist(true);
        _setFaceRot(personData->yaw, personData->pitch, personData->roll);
        _setFaceRect(personData->rectleft, personData->recttop, personData->rectright, personData->rectbottom);
        _setFaceData(personData->pointdata, sizeof(f32) * 2 * ST_POINT_NUM);
        if (m_pTracker) {
            m_pTracker->track_st(m_pFaceData, m_facePtNum, m_facerect, m_facerot.y, m_facerot.x, m_facerot.z, m_personID);
        }
    }
    //通知其他监听者更新数据
    _notice(0);
}

void SVPerson::_transDataToCener(f32 *_pOData, f32 *_pData){
    memcpy(_pData, _pOData, m_facePtNum*2*sizeof(f32));
    f32 t_camera_half_w = mApp->m_global_param.sv_width*0.5f;
    f32 t_camera_half_h = mApp->m_global_param.sv_height*0.5f;
    for (s32 i=0; i<m_facePtNum; i++) {
        _pData[2*i] = (_pOData[2*i] - t_camera_half_w);
        _pData[2*i+1] =  (t_camera_half_h - _pOData[2*i+1]);
    }
}

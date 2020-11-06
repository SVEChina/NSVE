//
// IMIPerson.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIPerson.h"
#include "IMITrackerFace.h"
#include "IMIDetectMgr.h"
#include "IMIDetectST.h"
#include "IMIKeyPointExt.h"
using namespace imi;

IMIPerson::IMIPerson(IMIInstPtr _app)
:IMIListenBase(_app){
    m_facePtNum = 0;
    m_personID = 0;
    m_exist = false;
    m_detectType = DETECT_T_NULL;
    m_face_attribute.mouth_noise_ratio = 0.80f;
    m_face_attribute.tip_thickness_ratio = 0.80f;
    m_face_attribute.eyes_down_ratio = 1.00f;
    m_face_attribute.eyes_in_corner_ratio = 0.20f;
    m_face_attribute.eyes_out_corner_ratio = 0.20f;
    m_pTracker = MakeSharedPtr<IMITrackerFace>(mApp);
    m_pFaceData= new f32[MAX_FACE_PT_NUM * 2];
    memset(m_pFaceData, 0, sizeof(f32) * 2 * MAX_FACE_PT_NUM);
    m_pFaceDataTuned= new f32[MAX_FACE_PT_NUM * 2];
    memset(m_pFaceDataTuned, 0, sizeof(f32) * 2 * MAX_FACE_PT_NUM);
    m_pFaceDataExt= new f32[MAX_FACE_PT_NUM * 2];
    memset(m_pFaceDataExt, 0, sizeof(f32) * 2 * MAX_FACE_PT_NUM);
    
}

IMIPerson::~IMIPerson() {
    m_pTracker = nullptr;
    if (m_pFaceData) {
        delete m_pFaceData;
    }
    if (m_pFaceDataTuned) {
        delete m_pFaceDataTuned;
    }
    if (m_pFaceDataExt) {
        delete m_pFaceDataExt;
    }
}

void IMIPerson::update(f32 _dt) {
    if(!m_pTracker){
        return;
    }
    m_dataLock.lock();
    if(m_detectType == DETECT_T_AS){
        
    }else if(m_detectType == DETECT_T_FP){
        
    }else if(m_detectType == DETECT_T_ST){
//        m_pTracker->track_st(m_pFaceData,
//                             m_facePtNum,
//                             m_facerect,
//                             m_facerot.x,
//                             m_facerot.y,
//                             m_facerot.z,
//                             m_personID);
    }
    m_dataLock.unlock();
}

void IMIPerson::setPersonID(s32 _id){
    m_personID = _id;
}

s32 IMIPerson::getPersonID() {
    return m_personID;
}

void IMIPerson::setDetectType(DETECTTYPE type) {
    if (m_detectType != type) {
        //去掉原来的监听
        IMIDetectBasePtr t_detect = mApp->getDetectMgr()->getDetect();
        t_detect->unregistListenFunc(this, &IMIObject::listenData);
        //增加新的监听
        m_detectType = type;
        t_detect->registListenFunc(this, &IMIObject::listenData);
    }
}

void IMIPerson::_setFaceData(void* _pdata,s32 _len) {
    if(_len>0 && _len<sizeof(f32)*2*MAX_FACE_PT_NUM) {
        m_dataLock.lock();
        memcpy(m_pFaceData, _pdata, _len);
        m_dataLock.unlock();
    }
}

void IMIPerson::_setFaceRect(f32 _left,f32 _top,f32 _right,f32 _bottom){
    m_dataLock.lock();
    m_facerect.m_lb_pt.x = _left;
    m_facerect.m_lb_pt.y = _top;
    m_facerect.m_rt_pt.x = _right;
    m_facerect.m_rt_pt.y = _bottom;
    m_dataLock.unlock();
}

IMIRect& IMIPerson::getFaceRect(){
    return m_facerect;
}

void IMIPerson::_setFaceRot(f32 _yaw,f32 _pitch,f32 _roll){
    m_dataLock.lock();
    m_facerot.x = _pitch;
    m_facerot.y = _yaw;
    m_facerot.z = _roll;
    m_dataLock.unlock();
}

FVec3& IMIPerson::getFaceRot(){
    return m_facerot;
}

f32 *IMIPerson::getFaceData(s32 &_ptNum, IMI_E_FACEDATA_TYPE _type,  bool _isTuned){
    f32 *t_tarFaceData;
    if (_isTuned) {
        s32 t_ptNum = 0;
        _transDataToFaceTune(m_pFaceData, m_facePtNum, m_pFaceDataTuned, t_ptNum);
        t_tarFaceData = m_pFaceDataTuned;
    }else{
        t_tarFaceData = m_pFaceData;
    }
    if (_type == IMI_E_FACEDATA_SIMPLITY) {
        _ptNum = m_facePtNum;
        return t_tarFaceData;
    }else if(_type == IMI_E_FACEDATA_BROW){
        _transDataToBrow(t_tarFaceData, m_facePtNum, m_pFaceDataExt, _ptNum);
        return m_pFaceDataExt;
    }else if(_type == IMI_E_FACEDATA_EYE){
        _transDataToEye(t_tarFaceData, m_facePtNum, m_pFaceDataExt, _ptNum);
        return m_pFaceDataExt;
    }else if(_type == IMI_E_FACEDATA_TUNED){
        _transDataToTuned(m_pFaceData, t_tarFaceData, m_pFaceDataExt, _ptNum);
        return m_pFaceDataExt;
    }
    return nullptr;
}

IMITrackerFacePtr IMIPerson::getTracker() {
    return m_pTracker;
}

void IMIPerson::listenData(IMIObjectPtr datagen) {
    m_dirty = true;
    if (m_detectType == DETECT_T_AS) {
        
    } else if (m_detectType == DETECT_T_ST) {
        m_facePtNum = ST_POINT_NUM;
        IMIDetectSTPtr t_detectST = std::dynamic_pointer_cast<IMIDetectST>(datagen);
        if (t_detectST) {
            _listenData_ST(t_detectST);
        }
    } else if (m_detectType == DETECT_T_FP) {
        
    }
    m_dirty = false;
}

void IMIPerson::_listenData_ST(IMIDetectSTPtr detect) {
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
//        if (m_pTracker) {
//            m_pTracker->track_st(m_pFaceData, m_facePtNum, m_facerect, m_facerot.y, m_facerot.x, m_facerot.z, m_personID);
//        }
    }
    //通知其他监听者更新数据
    _notice(0);
}

void IMIPerson::_transDataToScene(f32 *_pInData, s32 _inNum, f32 *_pOutData){
    f32 t_camera_half_w = mApp->m_global_param.sv_width*0.5f;
    f32 t_camera_half_h = mApp->m_global_param.sv_height*0.5f;
    for (s32 i=0; i<_inNum; i++) {
        _pOutData[2*i] = (_pInData[2*i] - t_camera_half_w);
        _pOutData[2*i+1] =  (t_camera_half_h - _pInData[2*i+1]);
    }
}

void IMIPerson::_transDataToBrow(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum){
    IMIKeyPointExt::faceDataForEyeBrow(_pInData, _pOutData, _outNum);
}

void IMIPerson::_transDataToEye(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum){
    IMIKeyPointExt::faceDataForEyes(_pInData, _pOutData, _outNum);
}

void IMIPerson::_transDataToFaceTune(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum){
    IMIKeyPointExt::IMI_S_FACETUNE_RATIO t_tuneRatio = (IMIKeyPointExt::IMI_S_FACETUNE_RATIO&)m_face_attribute;
    IMIKeyPointExt::faceDataForFaceTune(t_tuneRatio, _pInData, _inNum, _pOutData, _outNum);
}

void IMIPerson::_transDataToTuned(f32 *_pInData, f32 *_pInTuneData, f32 *_pOutData, s32 &_outNum){
    IMIKeyPointExt::faceDataForTune(_pInTuneData, _pInData, _pOutData, _outNum);
}

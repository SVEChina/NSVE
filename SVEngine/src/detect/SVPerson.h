//
// SVPerson.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_PERSON_H
#define SV_PERSON_H

#include "../base/SVListenBase.h"
#include "../base/SVRect.h"
#include "../base/SVVec3.h"
#include "../base/SVDatatDef.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVTrackerFace.h"

//最大支持面部400个点
#define MAX_FACE_PT_NUM 400

namespace sv {
    enum SV_E_FACEDATA_TYPE{
        SV_E_FACEDATA_NULL = 0,
        SV_E_FACEDATA_SCREEN,//屏幕坐标系下的原始人脸识别数据
        SV_E_FACEDATA_SCENE//场景坐标系下的原始人脸识别数据
        //    SV_E_FACEDATA_SCREEN_EXT//屏幕坐标系下补过点的数据
    };
    class SVPerson : public SVListenBase {
    public:
        SVPerson(SVInstPtr _app);
        
        ~SVPerson();
        
        SVTrackerFacePtr getTracker();
        
        void setDetectType(DETECTTYPE type);
        
        void update(f32 _dt);
        
        virtual void listenData(SVObjectPtr datagen);
        
        SVRect getFaceRect();
        
        FVec3 getFaceRot();
        
        f32 *getFaceData(s32 &_ptNum, SV_E_FACEDATA_TYPE _type);
        
        f32 getFaceDataX(s32 _index);
        
        f32 getFaceDataY(s32 _index);
        
        s32 getFacePtNum();
        
        bool getExist(){ return m_exist; }
        
        void setPersonID(s32 _id);
        
        s32  getPersonID();
        
    protected:
        void _setExist(bool _exist){ m_exist = _exist; }
        void _setFaceRot(f32 _yaw,f32 _pitch,f32 _roll);
        void _setFaceRect(f32 _left,f32 _top,f32 _right,f32 _bottom);
        void _setFaceData(void* _pdata,s32 _len);
        void _listenData_ST(SVDetectSTPtr detect);
        void _transDataToCener(f32 *_pOData, f32 *_pData);
        bool m_dirty;
        SVTrackerFacePtr m_pTracker;
        DETECTTYPE m_detectType;    //识别数据类型
        bool m_exist;
        s32 m_personID;
        s32 m_facePtNum; //识别面部顶点数
        f32 *m_pFaceData;//识别数据
        f32 *m_pOFaceData;//原始识别数据
        FVec3 m_facerot;
        SVRect m_facerect;
        SVLock m_dataLock;
    };
        
}//!namespace sv



//
#endif //SV_PERSON_H

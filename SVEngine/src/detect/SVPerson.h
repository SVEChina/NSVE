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

//最大支持面部400个点
#define MAX_FACE_PT_NUM 400

namespace sv {
    enum SV_E_FACEDATA_TYPE{
        SV_E_FACEDATA_NULL = 0,
        SV_E_FACEDATA_ORIGINAL,//屏幕坐标系下的原始人脸识别数据
        SV_E_FACEDATA_SIMPLITY,//场景坐标系下的原始人脸识别数据
        SV_E_FACEDATA_FACETUNE,//场景坐标系下微整形过的人脸识别数据
        SV_E_FACEDATA_BROW,//场景坐标系下眉毛部位数据
        SV_E_FACEDATA_EYE,//场景坐标系下眼睛部位数据
        SV_E_FACEDATA_TUNE//场景坐标系下微整形的数据
        //    SV_E_FACEDATA_SCREEN_EXT//屏幕坐标系下补过点的数据
    };

    struct SV_S_FACE_ATTRIBUTE{
        f32 mouth_noise_ratio;//嘴到人中比例
        f32 tip_thickness_ratio;//嘴唇厚度
        f32 eyes_down_ratio;//眼睑下至
        f32 eyes_in_corner_ratio;//内眼角
        f32 eyes_out_corner_ratio;//外眼角
    };

    class SVPerson : public SVListenBase {
    public:
        SVPerson(SVInstPtr _app);
        
        ~SVPerson();
        
        SVTrackerFacePtr getTracker();
        
        void setDetectType(DETECTTYPE type);
        
        void update(f32 _dt);
        
        virtual void listenData(SVObjectPtr datagen);
        
        void setPersonID(s32 _id);
        
        s32  getPersonID();
        
        bool getExist(){ return m_exist; }
        
        SVRect& getFaceRect();
        
        FVec3& getFaceRot();
        
        f32 *getFaceData(s32 &_ptNum, SV_E_FACEDATA_TYPE _type);
        
    protected:
        void _setExist(bool _exist){ m_exist = _exist; }
        void _setFaceRot(f32 _yaw,f32 _pitch,f32 _roll);
        void _setFaceRect(f32 _left,f32 _top,f32 _right,f32 _bottom);
        void _setFaceData(void* _pdata,s32 _len);
        void _listenData_ST(SVDetectSTPtr detect);
        //
        void _transDataToScene(f32 *_pInData, s32 _inNum, f32 *_pOutData);
        void _transDataToBrow(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToEye(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToFaceTune(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToTune(f32 *_pInData, f32 *_pInTuneData, f32 *_pOutData, s32 &_outNum);
        //
        bool m_dirty;
        SVTrackerFacePtr m_pTracker;
        DETECTTYPE m_detectType;    //识别数据类型
        SV_S_FACE_ATTRIBUTE m_face_attribute;
        bool m_exist;
        s32 m_personID;
        s32 m_facePtNum; //识别面部顶点数
        f32 *m_pFaceDataScreen;//原始识别数据
        f32 *m_pFaceDataScene;//场景坐标系识别数据
        f32 *m_pFaceDataTune;//场景坐标系下微整形的数据
        f32 *m_pFaceDataExt;//
        FVec3 m_facerot;
        SVRect m_facerect;
        SVLock m_dataLock;
    };
        
}//!namespace sv



//
#endif //SV_PERSON_H

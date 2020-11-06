//
// IMIPerson.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PERSON_H
#define IMI_PERSON_H

#include "../base/IMIListenBase.h"
#include "../base/IMIRect.h"
#include "../base/IMIVec3.h"
#include "../base/IMIDatatDef.h"
#include "../app/IMIInst.h"
#include "../work/IMITdCore.h"

//最大支持面部400个点
#define MAX_FACE_PT_NUM 400

namespace imi {
    enum IMI_E_FACEDATA_TYPE{
        IMI_E_FACEDATA_SIMPLITY = 1,//全脸的数据
        IMI_E_FACEDATA_BROW,//眉毛部位数据
        IMI_E_FACEDATA_EYE,//眼睛部位数据
        IMI_E_FACEDATA_TUNED//微整形部位的数据
    };

    struct IMI_S_FACE_ATTRIBUTE{
        f32 mouth_noise_ratio;//嘴到人中比例
        f32 tip_thickness_ratio;//嘴唇厚度
        f32 eyes_down_ratio;//眼睑下至
        f32 eyes_in_corner_ratio;//内眼角
        f32 eyes_out_corner_ratio;//外眼角
    };

    class IMIPerson : public IMIListenBase {
    public:
        IMIPerson(IMIInstPtr _app);
        
        ~IMIPerson();
        
        IMITrackerFacePtr getTracker();
        
        void setDetectType(DETECTTYPE type);
        
        void update(f32 _dt);
        
        virtual void listenData(IMIObjectPtr datagen);
        
        void setPersonID(s32 _id);
        
        s32  getPersonID();
        
        bool getExist(){ return m_exist; }
        
        IMIRect& getFaceRect();
        
        FVec3& getFaceRot();
        
        f32 *getFaceData(s32 &_ptNum, IMI_E_FACEDATA_TYPE _type, bool _isTuned = false);
    protected:
        void _setExist(bool _exist){ m_exist = _exist; }
        void _setFaceRot(f32 _yaw,f32 _pitch,f32 _roll);
        void _setFaceRect(f32 _left,f32 _top,f32 _right,f32 _bottom);
        void _setFaceData(void* _pdata,s32 _len);
        void _listenData_ST(IMIDetectSTPtr detect);
        //
        void _transDataToScene(f32 *_pInData, s32 _inNum, f32 *_pOutData);
        void _transDataToBrow(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToEye(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToFaceTune(f32 *_pInData, s32 _inNum, f32 *_pOutData, s32 &_outNum);
        void _transDataToTuned(f32 *_pInData, f32 *_pInTuneData, f32 *_pOutData, s32 &_outNum);
        //
        bool m_dirty;
        IMITrackerFacePtr m_pTracker;
        DETECTTYPE m_detectType;    //识别数据类型
        IMI_S_FACE_ATTRIBUTE m_face_attribute;
        bool m_exist;
        s32 m_personID;
        s32 m_facePtNum; //识别面部顶点数
        f32 *m_pFaceData;//原始识别数据
        f32 *m_pFaceDataTuned;
        f32 *m_pFaceDataExt;//
        FVec3 m_facerot;
        IMIRect m_facerect;
        IMILock m_dataLock;
    };
        
}//!namespace imi



//
#endif //IMI_PERSON_H

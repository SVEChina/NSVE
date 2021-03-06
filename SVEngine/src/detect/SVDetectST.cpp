//
// SVDetectST.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVDetectST.h"
#include "SVPerson.h"
#include "../basesys/SVConfig.h"

using namespace sv;

SVDetectST::SVDetectST(SVInstPtr _app)
:SVDetectBase(_app) {
     memset(stData, 0, SUPPORT_MAX_PERSON_NUM * sizeof(PERSON_STDATA));
}

SVDetectST::~SVDetectST() {
}

void SVDetectST::pushData(void *_faceData){
    _parseData(_faceData);
    //将数据分解到person上
}

void SVDetectST::_parseData(void *data) {
    if (!data)
        return;
    m_listenDirty = true;
    //解析人脸数目
    int t_facecount = 0;
    memcpy(&t_facecount, data, sizeof(int));
    char *t_stream = (char *) data;
    t_stream += sizeof(s32);
    
    for (s32 i = 0; i < SUPPORT_MAX_PERSON_NUM; i++) {
        stData[i].has = false;
    }
    char *t_data_point = (char *) t_stream;
    for (s32 i = 0; i < t_facecount; i++) {
        stData[i].has = true;
        //rotate
        size_t off_len = sizeof(f32);
        memcpy(&stData[i].yaw, t_data_point, off_len);
        t_data_point += off_len;
        memcpy(&stData[i].pitch, t_data_point, off_len);
        t_data_point += off_len;
        memcpy(&stData[i].roll, t_data_point, off_len);
        t_data_point += off_len;
        //rect
        off_len = sizeof(s32);
        memcpy(&stData[i].rectleft, t_data_point, off_len);
        t_data_point += off_len;
        
        memcpy(&stData[i].recttop, t_data_point, off_len);
        t_data_point += off_len;
        
        memcpy(&stData[i].rectright, t_data_point, off_len);
        t_data_point += off_len;
        
        memcpy(&stData[i].rectbottom, t_data_point, off_len);
        t_data_point += off_len;

        s32 data_len = sizeof(f32) * 2 * ST_POINT_NUM;
        memcpy(stData[i].pointdata,t_data_point, data_len);
        t_data_point+=data_len;
    }
}

PERSON_STDATA *SVDetectST::getData(s32 _personid) {
    if (_personid >= 1 && _personid <= SUPPORT_MAX_PERSON_NUM)
        return &(stData[_personid - 1]);
    return nullptr;
}

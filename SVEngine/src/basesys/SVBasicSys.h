//
// SVBasicSys.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_BASICSYS_H
#define SV_BASICSYS_H

#include "SVSysBase.h"

namespace sv{
    
    class SVBasicSys : public SVSysBase {
    public:
        SVBasicSys(SVInstPtr _app);
        
        ~SVBasicSys();
        
        void init();
        
        void destroy();
        
        void update(f32 dt);
        
        void output();
        
        void loadDefaultFMFont();
        
        //回收模块
        SVRecycleProcessPtr getRecycleModule();
        
        //拾取模块
        SVPickProcessPtr getPickModule();
        
        //字体模块
        SVFontProcessPtr getFontModule();
        
        //流入
        SVStreamInPtr getStreamIn();
        
        //流出
        SVStreamOutPtr getStreamOut();
        
        //图片处理
        SVPictureProcessPtr getPicProc();
        
        //传感器数据处理 
        SVSensorProcessPtr getSensorModule();

    protected:
        SVStreamInPtr m_stream_in;
        
        SVStreamOutPtr m_stream_out;
        
        SVPictureProcessPtr m_pic_proc;

        SVRecycleProcessPtr m_pRecycleModule;
        
        SVPickProcessPtr m_picker;

        SVFontProcessPtr m_fonter;

        SVSensorProcessPtr m_sensor;
    };

}//!namespace sv





#endif //SV_BASICSYS_H

//
// IMIStreamOut.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_STREAMOUT_H
#define IMI_STREAMOUT_H

#include "IMIProcess.h"
#include "../node/IMINodeDeclare.h"
#include "out/IMIOutMission.h"
#include "../base/IMIArray.h"
#include "../rendercore/IMIRenderDef.h"

namespace imi {

    enum OUTMETHOD{
        E_OUT_M_NULL = 0,
        E_OUT_M_READPIEXL,
        E_OUT_M_MAP,
        E_OUT_M_PBO,
        E_OUT_M_IOS,
        E_OUT_M_ANDRIOD
    };
    
    class IMIStreamOut : public IMIProcess {
    public:
        IMIStreamOut(IMIInstPtr _app);
        
        ~IMIStreamOut();
        
        //打开输出流
        bool openOutStream();
        
        //关闭输出输出流
        void closeOutStream();
        
        bool isOpen();
        
        //改变输出流方式
        void changeOutMethod(OUTMETHOD _method);
        
        void setOutMethod(OUTMETHOD _method);
        
        void setOutSize(s32 _width,s32 _height);
        
        void setOutFormat(IMI_OUTSTEAMFORMATE _format);
        
        //加了个StreamType,控制对外输出到哪个流。默认RST_DATATRANS这个流
        void createOutStream(cptr8 _name, s32 _type, s32 _format, s32 _width, s32 _height, RENDERSTREAMTYPE _steamType = RST_DATATRANS);
        
        void destroyOutStream();
        
        void active();
        
        void unactive();

        s32 getTexId();
        
        void setStreamOutCB(cb_out_stream _cb);
        
        void output();
        
        s32 getOutWidth();
        
        s32 getOutHeight();
        
        s32 getOutFormat();
        
        void lockData();
        
        void* getOutData();
        
        void unlockData();
        
    protected:
        void _refreshOutStream();
        
        OUTMETHOD m_outMethod;
        
        s32 m_outWidth;
        
        s32 m_outHeight;
        
        IMI_OUTSTEAMFORMATE m_outFormat;
        
        IMIFrameOutNodePtr m_pFrameOut;

        cb_out_stream m_pOutStreamCB;
        
        IMILockPtr m_lock;
        
    public:
        void addOutMission(IMIOutMissionPtr _mission);
        
        void delOutMission(cptr8 _name);
        
        void clearAllMission();
        
    protected:
        IMILockPtr m_missionlock;
        typedef IMIArray<IMIOutMissionPtr> MISSIONPOOL;
        MISSIONPOOL m_mission;
    };
    
    

}//!namespace imi



#endif //IMI_STREAMOUT_H

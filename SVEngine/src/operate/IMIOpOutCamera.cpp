//
// IMIOpOutCamera.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpOutCamera.h"
#include "../app/IMIInst.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIStreamIn.h"
#include "../basesys/IMIStreamOut.h"
#include "../rendercore/IMIRenderDef.h"

using namespace imi;

//设置ios相机
IMIOpCreateIOSInstream::IMIOpCreateIOSInstream(IMIInstPtr _app, cptr8 _name, IMI_PIC_FORMATE _format, s32 _w, s32 _h,f32 _angle, bool _show)
        : IMIOpBase(_app) {
    m_name = _name;
    m_formate = _format;
    m_width = _w;
    m_height = _h;
    m_angle = _angle;
    m_show = _show;
}

void IMIOpCreateIOSInstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    //创建一个ios相机节点 挂在场景中
//    IMIStreamInPtr t_cam_stream = mApp->getBasicSys()->getStreamIn();
//    if(t_cam_stream){
//        t_cam_stream->createInStream(m_name.c_str(),0,m_formate,m_width,m_height,m_angle, m_show);
//        t_cam_stream->active(m_name.c_str());
//    }
//#endif
}

//设置ios相机
IMIOpCreateIOSTexIDInstream::IMIOpCreateIOSTexIDInstream(IMIInstPtr _app, cptr8 _name, u32 _tex0ID, u32 _tex1ID, u32 _tex2ID, IMI_PIC_FORMATE _format, s32 _w, s32 _h,f32 _angle, bool _show)
: IMIOpBase(_app) {
    m_name = _name;
    m_formate = _format;
    m_width = _w;
    m_height = _h;
    m_angle = _angle;
    m_tex0ID = _tex0ID;
    m_tex1ID = _tex1ID;
    m_tex2ID = _tex2ID;
    m_show = _show;
}

void IMIOpCreateIOSTexIDInstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    //创建一个ios相机节点 挂在场景中
//    IMIStreamInPtr t_cam_stream = mApp->getBasicSys()->getStreamIn();
//    if(t_cam_stream){
//        t_cam_stream->createInTextureStream(m_name.c_str(), m_tex0ID, m_tex1ID, m_tex2ID, 0, m_formate, m_width, m_height, m_angle, m_show);
//        t_cam_stream->active(m_name.c_str());
//    }
//#endif
}

//删除ios相机
IMIOpDestroyIOSInstream::IMIOpDestroyIOSInstream(IMIInstPtr _app, cptr8 _name)
        : IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyIOSInstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    IMIStreamInPtr t_cam_stream = mApp->getBasicSys()->getStreamIn();
//    if(t_cam_stream){
//        t_cam_stream->unactive(m_name.c_str());
//        t_cam_stream->destroyInStream(m_name.c_str());
//    }
//#endif
}


IMIOpCreateIOSOutstream::IMIOpCreateIOSOutstream(IMIInstPtr _app, cptr8 _name, s32 _format,  s32 _width, s32 _height, s32 _steamType)
: IMIOpBase(_app) {
    m_name = _name;
    m_formate = _format;
    m_streamType = _steamType;
    m_width = _width;
    m_height = _height;
}

void IMIOpCreateIOSOutstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->createOutStream(m_name.c_str(), 0, m_formate, m_width, m_height, RENDERSTREAMTYPE(m_streamType));
//    }
//#endif
}


IMIOpDestroyIOSOutstream::IMIOpDestroyIOSOutstream(IMIInstPtr _app, cptr8 _name)
        : IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyIOSOutstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->unactive();
//        t_streamout->destroyOutStream();
//    }
//#endif
}


IMIOpOpenIOSOutstream::IMIOpOpenIOSOutstream(IMIInstPtr _app, cb_out_stream _cb)
        : IMIOpBase(_app) {
    m_cb = _cb;
}

void IMIOpOpenIOSOutstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->setStreamOutCB(m_cb);
//        t_streamout->active();
//    }
//#endif
}

IMIOpCloseIOSOutstream::IMIOpCloseIOSOutstream(IMIInstPtr _app)
        : IMIOpBase(_app) {
}

void IMIOpCloseIOSOutstream::_process(f32 _dt) {
//#ifdef IMI_IOS
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->unactive();
//    }
//#endif
}

//创建安卓相机
IMIOpCreateAndriodCamera::IMIOpCreateAndriodCamera(IMIInstPtr _app, s32 _format, s32 _w, s32 _h,
                                                 f32 _angle)
        : IMIOpBase(_app) {
    m_formate = _format;
    m_width = _w;
    m_height = _h;
    m_angle = _angle;
}

void IMIOpCreateAndriodCamera::_process(f32 _dt) {
    m_formate = GL_RGBA;


}

IMIOpDestroyAndoidCamera::IMIOpDestroyAndoidCamera(IMIInstPtr _app, cptr8 _name)
        : IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyAndoidCamera::_process(f32 _dt) {

}

//创建纹理相机
IMIOpCreateTextureCamera::IMIOpCreateTextureCamera(IMIInstPtr _app, s32 _format, s32 _w, s32 _h,
                                                 f32 _angle)
        : IMIOpBase(_app) {
    m_formate = _format;
    m_width = _w;
    m_height = _h;
    m_angle = _angle;
}

void IMIOpCreateTextureCamera::_process(f32 _dt) {
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->createOutStream(nullptr,1,GL_RGBA, m_width, m_height);
//        t_streamout->active();
//    }
}


IMIOpDestroyTextureOutstream::IMIOpDestroyTextureOutstream(IMIInstPtr _app, cptr8 _name): IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyTextureOutstream::_process(f32 _dt) {
//    IMIStreamOutPtr t_streamout = mApp->getBasicSys()->getStreamOut();
//    if( t_streamout ) {
//        t_streamout->unactive();
//        t_streamout->destroyOutStream();
//    }
}


//创建流相机
IMIOpCreateStreamCamera::IMIOpCreateStreamCamera(IMIInstPtr _app, cptr8 _name,s32 _format, s32 _w, s32 _h,
                                               f32 _angle)
        : IMIOpBase(_app) {
    m_formate = _format;
    m_width = _w;
    m_height = _h;
    m_angle = _angle;
    m_name = _name;
}

void IMIOpCreateStreamCamera::_process(f32 _dt) {
//    IMIStreamInPtr t_cam_stream = mApp->getBasicSys()->getStreamIn();
//    if (t_cam_stream) {
//        t_cam_stream->createInStream(m_name.c_str(), 1,(IMI_PIC_FORMATE)m_formate, m_width, m_height, m_angle,true);
//        t_cam_stream->active(m_name.c_str());
//    }
}

IMIOpDestroyStreamCamera::IMIOpDestroyStreamCamera(IMIInstPtr _app, cptr8 _name)
        : IMIOpBase(_app) {
    m_name = _name;
}

void IMIOpDestroyStreamCamera::_process(f32 _dt) {
//    IMIStreamInPtr t_cam_stream = mApp->getBasicSys()->getStreamIn();
//    if (t_cam_stream) {
//        t_cam_stream->unactive(m_name.c_str());
//        t_cam_stream->destroyInStream(m_name.c_str());
//    }
}



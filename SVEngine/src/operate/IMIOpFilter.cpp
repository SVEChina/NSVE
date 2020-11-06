//
// IMIOpFilter.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpFilter.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalMgr.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIBasicSys.h"
#include "../mtl/IMIFilterBase.h"
#include "../mtl/IMIFilterPicmodify.h"
#include "../mtl/IMIParseLUTFilter.h"
#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"
#include "../event/IMIOpEvent.h"
#include "../base/IMIDataSwap.h"

using namespace imi;

//设置美颜滤镜
IMIOpSetBeautyFilter::IMIOpSetBeautyFilter(IMIInstPtr _app,cptr8 _scenename,cptr8 _filter,s32 _lows)
:IMIOpBase(_app) {
    m_scenename = _scenename;
    m_filter = _filter;
    m_lows=_lows;
}

void IMIOpSetBeautyFilter::_process(f32 _dt) {
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if( t_picproc ) {
////        IMIFilterPicmodifyPtr t_baseOn=MakeSharedPtr<IMIFilterPicmodify>(mApp);
////        t_baseOn->create();
////        t_picproc->addFilter(t_baseOn);
////        t_picproc->openFilter(t_baseOn);
////        if(m_lows==0){
////            IMIFairDataPtr t_fair=MakeSharedPtr<IMIFairData>(mApp);
////            t_fair->create();
////            t_picproc->addFilter(t_fair);
////            t_picproc->openFilter(t_fair);
////        }else if(m_lows==1){
////            IMIFairDataBlurPtr t_fair=MakeSharedPtr<IMIFairDataBlur>(mApp);
////            t_fair->create();
////            t_picproc->addFilter(t_fair);
////            t_picproc->openFilter(t_fair);
////        }else if(m_lows==2){
////            IMIFairLtraLowPtr t_fair=MakeSharedPtr<IMIFairLtraLow>(mApp);
////            t_fair->create();
////            t_picproc->addFilter(t_fair);
////            t_picproc->openFilter(t_fair);
////        }
//    }
}

//设置美颜滤镜
IMIOpUpdateFilterSmooth::IMIOpUpdateFilterSmooth(IMIInstPtr _app,f32 _smooth,u32 _type)
:IMIOpBase(_app) {
    m_smooth=_smooth;
    m_type=_type;
}

void IMIOpUpdateFilterSmooth::_process(f32 _dt) {
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if( t_picproc ) {
//        t_picproc->setFilterParam(m_smooth,(IMIFILTERITEMTYPE)m_type);
//    }
}

//设置美颜滤镜
IMIOpUpdateBSplineFilter::IMIOpUpdateBSplineFilter(IMIInstPtr _app,IMIDataSwapPtr _pDataSwap)
:IMIOpBase(_app) {
    m_pDataSwap=_pDataSwap;
}

void IMIOpUpdateBSplineFilter::_process(f32 _dt) {
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if( t_picproc ) {
//        t_picproc->setFilterBSplineData((ptru8)m_pDataSwap->getData());
//
//    }
}

//关闭美颜滤镜
IMIOpCloseBeautyFilter::IMIOpCloseBeautyFilter(IMIInstPtr _app)
:IMIOpBase(_app) {
}

void IMIOpCloseBeautyFilter::_process(f32 _dt) {
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if( t_picproc ) {
//        t_picproc->clearFilter(IMI_FUNC_BEAUTY);
//    }
}

//
IMIOpShapeFaceSmoothFilter::IMIOpShapeFaceSmoothFilter(IMIInstPtr _app,f32 _face,f32 _eye)
:IMIOpBase(_app) {
    m_face = _face;
    m_eye=_eye;
}

void IMIOpShapeFaceSmoothFilter::_process(f32 _dt) {
    IMIFaceShapeEventPtr t_event = MakeSharedPtr<IMIFaceShapeEvent>();
    t_event->m_faceSmooth = m_face;
    t_event->m_eyeSmooth = m_eye;
    mApp->getEventMgr()->pushEvent(t_event);
}

IMIOpLUTFilterCreate::IMIOpLUTFilterCreate(IMIInstPtr _app,cptr8 _scenename,cptr8 _path,s32 resid)
:IMIOpBase(_app){
     m_path = _path;
     m_resid = resid;
}

void IMIOpLUTFilterCreate::_process(f32 _dt){
//    IMIFilterBasePtr t_lutFilter = IMIParseLUTFilter::parseLUT(mApp,m_path, m_resid);
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if( t_picproc&&t_lutFilter) {
//        t_lutFilter->create();
//        t_picproc->addFilter(t_lutFilter);
//        t_picproc->openFilter(t_lutFilter);
//    }
}

IMIOpLUTFilterDestory::IMIOpLUTFilterDestory(IMIInstPtr _app,cptr8 _scenename,s32 resid)
:IMIOpBase(_app){
    
}

void IMIOpLUTFilterDestory::_process(f32 _dt){
    
}


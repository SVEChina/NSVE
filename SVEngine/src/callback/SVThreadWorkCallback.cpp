//
// SVThreadWorkCallback.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVThreadWorkCallback.h"
#include "../app/SVInst.h"
#include "../work/SVThread.h"
#include "../work/SVThreadPool.h"

using namespace sv;

//空跑模式
void process_wt_null(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//停止模式
void process_wt_stop(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//预览模式
void process_wt_preview(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//合成模式
void process_wt_mix(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//相机模式
void process_wt_camera(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//录制模式
void process_wt_record(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//工作线程回调
void workThreadCallback(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

//线程销毁回调
void workThreadDestroyCallback(SVInstPtr _app,SVThread* _thread,SV_THREAD_STAGE _stage){
}

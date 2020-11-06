//
// IMITexture.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//
#include "IMITexture.h"
#include "../work/IMITdCore.h"
#include "../app/IMIDispatch.h"
#include "../app/IMIInst.h"
#include "../work/IMITdCore.h"
#include "../base/IMIDataSwap.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMITexture::IMITexture(IMIInstPtr _app)
:IMIGBaseEx(_app) {
    m_lock = MakeSharedPtr<IMILockSpin>();
    m_name = "";
    m_tex_pool_id = -1;
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

IMITexture::~IMITexture() {
    m_lock = nullptr;
    m_tex_pool_id = -1;
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

IMITexturePtr IMITexture::share() {
    return std::dynamic_pointer_cast<IMITexture>(shareObject()) ;
}

void IMITexture::dispatch() {
    IMIDispatch::dispatchTextureCreate(mApp, share());
}

void IMITexture::init(IMITextureDsp& _dsp) {
    setTexData(nullptr);
    m_texture_dsp = _dsp;
}

void IMITexture::init(IMITextureDsp& _dsp,IMIDataSwapPtr _data) {
    m_texture_dsp = _dsp;
    setTexData(_data);
}

void IMITexture::destroy(){
    for(s32 i=0;i<6;i++) {
        m_texture_dsp.m_pData[i] = nullptr;
    }
}

void IMITexture::resize(s32 _w,s32 _h) {
    if(m_texture_dsp.m_width == _w && m_texture_dsp.m_height == _h) {
        return ;
    }
    m_texture_dsp.m_width = _w;
    m_texture_dsp.m_height = _h;
//    if(m_restex) {
//        m_restex->resize();
//    }
}

IMIDataSwapPtr IMITexture::getTextureData() {
    return m_texture_dsp.m_pData[0];
}

IMIDataSwapPtr IMITexture::getTextureCubeData(s32 _index) {
    if(_index>=0 && _index<6) {
        return m_texture_dsp.m_pData[_index];
    }
    return nullptr;
}

void IMITexture::setTexData(IMIDataSwapPtr _data){
    m_lock->lock();
    m_texture_dsp.m_pData[0] = _data;
    m_lock->unlock();
}

void IMITexture::setTexCubeData(IMIDataSwapPtr _data,s32 _index){
    m_lock->lock();
    if(_index>=0 && _index<6) {
        m_texture_dsp.m_pData[_index] = _data;
    }
    m_lock->unlock();
}

void IMITexture::bindRes(s32 _instid) {
    m_tex_pool_id = _instid;
}

void IMITexture::unbindRes() {
    m_tex_pool_id = -1;
}

IMIRTexPtr IMITexture::getResTex(){
    if(mApp->getRenderer() ) {
        return mApp->getRenderer()->getResTexture( m_tex_pool_id );
    }
    return nullptr;
}

void IMITexture::swap(IMITexturePtr _tex) {
    //检测交换RES-ID的合理性
    if(_canSwap(_tex)) {
        s32 tmp = _tex->m_tex_pool_id;
        _tex->m_tex_pool_id = m_tex_pool_id;
        m_tex_pool_id = tmp;
    }
}

bool IMITexture::_canSwap(IMITexturePtr _tex) {
    IMITextureDsp* t_dsp = _tex->getTextureDsp();
    if( t_dsp->m_width == m_texture_dsp.m_width &&
       t_dsp->m_height == m_texture_dsp.m_height &&
       t_dsp->m_image_type == m_texture_dsp.m_image_type &&
       t_dsp->m_data_formate == m_texture_dsp.m_data_formate) {
        return true;
    }
    return false;
}

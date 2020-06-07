//
// SVRTech.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRTech.h"
#include "SVRenderer.h"

using namespace sv;

SVRTech::SVRTech(SVInstPtr _app)
:SVGBaseEx(_app)
,m_techDsp(0){
    m_vs_name = "default";
    m_fs_name = "default";
    m_gs_name = "default";
    m_tsc_name = "default";
    m_tsd_name = "default";
    m_cs_name = "default";
}

SVRTech::~SVRTech() {
}

void SVRTech::setShader(cptr8 _name,SV_TECH_TYPE _type) {
    
    if( strcmp(_name,"default") ) {
        if( _type == SV_E_TECH_VS) {
            m_vs_name = _name;
            m_techDsp &= ~SV_E_TECH_VS;
        }else if( _type == SV_E_TECH_FS) {
            m_fs_name = _name;
            m_techDsp &= ~SV_E_TECH_FS;
        }else if( _type == SV_E_TECH_GS) {
            m_gs_name = _name;
            m_techDsp &= ~SV_E_TECH_GS;
        }else if( _type == SV_E_TECH_CS) {
            m_cs_name = _name;
            m_techDsp &= ~SV_E_TECH_CS;
        }else if( _type == SV_E_TECH_TSC) {
            m_tsc_name = _name;
            m_techDsp &= ~SV_E_TECH_TSC;
        }else if( _type == SV_E_TECH_TSD) {
            m_tsd_name = _name;
            m_techDsp &= ~SV_E_TECH_TSD;
        }
    }else{
        if( _type == SV_E_TECH_VS) {
            m_vs_name = _name;
            m_techDsp |= SV_E_TECH_VS;
        }else if( _type == SV_E_TECH_FS) {
            m_fs_name = _name;
            m_techDsp |= SV_E_TECH_FS;
        }else if( _type == SV_E_TECH_GS) {
            m_gs_name = _name;
            m_techDsp |= SV_E_TECH_GS;
        }else if( _type == SV_E_TECH_CS) {
            m_cs_name = _name;
            m_techDsp |= SV_E_TECH_CS;
        }else if( _type == SV_E_TECH_TSC) {
            m_tsc_name = _name;
            m_techDsp |= SV_E_TECH_TSC;
        }else if( _type == SV_E_TECH_TSD) {
            m_tsd_name = _name;
            m_techDsp |= SV_E_TECH_TSD;
        }
    }
    
}

void SVRTech::build(SVRendererPtr _renderer){
}

void SVRTech::render(SVRendererPtr _renderer) {
}

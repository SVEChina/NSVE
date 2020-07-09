//
// SVRShader.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRShader.h"
#include "../app/SVInst.h"
#include "../work/SVTdCore.h"
#include "SVRenderer.h"

using namespace sv;

SVRShader::SVRShader(SVInstPtr _app)
:SVGBaseEx(_app){
    m_attri_formate = "all";
}

SVRShader::~SVRShader(){
}

void SVRShader::setAF(cptr8 _af) {
    m_attri_formate = _af;
}

cptr8 SVRShader::getAF() {
    return m_attri_formate.c_str();
}

void SVRShader::setProgrammeName(cptr8 _filename) {
    m_programme_fname = _filename;
}

cptr8 SVRShader::getProgrammeName(){
    return m_programme_fname.c_str();
}

void SVRShader::setVSFName(cptr8 _filename){
    m_vs_fname = _filename;
}

void SVRShader::setFSFName(cptr8 _filename){
    m_fs_fname = _filename;
}

void SVRShader::setGSFName(cptr8 _filename){
    m_gs_fname = _filename;
}

void SVRShader::setCSFName(cptr8 _filename){
    m_cs_fname = _filename;
}

void SVRShader::setTSCFName(cptr8 _filename){
    m_tsc_fname = _filename;
}

void SVRShader::setTSEFName(cptr8 _filename){
    m_tse_fname = _filename;
}

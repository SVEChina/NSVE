//
// IMIMtlFair1.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMtlFair1.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalParam.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

//
IMIMtlFilterBrilaterl::IMIMtlFilterBrilaterl(IMIInstPtr _app)
:IMIMtlCore(_app,"brilateralfilter") {
    m_texelWidthOffset = 0.0f;
    m_texelHeightOffset = 0.0f;
    m_distanceNormalizationFactor = 5.0f;
    m_paramDirty = true;
}

IMIMtlFilterBrilaterl::IMIMtlFilterBrilaterl(IMIMtlFilterBrilaterl *_mtl)
:IMIMtlCore(_mtl){
    m_texelWidthOffset =_mtl->m_texelWidthOffset;
    m_texelHeightOffset = _mtl->m_texelHeightOffset;
    m_distanceNormalizationFactor = _mtl->m_distanceNormalizationFactor;
    m_paramDirty = _mtl->m_paramDirty;
}

IMIMtlFilterBrilaterl::~IMIMtlFilterBrilaterl() {
}

IMIMtlCorePtr IMIMtlFilterBrilaterl::clone() {
    return PointerSharedPtr<IMIMtlFilterBrilaterl>(new IMIMtlFilterBrilaterl(this));
}

void IMIMtlFilterBrilaterl::setOffset(f32 _offw,f32 _offh) {
   // if( (m_texelWidthOffset!=_offw) || (m_texelHeightOffset!=_offh)) {
        m_texelWidthOffset = _offw;
        m_texelHeightOffset = _offh;
        m_paramDirty = true;
    //}
}

void IMIMtlFilterBrilaterl::setDistance(f32 _dis) {
    if(m_distanceNormalizationFactor!=_dis) {
        m_distanceNormalizationFactor = _dis;
        m_paramDirty = true;
    }
}

void IMIMtlFilterBrilaterl::_submitMtl(IMIRendererPtr _render) {
    if(m_paramDirty) {
        m_paramDirty = false;
//        f32 tt_w = m_texelWidthOffset /mApp->m_global_param.sv_width;
//        f32 tt_h = m_texelHeightOffset /mApp->m_global_param.sv_height;
//        _render->submitUniformf("texelWidthOffset", tt_w);
//        _render->submitUniformf("texelHeightOffset", tt_h);
//        _render->submitUniformf("distanceNormalizationFactor", m_distanceNormalizationFactor);
//        _render->submitUniformf("hlafWidth", 0.5/mApp->m_global_param.sv_width);
//        _render->submitUniformf("hlafHeight", 0.5/mApp->m_global_param.sv_height);
    }
}

//
IMIMtlFilterBrilaterl2::IMIMtlFilterBrilaterl2(IMIInstPtr _app)
:IMIMtlCore(_app,"brilateralfilter02") {
    m_texelWidthOffset = 0;
    m_texelHeightOffset = 0;
    m_distanceNormalizationFactor = 5.0f;
    m_paramDirty = true;
}

IMIMtlFilterBrilaterl2::IMIMtlFilterBrilaterl2(IMIMtlFilterBrilaterl2 *_mtl)
:IMIMtlCore(_mtl){
    m_texelWidthOffset =_mtl->m_texelWidthOffset;
    m_texelHeightOffset = _mtl->m_texelHeightOffset;
    m_distanceNormalizationFactor = _mtl->m_distanceNormalizationFactor;
    m_paramDirty = _mtl->m_paramDirty;
}

IMIMtlFilterBrilaterl2::~IMIMtlFilterBrilaterl2() {
}

IMIMtlCorePtr IMIMtlFilterBrilaterl2::clone() {
    return PointerSharedPtr<IMIMtlFilterBrilaterl2>(new IMIMtlFilterBrilaterl2(this));
}

//有问题
void IMIMtlFilterBrilaterl2::setOffset(f32 _offw,f32 _offh) {
   // if( (m_texelWidthOffset!=_offw) || (m_texelHeightOffset!=_offh)) {
        m_texelWidthOffset = _offw;
        m_texelHeightOffset = _offh;
        m_paramDirty = true;
   // }
}

void IMIMtlFilterBrilaterl2::setDistance(f32 _dis) {
    if(m_distanceNormalizationFactor!=_dis) {
        m_distanceNormalizationFactor = _dis;
        m_paramDirty = true;
    }
}

void IMIMtlFilterBrilaterl2::_submitMtl(IMIRendererPtr _render) {
    if(m_paramDirty) {
        m_paramDirty = false;
//        f32 tt_w = m_texelWidthOffset /mApp->m_global_param.sv_width;
//        f32 tt_h = m_texelHeightOffset /mApp->m_global_param.sv_height;
//        _render->submitUniformf("texelWidthOffset", tt_w);
//        _render->submitUniformf("texelHeightOffset", tt_h);
//        _render->submitUniformf("distanceNormalizationFactor", m_distanceNormalizationFactor);
//        _render->submitUniformf("hlafWidth", 0.5/mApp->m_global_param.sv_width);
//        _render->submitUniformf("hlafHeight", 0.5/mApp->m_global_param.sv_height);
    }
}

//
IMIMtlGaussian::IMIMtlGaussian(IMIInstPtr _app)
:IMIMtlCore(_app,"gaussian") {
    m_radius = 1.0f;
    m_paramDirty = true;
}

IMIMtlGaussian::IMIMtlGaussian(IMIMtlGaussian *_mtl)
:IMIMtlCore(_mtl){
    m_radius = _mtl->m_radius;
    m_paramDirty = _mtl->m_paramDirty;
}

IMIMtlGaussian::~IMIMtlGaussian() {
}

IMIMtlCorePtr IMIMtlGaussian::clone() {
    return PointerSharedPtr<IMIMtlGaussian>(new IMIMtlGaussian(this));
}

void IMIMtlGaussian::setRadius(f32 _radius) {
    if(m_radius!=_radius) {
        m_radius = _radius;
        m_paramDirty = true;
    }
}

void IMIMtlGaussian::_submitMtl(IMIRendererPtr _render) {
    if(m_paramDirty) {
        m_paramDirty = false;
//        f32 t_w = mApp->m_global_param.sv_width;
//        f32 t_h = mApp->m_global_param.sv_height;
//        _render->submitUniformf("texelWidthOffset", t_w);
//        _render->submitUniformf("texelHeightOffset", t_h);
//        _render->submitUniformf("radius", m_radius);
    }
}

IMIMtlBlurFairGus::IMIMtlBlurFairGus(IMIInstPtr _app)
:IMIMtlCore(_app,"blur_fair_gus") {
    
}

IMIMtlBlurFairGus::IMIMtlBlurFairGus(IMIMtlBlurFairGus *_mtl)
:IMIMtlCore(_mtl){
    
}

IMIMtlBlurFairGus::~IMIMtlBlurFairGus(){
    
}

void IMIMtlBlurFairGus::setSmooth(f32 _smooth){
    
}

void IMIMtlBlurFairGus::_submitMtl(IMIRendererPtr _render){
    
}

IMIMtlCorePtr IMIMtlBlurFairGus::clone(){
     return PointerSharedPtr<IMIMtlBlurFairGus>(new IMIMtlBlurFairGus(this));
}

IMIMtlBlur::IMIMtlBlur(IMIInstPtr _app)
:IMIMtlCore(_app,"blur") {
    m_radius = 1.0f;
    m_paramDirty = true;
}

IMIMtlBlur::IMIMtlBlur(IMIMtlBlur *_mtl)
:IMIMtlCore(_mtl){
    m_radius = _mtl->m_radius;
    m_paramDirty = _mtl->m_paramDirty;
}

IMIMtlBlur::~IMIMtlBlur() {
}

IMIMtlCorePtr IMIMtlBlur::clone() {
    return PointerSharedPtr<IMIMtlBlur>(new IMIMtlBlur(this));
}

void IMIMtlBlur::setRadius(f32 _radius) {
    if(m_radius!=_radius) {
        m_radius = _radius;
        m_paramDirty = true;
    }
}

void IMIMtlBlur::_submitMtl(IMIRendererPtr _render) {
    if(m_paramDirty) {
        m_paramDirty = false;
//        f32 t_w = mApp->m_global_param.sv_width;
//        f32 t_h = mApp->m_global_param.sv_height;
//        _render->submitUniformf("texelWidthOffset", t_w);
//        _render->submitUniformf("texelHeightOffset", t_h);
//        _render->submitUniformf("softenStrength", m_radius);
    }
}

IMIMtlBlurFair::IMIMtlBlurFair(IMIInstPtr _app)
:IMIMtlCore(_app,"blur_fair_hipass"){

}
    
IMIMtlBlurFair::IMIMtlBlurFair(IMIMtlBlurFair *_mtl)
:IMIMtlCore(_mtl){
    m_blurAlpha = _mtl->m_blurAlpha;
}
    
IMIMtlBlurFair::~IMIMtlBlurFair(){
}

void IMIMtlBlurFair::_submitMtl(IMIRendererPtr _render){
    //_render->submitUniformf("blurAlpha", m_blurAlpha);
}

void IMIMtlBlurFair::setSmooth(f32 _smooth){
    m_blurAlpha=_smooth;
}

IMIMtlCorePtr IMIMtlBlurFair::clone(){
    return PointerSharedPtr<IMIMtlBlurFair>(new IMIMtlBlurFair(this));
}

IMIMtlFairLtraLow::IMIMtlFairLtraLow(IMIInstPtr _app)
:IMIMtlCore(_app,"beauty"){
     m_smooth=0.0;
}

IMIMtlFairLtraLow::IMIMtlFairLtraLow(IMIMtlFairLtraLow *_mtl)
:IMIMtlCore(_mtl){
    m_smooth=_mtl->m_smooth;
}

IMIMtlFairLtraLow::~IMIMtlFairLtraLow(){
}

void IMIMtlFairLtraLow::setSmooth(f32 _smooth){
    m_smooth=_smooth;
}

void IMIMtlFairLtraLow::_submitMtl(IMIRendererPtr _render){
    //_render->submitUniformf("softenStrength", m_smooth);
}

IMIMtlCorePtr IMIMtlFairLtraLow::clone(){
    return PointerSharedPtr<IMIMtlFairLtraLow>(new IMIMtlFairLtraLow(this));
}


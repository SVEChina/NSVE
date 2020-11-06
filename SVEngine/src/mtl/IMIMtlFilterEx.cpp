//
//  IMIBrightnessMtl.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2018/9/25.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "IMIMtlFilterEx.h"
#include "../mtl/IMITexMgr.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMIMtlBrightnessContrast::IMIMtlBrightnessContrast(IMIInstPtr _app)
:IMIMtlCore(_app,"BrightnessContrast") {
    m_brightness=0.0f;
    m_contrast=0.0f;
}

IMIMtlBrightnessContrast::IMIMtlBrightnessContrast(IMIMtlBrightnessContrast* _mtl)
:IMIMtlCore(_mtl){
    m_brightness=_mtl->m_brightness;
    m_contrast=_mtl->m_contrast;
}

IMIMtlBrightnessContrast::~IMIMtlBrightnessContrast(){
    
}

IMIMtlCorePtr IMIMtlBrightnessContrast::clone(){
    return PointerSharedPtr<IMIMtlBrightnessContrast>(new IMIMtlBrightnessContrast(this));
}

void IMIMtlBrightnessContrast::setBrightness(f32 _smooth){
    m_brightness=_smooth;
}

void IMIMtlBrightnessContrast::setContrast(f32 _smooth){
    m_contrast=_smooth;
}

void IMIMtlBrightnessContrast::_submitMtl(IMIRendererPtr _render) {
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("brightness", m_brightness);
//    _render->submitUniformf("contrast", m_contrast);
}



IMIMtlSaturation::IMIMtlSaturation(IMIInstPtr _app)
:IMIMtlCore(_app,"saturation") {
    m_saturation=0.0f;
}

IMIMtlSaturation::IMIMtlSaturation(IMIMtlSaturation* _mtl)
:IMIMtlCore(_mtl){
    m_saturation=_mtl->m_saturation;
}

IMIMtlSaturation::~IMIMtlSaturation(){
    
}

IMIMtlCorePtr IMIMtlSaturation::clone(){
    return PointerSharedPtr<IMIMtlSaturation>(new IMIMtlSaturation(this));
}

void IMIMtlSaturation::setSaturation(f32 _smooth){
    m_saturation=_smooth;
}


void IMIMtlSaturation::_submitMtl(IMIRendererPtr _render) {
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformf("saturation", m_saturation);
}

IMIMtlVibrance::IMIMtlVibrance(IMIInstPtr _app)
:IMIMtlCore(_app,"vibrance") {
    m_vibrance=0.0f;
}

IMIMtlVibrance::IMIMtlVibrance(IMIMtlVibrance* _mtl)
:IMIMtlCore(_mtl){
    m_vibrance=_mtl->m_vibrance;
}

IMIMtlVibrance::~IMIMtlVibrance(){
    
}

IMIMtlCorePtr IMIMtlVibrance::clone(){
    return PointerSharedPtr<IMIMtlVibrance>(new IMIMtlVibrance(this));
}

void IMIMtlVibrance::setVibrance(f32 _smooth){
    m_vibrance=_smooth;
}


void IMIMtlVibrance::_submitMtl(IMIRendererPtr _render) {
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformf("vibrance", m_vibrance);
}

IMIMtlShadowHighlight::IMIMtlShadowHighlight(IMIInstPtr _app)
:IMIMtlCore(_app,"shadowhighlight") {
    m_shadow=0.0;
    m_HighLight=0.0;
}

IMIMtlShadowHighlight::IMIMtlShadowHighlight(IMIMtlShadowHighlight* _mtl)
:IMIMtlCore(_mtl){
    
}

IMIMtlShadowHighlight::~IMIMtlShadowHighlight(){
    
}

IMIMtlCorePtr IMIMtlShadowHighlight::clone(){
    return PointerSharedPtr<IMIMtlShadowHighlight>(new IMIMtlShadowHighlight(this));
}

void IMIMtlShadowHighlight::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("shadows", m_shadow);
//    _render->submitUniformf("highlights", m_HighLight);
}

IMIMtlWhiteBlackLevel::IMIMtlWhiteBlackLevel(IMIInstPtr _app)
:IMIMtlCore(_app,"whiteblackLevel") {
    m_shadow=0.0;
    m_HighLight=0.0;
}

IMIMtlWhiteBlackLevel::IMIMtlWhiteBlackLevel(IMIMtlWhiteBlackLevel* _mtl)
:IMIMtlCore(_mtl){
    
}

IMIMtlWhiteBlackLevel::~IMIMtlWhiteBlackLevel(){
    
}

IMIMtlCorePtr IMIMtlWhiteBlackLevel::clone(){
    return PointerSharedPtr<IMIMtlWhiteBlackLevel>(new IMIMtlWhiteBlackLevel(this));
}

void IMIMtlWhiteBlackLevel::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("shadows", m_shadow);
//    _render->submitUniformf("highlights", m_HighLight);
}

IMIMtlColorBalance::IMIMtlColorBalance(IMIInstPtr _app)
:IMIMtlCore(_app,"colorBalance"){
    m_redShift      = 0.0f;
    m_greenShift    = 0.0f;
    m_blueShift     = 0.0f;
    m_sdredShift    = 0.0f;
    m_sdgreenShift  = 0.0f;
    m_sdblueShift   = 0.0f;
    m_hhredShift    = 0.0f;
    m_hhgreenShift  = 0.0f;
    m_hhblueShift   = 0.0f;
}
    
IMIMtlColorBalance::IMIMtlColorBalance(IMIMtlColorBalance* _mtl)
:IMIMtlCore(_mtl){
    
}
    
IMIMtlColorBalance::~IMIMtlColorBalance(){
    m_redShift      = 0.0f;
    m_greenShift    = 0.0f;
    m_blueShift     = 0.0f;
    m_sdredShift    = 0.0f;
    m_sdgreenShift  = 0.0f;
    m_sdblueShift   = 0.0f;
    m_hhredShift    = 0.0f;
    m_hhgreenShift  = 0.0f;
    m_hhblueShift   = 0.0f;
}
    
IMIMtlCorePtr IMIMtlColorBalance::clone(){
     return PointerSharedPtr<IMIMtlColorBalance>(new IMIMtlColorBalance(this));
}

void IMIMtlColorBalance::_submitMtl(IMIRendererPtr _render){
     IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("redShift", m_redShift);
//    _render->submitUniformf("greenShift", m_greenShift);
//    _render->submitUniformf("blueShift", m_blueShift);
//    _render->submitUniformf("sdredShift", m_sdredShift);
//    _render->submitUniformf("sdgreenShift", m_sdgreenShift);
//    _render->submitUniformf("sdblueShift", m_sdblueShift);
//    _render->submitUniformf("hhredShift", m_hhredShift);
//    _render->submitUniformf("hhgreenShift", m_hhgreenShift);
//    _render->submitUniformf("hhblueShift", m_hhblueShift);
}


IMIMtlHSL::IMIMtlHSL(IMIInstPtr _app)
:IMIMtlCore(_app,"HSL2"){
     m_saturationRed=1.0;
     m_HueRed=0.0;
     m_LightnessRed=1.0;
    
     m_saturationYellow=1.0;
     m_HueYellow=0.0;
     m_LightnessYellow=1.0;
    
     m_saturationGreen=1.0;
     m_HueGreen=0.0;
     m_LightnessGreen=1.0;
    
     m_saturationMagenta=1.0;
     m_HueMagenta=0.0;
     m_LightnessMagenta=1.0;
    
     m_saturationBlue=1.0;
     m_HueBlue=0.0;
     m_LightnessBlue=1.0;
    
     m_saturationCyan=1.0;
     m_HueCyan=0.0;
     m_LightnessCyan=1.0;
}

IMIMtlHSL::IMIMtlHSL(IMIMtlHSL* _mtl)
:IMIMtlCore(_mtl){
}

IMIMtlHSL::~IMIMtlHSL(){
}

IMIMtlCorePtr IMIMtlHSL::clone(){
    return PointerSharedPtr<IMIMtlHSL>(new IMIMtlHSL(this));
}

void IMIMtlHSL::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("m_saturationRed", m_saturationRed);
//    _render->submitUniformf("m_HueRed", m_HueRed);
//    _render->submitUniformf("m_LightnessRed", m_LightnessRed);
//
//    _render->submitUniformf("m_saturationYellow", m_saturationYellow);
//    _render->submitUniformf("m_HueYellow", m_HueYellow);
//    _render->submitUniformf("m_LightnessYellow", m_LightnessYellow);
//
//    _render->submitUniformf("m_saturationGreen", m_saturationGreen);
//    _render->submitUniformf("m_HueGreen", m_HueGreen);
//    _render->submitUniformf("m_LightnessGreen", m_LightnessGreen);
//
//    _render->submitUniformf("m_saturationMagenta", m_saturationMagenta);
//    _render->submitUniformf("m_HueMagenta", m_HueMagenta);
//    _render->submitUniformf("m_LightnessMagenta", m_LightnessMagenta);
//
//    _render->submitUniformf("m_saturationBlue", m_saturationBlue);
//    _render->submitUniformf("m_HueBlue", m_HueBlue);
//    _render->submitUniformf("m_LightnessBlue", m_LightnessBlue);
//
//    _render->submitUniformf("m_saturationCyan", m_saturationCyan);
//    _render->submitUniformf("m_HueCyan", m_HueCyan);
//    _render->submitUniformf("m_LightnessCyan", m_LightnessCyan);

}

IMIMtlWhiteBalance::IMIMtlWhiteBalance(IMIInstPtr _app)
:IMIMtlCore(_app,"WhiteBalance"){
    m_Temperature = 5000.0f;
    m_Tint = 0.0f;
}

IMIMtlWhiteBalance::IMIMtlWhiteBalance(IMIMtlWhiteBalance* _mtl)
:IMIMtlCore(_mtl){
    m_Temperature = _mtl->m_Temperature;
    m_Tint = _mtl->m_Tint;
}

IMIMtlWhiteBalance::~IMIMtlWhiteBalance(){
    
}

IMIMtlCorePtr IMIMtlWhiteBalance::clone(){
      return PointerSharedPtr<IMIMtlWhiteBalance>(new IMIMtlWhiteBalance(this));
}

void IMIMtlWhiteBalance::setTemperature(f32 _smooth){
    m_Temperature= _smooth < 5000 ? 0.0004 * (_smooth-5000.0) : 0.00006 * (_smooth-5000.0);
}

void IMIMtlWhiteBalance::setTint(f32 _smooth){
    m_Tint = _smooth;
}

void IMIMtlWhiteBalance::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
//    _render->submitUniformf("m_temperature", m_Temperature);
//    _render->submitUniformf("m_tint", m_Tint);
}

IMIMtlGamma::IMIMtlGamma(IMIInstPtr _app)
:IMIMtlCore(_app,"gamma"){
    m_Gamma = 1.0f;
}

IMIMtlGamma::IMIMtlGamma(IMIMtlGamma* _mtl)
:IMIMtlCore(_mtl){
    m_Gamma=_mtl->m_Gamma;
}

IMIMtlGamma::~IMIMtlGamma(){
    
}

IMIMtlCorePtr IMIMtlGamma::clone(){
     return PointerSharedPtr<IMIMtlGamma>(new IMIMtlGamma(this));
}

void IMIMtlGamma::setGamma(f32 _smooth){
    m_Gamma=_smooth;
}

void IMIMtlGamma::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformf("m_gamma", m_Gamma);
}

IMIMtlExposure::IMIMtlExposure(IMIInstPtr _app)
:IMIMtlCore(_app,"Exposure"){
    m_Exposure=0.0f;
}

IMIMtlExposure::IMIMtlExposure(IMIMtlExposure* _mtl)
:IMIMtlCore(_mtl){
    m_Exposure = _mtl->m_Exposure;
}

IMIMtlExposure::~IMIMtlExposure(){
    m_Exposure = 0.0f;
}

IMIMtlCorePtr IMIMtlExposure::clone(){
    return PointerSharedPtr<IMIMtlExposure>(new IMIMtlExposure(this));
}

void IMIMtlExposure::setExposure(f32 _smooth){
    m_Exposure = _smooth;
}

void IMIMtlExposure::_submitMtl(IMIRendererPtr _render){
    IMIMtlCore::_submitMtl(_render);
    //_render->submitUniformf("m_exposure", m_Exposure);
}

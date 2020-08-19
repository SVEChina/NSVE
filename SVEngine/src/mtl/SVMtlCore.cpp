//
// SVMtlCore.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVMtlCore.h"
#include "SVSurface.h"
#include "../base/SVDataChunk.h"
#include "../operate/SVOpCreate.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"

#include "../rendercore/SVGL/SVRTexGL.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRShader.h"

using namespace sv;

/*
 纹理单元
 */
TexUnit::TexUnit(){
    m_texForm = E_TEX_END;
    m_pTex = nullptr;
    m_stage_type = 0;   //纹理使用阶段类型，0:fs 1:vs
    m_chn = -1;          //纹理使用的通道
};

TexUnit::~TexUnit(){
    m_pTex = nullptr;
}

void TexUnit::reset(){
    m_pTex = nullptr;
}

void TexUnit::copy(TexUnit& _texunit){
    m_pTex = _texunit.m_pTex;
    m_texForm = _texunit.m_texForm;
}

//
SVMtlCore::SVMtlCore(SVInstPtr _app)
:SVGBaseEx(_app){
    m_shader_obj = nullptr;
    reset();
}

//
SVMtlCore::SVMtlCore(SVInstPtr _app, cptr8 _shader)
:SVGBaseEx(_app)
,m_shader_name(_shader){
    m_shader_obj = nullptr;
    reset();
}

SVMtlCore::SVMtlCore(SVInstPtr _app, SVShaderPtr _shader)
:SVGBaseEx(_app)
,m_shader_obj(_shader){
}

SVMtlCore::SVMtlCore(SVMtlCore* _mtl)
:SVGBaseEx(_mtl->mApp){
}

SVMtlCore::~SVMtlCore() {
    reset();
}

SVMtlCorePtr SVMtlCore::clone() {
    return nullptr;
}

void SVMtlCore::reset() {
    m_LogicMtlFlag0 = 0;
    for(s32 i=0;i<MAX_TEXUNIT;i++){
        m_texUnit[i].reset();
    }
    //
    //融合参数
    m_blend_enable = 0;
    m_blend_src_param = 0;
    m_blend_dst_param = 0;
//    //裁剪面参数
//    m_cull_enable;
//    m_frontFace;
//    m_cullFace;
//    //深度参数
//    m_depth_clear;
//    m_depth_enable;        //开启深度测试
//    //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
//    m_depthtest_method;
//    //模板参数
//    m_stencil_clear;         //
//    m_stencil_enable;        //开启模板测试
//    m_stencil_passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
//    m_stencil_refValue;       //通过模板测试的参考值(0-255)
//    m_stencil_maskValue;      //掩码( 模板值&掩码 * 参考值&掩码 )
//    m_stencil_sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
//    m_stencil_zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
//    m_stencil_zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
//    //Z偏移参数
//    m_zoff_enable;
//    m_zoff_factor;
//    m_zoff_unit;
//    //alpha参数
//    m_alpha_enable;         //开启alpha测试
//    m_alpha_testMethod;     //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
}

void SVMtlCore::setTexture(s32 _chn,s32 _stage,SVINTEX _from,cptr8 _fname) {
    if(_chn<0 || _chn>=MAX_TEXUNIT) {
        return ;
    }
    m_texUnit[_chn].m_stage_type = _stage;
    m_texUnit[_chn].m_texForm = _from;
    m_texUnit[_chn].m_fname = _fname;
    m_texUnit[_chn].m_pTex = nullptr;
    if(E_TEX_FILE == _from) {
        //从文件加载纹理
        m_texUnit[_chn].m_pTex = mApp->getTexMgr()->getTexture(_fname);
    }else{
    }
}

//
void SVMtlCore::setTexture(s32 _chn,cptr8 _fname) {
    //从文件加载纹理
    if(_chn<0 || _chn>=MAX_TEXUNIT) {
        return ;
    }
    m_texUnit[_chn].m_fname = _fname;
    m_texUnit[_chn].m_texForm = E_TEX_FILE;
    SVTexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
    if(!t_tex) {
        t_tex = mApp->getTexMgr()->getSVETexture(); //error 报错 用默认纹理代替
    }
    m_texUnit[_chn].m_pTex = t_tex;
//    //
//    s32 t_flag = MTL_F0_TEX0;
//    t_flag = t_flag<<_chn;
//    m_LogicMtlFlag0 |= t_flag;
}

void SVMtlCore::setTexture(s32 _chn,sv::SVINTEX _from) {
    if(_chn<0 || _chn>=MAX_TEXUNIT)
        return;
    m_texUnit[_chn].m_fname = "default";
    m_texUnit[_chn].m_texForm = _from;
//    s32 t_flag = MTL_F0_TEX0;
//    t_flag = t_flag<<_chanel;
//    m_LogicMtlFlag0 |= t_flag;
}

void SVMtlCore::setTexture(s32 _chn,SVTexturePtr _texture) {
    if(_chn<0 || _chn>=MAX_TEXUNIT)
        return;
    m_texUnit[_chn].m_fname = _texture->m_name;
    m_texUnit[_chn].m_texForm = E_TEX_FILE;
    m_texUnit[_chn].m_pTex = _texture;
//    s32 t_flag = MTL_F0_TEX0;
//    t_flag = t_flag<<_chn;
//    m_LogicMtlFlag0 |= t_flag;
}

//逻辑更新
void SVMtlCore::update(f32 dt) {
    reloadShader();
}

void SVMtlCore::reloadShader(){
    if(m_shader_obj)
        return ;
    if(mApp->getShaderMgr()) {
        m_shader_obj = mApp->getShaderMgr()->getShader(m_shader_name.c_str());
    }
}

//提交参数到GPU
s32 SVMtlCore::submitMtl() {
    return 0;
}

//交换
void SVMtlCore::swap() {
    
}

void SVMtlCore::_submitUniform(SVRendererPtr _render) {
    
}

void SVMtlCore::_submitMtl(SVRendererPtr _render) {
    
}

void SVMtlCore::setBlendState(s32 _src , s32 _dst){
//    m_LogicParamBlend.srcParam = _src;
//    m_LogicParamBlend.dstParam = _dst;
}

void SVMtlCore::setBlendEnable(bool _bBlendEnable){
    //m_LogicParamBlend.enable = _bBlendEnable;
    m_LogicMtlFlag0 |= MTL_F0_BLEND;
}

void SVMtlCore::setCullEnable(bool _bCullEnable){
//    m_LogicParamCull.enable = _bCullEnable;
//    m_LogicMtlFlag0 |= MTL_F0_CULL;
}

void SVMtlCore::setCullFace(s32 _frontFace, s32 _cullFace){
//    m_LogicParamCull.frontFace = _frontFace;
//    m_LogicParamCull.cullFace = _cullFace;
}

void SVMtlCore::setDepthEnable(bool _bDepthEnable){
    //m_LogicParamDepth.enable = _bDepthEnable;
    m_LogicMtlFlag0 |= MTL_F0_DEPTH;
}

void SVMtlCore::setZOffEnable(bool _enable) {
    //m_LogicParamZOff.enable = _enable;
    m_LogicMtlFlag0 |= MTL_F0_ZOFF;
}

void SVMtlCore::setZOffParam(f32 _factor,f32 _unit) {
//    m_LogicParamZOff.m_factor = _factor;
//    m_LogicParamZOff.m_unit = _unit;
}

//设置模版测试
void SVMtlCore::setStencilEnable(bool _bStencilEnable) {
    //m_LogicParamStencil.enable = _bStencilEnable;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilClear(bool _clear) {
    //m_LogicParamStencil.clear = _clear;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilPass(s32 _pass) {
    //m_LogicParamStencil.passMethod = _pass;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilRef(s32 _ref) {
    //m_LogicParamStencil.refValue = _ref;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilMask(s32 _mask) {
    //m_LogicParamStencil.maskValue = _mask;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilZPass(s32 _method) {
    //m_LogicParamStencil.zpass = _method;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilZfail(s32 _method) {
    //m_LogicParamStencil.zfail = _method;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilSfail(s32 _method) {
    //m_LogicParamStencil.sfail = _method;
    m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::fromJSON1(RAPIDJSON_NAMESPACE::Value &_item){
    //材质名称
    if (_item.HasMember("name") && _item["name"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _item["name"];
        m_mtl_name = t_value.GetString();
    }else{
        return ;
    }
    //对应的shader
    if (_item.HasMember("shader") && _item["shader"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _item["shader"];
        m_shader_name = t_value.GetString();
    }else{
        return ;
    }
    //texture参数
    SVString t_chn = "chn";
    for(s32 i=0;i<8;i++) {
        t_chn.printf("chn%d",i);
        if (_item.HasMember(t_chn.c_str()) && _item[t_chn.c_str()].IsObject()) {
            RAPIDJSON_NAMESPACE::Document::Object element = _item[t_chn.c_str()].GetObject();
            SVString t_param_type = element["from"].GetString();
            SVString t_param_path = element["path"].GetString();
            SVString t_param_stage = element["stage"].GetString();
            s32 t_stage = 0;
            if(t_param_stage == "vs") {
                t_stage = 0;
            }else if(t_param_stage == "fs") {
                t_stage = 1;
            }
            //
            SVINTEX t_from;
            if(t_param_type == "file") {
                t_from = E_TEX_FILE;
            }else{
                t_from = E_TEX_MAIN;
            }
            setTexture(i, t_stage, t_from, t_param_path.c_str());
        }
    }
    //blend param 融合
    if (_item.HasMember("blend-param") && _item["blend-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["blend-param"].GetObject();
        m_blend_enable = t_value_obj["enable"].GetInt();
    }
    //stencil param 融合
    if (_item.HasMember("stencil-param") && _item["stencil-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["stencil-param"].GetObject();
        m_stencil_enable = t_value_obj["enable"].GetInt();
    }
    //alpha param 融合
    if (_item.HasMember("alpha-param") && _item["alpha-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["alpha-param"].GetObject();
        m_alpha_enable = t_value_obj["enable"].GetInt();
    }
}

//
void SVMtlCore::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                       RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

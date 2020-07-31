//
// SVMtlCore.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVMtlCore.h"
#include "SVGLModify.h"
#include "../base/SVDataChunk.h"
#include "../operate/SVOpCreate.h"
#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../rendercore/SVRenderScene.h"
#include "../rendercore/SVGL/SVRTexGL.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRShader.h"

using namespace sv;

//
SVMtlCore::SVMtlCore(SVInstPtr _app)
:SVGBaseEx(_app){
    m_shader_obj = nullptr;
    m_paramValues = MakeSharedPtr<SVDataChunk>();
    reset();
}

//
SVMtlCore::SVMtlCore(SVInstPtr _app, cptr8 _shader)
:SVGBaseEx(_app)
,m_shader_name(_shader){
    m_shader_obj = nullptr;
    m_paramValues = MakeSharedPtr<SVDataChunk>();
    reset();
}

SVMtlCore::SVMtlCore(SVInstPtr _app, SVShaderPtr _shader)
:SVGBaseEx(_app)
,m_shader_obj(_shader){
    if(m_shader_obj) {
        //m_shader_name = m_shader_obj->
    }
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
    //
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

void SVMtlCore::addParam(cptr8 _name,cptr8 _type,cptr8 _value)  {
    if( strcmp(_type,"s32") == 0) {
        s32 tmp = atoi(_value);
        if(strcmp(_value,"identify") == 0) {
            setParam(_name,1);
        }else{
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"f32") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            setParam(_name,1.0f);
        }else{
            f32 tmp = atof(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fvec2") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec2 tmp = FVec2_one;;
            setParam(_name,tmp);
        }else{
            FVec2 tmp(_value);
            setParam(_name,tmp);
        }
        
    }else if( strcmp(_type,"fvec3") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec3 tmp = FVec3_one;
            setParam(_name,tmp);
        }else{
            FVec3 tmp(_value);
            setParam(_name,tmp);
        }
        
    }else if( strcmp(_type,"fvec4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FVec4 tmp = FVec4_one;
            setParam(_name,tmp);
        }else{
            FVec4 tmp(_value);
            setParam(_name,tmp);
        }
    }else if( strcmp(_type,"fmat4") == 0 ) {
        if(strcmp(_value,"identify") == 0) {
            FMat4 tmp;
            tmp.setIdentity();
            setParam(_name,tmp);
        }else{
            FMat4 tmp(_value);
            setParam(_name,tmp);
        }
    }
}

void SVMtlCore::setParam(cptr8 _name,s32 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_INT;
    t_param.m_size = sizeof(s32);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void SVMtlCore::setParam(cptr8 _name,f32 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_FLOAT;
    t_param.m_size = sizeof(f32);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void SVMtlCore::setParam(cptr8 _name,FVec2 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_FVEC2;
    t_param.m_size = sizeof(FVec2);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void SVMtlCore::setParam(cptr8 _name,FVec3 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_FVEC3;
    t_param.m_size = sizeof(FVec3);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void SVMtlCore::setParam(cptr8 _name,FVec4 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_FVEC4;
    t_param.m_size = sizeof(FVec4);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void SVMtlCore::setParam(cptr8 _name,FMat4 _value) {
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            m_paramValues->set(m_paramTbl[i].m_off,_value);
            return ;
        }
    }
    //推送目标参数
    MtlParamDsp t_param;
    t_param.m_name = _name;
    t_param.m_type = SV_FMAT4;
    t_param.m_size = sizeof(FMat4);
    t_param.m_off = m_paramValues->push(_value);
    m_paramTbl.push_back(t_param);
}

void* SVMtlCore::getParam(cptr8 _name) {
    u64 t_off = 0;
    for(int i=0;i<m_paramTbl.size();i++) {
        if( strcmp( m_paramTbl[i].m_name.c_str() ,_name) == 0 ) {
            //找到目标参数 ，拷贝即可
            t_off = m_paramTbl[i].m_off;
            break;
        }
    }
    return m_paramValues->getPointer(t_off);
}

//
void SVMtlCore::setTexture(s32 _chanel,cptr8 _fname) {
    //从文件加载纹理
    if(_chanel<0 || _chanel>=MAX_TEXUNIT) {
         //error 报错
        return ;
    }
    SVTexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
    if(!t_tex) {
        //error 报错 用默认纹理代替
        t_tex = mApp->getTexMgr()->getSVETexture();
    }
    //
    m_texUnit[_chanel].m_pTex = t_tex;
    //
    s32 t_flag = MTL_F0_TEX0;
    t_flag = t_flag<<_chanel;
    m_LogicMtlFlag0 |= t_flag;
}

void SVMtlCore::setTexture(s32 _chanel,sv::SVTEXINID _from) {
    if(_chanel<0 || _chanel>=MAX_TEXUNIT)
        return;
    m_texUnit[_chanel].m_texForm = _from;
    s32 t_flag = MTL_F0_TEX0;
    t_flag = t_flag<<_chanel;
    m_LogicMtlFlag0 |= t_flag;
}

void SVMtlCore::setTexture(s32 _chanel,SVTexturePtr _texture) {
    if(_chanel<0 || _chanel>=MAX_TEXUNIT)
        return;
    //
    m_texUnit[_chanel].m_pTex = _texture;
    //
    s32 t_flag = MTL_F0_TEX0;
    t_flag = t_flag<<_chanel;
    m_LogicMtlFlag0 |= t_flag;
}

void SVMtlCore::setTextureParam(s32 _chanel,TEXTUREPARAM _type,s32 _value) {
    if(_chanel>=0 && _chanel<MAX_TEXUNIT) {
        if(_type == E_T_PARAM_FILTER_MAG) {
            //filter_max
            m_texUnit[_chanel].m_mag_filter = _value;
        }else if(_type == E_T_PARAM_FILTER_MIN) {
            //filter_min
            m_texUnit[_chanel].m_min_filter = _value;
        }else if(_type == E_T_PARAM_WRAP_S) {
            //wrap_s
            m_texUnit[_chanel].m_s_wrap = _value;
        }else if(_type == E_T_PARAM_WRAP_T) {
            //wrap_t
            m_texUnit[_chanel].m_t_wrap = _value;
        }
    }
}

//逻辑更新
void SVMtlCore::update(f32 dt) {
}

void SVMtlCore::reloadShader(){
    //m_shader_name
    if(mApp->getShaderMgr()) {
        m_shader_obj = mApp->getShaderMgr()->getShader(m_shader_name.c_str());
    }
}

//提交参数到GPU
s32 SVMtlCore::submitMtl() {
    return 0;
}

void SVMtlCore::recoverMtl() {
    SVRendererPtr t_renderer = mApp->getRenderer();
    if(!t_renderer)
        return ;
    //融合
    if((m_LogicMtlFlag0&MTL_F0_BLEND)>0){
        //m_LogicParamBlend.enable = false;
        //t_renderer->submitBlend(m_LogicParamBlend);
    }
    //隐藏面消除
    if((m_LogicMtlFlag0&MTL_F0_CULL)>0){
        //m_LogicParamCull.enable = false;
    }
    //模板测试
    if((m_LogicMtlFlag0&MTL_F0_STENCIL)>0){
//        m_LogicParamStencil.enable = false;
//        m_LogicParamStencil.clear = false;
    }
    //alpha测试
    if((m_LogicMtlFlag0&MTL_F0_ALPHA)>0){
    }
    //深度测试
    if((m_LogicMtlFlag0&MTL_F0_DEPTH)>0){
//        m_LogicParamDepth.enable = false;
//        t_renderer->submitDepth(m_LogicParamDepth);
    }
    //Z冲突
    if((m_LogicMtlFlag0&MTL_F0_ZOFF)>0){
        //m_LogicParamZOff.enable = false;
        //t_renderer->submitZOff(m_LogicParamZOff);
    }
}


//交换
void SVMtlCore::swap() {
    
}

void SVMtlCore::_submitUniform(SVRendererPtr _render) {
}

//void SVMtlCore::_submitState(SVRendererPtr _render) {
////    //更新纹理
////    if((m_LogicMtlFlag0&MTL_F0_TEX0)>0){
////        _render->submitTex(0, m_paramTex.m_texUnit[0]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX1)>0){
////        _render->submitTex(1, m_paramTex.m_texUnit[1]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX2)>0){
////        _render->submitTex(2, m_paramTex.m_texUnit[2]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX3)>0){
////        _render->submitTex(3, m_paramTex.m_texUnit[3]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX4)>0){
////        _render->submitTex(4, m_paramTex.m_texUnit[4]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX5)>0){
////        _render->submitTex(5, m_paramTex.m_texUnit[5]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX6)>0){
////        _render->submitTex(6, m_paramTex.m_texUnit[6]);
////    }
////    if((m_LogicMtlFlag0&MTL_F0_TEX7)>0){
////        _render->submitTex(7, m_paramTex.m_texUnit[7]);
////    }
////    //
////    if((m_LogicMtlFlag0&MTL_F0_LINE_SIZE)>0){
////        //_render->submitLineWidth(m_LogicParamSize.m_linewidth);
////    }
////    //融合
////    if((m_LogicMtlFlag0&MTL_F0_BLEND)>0){
////        //_render->submitBlend(m_LogicParamBlend);
////    }
////    //隐藏面消除
////    if((m_LogicMtlFlag0&MTL_F0_CULL)>0){
////        //_render->submitCull(m_LogicParamCull);
////    }
////    //模板测试
////    if((m_LogicMtlFlag0&MTL_F0_STENCIL)>0){
////    }
////    //alpha测试
////    if((m_LogicMtlFlag0&MTL_F0_ALPHA)>0){
////    }
////    //深度测试
////    if((m_LogicMtlFlag0&MTL_F0_DEPTH)>0){
////    }
////    //Z冲突
////    if((m_LogicMtlFlag0&MTL_F0_ZOFF)>0){
////        //_render->submitZOff(m_LogicParamZOff);
////    }else{
////        //_render->submitZOff(m_LogicParamZOff);
////    }
//}

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
    if (_item.HasMember("shader") && _item["shader"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _item["shader"];
        m_shader_name = t_value.GetString();
    }else{
        return ;
    }
    //uniform参数
    if (_item.HasMember("param-tbl") && _item["param-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _item["param-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            SVString t_param_name = element["name"].GetString();
            SVString t_param_type = element["type"].GetString();
            SVString t_param_value = element["value"].GetString();
            addParam(t_param_name.c_str(),t_param_type.c_str(),t_param_value.c_str());
        }
    }
    //texture参数
    if (_item.HasMember("texture-tbl") && _item["texture-tbl"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_value_array = _item["texture-tbl"].GetArray();
        for(s32 i=0;i<t_value_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object element = t_value_array[i].GetObject();
            s32 t_param_chan = element["chn"].GetInt();
            SVString t_param_type = element["from"].GetString();
            SVString t_param_path = element["path"].GetString();
            if(t_param_type == "file") {
                setTexture(t_param_chan, t_param_path.c_str());
            }else if(t_param_type == "inner") {
                if(t_param_path == "SV_MAIN") {
                    setTexture(t_param_chan,E_TEX_MAIN);
                }
            }
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
                       RAPIDJSON_NAMESPACE::Value &_objValue){
}

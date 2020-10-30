//
// SVMtlCore.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//


#include "SVMtlCore.h"
#include "SVSurface.h"
#include "SVTexMgr.h"
#include "SVTexture.h"
#include "../base/SVDataChunk.h"
#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRShader.h"

using namespace sv;

/*
 纹理单元
 */

static void lua_regist_TexUnit(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
        
    }
}

static void lua_regist_SVMtlCore(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
        
    }
}

LUA_REG_IMP(TexUnit,lua_regist_TexUnit);
LUA_REG_IMP(SVMtlCore,lua_regist_SVMtlCore);

TexUnit::TexUnit(){
    m_texForm = E_TEX_END;
    m_pTex = nullptr;
    m_stage_type = 0;   //纹理使用阶段类型，0:fs 1:vs
    m_chn = -1;         //纹理使用的通道
};

TexUnit::~TexUnit(){
    m_pTex = nullptr;
}

void TexUnit::reset(){
    m_pTex = nullptr;
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
    m_shader_defs.clear();
    reset();
}

SVMtlCore::SVMtlCore(SVInstPtr _app, SVShaderPtr _shader)
:SVGBaseEx(_app)
,m_shader_obj(_shader){
    m_shader_defs.clear();
    reset();
}

SVMtlCore::SVMtlCore(SVMtlCore* _mtl)
:SVGBaseEx(_mtl->mApp){
    m_shader_defs.clear();
    reset();
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
        m_vs_texUnit[i].reset();
        m_fs_texUnit[i].reset();
    }
    //
    //融合参数
    m_blend_enable = 0;
    m_blend_src_param = 0;
    m_blend_dst_param = 0;
    //裁剪面参数
    m_cull_enable = 0;
    m_frontFace = SV_CCW;
    m_cullFace = SV_BACK;
//    //深度参数
//    m_depth_clear;
//    m_depth_enable;        //开启深度测试
//    //深度测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
//    m_depth_method;
//    //模板参数
//    m_stencil_clear;         //
//    m_stencil_enable;        //开启模板测试
//    m_stencil_passMethod;     //通过模板测试的规则(GL_NEVER,GL_LESS < ,GL_LEQUAL <= ,GL_GREATER > ,GL_GEEQUAL >= ,GL_EQUAL == ,GL_ALWAYS)
//    m_stencil_ref;       //通过模板测试的参考值(0-255)
//    m_stencil_mask;      //掩码( 模板值&掩码 * 参考值&掩码 )
//    m_stencil_sfail;          //模板测试失败     (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
//    m_stencil_zfail;          //模板通过 深度失败 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写入),GL_INCR,GL_DECR,GL_INVERT(按位取反))
//    m_stencil_zpass;          //模板通过 深度通过 (GL_KEEP,GL_ZERO,GL_REPLACE(参考值代替写≤
//    //Z偏移参数
//    m_zoff_enable;
//    m_zoff_factor;
//    m_zoff_unit;
//    //alpha参数
//    m_alpha_enable;         //开启alpha测试
//    m_alpha_method;     //alpha测试方法(GL_NEVER,GL_ALWAYS,GL_LESS,GL_LEQUAL,GL_GREATER,GL_GEQUAL,GL_NOTEQUAL)
}

void SVMtlCore::setTexture(s32 _chn,s32 _stage,SV_TEXIN _from,cptr8 _fname) {
    if(_chn<0 || _chn>=MAX_TEXUNIT) {
        return ;
    }
    if(_stage == 0) {
        m_vs_texUnit[_chn].m_stage_type = _stage;
        m_vs_texUnit[_chn].m_texForm = _from;
        m_vs_texUnit[_chn].m_fname = _fname;
        m_vs_texUnit[_chn].m_pTex = nullptr;
        if(E_TEX_FILE == _from) {
            m_vs_texUnit[_chn].m_pTex = mApp->getTexMgr()->getTexture(_fname);
        }
    } else if(_stage == 1) {
        m_fs_texUnit[_chn].m_stage_type = _stage;
        m_fs_texUnit[_chn].m_texForm = _from;
        m_fs_texUnit[_chn].m_fname = _fname;
        m_fs_texUnit[_chn].m_pTex = nullptr;
        if(E_TEX_FILE == _from) {
            m_fs_texUnit[_chn].m_pTex = mApp->getTexMgr()->getTexture(_fname);
        }
    }
}

//
void SVMtlCore::setTexture(s32 _chn,s32 _stage,cptr8 _fname) {
    //从文件加载纹理
    if(_chn<0 || _chn>=MAX_TEXUNIT) {
        return ;
    }
    if(_stage == 0) {
        m_vs_texUnit[_chn].m_fname = _fname;
        m_vs_texUnit[_chn].m_texForm = E_TEX_FILE;
        SVTexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
        if(!t_tex) {
            t_tex = mApp->getTexMgr()->getSVETexture(); //error 报错 用默认纹理代替
        }
        m_vs_texUnit[_chn].m_pTex = t_tex;
    }else if(_stage == 1) {
        m_fs_texUnit[_chn].m_fname = _fname;
        m_fs_texUnit[_chn].m_texForm = E_TEX_FILE;
        SVTexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
        if(!t_tex) {
            t_tex = mApp->getTexMgr()->getSVETexture(); //error 报错 用默认纹理代替
        }
        m_fs_texUnit[_chn].m_pTex = t_tex;
    }
}

void SVMtlCore::setTexture(s32 _chn,s32 _stage,sv::SV_TEXIN _from) {
    if(_chn<0 || _chn>=MAX_TEXUNIT)
        return;
    if(_stage == 0) {
        m_vs_texUnit[_chn].m_fname = "default";
        m_vs_texUnit[_chn].m_texForm = _from;
    }else if(_stage == 1) {
        m_fs_texUnit[_chn].m_fname = "default";
        m_fs_texUnit[_chn].m_texForm = _from;
    }
}

void SVMtlCore::setTexture(s32 _chn,s32 _stage,SVTexturePtr _texture) {
    if(_chn<0 || _chn>=MAX_TEXUNIT)
        return;
    if(_stage == 0) {
        m_vs_texUnit[_chn].m_fname = _texture->m_name;
        m_vs_texUnit[_chn].m_texForm = E_TEX_FILE;
        m_vs_texUnit[_chn].m_pTex = _texture;
    }else if(_stage == 1) {
        m_fs_texUnit[_chn].m_fname = _texture->m_name;
        m_fs_texUnit[_chn].m_texForm = E_TEX_FILE;
        m_fs_texUnit[_chn].m_pTex = _texture;
    }
}

//逻辑更新
void SVMtlCore::update(f32 dt) {
    reloadShader();
    if(m_script!="") {
    }
}

void SVMtlCore::reloadShader(){
    if(m_shader_obj)
        return ;
    if( mApp->getShaderMgr() ) {
        s32 t_code =  mApp->getShaderMgr()->getDefCode(m_shader_defs);
        m_shader_obj = mApp->getShaderMgr()->getShader(m_shader_name.c_str(),t_code);
        if(!m_shader_obj) {
            //需要加载新的shader
            m_shader_obj = mApp->getShaderMgr()->loadSDSP(m_shader_name.c_str(),m_shader_defs);
        }
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
    m_blend_src_param = _src;
    m_blend_dst_param = _dst;
}

void SVMtlCore::setBlendEnable(bool _enable){
     m_blend_enable = _enable;
}

void SVMtlCore::setCullEnable(bool _enable){
     m_cull_enable = _enable;
}

void SVMtlCore::setCullFace(s32 _frontFace, s32 _cullFace){
    m_frontFace = _frontFace;
    m_cullFace = _cullFace;
}

void SVMtlCore::setDepthEnable(bool _enable){
    m_depth_enable = _enable;
}

void SVMtlCore::setZOffEnable(bool _enable) {
    m_zoff_enable = _enable;
}

void SVMtlCore::setZOffParam(f32 _factor,f32 _unit) {
    m_zoff_factor = _factor;
    m_zoff_unit = _unit;
}

//设置模版测试
void SVMtlCore::setStencilEnable(bool _enable) {
    m_stencil_enable = _enable;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilClear(bool _clear) {
    //m_LogicParamStencil.clear = _clear;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilPass(s32 _pass) {
    //m_LogicParamStencil.passMethod = _pass;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilRef(s32 _ref) {
    //m_LogicParamStencil.refValue = _ref;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilMask(s32 _mask) {
    //m_LogicParamStencil.maskValue = _mask;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilZPass(s32 _method) {
    //m_LogicParamStencil.zpass = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilZfail(s32 _method) {
    //m_LogicParamStencil.zfail = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::setStencilSfail(s32 _method) {
    //m_LogicParamStencil.sfail = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void SVMtlCore::fromJSON1(RAPIDJSON_NAMESPACE::Value& _item){
    //对应的shader
    if (_item.HasMember("shader") && _item["shader"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _item["shader"];
        m_shader_name = t_value.GetString();
        s32 t_pos = m_shader_name.rfind('.');
        if(t_pos>0) {
            m_shader_name = SVString::substr(m_shader_name.c_str(), 0, t_pos);
        }
    }else{
        return ;
    }
    //ssdef参数
    if (_item.HasMember("ssdef") && _item["ssdef"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_array = _item["ssdef"].GetArray();
        for(s32 i=0;i<t_array.Size();i++) {
            //拼接shader宏
            SVString t_def_str = t_array[i].GetString();
            m_shader_defs.push_back(t_def_str);
        }
    }
    //texture参数
    if (_item.HasMember("textures") && _item["textures"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_texs = _item["textures"].GetArray();
        for(s32 i=0;i<t_texs.Size();i++) {
            //
            RAPIDJSON_NAMESPACE::Document::Object element = t_texs[i].GetObject();
            s32 t_param_chn = element["chn"].GetInt();
            SVString t_param_type = element["from"].GetString();
            SVString t_param_path = element["path"].GetString();
            SVString t_param_stage = element["stage"].GetString();
            s32 t_stage = 0;
            if(t_param_stage == "vs") {
                t_stage = 0;
            }else if(t_param_stage == "fs") {
                t_stage = 1;
            }
            SV_TEXIN t_from;
            if(t_param_type == "file") {
                t_from = E_TEX_FILE;
            }else{
                t_from = E_TEX_MAIN;
            }
            setTexture(t_param_chn, t_stage, t_from, t_param_path.c_str());
        }
    }
    
    //blend param 融合
    if (_item.HasMember("blend-param") && _item["blend-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["blend-param"].GetObject();
        m_blend_enable = t_value_obj["enable"].GetInt();
        if( t_value_obj.HasMember("src") && t_value_obj["src"].IsString() ) {
            SVString t_src_str = t_value_obj["src"].GetString();
            if(t_src_str == "BLEND_NONE" ) {
                m_blend_src_param = BLEND_NONE;
            }else if(t_src_str == "BLEND_ZERO" ) {
                m_blend_src_param = BLEND_ZERO;
            }else if(t_src_str == "BLEND_ONE" ) {
                m_blend_src_param = BLEND_ONE;
            }else if(t_src_str == "BLEND_SRC_COLOR" ) {
                m_blend_src_param = BLEND_SRC_COLOR;
            }else if(t_src_str == "BLEND_ONE_MINUS_SRC_COLOR" ) {
                m_blend_src_param = BLEND_ONE_MINUS_SRC_COLOR;
            }else if(t_src_str == "BLEND_SRC_ALPHA" ) {
                m_blend_src_param = BLEND_SRC_ALPHA;
            }else if(t_src_str == "BLEND_ONE_MINUS_SRC_ALPHA" ) {
                m_blend_src_param = BLEND_ONE_MINUS_SRC_ALPHA;
            }else if(t_src_str == "BLEND_DST_COLOR" ) {
                m_blend_src_param = BLEND_DST_COLOR;
            }else if(t_src_str == "BLEND_ONE_MINUS_DST_COLOR" ) {
                m_blend_src_param = BLEND_ONE_MINUS_DST_COLOR;
            }else if(t_src_str == "BLEND_DST_ALPHA" ) {
                m_blend_src_param = BLEND_DST_ALPHA;
            }else if(t_src_str == "BLEND_ONE_MINUS_DEST_ALPHA" ) {
                m_blend_src_param = BLEND_ONE_MINUS_DEST_ALPHA;
            }else if(t_src_str == "BLEND_SRC1_COLOR" ) {
                m_blend_src_param = BLEND_SRC1_COLOR;
            }else if(t_src_str == "BLEND_ONE_MINUS_SRC1_COLOR" ) {
                m_blend_src_param = BLEND_ONE_MINUS_SRC1_COLOR;
            }else if(t_src_str == "BLEND_SRC1_ALPHA" ) {
                m_blend_src_param = BLEND_SRC1_ALPHA;
            }else if(t_src_str == "BLEND_ONE_MINUS_SRC1_ALPHA" ) {
                m_blend_src_param = BLEND_ONE_MINUS_SRC1_ALPHA;
            }
        }else{
            m_blend_src_param = BLEND_SRC_ALPHA;
        }
        //
        if( t_value_obj.HasMember("dst") && t_value_obj["dst"].IsString() ) {
            SVString t_dst_str = t_value_obj["dst"].GetString();
            if(t_dst_str == "BLEND_NONE" ) {
                m_blend_dst_param = BLEND_NONE;
            }else if(t_dst_str == "BLEND_ZERO" ) {
                m_blend_dst_param = BLEND_ZERO;
            }else if(t_dst_str == "BLEND_ONE" ) {
                m_blend_dst_param = BLEND_ONE;
            }else if(t_dst_str == "BLEND_SRC_COLOR" ) {
                m_blend_dst_param = BLEND_SRC_COLOR;
            }else if(t_dst_str == "BLEND_ONE_MINUS_SRC_COLOR" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_SRC_COLOR;
            }else if(t_dst_str == "BLEND_SRC_ALPHA" ) {
                m_blend_dst_param = BLEND_SRC_ALPHA;
            }else if(t_dst_str == "BLEND_ONE_MINUS_SRC_ALPHA" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_SRC_ALPHA;
            }else if(t_dst_str == "BLEND_DST_COLOR" ) {
                m_blend_dst_param = BLEND_DST_COLOR;
            }else if(t_dst_str == "BLEND_ONE_MINUS_DST_COLOR" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_DST_COLOR;
            }else if(t_dst_str == "BLEND_DST_ALPHA" ) {
                m_blend_dst_param = BLEND_DST_ALPHA;
            }else if(t_dst_str == "BLEND_ONE_MINUS_DEST_ALPHA" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_DEST_ALPHA;
            }else if(t_dst_str == "BLEND_SRC1_COLOR" ) {
                m_blend_dst_param = BLEND_SRC1_COLOR;
            }else if(t_dst_str == "BLEND_ONE_MINUS_SRC1_COLOR" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_SRC1_COLOR;
            }else if(t_dst_str == "BLEND_SRC1_ALPHA" ) {
                m_blend_dst_param = BLEND_SRC1_ALPHA;
            }else if(t_dst_str == "BLEND_ONE_MINUS_SRC1_ALPHA" ) {
                m_blend_dst_param = BLEND_ONE_MINUS_SRC1_ALPHA;
            }
        }else{
            m_blend_dst_param = BLEND_ONE_MINUS_SRC_COLOR;
        }
    }else{
        //默认blend
        m_blend_enable = 0;
        m_blend_src_param = BLEND_SRC_ALPHA;
        m_blend_dst_param = BLEND_ONE_MINUS_SRC_COLOR;
    }
    
    //stencil param
    if (_item.HasMember("stencil-param") && _item["stencil-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["stencil-param"].GetObject();
        m_stencil_enable = t_value_obj["enable"].GetInt();
    }else{
        //默认stencil
        m_stencil_enable = 0;
        m_stencil_clear = 0;
        m_stencil_passMethod = 0;
        m_stencil_ref = 0;
        m_stencil_mask = 0;
        m_stencil_sfail = 0;
        m_stencil_zfail = 0;
        m_stencil_zpass = 0;
    }
    
    //alpha param 融合
    if (_item.HasMember("alpha-param") && _item["alpha-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["alpha-param"].GetObject();
        m_alpha_enable = t_value_obj["enable"].GetInt();
    }else{
        //默认alpha
        m_alpha_enable = 0;
        m_alpha_method = 0;
    }
    
    //depth param
    if (_item.HasMember("depth-param") && _item["depth-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["depth-param"].GetObject();
        m_depth_enable = t_value_obj["enable"].GetInt();
    }else{
        //默认depth
        m_depth_enable = 0;
    }
    
    //cull param
    if (_item.HasMember("cull-param") && _item["cull-param"].IsObject()) {
        RAPIDJSON_NAMESPACE::Document::Object t_value_obj = _item["cull-param"].GetObject();
        m_cull_enable = t_value_obj["enable"].GetInt();
//        m_frontFace = t_value_obj["enable"].GetInt();//SV_CCW;
//        m_cullFace = t_value_obj["enable"].GetInt();//SV_BACK;
    }else{
        //默认cull
        m_cull_enable = 0;
        m_frontFace = SV_CCW;
        m_cullFace = SV_BACK;
    }
}

//
void SVMtlCore::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                       RAPIDJSON_NAMESPACE::Value &_objValue) {
}

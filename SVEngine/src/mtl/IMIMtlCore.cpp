//
// IMIMtlCore.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//


#include "IMIMtlCore.h"
#include "IMISurface.h"
#include "IMITexMgr.h"
#include "IMITexture.h"
#include "../base/IMIDataChunk.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRShader.h"

using namespace imi;

/*
 纹理单元
 */

static void lua_regist_TexUnit(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
        
    }
}

static void lua_regist_IMIMtlCore(void* ls) {
    lua_State* L = (lua_State*)ls;
    if(L) {
        
    }
}

LUA_REG_IMP(TexUnit,lua_regist_TexUnit);
LUA_REG_IMP(IMIMtlCore,lua_regist_IMIMtlCore);

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
IMIMtlCore::IMIMtlCore(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_shader_obj = nullptr;
    reset();
}

//
IMIMtlCore::IMIMtlCore(IMIInstPtr _app, cptr8 _shader)
:IMIGBaseEx(_app)
,m_shader_name(_shader){
    m_shader_obj = nullptr;
    m_shader_defs.clear();
    reset();
}

IMIMtlCore::IMIMtlCore(IMIInstPtr _app, IMIShaderPtr _shader)
:IMIGBaseEx(_app)
,m_shader_obj(_shader){
    m_shader_defs.clear();
    reset();
}

IMIMtlCore::IMIMtlCore(IMIMtlCore* _mtl)
:IMIGBaseEx(_mtl->mApp){
    m_shader_defs.clear();
    reset();
}

IMIMtlCore::~IMIMtlCore() {
    reset();
}

IMIMtlCorePtr IMIMtlCore::clone() {
    return nullptr;
}

void IMIMtlCore::reset() {
    m_shader_dirty = true;
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
    m_frontFace = IMI_CCW;
    m_cullFace = IMI_BACK;
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

void IMIMtlCore::setTexture(s32 _chn,s32 _stage,IMI_TEXIN _from,cptr8 _fname) {
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
void IMIMtlCore::setTexture(s32 _chn,s32 _stage,cptr8 _fname) {
    //从文件加载纹理
    if(_chn<0 || _chn>=MAX_TEXUNIT) {
        return ;
    }
    if(_stage == 0) {
        m_vs_texUnit[_chn].m_fname = _fname;
        m_vs_texUnit[_chn].m_texForm = E_TEX_FILE;
        IMITexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
        if(!t_tex) {
            t_tex = mApp->getTexMgr()->getIMITexture(); //error 报错 用默认纹理代替
        }
        m_vs_texUnit[_chn].m_pTex = t_tex;
    }else if(_stage == 1) {
        m_fs_texUnit[_chn].m_fname = _fname;
        m_fs_texUnit[_chn].m_texForm = E_TEX_FILE;
        IMITexturePtr t_tex = mApp->getTexMgr()->getTexture(_fname);
        if(!t_tex) {
            t_tex = mApp->getTexMgr()->getIMITexture(); //error 报错 用默认纹理代替
        }
        m_fs_texUnit[_chn].m_pTex = t_tex;
    }
}

void IMIMtlCore::setTexture(s32 _chn,s32 _stage,imi::IMI_TEXIN _from) {
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

void IMIMtlCore::setTexture(s32 _chn,s32 _stage,IMITexturePtr _texture) {
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
void IMIMtlCore::update(f32 dt) {
    reloadShader();
    if(m_script!="") {
    }
}

void IMIMtlCore::reloadShader(){
    if(m_shader_dirty) {
        m_shader_dirty = false;
        m_shader_obj = nullptr;
    }
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

void IMIMtlCore::setShader(ptr8 _sname,std::vector<IMIString>& _sdef) {
    m_shader_name = _sname;
    m_shader_defs.clear();
    for(s32 i=0;i<_sdef.size();i++) {
        m_shader_defs.push_back(_sdef[i]);
    }
    m_shader_dirty = true;
}

//提交参数到GPU
s32 IMIMtlCore::submitMtl() {
    return 0;
}

//交换
void IMIMtlCore::swap() {
}

void IMIMtlCore::_submitUniform(IMIRendererPtr _render) {
}

void IMIMtlCore::_submitMtl(IMIRendererPtr _render) {
}

void IMIMtlCore::setBlendState(s32 _src , s32 _dst){
    m_blend_src_param = _src;
    m_blend_dst_param = _dst;
}

void IMIMtlCore::setBlendEnable(bool _enable){
     m_blend_enable = _enable;
}

void IMIMtlCore::setBlendSeparateEnable(bool _enable) {
    m_blend_separate_enable = _enable;
}
void IMIMtlCore::setBlendSeparateState(s32 _srcRGB, s32 _dstRGB, s32 _srcAlpha, s32 _dstAlpha, s32 _equation) {
    m_blend_separate_src_rgb = _srcRGB;
    m_blend_separate_dst_rgb = _dstRGB;
    m_blend_separate_src_alpha = _srcAlpha;
    m_blend_separate_dst_alpha = _dstAlpha;
    m_blend_separate_equation = _equation;
}

void IMIMtlCore::setCullEnable(bool _enable){
     m_cull_enable = _enable;
}

void IMIMtlCore::setCullFace(s32 _frontFace, s32 _cullFace){
    m_frontFace = _frontFace;
    m_cullFace = _cullFace;
}

void IMIMtlCore::setDepthEnable(bool _enable){
    m_depth_enable = _enable;
}

void IMIMtlCore::setDepthMethod(s32 _method) {
    m_depth_method = _method;
}

void IMIMtlCore::setZOffEnable(bool _enable) {
    m_zoff_enable = _enable;
}

void IMIMtlCore::setZOffParam(f32 _factor,f32 _unit) {
    m_zoff_factor = _factor;
    m_zoff_unit = _unit;
}

//设置模版测试
void IMIMtlCore::setStencilEnable(bool _enable) {
    m_stencil_enable = _enable;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilClear(bool _clear) {
    //m_LogicParamStencil.clear = _clear;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilPass(s32 _pass) {
    //m_LogicParamStencil.passMethod = _pass;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilRef(s32 _ref) {
    //m_LogicParamStencil.refValue = _ref;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilMask(s32 _mask) {
    //m_LogicParamStencil.maskValue = _mask;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilZPass(s32 _method) {
    //m_LogicParamStencil.zpass = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilZfail(s32 _method) {
    //m_LogicParamStencil.zfail = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::setStencilSfail(s32 _method) {
    //m_LogicParamStencil.sfail = _method;
    //m_LogicMtlFlag0 |= MTL_F0_STENCIL;
}

void IMIMtlCore::fromJSON1(RAPIDJSON_NAMESPACE::Value& _item){
    //对应的shader
    if (_item.HasMember("shader") && _item["shader"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &t_value = _item["shader"];
        m_shader_name = t_value.GetString();
        s32 t_pos = m_shader_name.rfind('.');
        if(t_pos>0) {
            m_shader_name = IMIString::substr(m_shader_name.c_str(), 0, t_pos);
        }
    }else{
        return ;
    }
    //ssdef参数
    if (_item.HasMember("ssdef") && _item["ssdef"].IsArray()) {
        RAPIDJSON_NAMESPACE::Document::Array t_array = _item["ssdef"].GetArray();
        for(s32 i=0;i<t_array.Size();i++) {
            //拼接shader宏
            IMIString t_def_str = t_array[i].GetString();
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
            IMIString t_param_type = element["from"].GetString();
            IMIString t_param_path = element["path"].GetString();
            IMIString t_param_stage = element["stage"].GetString();
            s32 t_stage = 0;
            if(t_param_stage == "vs") {
                t_stage = 0;
            }else if(t_param_stage == "fs") {
                t_stage = 1;
            }
            IMI_TEXIN t_from;
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
            IMIString t_src_str = t_value_obj["src"].GetString();
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
            IMIString t_dst_str = t_value_obj["dst"].GetString();
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
//        m_frontFace = t_value_obj["enable"].GetInt();//IMI_CCW;
//        m_cullFace = t_value_obj["enable"].GetInt();//IMI_BACK;
    }else{
        //默认cull
        m_cull_enable = 0;
        m_frontFace = IMI_CCW;
        m_cullFace = IMI_BACK;
    }
}

//
void IMIMtlCore::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                       RAPIDJSON_NAMESPACE::Value &_objValue) {
    
}

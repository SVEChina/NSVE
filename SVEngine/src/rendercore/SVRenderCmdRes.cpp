//
// SVRenderCmdRes.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderCmdRes.h"
#include "SVRenderMesh.h"
#include "SVRenderer.h"
#include "SVRMeshRes.h"
#include "SVRShader.h"
#include "SVRTex.h"
#include "SVRTarget.h"
#include "SVRFbo.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVShader.h"

using namespace sv;

SVRCmdCreateMesh::SVRCmdCreateMesh(SVRenderMeshPtr _mesh)
:m_rendermesh(_mesh){
}

SVRCmdCreateMesh::~SVRCmdCreateMesh() {
    m_rendermesh = nullptr;
}

void SVRCmdCreateMesh::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if(m_rendermesh && _renderer) {
        SVRMeshResPtr t_rbuffer = _renderer->createResBuf() ;
        t_rbuffer->m_logic_obj = m_rendermesh;
        m_rendermesh->bindRes(t_rbuffer);
        //
        t_rbuffer->create(_renderer);
        _renderer->addRes(t_rbuffer);
        SV_LOG_ERROR("sve create mesh end!\n");
    }
}

//
SVRCmdCreateShader::SVRCmdCreateShader(SVShaderPtr _shader)
:m_shader(_shader){

}

SVRCmdCreateShader::~SVRCmdCreateShader() {
    m_shader = nullptr;
}

void SVRCmdCreateShader::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if(m_shader && _renderer) {
        SVRShaderPtr t_rshader = _renderer->createResShader() ;
        t_rshader->m_logic_obj = m_shader;
        m_shader->bindRes(t_rshader);
        //
        t_rshader->create(_renderer);
        _renderer->addRes(t_rshader);
        SV_LOG_ERROR("sve create shader end!\n");
    }
}

//
SVRCmdCreateTex::SVRCmdCreateTex(SVTexturePtr _texture)
:m_texture(_texture){
    
}

SVRCmdCreateTex::~SVRCmdCreateTex(){
    m_texture = nullptr;
}

void SVRCmdCreateTex::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if(m_texture && _renderer) {
        SVRTexPtr t_rtex = _renderer->createResTexture() ;
        t_rtex->m_logic_obj = m_texture;
        m_texture->bindRes(t_rtex);
        //
        t_rtex->create(_renderer);
        _renderer->addRes(t_rtex);
        SV_LOG_ERROR("sve create tex end!\n");
    }
}

//
SVRCmdCreateFbo::SVRCmdCreateFbo(SVRTargetPtr _target)
:m_rtarget(_target){
    
}

SVRCmdCreateFbo::~SVRCmdCreateFbo(){
    m_rtarget = nullptr;
}

void SVRCmdCreateFbo::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if(m_rtarget && _renderer) {
        SVRFboPtr t_rfbo = _renderer->createResFbo() ;
        t_rfbo->m_logic_obj = m_rtarget;
        m_rtarget->bindRes(t_rfbo);
        //
        t_rfbo->create(_renderer);
        _renderer->addRes(t_rfbo);
        SV_LOG_ERROR("sve create fbo end!\n");
    }
}


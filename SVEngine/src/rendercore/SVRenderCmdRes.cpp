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
        m_rendermesh->bindRes(t_rbuffer->m_pool_id);
        t_rbuffer->create(_renderer,
                          m_rendermesh->getIndexDsp(),
                          m_rendermesh->getStreamDsp(),
                          m_rendermesh->getInstanceDsp(),
                          m_rendermesh->getRMeshDsp());
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
        m_shader->bindRes(t_rshader->m_pool_id);
        t_rshader->create( _renderer,m_shader->getShaderDsp() );
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
        m_texture->bindRes(t_rtex->m_pool_id);
        t_rtex->create( _renderer,m_texture->getTextureDsp() );
    }
}

//
SVRCmdCreateTarget::SVRCmdCreateTarget(SVRTargetPtr _target)
:m_rtarget(_target){
    
}

SVRCmdCreateTarget::~SVRCmdCreateTarget(){
    m_rtarget = nullptr;
}

void SVRCmdCreateTarget::render(SVRendererPtr _renderer,SVRTargetPtr _target) {
    if(m_rtarget && _renderer) {
        SVRFboPtr t_rfbo = _renderer->createResFbo() ;
        if(t_rfbo) {
            m_rtarget->bindRes(t_rfbo->m_pool_id);
            t_rfbo->create(_renderer,m_rtarget->getTargetDsp());
        }
    }
}


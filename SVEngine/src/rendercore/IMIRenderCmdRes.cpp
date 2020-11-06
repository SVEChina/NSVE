//
// IMIRenderCmdRes.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIRenderCmdRes.h"
#include "IMIRenderMesh.h"
#include "IMIRenderer.h"
#include "IMIRMeshRes.h"
#include "IMIRShader.h"
#include "IMIRTex.h"
#include "IMIRTarget.h"
#include "IMIRFbo.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMIShader.h"

using namespace imi;

IMIRCmdCreateMesh::IMIRCmdCreateMesh(IMIRenderMeshPtr _mesh)
:m_rendermesh(_mesh){
}

IMIRCmdCreateMesh::~IMIRCmdCreateMesh() {
    m_rendermesh = nullptr;
}

bool IMIRCmdCreateMesh::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if(m_rendermesh && _renderer) {
        IMIRMeshResPtr t_rbuffer = _renderer->createResBuf() ;
        m_rendermesh->bindRes(t_rbuffer->m_pool_id);
        t_rbuffer->load(_renderer,
                        m_rendermesh->getIndexDsp(),
                        m_rendermesh->getStreamDsp(),
                        m_rendermesh->getInstanceDsp(),
                        m_rendermesh->getRMeshDsp());
    }
    return true;
}

//
IMIRCmdCreateShader::IMIRCmdCreateShader(IMIShaderPtr _shader)
:m_shader(_shader){

}

IMIRCmdCreateShader::~IMIRCmdCreateShader() {
    m_shader = nullptr;
}

bool IMIRCmdCreateShader::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if(m_shader && _renderer) {
        IMIRShaderPtr t_rshader = _renderer->createResShader() ;
        m_shader->bindRes(t_rshader->m_pool_id);
        t_rshader->load( _renderer,m_shader->getShaderDsp() );
    }
    return true;
}

//
IMIRCmdCreateTex::IMIRCmdCreateTex(IMITexturePtr _texture)
:m_texture(_texture){
    
}

IMIRCmdCreateTex::~IMIRCmdCreateTex(){
    m_texture = nullptr;
}

bool IMIRCmdCreateTex::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if(m_texture && _renderer) {
        IMIRTexPtr t_rtex = _renderer->createResTexture() ;
        m_texture->bindRes(t_rtex->m_pool_id);
        t_rtex->load( _renderer,m_texture->getTextureDsp() );
    }
    return true;
}

//
IMIRCmdCreateTarget::IMIRCmdCreateTarget(IMIRTargetPtr _target)
:m_rtarget(_target){
    
}

IMIRCmdCreateTarget::~IMIRCmdCreateTarget(){
    m_rtarget = nullptr;
}

bool IMIRCmdCreateTarget::render(IMIRendererPtr _renderer,IMIRTargetPtr _target) {
    if(m_rtarget && _renderer) {
        IMIRFboPtr t_rfbo = _renderer->createResFbo() ;
        if(t_rfbo) {
            m_rtarget->bindRes(t_rfbo->m_pool_id);
            t_rfbo->load(_renderer,m_rtarget->getTargetDsp());
        }
    }
    return true;
}


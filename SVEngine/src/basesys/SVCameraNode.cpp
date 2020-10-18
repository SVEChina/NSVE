//
// SVCameraNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "../basesys/SVCameraNode.h"
#include "../basesys/SVConfig.h"
#include "../work/SVTdCore.h"

using namespace sv;

//
SVCameraNode::SVCameraNode(SVInstPtr _app)
: SVEventProc(_app) {
    m_active = false;
    m_dirty = true;
    m_is_ortho = false;
    m_res_lock = MakeSharedPtr<SVLockSpin>();
    //
    m_mat_v.setIdentity();
    m_mat_p.setIdentity();
    m_mat_vp.setIdentity();
    //
    m_znear = 1.0f;
    m_zfar = 1000.0f;
    m_width = 720.0f;
    m_height = 1280.0f;
    m_fovy = 60.0f;
    //
    m_pos.set(0.0f,0.0f,500.0f);
    m_up.set(0.0f, 1.0f, 0.0f);
    m_target.set(0.0f,0.0f,0.0f);    //m_target 就是target
    m_distance = 100.0f;
}

SVCameraNode::~SVCameraNode() {
    m_res_lock = nullptr;
}

void SVCameraNode::init() {
    if(m_is_ortho) {
        setOrtho();
    }else{
        setProject();
    }
}

void SVCameraNode::destroy() {
}

//
void SVCameraNode::update(f32 _dt) {
    if(!m_active){
        return ;
    }
    //移除关联fbo
    m_res_lock->lock();
    m_dirty = true;
    if (m_dirty) {
        m_dirty = false;
        //更新相机矩阵
        m_mat_v = lookAt(m_pos,m_target,m_up);
        if(mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS) {
            m_mat_v = transpose(m_mat_v);
            m_mat_vp = m_mat_v*m_mat_p;
        }else {
            m_mat_vp = m_mat_p*m_mat_v;
        }
    }
    m_res_lock->unlock();
}

void SVCameraNode::updateForce() {
    m_res_lock->lock();
    //更新相机矩阵
    m_mat_v = lookAt(m_pos,m_target,m_up);
    if(mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS) {
        m_mat_v = transpose(m_mat_v);
    }
    _updateProj();
    m_mat_vp =m_mat_p*m_mat_v;
    m_res_lock->unlock();
}

void SVCameraNode::_updateProj() {
    if(m_is_ortho) {
        m_mat_p = ortho(-m_width*0.5f,m_width*0.5f,
                        -m_height*0.5f,m_height*0.5f,
                        m_znear,m_zfar);
        if(mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS) {
            m_mat_p = hardwareProjectionMetal(m_mat_p);
            m_mat_p = transpose(m_mat_p);
        }
    }else{
        f32 t_aspect = m_width/m_height;
        m_mat_p = perspective(m_fovy,t_aspect,m_znear,m_zfar);
        if(mApp->m_rcore == E_R_METAL_OSX || mApp->m_rcore == E_R_METAL_IOS) {
            m_mat_p = hardwareProjectionMetal(m_mat_p);
            m_mat_p = transpose(m_mat_p);
        }
    }
}

void SVCameraNode::setProject() {
    m_res_lock->lock();
    m_is_ortho = false;
    _updateProj();
    m_res_lock->unlock();
}

void SVCameraNode::setOrtho() {
    m_res_lock->lock();
    m_is_ortho = true;
    _updateProj();
    m_res_lock->unlock();
}

void SVCameraNode::resetDefault() {
    m_res_lock->lock();
    m_width = 720.0f;
    m_height = 1280.0f;
    _updateProj();
    m_res_lock->unlock();
}

//设置宽高
void SVCameraNode::setSize(f32 _w, f32 _h) {
    m_res_lock->lock();
    m_width = _w;
    m_height = _h;
    _updateProj();
    m_dirty = true;
    m_res_lock->unlock();
}

//设置远进裁
void SVCameraNode::setZ(f32 _near, f32 _far) {
    m_res_lock->lock();
    m_znear = _near;
    m_zfar = _far;
    _updateProj();
    m_dirty = true;
    m_res_lock->unlock();
}

FVec3 SVCameraNode::getPosition() {
    return m_pos;
}

FMat4 SVCameraNode::projectMat(){
    return m_mat_p;
}

FMat4 SVCameraNode::viewMat(){
    return m_mat_v;
}

FMat4 SVCameraNode::vpMat(){
    return m_mat_vp;
}

//
// IMICameraNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIConfig.h"
#include "../work/IMITdCore.h"

using namespace imi;

//
IMICameraNode::IMICameraNode(IMIInstPtr _app)
: IMIEventProc(_app) {
    m_active = false;
    m_dirty = true;
    m_is_ortho = false;
    m_res_lock = MakeSharedPtr<IMILockSpin>();
    //
    m_mat_v.setIdentity();
    m_mat_p.setIdentity();
    m_mat_vp.setIdentity();
    //
    m_znear = 10.0f;
    m_zfar = 2000.0f;
    m_width = 720.0f;
    m_height = 1280.0f;
    m_fovy = 60.0f;
    //
    m_pos.set(0.0f,500.0f,500.0f);
    m_up.set(0.0f, 1.0f, 0.0f);
    m_target.set(0.0f,0.0f,0.0f);    //m_target 就是target
    m_distance = 100.0f;
}

IMICameraNode::~IMICameraNode() {
    m_res_lock = nullptr;
}

void IMICameraNode::init() {
    if(m_is_ortho) {
        setOrtho();
    }else{
        setProject();
    }
}

void IMICameraNode::destroy() {
}

//
void IMICameraNode::update(f32 _dt) {
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

void IMICameraNode::updateForce() {
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

void IMICameraNode::_updateProj() {
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

void IMICameraNode::setProject() {
    m_res_lock->lock();
    m_is_ortho = false;
    _updateProj();
    m_res_lock->unlock();
}

void IMICameraNode::setOrtho() {
    m_res_lock->lock();
    m_is_ortho = true;
    _updateProj();
    m_res_lock->unlock();
}

void IMICameraNode::resetDefault() {
    m_res_lock->lock();
    m_width = 720.0f;
    m_height = 1280.0f;
    _updateProj();
    m_res_lock->unlock();
}

//设置宽高
void IMICameraNode::setSize(f32 _w, f32 _h) {
    m_res_lock->lock();
    m_width = _w;
    m_height = _h;
    _updateProj();
    m_dirty = true;
    m_res_lock->unlock();
}

//设置远进裁
void IMICameraNode::setZ(f32 _near, f32 _far) {
    m_res_lock->lock();
    m_znear = _near;
    m_zfar = _far;
    _updateProj();
    m_dirty = true;
    m_res_lock->unlock();
}

FVec3 IMICameraNode::getPosition() {
    return m_pos;
}

FMat4 IMICameraNode::projectMat(){
    return m_mat_p;
}

FMat4 IMICameraNode::viewMat(){
    return m_mat_v;
}

FMat4 IMICameraNode::vpMat(){
    return m_mat_vp;
}

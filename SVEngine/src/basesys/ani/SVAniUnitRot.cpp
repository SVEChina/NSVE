//
// SVAniUnitRot.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVAniUnitRot.h"
#include "../../node/SVNode.h"

using namespace sv;

//
SVAniUnitRot::SVAniUnitRot(SVInstPtr _app)
:SVAniUnit(_app) {
    m_src_rot_x = 0.0f;
    m_src_rot_y = 0.0f;
    m_src_rot_z = 0.0f;
    //
    m_dst_rot_x = 0.0f;
    m_dst_rot_y = 0.0f;
    m_dst_rot_z = 0.0f;
    //
    m_rot_y_sp = 10.0f;
}

SVAniUnitRot::~SVAniUnitRot() {
}

void SVAniUnitRot::init() {
    
}

void SVAniUnitRot::destroy() {
    
}

void SVAniUnitRot::bind(SVNodePtr _node) {
    if(_node) {
        FVec3 t_rot = _node->getRotation();
        m_src_rot_x = t_rot.x;
        m_src_rot_y = t_rot.y;
        m_src_rot_z = t_rot.z;
        m_dst_rot_x = m_src_rot_x;
        m_dst_rot_y = m_src_rot_y;
        m_dst_rot_z = m_src_rot_z;
    }
}

void SVAniUnitRot::update(f32 _dt,SVNodePtr _node) {
    if(_node) {
        //
        m_dst_rot_y = m_dst_rot_y + _dt*m_rot_y_sp;
        //
        s32 t_num = s32(m_dst_rot_y/360.0f);
        m_dst_rot_y -= 360.0f*t_num;
        //
        _node->setRotation(m_dst_rot_x,m_dst_rot_y,m_dst_rot_z);
    }
}

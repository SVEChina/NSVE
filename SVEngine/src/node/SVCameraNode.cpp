//
// SVCameraNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVCameraNode.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVFboObject.h"
#include "../act/SVCameraCtrl.h"

using namespace sv;

//
SVCameraNode::SVCameraNode(SVInstPtr _app)
: SVEventProc(_app) {
    m_dirty = true;
    m_is_ortho = false;
    m_resLock = MakeSharedPtr<SVLock>();
    m_znear = 1.0f;
    m_zfar = 100.0f;
    m_width = 720.0f;
    m_height = 1280.0f;
    m_fovy = 60.0f;
}

SVCameraNode::~SVCameraNode() {
    
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

void SVCameraNode::setProject() {
    f32 t_aspect = m_width/m_height;
    m_mat_p = perspective(m_fovy,t_aspect,m_znear,m_zfar);
}

void SVCameraNode::setOrtho() {
    m_mat_p = ortho(-m_width*0.5f,m_width*0.5f,-m_height*0.5f,m_height*0.5f,m_znear,m_zfar);
}

//
void SVCameraNode::update(f32 _dt) {
    //移除关联fbo
    if (m_dirty) {
        m_dirty = true;
        //
        if(m_is_ortho) {
            setOrtho();
        }else{
            setProject();
        }
        //
        m_mat_vp =m_mat_p*m_mat_v;
        updateViewProj();  // 更新vp矩阵
    }
}

void SVCameraNode::_updateForce() {
    m_dirty = false;
    if(m_is_ortho) {
        setOrtho();
    }else{
        setProject();
    }
    m_mat_vp =m_mat_p*m_mat_v;
    updateViewProj();
}

void SVCameraNode::resetDefault() {
    m_width = 720.0f;
    m_height = 1280.0f;
    m_dirty = true;
}

void SVCameraNode::resetSize(f32 _w, f32 _h) {
    m_width = _w;
    m_height = _h;
    m_dirty = true;
}

//设置远进裁
void SVCameraNode::setZ(f32 _near, f32 _far) {
    m_znear = _near;
    m_zfar = _far;
    m_dirty = true;
}

FVec3& SVCameraNode::getPosition() {
    return m_pos;
}

f32 *SVCameraNode::getProjectMat() {
    return m_mat_p.get();
}

f32 *SVCameraNode::getCameraMat() {
    return m_mat_v.get();
}

f32 *SVCameraNode::getVPMat() {
    return m_mat_vp.get();
}

FMat4& SVCameraNode::getProjectMatObj(){
    return m_mat_p;
}

FMat4& SVCameraNode::getViewMatObj(){
    return m_mat_v;
}

FMat4& SVCameraNode::getVPMatObj(){
    return m_mat_vp;
}

////获取控制器
//SVCameraCtrlPtr SVCameraNode::getCtrl(){
//    return nullptr;
//}

void SVCameraNode::updateViewProj() {
    m_mat_vp =m_mat_p*m_mat_v;
}


///*proj camera*/
//
//SVCameraProjNode::SVCameraProjNode(SVInstPtr _app)
//:SVCameraNode(_app) {
//    m_fovy = 60.0f;
//}
//
//SVCameraProjNode::~SVCameraProjNode() {
//}
//
//void SVCameraProjNode::setProjectParam(f32 _znear, f32 _zfar, f32 _fovy, f32 _aspect) {
//    m_p_zn = _znear;
//    m_p_zf = _zfar;
//    m_fovy = _fovy;
//    m_aspect = _aspect;
//    updateProjMat();
//}
//
////
//void SVCameraProjNode::resetCamera(f32 w, f32 h) {
//    //设置默认值
//    m_width = w;
//    m_height = h;
//    m_p_zn = 100.0f;
//    m_p_zf = 15000.0f;
//    m_fovy = 60.0f;
//    //
//    f32 t_pos_z = 0.5f * m_height / tan(0.5f*m_fovy * DEGTORAD);
//    m_pos.set(0.0f, 0.0,t_pos_z);
//    m_targetEx.set(0.0f, 0.0f, 0.0f);
//    m_direction = m_targetEx - m_pos;
//    m_direction.normalize();
//    m_upEx.set(0.0f,1.0f,0.0f);
//    m_upEx.normalize();
////    //计算角度
////    m_angle_yaw = acos(m_direction.x)*RAD2DEG;
////    if(m_direction.z<0) {
////        m_angle_yaw = 360.0f - m_angle_yaw;
////    }
////    m_angle_pitch = asin(m_direction.y)*RAD2DEG;
//}
//
//void SVCameraProjNode::updateProjMat(){
//    m_mat_proj = perspective(m_fovy,m_width/m_height, m_p_zn, m_p_zf);
//    updateViewProj();
//}
//
///*ortho camera*/
//SVCameraOrthoNode::SVCameraOrthoNode(SVInstPtr _app)
//:SVCameraNode(_app)  {
//    m_p_zn = 100.0f;
//    m_p_zf = 5000.0f;
//}
//
//SVCameraOrthoNode::~SVCameraOrthoNode() {
//}
//
//void SVCameraOrthoNode::resetCamera(f32 w, f32 h) {
//    //正交
//    m_width = w;
//    m_height = h;
//    m_p_zn = 100.0f;
//    m_p_zf = 15000.0f;
//    f32 t_pos_z = 1000.0f;
//    m_pos.set(0.0f, 0.0,t_pos_z);
//    m_targetEx.set(0.0f, 0.0f, 0.0f);
//    m_direction = m_targetEx - m_pos;
//    m_direction.normalize();
//    m_upEx.set(0.0f,1.0f,0.0f);
//    m_upEx.normalize();
//}
//
////
//void SVCameraOrthoNode::updateProjMat() {
//    m_mat_proj = ortho( -m_width/2 , m_width/2 , -m_height/2 , m_height/2  , m_p_zn  , m_p_zf );   //投影矩阵
//    updateViewProj();
//}
//
////
//SVCameraARNode::SVCameraARNode(SVInstPtr _app)
//:SVCameraNode(_app)  {
//}
//
//SVCameraARNode::~SVCameraARNode() {
//}
////void SVCameraARNode::setPose(f32 _x, f32 _y, f32 _z){
////    FMat4 rotMatX;
////    rotMatX.setIdentity();
////    rotMatX.setRotateX(_x);
////    FMat4 rotMatY;
////    rotMatY.setIdentity();
////    rotMatY.setRotateY(_y);
////    FMat4 rotMatZ;
////    rotMatZ.setIdentity();
////    rotMatZ.setRotateZ(_z);
////    FMat4 rotMat;
////    rotMat.setIdentity();
////    rotMat = rotMatZ * rotMatY * rotMatX;
////    rotMat = inverse(rotMat);
////    resetDefaultCamera();
////    m_mat_view = rotMat*m_mat_view;
////    updateViewProj();
////}
////
////void SVCameraARNode::syncViewMatrix(FMat4 &_mat){
////    m_mat_view = _mat;
////    m_mat_vp =m_mat_proj*m_mat_view;
////    //反算其他参数
////    FMat4 t_camRotInver = m_mat_view;
////    t_camRotInver[12] = 0;
////    t_camRotInver[13] = 0;
////    t_camRotInver[14] = 0;
////    t_camRotInver =transpose(t_camRotInver);
////    FMat4 tmpMat = t_camRotInver*m_mat_view;
////    //获取相机世界位置
////    FVec3 t_cameraEye = FVec3(-tmpMat[12], -tmpMat[13], -tmpMat[14]);
////    m_postion.set(t_cameraEye);
////    //获取up
////    m_upEx.set(m_mat_view[0], m_mat_view[4], m_mat_view[8]);
////}
////
////void SVCameraARNode::syncProjectMatrix(FMat4 &_mat){
////    m_mat_proj = _mat;
////    m_mat_vp =m_mat_proj*m_mat_view;
////    //反算裁剪面
////}


//    FMat4 reflect(const FVec4 &plane);
//    FMat4 ortho(f32 left,f32 right,f32 bottom,f32 top,f32 znear,f32 zfar);
//    FMat4 frustum(f32 left,f32 right,f32 bottom,f32 top,f32 znear,f32 zfar);
//    FMat4 perspective(f32 fov,f32 aspect,f32 znear,f32 zfar);
//    FMat4 setTo(const FVec3 &position,const FVec3 &direction,const FVec3 &up);
//    FMat4 lookAt(const FVec3 &position,const FVec3 &direction,const FVec3 &up);
//    FMat4 obliqueProjection(const FMat4 &projection,const FVec4 &plane);
//    FMat4 symmetryProjection(const FMat4 &projection);
//    FMat4 cubeTransform(s32 face);

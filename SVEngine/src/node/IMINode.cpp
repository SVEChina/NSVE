//
// IMINode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMINode.h"
#include "IMINodeVisit.h"
#include "../app/IMIInst.h"
#include "../app/IMIDispatch.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMICameraNode.h"
#include "../mtl/IMIMtlLib.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMISurface.h"
#include "../event/IMIEventMgr.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMIConfig.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

//
IMINode::IMINode(IMIInstPtr _app)
:IMIEventProc(_app) {
    ntype = "IMINode";
    m_parent = nullptr;
    m_mtl = nullptr;
    m_name = "";
    m_rsType = RST_DEBUG;
    m_canSelect = false;
    m_beSelect = false;
    m_canProcEvent = false;
    m_visible = true;
    m_dirty = false;
    m_alpha = 1.0f;
    //基础属性
    m_localMat.setIdentity();
    m_absolutMat.setIdentity();
    m_iabsolutMat.setIdentity();
    //包围盒
    m_drawBox = false;
    m_aabbBox.clear();
    m_aabbBox_sw.clear();
    //
    m_surface = MakeSharedPtr<IMISurface>();
}

IMINode::~IMINode() {
    m_surface = nullptr;
}

void IMINode::enter(){
}

void IMINode::exit(){
}

//做子节点的深度遍历(先子节点 在兄弟节点)
void IMINode::deep_update(f32 dt) {
    //排序
    //_sort_child();
    //可见性(属性)判断,优先级最高
    if(m_visible){
        //节点更新
        update(dt);
        //节点剔除(属于渲染优化部分)
        if( !_clip() ) {
            //节点渲染
            render();
        }
    }
}

//深度访问
void IMINode::deep_visit(IMIVisitorBasePtr _visit) {
}

void IMINode::select_visit(IMIVisitorBasePtr _visit) {
}

void IMINode::update(f32 _dt) {
    //计算相对矩阵(local)
    if (m_dirty) {
        m_localMat = m_attri_pos.getMatrix();
        m_dirty = false;
    }
    //计算绝对矩阵(world_matrix)
    if (m_parent) {
        m_absolutMat = m_parent->m_absolutMat*m_localMat;
    } else {
        m_absolutMat = m_localMat;
    }
    //更新包围盒
    m_aabbBox_sw = m_aabbBox;
    m_aabbBox_sw.setTransform(m_absolutMat);
    //
    if(m_mtl) {
        m_mtl->update(_dt);
    }
}

bool IMINode::_clip() {
    return false;
}

void IMINode::render() {
    if( m_drawBox){
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if( t_rs ){
//            IMIMtlGeo3dPtr t_mtl = MakeSharedPtr<IMIMtlGeo3d>(mApp);
//            t_mtl->setColor(0.0f, 1.0f, 0.0f, 1.0f);
//            FMat4 m_mat_unit = FMat4_identity;
//            t_mtl->setModelMatrix( m_mat_unit );
//            IMIRenderObjInst::pushAABBCmd(t_rs,RST_DEBUG_INNER,m_aabbBox_sw,t_mtl,"IMI3DBOX_aabb");
//        }
    }
}

//获取本地空间矩阵
FMat4 IMINode::getLocalMat() {
    return m_localMat;
}

FMat4 IMINode::getAbsoluteMat() {
    return m_absolutMat;
}

FMat4 IMINode::getIAbsoluteMat() {
    return m_iabsolutMat;
}

void IMINode::setPosition(f32 _x, f32 _y, f32 _z) {
    m_attri_pos.m_pos.set(_x, _y, _z);
    m_dirty = true;
}

void IMINode::setRotation(f32 _x, f32 _y, f32 _z) {
    m_attri_pos.m_rot.set(_x, _y, _z);
    m_dirty = true;
}

void IMINode::setScale(f32 _x, f32 _y, f32 _z) {
    m_attri_pos.m_scale.set(_x, _y, _z);
    m_dirty = true;
}

void IMINode::setPosition(FVec3& _pos) {
    m_attri_pos.m_pos = _pos;
    m_dirty = true;
}

void IMINode::setRotation(FVec3& _rot) {
    m_attri_pos.m_rot = _rot;
    m_dirty = true;
}

void IMINode::setQuat(IMIQuat& _quat) {
//    m_rotation.x = _quat.getAngle(FVec3(1.0f,0.0f,0.0f));
//    m_rotation.y = _quat.getAngle(FVec3(0.0f,1.0f,0.0f));
//    m_rotation.z = _quat.getAngle(FVec3(0.0f,0.0f,1.0f));
    m_dirty = true;
}

void IMINode::setScale(FVec3& _scale) {
    m_attri_pos.m_scale = _scale;
    m_dirty = true;
}

FVec3 IMINode::getPosition() {
    return m_attri_pos.m_pos;
}

FVec3 IMINode::getRotation() {
    return m_attri_pos.m_rot;
}

IMIQuat IMINode::getQuat() {
    IMIQuat t_quat(m_attri_pos.m_rot);
    return t_quat;
}

FVec3 IMINode::getScale() {
    return m_attri_pos.m_scale;
}

void IMINode::setbeSelect(bool _select){
    m_beSelect = _select;
}

void IMINode::setcanSelect(bool _select){
    m_canSelect = _select;
}

void IMINode::setRSType(RENDERSTREAMTYPE _rsType) {
    m_rsType = _rsType;
}

RENDERSTREAMTYPE IMINode::getRSType(){
    return m_rsType;
}

void IMINode::setdrawAABB(bool _drawaabb){
    m_drawBox = _drawaabb;
}

bool IMINode::getDrawAABB(){
    return m_drawBox;
}

void IMINode::setAABB(IMIBoundBox& _aabb){
    m_aabbBox = _aabb;
}

IMIBoundBox IMINode::getAABB(){
    return m_aabbBox;
}

IMIBoundBox IMINode::getAABBSW(){
    return m_aabbBox_sw;
}

void IMINode::setAlpha(f32 _alpha){
    m_alpha = _alpha;
}

IMIMtlCorePtr IMINode::setMtl(cptr8 _name) {
    m_mtl = mApp->getMtlLib()->getMtl(_name);
    return m_mtl;
}

//序列化接口
void IMINode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    //_toJsonData(_allocator, locationObj);
    _objValue.AddMember("IMINode", locationObj, _allocator);
}

void IMINode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
}

void IMINode::_toJsonData(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                             RAPIDJSON_NAMESPACE::Value &locationObj){
    locationObj.AddMember("name",  RAPIDJSON_NAMESPACE::StringRef(m_name.c_str()), _allocator);
    locationObj.AddMember("renderstream", (s32)m_rsType, _allocator);
    //
    locationObj.AddMember("canselect", m_canSelect, _allocator);
    locationObj.AddMember("drawaabb", m_drawBox, _allocator);
    locationObj.AddMember("canprocevent", m_canProcEvent, _allocator);
    locationObj.AddMember("visible", m_visible, _allocator);
}

void IMINode::_fromJsonData(RAPIDJSON_NAMESPACE::Value &item){
    if (item.HasMember("name") && item["name"].IsString()) {
        m_name = item["name"].GetString();
    }
//    FVec3 t_pos = FVec3(0.0f, 0.0f, 0.0f);
//    if (item.HasMember("posX") && item["posX"].IsFloat()) {
//        t_pos.x = item["posX"].GetFloat();
//    }
//    if (item.HasMember("posY") && item["posY"].IsFloat()) {
//        t_pos.y = item["posY"].GetFloat();
//    }
//    if (item.HasMember("posZ") && item["posZ"].IsFloat()) {
//        t_pos.z = item["posZ"].GetFloat();
//    }
//    setPosition(t_pos);
//    if (item.HasMember("rotX") && item["rotX"].IsFloat()) {
//        m_rotation.x = item["rotX"].GetFloat();
//    }
//    if (item.HasMember("rotY") && item["rotY"].IsFloat()) {
//        m_rotation.y  = item["rotY"].GetFloat();
//    }
//    if (item.HasMember("rotZ") && item["rotZ"].IsFloat()) {
//        m_rotation.z = item["rotZ"].GetFloat();
//    }
//    FVec3 t_scale = FVec3(1.0f, 1.0f, 1.0f);
//    if (item.HasMember("scaleX") && item["scaleX"].IsFloat()) {
//        t_scale.x = item["scaleX"].GetFloat();
//    }
//    if (item.HasMember("scaleY") && item["scaleY"].IsFloat()) {
//        t_scale.y = item["scaleY"].GetFloat();
//    }
//    if (item.HasMember("scaleZ") && item["scaleZ"].IsFloat()) {
//        t_scale.z = item["scaleZ"].GetFloat();
//    }
//    setScale(t_scale);
    if (item.HasMember("renderstream") && item["renderstream"].IsInt()) {
        m_rsType = (RENDERSTREAMTYPE)item["renderstream"].GetInt();
    }
    //
    if (item.HasMember("canselect") && item["canselect"].IsBool()) {
        m_canSelect = item["canselect"].GetBool();
    }
    if (item.HasMember("drawaabb") && item["drawaabb"].IsBool()) {
        m_drawBox = item["drawaabb"].GetBool();
    }
    if (item.HasMember("canprocevent") && item["canprocevent"].IsBool()) {
        m_canProcEvent = item["canprocevent"].GetBool();
    }
    if (item.HasMember("visible") && item["visible"].IsBool()) {
        m_visible = item["visible"].GetBool();
    }
    m_dirty = true;
}

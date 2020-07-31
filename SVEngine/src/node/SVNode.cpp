//
// SVNode.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVNode.h"
#include "SVNodeVisit.h"
#include "../basesys/SVScene.h"
#include "../basesys/SVCameraNode.h"
#include "../mtl/SVMtlCore.h"
#include "../mtl/SVMtlNocolor.h"
#include "../act/SVActBase.h"
#include "../event/SVEventMgr.h"
#include "../basesys/SVSceneMgr.h"
#include "../basesys/SVConfig.h"
#include "../rendercore/SVRenderObject.h"
#include "../rendercore/SVRenderMgr.h"

using namespace sv;

//
SVNode::SVNode(SVInstPtr _app)
:SVEventProc(_app) {
    ntype = "SVNode";
    m_name = "";
    m_rsType = RST_DEBUG;
    m_canSelect = false;
    m_beSelect = false;
    m_canProcEvent = false;
    m_adaptDesign = false;
    m_visible = true;
    m_dirty = false;
    m_iZOrder = 0;
    m_bindIndex = -1;
    m_personID = 1;
    m_alpha = 1.0f;
    //基础属性
    m_postion.set(0.0f, 0.0f, 0.0f);
    m_offpos.set(0.0f, 0.0f, 0.0f);
    m_rotation.set(0.0f, 0.0f, 0.0f);
    m_scale.set(1.0f, 1.0f, 1.0f);
    m_bindOffset.set(0.0f, 0.0f, 0.0f);
    m_localMat.setIdentity();
    m_absolutMat.setIdentity();
    m_iabsolutMat.setIdentity();
    //包围盒
    m_drawBox = false;
    m_aabbBox.clear();
    m_aabbBox_sw.clear();
    //
    m_pMtl = nullptr;
}

SVNode::~SVNode() {
    m_pMtl = nullptr;
}

void SVNode::enter(){
}

void SVNode::exit(){
}

//做子节点的深度遍历(先子节点 在兄弟节点)
void SVNode::deep_update(f32 dt) {
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
void SVNode::deep_visit(SVVisitorBasePtr _visit) {
}

void SVNode::select_visit(SVVisitorBasePtr _visit) {
}

void SVNode::update(f32 dt) {
    SV_LOG_INFO("node type %s \n",ntype.c_str());
    //计算相对矩阵(local)
    if (m_dirty) {
        //更新本地矩阵
        m_localMat.setIdentity();
        FMat4 t_mat_scale = FMat4_identity;
        FMat4 t_mat_rotX = FMat4_identity;
        FMat4 t_mat_rotY = FMat4_identity;
        FMat4 t_mat_rotZ = FMat4_identity;
        FMat4 t_mat_trans = FMat4_identity;
        //
        FVec3 t_scale = FVec3(m_scale.x,m_scale.y,m_scale.z);
        FVec3 t_translate = FVec3(m_postion.x + m_offpos.x,m_postion.y + m_offpos.y, m_postion.z + m_offpos.z);
        //适配设计分辨率
        if (m_adaptDesign) {
            f32 t_adaptScale = mApp->getConfig()->getDesignAdaptScale();
            t_scale *= t_adaptScale;
            t_translate *= t_adaptScale;
        }
        t_mat_scale.setScale(t_scale);
        t_mat_rotX.setRotateX(m_rotation.x);
        t_mat_rotY.setRotateY(m_rotation.y);
        t_mat_rotZ.setRotateZ(m_rotation.z);
        t_mat_trans.setTranslate(t_translate);
        m_localMat = t_mat_trans*t_mat_rotZ*t_mat_rotY*t_mat_rotX*t_mat_scale;
        m_dirty = false;
    }
    //计算绝对矩阵(world_matrix)
//    if (m_parent) {
//        m_absolutMat = m_parent->m_absolutMat*m_localMat;
//    } else {
//        m_absolutMat = m_localMat;
//    }
    //更新包围盒
    m_aabbBox_sw = m_aabbBox;
    m_aabbBox_sw.setTransform(m_absolutMat);
}

bool SVNode::_clip() {
    return false;
}

void SVNode::render() {
    if( m_drawBox){
//        SVRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        if( t_rs ){
//            SVMtlGeo3dPtr t_mtl = MakeSharedPtr<SVMtlGeo3d>(mApp);
//            t_mtl->setColor(0.0f, 1.0f, 0.0f, 1.0f);
//            FMat4 m_mat_unit = FMat4_identity;
//            t_mtl->setModelMatrix( m_mat_unit );
//            SVRenderObjInst::pushAABBCmd(t_rs,RST_DEBUG_INNER,m_aabbBox_sw,t_mtl,"SV3DBOX_aabb");
//        }
    }
}

//获取本地空间矩阵
FMat4& SVNode::getLocalMat() {
    return m_localMat;
}

FMat4& SVNode::getAbsoluteMat() {
    return m_absolutMat;
}

FMat4& SVNode::getIAbsoluteMat() {
    return m_iabsolutMat;
}

void SVNode::setPosition(f32 _x, f32 _y, f32 _z) {
    m_postion.set(_x, _y, _z);
    m_dirty = true;
}

void SVNode::setOffset(f32 _x, f32 _y, f32 _z){
    m_offpos.set(_x, _y, _z);
    m_dirty = true;
}

void SVNode::setRotation(f32 _x, f32 _y, f32 _z) {
    m_rotation.set(_x, _y, _z);
    m_dirty = true;
}

void SVNode::setScale(f32 _x, f32 _y, f32 _z) {
    m_scale.set(_x, _y, _z);
    m_dirty = true;
}

void SVNode::setPosition(FVec3& _pos) {
    m_postion = _pos;
    m_dirty = true;
}

void SVNode::setOffset(FVec3& _pos) {
    m_offpos = _pos;
    m_dirty = true;
}

void SVNode::setRotation(FVec3& _rot) {
    m_rotation = _rot;
    m_dirty = true;
}

void SVNode::setQuat(SVQuat& _quat) {
    m_rotation.x = _quat.getAngle(FVec3(1.0f,0.0f,0.0f));
    m_rotation.y = _quat.getAngle(FVec3(0.0f,1.0f,0.0f));
    m_rotation.z = _quat.getAngle(FVec3(0.0f,0.0f,1.0f));
    m_dirty = true;
}

void SVNode::setScale(FVec3& _scale) {
    m_scale = _scale;
    m_dirty = true;
}

FVec3& SVNode::getPosition() {
    return m_postion;
}

FVec3& SVNode::getOffset() {
    return m_offpos;
}

void SVNode::setBindOffset(FVec3& _offset){
    m_bindOffset = _offset;
    m_dirty = true;
}

void SVNode::setBindOffset(f32 _offsetX, f32 _offsetY, f32 _offsetZ){
    m_bindOffset.set(_offsetX, _offsetY, _offsetZ);
    m_dirty = true;
}

FVec3& SVNode::getBindOffset(){
    return m_bindOffset;
}

FVec3& SVNode::getRotation() {
    return m_rotation;
}

SVQuat SVNode::getQuat() {
    SVQuat t_quat(m_rotation.x,m_rotation.y,m_rotation.z);
    return t_quat;
}

FVec3& SVNode::getScale() {
    return m_scale;
}

void SVNode::setAutoAdaptDesign(bool _adapt){
    m_adaptDesign = _adapt;
    m_dirty = true;
}

void SVNode::setbeSelect(bool _select){
    m_beSelect = _select;
}

void SVNode::setcanSelect(bool _select){
    m_canSelect = _select;
}

void SVNode::setBindIndex(s32 _index){
    m_bindIndex = _index;
}

s32  SVNode::getBindIndex(){
    return m_bindIndex;
}

void SVNode::setRSType(RENDERSTREAMTYPE _rsType) {
    m_rsType = _rsType;
}

RENDERSTREAMTYPE SVNode::getRSType(){
    return m_rsType;
}

void SVNode::setdrawAABB(bool _drawaabb){
    m_drawBox = _drawaabb;
}

bool SVNode::getDrawAABB(){
    return m_drawBox;
}

void SVNode::setAABB(SVBoundBox& _aabb){
    m_aabbBox = _aabb;
}

SVBoundBox& SVNode::getAABB(){
    return m_aabbBox;
}

SVBoundBox& SVNode::getAABBSW(){
    return m_aabbBox_sw;
}

void SVNode::setZOrder(s32 _zorder){
    m_iZOrder = _zorder;
}

void SVNode::setAlpha(f32 _alpha){
    m_alpha = _alpha;
}

void SVNode::setLocalMatrix(FMat4 &_mat){
    m_localMat = _mat;
}

//序列化接口
void SVNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                    RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    //_toJsonData(_allocator, locationObj);
    _objValue.AddMember("SVNode", locationObj, _allocator);
}

void SVNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
}

void SVNode::_toJsonData(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                             RAPIDJSON_NAMESPACE::Value &locationObj){
    locationObj.AddMember("name",  RAPIDJSON_NAMESPACE::StringRef(m_name.c_str()), _allocator);
    locationObj.AddMember("posX", m_postion.x, _allocator);
    locationObj.AddMember("posY", m_postion.y, _allocator);
    locationObj.AddMember("posZ", m_postion.z, _allocator);
    locationObj.AddMember("rotX", m_rotation.x, _allocator);
    locationObj.AddMember("rotY", m_rotation.y, _allocator);
    locationObj.AddMember("rotZ", m_rotation.z, _allocator);
    locationObj.AddMember("scaleX", m_scale.x, _allocator);
    locationObj.AddMember("scaleY", m_scale.y, _allocator);
    locationObj.AddMember("scaleZ", m_scale.z, _allocator);
    locationObj.AddMember("offsetX", m_offpos.x, _allocator);
    locationObj.AddMember("offsetY", m_offpos.y, _allocator);
    //
    locationObj.AddMember("zorder", m_iZOrder, _allocator);
    locationObj.AddMember("renderstream", (s32)m_rsType, _allocator);
    locationObj.AddMember("bind", m_bindIndex, _allocator);
    locationObj.AddMember("person", m_personID, _allocator);
    locationObj.AddMember("bindOffsetX", m_bindOffset.x, _allocator);
    locationObj.AddMember("bindOffsetY", m_bindOffset.y, _allocator);
    locationObj.AddMember("bindOffsetZ", m_bindOffset.z, _allocator);
    //
    locationObj.AddMember("canselect", m_canSelect, _allocator);
    locationObj.AddMember("drawaabb", m_drawBox, _allocator);
    locationObj.AddMember("canprocevent", m_canProcEvent, _allocator);
    locationObj.AddMember("autoadaptdesign", m_adaptDesign, _allocator);
    locationObj.AddMember("visible", m_visible, _allocator);
}

void SVNode::_fromJsonData(RAPIDJSON_NAMESPACE::Value &item){
    if (item.HasMember("name") && item["name"].IsString()) {
        m_name = item["name"].GetString();
    }
    FVec3 t_pos = FVec3(0.0f, 0.0f, 0.0f);
    if (item.HasMember("posX") && item["posX"].IsFloat()) {
        t_pos.x = item["posX"].GetFloat();
    }
    if (item.HasMember("posY") && item["posY"].IsFloat()) {
        t_pos.y = item["posY"].GetFloat();
    }
    if (item.HasMember("posZ") && item["posZ"].IsFloat()) {
        t_pos.z = item["posZ"].GetFloat();
    }
    setPosition(t_pos);
    if (item.HasMember("rotX") && item["rotX"].IsFloat()) {
        m_rotation.x = item["rotX"].GetFloat();
    }
    if (item.HasMember("rotY") && item["rotY"].IsFloat()) {
        m_rotation.y  = item["rotY"].GetFloat();
    }
    if (item.HasMember("rotZ") && item["rotZ"].IsFloat()) {
        m_rotation.z = item["rotZ"].GetFloat();
    }
    FVec3 t_scale = FVec3(1.0f, 1.0f, 1.0f);
    if (item.HasMember("scaleX") && item["scaleX"].IsFloat()) {
        t_scale.x = item["scaleX"].GetFloat();
    }
    if (item.HasMember("scaleY") && item["scaleY"].IsFloat()) {
        t_scale.y = item["scaleY"].GetFloat();
    }
    if (item.HasMember("scaleZ") && item["scaleZ"].IsFloat()) {
        t_scale.z = item["scaleZ"].GetFloat();
    }
    setScale(t_scale);
    if (item.HasMember("offsetX") && item["offsetX"].IsFloat()) {
        m_offpos.x = item["offsetX"].GetFloat();
    }
    if (item.HasMember("offsetY") && item["offsetY"].IsFloat()) {
        m_offpos.y = item["offsetY"].GetFloat();
    }
    if (item.HasMember("offsetZ") && item["offsetZ"].IsFloat()) {
        m_offpos.z = item["offsetZ"].GetFloat();
    }
    //
    if (item.HasMember("zorder") && item["zorder"].IsInt()) {
        m_iZOrder = item["zorder"].GetInt();
    }
    if (item.HasMember("renderstream") && item["renderstream"].IsInt()) {
        m_rsType = (RENDERSTREAMTYPE)item["renderstream"].GetInt();
    }
    if (item.HasMember("bind") && item["bind"].IsInt()) {
        m_bindIndex  = item["bind"].GetInt();
    }
    if (item.HasMember("person") && item["person"].IsInt()) {
        m_personID  = item["person"].GetInt();
    }
    FVec3 t_bindOffset = FVec3(0.0f, 0.0f, 0.0f);
    if (item.HasMember("bindOffsetX") && item["bindOffsetX"].IsFloat()) {
        t_bindOffset.x  = item["bindOffsetX"].GetFloat();
    }
    if (item.HasMember("bindOffsetY") && item["bindOffsetY"].IsFloat()) {
        t_bindOffset.y  = item["bindOffsetY"].GetFloat();
    }
    if (item.HasMember("bindOffsetZ") && item["bindOffsetZ"].IsFloat()) {
        t_bindOffset.z  = item["bindOffsetZ"].GetFloat();
    }
    setBindOffset(t_bindOffset);
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
    if (item.HasMember("autoadaptdesign") && item["autoadaptdesign"].IsBool()) {
        m_adaptDesign = item["autoadaptdesign"].GetBool();
    }else{
        //特效包里要是没有“m_adaptDesign”这个属性，默认是适配设计分辨率的
        m_adaptDesign = true;
    }
    if (item.HasMember("visible") && item["visible"].IsBool()) {
        m_visible = item["visible"].GetBool();
    }
    m_dirty = true;
}

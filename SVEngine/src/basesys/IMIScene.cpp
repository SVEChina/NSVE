//
// IMIScene.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIScene.h"
#include "IMISceneMgr.h"
#include "IMICameraMgr.h"
#include "IMIConfig.h"

#include "../work/IMITdCore.h"

#include "../node/IMINodeVisit.h"
#include "../node/IMINode.h"
#include "../node/IMICube.h"
#include "../node/IMISpriteNode.h"
#include "../node/IMIFaceTuneNode.h"
#include "../node/IMIFacePointNode.h"

#include "../app/IMIGlobalMgr.h"
#include "../app/IMIGlobalParam.h"

#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIComData.h"

#include "../rendercore/IMIRenderMgr.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderCmd.h"

#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"
#include "../event/IMIOpEvent.h"

#include "../mtl/IMITexMgr.h"
#include "../mtl/IMITexture.h"
#include "../mtl/IMISurface.h"
#include "../mtl/IMIFilterBase.h"

#include "../basesys/IMIAniMgr.h"
#include "../basesys/ani/IMIAniUnitRot.h"

#include "../mtl/IMIFilterLib.h"

using namespace imi;

IMITreeLeaf::IMITreeLeaf(IMIInstPtr _app)
:IMIGBaseEx(_app){
}
       
IMITreeLeaf::~IMITreeLeaf() {
    m_nodePool.clear();
}

bool IMITreeLeaf::addNode(IMINodePtr _node) {
    if(_node) {
        m_nodePool.push_back(_node);
        return true;
    }
    return false;
}

bool IMITreeLeaf::removeNode(IMINodePtr _node) {
    NODEPOOL::iterator it = m_nodePool.begin();
    while( it!= m_nodePool.end() ) {
        if( (*it) == _node ) {
            m_nodePool.erase(it);
            return true;
        }
        it++;
    }
    return false;
}

bool IMITreeLeaf::hasNode(IMINodePtr _node) {
    for(s32 i=0;i<m_nodePool.size();i++) {
        if(m_nodePool[i] == _node) {
            return true;
        }
    }
    return false;
}

void IMITreeLeaf::clear() {
    m_nodePool.clear();
}

void IMITreeLeaf::update(f32 _dt) {
    //需要做剔除操作
    for(s32 i=0;i<m_nodePool.size();i++) {
        m_nodePool[i]->deep_update(_dt);
    }
}

void IMITreeLeaf::visit(IMIVisitorBasePtr _visitor) {
    //需要做剔除操作
    for(s32 i=0;i<m_nodePool.size();i++) {
        m_nodePool[i]->deep_visit(_visitor);
    }
}

//
IMISceneTree::IMISceneTree(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_treeLock = MakeSharedPtr<IMILockSpin>();
    resize( FVec3(512,512,512) );
}

IMISceneTree::~IMISceneTree(){
    m_treeLock = nullptr;
}

void IMISceneTree::clear() {
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->clear();
        it++;
    }
    m_leafPool.clear();
}

void IMISceneTree::resize(FVec3 _unit) {
    m_leafSize = _unit;
    FVec3 t_max_world_size = m_leafSize*pow(2,9);
    m_wold_range.set(-t_max_world_size,t_max_world_size);
}

s32 IMISceneTree::_transID(FVec3 _pos) {
    if(m_wold_range.inside(_pos)) {
        //位置转叶子结点ID
        s32 t_x_id = ceil32(_pos.x/m_leafSize.x);  //低10位
        s32 t_y_id = ceil32(_pos.y/m_leafSize.y);  //中10位
        s32 t_z_id = ceil32(_pos.z/m_leafSize.z);  //高10位
        s32 t_leaf_id = t_x_id + (t_y_id<<10) + (t_z_id<<20);
        return t_leaf_id;
    }
    return 0;
}

FVec3 IMISceneTree::getWorldSize() {
    return m_wold_range.getMax() - m_wold_range.getMin();
}

void IMISceneTree::update(f32 _dt){
    //需要做剔除操作
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->update(_dt);
        it++;
    }
}

void IMISceneTree::visit(IMIVisitorBasePtr _visitor){
    //需要做剔除操作
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->visit(_visitor);
        it++;
    }
}

bool IMISceneTree::addNode(IMINodePtr _node, s32 iZOrder){
    if (_node){
        return addNode(_node);
    }
    return false;
}

//增加节点
bool IMISceneTree::addNode(IMINodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it == m_leafPool.end() ) {
        IMITreeLeafPtr t_leaf = MakeSharedPtr<IMITreeLeaf>(mApp);
        t_leaf->addNode(_node);
        m_leafPool.insert(std::make_pair(t_leaf_id, t_leaf));
    }else{
        it->second->addNode(_node);
    }
    return true;
}

//移除节点
bool IMISceneTree::removeNode(IMINodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it != m_leafPool.end() ) {
        it->second->removeNode(_node);
        return true;
    }
    return false;
}

bool IMISceneTree::hasNode(IMINodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it != m_leafPool.end() ) {
        return true;
    }
    return false;
}

//逻辑场景
IMIScene::IMIScene(IMIInstPtr _app,cptr8 _name)
:IMIGBaseEx(_app) {
    m_name = _name;
    m_color.setColorARGB(0x00000000);
    m_pSceneTree = MakeSharedPtr<IMISceneTree>(_app);
}

IMIScene::~IMIScene() {
    m_pSceneTree = nullptr;
}

FVec3 IMIScene::getWorldSize() {
    return m_pSceneTree->getWorldSize();\
}

void IMIScene::create(){
    //scene tree 可以 resize
//    m_worldSize.x = _worldw;
//    m_worldSize.y = _worldh;
//    m_worldSize.z = _depth;
//    if(m_pSceneTree){
////        IMIBoundBox _box;
////        FVec3 t_min,t_max;
////        f32 t_z = 100000.0f;
////        t_min.set(-0.5f*_worldw,-0.5f*_worldh, -0.5f*t_z);
////        t_max.set(0.5f*_worldw,0.5f*_worldh, 0.5f*t_z);
////        _box.set(t_min, t_max);
////        m_pSceneTree->create(_box,_depth);
//    }
//    s32 m_sw = mApp->m_global_param.sv_width;
//    s32 m_sh = mApp->m_global_param.sv_height;
//    IMICameraNodePtr mainCamera = mApp->getCameraMgr()->getMainCamera();
//    if(mainCamera) {
//        mainCamera->resetSize(m_sw,m_sh);
//    }
//    //
//    IMICameraNodePtr uiCamera = mApp->getCameraMgr()->getUICamera();
//    if(uiCamera) {
//        uiCamera->resetSize(m_sw,m_sh);
//    }
}

void IMIScene::destroy(){
}

void IMIScene::addNode(IMINodePtr _node){
    if(_node && m_pSceneTree){
        m_pSceneTree->addNode(_node);
    }
}

void IMIScene::addNode(IMINodePtr _node,s32 _zorder){
    if(_node && m_pSceneTree){
        addNode(_node);
    }
}

void IMIScene::removeNode(IMINodePtr _node){
    if(_node && m_pSceneTree){
        m_pSceneTree->removeNode(_node);
    }
}

void IMIScene::active() {
}

void IMIScene::unactive() {
}

void IMIScene::setSceneColor(f32 _r,f32 _g,f32 _b,f32 _a) {
    m_color.setColor(_r, _g, _b, _a);
}

void IMIScene::update(f32 dt) {
    //遍历场景树
    if(m_pSceneTree){
        m_pSceneTree->update(dt);
    }
}

void IMIScene::visit(IMIVisitorBasePtr _visitor){
    if( m_pSceneTree ){
        m_pSceneTree->visit(_visitor);
    }
}

bool IMIScene::procEvent(IMIEventPtr _event) {
    return true;
}

//序列化场景
void IMIScene::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                  RAPIDJSON_NAMESPACE::Value &_objValue) {
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    locationObj.AddMember("name",  RAPIDJSON_NAMESPACE::StringRef(m_name.c_str()), _allocator);
    u32 t_color = m_color.getColorARGB();
    locationObj.AddMember("color", t_color, _allocator);
//    locationObj.AddMember("worldw", m_worldW, _allocator);
//    locationObj.AddMember("worldh", m_worldH, _allocator);
//    locationObj.AddMember("worldd", m_worldD, _allocator);
    //序列化树 ? 要做这么复杂吗
//    if(m_pSceneTree){
//    }
    _objValue.AddMember("IMIScene", locationObj, _allocator);
}

void IMIScene::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    if (item.HasMember("name") && item["name"].IsString()) {
        m_name = item["name"].GetString();
    }
    if (item.HasMember("color") && item["color"].IsUint()) {
        u32 t_color = item["color"].GetUint();
        m_color.setColorARGB(t_color);
    }
}

#include "../file/IMILoaderGLTFEx.h"
#include "../node/IMISkinNode.h"

void IMIScene::test() {
    IMISkinNodePtr skinNode = IMILoaderGLTFEx::loadFromFile(mApp, "res/taidi/scene.gltf");
    if(skinNode) {
        addNode(skinNode);
    }
//    IMITexturePtr t_tex = mApp->getTexMgr()->getTexture("res/test2.jpeg");
//    IMIFacePointNodePtr t_facept_node = MakeSharedPtr<IMIFacePointNode>(mApp);
//    addNode(t_facept_node);
    
    IMIFaceTuneNodePtr t_tune_node = MakeSharedPtr<IMIFaceTuneNode>(mApp);
    addNode(t_tune_node);
    //
//
//    IMICubePtr t_box_node = MakeSharedPtr<IMICube>(mApp);
//    t_box_node->setRotation(45.0f, 45.0f, 45.0f);
//    t_box_node->setMtl("pbr");
//    IMISurfacePtr t_surface = t_box_node->getSurface();
//    if(t_surface) {
//        //t_surface->setTexture(1, 0, t_tex);
//        FVec3 u_LightDirection = FVec3(0.0f,1.0f,0.0f);
//        t_surface->setParam("u_LightDirection", u_LightDirection);
//        //
//        FVec3 u_LightColor = FVec3(1.0f,1.0f,0.0f);
//        t_surface->setParam("u_LightColor", u_LightColor);
//        //
//        f32 u_NormalScale = 0.1;
//        t_surface->setParam("u_NormalScale", u_NormalScale);
//        //
//        FVec3 u_EmissiveFactor = FVec3(1.0f,1.0f,0.0f);
//        t_surface->setParam("u_EmissiveFactor", u_EmissiveFactor);
//        //
//        f32 u_OcclusionStrength = 0.5;
//        t_surface->setParam("u_OcclusionStrength", u_OcclusionStrength);
//        //
//        FVec2 u_MetallicRoughnessValues = FVec2(0.5f,1.0f);
//        t_surface->setParam("u_MetallicRoughnessValues", u_MetallicRoughnessValues);
//        //
//        FVec4 u_BaseColorFactor = FVec4(0.0f,1.0f,0.0f,1.0f);
//        t_surface->setParam("u_BaseColorFactor", u_BaseColorFactor);
//        //
//        FVec3 u_Camera = FVec3(1.0f,1.0f,0.0f);
//        t_surface->setParam("u_Camera", u_Camera);
//        //
//        FVec4 u_ScaleDiffBaseMR = FVec4(1.0f,1.0f,0.0f,1.0f);
//        t_surface->setParam("u_ScaleDiffBaseMR", u_ScaleDiffBaseMR);
//        //
//        FVec4 u_ScaleFGDSpec = FVec4(1.0f,1.0f,0.0f,1.0f);
//        t_surface->setParam("u_ScaleFGDSpec", u_ScaleFGDSpec);
//        //
//        FVec4 u_ScaleIBLAmbient = FVec4(1.0f,1.0f,0.0f,1.0f);
//        t_surface->setParam("u_ScaleIBLAmbient", u_ScaleIBLAmbient);
//    }
//    addNode(t_box_node);
//    //
//    IMIAniUnitRotPtr t_rot = MakeSharedPtr<IMIAniUnitRot>(mApp);
//    mApp->getAniMgr()->addAni(t_box_node,t_rot);

//    IMICubePtr t_box_node = MakeSharedPtr<IMICube>(mApp);
//    t_box_node->setRotation(45.0f, 45.0f, 45.0f);
//    t_box_node->setMtl("normal3d");
//    IMISurfacePtr t_surface = t_box_node->getSurface();
//    if(t_surface) {
//        t_surface->setTexture(1, 0, t_tex);
//    }
//    addNode(t_box_node);
//    IMIAniUnitRotPtr t_rot = MakeSharedPtr<IMIAniUnitRot>(mApp);
//    mApp->getAniMgr()->addAni(t_box_node,t_rot);

}

//
// SVScene.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVScene.h"
#include "SVSceneMgr.h"
#include "SVCameraMgr.h"
#include "SVConfig.h"
#include "../work/SVTdCore.h"
#include "../node/SVNodeVisit.h"
#include "../node/SVNode.h"
#include "../node/SVCube.h"
#include "../node/SVSpriteNode.h"
#include "../app/SVGlobalMgr.h"
#include "../app/SVGlobalParam.h"

#include "../basesys/SVCameraNode.h"
#include "../basesys/SVComData.h"

#include "../rendercore/SVRenderMgr.h"
#include "../rendercore/SVRenderer.h"
#include "../rendercore/SVRenderCmd.h"

#include "../event/SVEventMgr.h"
#include "../event/SVEvent.h"
#include "../event/SVOpEvent.h"

#include "../mtl/SVTexMgr.h"
#include "../mtl/SVTexture.h"
#include "../mtl/SVSurface.h"
#include "../mtl/SVFilterBase.h"

#include "../basesys/SVAniMgr.h"
#include "../basesys/ani/SVAniUnitRot.h"

#include "../mtl/SVFilterLib.h"

using namespace sv;

SVTreeLeaf::SVTreeLeaf(SVInstPtr _app)
:SVGBaseEx(_app){
}
       
SVTreeLeaf::~SVTreeLeaf() {
    m_nodePool.clear();
}

bool SVTreeLeaf::addNode(SVNodePtr _node) {
    if(_node) {
        m_nodePool.push_back(_node);
        return true;
    }
    return false;
}

bool SVTreeLeaf::removeNode(SVNodePtr _node) {
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

bool SVTreeLeaf::hasNode(SVNodePtr _node) {
    for(s32 i=0;i<m_nodePool.size();i++) {
        if(m_nodePool[i] == _node) {
            return true;
        }
    }
    return false;
}

void SVTreeLeaf::clear() {
    m_nodePool.clear();
}

void SVTreeLeaf::update(f32 _dt) {
    //需要做剔除操作
    for(s32 i=0;i<m_nodePool.size();i++) {
        m_nodePool[i]->deep_update(_dt);
    }
}

void SVTreeLeaf::visit(SVVisitorBasePtr _visitor) {
    //需要做剔除操作
    for(s32 i=0;i<m_nodePool.size();i++) {
        m_nodePool[i]->deep_visit(_visitor);
    }
}

//
SVSceneTree::SVSceneTree(SVInstPtr _app)
:SVGBaseEx(_app){
    m_treeLock = MakeSharedPtr<SVLockSpin>();
    resize( FVec3(512,512,512) );
}

SVSceneTree::~SVSceneTree(){
    m_treeLock = nullptr;
}

void SVSceneTree::clear() {
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->clear();
        it++;
    }
    m_leafPool.clear();
}

void SVSceneTree::resize(FVec3 _unit) {
    m_leafSize = _unit;
    FVec3 t_max_world_size = m_leafSize*pow(2,9);
    m_wold_range.set(-t_max_world_size,t_max_world_size);
}

s32 SVSceneTree::_transID(FVec3 _pos) {
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

FVec3 SVSceneTree::getWorldSize() {
    return m_wold_range.getMax() - m_wold_range.getMin();
}

void SVSceneTree::update(f32 _dt){
    //需要做剔除操作
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->update(_dt);
        it++;
    }
}

void SVSceneTree::visit(SVVisitorBasePtr _visitor){
    //需要做剔除操作
    LEAFPOOL::iterator it = m_leafPool.begin();
    while (it!=m_leafPool.end()) {
        it->second->visit(_visitor);
        it++;
    }
}

bool SVSceneTree::addNode(SVNodePtr _node, s32 iZOrder){
    if (_node){
        return addNode(_node);
    }
    return false;
}

//增加节点
bool SVSceneTree::addNode(SVNodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it == m_leafPool.end() ) {
        SVTreeLeafPtr t_leaf = MakeSharedPtr<SVTreeLeaf>(mApp);
        t_leaf->addNode(_node);
        m_leafPool.insert(std::make_pair(t_leaf_id, t_leaf));
    }else{
        it->second->addNode(_node);
    }
    return true;
}

//移除节点
bool SVSceneTree::removeNode(SVNodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it != m_leafPool.end() ) {
        it->second->removeNode(_node);
        return true;
    }
    return false;
}

bool SVSceneTree::hasNode(SVNodePtr _node) {
    s32 t_leaf_id = _transID(_node->getPosition());
    LEAFPOOL::iterator it = m_leafPool.find(t_leaf_id);
    if(it != m_leafPool.end() ) {
        return true;
    }
    return false;
}

//逻辑场景
SVScene::SVScene(SVInstPtr _app,cptr8 _name)
:SVGBaseEx(_app) {
    m_name = _name;
    m_color.setColorARGB(0x00000000);
    m_pSceneTree = MakeSharedPtr<SVSceneTree>(_app);
}

SVScene::~SVScene() {
    m_pSceneTree = nullptr;
}

FVec3 SVScene::getWorldSize() {
    return m_pSceneTree->getWorldSize();\
}

void SVScene::create(){
    //scene tree 可以 resize
    
//    m_worldSize.x = _worldw;
//    m_worldSize.y = _worldh;
//    m_worldSize.z = _depth;
//    if(m_pSceneTree){
////        SVBoundBox _box;
////        FVec3 t_min,t_max;
////        f32 t_z = 100000.0f;
////        t_min.set(-0.5f*_worldw,-0.5f*_worldh, -0.5f*t_z);
////        t_max.set(0.5f*_worldw,0.5f*_worldh, 0.5f*t_z);
////        _box.set(t_min, t_max);
////        m_pSceneTree->create(_box,_depth);
//    }
//    s32 m_sw = mApp->m_global_param.sv_width;
//    s32 m_sh = mApp->m_global_param.sv_height;
//    SVCameraNodePtr mainCamera = mApp->getCameraMgr()->getMainCamera();
//    if(mainCamera) {
//        mainCamera->resetSize(m_sw,m_sh);
//    }
//    //
//    SVCameraNodePtr uiCamera = mApp->getCameraMgr()->getUICamera();
//    if(uiCamera) {
//        uiCamera->resetSize(m_sw,m_sh);
//    }
}

void SVScene::destroy(){
}

void SVScene::addNode(SVNodePtr _node){
    if(_node && m_pSceneTree){
        m_pSceneTree->addNode(_node);
    }
}

void SVScene::addNode(SVNodePtr _node,s32 _zorder){
    if(_node && m_pSceneTree){
        addNode(_node);
    }
}

void SVScene::removeNode(SVNodePtr _node){
    if(_node && m_pSceneTree){
        m_pSceneTree->removeNode(_node);
    }
}

void SVScene::active() {
}

void SVScene::unactive() {
}

void SVScene::setSceneColor(f32 _r,f32 _g,f32 _b,f32 _a) {
    m_color.setColor(_r, _g, _b, _a);
}

void SVScene::update(f32 dt) {
    //遍历场景树
    if(m_pSceneTree){
        m_pSceneTree->update(dt);
    }
}

void SVScene::visit(SVVisitorBasePtr _visitor){
    if( m_pSceneTree ){
        m_pSceneTree->visit(_visitor);
    }
}

bool SVScene::procEvent(SVEventPtr _event) {
    return true;
}

//序列化场景
void SVScene::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
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
    //
    _objValue.AddMember("SVScene", locationObj, _allocator);
}

void SVScene::fromJSON(RAPIDJSON_NAMESPACE::Value &item) {
    if (item.HasMember("name") && item["name"].IsString()) {
        m_name = item["name"].GetString();
    }
    if (item.HasMember("color") && item["color"].IsUint()) {
        u32 t_color = item["color"].GetUint();
        m_color.setColorARGB(t_color);
    }
}

void SVScene::test() {
    SVTexturePtr t_tex = mApp->getTexMgr()->getTexture("res/test1.png");
    //创建一个测试场景
//    SVSpriteNodePtr t_sp_node = MakeSharedPtr<SVSpriteNode>(mApp);
//    t_sp_node->setMtl("normal2d");
//    t_sp_node->setTexture("res/test1.png");
//    addNode(t_sp_node);
    SVCubePtr t_box_node = MakeSharedPtr<SVCube>(mApp);
    t_box_node->setRotation(45.0f, 45.0f, 45.0f);
    t_box_node->setMtl("normal3d");
    SVSurfacePtr t_surface = t_box_node->getSurface();
    if(t_surface) {
        t_surface->setTexture(1, 0, t_tex);
    }
    addNode(t_box_node);
    //
    SVAniUnitRotPtr t_rot = MakeSharedPtr<SVAniUnitRot>(mApp);
    mApp->getAniMgr()->addAni(t_box_node,t_rot);
//    //
//    SVFilterBasePtr t_filter = SVFilterLib::openFilter(mApp,FILTER_LUT);
//    if(t_filter) {
//        SVSurfacePtr t_surface = t_filter->getSurface();
//        if(t_surface) {
//            SVTexturePtr _tex_img = mApp->getTexMgr()->getTexture("res/filterimg/sunset_20170620.png");
//            t_surface->setTexture(1, 1, _tex_img);
//        }
//    }
    //
    SVFilterLib::openFilter(mApp,FILTER_HDR);
}

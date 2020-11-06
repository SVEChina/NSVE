//
// IMIFrameAniNode.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFrameAniNode.h"
#include "../basesys/IMICameraNode.h"
#include "../basesys/IMIScene.h"
#include "../mtl/IMIMtlCore.h"
#include "../mtl/IMITexMgr.h"
#include "../core/IMIGeoGen.h"
#include "../rendercore/IMIRenderMgr.h"

using namespace imi;

IMIFrameAniNode::IMIFrameAniNode(IMIInstPtr _app)
:IMINode(_app){
    ntype = "IMIFrameAniNode";
    m_rsType = RST_SOLID_3D;
    m_state = tANI_STATE_WAIT;
    m_canSelect = false;
    m_visible = false;
    m_accTime = 0.0f;
    m_totalTime = 90.0f;
    m_frameRate = 15.0f;
    m_framecount = 0;
    m_texprename = "";
    m_pActTex = nullptr;
    m_pMesh = nullptr;
    m_width = 850;
    m_height = 1000;
    setSize(m_width,m_height);
    m_loop = true;
    m_p_cb_obj = nullptr;
    m_frameani_callback = nullptr;
}

IMIFrameAniNode::~IMIFrameAniNode() {
    m_pActTex = nullptr;
    m_pMesh = nullptr;
}

//
void IMIFrameAniNode::setSize(f32 _w,f32 _h) {
    m_width = _w;
    m_height = _h;
    m_pMesh = IMIGeoGen::genRect(mApp, m_width, m_height,m_aabbBox);
}

f32 IMIFrameAniNode::getWidth(){
    return m_width;
}

f32 IMIFrameAniNode::getHeight(){
    return m_height;
}

void IMIFrameAniNode::update(f32 dt) {
    IMINode::update(dt);
//    if (!m_visible) {
//        return;
//    }
//    if (m_state == tANI_STATE_STOP) {
//        return;
//    }
//    //时间更新
//    if (m_state == tANI_STATE_PLAY) {
//        m_accTime += dt;
//    }
//    if(m_accTime>m_totalTime) {
//        _complete();
//        if(m_loop) {
//            m_accTime = 0.0f;
//        }else{
//            m_accTime = m_totalTime;
//            stop();
//        }
//    }
//    //预先加载
//    _preload();
//    //根据时间计算激活纹理
//    m_pActTex = _selectTex(m_accTime);
//    if(!m_pActTex) {
//        m_pActTex = mApp->getTexMgr()->getIMITexture();
//    }
//    //卸载
//    _unload();
}

void IMIFrameAniNode::render() {
    if (m_state == tANI_STATE_STOP) {
        return;
    }
//    if (m_visible && m_pRenderObj ){
//        IMIRenderScenePtr t_rs = mApp->getRenderMgr()->getRenderScene();
//        m_pRenderObj->pushCmd(t_rs, m_rsType, "IMIFrameAniNode");
//    }
    IMINode::render();
}

//播放控制
void IMIFrameAniNode::play() {
    if (m_state != tANI_STATE_PLAY) {
        m_state = tANI_STATE_PLAY;
        m_visible = true;
        if(m_frameani_callback){
            (*m_frameani_callback)(THIS_TO_SHAREPTR(IMIFrameAniNode),m_p_cb_obj,1);
        }
    }
}

void IMIFrameAniNode::pause() {
    if (m_state != tANI_STATE_PAUSE) {
        m_state = tANI_STATE_PAUSE;
    }
}

void IMIFrameAniNode::stop() {
    if (m_state != tANI_STATE_STOP) {
        m_state = tANI_STATE_STOP;
        m_visible = false;
        if(m_frameani_callback){
            (*m_frameani_callback)(THIS_TO_SHAREPTR(IMIFrameAniNode),m_p_cb_obj,3);
        }
    }
}

void IMIFrameAniNode::_complete(){
    if(m_frameani_callback){
        (*m_frameani_callback)(THIS_TO_SHAREPTR(IMIFrameAniNode),m_p_cb_obj,2);
    }
}

IMITexturePtr IMIFrameAniNode::_selectTex(f32 _time) {
    //二分法查目标
    s32 t_ct =m_framePool.size();
    if(t_ct<0)
        return nullptr;
    m_curFrame = s32(_time*m_frameRate);
    if(m_curFrame>=t_ct)
        return nullptr;
     m_framePool[m_curFrame].m_pTex = mApp->getTexMgr()->getTexture( m_framePool[m_curFrame].m_pTexName.c_str(),true);
//    for(s32 i=0;i<2;i++) {
//        s32 t_aim_index = (m_curFrame + i)%t_ct;
//        m_framePool[t_aim_index].m_pTex = mApp->getTexMgr()->getTexture( m_framePool[t_aim_index].m_pTexName.c_str(),true);
//    }
    return m_framePool[m_curFrame].m_pTex;
}

void IMIFrameAniNode::_preload() {
    //预加载
//    s32 m_curFrame; //当前帧
//    s32 m_aimFrame; //目标帧
//    s32 m_preFrame; //预先帧
}

void IMIFrameAniNode::_unload() {
    //卸载当前帧就可以，用一帧，卸一帧
    if(m_curFrame>=0 && m_curFrame<m_framePool.size()) {
        m_framePool[m_curFrame].m_pTex = nullptr;
    }
}

void IMIFrameAniNode::pushFrame(cptr8 _texname) {
    FrameTex t_ftex;
    t_ftex.m_pTexName = _texname;
    t_ftex.m_pTex = nullptr;
    m_framePool.append(t_ftex);
}

void IMIFrameAniNode::clearFrame() {
    for(s32 i=0;i<m_framePool.size();i++) {
        m_framePool[i].m_pTex = nullptr;
    }
    m_framePool.destroy();
}

void IMIFrameAniNode::setCallback(sv_frameani_callback _cb,void* _obj){
    m_frameani_callback = _cb;
    m_p_cb_obj = _obj;
}

void IMIFrameAniNode::setTexPrename(cptr8 _prename){
    m_texprename = _prename;
}

cptr8 IMIFrameAniNode::getTexPrename(){
    return m_texprename.c_str();
}

void IMIFrameAniNode::setTotalTime(f32 _time){
    m_totalTime = _time;
    if (m_framecount > 0 && m_totalTime > 0) {
        m_frameRate = m_framecount/m_totalTime;
    }
}

f32  IMIFrameAniNode::getTotlaTime(){
    return m_totalTime;
}

void IMIFrameAniNode::setFrameCount(s32 _count){
    m_framecount = _count;
    if (m_framecount > 0 && m_totalTime > 0) {
        m_frameRate = m_framecount/m_totalTime;
    }
}

s32  IMIFrameAniNode::getFrameCount(){
    return m_framecount;
}

void IMIFrameAniNode::setLoop(bool _loop){
    m_loop = _loop;
}

bool IMIFrameAniNode::getLoop(){
    return m_loop;
}

//序列化
void IMIFrameAniNode::toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator, RAPIDJSON_NAMESPACE::Value &_objValue){
    RAPIDJSON_NAMESPACE::Value locationObj(RAPIDJSON_NAMESPACE::kObjectType);//创建一个Object类型的元素
    _toJsonData(_allocator, locationObj);
    locationObj.AddMember("width", m_width, _allocator);
    locationObj.AddMember("height", m_height, _allocator);
    locationObj.AddMember("loop", m_loop, _allocator);
    locationObj.AddMember("time", m_totalTime, _allocator);
    locationObj.AddMember("count", m_framecount, _allocator);
    locationObj.AddMember("prename", RAPIDJSON_NAMESPACE::StringRef(m_texprename.c_str()), _allocator);
    _objValue.AddMember("IMIFrameAniNode", locationObj, _allocator);
}

void IMIFrameAniNode::fromJSON(RAPIDJSON_NAMESPACE::Value &item){
    _fromJsonData(item);
    f32 t_width = 100.0f;
    if (item.HasMember("width") && item["width"].IsFloat()) {
        t_width = item["width"].GetFloat();
    }
    f32 t_height = 100.0f;
    if (item.HasMember("height") && item["height"].IsFloat()) {
        t_height = item["height"].GetFloat();
    }
    setSize(t_width, t_height);
    //
    bool t_loop = false;
    if (item.HasMember("loop") && item["loop"].IsBool()) {
        t_loop = item["loop"].GetBool();
    }
    setLoop(t_loop);
    //
    f32 t_time = 90.0f;
    if (item.HasMember("time") && item["time"].IsFloat()) {
         t_time = item["time"].GetFloat();
    }
    setTotalTime(t_time);
    //
    s32 t_count = 0;
    if (item.HasMember("count") && item["count"].IsInt()) {
        t_count = item["count"].GetInt();
    }
    setFrameCount(t_count);
    //
    IMIString t_prename = "";
    if (item.HasMember("prename") && item["prename"].IsString()) {
        t_prename = item["prename"].GetString();
    }
    setTexPrename(t_prename.c_str());
    //
    for (s32 i = 0; i<m_framecount; i++) {
        IMIString t_name = IMIString::format("%s%d.png",m_texprename.c_str(), i);
        t_name = m_rootPath + t_name;
        pushFrame(t_name.c_str());
    }
    m_dirty = true;
}

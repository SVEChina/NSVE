//
// IMIEvent.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIEvent.h"
#include "../rendercore/IMIRenderer.h"

using namespace imi;

IMIEvent::IMIEvent() {
    eventType = EVN_T_NONE;
    eventName = "";
}

IMIEvent::IMIEvent(IMI_EVENT_TYPE _type) {
    eventType = _type;
    eventName = "";
}

IMIEvent::~IMIEvent() {
}

bool IMIEvent::isEqual(IMIEventPtr _event) {
    return strcmp(eventName.c_str(), _event->eventName.c_str()) == 0;
}

/*
 渲染器初始化消息
 */
IMIvtRenderInit::IMIvtRenderInit(IMIRendererPtr _renderer)
:m_renderer(_renderer){
    eventType = EVN_T_SYS_INIT_RENDERER;
}

IMIvtRenderInit::~IMIvtRenderInit() {
    m_renderer = nullptr;
}

/*
 垃圾回收消息
 */
IMIvtRecycle::IMIvtRecycle(){
    m_obj = nullptr;
}

/*
 人物消息
 */
IMIPersonEvent::IMIPersonEvent() {
    personID = -1;
}

IMIPersonEvent::~IMIPersonEvent() {

}

bool IMIPersonEvent::isEqual(IMIEventPtr _event) {
    bool t_flag = IMIEvent::isEqual(_event);
    IMIPersonEventPtr t_person_event = DYN_TO_SHAREPTR(IMIPersonEvent, _event);
    if(t_person_event->personID!=personID){
        t_flag = false;
    }
    return t_flag;
}

//
IMIAnimateEvent::IMIAnimateEvent() {
    eventType = EVN_T_ANIMATE;
    resid = 0;
    m_AnimateName = "";
}

bool IMIAnimateEvent::isEqual(IMIEventPtr _event) {
    bool t_flag = IMIPersonEvent::isEqual(_event);
    if (t_flag) {
        IMIAnimateEventPtr tempEvent = DYN_TO_SHAREPTR(IMIAnimateEvent,_event);
        if (!tempEvent || m_AnimateName != tempEvent->m_AnimateName)
            t_flag = false;
    }
    return t_flag;
}

//解析事件
IMIParseEvent::IMIParseEvent() {
    eventType = EVN_T_PARSE;
    isloadEffect = false;
    resid = 0;
    screenName = "";
}

IMIParseEvent::~IMIParseEvent() {
}

//
IMIFaceShapeEvent::IMIFaceShapeEvent(){
    m_faceSmooth = 0;
    m_eyeSmooth = 0;
}

IMIFaceShapeEvent::~IMIFaceShapeEvent(){
    m_faceSmooth = 0;
    m_eyeSmooth = 0;
}

//拾取焦点信息
IMIPickGetEvent::IMIPickGetEvent(IMINodePtr _node){
    eventType = EVN_T_PICK_GET_NODE;
    m_pNode = _node;
}

IMIPickGetEvent::~IMIPickGetEvent(){
    m_pNode = nullptr;
}

//拾取焦点信息
IMIPickGetUIEvent::IMIPickGetUIEvent(IMINodePtr _node){
    eventType = EVN_T_PICK_GET_UI;
    m_pNode = _node;
}

IMIPickGetUIEvent::~IMIPickGetUIEvent(){
    m_pNode = nullptr;
}

IMIPickGetNothingEvent::IMIPickGetNothingEvent(){
    eventType = EVN_T_PICK_GET_NOTHING;
}

IMIPickGetNothingEvent::~IMIPickGetNothingEvent(){
    
}

//丢失焦点
IMIPickLoseEvent::IMIPickLoseEvent(IMINodePtr _node){
    m_pNode = _node;
}

IMIPickLoseEvent::~IMIPickLoseEvent(){
    m_pNode = nullptr;
}

//改变信息
IMIPickChangeEvent::IMIPickChangeEvent(IMINodePtr _getnode,IMINodePtr _losenode){
    m_pLastNode = _getnode;
    m_pNewNode = _losenode;
}

IMIPickChangeEvent::~IMIPickChangeEvent(){
    m_pLastNode = nullptr;
    m_pNewNode = nullptr;
}

//
IMIRedPacketEvent::IMIRedPacketEvent(){
    
}

IMIRedPacketEvent::~IMIRedPacketEvent(){
    
}

IMIffectMusicEvent::IMIffectMusicEvent(){
    eventType = EVN_T_EFFECT_MUSIC_LOAD;
    eventName = "IMIffectMusicEvent";
}

IMIffectMusicEvent::~IMIffectMusicEvent(){
    
}
//
IMIEventPersonExpression::IMIEventPersonExpression(){
  ;
}

IMIEventPersonExpression::~IMIEventPersonExpression(){
    
}

//
// IMIffectPackage.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIEffectPackage.h"
#include "../app/IMIGlobalMgr.h"
#include "../core/IMISpine.h"
#include "../core/IMIDeformImageMove.h"
#include "../work/IMITdCore.h"
#include "../base/IMIPreDeclare.h"
#include "../node/IMINode.h"
#include "../node/IMISpineNode.h"
#include "../node/IMISpriteNode.h"
#include "../node/IMIBitFontNode.h"
#include "../node/IMIFrameAniNode.h"
#include "../event/IMIEvent.h"
#include "../basesys/IMISceneMgr.h"
#include "../mtl/IMIParseLUTFilter.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIDeformMgr.h"
#include "../basesys/IMIConfig.h"
#include "../basesys/IMIScene.h"

using namespace imi;


void spinenode_callback(IMISpineNodePtr _node,void* _obj,s32 _status) {
    IMIffectUnit *t_unit = (IMIffectUnit*)(_obj);
    if(_status == 2) {
        t_unit->setEnd(true);
    }else if(_status == 3) {
        t_unit->setEnd(true);
    }
}

void frameani_callback(IMIFrameAniNodePtr _node,void* _obj,s32 _status){
    IMIffectUnit *t_unit = (IMIffectUnit*)(_obj);
    if(_status == 2) {
        t_unit->setEnd(true);
    }else if(_status == 3) {
        t_unit->setEnd(true);
    }
}

IMIffectUnit::IMIffectUnit(IMIInstPtr _app)
:IMIGBaseEx(_app){
    m_end = true;
}

IMIffectUnit::~IMIffectUnit(){
    m_node = nullptr;
}

void IMIffectUnit::init(IMINodePtr _node){
    IMIScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if(_node && t_scene){
        m_node = _node;
        t_scene->addNode(m_node);
//        //需要挂的人身上
//        if (_node->getBindIndex() >= 0 && !m_personAct) {
//            _attachToPeople(_node);
//        }
        IMISpineNodePtr t_spineNode = DYN_TO_SHAREPTR(IMISpineNode, m_node);
        if (t_spineNode) {
            t_spineNode->setSpineCallback(spinenode_callback, this);
            t_spineNode->stop();
            if (t_spineNode->isImmediatelyPlay()) {
                cptr8 t_defAniName = t_spineNode->getCurAniName();
                t_spineNode->play(t_defAniName);
                setEnd(false);
            }
        }
        //
        IMIFrameAniNodePtr t_frameAni = DYN_TO_SHAREPTR(IMIFrameAniNode, m_node);
        if (t_frameAni) {
            t_frameAni->setCallback(frameani_callback, this);
            t_frameAni->play();
            setEnd(false);
        }
    }
}

void IMIffectUnit::_attachToPeople(IMINodePtr _node){
    
}

void IMIffectUnit::destroy(){
    if (m_node) {
        IMISpineNodePtr t_spineNode = DYN_TO_SHAREPTR(IMISpineNode, m_node);
        if (t_spineNode) {
            t_spineNode->stop();
        }
    }
}

IMINodePtr IMIffectUnit::getNode(){
    return m_node;
}

void IMIffectUnit::setEnd(bool _end){
    m_end = _end;
}

bool IMIffectUnit::isEnd(){
    return m_end;
}

IMIffectPackage::IMIffectPackage(IMIInstPtr _app)
:IMIModuleBase(_app){
    m_lock = MakeSharedPtr<IMILock>();
    m_aniState = EFFECT_ANI_WAIT;
}

IMIffectPackage::~IMIffectPackage(){
    m_lock = nullptr;
}

void IMIffectPackage::init(){
    IMIModuleBase::init();
    startListen();
}

void IMIffectPackage::destroy(){
    m_lock->lock();
    IMIModuleBase::destroy();
    stopListen();
//    for (s32 i = 0; i<m_attachmentPool.size(); i++) {
//        IMIAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        t_attachment->removeFromActionMgr();
//        t_attachment->destroy();
//    }
//    m_attachmentPool.destroy();
    //
//    for (s32 i = 0; i<m_triggerPool.size(); i++) {
//        IMIAniTriggerPtr t_trigger = m_triggerPool[i];
//        t_trigger->destroy();
//    }
//    m_triggerPool.destroy();
    //
    for (s32 i = 0; i<m_effectUnitPool.size(); i++) {
        IMIffectUnitPtr t_unit = m_effectUnitPool[i];
        t_unit->destroy();
    }
    m_effectUnitPool.destroy();
//    //
//    for (s32 i = 0; i<m_filterBasePool.size(); i++) {
//        IMIFilterBasePtr t_filterBase = m_filterBasePool[i];
//        IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//        if( t_picproc) {
//            t_picproc->clearFilter(t_filterBase);
//        }
//    }
//    m_filterBasePool.destroy();
    for (s32 i = 0; i<m_deformPool.size(); i++) {
        IMIDeformImageMovePtr t_deform = m_deformPool[i];
        IMIDeformMgrPtr t_deformMgr = mApp->getDeformMgr();
        t_deform->m_rule=1;
    }
    m_deformPool.destroy();
    m_lock->unlock();
    if (m_cb) {
        IMIString msg = IMIString::format("effectpackageremovesuccess_%s",m_module_name.c_str());
        (*m_cb)(msg.c_str(), m_obj);
    }
}

void IMIffectPackage::open(){
    IMIModuleBase::open();
    m_aniState = EFFECT_ANI_RUN;
}

void IMIffectPackage::close(){
    IMIModuleBase::close();
    m_aniState = EFFECT_ANI_END;
}

void IMIffectPackage::reset(){
    m_aniState = EFFECT_ANI_WAIT;
    for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
        IMIffectUnitPtr t_unit = m_effectUnitPool[i];
        t_unit->setEnd(false);
    }
}

void IMIffectPackage::update(f32 _dt) {
    IMIModuleBase::update(_dt);
    if (m_aniState == EFFECT_ANI_RUN) {
        _updateEffectUnits(_dt);
    }
}

void IMIffectPackage::_updateEffectUnits(f32 _dt){
    bool end = true;
    for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
        IMIffectUnitPtr t_unit = m_effectUnitPool[i];
        if (!t_unit->isEnd()) {
            end = false;
            break;
        }
    }
    if (end) {
        m_aniState = EFFECT_ANI_END;
        if (m_cb) {
            IMIString msg = IMIString::format("effectpackageend_%s",m_module_name.c_str());
            (*m_cb)(msg.c_str(), m_obj);
            reset();
        }
    }
}

bool IMIffectPackage::procEvent(IMIEventPtr _event) {
    return  true;
}

void IMIffectPackage::addEffectUnit(IMINodePtr _nodePtr){
    if (_nodePtr) {
        IMIffectUnitPtr effectUnit = MakeSharedPtr<IMIffectUnit>(mApp);
        effectUnit->init(_nodePtr);
        m_effectUnitPool.append(effectUnit);
    }
}

//bool IMIffectPackage::_hasAttachment(IMIAniTexAttachmentPtr _attachment){
//    for (s32 i = 0; i<m_attachmentPool.size(); i++) {
//        IMIAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        if (t_attachment == _attachment) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void IMIffectPackage::addAttachment(IMIAniTexAttachmentPtr _attachment){
//    m_lock->lock();
////    if (_attachment && !_hasAttachment(_attachment)) {
////        mApp->getActionMgr()->addAni(_attachment);
////        m_attachmentPool.append(_attachment);
////    }
//    m_lock->unlock();
//}
//
//bool IMIffectPackage::_hasTrigger(IMIAniTriggerPtr _trigger){
//    for (s32 i = 0; i<m_triggerPool.size(); i++) {
//        IMIAniTriggerPtr t_trigger = m_triggerPool[i];
//        if (t_trigger == _trigger) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void IMIffectPackage::addTrigger(IMIAniTriggerPtr _trigger){
//    m_lock->lock();
//    if (_trigger && !_hasTrigger(_trigger)) {
//        m_triggerPool.append(_trigger);
//    }
//    m_lock->unlock();
//}

void IMIffectPackage::addFilter(IMIFilterBasePtr _filter){
//    IMIPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if(_filter && t_picproc){
//        _filter->create();
//        t_picproc->addFilter(_filter);
//        t_picproc->openFilter(_filter);
//        m_filterBasePool.append(_filter);
//    }
}

void IMIffectPackage::addDefrom(IMIDeformImageMovePtr _deform){
    IMIDeformMgrPtr t_deformMrg = mApp->getDeformMgr();
    if(_deform && t_deformMrg){
        t_deformMrg->pushDeform(_deform);
        m_deformPool.append(_deform);
    }
}

//IMIAniTexAttachmentPtr IMIffectPackage::getTexAttachment(s32 _channel){
//    for (s32 i = 0; i < m_attachmentPool.size(); i++) {
//        IMIAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        IMIAniTexAttachment::TEXATTACHSPARAM t_param = t_attachment->getParam();
//        if (t_param.channel == _channel) {
//            return t_attachment;
//        }
//    }
//    return nullptr;
//}




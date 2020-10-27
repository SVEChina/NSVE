//
// SVEffectPackage.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVEffectPackage.h"
#include "../app/SVGlobalMgr.h"
#include "../core/SVSpine.h"
#include "../core/SVDeformImageMove.h"
#include "../work/SVTdCore.h"
#include "../base/SVPreDeclare.h"
#include "../node/SVNode.h"
#include "../node/SVSpineNode.h"
#include "../node/SVSpriteNode.h"
#include "../node/SVBitFontNode.h"
#include "../node/SVFrameAniNode.h"
#include "../event/SVEvent.h"
#include "../basesys/SVSceneMgr.h"
#include "../mtl/SVParseLUTFilter.h"
#include "../basesys/SVBasicSys.h"
#include "../basesys/SVDeformMgr.h"
#include "../basesys/SVConfig.h"
#include "../basesys/SVScene.h"

using namespace sv;


void spinenode_callback(SVSpineNodePtr _node,void* _obj,s32 _status) {
    SVEffectUnit *t_unit = (SVEffectUnit*)(_obj);
    if(_status == 2) {
        t_unit->setEnd(true);
    }else if(_status == 3) {
        t_unit->setEnd(true);
    }
}

void frameani_callback(SVFrameAniNodePtr _node,void* _obj,s32 _status){
    SVEffectUnit *t_unit = (SVEffectUnit*)(_obj);
    if(_status == 2) {
        t_unit->setEnd(true);
    }else if(_status == 3) {
        t_unit->setEnd(true);
    }
}

SVEffectUnit::SVEffectUnit(SVInstPtr _app)
:SVGBaseEx(_app){
    m_end = true;
}

SVEffectUnit::~SVEffectUnit(){
    m_node = nullptr;
}

void SVEffectUnit::init(SVNodePtr _node){
    SVScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if(_node && t_scene){
        m_node = _node;
        t_scene->addNode(m_node);
//        //需要挂的人身上
//        if (_node->getBindIndex() >= 0 && !m_personAct) {
//            _attachToPeople(_node);
//        }
        SVSpineNodePtr t_spineNode = DYN_TO_SHAREPTR(SVSpineNode, m_node);
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
        SVFrameAniNodePtr t_frameAni = DYN_TO_SHAREPTR(SVFrameAniNode, m_node);
        if (t_frameAni) {
            t_frameAni->setCallback(frameani_callback, this);
            t_frameAni->play();
            setEnd(false);
        }
    }
}

void SVEffectUnit::_attachToPeople(SVNodePtr _node){
    
}

void SVEffectUnit::destroy(){
    if (m_node) {
        SVSpineNodePtr t_spineNode = DYN_TO_SHAREPTR(SVSpineNode, m_node);
        if (t_spineNode) {
            t_spineNode->stop();
        }
    }
}

SVNodePtr SVEffectUnit::getNode(){
    return m_node;
}

void SVEffectUnit::setEnd(bool _end){
    m_end = _end;
}

bool SVEffectUnit::isEnd(){
    return m_end;
}

SVEffectPackage::SVEffectPackage(SVInstPtr _app)
:SVModuleBase(_app){
    m_lock = MakeSharedPtr<SVLock>();
    m_aniState = EFFECT_ANI_WAIT;
}

SVEffectPackage::~SVEffectPackage(){
    m_lock = nullptr;
}

void SVEffectPackage::init(){
    SVModuleBase::init();
    startListen();
}

void SVEffectPackage::destroy(){
    m_lock->lock();
    SVModuleBase::destroy();
    stopListen();
//    for (s32 i = 0; i<m_attachmentPool.size(); i++) {
//        SVAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        t_attachment->removeFromActionMgr();
//        t_attachment->destroy();
//    }
//    m_attachmentPool.destroy();
    //
//    for (s32 i = 0; i<m_triggerPool.size(); i++) {
//        SVAniTriggerPtr t_trigger = m_triggerPool[i];
//        t_trigger->destroy();
//    }
//    m_triggerPool.destroy();
    //
    for (s32 i = 0; i<m_effectUnitPool.size(); i++) {
        SVEffectUnitPtr t_unit = m_effectUnitPool[i];
        t_unit->destroy();
    }
    m_effectUnitPool.destroy();
//    //
//    for (s32 i = 0; i<m_filterBasePool.size(); i++) {
//        SVFilterBasePtr t_filterBase = m_filterBasePool[i];
//        SVPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//        if( t_picproc) {
//            t_picproc->clearFilter(t_filterBase);
//        }
//    }
//    m_filterBasePool.destroy();
    for (s32 i = 0; i<m_deformPool.size(); i++) {
        SVDeformImageMovePtr t_deform = m_deformPool[i];
        SVDeformMgrPtr t_deformMgr = mApp->getDeformMgr();
        t_deform->m_rule=1;
    }
    m_deformPool.destroy();
    m_lock->unlock();
    if (m_cb) {
        SVString msg = SVString::format("effectpackageremovesuccess_%s",m_module_name.c_str());
        (*m_cb)(msg.c_str(), m_obj);
    }
}

void SVEffectPackage::open(){
    SVModuleBase::open();
    m_aniState = EFFECT_ANI_RUN;
}

void SVEffectPackage::close(){
    SVModuleBase::close();
    m_aniState = EFFECT_ANI_END;
}

void SVEffectPackage::reset(){
    m_aniState = EFFECT_ANI_WAIT;
    for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
        SVEffectUnitPtr t_unit = m_effectUnitPool[i];
        t_unit->setEnd(false);
    }
}

void SVEffectPackage::update(f32 _dt) {
    SVModuleBase::update(_dt);
    if (m_aniState == EFFECT_ANI_RUN) {
        _updateEffectUnits(_dt);
    }
}

void SVEffectPackage::_updateEffectUnits(f32 _dt){
    bool end = true;
    for (s32 i = 0; i < m_effectUnitPool.size(); i++) {
        SVEffectUnitPtr t_unit = m_effectUnitPool[i];
        if (!t_unit->isEnd()) {
            end = false;
            break;
        }
    }
    if (end) {
        m_aniState = EFFECT_ANI_END;
        if (m_cb) {
            SVString msg = SVString::format("effectpackageend_%s",m_module_name.c_str());
            (*m_cb)(msg.c_str(), m_obj);
            reset();
        }
    }
}

bool SVEffectPackage::procEvent(SVEventPtr _event) {
    return  true;
}

void SVEffectPackage::addEffectUnit(SVNodePtr _nodePtr){
    if (_nodePtr) {
        SVEffectUnitPtr effectUnit = MakeSharedPtr<SVEffectUnit>(mApp);
        effectUnit->init(_nodePtr);
        m_effectUnitPool.append(effectUnit);
    }
}

//bool SVEffectPackage::_hasAttachment(SVAniTexAttachmentPtr _attachment){
//    for (s32 i = 0; i<m_attachmentPool.size(); i++) {
//        SVAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        if (t_attachment == _attachment) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void SVEffectPackage::addAttachment(SVAniTexAttachmentPtr _attachment){
//    m_lock->lock();
////    if (_attachment && !_hasAttachment(_attachment)) {
////        mApp->getActionMgr()->addAni(_attachment);
////        m_attachmentPool.append(_attachment);
////    }
//    m_lock->unlock();
//}
//
//bool SVEffectPackage::_hasTrigger(SVAniTriggerPtr _trigger){
//    for (s32 i = 0; i<m_triggerPool.size(); i++) {
//        SVAniTriggerPtr t_trigger = m_triggerPool[i];
//        if (t_trigger == _trigger) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void SVEffectPackage::addTrigger(SVAniTriggerPtr _trigger){
//    m_lock->lock();
//    if (_trigger && !_hasTrigger(_trigger)) {
//        m_triggerPool.append(_trigger);
//    }
//    m_lock->unlock();
//}

void SVEffectPackage::addFilter(SVFilterBasePtr _filter){
//    SVPictureProcessPtr t_picproc = mApp->getBasicSys()->getPicProc();
//    if(_filter && t_picproc){
//        _filter->create();
//        t_picproc->addFilter(_filter);
//        t_picproc->openFilter(_filter);
//        m_filterBasePool.append(_filter);
//    }
}

void SVEffectPackage::addDefrom(SVDeformImageMovePtr _deform){
    SVDeformMgrPtr t_deformMrg = mApp->getDeformMgr();
    if(_deform && t_deformMrg){
        t_deformMrg->pushDeform(_deform);
        m_deformPool.append(_deform);
    }
}

//SVAniTexAttachmentPtr SVEffectPackage::getTexAttachment(s32 _channel){
//    for (s32 i = 0; i < m_attachmentPool.size(); i++) {
//        SVAniTexAttachmentPtr t_attachment = m_attachmentPool[i];
//        SVAniTexAttachment::TEXATTACHSPARAM t_param = t_attachment->getParam();
//        if (t_param.channel == _channel) {
//            return t_attachment;
//        }
//    }
//    return nullptr;
//}




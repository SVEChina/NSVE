//
// IMIOpLoadBase.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIOpLoadBase.h"
#include "../basesys/IMIBasicSys.h"
#include "../basesys/IMIPickProcess.h"
#include "../basesys/IMISceneMgr.h"
#include "../basesys/IMICameraMgr.h"
#include "../node/IMINode.h"
#include "../basesys/IMICameraNode.h"

using namespace imi;

IMIOpLoadBase::IMIOpLoadBase(IMIInstPtr _app)
: IMIOpBase(_app) {
}

IMIOpLoadBase::~IMIOpLoadBase() {
}

//回收节点有问题
IMIOpRecycleNode::IMIOpRecycleNode(IMIInstPtr _app, IMINodePtr _node)
:IMIOpBase(_app) {
    m_node = _node;
}

void IMIOpRecycleNode::_process(f32 dt){
    m_node = nullptr;
}

//拾取包
IMIOpPick::IMIOpPick(IMIInstPtr _app, s32 _x,s32 _y)
:IMIOpBase(_app){
    m_ui_x = _x;
    m_ui_y = _y;
}

//
IMIOpPick::~IMIOpPick() {
}

//
void IMIOpPick::_process(f32 dt){
    IMIPickProcessPtr t_pickModule = mApp->getBasicSys()->getPickModule();
    if(t_pickModule){
        f32 t_new_x = m_ui_x;
        f32 t_new_y = m_ui_y;
        //反适配
        mApp->getSceneMgr()->uiToScene(t_new_x,t_new_y);
        IMICameraNodePtr t_camera = mApp->m_global_mgr->m_camera_mgr->getMainCamera();
        if( t_pickModule->pickScene(t_camera,t_new_x, t_new_y) ){
            IMINodePtr t_pickNode = t_pickModule->getPickNode();
            if( t_pickNode ) {
                t_pickNode->setdrawAABB(true);
            }
        }
    }
}

//
// SVRenderObject.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVRenderObject.h"
#include "SVRenderScene.h"
#include "../app/SVInst.h"
#include "../basesys/SVConfig.h"
#include "../mtl/SVMtlCore.h"
#include "../base/SVDataSwap.h"
#include "SVFboObject.h"
#include "../rendercore/SVRenderMesh.h"
#include "../rendercore/SVRenderCmd.h"
#include "../rendercore/SVRenderCmdOut.h"
#include "../rendercore/SVRenderCmdGeo.h"

using namespace sv;

//
void SVRenderObjInst::pushLineCmd(SVRenderScenePtr _rs,
                                  RENDERSTREAMTYPE streamtype,
                                  FVec3 _start,
                                  FVec3 _end,
                                  SVMtlCorePtr _mtl,
                                  cptr8 tag){
//    if (!_rs)
//        return;
//    if(_rs->isSuspend())
//        return;
//    SVRenderCmdLinePtr t_cmd = MakeSharedPtr<SVRenderCmdLine>();
//    t_cmd->mTag = tag;
//    t_cmd->setLine(_start,_end);
//    t_cmd->setMtl(_mtl);
//    _rs->pushRenderCmd(streamtype, t_cmd);
}
//
void SVRenderObjInst::pushRectCmd(SVRenderScenePtr _rs,
                                  RENDERSTREAMTYPE streamtype,
                                  SVRect& _rect,
                                  SVMtlCorePtr _mtl,
                                  cptr8 tag){
//    if (!_rs)
//        return;
//    if(_rs->isSuspend())
//        return;
//    SVRenderCmdRectPtr t_cmd = MakeSharedPtr<SVRenderCmdRect>();
//    t_cmd->mTag = tag;
//    t_cmd->setRect(_rect);
//    t_cmd->setMtl(_mtl);
//    _rs->pushRenderCmd(streamtype, t_cmd);
}
//
void SVRenderObjInst::pushAABBCmd(SVRenderScenePtr _rs,
                                  RENDERSTREAMTYPE streamtype,
                                  SVBoundBox& _aabb,
                                  SVMtlCorePtr _mtl,
                                  cptr8 tag){
//    if (!_rs)
//        return;
//    if(_rs->isSuspend())
//        return;
//    SVRenderCmdAABBPtr t_cmd = MakeSharedPtr<SVRenderCmdAABB>();
//    t_cmd->mTag = tag;
//    t_cmd->setAABB(_aabb);
//    t_cmd->setMtl(_mtl);
//    _rs->pushRenderCmd(streamtype, t_cmd);
}


SVRenderObject::SVRenderObject()
:m_pMesh(nullptr)
,m_pMtl(nullptr) {
}

SVRenderObject::~SVRenderObject() {
    m_pMesh = nullptr;
    m_pMtl = nullptr;
}

void SVRenderObject::setMesh(SVRenderMeshPtr _mesh){
    m_pMesh = _mesh;
}

void SVRenderObject::setMtl(SVMtlCorePtr _mtl,bool _copy){
//    if(_copy){
//        if(_mtl){
//            m_pMtl = _mtl->clone();
//        }else{
//            m_pMtl = nullptr;
//        }
//    }else{
//        m_pMtl = _mtl;
//    }
}

void SVRenderObject::pushCmd(SVRenderScenePtr _rs, RENDERSTREAMTYPE streamtype, cptr8 tag) {
    if (!_rs)
        return;
    if(_rs->isSuspend())
        return;
    SVRenderCmdNorPtr t_cmd = MakeSharedPtr<SVRenderCmdNor>();
    t_cmd->mTag = tag;
    t_cmd->setMesh(m_pMesh);
    t_cmd->setMaterial(m_pMtl);
    _rs->pushRenderCmd(streamtype, t_cmd);
}

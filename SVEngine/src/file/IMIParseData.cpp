//
// IMIParseData.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseData.h"
#include "../app/IMIInst.h"
#include "../node/IMINode.h"
#include "../basesys/IMIScene.h"
#include "../basesys/IMISceneMgr.h"

using namespace imi;

//解析基本数据
IMIParseData::IMIParseData(IMIInstPtr _app)
: IMIGBaseEx(_app) {
    personid = 0;
}

IMIParseData::~IMIParseData() {
    _clearNode();
}

void IMIParseData::generate(s32 resid) {
}

void IMIParseData::generate(s32 resid, cptr8 path) {
}

void IMIParseData::suspend() {
    IMIScenePtr t_scene = mApp->getSceneMgr()->getScene();
    if (t_scene) {
        for (s32 i = 0; i < m_Nodes.size(); i++) {
            t_scene->addNode(m_Nodes[i]);
        }
        m_Nodes.destroy();
    }
}

void IMIParseData::_addNode(IMINodePtr _node) {
    if (_node) {
        m_Nodes.append(_node);
    }
}

void IMIParseData::_clearNode() {
    for (s32 i = 0; i < m_Nodes.size(); i++) {
        m_Nodes[i] = nullptr;
    }
    m_Nodes.destroy();
}



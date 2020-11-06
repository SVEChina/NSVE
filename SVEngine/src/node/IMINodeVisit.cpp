//
// IMINodeVisit.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMINodeVisit.h"
#include "IMINode.h"
#include "IMISpineNode.h"
#include "../core/IMISpine.h"
#include "../base/IMIBounds.h"

using namespace imi;

bool IMIVisitorBase::visit(IMINodePtr _node) {
    return false;
}

//
IMIVisitCollectResID::IMIVisitCollectResID(u32 _resid)
:m_targetResUID(_resid) {
}

bool IMIVisitCollectResID::visit(IMINodePtr _node) {
//    if (_node && _node->getresUID() == m_targetResUID) {
//        m_resUIDSet.append(m_targetResUID);
//    }
    return false;
}

IMISpineNodeNameVisitor::IMISpineNodeNameVisitor(cptr8 _nodeName)
:m_nodeName(_nodeName) {
}

bool IMISpineNodeNameVisitor::visit(IMINodePtr _node) {
    IMISpineNode *t_spianNode = dynamic_cast<IMISpineNode *>(_node.get());
    if (t_spianNode && t_spianNode->getSpine()->m_spineName == m_nodeName) {
        m_spineNodeSet.append(_node);
    }
    return true;
}

//
IMIVisitCollectAllNode::IMIVisitCollectAllNode() {
}

bool IMIVisitCollectAllNode::visit(IMINodePtr _node) {
    m_nodearray.append(_node);
    return true;
}


IMIVisitorNodeName::IMIVisitorNodeName(cptr8 _nodeName)
:m_nodeName(_nodeName) {
}

bool IMIVisitorNodeName::visit(IMINodePtr _node) {
    if (strcmp(_node->getname(), m_nodeName.c_str())  == 0) {
        m_nodeSet.append(_node);
    }
    return true;
}

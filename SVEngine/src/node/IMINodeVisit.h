//
// IMINodeVisit.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_NODEVISIT_H
#define IMI_NODEVISIT_H

#include "../base/IMIObject.h"
#include "../node/IMINodeDeclare.h"

namespace imi {
    
    class IMIVisitorBase : public IMIObject {
    public:
        virtual bool visit(IMINodePtr _node);
    };
    
    //获取目标RESID节点
    class IMIVisitCollectResID : public IMIVisitorBase {
    public:
        IMIVisitCollectResID(u32 resid);
        
        virtual bool visit(IMINodePtr _node);
        
    protected:
        typedef IMIArray<u32> RESSET;
        RESSET m_resUIDSet;
        u32 m_targetResUID;
    };
    
    //获取系统中spineName为特定值的所有spine节点
    class IMISpineNodeNameVisitor : public IMIVisitorBase {
        typedef IMIArray<IMINodePtr> SPINENODESET;
    public:
        IMISpineNodeNameVisitor(cptr8 nodeName);
        
        virtual bool visit(IMINodePtr _node);
        
    protected:
        SPINENODESET m_spineNodeSet;
        IMIString m_nodeName;
    };
    
    //获取场景的所有子节点
    class IMIVisitCollectAllNode : public IMIVisitorBase {
    public:
        IMIVisitCollectAllNode();
        
        virtual bool visit(IMINodePtr _node);
        
    public:
        typedef IMIArray<IMINodePtr> NodeArray;
        NodeArray m_nodearray;
    };
    
    //获取系统中spineName为特定值的所有spine节点
    class IMIVisitorNodeName : public IMIVisitorBase {
        typedef IMIArray<IMINodePtr> NODESET;
    public:
        IMIVisitorNodeName(cptr8 nodeName);
        
        virtual bool visit(IMINodePtr _node);
        
    public:
        NODESET m_nodeSet;
        IMIString m_nodeName;
    };
    
    
    
}//!namespace imi



#endif //IMI_NODEVISIT_H

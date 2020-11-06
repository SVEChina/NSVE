//
// IMIScene.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SCENE_H
#define IMI_SCENE_H

#include "../base/IMIGBase.h"
#include "../base/IMIRect.h"
#include "../base/IMIBounds.h"
#include "../base/IMIColor.h"
#include "../node/IMINodeDeclare.h"
#include "../event/IMIEventDeclare.h"
#include "../work/IMIWorkDeclare.h"

#include <vector>
#include <map>

namespace imi {
    
    /*
     scenetree进行场景管理
     scenetree BVH
     */

    class IMITreeLeaf :public IMIGBaseEx {
    public:
        IMITreeLeaf(IMIInstPtr _app);
               
        ~IMITreeLeaf();
        
        bool addNode(IMINodePtr node);
        
        bool removeNode(IMINodePtr node);
        
        bool hasNode(IMINodePtr node);
        
        void clear();
        
        void update(f32 _dt);
        
        void visit(IMIVisitorBasePtr _visitor);
        
    public:
        //节点列表
        typedef std::vector<IMINodePtr> NODEPOOL;
        NODEPOOL m_nodePool;
        //
        //树包围盒
        IMIBoundBox m_treeBox;
    };

    class IMISceneTree :public IMIGBaseEx{
    public:
        IMISceneTree(IMIInstPtr _app);
        
        ~IMISceneTree();
        
        void clear();
        
        void resize(FVec3 _unit);
        
        FVec3 getWorldSize();
        
        void update(f32 _dt);
        
        void visit(IMIVisitorBasePtr _visitor);
        
        bool addNode(IMINodePtr node);
        
        bool addNode(IMINodePtr node, s32 iZOrder);
        
        bool removeNode(IMINodePtr node);
        
        bool hasNode(IMINodePtr node);
        
    protected:
        s32 _transID(FVec3 _pos);
        
        //锁
        IMILockSpinPtr m_treeLock;
        //
        FVec3 m_leafSize;     //节点的尺寸
        //
        typedef std::map<s32,IMITreeLeafPtr> LEAFPOOL;
        LEAFPOOL m_leafPool;
        //
        IMIBoundBox m_wold_range;
    };
            
    /*场景*/
    class IMIScene : public IMIGBaseEx {
    public:
        IMIScene(IMIInstPtr _app,cptr8 name);
        
        ~IMIScene();
        
        //世界大小和深度
        void create();
        
        void destroy();
        
        void addNode(IMINodePtr _node);
        
        void addNode(IMINodePtr _node,s32 _zorder);
        
        void removeNode(IMINodePtr _node);
        
        void active();
        
        void unactive();
        
        void update(f32 dert);
        
        void visit(IMIVisitorBasePtr _visitor);
        
        cptr8 getname(){ return m_name.c_str(); }
        
        void setSceneColor(f32 _r,f32 _g,f32 _b,f32 _a);
        
        FVec3 getWorldSize();
        
    protected:
        //场景名称
        IMIString m_name;
        //世界树
        IMISceneTreePtr m_pSceneTree;
        //
        IMIColor m_color;

    public:
        bool procEvent(IMIEventPtr _event);
        
        //序列化场景
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
        void test();
    };

        
}//!namespace imi


#endif //IMI_SCENE_H

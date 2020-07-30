//
// SVScene.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SCENE_H
#define SV_SCENE_H

#include "../base/SVGBase.h"
#include "../base/SVRect.h"
#include "../base/SVBounds.h"
#include "../base/SVColor.h"
#include "../node/SVNodeDeclare.h"
#include "../event/SVEventDeclare.h"
#include "../work/SVWorkDeclare.h"

#include <vector>
#include <map>

namespace sv {
    
    /*
     scenetree进行场景管理
     scenetree BVH
     */

    class SVTreeLeaf :public SVGBaseEx {
    public:
        SVTreeLeaf(SVInstPtr _app);
               
        ~SVTreeLeaf();
        
        bool addNode(SVNodePtr node);
        
        bool removeNode(SVNodePtr node);
        
        bool hasNode(SVNodePtr node);
        
        void clear();
        
        void update(f32 _dt);
        
        void visit(SVVisitorBasePtr _visitor);
        
    public:
        //节点列表
        typedef std::vector<SVNodePtr> NODEPOOL;
        NODEPOOL m_nodePool;
        //
        //树包围盒
        SVBoundBox m_treeBox;
    };

    class SVSceneTree :public SVGBaseEx{
    public:
        SVSceneTree(SVInstPtr _app);
        
        ~SVSceneTree();
        
        void clear();
        
        void resize(FVec3 _unit);
        
        FVec3 getWorldSize();
        
        void update(f32 _dt);
        
        void visit(SVVisitorBasePtr _visitor);
        
        bool addNode(SVNodePtr node);
        
        bool addNode(SVNodePtr node, s32 iZOrder);
        
        bool removeNode(SVNodePtr node);
        
        bool hasNode(SVNodePtr node);
        
    protected:
        s32 _transID(FVec3 _pos);
        
        //锁
        SVLockSpinPtr m_treeLock;
        //
        FVec3 m_leafSize;     //节点的尺寸
        //
        typedef std::map<s32,SVTreeLeafPtr> LEAFPOOL;
        LEAFPOOL m_leafPool;
        //
        SVBoundBox m_wold_range;
    };
            
    /*场景*/
    class SVScene : public SVGBaseEx {
    public:
        SVScene(SVInstPtr _app,cptr8 name);
        
        ~SVScene();
        
        //世界大小和深度
        void create();
        
        void destroy();
        
        void addNode(SVNodePtr _node);
        
        void addNode(SVNodePtr _node,s32 _zorder);
        
        void removeNode(SVNodePtr _node);
        
        void active();
        
        void unactive();
        
        void update(f32 dert);
        
        void visit(SVVisitorBasePtr _visitor);
        
        cptr8 getname(){ return m_name.c_str(); }
        
        void setSceneColor(f32 _r,f32 _g,f32 _b,f32 _a);
        
        FVec3 getWorldSize();
        
    protected:
        //场景名称
        SVString m_name;
        //世界树
        SVSceneTreePtr m_pSceneTree;
        //
        SVColor m_color;

    public:
        bool procEvent(SVEventPtr _event);
        
        //序列化场景
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
        void test();
    };

        
}//!namespace sv


#endif //SV_SCENE_H

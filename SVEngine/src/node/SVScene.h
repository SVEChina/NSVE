//
// SVScene.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SCENE_H
#define SV_SCENE_H

#include "SVNode.h"
#include "../base/SVRect.h"

namespace sv {
    
    namespace node{
        
        //四叉数进行场景管理
        class SVTree4 :public SVGBase{
        public:
            SVTree4(SVInst *_app);
            
            ~SVTree4();
            
            //世界大小和深度
            void create(util::SVBoundBox& _box,s32 _depth);
            
            void destroy();
            
            void update(f32 _dt);
            
            void visit(SVVisitorBasePtr _visitor);
            //节点模块
            void addNode(SVNodePtr node);
            
            void addNode(SVNodePtr node, s32 iZOrder);
            
            bool removeNode(SVNodePtr node);
            
            bool hasNode(SVNodePtr node);
            
            void clearNode();
            
        protected:
            //判断是否in
            bool _isIn(SVNodePtr _node);
            //锁
            SVLockPtr m_treeLock;
            //子节点
            SVTree4Ptr m_pTreeNode[4];
            //关联节点
            SVNodePtr m_node;
            //节点列表
            typedef util::SVArray<SVNodePtr> NODEPOOL;
            NODEPOOL m_nodePool;
            //树包围盒
            util::SVBoundBox m_treeBox;
        };
                
        //场景
        class SVScene : public SVGBase {
        public:
            SVScene(SVInst *_app,cptr8 name);
            
            ~SVScene();
            
            //世界大小和深度
            void create(f32 _worldw = SV_WORLD_SIZE ,f32 _worldh = SV_WORLD_SIZE ,s32 _depth = SV_WORLD_DEPTH);
            
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
            
        protected:
            //场景名称
            util::SVString m_name;
            //世界树
            SVTree4Ptr m_pSceneTree;
            //
            SVColor m_color;
            //
            f32 m_worldW;
            f32 m_worldH;
            s32 m_worldD;

        public:
            bool procEvent(SVEventPtr _event);
            
        public:
            //序列化场景
            virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                                RAPIDJSON_NAMESPACE::Value &_objValue);
            
            virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        };

        
    }//!namespace node
    
}//!namespace sv


#endif //SV_SCENE_H

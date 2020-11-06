//
// IMINode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_NODE_H
#define IMI_NODE_H

#include "IMINodeDef.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../rendercore/IMIRenderDef.h"
#include "../core/IMIVertDef.h"
#include "../base/IMIMat4d.h"
#include "../base/IMIVec3.h"
#include "../base/IMIQuat.h"
#include "../base/IMIBounds.h"
#include "../base/IMIPreDeclare.h"
#include "../event/IMIEventProc.h"
#include "../detect/IMIPerson.h"
#include "../base/IMIDataSwap.h"

namespace imi {
    
    /*
     node 概念
     */

    class IMINode : public IMIEventProc {
    public:
        IMINode(IMIInstPtr _app);
        
        virtual ~IMINode();

        virtual void enter();
        
        virtual void exit();
        
        void deep_update(f32 dt);
        
        //深度访问
        void deep_visit(IMIVisitorBasePtr _visit);
        
        //选择访问 用于子访问
        void select_visit(IMIVisitorBasePtr _visit);
        
        FMat4 getLocalMat();
        
        FMat4 getAbsoluteMat();
        
        FMat4 getIAbsoluteMat();
        
        void setPosition(f32 x, f32 y, f32 z);

        void setPosition(FVec3& _pos);

        void setRotation(f32 x, f32 y, f32 z);

        void setRotation(FVec3& _rot);

        void setQuat(IMIQuat& _quat);

        void setScale(f32 x, f32 y, f32 z);

        void setScale(FVec3& _scale);
        
        virtual void setAlpha(f32 _alpha);
        
        void setbeSelect(bool _select);
        
        void setcanSelect(bool _select);
        
        void setRSType(RENDERSTREAMTYPE _retype);
        
        RENDERSTREAMTYPE getRSType();
        
        void setdrawAABB(bool _drawaabb);
        
        bool getDrawAABB();
        
        FVec3 getPosition();

        FVec3 getRotation();
        
        FVec3 getScale();

        IMIQuat getQuat();
        
        void setAABB(IMIBoundBox& _aabb);
        
        IMIBoundBox getAABB();
        
        IMIBoundBox getAABBSW();
        
        IMIMtlCorePtr setMtl(cptr8 _name);
        
        IMIMtlCorePtr getMtl() { return m_mtl; } //材质
        
        IMISurfacePtr getSurface() { return m_surface; } //材质表面
        
        inline cptr8 getType(){ return ntype.c_str(); }
        
        inline cptr8 getname(){return m_name.c_str();}
        
        inline bool canSelect(){ return m_canSelect; }
        
        inline bool beSelect(){ return m_beSelect; }
        
        inline bool canProcEvent(){ return m_canProcEvent; }
        
        inline bool visible(){ return m_visible; }
    
        inline void setname(const char* _name){ m_name = _name; }
        
        inline void setvisible(bool _visible){ m_visible = _visible; }
        
    protected:
        //更新
        virtual void update(f32 dt);
        //剔除
        virtual bool _clip();
        //渲染
        virtual void render();
        //
        IMIString ntype;         //节点类型
        IMIString m_name;        //唯一名称
        bool m_canSelect;       //是否可以选择
        bool m_canProcEvent;    //是否能处理事件
        bool m_visible;         //是否可见
        bool m_drawBox;         //是否渲染包围盒
        bool m_dirty;
        bool m_beSelect;        //是否被选择
        //
        RENDERSTREAMTYPE m_rsType;      //渲染流类型
        f32 m_alpha;
        //
        IMIBoundBox m_aabbBox;   //AABB包围盒
        IMIBoundBox m_aabbBox_sw;//AABB世界包围盒
        //
        FMat4 m_localMat;       //本地矩阵
        FMat4 m_absolutMat;     //绝对世界矩阵
        FMat4 m_iabsolutMat;    //逆绝对世界矩阵
        //位置属性
        IMIAttriPos m_attri_pos;
        //渲染属性
        IMIAttriRender m_attri_render;
        //父节点
        IMINodePtr m_parent;
        //
        IMIMtlCorePtr m_mtl;
        //材质表面
        IMISurfacePtr m_surface;

    public:
        //序列化接口
        IMIString m_rootPath;
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        virtual void _toJsonData(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                         RAPIDJSON_NAMESPACE::Value &locationObj);
        
        virtual void _fromJsonData(RAPIDJSON_NAMESPACE::Value &item);

    };

}//!namespace imi



#endif //IMI_NODE_H

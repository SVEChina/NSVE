//
// SVNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_NODE_H
#define SV_NODE_H

#include "SVNodeDef.h"
#include "../mtl/SVMtlDeclare.h"
#include "../rendercore/SVRenderDef.h"
#include "../core/SVVertDef.h"
#include "../base/SVMat4d.h"
#include "../base/SVVec3.h"
#include "../base/SVQuat.h"
#include "../base/SVBounds.h"
#include "../base/SVPreDeclare.h"
#include "../event/SVEventProc.h"
#include "../detect/SVPerson.h"
#include "../base/SVDataSwap.h"

namespace sv {
    
    /*
     entity 概念
     */

    class SVNode : public SVEventProc {
    public:
        SVNode(SVInstPtr _app);
        
        ~SVNode();
        
        bool operator <(const SVNode& rhs) const{
            return m_iZOrder < rhs.m_iZOrder;
        }
        bool operator >(const SVNode& rhs) const{
            return m_iZOrder > rhs.m_iZOrder;
        }

        virtual void enter();
        
        virtual void exit();
        
        void deep_update(f32 dt);
        
        //深度访问
        void deep_visit(SVVisitorBasePtr _visit);
        
        //选择访问 用于子访问
        void select_visit(SVVisitorBasePtr _visit);
        
        FMat4 getLocalMat();
        
        FMat4 getAbsoluteMat();
        
        FMat4 getIAbsoluteMat();
        
        void setPosition(f32 x, f32 y, f32 z);

        void setPosition(FVec3& _pos);

        void setRotation(f32 x, f32 y, f32 z);

        void setRotation(FVec3& _rot);

        void setQuat(SVQuat& _quat);

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

        SVQuat getQuat();
        
        void setAABB(SVBoundBox& _aabb);
        
        SVBoundBox getAABB();
        
        SVBoundBox getAABBSW();
        //设置z顺序
        void setZOrder(s32 _zorder);
        
        inline cptr8 getType(){ return ntype.c_str(); }
        
        inline cptr8 getname(){return m_name.c_str();}
        
        inline s32 getZOrder(){ return m_iZOrder;}
        
        inline bool getcanSelect(){ return m_canSelect; }
        
        inline bool getbeSelect(){ return m_beSelect; }
        
        inline bool getcanProcEvent(){ return m_canProcEvent; }
        
        inline bool getvisible(){ return m_visible; }
    
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
        SVString ntype;         //节点类型
        SVString m_name;        //唯一名称
        s32 m_iZOrder;          //Z值
        bool m_canSelect;       //是否可以选择
        bool m_canProcEvent;    //是否能处理事件
        bool m_visible;         //是否可见
        bool m_drawBox;         //是否渲染包围盒
        //
        RENDERSTREAMTYPE m_rsType;      //渲染流类型
        f32 m_alpha;
        bool m_dirty;
        bool m_beSelect;        //是否被选择
        //
        SVBoundBox m_aabbBox;   //AABB包围盒
        SVBoundBox m_aabbBox_sw;//AABB世界包围盒
        //
        FMat4 m_localMat;       //本地矩阵
        FMat4 m_absolutMat;     //绝对世界矩阵
        FMat4 m_iabsolutMat;    //逆绝对世界矩阵
        
        //位置属性
        SVAttriPos m_attri_pos;
        //渲染属性
        SVAttriRender m_attri_render;
        //材质表面
        SVSurfacePtr m_surface;
        //
        SVNodePtr m_parent;
        //
        bool m_needsort;

    public:
        //序列化接口
        SVString m_rootPath;
        virtual void toJSON(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                            RAPIDJSON_NAMESPACE::Value &_objValue);
        
        virtual void fromJSON(RAPIDJSON_NAMESPACE::Value &item);
        
    protected:
        virtual void _toJsonData(RAPIDJSON_NAMESPACE::Document::AllocatorType &_allocator,
                         RAPIDJSON_NAMESPACE::Value &locationObj);
        
        virtual void _fromJsonData(RAPIDJSON_NAMESPACE::Value &item);

    };

}//!namespace sv



#endif //SV_NODE_H

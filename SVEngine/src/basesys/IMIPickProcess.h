//
// IMIPickProcess.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_PICKMODULE_H
#define IMI_PICKMODULE_H

#include "IMIProcess.h"
#include "../base/IMIVec3.h"
#include "../node/IMINodeDeclare.h"
#include "../node/IMINodeVisit.h"
#include "../base/IMIMat4.h"

//获取射线拾取(拣选器)

typedef void (*pick_callback)(void* _obj,void* _node,int _flag);

namespace imi {

    class IMIVisitRayPick : public IMIVisitorBase {
    public:
        IMIVisitRayPick(FVec3& _rayStart,FVec3& _rayEnd);
        
        ~IMIVisitRayPick();
        
        virtual bool visit(IMINodePtr _node);
        
        IMINodePtr getCrossNode(FVec3& _campos);
        
    protected:
        FVec3 m_rayStart;
        FVec3 m_rayEnd;
        typedef IMIArray<IMINodePtr> NodeArray;
        NodeArray m_nodearray;
    };

    class IMIVisitRayPickUI : public IMIVisitRayPick {
    public:
        IMIVisitRayPickUI(FVec3& _rayStart,FVec3& _rayEnd);
        
        ~IMIVisitRayPickUI();
        
        virtual bool visit(IMINodePtr _node);
        
        IMINodePtr getPickNode();
        
    protected:
        IMINodePtr m_pNode;
    };


    class IMIPickProcess : public IMIProcess {
    public:
        IMIPickProcess(IMIInstPtr _app);
        
        ~IMIPickProcess();
        //
        void enablePick();
        //
        void disablePick();
        //
        void clear();
        //场景拾取
        bool pickScene(IMICameraNodePtr _cam,s32 _sx,s32 _sy);
        //UI拾取
        bool pickUI(s32 _sx,s32 _sy);
        //移动节点
        void moveNode(IMICameraNodePtr _cam,s32 _sx,s32 _sy);
        //获取交叉点
        bool getCrossPoint(IMICameraNodePtr _cam,s32 _sx,s32 _sy,FVec3& _crosspt);
        //
        bool getCrossPointUI(IMICameraNodePtr _cam,s32 _sx,s32 _sy,FVec3& _crosspt);
        //
        bool getCrossPointWithPlane(IMICameraNodePtr _cam,s32 _sx,s32 _sy,FVec3& _crosspt, FVec4& _plane);
        //
        IMINodePtr getPickNode();
        //
        IMINodePtr getPickUI();
        //
        virtual bool procEvent(IMIEventPtr _event);
        
        void transScreenPtToWorld(FVec2 &_screenPt, FVec3 &_worldPt);
        
    protected:
        //
        void _pick(IMINodePtr _node);
        //
        void _pickUI(IMINodePtr _node);
        //获取射线
        bool _getRay(IMICameraNodePtr _cam,s32 _sx,s32 _sy,FVec3& _rayStart,FVec3& _rayEnd);
        bool _getRayMat(IMICameraNodePtr _cam,FMat4 _vpMat,s32 _sx,s32 _sy,FVec3& _rayStart,FVec3& _rayEnd);
        //
        bool m_enablePick;
        IMINodePtr m_curPickNode;
        IMINodePtr m_curPickUI;
    };
    
    

}//!namespace imi




#endif //IMI_PICKMODULE_H

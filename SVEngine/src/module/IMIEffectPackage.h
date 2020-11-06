//
// IMIEffectPackage.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_EFFECTPACKAGE_H
#define IMI_EFFECTPACKAGE_H

#include "IMIModuleBase.h"

namespace imi{
    
    class IMIffectUnit : public IMIGBaseEx{
    public:
        IMIffectUnit(IMIInstPtr _app);
        
        ~IMIffectUnit();
        
        void init(IMINodePtr _node);
        
        void destroy();
        
        IMINodePtr getNode();
        
        void setEnd(bool _end);
        
        bool isEnd();
        
    protected:
        void _attachToPeople(IMINodePtr _node);

        IMINodePtr m_node;
       
        bool m_end;
    };
    
    class IMIffectPackage : public IMIModuleBase {
    public:
        enum EFFECTANISTATE{
            EFFECT_ANI_WAIT = 0,
            EFFECT_ANI_RUN,
            EFFECT_ANI_END
        };
        IMIffectPackage(IMIInstPtr _app);
        
        ~IMIffectPackage();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        virtual void open();
        
        virtual void close();
        
        void reset();
        
        virtual bool procEvent(IMIEventPtr _event);
        
        void addEffectUnit(IMINodePtr _nodePtr);
        
        void addFilter(IMIFilterBasePtr _filter);
        
        void addDefrom(IMIDeformImageMovePtr _deform);
    protected:
        void _updateTriggers(f32 _dt);
        void _updateEffectUnits(f32 _dt);
        
        EFFECTANISTATE m_aniState;
        typedef IMIArray<IMIffectUnitPtr> IMIFFECTUNITPOOL;
        IMIFFECTUNITPOOL m_effectUnitPool;
//        typedef IMIArray<IMIAniTexAttachmentPtr> IMIATTACHMENTPOOL;
//        IMIATTACHMENTPOOL m_attachmentPool;
//        //trigger
//        typedef IMIArray<IMIAniTriggerPtr> IMITRIGGERPOOL;
//        IMITRIGGERPOOL m_triggerPool;
        //
        typedef IMIArray<IMIFilterBasePtr> IMIFILTERPOOL;
        IMIFILTERPOOL m_filterBasePool;
        typedef IMIArray<IMIDeformImageMovePtr> IMIDEFORMPOOL;
        IMIDEFORMPOOL m_deformPool;
        IMILockPtr m_lock;
    };
    
    
}//!namespace imi

#endif /* IMI_EFFECTPACKAGE_H */

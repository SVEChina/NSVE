//
// IMIAniUnit.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_ANIUNIT_ROT_H
#define IMI_ANIUNIT_ROT_H

#include "IMIAniUnit.h"

namespace imi {

    class IMIAniUnitRot  : public IMIAniUnit {
    public:
        IMIAniUnitRot(IMIInstPtr _app);
        
        virtual ~IMIAniUnitRot();
        
        virtual void init();

        virtual void destroy();
        
        virtual void bind(IMINodePtr _node);

        virtual void update(f32 _dt,IMINodePtr _node);
        
    protected:
        //
        f32 m_src_rot_x;
        f32 m_src_rot_y;
        f32 m_src_rot_z;
        //
        f32 m_dst_rot_x;
        f32 m_dst_rot_y;
        f32 m_dst_rot_z;
        //
        f32 m_rot_y_sp;
    };
    
}//!namespace imi



#endif //IMI_ANIUNIT_ROT_H

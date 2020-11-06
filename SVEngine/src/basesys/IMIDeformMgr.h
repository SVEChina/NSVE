//
//  IMIDeformMgr.h
//  IMIngine
//
//  Created by 徐子昱 on 2019/4/13.
//  Copyright © 2019 李晓帆. All rights reserved.
//

#ifndef IMI_DEFORM_MGR_H
#define IMI_DEFORM_MGR_H

#include "../basesys/IMISysBase.h"

namespace imi {
        
    //图片处理系统

    class IMIDeformMgr : public IMISysBase {
    public:
        IMIDeformMgr(IMIInstPtr _app);
        
        ~IMIDeformMgr();
        //
        void init();
        
        void update(f32 _dt);
        
        void destroy();

        void pushDeform(IMIDeformImageMovePtr deform);
        
        IMIDeformImageMovePtr getDeform(s32 _postion);
        
        void clear();
        
    protected:
        void removeEnd();

        IMILockPtr m_defromLock;
        IMIArray<IMIDeformImageMovePtr> m_deformArray;
        IMIArray<IMIDeformImageMovePtr> m_deformCir;
    };
    
}//!namespace imi

#endif /* IMI_DEFORM_MGR_H */

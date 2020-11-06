//
// IMIModel.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_MODEL_H
#define IMI_MODEL_H

#include "../base/IMIGBase.h"
#include "../base/IMIPreDeclare.h"
#include "../base/IMIBounds.h"

#include <vector>

namespace imi {
    
    /* 模型 由多个mesh构成 */

    class IMIModel : public IMIGBaseEx {
    public:
        IMIModel(IMIInstPtr _app);
        
        virtual ~IMIModel();
        
        cptr8 getName();
        
        void setName(cptr8 _name);
        
        void clear(){};
        
        void addMesh(IMIMesh3dPtr _mesh);
    
        IMIMesh3dPtr getMesh(s32 _index);
        
        s32  getMeshNum();
        
        void clearMesh();
        
        IMIBoundBox getBox();
        
        void update(f32 _dt,FMat4& _mat);
        
        void render();
        
        void createShadow();
        
        void bindSke(IMISkeletonPtr _ske);
        
        void unbindSke();
        
    protected:
        IMIString m_name;
        IMIBoundBox m_box;
        IMISkeletonPtr m_ske;
        //一个模型包含多个mesh
        typedef std::vector<IMIMesh3dPtr> MESHPOOL;
        MESHPOOL m_meshPool;
    };
        
    
}//!namespace imi



#endif //IMI_MODEL_H

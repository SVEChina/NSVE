//
// IMIPhysicsBodyCloth.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_BODIES_PHYSICSBODYCLOTH_H
#define IMI_BODIES_PHYSICSBODYCLOTH_H
#include "IMIPhysicsBodySoft.h"
#include "../../base/IMIVec3.h"
namespace imi {
    
    class IMIPhysicsBodyCloth : public IMIPhysicsBodySoft {
    public:
        IMIPhysicsBodyCloth(IMIInstPtr _app, btSoftBodyWorldInfo& _worldInfo, const FVec3& _corner00,
                           const FVec3& _corner10,
                           const FVec3& _corner01,
                           const FVec3& _corner11,
                           s32 _resx,
                           s32 _resy,
                           s32 _fixeds = 1 + 2 + 4 + 8,
                           bool gendiags = true);
        //根据已有的mesh顶点创建
        IMIPhysicsBodyCloth(IMIInstPtr _app, btSoftBodyWorldInfo& _worldInfo, const f32 *_vertices, const s32 *_indices, s32 _ntrangles,
        bool randomizeConstraints = true);
        
        ~IMIPhysicsBodyCloth();
        
        virtual void init();
        
        virtual void destroy();
        
        virtual void update(f32 _dt);
        
        void *getFaceVertexData();
        
        u32   getFaceVertexDataSize();
        
        u32   getFaceVertexCount();
    private:
        void _updateFaceVertexData();
    protected:
        u32 m_vertexCount;
        IMIDataSwapPtr m_pVertexData;
    };
    
}//!namespace imi

#endif //IMI_BODIES_PHYSICSBODYCLOTH_H

//
// SVSkinNode.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SKINNODE_H
#define SV_SKINNODE_H

#include "SVNode.h"
#include "../base/SVMap.h"

namespace sv {
    
    /*
     3d骨骼动画节点
     */
    
    class SVSkinNode : public SVNode {
    public:
        SVSkinNode(SVInstPtr _app);
        
        ~SVSkinNode();
        
        //更新
        virtual void update(f32 dt);

        //渲染
        virtual void render();
        
        std::vector<SVModelPtr> &getModel();
        void setModel(std::vector<SVModelPtr> &_models);
        void clearModel();
        
        std::vector<SVSurfacePtr> &getSurface();
        void setSurface(std::vector<SVSurfacePtr> &_surfaces);
        void clearSurface();
        
        std::vector<SVMtlCorePtr> &getMaterial();
        void setMaterial(std::vector<SVMtlCorePtr> &_mtls);
        void clearMaterial();
        
        //
        void setSke(SVSkeletonPtr _ske);
        
        void clearSke();
        
        //动画操作
        void addAni(SVAnimateSkinPtr _ani);
        
        void delAni(cptr8 _name);
        
        void clearAni();
        
        //播放控制
        void play(cptr8 _name);
        
        void pause();
        
        void stop();

    protected:
        std::vector<SVModelPtr> m_pModels;
        std::vector<SVSurfacePtr> m_pSurfaces;
        std::vector<SVMtlCorePtr> m_pMtls;
        
        SVSkeletonPtr m_pSke;
        
        typedef SVMap<SVString,SVAnimateSkinPtr> ANIPOOL;
        ANIPOOL m_aniPool;
        
        //当前动画
        SVAnimateSkinPtr m_pActAni;
        
    public:
        FVec3 m_filePos;
        FVec3 m_fileScale;
        SVQuat m_fileRot;
    };
        
}//!namespace sv

//
#endif //SV_SKINNODE_H



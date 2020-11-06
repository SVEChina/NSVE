//
// IMISkinNode.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SKINNODE_H
#define IMI_SKINNODE_H

#include "IMINode.h"
#include "../base/IMIMap.h"

namespace imi {
    
    /*
     3d骨骼动画节点
     */
    
    class IMISkinNode : public IMINode {
    public:
        IMISkinNode(IMIInstPtr _app);
        
        ~IMISkinNode();
        
        //更新
        virtual void update(f32 dt);

        //渲染
        virtual void render();
        
        std::vector<IMIModelPtr> &getModel();
        void setModel(std::vector<IMIModelPtr> &_models);
        void clearModel();
        
        std::vector<IMISurfacePtr> &getSurface();
        void setSurface(std::vector<IMISurfacePtr> &_surfaces);
        void clearSurface();
        
        std::vector<IMIMtlCorePtr> &getMaterial();
        void setMaterial(std::vector<IMIMtlCorePtr> &_mtls);
        void clearMaterial();
        
        //动画操作
        void addAni(IMIAnimateSkinPtr _ani);
        
        void delAni(cptr8 _name);
        
        void clearAni();
        
        //播放控制
        void play(cptr8 _name);
        
        void pause();
        
        void stop();

    protected:
        std::vector<IMIModelPtr> m_pModels;
        std::vector<IMISurfacePtr> m_pSurfaces;
        std::vector<IMIMtlCorePtr> m_pMtls;
        
        typedef IMIMap<IMIString,IMIAnimateSkinPtr> ANIPOOL;
        ANIPOOL m_aniPool;
        
        //当前动画
        IMIAnimateSkinPtr m_pActAni;
        
    public:
        FVec3 m_filePos;
        FVec3 m_fileScale;
        IMIQuat m_fileRot;
    };
        
}//!namespace imi

//
#endif //IMI_SKINNODE_H



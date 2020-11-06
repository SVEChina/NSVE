//
// IMIFrameOutTex.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_FRAMEOUT_TEX_H
#define IMI_FRAMEOUT_TEX_H

#include "IMIFrameOutNode.h"

namespace imi {

    class IMIFrameOutTex : public IMIFrameOutNode {
    public:
        IMIFrameOutTex(IMIInstPtr _app);

        virtual ~IMIFrameOutTex();

        void update(f32 dt);

        void render();

        s32 getTexId();

    private:
        //IMIRenderTexturePtr m_fbo;
        IMIRenderMeshPtr m_pMesh;
        IMIMtlCorePtr m_pMtl;
    };

}


#endif //IMI_FRAMEOUT_TEX_H

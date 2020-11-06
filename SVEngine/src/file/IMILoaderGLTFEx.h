//
// IMILoaderGLTFEX.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_LOADER_GLTF_EX_H
#define IMI_LOADER_GLTF_EX_H

#include "IMIFileLoader.h"
#include "../base/IMIPreDeclare.h"
#include "../rendercore/IMIRenderDeclare.h"
#include "../node/IMINodeDeclare.h"
#include "../base/IMIMap.h"
#include "../base/IMIArray.h"
#include "../base/imistr.h"
#include "../base/IMIMat4.h"
#include "../base/IMIDataSwap.h"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "../third/gltf/tiny_gltf.h"

namespace imi {
    
    typedef struct IMIGLTF {
//        std::vec
    }IMIGLTF;
    
    class IMILoaderGLTFEx : public IMIGBaseEx{
    public:
        IMILoaderGLTFEx(IMIInstPtr _app);
        
        ~IMILoaderGLTFEx();
        
        static IMISkinNodePtr loadFromFile(IMIInstPtr _app,cptr8 _filename);
        
    protected:
        static IMISkinNodePtr building(IMIInstPtr _app, tinygltf::Model* _model, cptr8 _path);
        
        static s32 getSkinIndexForMeshId(IMIInstPtr _app, tinygltf::Model* _model, s32 _meshId);
        
        static void genNode(IMIInstPtr _app, tinygltf::Model* _model, s32 _nodeid, cptr8 _path);
        
        //生成rmesh
        static IMIModelPtr _genModel(IMIInstPtr _app,
                                    tinygltf::Model* _model,
                                    s32 _index,
                                    cptr8 _path);
        
        //生成皮肤
        static IMISkeletonPtr _genSkin(IMIInstPtr _app,
                                   tinygltf::Model* _model,
                                   s32 _index,
                                   cptr8 _path);
        
        static IMIBonePtr _genBone(IMIInstPtr _app,
                                    tinygltf::Model* _model,
                                    tinygltf::Skin* _skinData,
                                    s32 _nodeIndex,
                                    IMIBonePtr _parent,
                                    IMISkeletonPtr _ske);
        
        static IMIAnimateSkinPtr _genAnimate(IMIInstPtr _app,
                                            tinygltf::Model* _model,
                                            s32 _aniIndex,
                                            cptr8 _path);

        //生成材质
        static IMIMtlCorePtr _genMtl(IMIInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path);
        static IMISurfacePtr _genSurface(IMIInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path);
        
        static IMITexturePtr _genTexture(IMIInstPtr _app,
                                        tinygltf::Model* _model,
                                        s32 _index,
                                        cptr8 _path);
        
        static IMIMesh3dPtr _genMeshPri(IMIInstPtr _app,
                                       tinygltf::Model* _model,
                                       tinygltf::Primitive* _prim,
                                       cptr8 _path);
        
        static s8* _getAccDataPointer(tinygltf::Model* _model,
                                      tinygltf::Accessor* acc,
                                      cptr8 _path);
        
        static s32 _getAccLen(tinygltf::Accessor* acc);
    };
    

}//!namespace imi




#endif //IMI_LOADER_GLTF_EX_H

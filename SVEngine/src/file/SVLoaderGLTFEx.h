//
// SVLoaderGLTFEX.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_LOADER_GLTF_EX_H
#define SV_LOADER_GLTF_EX_H

#include "SVFileLoader.h"
#include "../base/SVPreDeclare.h"
#include "../rendercore/SVRenderDeclare.h"
#include "../node/SVNodeDeclare.h"
#include "../base/SVMap.h"
#include "../base/SVArray.h"
#include "../base/svstr.h"
#include "../base/SVMat4.h"
#include "../base/SVDataSwap.h"

#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_EXTERNAL_IMAGE
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include "../third/gltf/tiny_gltf.h"

namespace sv {
    
    typedef struct SVGLTF {
//        std::vec
    }SVGLTF;
    
    class SVLoaderGLTFEx : public SVGBaseEx{
    public:
        SVLoaderGLTFEx(SVInstPtr _app);
        
        ~SVLoaderGLTFEx();
        
        static SVSkinNodePtr loadFromFile(SVInstPtr _app,cptr8 _filename);
        
    protected:
        static SVSkinNodePtr building(SVInstPtr _app, tinygltf::Model* _model, cptr8 _path);
        
        static s32 getSkinIndexForMeshId(SVInstPtr _app, tinygltf::Model* _model, s32 _meshId);
        
        static void genNode(SVInstPtr _app, tinygltf::Model* _model, s32 _nodeid, cptr8 _path);
        
        //生成rmesh
        static SVModelPtr _genModel(SVInstPtr _app,
                                    tinygltf::Model* _model,
                                    s32 _index,
                                    cptr8 _path);
        
        //生成皮肤
        static SVSkeletonPtr _genSkin(SVInstPtr _app,
                                   tinygltf::Model* _model,
                                   s32 _index,
                                   cptr8 _path);
        
        static SVBonePtr _genBone(SVInstPtr _app,
                                    tinygltf::Model* _model,
                                    tinygltf::Skin* _skinData,
                                    s32 _nodeIndex,
                                    SVBonePtr _parent,
                                    SVSkeletonPtr _ske);
        
        static SVAnimateSkinPtr _genAnimate(SVInstPtr _app,
                                            tinygltf::Model* _model,
                                            s32 _aniIndex,
                                            cptr8 _path);

        //生成材质
        static SVMtlCorePtr _genMtl(SVInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path);
        static SVSurfacePtr _genSurface(SVInstPtr _app, tinygltf::Model* _model, s32 _index, cptr8 _path);
        
        static SVTexturePtr _genTexture(SVInstPtr _app,
                                        tinygltf::Model* _model,
                                        s32 _index,
                                        cptr8 _path);
        
        static SVMesh3dPtr _genMeshPri(SVInstPtr _app,
                                       tinygltf::Model* _model,
                                       tinygltf::Primitive* _prim,
                                       cptr8 _path);
        
        static s8* _getAccDataPointer(tinygltf::Model* _model,
                                      tinygltf::Accessor* acc,
                                      cptr8 _path);
        
        static s32 _getAccLen(tinygltf::Accessor* acc);
    };
    

}//!namespace sv




#endif //SV_LOADER_GLTF_EX_H

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
    
    class SVLoaderGLTFEx : public SVGBaseEx{
    public:
        SVLoaderGLTFEx(SVInstPtr _app);
        
        ~SVLoaderGLTFEx();
        
        static bool loadFromFile(SVInstPtr _app,cptr8 _filename);
        
    protected:
        static void building(SVInstPtr _app,
                             tinygltf::Model* _model);
        
        static void genNode(SVInstPtr _app,
                            tinygltf::Model* _model,s32 _nodeid);
        
        //生成rmesh
        static SVModelPtr _genModel(SVInstPtr _app,
                                    tinygltf::Model* _model,
                                    s32 _index);
        
        //生成皮肤
        static SVModelPtr _genSkin(SVInstPtr _app,
                                   tinygltf::Model* _model,
                                   s32 _index);

        //生成材质
        static SVModelPtr _genMtl(SVInstPtr _app,
                                  tinygltf::Model* _model,
                                  s32 _index);
        
        static SVMesh3dPtr _buildMeshPri(SVInstPtr _app,
                                         tinygltf::Model* _model,
                                         tinygltf::Primitive* _prim);
        
        static SVMtlCorePtr _buildMtl(SVInstPtr _app,
                                      tinygltf::Model* _model,
                                      tinygltf::Primitive* _prim);
        
        static s8* _getAccDataPointer(tinygltf::Model* _model,
                                      tinygltf::Accessor* acc);
    };
    

}//!namespace sv




#endif //SV_LOADER_GLTF_EX_H

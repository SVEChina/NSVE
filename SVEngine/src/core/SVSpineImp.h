//
// SVSpineImp.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_SPINEOBJC_H
#define SV_SPINEOBJC_H

#include "../third/spine4/include/spine/Atlas.h"
#include "../base/SVPreDeclare.h"
#include "../mtl/SVMtlDeclare.h"

extern "C" {

    namespace sv{
    
        class SVSpineImp {
        public:
            SVSpineImp(SVInstPtr _inst);
            
            virtual ~SVSpineImp();
            
            SVTexturePtr loadTexture(const char* _path);
            
        protected:
            SVInstPtr m_inst;
        };
    
        //
        class SVSpinePageImp {
        public:
            SVSpinePageImp() {
                m_tex = nullptr;
            }
            
            virtual ~SVSpinePageImp() {
                m_tex = nullptr;
            }
            
            SVTexturePtr m_tex;
        };
    }

    void _spAtlasPage_createTexture (spAtlasPage* _page, const char* path);

    void _spAtlasPage_disposeTexture (spAtlasPage* _page);

    char* _spUtil_readFile (const char* path, int* length);

//    char *_spUtil_readFile(void *_app, const char *path, int *length);
//
//    void _spAtlasPage_createTexture(void *_app, spAtlasPage *self, const char *path, char enableMipMap);
//
//    void _spAtlasPage_disposeTexture(spAtlasPage *self);

}

#endif //SV_MASPINEOBJC_H

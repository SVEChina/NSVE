//
// IMISpineImp.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_SPINEOBJC_H
#define IMI_SPINEOBJC_H

#include "../third/spine4/include/spine/Atlas.h"
#include "../base/IMIPreDeclare.h"
#include "../mtl/IMIMtlDeclare.h"

extern "C" {

    namespace imi{
    
        //c++对象
        class IMISpineImp {
        public:
            IMISpineImp(IMIInstPtr _inst);
            
            virtual ~IMISpineImp();
            
            IMITexturePtr loadTexture(const char* _path);
            
        protected:
            IMIInstPtr m_inst;
        };
    
        //page实现
        class IMISpinePageImp {
        public:
            IMISpinePageImp() {
                m_tex = nullptr;
            }
            
            virtual ~IMISpinePageImp() {
                m_tex = nullptr;
            }
            
            IMITexturePtr m_tex;
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

#endif //IMI_MASPINEOBJC_H

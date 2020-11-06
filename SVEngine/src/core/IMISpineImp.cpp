//
// IMISpineImp.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMISpineImp.h"
#include "../../../base/IMIDataChunk.h"
#include "../../../mtl/IMITexture.h"
#include "../../../mtl/IMITexMgr.h"
#include "../../../file/IMIFileMgr.h"
#include "../../../app/IMIInst.h"
#include "IMISpine.h"

using namespace imi;

IMISpineImp::IMISpineImp(IMIInstPtr _inst)
:m_inst(_inst){
}

IMISpineImp::~IMISpineImp(){
    m_inst = nullptr;
}

IMITexturePtr IMISpineImp::loadTexture(const char* _path) {
    return m_inst->getTexMgr()->getTexture(_path,true);
}

//const spAtlas* atlas;
//const char* name;
//spAtlasFormat format;
//spAtlasFilter minFilter, magFilter;
//spAtlasWrap uWrap, vWrap;
//void* rendererObject;
//int width, height;
//spAtlasPage* next;

//创建纹理
void _spAtlasPage_createTexture (spAtlasPage* _page, const char* path) {
    //
    spAtlas* t_atlas = (spAtlas*)(_page->atlas);
    IMISpineImp* t_imp = (IMISpineImp*)(t_atlas->rendererObject);
    //
    IMISpinePageImp* t_page_imp = new IMISpinePageImp();
    t_page_imp->m_tex = t_imp->loadTexture(path);
    //设置环绕等相关属性
    //t_page_imp->m_tex
    //
    _page->rendererObject = t_page_imp;
}

//销毁纹理
void _spAtlasPage_disposeTexture (spAtlasPage* _page) {
    IMISpinePageImp* t_imp = (IMISpinePageImp*)(_page->rendererObject);
    if (t_imp){
        delete t_imp;
    }
    _page->rendererObject = nullptr;
}

//获取数据内容接口
char* _spUtil_readFile (const char* path, int* length) {
    //返回文件内容
    IMIDataChunk tChunk;
    bool t_ret = IMIFileMgr::s_loadFileContent(&tChunk, path);
    if(t_ret) {
        (*length) = int(tChunk.getRealSize());
        char *t_data = (char *) malloc(tChunk.getRealSize() );
        memcpy(t_data, tChunk.getPointer(), tChunk.getRealSize() );
        return t_data;
    }
    return nullptr;
}




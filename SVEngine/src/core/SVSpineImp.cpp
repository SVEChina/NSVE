//
// SVSpineImp.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVSpineImp.h"
#include "../../../base/SVDataChunk.h"
#include "../../../mtl/SVTexture.h"
#include "../../../mtl/SVTexMgr.h"
#include "../../../file/SVFileMgr.h"
#include "../../../app/SVInst.h"
#include "SVSpine.h"

using namespace sv;

SVSpineImp::SVSpineImp(SVInstPtr _inst)
:m_inst(_inst){
}

SVSpineImp::~SVSpineImp(){
    m_inst = nullptr;
}

SVTexturePtr SVSpineImp::loadTexture(const char* _path) {
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
    SVSpineImp* t_imp = (SVSpineImp*)(t_atlas->rendererObject);
    //
    SVSpinePageImp* t_page_imp = new SVSpinePageImp();
    t_page_imp->m_tex = t_imp->loadTexture(path);
    //设置环绕等相关属性
    //t_page_imp->m_tex
    //
    _page->rendererObject = t_page_imp;
}

//销毁纹理
void _spAtlasPage_disposeTexture (spAtlasPage* _page) {
    SVSpinePageImp* t_imp = (SVSpinePageImp*)(_page->rendererObject);
    if (t_imp){
        delete t_imp;
    }
    _page->rendererObject = nullptr;
}

//获取数据内容接口
char* _spUtil_readFile (const char* path, int* length) {
    //返回文件内容
    SVDataChunk tChunk;
    bool t_ret = SVFileMgr::s_loadFileContent(&tChunk, path);
    if(t_ret) {
        (*length) = int(tChunk.getRealSize());
        char *t_data = (char *) malloc(tChunk.getRealSize() );
        memcpy(t_data, tChunk.getPointer(), tChunk.getRealSize() );
        return t_data;
    }
    return nullptr;
}




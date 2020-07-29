//
// SVTexMgr.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVTexMgr.h"
#include "SVTexturePList.h"
#include "SVTexture.h"
#include "../app/SVDispatch.h"
#include "../file/SVLoaderPng.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataChunk.h"
#include "../app/SVInst.h"
#include "../core/SVImage.h"
#include "../rendercore/SVRenderMgr.h"
#include "../work/SVThreadPool.h"

using namespace sv;

SVTexMgr::SVTexMgr(SVInstPtr _app)
:SVGBaseEx(_app) {
    mAsync = false;
    m_sve_tex = nullptr;
    m_texLock = MakeSharedPtr<SVLock>();
    //主纹理
    m_pMainTex = nullptr;
    //阴影纹理
    m_pShadowTex = nullptr;
    //G-BUFFER
    m_pMainPosTex = nullptr;
    m_pMainNorTex = nullptr;
    m_pMainColoreTex = nullptr;
    //后处理纹理
    m_pPostTex0 = nullptr;
    m_pPostTex1 = nullptr;
    m_pPostTex2 = nullptr;
    m_pPostTex3 = nullptr;
}

SVTexMgr::~SVTexMgr() {
    m_texLock = nullptr;
    m_sve_tex = nullptr;
}

void SVTexMgr::init() {
    m_sve_tex = getTexture("svres/sve.png",true);
}

void SVTexMgr::destroy() {
    m_ftex_pool.clear();
    m_sve_tex = nullptr;
}

SVTexturePtr SVTexMgr::getSVETexture(){
    return m_sve_tex;
}

void SVTexMgr::update(f32 _dt){
    //
    _removeUnuseTexture();
}

void SVTexMgr::clear() {
    //_removeUnuseTexture();
}

//
SVTexturePtr SVTexMgr::getTexture(cptr8 _name,bool _sync) {
    FTEXPOOL::iterator it = m_ftex_pool.find(_name);
    if( it!=m_ftex_pool.end() ) {
        return it->second;
    }
    return _createTexture(_name, _sync, true);
}

SVTexturePtr SVTexMgr::_createTexture(cptr8 _name, bool _sync, bool _enableMipMap) {
    //返回空壳纹理
    SVTexturePtr tTexture = nullptr;
    m_texLock->lock();
    SVImagePtr t_img = MakeSharedPtr<SVImage>(mApp);
    if (_sync) {
        if( t_img->load(_name) ) {
            tTexture = t_img->toTexture();
            SVDispatch::dispatchTextureCreate(mApp, tTexture);
        }
    } else {
        //异步创建需要等
        if( t_img->load(_name) ) {
            tTexture = t_img->toTexture();
        }
    }
    if(tTexture) {
        m_ftex_pool.insert(std::make_pair(_name, tTexture));
    }
    t_img = nullptr;
    m_texLock->unlock();
    return tTexture;
}

SVTexturePtr SVTexMgr::getTexture(SVTEXINID _texname) {
    //获取内置纹理
//    if(_texname>=E_TEX_MAIN && _texname<E_TEX_END){
//        return m_intex_pool[_texname];
//    }
    return nullptr;
}

SVTexturePtr SVTexMgr::createTexture(SVTEXINID _texname,SVTextureDsp _param) {
    if(_texname>=E_TEX_MAIN && _texname<E_TEX_END){
        SVTexturePtr tTexture = MakeSharedPtr<SVTexture>(mApp);
        tTexture->init(_param);
        //m_intex_pool[_texname] = tTexture;
    }
    return nullptr;
}

//创建外部纹理
SVTexturePtr SVTexMgr::createTexture(SVTextureDsp _param) {
    return nullptr;
}

SVTexturePtr SVTexMgr::createTexture(SVTextureDsp _param,SVDataSwapPtr _data) {
    return nullptr;
}

//这里才是真正干掉纹理的地方
void SVTexMgr::_removeUnuseTexture() {
    m_texLock->lock();
//    TEXPOOL::Iterator it = m_filetex_pool.begin();
//    while ( it!=m_filetex_pool.end() ) {
//        if (it->data && it->data.use_count() == 2) {
//            mTexpool.remove(it);    //移除是不是会导致迭代器失效?
//            it = mTexpool.begin();  //重置迭代器
//        } else {
//            it++;
//        }
//    }
    m_texLock->unlock();
}


//SVTexturePtr SVTexMgr::createUnctrlTextureWithTexID(s32 _texId, s32 _width, s32 _height, s32 _informat, s32 _dataformat, bool _enableMipMap){
////    SVTexturePtr tTexture = MakeSharedPtr<SVTextureInputTexID>(mApp, _texId);
////    tTexture->init("", GL_TEXTURE_2D, _width, _height, _informat, _dataformat, _enableMipMap);
////    //mApp->getRenderMgr()->pushRCmdCreate(tTexture);
////    return tTexture;
//    return nullptr;
//}
//
//SVTexturePtr SVTexMgr::createUnctrlTextureWithData(s32 _width, s32 _height, s32 _informat, s32 _dataformat, void* _data, bool _enableMipMap){
//    SVTexturePtr tTexture = MakeSharedPtr<SVTexture>(mApp);
//    SVString t_name = SVString::format("%d", tTexture->getUID());
//    t_name = SVString("unctrltexdata") + SVString("_") + t_name;
//    tTexture->init(t_name.c_str(), GL_TEXTURE_2D, _width, _height, _informat, _dataformat, _enableMipMap);
//    s32 t_len = 0;//应该根据格式算的
//    if(_informat == GL_RGB){
//        t_len = _width*_height*3;
//    }else if(_informat == GL_RGBA){
//        t_len = _width*_height*4;
//    }else if(_informat == GL_LUMINANCE){
//        t_len = _width*_height;
//    }else if(_informat == GL_LUMINANCE_ALPHA){
//        t_len = _width*_height*2;
//    }
//    tTexture->setTexData(_data, t_len);
//    //mApp->getRenderMgr()->pushRCmdCreate(tTexture);
//    mTexpool.append(t_name, tTexture);
//    return tTexture;
//}
//
//SVTexturePtr SVTexMgr::createUnctrlTexture(s32 _w, s32 _h, s32 _informat,  s32 _dataformat, bool _enableMipMap){
//    SVTexturePtr tTexture = MakeSharedPtr<SVTexture>(mApp);
//    SVString t_name = SVString::format("%d", tTexture->getUID());
//    t_name = SVString("unctrltex") + SVString("_") + t_name;
//    tTexture->init(t_name.c_str(), GL_TEXTURE_2D, _w, _h, _informat, _dataformat, _enableMipMap);
//    //mApp->getRenderMgr()->pushRCmdCreate(tTexture);
//    mTexpool.append(t_name, tTexture);
//    return tTexture;
//}

//SVTexturePtr SVTexMgr::_createTextureSet(cptr8 _name, bool _sync, bool _enableMipMap) {
//    //返回空壳纹理
//    SVTexturePtr tTexture = nullptr;
//    m_texLock->lock();
//    SVImagePtr t_img = MakeSharedPtr<SVImage>(mApp);
//    if (_sync) {
//        if( t_img->load(_name) ) {
//            tTexture = t_img->toTexture();
//        }
//    } else {
//        if( t_img->load(_name) ) {
//            tTexture = t_img->toTexture();
//        }
//    }
//    if(tTexture) {
//        m_ftex_pool.insert(std::make_pair(_name, tTexture));
//    }
//    t_img = nullptr;
//    m_texLock->unlock();
//    return tTexture;
//}

bool SVTexMgr::hasTexture(cptr8 _name) {
    FTEXPOOL::iterator it = m_ftex_pool.find(_name);
    if( it!=m_ftex_pool.end() ) {
        return true;
    }
    //内置纹理中寻找
    return false;
}

//加载纹理
SVTexturePtr SVTexMgr::loadImgPList(cptr8 _plistname,cptr8 _path) {
    return nullptr;
}

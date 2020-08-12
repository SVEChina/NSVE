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
    m_intex_pool.resize(E_TEX_END);
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
//    //主纹理
//    m_main_tex = nullptr;
//    //阴影纹理
//    m_shadow_tex = nullptr;
//    //G-BUFFER
//    m_gbuf_postex = nullptr;
//    m_gbuf_nortex = nullptr;
//    m_gbuf_colortex = nullptr;
//    //后处理纹理
//    m_post_tex0 = nullptr;
//    m_post_tex1 = nullptr;
//    m_post_tex2 = nullptr;
//    m_post_tex3 = nullptr;
}

SVTexMgr::~SVTexMgr() {
    m_texLock = nullptr;
    m_sve_tex = nullptr;
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
}

void SVTexMgr::init() {
    m_sve_tex = getTexture("svres/sve.png",true);
}

void SVTexMgr::destroy() {
    m_ftex_pool.clear();
    m_sve_tex = nullptr;
}

void SVTexMgr::update(f32 _dt){
    //_removeUnuseTexture();
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

SVTexturePtr SVTexMgr::getInTexture(SVINTEX _texid) {
    //获取内置纹理
    if(_texid>=E_TEX_MAIN && _texid<E_TEX_END){
        if(m_intex_pool[_texid] ) {
            return m_intex_pool[_texid];
        }
    }
    return nullptr;
}

SVTexturePtr SVTexMgr::createInTexture(SVINTEX _texname,SVTextureDsp _dsp) {
    if(_texname>=E_TEX_MAIN && _texname<E_TEX_END){
        if(m_intex_pool[_texname]) {
            return m_intex_pool[_texname];
        }
        m_intex_pool[_texname] = MakeSharedPtr<SVTexture>(mApp);
        m_intex_pool[_texname] ->init(_dsp);
        SVDispatch::dispatchTextureCreate(mApp, m_intex_pool[_texname]);
        return m_intex_pool[_texname];
    }
    return nullptr;
}

bool SVTexMgr::hasInTexture(SVINTEX _texid) {
    if(_texid>=E_TEX_MAIN && _texid<E_TEX_END){
        if(m_intex_pool[_texid] ) {
            return true;
        }
    }
    return false;
}

SVTexturePtr SVTexMgr::getSVETexture(){
    return m_sve_tex;
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

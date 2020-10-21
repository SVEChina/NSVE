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
}

SVTexMgr::~SVTexMgr() {
    m_texLock = nullptr;
    m_sve_tex = nullptr;
}

void SVTexMgr::init() {
    //内置纹理
    m_intex_pool.resize(E_TEX_END);
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
}

void SVTexMgr::destroy() {
    //
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
    //
    m_ftex_pool.clear();
    m_sve_tex = nullptr;
}

void SVTexMgr::loadDefault() {
    m_sve_tex = getTexture("res/sve.png",true);
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
            tTexture->dispatch();
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

SVTexturePtr SVTexMgr::createInTexture(SV_TEXIN _texname,SVTextureDsp& _dsp) {
    if(_texname>E_TEX_BEGIN && _texname<E_TEX_END){
        if(m_intex_pool[_texname]) {
            return m_intex_pool[_texname];
        }
        m_intex_pool[_texname] = MakeSharedPtr<SVTexture>(mApp);
        m_intex_pool[_texname] ->init(_dsp);
        m_intex_pool[_texname]->dispatch();
        return m_intex_pool[_texname];
    }
    return nullptr;
}

bool SVTexMgr::hasInTexture(SV_TEXIN _texid) {
    if(_texid>E_TEX_BEGIN && _texid<E_TEX_END){
        if(m_intex_pool[_texid] ) {
            return true;
        }
    }
    return false;
}

SVTexturePtr SVTexMgr::getInTexture(SV_TEXIN _texid) {
    if(_texid>E_TEX_BEGIN && _texid<E_TEX_END) {
        return m_intex_pool[_texid];
    }
    return nullptr;
}

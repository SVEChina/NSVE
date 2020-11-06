//
// IMITexMgr.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMITexMgr.h"
#include "IMITexturePList.h"
#include "IMITexture.h"
#include "../app/IMIDispatch.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../app/IMIInst.h"
#include "../core/IMIImage.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../work/IMIThreadPool.h"

using namespace imi;

IMITexMgr::IMITexMgr(IMIInstPtr _app)
:IMIGBaseEx(_app) {
    mAsync = false;
    m_sve_tex = nullptr;
    m_texLock = MakeSharedPtr<IMILock>();
}

IMITexMgr::~IMITexMgr() {
    m_texLock = nullptr;
    m_sve_tex = nullptr;
}

void IMITexMgr::init() {
    //内置纹理
    m_intex_pool.resize(E_TEX_END);
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
}

void IMITexMgr::destroy() {
    //
    for(s32 i=0;i<E_TEX_END;i++) {
        m_intex_pool[i] = nullptr;
    }
    //
    m_ftex_pool.clear();
    m_sve_tex = nullptr;
}

void IMITexMgr::loadDefault() {
    m_sve_tex = getTexture("res/sve.png",true);
}

void IMITexMgr::clear() {
    //_removeUnuseTexture();
}

//
IMITexturePtr IMITexMgr::getTexture(cptr8 _name,bool _sync) {
    FTEXPOOL::iterator it = m_ftex_pool.find(_name);
    if( it!=m_ftex_pool.end() ) {
        return it->second;
    }
    return _createTexture(_name, _sync, true);
}

IMITexturePtr IMITexMgr::_createTexture(cptr8 _name, bool _sync, bool _enableMipMap) {
    //返回空壳纹理
    IMITexturePtr tTexture = nullptr;
    m_texLock->lock();
    IMIImagePtr t_img = MakeSharedPtr<IMIImage>(mApp);
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

IMITexturePtr IMITexMgr::getIMITexture(){
    return m_sve_tex;
}

//这里才是真正干掉纹理的地方
void IMITexMgr::_removeUnuseTexture() {
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

bool IMITexMgr::hasTexture(cptr8 _name) {
    FTEXPOOL::iterator it = m_ftex_pool.find(_name);
    if( it!=m_ftex_pool.end() ) {
        return true;
    }
    //内置纹理中寻找
    return false;
}

IMITexturePtr IMITexMgr::createInTexture(IMI_TEXIN _texname,IMITextureDsp& _dsp) {
    if(_texname>E_TEX_BEGIN && _texname<E_TEX_END){
        if(m_intex_pool[_texname]) {
            return m_intex_pool[_texname];
        }
        m_intex_pool[_texname] = MakeSharedPtr<IMITexture>(mApp);
        m_intex_pool[_texname] ->init(_dsp);
        m_intex_pool[_texname]->dispatch();
        return m_intex_pool[_texname];
    }
    return nullptr;
}

bool IMITexMgr::hasInTexture(IMI_TEXIN _texid) {
    if(_texid>E_TEX_BEGIN && _texid<E_TEX_END){
        if(m_intex_pool[_texid] ) {
            return true;
        }
    }
    return false;
}

IMITexturePtr IMITexMgr::getInTexture(IMI_TEXIN _texid) {
    if(_texid>E_TEX_BEGIN && _texid<E_TEX_END) {
        return m_intex_pool[_texid];
    }
    return nullptr;
}

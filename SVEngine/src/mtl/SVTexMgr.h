//
// SVTexMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TEXMGR_H
#define SV_TEXMGR_H

#include "../base/SVGBase.h"
#include "../mtl/SVMtlDeclare.h"
#include "../work/SVWorkDeclare.h"
#include "SVTexture.h"
#include <vector>
#include <map>

namespace sv {

    //
    class SVTexMgr : public SVGBaseEx {
    public:
        SVTexMgr(SVInstPtr _app);
        
        ~SVTexMgr();
        
        void init();
        //
        void destroy();
        //
        void loadDefault();
        //从文件加载纹理
        SVTexturePtr getTexture(cptr8 _name,bool _sync = true);
        //
        bool hasTexture(cptr8 _name);
        //
        void clear();
        //
        SVTexturePtr getSVETexture();
    protected:
        SVTexturePtr _createTexture(cptr8 _name, bool _sync = true, bool _enableMipMap = false);
        
        void _removeUnuseTexture();
        
        //文件纹理池
        typedef std::map<SVString, SVTexturePtr> FTEXPOOL;
        FTEXPOOL m_ftex_pool;
        //
        SVLockPtr m_texLock;
        //
        SVTexturePtr m_sve_tex;
        //
        bool mAsync;
    };

    
}//!namespace sv



#endif //SV_TEXMGR_H

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
        
        void destroy();
        
        void update(f32 _dt);
        
        //从文件加载纹理
        SVTexturePtr getTexture(cptr8 _name,bool _sync = true);
        
        bool hasTexture(cptr8 _name);
        
        //获取内部纹理
        SVTexturePtr getInTexture(SVINTEX _texname);
        
        //创建内部纹理
        SVTexturePtr createInTexture(SVINTEX _texname,SVTextureDsp _param);
        
        bool hasInTexture(SVINTEX _texid);
        
        void clear();
        
        //
        SVTexturePtr getSVETexture();
        
        //
        SVTexturePtr loadImgPList(cptr8 _plistname, cptr8 _path);
        
    protected:
        
        SVTexturePtr _createTexture(cptr8 _name, bool _sync = true, bool _enableMipMap = false);
        
        void _removeUnuseTexture();
        
        //文件纹理池
        typedef std::map<SVString, SVTexturePtr> FTEXPOOL;
        FTEXPOOL m_ftex_pool;
        //内置纹理池
        typedef std::vector<SVTexturePtr> INTEXPOOL;
        INTEXPOOL m_intex_pool;
        //
        SVLockPtr m_texLock;
        //
        SVTexturePtr m_sve_tex;
        //
        bool mAsync;
    };

    
}//!namespace sv



#endif //SV_TEXMGR_H

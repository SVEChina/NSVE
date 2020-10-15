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
        
        /*文件纹理*/
        //获取文件纹理
        SVTexturePtr getTexture(cptr8 _name,bool _sync = true);
        //文件纹理是否存在
        bool hasTexture(cptr8 _name);
        //清理文件纹理
        void clear();
        
        /*标准纹理*/
        SVTexturePtr getSVETexture();
        
        /*内部纹理*/
        //创建内置纹理
        SVTexturePtr createInTexture(SV_TEXIN _texname,SVTextureDsp _dsp);
        //内置纹理是否存在
        bool hasInTexture(SV_TEXIN _texid);
        //获取内置纹理
        SVTexturePtr getInTexture(SV_TEXIN _texid);
        
    protected:
        SVTexturePtr _createTexture(cptr8 _name, bool _sync = true, bool _enableMipMap = false);
        //
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

//
// IMITexMgr.h
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#ifndef IMI_TEXMGR_H
#define IMI_TEXMGR_H

#include "../base/IMIGBase.h"
#include "../mtl/IMIMtlDeclare.h"
#include "../work/IMIWorkDeclare.h"
#include "IMITexture.h"
#include <vector>
#include <map>

namespace imi {

    //
    class IMITexMgr : public IMIGBaseEx {
    public:
        IMITexMgr(IMIInstPtr _app);
        
        ~IMITexMgr();
        
        void init();
        //
        void destroy();
        //
        void loadDefault();
        
        /*文件纹理*/
        //获取文件纹理
        IMITexturePtr getTexture(cptr8 _name,bool _sync = true);
        //文件纹理是否存在
        bool hasTexture(cptr8 _name);
        //清理文件纹理
        void clear();
        
        /*标准纹理*/
        IMITexturePtr getIMITexture();
        
        /*内部纹理*/
        //创建内置纹理
        IMITexturePtr createInTexture(IMI_TEXIN _texname,IMITextureDsp& _dsp);
        //内置纹理是否存在
        bool hasInTexture(IMI_TEXIN _texid);
        //获取内置纹理
        IMITexturePtr getInTexture(IMI_TEXIN _texid);
        
    protected:
        IMITexturePtr _createTexture(cptr8 _name, bool _sync = true, bool _enableMipMap = false);
        //
        void _removeUnuseTexture();
        //文件纹理池
        typedef std::map<IMIString, IMITexturePtr> FTEXPOOL;
        FTEXPOOL m_ftex_pool;
        //内置纹理池
        typedef std::vector<IMITexturePtr> INTEXPOOL;
        INTEXPOOL m_intex_pool;
        //
        IMILockPtr m_texLock;
        //
        IMITexturePtr m_sve_tex;
        //
        bool mAsync;
    };

    
}//!namespace imi



#endif //IMI_TEXMGR_H

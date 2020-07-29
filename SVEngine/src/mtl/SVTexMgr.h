//
// SVTexMgr.h
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#ifndef SV_TEXMGR_H
#define SV_TEXMGR_H

#include "../base/SVGBase.h"
#include "SVTexture.h"
#include "../base/SVMap.h"
#include "../mtl/SVMtlDeclare.h"
#include <vector>
#include <list>
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
        
        //创建内部纹理
        SVTexturePtr getTexture(SVTEXINID _texname);
        
        //创建内部纹理
        SVTexturePtr createTexture(SVTEXINID _texname,SVTextureDsp _param);
        
        //创建外部纹理
        SVTexturePtr createTexture(SVTextureDsp _param);
        
        //
        SVTexturePtr createTexture(SVTextureDsp _param,SVDataSwapPtr _data);
        
        bool hasTexture(cptr8 _name);
        
        void clear();
        
        SVTexturePtr getSVETexture();
        
        SVTexturePtr loadImgPList(cptr8 _plistname, cptr8 _path);
        
    protected:
        
        SVTexturePtr _createTexture(cptr8 _name, bool _sync = true, bool _enableMipMap = false);
        
        void _removeUnuseTexture();
        
        //文件纹理池
        typedef std::map<SVString, SVTexturePtr> FTEXPOOL;
        FTEXPOOL m_ftex_pool;
        //
        SVLockPtr m_texLock;
        SVTexturePtr m_sve_tex;
        bool mAsync;
        //
    public:
        //所有内置纹理都在这里
        //主纹理
        SVTexturePtr m_pMainTex;
        //阴影纹理
        SVTexturePtr m_pShadowTex;
        //G-BUFFER
        SVTexturePtr m_pMainPosTex;
        SVTexturePtr m_pMainNorTex;
        SVTexturePtr m_pMainColoreTex;
        //后处理纹理
        SVTexturePtr m_pPostTex0;
        SVTexturePtr m_pPostTex1;
        SVTexturePtr m_pPostTex2;
        SVTexturePtr m_pPostTex3;
    };

    
}//!namespace sv



#endif //SV_TEXMGR_H

//
// SVMtlLib.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMtlLib.h"
#include "SVMtlGLTF.h"

using namespace sv;

SVMtlCorePtr SVMtlLib::m_pSkinMtl = nullptr;

void SVMtlLib::clear() {
    m_pSkinMtl = nullptr;
}

SVMtlCorePtr SVMtlLib::getSkinMtl(SVInstPtr _app) {
    if(!m_pSkinMtl) {
         m_pSkinMtl = MakeSharedPtr<SVMtlGLTF>(_app);
    }
    //
    FMat4 tMat_rotx;
    tMat_rotx.setIdentity();
    tMat_rotx.setRotateX(45.0f);

    FMat4 tMat_roty;
    tMat_roty.setIdentity();
    tMat_roty.setRotateY(45.0f);

    FMat4 tMat_sc;
    tMat_sc.setIdentity();
    tMat_sc.setScale(FVec3(200.0f,200.0f,200.0f));
    //
    FMat4 tMat = tMat_sc * tMat_roty * tMat_rotx;
    m_pSkinMtl->setModelMatrix(tMat.get());
    m_pSkinMtl->setBlendEnable(false);
    m_pSkinMtl->setDepthEnable(true);
    m_pSkinMtl->update(0.03f);
    //
    return m_pSkinMtl;
}

SVMtlCorePtr SVMtlLib::get3DNorMtl(SVInstPtr _app) {
    SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlGLTF>(_app);
    return t_mtl;
}

//材质名称和shader名称有个映射关系
SVString SVMtlLib::mapName(cptr8 _name) {
    return "";
}

SVMtlCorePtr SVMtlLib::genMtl(SVInstPtr _app,cptr8 _name) {
    SVString t_mtlname = _name;
    SVString t_shadername = mapName(_name);
    SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(_app,t_shadername.c_str());
    if(t_mtlname == "SVMtl2D") {
        t_mtl->setParam("u_alpha",0.0f);
    }
    //根据shader不同，生成不同的tech;
    
    
    //
    return t_mtl;
}

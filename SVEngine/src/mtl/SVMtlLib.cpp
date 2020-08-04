//
// SVMtlLib.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVMtlLib.h"
#include "SVMtlCore.h"
#include "SVMtlGLTF.h"
#include "../app/SVInst.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataChunk.h"

using namespace sv;

SVMtlLib::SVMtlLib(SVInstPtr _app)
:SVGBaseEx(_app){
}

SVMtlLib::~SVMtlLib() {
}

void SVMtlLib::init() {
    createMtl("screen.mtl");
    createMtl("sprite.mtl");
}

void SVMtlLib::destroy() {
}

//加载材质库
void SVMtlLib::loadMtlPack(cptr8 _pack) {
}

void SVMtlLib::clear() {
    //    //运行时的材质库
    //   typedef std::vector<SVMtlCorePtr> MTLPOOLRUN;
    //   MTLPOOL m_mtlPool_run;
    //
    //   //空闲的材质
    //   typedef std::vector<s32> EMPTYMTLPOOL;
    //   EMPTYMTLPOOL m_empty_mtl_ool;
    MTLPOOL::iterator it = m_mtlPool.begin();
    while ( it!=m_mtlPool.end() ) {
        it++;
    }
}

SVMtlCorePtr SVMtlLib::getMtl(s32 _mtlID) {
//    if(m_mtlpool_run.size()>_mtlID && m_mtlpool_run[_mtlID]) {
//        return m_mtlpool_run[_mtlID];
//    }
//    return nullptr;
    return nullptr;
}

SVMtlCorePtr SVMtlLib::getMtl(cptr8 _mtlname) {
    //本身找
    MTLPOOL::iterator it = m_mtlPool.find(_mtlname);
    if(it!=m_mtlPool.end()) {
        return it->second;
    }
    return nullptr;
}

SVMtlCorePtr SVMtlLib::createMtl(cptr8 _mtlname) {
    SVDataChunk t_data;
    bool t_ret = mApp->m_pFileMgr->loadFileContent(&t_data, _mtlname);
    if(!t_ret) {
        return nullptr;
    }
    //解析json文件
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse(t_data.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d - %s\n", code,_mtlname);
        return nullptr;
    }
    SVString t_version = "1.0";
    if (doc.HasMember("version")) {
        t_version = doc["version"].GetString();
    }
    if(t_version == "1.0") {
        SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(mApp);
        t_mtl->fromJSON1(doc);
        //
        m_mtlPool.insert(std::make_pair(t_mtl->m_mtl_name, t_mtl));
        return t_mtl;
    }
    return nullptr;
}

bool SVMtlLib::parseMtl1(SVMtlCorePtr _mtl,RAPIDJSON_NAMESPACE::Document& _doc) {
    if(!_mtl)
        return false;
    return true;
}

//SVMtlCorePtr SVMtlLib::getSkinMtl(SVInstPtr _app) {
////    if(!m_pSkinMtl) {
////         m_pSkinMtl = MakeSharedPtr<SVMtlGLTF>(_app);
////    }
////    //
////    FMat4 tMat_rotx;
////    tMat_rotx.setIdentity();
////    tMat_rotx.setRotateX(45.0f);
////
////    FMat4 tMat_roty;
////    tMat_roty.setIdentity();
////    tMat_roty.setRotateY(45.0f);
////
////    FMat4 tMat_sc;
////    tMat_sc.setIdentity();
////    tMat_sc.setScale(FVec3(200.0f,200.0f,200.0f));
////    //
////    FMat4 tMat = tMat_sc * tMat_roty * tMat_rotx;
////    m_pSkinMtl->setModelMatrix(tMat.get());
////    m_pSkinMtl->setBlendEnable(false);
////    m_pSkinMtl->setDepthEnable(true);
////    m_pSkinMtl->update(0.03f);
////    //
////    return m_pSkinMtl;
//    return nullptr;
//}

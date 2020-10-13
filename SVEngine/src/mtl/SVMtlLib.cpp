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
#include "../event/SVEvent.h"

using namespace sv;

//材质包

SVMtlPack::SVMtlPack(SVInstPtr _app)
:SVGBaseEx(_app) {
}

SVMtlPack::~SVMtlPack() {
}

bool SVMtlPack::hasMtl(cptr8 _name) {
    return false;
}

//材质库

SVMtlLib::SVMtlLib(SVInstPtr _app)
:SVEventProc(_app){
}

SVMtlLib::~SVMtlLib() {
}

void SVMtlLib::init() {
    for(s32 i=0;i<m_pack_pool.size();i++) {
        m_pack_pool.clear();
    }
}

void SVMtlLib::destroy() {
    for(s32 i=0;i<m_pack_pool.size();i++) {
        m_pack_pool.clear();
    }
}

//
void SVMtlLib::procSysEvent(SVObjectPtr _caller,SVEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        //渲染器初始化
        SVMtlLibPtr t_sender = dynamic_pointer_cast<SVMtlLib>(_caller);
        if(t_sender) {
            t_sender->loadDefaultPack();
        }
    }
}

//加载默认的材质包
void SVMtlLib::loadDefaultPack() {
    loadMtlPack("base.pack");
}

//加载材质库
void SVMtlLib::loadMtlPack(cptr8 _pack) {
    //材质库其实可以异步加载，可以根据渲染引擎进行异步，加载
    SVDataChunk tDataStream;
    SV_LOG_ERROR("load mtl-pack begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, _pack);//"base.pack"
    if (!tflag) {
       SV_LOG_INFO("not find base.pack! please check pack!\n");
       return;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
       RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
       SV_LOG_ERROR("rapidjson error code:%d \n", code);
       return;
    }
    //包名
    if ( doc.HasMember("name") && doc["name"].IsString() ) {
        RAPIDJSON_NAMESPACE::Value &t_name = doc["name"];
        SVString t_packname = t_name.GetString();
    }
    //文件列表
    if ( doc.HasMember("files") && doc["files"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Value &t_mtlfiles = doc["files"];
        RAPIDJSON_NAMESPACE::Document::Array t_files = t_mtlfiles.GetArray();
        for(s32 i=0;i<t_files.Size();i++) {
            SVString t_filename = t_files[i].GetString();
            createMtl(t_filename.c_str());
        }
    }
    //
    SV_LOG_DEBUG("load mtl-pack end\n");
}

void SVMtlLib::clear() {
    MTLPOOL::iterator it = m_mtlPool.begin();
    while ( it!=m_mtlPool.end() ) {
        it++;
    }
}

SVMtlCorePtr SVMtlLib::getMtl(cptr8 _mtlname) {
    MTLPOOL::iterator it = m_mtlPool.find(_mtlname);
    if(it!=m_mtlPool.end()) {
        return it->second;
    }
    return nullptr;
}

SVMtlCorePtr SVMtlLib::createMtl(cptr8 _mtlname) {
    SVDataChunk t_data;
    bool t_ret = mApp->m_file_sys->loadFileContentStr(&t_data, _mtlname);   //解析JSON一定要用这个函数
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
    //获取材质名称
    SVString t_mtl_name = _mtlname;
    s32 t_pos = t_mtl_name.rfind('.');
    if(t_pos>0) {
        t_mtl_name = SVString::substr(t_mtl_name.c_str(), 0, t_pos);
    }
    t_pos = t_mtl_name.rfind('\\');
    if(t_pos>0) {
       t_mtl_name = SVString::substr(t_mtl_name.c_str(), t_pos+1);
    }
    t_pos = t_mtl_name.rfind('/');
    if(t_pos>0) {
       t_mtl_name = SVString::substr(t_mtl_name.c_str(), t_pos+1);
    }
    //
    MTLPOOL::iterator it = m_mtlPool.find(t_mtl_name);
    if( it == m_mtlPool.end() ) {
        if(t_version == "1.0") {
            SVMtlCorePtr t_mtl = MakeSharedPtr<SVMtlCore>(mApp);
            t_mtl->m_mtl_name = t_mtl_name;
            t_mtl->fromJSON1(doc);
            m_mtlPool.insert(std::make_pair(t_mtl_name, t_mtl));
            return t_mtl;
        }
    }
    return nullptr;
}

bool SVMtlLib::parseMtl1(SVMtlCorePtr _mtl,RAPIDJSON_NAMESPACE::Document& _doc) {
    if(!_mtl)
        return false;
    return true;
}

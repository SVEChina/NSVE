//
// IMIMtlLib.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIMtlLib.h"
#include "IMIMtlCore.h"
#include "IMIMtlGLTF.h"
#include "../app/IMIInst.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../event/IMIEvent.h"

using namespace imi;

//材质包

IMIMtlPack::IMIMtlPack(IMIInstPtr _app)
:IMIGBaseEx(_app) {
}

IMIMtlPack::~IMIMtlPack() {
}

bool IMIMtlPack::hasMtl(cptr8 _name) {
    return false;
}

//材质库

IMIMtlLib::IMIMtlLib(IMIInstPtr _app)
:IMIEventProc(_app){
}

IMIMtlLib::~IMIMtlLib() {
}

void IMIMtlLib::init() {
    for(s32 i=0;i<m_pack_pool.size();i++) {
        m_pack_pool.clear();
    }
}

void IMIMtlLib::destroy() {
    for(s32 i=0;i<m_pack_pool.size();i++) {
        m_pack_pool.clear();
    }
}

//
void IMIMtlLib::procSysEvent(IMIObjectPtr _caller,IMIEventPtr _event) {
    if(_event->eventType == EVN_T_SYS_INIT_RENDERER) {
        IMIMtlLibPtr t_sender = dynamic_pointer_cast<IMIMtlLib>(_caller);
        if(t_sender) {
            t_sender->loadDefaultPack();
        }
    }
}

//加载默认的材质包
void IMIMtlLib::loadDefaultPack() {
    loadMtlPack("sve-pack-base");
}

//加载材质库
void IMIMtlLib::loadMtlPack(cptr8 _pack) {
    //加载材质包，先做文件拼接
    IMIString pack_cfg = _pack;
    pack_cfg += "/info.json";
    //材质库其实可以异步加载，可以根据渲染引擎进行异步，加载
    IMIDataChunk tDataStream;
    IMI_LOG_ERROR("load mtl-pack begin\n");
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, pack_cfg);
    if (!tflag) {
       IMI_LOG_INFO("not find base.pack! please check pack!\n");
       return;
    }
    IMIString t_pack_fullname = mApp->m_file_sys->getFileFullName(pack_cfg);
    IMIString t_pack_path = mApp->m_file_sys->getPath(t_pack_fullname);
    mApp->m_file_sys->addRespath(t_pack_path.c_str());
    //
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse<0>(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
       RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
       IMI_LOG_ERROR("rapidjson error code:%d \n", code);
       return;
    }
    //包名
    if ( doc.HasMember("pack-name") && doc["pack-name"].IsString() ) {
        RAPIDJSON_NAMESPACE::Value &t_name = doc["pack-name"];
        IMIString t_packname = t_name.GetString();
    }
    //文件链接方式
    if ( doc.HasMember("pack-files") && doc["pack-files"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Value &t_mtlfiles = doc["pack-files"];
        RAPIDJSON_NAMESPACE::Document::Array t_files = t_mtlfiles.GetArray();
        for(s32 i=0;i<t_files.Size();i++) {
            IMIString t_filename = t_files[i].GetString();
            createMtlFromFile(t_filename.c_str());
        }
    }
    //直接打到包内的方式
    if ( doc.HasMember("pack-mtls") && doc["pack-mtls"].IsArray() ) {
        RAPIDJSON_NAMESPACE::Value &t_mtls = doc["pack-mtls"];
        RAPIDJSON_NAMESPACE::Document::Array t_mtl_array = t_mtls.GetArray();
        for(s32 i=0;i<t_mtl_array.Size();i++) {
            RAPIDJSON_NAMESPACE::Document::Object t_jsonstr = t_mtl_array[i].GetObject();
            IMIString t_name = t_jsonstr["name"].GetString();
            createMtlFromJson(t_mtl_array[i],t_name.c_str());
        }
    }
    //
    IMI_LOG_DEBUG("load mtl-pack end\n");
}

void IMIMtlLib::clear() {
    MTLPOOL::iterator it = m_mtlPool.begin();
    while ( it!=m_mtlPool.end() ) {
        it++;
    }
}

IMIMtlCorePtr IMIMtlLib::getMtl(cptr8 _mtlname) {
    MTLPOOL::iterator it = m_mtlPool.find(_mtlname);
    if(it!=m_mtlPool.end()) {
        return it->second;
    }
    return nullptr;
}

IMIMtlCorePtr IMIMtlLib::createMtlFromFile(cptr8 _fname) {
    IMIDataChunk t_data;
    bool t_ret = mApp->m_file_sys->loadFileContentStr(&t_data, _fname);   //解析JSON一定要用这个函数
    if(!t_ret) {
        return nullptr;
    }
    //解析json文件
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse(t_data.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d - %s\n", code,_fname);
        return nullptr;
    }
    return createMtlFromJson( doc, _fname);
}

IMIMtlCorePtr IMIMtlLib::createMtlFromJson(RAPIDJSON_NAMESPACE::Value& _obj,cptr8 _mtlname) {
    IMIString t_version = "1.0";
    if (_obj.HasMember("version")) {
        t_version = _obj["version"].GetString();
    }
    //获取材质名称
    IMIString t_mtl_name = _mtlname;
    s32 t_pos = t_mtl_name.rfind('.');
    if(t_pos>0) {
        t_mtl_name = IMIString::substr(t_mtl_name.c_str(), 0, t_pos);
    }
    t_pos = t_mtl_name.rfind('\\');
    if(t_pos>0) {
       t_mtl_name = IMIString::substr(t_mtl_name.c_str(), t_pos+1);
    }
    t_pos = t_mtl_name.rfind('/');
    if(t_pos>0) {
       t_mtl_name = IMIString::substr(t_mtl_name.c_str(), t_pos+1);
    }
    MTLPOOL::iterator it = m_mtlPool.find(t_mtl_name);
    if( it == m_mtlPool.end() ) {
        if(t_version == "1.0") {
            IMIMtlCorePtr t_mtl = MakeSharedPtr<IMIMtlCore>(mApp);
            t_mtl->m_mtl_name = t_mtl_name;
            t_mtl->fromJSON1(_obj);
            m_mtlPool.insert(std::make_pair(t_mtl_name, t_mtl));
            return t_mtl;
        }
    }
    return nullptr;
}

//
//  SVParseLUTFilter.cpp
//  SVEngine
//
//  Created by 徐子昱 on 2018/10/23.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "SVParseLUTFilter.h"
#include "../app/SVGlobalMgr.h"
#include "../file/SVFileMgr.h"
#include "../base/SVDataChunk.h"
#include "../app/SVInst.h"

using namespace sv;

SVFilterBasePtr SVParseLUTFilter::parseLUT(SVInstPtr _app,cptr8 _path, s32 resid){
    RAPIDJSON_NAMESPACE::Document t_doc;
    //解析滤镜包
    SVDataChunk tDataStream;
    bool tflag = _app->m_file_sys->loadFileContentStr(&tDataStream, _path);
    if (!tflag) {
        return nullptr;
    }
    SV_LOG_ERROR("SVParseMain::load effect sucess\n");
    if (!tDataStream.getPointer() ) {
        SV_LOG_ERROR("data stream is null");
        return nullptr;
    }
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse( (char*)(tDataStream.getPointer()) );
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        SV_LOG_ERROR("rapidjson error code:%d \n", code);
        return nullptr;
    }
    if (doc.HasMember("version")) {
        RAPIDJSON_NAMESPACE::Value &version = doc["version"];
    }
    if(doc.HasMember("filterLUT")&& doc["filterLUT"].IsObject()){
//        RAPIDJSON_NAMESPACE::Value &t_lut = doc["filterLUT"];
//        SVFilterLUTPtr t_filterLUT = MakeSharedPtr<SVFilterLUT>(_app);
//        t_filterLUT->fromJSON(t_lut);
//        return t_filterLUT;
        return nullptr;
    }
    return nullptr;
}

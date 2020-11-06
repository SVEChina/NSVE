//
//  IMIParseDeform.cpp
//  IMIngine
//
//  Created by 徐子昱 on 2018/10/29.
//  Copyright © 2018年 李晓帆. All rights reserved.
//

#include "IMIParseDeform.h"
#include "../core/IMIDeformImageMove.h"
#include "../rendercore/IMIRenderer.h"
#include "../rendercore/IMIRenderMgr.h"
#include "../operate/IMIOpParse.h"
#include "../work/IMIThreadPool.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../app/IMIInst.h"
#include "../mtl/IMITexMgr.h"
#include "../app/IMIInst.h"

using namespace imi;

IMIDeformImageMovePtr IMIParseDeform::parseDeform(IMIInstPtr app, RAPIDJSON_NAMESPACE::Value &item, s32 _resid, cptr8 _path){
    IMIDeformImageMovePtr m_deform = MakeSharedPtr<IMIDeformImageMove>(app);
//    IMITexturePtr t_innerTex = app->getRenderer()->getIMITex(E_TEX_MAIN);
//    m_deform->init(t_innerTex,t_innerTex);
//    m_deform->setIsDetect(true);
//    // m_deform->setvisiPoint(true);
//    m_deform->setFlip(true);
//    m_deform->m_rule=0;
//    m_deform->fromJSON(item);
    return m_deform;
}

void IMIParseDeform::parse(IMIInstPtr app,cptr8 path, s32 resid,IMIDeformImageMovePtr _deform) {
    RAPIDJSON_NAMESPACE::Document t_doc;
    //解析效果包
    IMIString t_path = IMIString(path) + IMIString("/");
    IMI_LOG_INFO("IMIParseMain::parse begin\n");
    IMIString config_name = t_path + "config.json";
    IMIDataChunk tDataStream;
    IMI_LOG_ERROR("IMIParseMain::parse begin config name %s\n", config_name.get());
    bool tflag = app->m_file_sys->loadFileContentStr(&tDataStream, config_name.get());
    if (!tflag)
        return ;
    IMI_LOG_ERROR("IMIParseMain::load effect sucess\n");
    IMI_LOG_ERROR("filedata %s\n", tDataStream.getPointerChar());
    if (!tDataStream.getPointerChar()) {
        IMI_LOG_ERROR("data stream is null");
        return ;
    }
    
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return ;
    }
    
    if (doc.HasMember("IMIDeform") && doc["IMIDeform"].IsObject()) {
        RAPIDJSON_NAMESPACE::Value &deformObj = doc["IMIDeform"];
        _deform->fromJSON(deformObj);
    }
    IMI_LOG_ERROR("IMIParseMain::parse end\n");
}

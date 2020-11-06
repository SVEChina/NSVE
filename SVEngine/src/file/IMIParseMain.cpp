//
// IMIParseMain.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIParseMain.h"
#include "../operate/IMIOpParse.h"
#include "../work/IMIThreadPool.h"
#include "../file/IMIFileMgr.h"
#include "../base/IMIDataChunk.h"
#include "../app/IMIInst.h"
#include "../mtl/IMITexMgr.h"
#include "../operate/IMIOpCreate.h"
#include "../basesys/IMIConfig.h"
#include "IMIParseDeform.h"
#include "IMIParseMask.h"
#include "IMIParseSprite.h"
#include "IMIParseBitfont.h"
#include "IMIParseBMFont.h"
#include "IMIParseParticles.h"
#include "IMIParseFrameAni.h"
#include "IMIParseBackground.h"
#include "IMIParseTexAttachment.h"
#include "IMIParseAniTrigger.h"
#include "IMIParseFilter.h"
#include "../module/IMIEffectPackage.h"
#include "../mtl/IMIParseLUTFilter.h"

using namespace imi;

IMIParseMain::IMIParseMain(IMIInstPtr _app)
:IMIGBaseEx(_app) {
    m_app = _app;
    _registDictionary("IMISpineNode", IMIParseAnimate::parseAnim);
    _registDictionary("IMIFrameAniNode", IMIParseFrameAni::parseFrameAni);
    _registDictionary("IMISpriteNode", IMIParseSprite::parseSprite);
    _registDictionary("IMIBitFontNode", IMIParseBitfont::parseBitfont);
    _registDictionary("IMIBMFontNode", IMIParseBMFont::parseBMFont);
    _registDictionary("IMIParticlesNode", IMIParseParticles::parseParticles);
}

IMIParseMain::~IMIParseMain(){
    parse_dictionary.clear();
}

void IMIParseMain::_registDictionary(cptr8 type, prase_content_fun fun) {
    if (!_hasRegist(type)) {
        parse_dictionary.append(type, fun);
    }
}

void IMIParseMain::_unregistDictionary(cptr8 type) {
    if ( _hasRegist(type) ) {
        parse_dictionary.remove(type);
    }
}

bool IMIParseMain::_hasRegist(cptr8 type) {
    PARSEPOOL::Iterator it = parse_dictionary.find(type);
    if(it!=parse_dictionary.end())
        return true;
    return false;
}

IMIModuleBasePtr IMIParseMain::parse(cptr8 path, s32 resid) {
    RAPIDJSON_NAMESPACE::Document t_doc;
    //解析效果包
    IMIString t_path = IMIString(path) + IMIString("/");
    IMI_LOG_INFO("IMIParseMain::parse begin\n");
    IMIString config_name = t_path + "config.json";
    IMIDataChunk tDataStream;
    IMI_LOG_ERROR("IMIParseMain::parse begin config name %s\n", config_name.get());
    bool tflag = mApp->m_file_sys->loadFileContentStr(&tDataStream, config_name.get());
    if (!tflag)
        return nullptr;
    IMI_LOG_ERROR("IMIParseMain::load effect sucess\n");
    IMI_LOG_ERROR("filedata %s\n", tDataStream.getPointerChar());
    if (!tDataStream.getPointer() ) {
        IMI_LOG_ERROR("data stream is null");
        return nullptr;
    }
    
    RAPIDJSON_NAMESPACE::Document doc;
    doc.Parse(tDataStream.getPointerChar());
    if (doc.HasParseError()) {
        RAPIDJSON_NAMESPACE::ParseErrorCode code = doc.GetParseError();
        IMI_LOG_ERROR("rapidjson error code:%d \n", code);
        return nullptr;
    }
    if (doc.HasMember("version")) {
        RAPIDJSON_NAMESPACE::Value &version = doc["version"];
    }
    IMIString t_type = "gift";
    if (doc.HasMember("type") && doc["type"].IsString()) {
        RAPIDJSON_NAMESPACE::Value &type = doc["type"];
        t_type = type.GetString();
    }
    IMIffectPackagePtr t_bundle = MakeSharedPtr<IMIffectPackage>(m_app);
    t_bundle->init();
    if (doc.HasMember("nodearray") && doc["nodearray"].IsArray()) {
        RAPIDJSON_NAMESPACE::Value &nodearray = doc["nodearray"];
        for(s32 i = 0; i<nodearray.Size(); i++){
            RAPIDJSON_NAMESPACE::Value &node = nodearray[i];
            for(auto iter = node.MemberBegin(); iter != node.MemberEnd(); ++iter){
                cptr8 key = (iter->name).GetString();
                if (node.HasMember(key)) {
                    RAPIDJSON_NAMESPACE::Value &item = iter->value;
                    IMINodePtr t_node = _callTypeParse(key, item, resid, t_path.get());
                    if (t_node) {
                        t_bundle->addEffectUnit(t_node);
                    }
                }
            }
        }
    }

    //parse tex attachment
    if (doc.HasMember("TexAttachment") && doc["TexAttachment"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &attachments = doc["TexAttachment"];
//        for (s32 i = 0; i<attachments.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &attachment = attachments[i];
//            IMIAniTexAttachmentPtr t_texAttachment = IMIParseTexAttachment::parseTexAttachmet(mApp, attachment, 102, t_path.get());
//            t_bundle->addAttachment(t_texAttachment);
//        }
    }
    
    //parse trigger
    if (doc.HasMember("triggerarray") && doc["triggerarray"].IsArray()) {
//        RAPIDJSON_NAMESPACE::Value &triggers = doc["triggerarray"];
//        for (s32 i = 0; i<triggers.Size(); i++) {
//            RAPIDJSON_NAMESPACE::Value &trigger = triggers[i];
//            IMIAniTriggerPtr t_trigger = IMIParseAniTrigger::parseAniTrigger(mApp, trigger, 102, t_path.get());
//            t_bundle->addTrigger(t_trigger);
//        }
    }
    
    if (doc.HasMember("IMILutFlter") && doc["IMILutFlter"].IsObject()) {
        RAPIDJSON_NAMESPACE::Value &attachments = doc["IMILutFlter"];
        IMIString t_name = attachments["name"].GetString();
        IMIString t_pathLut = t_path + t_name;
        IMIFilterBasePtr t_baseFilter = IMIParseLUTFilter::parseLUT(mApp,t_pathLut, 107);
        t_bundle->addFilter(t_baseFilter);
    }
    
    if (doc.HasMember("IMIFilter") && doc["IMIFilter"].IsObject()) {
        RAPIDJSON_NAMESPACE::Value &filterObj = doc["IMIFilter"];
        IMIFilterBasePtr t_baseFilter = IMIParseFilter::parseFilter(mApp, filterObj, resid, t_path.get());
        if (t_baseFilter) {
            t_bundle->addFilter(t_baseFilter);
        }
    }
    
    if (doc.HasMember("IMIDeform") && doc["IMIDeform"].IsObject()) {
        RAPIDJSON_NAMESPACE::Value &deformObj = doc["IMIDeform"];
        IMIDeformImageMovePtr t_deform = IMIParseDeform::parseDeform(mApp, deformObj, resid, t_path.get());
        if (t_deform) {
            t_bundle->addDefrom(t_deform);
        }
    }
    
    IMI_LOG_ERROR("IMIParseMain::parse end\n");
    return t_bundle;
}

IMINodePtr IMIParseMain::_callTypeParse(cptr8 type, RAPIDJSON_NAMESPACE::Value &item, s32 resid, cptr8 _path) {
    if(_hasRegist(type)) {
        prase_content_fun t_fun = parse_dictionary[type];
        if (t_fun) {
            return (*t_fun)(mApp, item, resid,_path);
        }
    }
    return nullptr;
}




















//
// IMIFontProcess.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFontProcess.h"
#include "../app/IMIInst.h"
#include "../app/IMIGlobalParam.h"
#include "../work/IMITdCore.h"
#include "../core/IMIBMFont.h"
#include "../event/IMIEventMgr.h"
#include "../event/IMIEvent.h"
#include "../file/IMIFileMgr.h"
#include "../file/IMIBMFontLoader.h"
#include "../node/IMIFreeTypeNode.h"

#ifdef CONFIG_IS_LOAD_FREETYPE
#include "ft2build.h"
#include "freetype.h"
#endif

using namespace imi;

IMIFontProcess::IMIFontProcess(IMIInstPtr _app)
:IMIProcess(_app) {
    m_lock = MakeSharedPtr<IMILock>();
#ifdef CONFIG_IS_LOAD_FREETYPE
    m_fontFace = nullptr;
    m_fontLib = nullptr;
    m_fontPixelSize = 64;
    m_fontCharSize = 16;
    //
    do {
        IMIString t_fullname = mApp->m_file_sys->getFileFullName(mApp->m_global_param.m_fontFileName.c_str());
        // 1. 初始化freetype2库
        FT_Error t_error = FT_Init_FreeType(&m_fontLib);
        if (FT_Err_Ok != t_error) {
            break;
        }
        // 2. 创建一个face
        t_error = FT_New_Face(m_fontLib, t_fullname.c_str(), 0, &m_fontFace);
        if (FT_Err_Ok != t_error) {
            FT_Done_Face( m_fontFace );
            FT_Done_FreeType( m_fontLib );
            m_fontFace = nullptr;
            m_fontLib = nullptr;
            break;
        }
        // 3. 设置字体尺寸 (大小 x 64 ) 设备水平分辨率 垂直分辨率
        t_error = FT_Set_Char_Size(m_fontFace, m_fontCharSize*64, m_fontCharSize*64, 0, 0);
        if (FT_Err_Ok != t_error) {
            FT_Done_Face( m_fontFace );
            FT_Done_FreeType( m_fontLib );
            m_fontFace = nullptr;
            m_fontLib = nullptr;
        }
        // 4. 设置实际像素大小
        t_error = FT_Set_Pixel_Sizes(m_fontFace, m_fontPixelSize, m_fontPixelSize);
        if (FT_Err_Ok != t_error) {
            FT_Done_Face( m_fontFace );
            FT_Done_FreeType( m_fontLib );
            m_fontFace = nullptr;
            m_fontLib = nullptr;
        }
    }while(0);
#endif
}

IMIFontProcess::~IMIFontProcess() {
    m_lock = nullptr;
#ifdef CONFIG_IS_LOAD_FREETYPE
    FT_Done_Face( m_fontFace );
    FT_Done_FreeType( m_fontLib );
    m_fontFace = nullptr;
    m_fontLib = nullptr;
#endif
    m_bmFonts.destroy();
}

bool IMIFontProcess::procEvent(IMIEventPtr _event){
    return true;
}

void IMIFontProcess::loadDefBMFont(){
    loadBMFont("svres/bmfont/chineses.fnt");
    loadBMFont("svres/bmfont/sveengine.fnt");
}

void IMIFontProcess::loadBMFont(cptr8 _path){
    m_lock->lock();
    IMIString t_path = _path;
    s32 pos = t_path.rfind('/');
    IMIString t_name = IMIString::substr(t_path.c_str(), pos+1, t_path.size() - pos - 1);
    bool t_result = false;
    for (s32 i = 0; i<m_bmFonts.size(); i++) {
        IMIBMFontPtr t_font = m_bmFonts[i];
        IMIString t_t_name = t_font->m_fntFileName;
        if (strcmp(t_name.c_str(), t_t_name.c_str()) == 0) {
            t_result = true;
        }
    }
    if (!t_result) {
        IMIBMFontPtr font = IMIBMFont::creatFnt(_path, mApp);
        if (font) {
            m_bmFonts.append(font);
        }
    }
    m_lock->unlock();
}

IMIBMFontPtr IMIFontProcess::getBMFont(cptr8 _name){
    for (s32 i = 0; i<m_bmFonts.size(); i++) {
        IMIBMFontPtr t_font = m_bmFonts[i];
        IMIString t_t_name = t_font->m_fntFileName;
        if (strcmp(_name, t_t_name.c_str()) == 0) {
            return t_font;
        }
    }
    return nullptr;
}

void IMIFontProcess::removeBMFont(cptr8 _name){
    m_lock->lock();
    for (s32 i = 0; i<m_bmFonts.size(); i++) {
        IMIBMFontPtr t_font = m_bmFonts[i];
        IMIString t_t_name = t_font->m_fntFileName;
        if (strcmp(_name, t_t_name.c_str()) == 0) {
            m_bmFonts.removeForce(i);
            break;
        }
    }
    m_lock->unlock();
}

void IMIFontProcess::getAllBMFontNames(IMIArray<IMIString> &_array){
    m_lock->lock();
    for (s32 i = 0; i<m_bmFonts.size(); i++) {
        IMIBMFontPtr t_font = m_bmFonts[i];
        IMIString t_t_name = t_font->m_fntFileName;
        _array.append(t_t_name);
    }
    m_lock->unlock();
}

#ifdef CONFIG_IS_LOAD_FREETYPE
FT_Library IMIFontProcess::getFontLib(){
    return m_fontLib;
}

FT_Face IMIFontProcess::getFontFace(){
    return m_fontFace;
}

s32 IMIFontProcess::getFontPixelSize(){
    return m_fontPixelSize;
}

#endif

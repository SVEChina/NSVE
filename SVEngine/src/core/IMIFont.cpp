//
// IMIFont.cpp
// IMIngine
// Copyright 2017-2020
// yizhou.Fu
//

#include "IMIFont.h"

using namespace imi;

IMIFont::IMIFont(IMIInstPtr _app)
:IMIGBaseEx(_app) {

}

IMIFont::~IMIFont() {
    
}

void IMIFont::init(){
    
}

void IMIFont::setTextEncoding(IMIFONTTEXTENCODING _encoding){
    m_encoding = _encoding;
}

IMIFont::IMIFONTTEXTENCODING IMIFont::getTextEncoding(){
    return m_encoding;
}

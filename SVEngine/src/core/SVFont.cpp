//
// SVFont.cpp
// SVEngine
// Copyright 2017-2020
// yizhou Fu,long Yin,longfei Lin,ziyu Xu,xiaofan Li,daming Li
//

#include "SVFont.h"

using namespace sv;

SVFont::SVFont(SVInstPtr _app)
:SVGBaseEx(_app) {

}

SVFont::~SVFont() {
    
}

void SVFont::init(){
    
}

void SVFont::setTextEncoding(SVFONTTEXTENCODING _encoding){
    m_encoding = _encoding;
}

SVFont::SVFONTTEXTENCODING SVFont::getTextEncoding(){
    return m_encoding;
}

#include "SVGBase.h"
#include "../app/SVInst.h"

using namespace sv;

SVGBaseEx::SVGBaseEx(SVInstPtr _app)
:mApp(_app){
    if(mApp) {
        m_uid = mApp->m_IDPool.applyUID();
    }else{
        m_uid = -1;
    }
}

SVGBaseEx::~SVGBaseEx(){
    if(mApp) {
        mApp->m_IDPool.returnUID(m_uid);
        mApp = nullptr;
    }
}


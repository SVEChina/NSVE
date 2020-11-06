#include "IMIGBase.h"
#include "../app/IMIInst.h"

using namespace imi;

IMIGBaseEx::IMIGBaseEx(IMIInstPtr _app)
:mApp(_app){
    if(mApp) {
        m_uid = mApp->m_IDPool.applyUID();
    }else{
        m_uid = -1;
    }
}

IMIGBaseEx::~IMIGBaseEx(){
    if(mApp) {
        mApp->m_IDPool.returnUID(m_uid);
        mApp = nullptr;
    }
}


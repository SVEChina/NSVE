#include "SVGBase.h"
#include "../app/SVInst.h"

using namespace sv;

SVGBaseEx::SVGBaseEx(SVInstPtr _app)
:mApp(_app){
}

SVGBaseEx::~SVGBaseEx(){
    mApp = nullptr;
}

